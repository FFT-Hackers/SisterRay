#ifndef SISTER_RAY_GAME_STRUCTS_H
#define SISTER_RAY_GAME_STRUCTS_H

#include <SisterRay/types.h>

//This struct has size 260h and is referenced by the main context ptr
#pragma pack(push, 1)
typedef struct {
    u32 attackerID; //0x00
    u32 attackerLevel; //0x04
    u32 attackerEnemyIndex; //0x08
    u32 commandIndex; //0x0C
    u32 attackIndex; //0x10
    u32 animationBaseOffset; //0x14
    u32 targetMask; //0x18
    u32 activeAllies; //0x1C
    u32 animationScriptID; //0x20
    u32 AttackEffectID; //0x24
    u32 actionIDCopy; //0x28
    u32 attackIDCopy; //0x2C
    u32 attackerMask; //0x30
    u32 partofAttackerMask; //034
    u32 MPCost; //0x38
    u32 hitChance; //0x3C
    u32 damageFormulaID; //0x40
    u32 attackElementsMask; //0x44
    u32 abilityPower; //0x48
    i32 attackerAtk; //0x4C
    u32 targetStateMask; //0x50
    u32 impactSound; //0x54
    u32 critkSound; //0x58
    u32 missAtkSound; //0x5C
    u32 cameraDataSingle; //0x60
    u32 cameraDataMultiple; //0x64
    u32 impactEffectID; //0x68
    u32 specialAbilityFlags; //0x6C
    u8 padding1[8]; //0x70, 0x74
    u32 damageCalcMask; //0x78
    u32 unkTHATCRASHEDTHEGAME; // 0x7C
    u32 addStatusMask; //0x80
    u32 rmStatusMask; //0x84
    u32 changeStatusMask; //0x88
    u32 inflictStatusChange; //0x8C
    u32 miscActionflags; //0x90
    u32 targetMaskCopy; //0x94
    u32 attackIndexCopy; //0x98
    u8 padding2[4];
    u32 formulaType; //0xA0
    u32 formulaID; //0xA4
    u32 SenseFlag; //0xA8
    u32 unkDWord1; //0xAC
    u32 attackHitCount; //0xB0
    u32 doubleCutRelated; //0xB4
    u32 targetCount; //0xB8
    u32 additionalEffects; //0xBC
    u32 additionalEffectsModifer; //0xC0
    u32 abilityPowerCopy; //0xC4
    u32 attackerStatusMask; //0xC8
    u32 miscAttackData; //0xCC
    u32 unkDWord2; //0xD0
    u32 unkDWord3; //0xD4
    u32 throwFormulaPower; //0xD8
    u32 displayString; //0xDC
    u32 incOnDamageDealt; //0xE0
    u32 unkDWord4; //0xE4
    u32 MPTurboBoost; //0xE8
    u32 targetMaskCopy2; //0xEC
    u32 addedCutMPHPAbsorbByte; //0xF0
    u32 currentUnitIDTempt; //0xF4
    u32 unkDWord5; //0xF8
    u32 hitCountCopy; //0xFC
    /*256 unused bytes*/
    u8 padding3[0x100];
    u32 targetObjectBlock1Ptr; //0x200
    u32 targetObjectBlock2Ptr; //0x204
    u32 targetID; //0x208
    u32 targetEnemyIndex; //0x20C
    u32 targetDefense; //0x210
    u32 currentDamage; //0x214
    u32 abilityFlags1; //0x218
    u32 unkDWord6; //0x21C
    u32 abilityFlags2; //0x220
    u32 unkActionID; //0x224
    u32 targetStatusMask; //0x228
    u32 targetStatusImmuneMask; //0x22C
    u32 elementalDefenseMask; //0x230
    u32 targetStateFlags; //0x234
    u32 addStatusMaskCopy; //0x238
    u32 rmStatusMaskCopy; //0x23C
    u32 changeStatusMaskCopy; //0x240
    u32 combinedStatusMask; //0x244
    u32 attackImpactSound; //0x248
    u32 attackImpactEffectID; //0x24C
    u32 killRecoverDamage; //0x250
    u32 targetLevel; //0x254
    u32 targetCurrentHP; //0x258
    u32 targeCurrentMP; //0x25C
    u32 hitChanceCopy; //0x260
} DamageCalcStruct;
#pragma pack(pop)

