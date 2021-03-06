#include <cstring>
#include <cstdint>
#include "EncodedString.h"

EncodedString::EncodedString() : _size(0) {
    _str = new char[1];
    _str[0] = (char)0xff;
}

EncodedString::EncodedString(const char* str) {
    size_t i;

    i = 0;
    while (str[i] != (char)0xff)
        i++;
    _size = i;
    _str = new char[i + 1];
    memcpy(_str, str, i + 1);
}

EncodedString::EncodedString(const EncodedString& other) : _size(other._size) {
    _str = new char[_size + 1];
    memcpy(_str, other._str, _size + 1);
}

EncodedString::~EncodedString() {
    delete[] _str;
}

EncodedString& EncodedString::operator=(const EncodedString& other) {
    delete[] _str;
    _size = other._size;
    _str = new char[_size + 1];
    memcpy(_str, other._str, _size + 1);

    return *this;
}

const char* EncodedString::str() const {
    return _str;
}

const char* EncodedString::unicode() const {
    static const char* kCharset =
        " !\"#$%&'()*+,-./"
        "0123456789:;<=>?"
        "@ABCDEFGHIJKLMNO"
        "PQRSTUVWXYZ[\\]^_"
        "`abcdefghijklmno"
        "pqrstuvwxyz{|}~ "
        "ÄÅÇÉÑÖÜáàâäãåçéè"
        "êëíìîïñóòôöõúùûü"
        "♥°¢£↔→♪ßα  ´¨≠ÆØ"
        "∞±≤≥¥µ∂ΣΠπ⌡ªºΩæø"
        "¿¡¬√ƒ≈∆«»… ÀÃÕŒœ"
        "–—“”‘’÷◊ÿŸ⁄ ‹›ﬁﬂ"
        "■‧‚„‰ÂÊÁËÈÍÎÏÌÓÔ"
        " ÒÚÛÙıˆ˜¯˘˙˚¸˝˛ˇ"
        "       ";

    static char buffer[16384];

    for (size_t i = 0; i < _size + 1; ++i)
        buffer[i] = kCharset[_str[i]];

    return buffer;
}

size_t EncodedString::size() const {
    return _size;
}

EncodedString EncodedString::from_unicode(const char* str) {
    static char buffer[16384];
    static const uint8_t kReverseCharset[256] = {
        0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    size_t len;

    len = strlen(str);
    for (size_t i = 0; i < len + 1; ++i)
        buffer[i] = kReverseCharset[str[i]];
    return EncodedString(buffer);
}
