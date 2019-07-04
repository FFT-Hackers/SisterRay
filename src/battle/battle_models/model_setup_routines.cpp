#include "model_setup_routines.h"
#include "../../impl.h"
#include "../../party/party_utils.h"

typedef void(*PFNSRSUB42B4AF)();
#define sub_42B4AF  ((PFNSRSUB42B4AF)0x42B4AF)

typedef void(*PFNSRSUB42B579)();
#define sub_42B579  ((PFNSRSUB42B579)0x42B579)

typedef void(*PFNSRSUB42BC15)(u8);
#define initEnemyModelsFromAB   ((PFNSRSUB42BC15)0x42BC15)

typedef void(*PFNSRSUB42B66A)(u8);
#define copyDataFromBFile  ((PFNSRSUB42B66A)0x42B66A)

/*Rewritten because we are now initializing b-data dynamically, so do not want the original
  loops which could only initialize a fixed number of animations scripts*/
void translateEnemyABData() {
    u8* battleType = (u8*)0xBFD0E0;
    u8* byte_BF2DF8 = (u8*)0xBF2DF8;
    u8* enemyCountGlobal = (u8*)0xBF2050;
    ModelPositionStruct* actorPositionArray = (ModelPositionStruct*)(0xBFD0A0);
    EnemyPositionStruct* enemyInitialPositionArray = (EnemyPositionStruct*)(0xBF2056);

    for (u16 enemyActorIdx = 4; enemyActorIdx < (*enemyCountGlobal) + 4; ++enemyActorIdx) {
        MODEL_DATA_74_ARRAY[enemyActorIdx].modelDataIndex = 0;
        initEnemyModelsFromAB(enemyActorIdx);
        byte_BF2DF8[enemyActorIdx] = UNK_ACTOR_STRUCT_ARRAY[enemyActorIdx].field_1;
        actorPositionArray[enemyActorIdx].xPosition = enemyInitialPositionArray[(enemyActorIdx - 4)].enemyPosition.xPosition;
        actorPositionArray[enemyActorIdx].yPosition = enemyInitialPositionArray[(enemyActorIdx - 4)].enemyPosition.yPosition;
        actorPositionArray[enemyActorIdx].zPosition = enemyInitialPositionArray[(enemyActorIdx - 4)].enemyPosition.zPosition;
        gBigAnimBlock[enemyActorIdx].field_162 = 0;
        gBigAnimBlock[enemyActorIdx].field_15E = 0;
        switch (*battleType) {
            case 1: {
                gBigAnimBlock[enemyActorIdx].field_18 = 2048;
                gBigAnimBlock[enemyActorIdx].field_160 = 0;
                break;
            }
            case 3:
            case 5:
            case 6:
            case 7: {
                if (actorPositionArray[enemyActorIdx].zPosition >= 0) {
                    gBigAnimBlock[enemyActorIdx].field_160 = 2048;
                    gBigAnimBlock[enemyActorIdx].field_18 = 2048;
                }
                else {
                    gBigAnimBlock[enemyActorIdx].field_160 = 0;
                    gBigAnimBlock[enemyActorIdx].field_18 = 0;
                }
                break;
            }
            default: {
                if (actorPositionArray[enemyActorIdx].zPosition >= 0) {
                    gBigAnimBlock[enemyActorIdx].field_160 = 0;
                    gBigAnimBlock[enemyActorIdx].field_18 = 0;
                }
                else {
                    gBigAnimBlock[enemyActorIdx].field_160 = 2048;
                    gBigAnimBlock[enemyActorIdx].field_18 = 2048;
                }
                break;
            }
        }
    }
}

