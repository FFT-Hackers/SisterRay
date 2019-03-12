#ifndef MENU_H
#define MENU_H

#include <SisterRay/types.h>
#include <SisterRay/SisterRay.h>

enum color { COLOR_GRAY, COLOR_UNKNOWN_1, COLOR_RED, COLOR_UNKNOWN_2, COLOR_UNKNOWN_3, COLOR_TEAL, COLOR_GREEN, COLOR_WHITE };
#pragma pack(push, 1)
typedef struct {
    u16 viewSize;
    u16 maxRows;
    u16 baseRow;
    u16 position1;
    u16 position2;
    u16 position3;
    u16 position4;
} sideScrollerArguments;
#pragma pack(pop)

// Todo: Pixel count to figure out which draw distance is which
#pragma pack(push, 1)
typedef struct {
    u16 drawDistance1;
    u16 drawDistance2;
    u16 drawDistance3;
    u16 drawDistance4;
    float boxFloat;
} drawBoxParams;
#pragma pack(pop)

typedef struct {
    i32 xCoordinate;
    i32 yCoordinate;
    char* stringToDraw;
    color textColor;
    float textThickness;
} drawTextParams;

typedef struct {
    i32 xCoordinate;
    i32 yCoordinate;
    u32 numberToDraw;
    u8 charCount;
    color numberColor;
    float numberThickness;
} drawNumberParams;

#define menuWindowConfig ((drawBoxParams*)0x921C78)
#define equipMenuWindowConfig ((drawBoxParams*)0x920AC8)

#endif