#define gDamageContextPtr   ((DamageCalcStruct*)0x0099E308)

//An array of size ACTOR_ARRAY_SIZE w/ elements of size 0x68 exists at ARRAY_ACTOR_START
#pragma pack(push, 1)
typedef struct {
    u32     statusMasks;
    u32     stateFlags;
    u8      index;
    u8      level;
    u8      unknown0;
    u8      elementDamageMask;
    u8      characterID;
    u8      physAtk;
    u8      magAtk;
    u8      pEvade;
    u8      idleAnimID;
    u8      damageAnimID;
    u8      backDamageMult;
    u8      sizeScale;
    u8      dexterity;
    u8      luck;
    u8      idleAnimHolder;
    u8      lastCovered;
    u16     lastTargets;
    u16     prevAttackerMask;
    u16     prevPhysAttackerMask;
    u16     prevMagAttackerMask;
    u16     Defense;
    u16     MDefense;
    u16     formationID;
    u16     absorbedElementsMask;
    u16     currentMP;
    u16     maxMP;
    i32     currentHP;
    i32     maxHP;
    u32     unknown1;
    u32     unknown2;
    u32     unknown3;
    u32     unknown4;
    u32     initalStatusMasks;
    u32     unknown5;
    u8      unknown6;
    u8      mEvade;
    u8      actorRow;
    u8      cameraData;
    u16     gilStolen;
    u16     itemStolen;
    u16     unknown7;
    u16     apValue;
    u32     gilValue;
    u32     expValue;
    u8      unused8;
    u8      unused9;
    u16     unused10; //This is being used for the tactical elements mod, unused in original game
    u8      unused12;
    u8      unused13;
    u8      unused14;
    u8      unused15;

} ActorBattleVars;
#pragma pack(pop)

#define gAiActorVariables   ((ActorBattleVars*)0x009AB0DC)

/*Should  have size 0x1AEC*/
#pragma pack(push, 1)
typedef struct {
	u16 ActorID; //BE1170
	u8 padding1[6]; //BE1171
	u16 AnimationData; //BE1178
	u16 commandAnimID; //BE117A
	u8 padding2[30]; //BE117C
	u8 AnimationEffect; //BE119A
	u8 commandID; //BE119B
	u8 padding3[0x1AC0];
} BigAnimBlock;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	i8 PoisonTimer;
	u8 padding[43];
} ActorTimerBlock;
#pragma pack(pop)

#define gBigAnimBlock       ((BigAnimBlock*)0x00BE1170)
#define gActorTimerBlock    ((ActorTimerBlock*)0x009A8B26)

#pragma pack(push, 1)
typedef struct {
    u16 something;
    u16 something2;
    u16 something3;
} enabledCommandStruct;
#pragma pack(pop)

/*This is the structure of attack data*/
typedef struct {
    u8 padding[0x1C];
} attackData;

/*This contains a bit vector of flags for spells*/
#pragma pack(push, 1)
typedef struct {
    u8 magicIndex;
    u8 mpCost;
    u8 allCount;
    u8 quadEnabled;
    u8 quadCount;
    u8 targetData;
    u16 propertiesMask;
} spellFlags;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    u32 statToIncrease;
    u32 increaseValue;
} statIncrease;
#pragma pack(pop)