void translatePlayerABData() {
    u8* gCharacterModelCount = (u8*)(0xBF2E0C);
    u8* battleType = (u8*)0xBFD0E0;
    u8* byte_BF2DF8 = (u8*)0xBF2DF8;
    ModelPositionStruct* actorPositionArray = (ModelPositionStruct*)(0xBFD0A0);
    TwoMemberPositionStruct* twoPartyPositionArray = (TwoMemberPositionStruct*)(0x7C23B0);
    FullPartyPositionStruct* fullPartyPositionArray = (FullPartyPositionStruct*)(0x7C2298);
    UnkTwoPartyStruct* twoPartyAngles = (UnkTwoPartyStruct*)(0x7C24B8);

    *gCharacterModelCount = 0;
    for (auto partyIdx = 0; partyIdx < 3; ++partyIdx) {
        MODEL_DATA_74_ARRAY[partyIdx].modelDataIndex = partyIdx; //The other model data struct, which I do not yet understand
        if (UNK_ACTOR_STRUCT_ARRAY[partyIdx].characterID != 0xFF) {
            copyDataFromBFile(partyIdx);
            *gCharacterModelCount = *gCharacterModelCount + 1;
        }
    }

    /*If there is one party member*/
    switch (*gCharacterModelCount) {
        case 1: {
            sub_42B4AF();
            for (auto partyIdx = 0; partyIdx < 3; ++partyIdx) {
                actorPositionArray[partyIdx].xPosition = 0;
                actorPositionArray[partyIdx].yPosition = fullPartyPositionArray[*battleType].enemyPosition[partyIdx].yPosition;
                actorPositionArray[partyIdx].zPosition = fullPartyPositionArray[*battleType].enemyPosition[partyIdx].zPosition;
            }
            sub_42B579();
        }
        case 2: {
            auto relIndex = 0;
            for (auto partyIdx = 0; partyIdx < 3; ++partyIdx) {
                if (UNK_ACTOR_STRUCT_ARRAY[partyIdx].characterID != 0xFF) {
                    if (UNK_ACTOR_STRUCT_ARRAY[partyIdx].field_6 & 1) {
                        if (twoPartyAngles[*battleType].angles[relIndex])
                            twoPartyPositionArray[*battleType].enemyPosition[relIndex].zPosition -= 516;
                        else
                            twoPartyPositionArray[*battleType].enemyPosition[relIndex].zPosition += 516;
                    }

                    actorPositionArray[partyIdx].xPosition = twoPartyPositionArray[*battleType].enemyPosition[relIndex].xPosition;
                    actorPositionArray[partyIdx].yPosition = twoPartyPositionArray[*battleType].enemyPosition[relIndex].yPosition;
                    actorPositionArray[partyIdx].zPosition = twoPartyPositionArray[*battleType].enemyPosition[relIndex].zPosition;


                    gBigAnimBlock[partyIdx].field_18 = twoPartyAngles[*battleType].angles[relIndex];
                    if (*battleType == 2)
                        gBigAnimBlock[partyIdx].field_160 = 0;
                    else
                        gBigAnimBlock[partyIdx].field_160 = twoPartyAngles[*battleType].angles[relIndex];
                    gBigAnimBlock[partyIdx].field_162 = 0;
                    gBigAnimBlock[partyIdx].field_15E = 0;
                    ++relIndex;
                }
            }
        }
        default: {
            sub_42B4AF();
            for (auto partyIdx = 0; partyIdx < 3; ++partyIdx) {
                actorPositionArray[partyIdx].xPosition = fullPartyPositionArray[*battleType].enemyPosition[partyIdx].xPosition;
                actorPositionArray[partyIdx].yPosition = fullPartyPositionArray[*battleType].enemyPosition[partyIdx].yPosition;
                actorPositionArray[partyIdx].zPosition = fullPartyPositionArray[*battleType].enemyPosition[partyIdx].zPosition;
            }
            sub_42B579();
        }
    }

    for (auto partyIdx = 0; partyIdx < 3; ++partyIdx) {
        byte_BF2DF8[partyIdx] = UNK_ACTOR_STRUCT_ARRAY[partyIdx].field_1;
        u8* byteViewAnimBlock = (u8*)&(gBigAnimBlock[partyIdx].characterID);
        gBigAnimBlock[partyIdx].restingPosition.xCoordinate = actorPositionArray[partyIdx].xPosition;
        gBigAnimBlock[partyIdx].restingPosition.yCoordinate = actorPositionArray[partyIdx].yPosition;
        gBigAnimBlock[partyIdx].restingPosition.zCoordinate = actorPositionArray[partyIdx].zPosition;
    }
}

typedef void(*SRPFNSUB66335F)(u8, u8, u8);
#define sub_66335F    ((SRPFNSUB66335F)0x66335F)

typedef void(*SRPFNSUB68CF75)(u8, LocalWeaponStruct*);
#define zeroWeaponStruct ((SRPFNSUB68CF75)0x68CF75)

typedef i32(*SRPFNSUB66101A)();
#define sub_66101A ((SRPFNSUB66101A)0x66101A)

