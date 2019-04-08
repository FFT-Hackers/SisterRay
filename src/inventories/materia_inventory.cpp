#include "materia_inventory.h"
#include "../impl.h"
#include <memory>

SrMateriaInventory::SrMateriaInventory(i16 allocation_size) : SrResourceRegistry<MateriaInventoryEntry>(allocation_size) {
    for (i32 i = 0; i < MATERIA_INVENTORY_SIZE; i++) {
        MateriaInventoryEntry entry = {
            0xFF,
            0
        };
        add_resource(entry);
    }
}

/*there's some other things that normally happen when this is called*/
void SrMateriaInventory::insertIntoMateriaInventory(MateriaInventoryEntry* entry) {
    u16 inventoryIndex;
    for (auto it = begin(resource_registry); it != end(resource_registry); ++it) {
        if ((*it).item_id == 0xFFFF) {
            inventoryIndex = distance(resource_registry.begin(), it);
            update_resource(inventoryIndex, *entry);

            if (returnMateriaType(entry->item_id) == 10) // if Summon Materia
                *enabledSpellTypeMask = *enabledSpellTypeMask | 1u; //enable summons on magic menu
            if (entry->item_id == 44)   // Enemy Skill Case
                *enabledSpellTypeMask = *enabledSpellTypeMask | 2u; //enable eskill on magic menu
            sub_6CC2C9(entry->item_id);
        }
    }
}

void SrMateriaInventory::removeFromMateriaInventory(u8* inventory_index) {
}

SISTERRAY_API void initMateriaInventory() {
    gContext.materia_inventory = std::make_unique<SrMateriaInventory>(MATERIA_INVENTORY_SIZE);
    srLogWrite("sister ray: inventory initialized with capacity: %lu", (unsigned long)gContext.inventory->current_capacity());
}