#pragma pack(push, 1)
/*Three of these are maintained for each active party member, they have size 0x440*/
typedef struct {
    u8 characterID; //0x00
    u8 coverChance; //0x01
    u8 strength; //0x02
    u8 vitality; //0x03
    u8 magic; //0x04
    u8 spirit; //0x05
    u8 speed; //0x06
    u8 luck; //0x07
    u16 physAttack; //0x08
    u16 physDefense; //0x0A
    u16 magAttack; //0x0C
    u16 magDefense; //0x0E
    u16 currentHP; //0x10
    u16 maxHP; //0x12
    u16 currentMP; //0x14
    u16 maxMP; //0x16
    u32 timer; //0x18
    u16 counterActionIndex; //0x1C
    u16 counterChance; //0x1E
    u8 padding; //0x20
    u16 unknownDiviosr; //0x21
    u8 characterFlags; //0x23
    u8 unknown24bitInts[24]; //0x24
    u16 attackElementsMask; //0x3C
    u16 halvedElementsMask; //003E
    u16 nulledElementsMask; //0x40
    u16 absorbeElementsMask; //0x42
    u32 attackStatusesMask; //0x44
    u32 immuneStatusesMask; //0x48
    enabledCommandStruct enabledCommandArray[0x10]; //0x4C
    u8 unknownbytes[8]; //0xAC
    attackData enabledLimitData[3]; //0xB4
    spellFlags enabledMagicsData[54]; //0x108
    spellFlags unusedMagics[2]; //0x2B8
    spellFlags enabledSummons[16]; //0x2C8
    spellFlags enabledEnemySkills[24]; //0x348
    u8 weaponData[5]; //0x408
    u16 weaponStatus; //0x40D
    u8 lepad;
    u8 weaponAccuracy; //0x410
    u8 paddin[7];
    u32 additionalAttackElements;
    statIncrease statsToIncrease[4];
    u8 charGilBonus;
    u8 encounterRate;
    u8 chocoboChance;
    u8 preEmptiveChance;
} activePartyMemberStruct;
#pragma pack(pop)

#define activePartyStructArray   ((activePartyMemberStruct*)0xDBA498)

#pragma pack(push, 1)
typedef struct {
    u8 character_id;
    u8 level;
    u8 strength;
    u8 vitality;
    u8 magic;
    u8 spirit;
    u8 dexterity;
    u8 luck;
    u8 bonus_strength;
    u8 bonus_vitality;
    u8 bonus_magic;
    u8 bonus_spirit;
    u8 bonus_dexterity;
    u8 bonus_luck;
    u8 active_limit_level;
    u8 limit_bar_progress;
    u8 character_name[12];
    u8 equipped_weapon;
    u8 equipped_armor;
    u8 equipped_accessory;
    u8 out_of_battle_status;
    u8 character_row;
    u8 level_progress;
    u16 learned_limits;
    u16 character_kills;
    u16 limit_1A_uses;
    u16 limit_2A_uses;
    u16 limit_3A_uses;
    u16 current_HP;
    u16 base_HP;
    u16 current_MP;
    u16 base_MP;
    u8 unknown[4];
    u16 max_HP;
    u16 max_MP;
    u32 current_EXP;
    u32 weapon_materia_slots[8];
    u32 armor_materia_slots[8];
    u32 exp_to_next_level;
} characterRecord;
#pragma pack(pop)

#define CHARACTER_RECORD_ARRAY ((characterRecord*)0xDBFD8C)

#pragma pack(push, 1)
typedef struct {
    u32 relativeColumnIndex;
    u32 relativeRowIndex;
    u32 viewColumnBound;
    u32 viewRowBound;
    u32 baseColumnIndex;
    u32 baseRowIndex;
    u32 maxColumnBound;
    u32 maxRowBound;
    u32 ninth_dword;
    u32 tenth_dword;
    u32 eleventh_dword;
    u32 twelth_dword;
    u32 thirteenth_dword;
    u32 fourteenh_dword;
} cursorContext;
#pragma pack(pop)
#endif