typedef u8(*SRPFNSUB429343)(i32);
#define sub_429343 ((SRPFNSUB429343)0x429343)

typedef void(*SRPFNSUB684F73)(LocalWeaponStruct*, void*);
#define sub_684F73  ((SRPFNSUB684F73)0x684F73)

typedef void(*SRPFNSUB5E0DDE)(u16, u16, u16, u16, BattleModel*);
#define playWeaponAnimation   ((SRPFNSUB5E0DDE)0x5E0DDE)

typedef float*(*SRPFNSUB67C9BE)(u32, MatrixStruct*);
#define getMatrix     ((SRPFNSUB67C9BE)0x67C9BE)

typedef void(*SRPFNSUB6616CF)(void*, float*);
#define sub_6616CF    ((SRPFNSUB6616CF)0x6616CF)

/*This function offsets the animation index that is playing and animations the weapon*/
void playCorrectWeaponAnimation(u32 actorIdx) {
    int v5; 
    int v6; 
    LocalWeaponStruct localWeaponStruct;
    int v14;
    u32* dword_90C9F0 = (u32*)(0x90C9F0);
    u8* byte_BE0E30 = (u8*)(0xBE0E30);

    if (!(*dword_90C9F0))
        return;

    auto& modelState = gBigAnimBlock[actorIdx];
    if (!(modelState.field_25 & 4)) {
        sub_66335F(modelState.field_28, modelState.unkActorFlags, modelState.field_2A);
        
        auto actorDataPtr = getActivePartyMember(actorIdx);
        if (!actorDataPtr)
            return;

        BattleModel* modelData = (BattleModel *)modelState.modelDataPtr;
        if (!modelData) {
            return;
        }

        u8 weaponModelID = actorDataPtr->weaponData.weapon_model & 0xF;
        ModelSkeleton* weaponDataPtr = modelData->weaponModels[weaponModelID];
        if (!weaponDataPtr) {
            return;
        }

        LocalWeaponStruct* structPtr = &localWeaponStruct;
        zeroWeaponStruct(0, structPtr);
        //This logic is very strange
        (*((u32*)&structPtr->unkBytes[8])) = sub_66101A();
        structPtr->unkBytes[11] = sub_429343(modelState.field_14);
        //End strange logic
        if (modelState.field_28 || modelState.unkActorFlags || modelState.field_2A) {
            structPtr->unkBytes[0] = 9;
        }
        else {
            structPtr->unkBytes[0] = 10;
        }

        /*Probably modulate opacity based on fraction of HP*/
        /*bool isUltimaWeapon = (!modelState.characterID && weaponModelID == 15);
        if (isUltimaWeapon) {
            if (modelState.field_3F & 8) {
                v6 = 0;
                void * ffContext = GetContext();  // This is a graphics/game context object, it is large so I don't want to define so it's a void* for now
                sub_660C9A(ffContext);
            }
            else {
                v6 = 1;
            }
            sub_685028(v6, (void(__cdecl *)(u32, u32)(0x4303BE)), weaponDataPtr);
            sub_66C4BC(-4, weaponDataPtr);
            i32 cloudHPRatio = sub_6DC910();
            sub_685028(cloudHPRatio, (void(__cdecl *)(u32, u32))(0x68F758), weaponDataPtr);
        }*/

        sub_684F73(structPtr, weaponDataPtr);
        modelData->unk1 = 0;
        modelData->unk2 = 0;

        std::string& modelName = gContext.party.get_element(getPartyKey(actorIdx)).modelName;
        u16 weaponOffset = 0;
        if (modelState.setForLimitBreaks) {
            weaponOffset = 8;
        }
        else {
            weaponOffset = gContext.battleAnimations.get_element(modelName).modelAnimationCount;
        }
        srLogWrite("Animating weapon offset %i for model %s", weaponOffset, modelName);
        playWeaponAnimation(modelState.setForLimitBreaks, modelState.tableRelativeModelAnimIdx + weaponOffset, modelState.currentPlayingFrame, weaponModelID, modelData);
        float* matrix = getMatrix(0, weaponDataPtr->bonesArray->polygonData->texDataPtr->texMatrices->matrixStructPtr);
        sub_6616CF(&(byte_BE0E30[64 * actorIdx]), matrix);
    }
}