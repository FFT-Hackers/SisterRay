#ifndef SR_EVENTS_H
#define SR_EVENTS_H

#include "types.h"
#include "srparty.h"
#include "srwidgets.h"
#include "game_data_types.h"
#include "srparty.h"

typedef enum {
    NO_TYPE,
    INIT_EQUIP_MENU,
    DRAW_EQUIP_MENU,
    INIT_STATUS_MENU,
    DRAW_STATUS_MENU,
    INIT_INVENTORY_MENU,
    DRAW_INVENTORY_MENU,
    INIT_MATERIA_MENU,
    DRAW_MATERIA_MENU,
    DRAW_MATERIA_DATA, //Dispatches on keyed subtypes
    INIT_BATTLE_MENU,
    DRAW_BATTLE_MENU,
    DRAW_BATTLE_COMMAND,
    INIT_BATTLE_COMMAND,
    DRAW_BATTLE_SPELL,
    INIT_BATTLE_SPELL,
    DRAW_BATTLE_SUMMON,
    INIT_BATTLE_SUMMON,
    DRAW_BATTLE_ESKILL,
    INIT_BATTLE_ESKILL,
    DRAW_BATTLE_ITEM,
    INIT_BATTLE_ITEM,
    INIT_BATTLE_CHANGE,
    MENU_INPUT_OK,
    MENU_INPUT_CANCEL,
    MENU_INPUT_SQUARE,
    MENU_INPUT_TRIANGLE,
    MENU_INPUT_R2,
    MENU_INPUT_R1,
    MENU_INPUT_L1,
    MENU_INPUT_RIGHT,
    MENU_INPUT_LEFT,
    MENU_INPUT_UP,
    MENU_INPUT_DOWN,
    MENU_INPUT_START,
    MENU_INPUT_SELECT,
    ENABLE_ACTIONS,
    APPLY_SUPPORT,
    ACTION_PRE_COMMAND,
    ACTION_POST_COMMAND,
    ON_LOAD_ANIMATION_EFFECT,
    ON_DISPATCH_ANIMAMTION_EFFECT,
    ON_RUN_ANIMATION_SCRIPT,
    SETUP_MODEL_ANIMATION,
    POST_MODEL_ANIMATION,

    //DAMAGE CALC EVENTS, ADDITIONAL EFFECTS IMPLEMENTED WITH THESE
    PRE_HIT_FORMULA,
    POST_HIT_FORMULA,
    PRE_DAMAGE_FORMULA,
    POST_DAMAGE_FORMULA,
    PRE_DAMAGE_DEALT,
    POST_DAMAGE_DEALT,
    POST_ACTION_DAMAGE_CALC,
    ON_FINALIZE_IMPACT_EVENTS,
    TRIGGER_DAMAGE_DISPLAY,
    UPDATE_ACTOR_TIMERS,
    ON_ACTOR_ATB_FILL,
    ON_ACTOR_ATB_FULL,
    ON_VTIMER_TICK,
    ON_CTIMER_TICK,
    INIT_BATTLE_ACTORS,
    SET_TARGET_REACTION,

    //Initialization Events
    INIT_PLAYER_BATTLE_ACTOR,
    INIT_PLAYER_PARTY_MEMBER,
    INIT_SUMMON_PARTY_MEMBER,
    INIT_STATS,
    INIT_ELEMENTS,
    INIT_STATUSES,
    INIT_CHARACTERS,
    INIT_ENEMY,
    INIT_ENEMY_ACTOR,
    INIT_WEAPON,
    INIT_ARMOR,
    INIT_ACCESSORY,
    INIT_COMMAND,
    INIT_ATTACK,


    RUN_ANIM_SCRIPT_OPCODE,
    SR_COMBO_OPCODE,
    RETURN_TO_IDLE,
    ON_TARGETS_SELECTED
} SrEventType;


typedef enum {
    INVALID_CONTEXT,
    EQUIP_MENU_CONTEXT,
    STATUS_MENU_CONTEXT,
    INVENTORY_MENU_CONTEXT,
    MATERIA_MENU_CONTEXT,
    BATTLE_MENU,
    /*Battle menu is much more modular, leading to separate contexts for each view -- at least for now*/
    BATTLE_SPELL_VIEW,
    BATTLE_SUMMON_VIEW,
    BATTLE_ESKILL_VIEW,
    BATTLE_ITEM_VIEW,
    BATTLE_CHANGE_VIEW,
    BATTLE_COMMAND_VIEW,
    ENABLE_ACTION_NO_MATERIA,
    PLAYING_ANIMATION,
    SR_COMBO_INPUT,
    MAT_HIGH_TYPE_0,
    MAT_HIGH_TYPE_1,
    MAT_HIGH_TYPE_2,
    MAT_HIGH_TYPE_3,
    MAT_HIGH_TYPE_4,
    MAT_HIGH_TYPE_5,
    MAT_HIGH_TYPE_6,
    MAT_HIGH_TYPE_7,
    MAT_HIGH_TYPE_8,
    MAT_HIGH_TYPE_9,
    MAT_HIGH_TYPE_10,
    MAT_HIGH_TYPE_11,
    MAT_HIGH_TYPE_12,
    MAT_HIGH_TYPE_13,
    MAT_HIGH_TYPE_14,
    MAT_HIGH_TYPE_15,
    MAT_SUB_TYPE_0,
    MAT_SUB_TYPE_1,
    MAT_SUB_TYPE_2,
    MAT_SUB_TYPE_3,
    MAT_SUB_TYPE_4,
    MAT_SUB_TYPE_5,
    MAT_SUB_TYPE_6,
    MAT_SUB_TYPE_7,
    MAT_SUB_TYPE_8,
    MAT_SUB_TYPE_9,
    MAT_SUB_TYPE_10,
    MAT_SUB_TYPE_11,
    MAT_SUB_TYPE_12,
    MAT_SUB_TYPE_13,
    MAT_SUB_TYPE_14,
    MAT_SUB_TYPE_15,
} SrEventContext;

typedef struct SrEventListener_ SrEventListener;
typedef void(*SrEventCallback)(const void*);

/* SisterRay API */
typedef SrEventListener(PFNSRADDLISTENERPROC)(SrEventType eventType, SrEventCallback callback);

/*Types of Events*/
/*For the public API events should be C-Standard compliant*/

typedef struct {
    Menu* menu;
    u32 menuState;
    i32 updateStateMask;
} MenuDrawEvent;

typedef struct {
    Menu* menu;
} MenuInitEvent;


typedef struct {
    Menu* menu;
    u32 menuState;
} MenuInputEvent;

/*Event on which we dispatch handlers for displaying the various types of materia*/
typedef struct {
    Widget* displayWidget;
    MateriaInventoryEntry materia;
    u8 materiaLevel;
} DrawMateriaDataEvent;


typedef enum {
    PHYSICAL,
    MAGICAL
} DamageType;

typedef struct ActorBattleState_ ActorBattleState;
typedef struct SrDamageContext_ SrDamageContext;
typedef struct DamageFormula_ DamageFormula;
typedef struct HitFormula_ HitFormula;
typedef struct PartyMemberState_ PartyMemberState;
typedef struct SrEnemyData_ SrEnemyData;
typedef struct SrPartyData_ SrPartyData;
typedef struct SrStat_ SrStat;
typedef struct SrExtendedImpactEvent_ SrExtendedImpactEvent;

typedef i32(*SRPFN_DERIVEDSTATFORMULA)(StatFormulaCtx*);

#pragma pack(push, 1)
typedef struct {
    u8 targetID;
    u8 attackerID;
    u8 damagedAnimScriptIdx;
    u8 impactEventQueueIdx;
    u16 actionFlags;
    u8 field_6;
    u8 field_7;
    u32 targetStatusMask;
} DamageEvent;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    u16 targetID;
    u16 dealtDamage;
    u16 actionFlags;
    u16 currentTargetHP;
    u16 currentTargetMP;
    u16 impactSoundID;
    u16 impactEffectID;
} ImpactEvent;
#pragma pack(pop)

typedef struct {
    DamageEvent* damageEvent;
    ImpactEvent* impactEvent;
    SrExtendedImpactEvent* extendedImpactEvent;
    ActorBattleState* targetState;
} TriggerDamageDisplayEvent;

#pragma pack(push, 1)
typedef struct {
    u16 dealtDamage;
    u16 actionFlags;
    u16 impactSoundID;
    u16 impactEffectID;
    u16 impactEventQueueIdx;
    u16 damageEventQueueIdx;
} DamageDisplayEvent;
#pragma pack(pop)

typedef struct {
    DamageCalcStruct* damageContext;
    SrDamageContext* srDamageContext;
    AIBattleContext* aiContext;
} CommandSetupEvent;

typedef struct {
    DamageCalcStruct* damageContext;
    SrDamageContext* srDamageContext;
    AIBattleContext* aiContext;
    DamageEvent* gameDamageEvent;
} DamageCalculationEvent;

typedef struct {
    Menu*  menuObect;
    EnabledCommand* command;
} SelectCommandEvent;

typedef struct {
    DamageCalcStruct* damageContext;
    SrDamageContext* srDamageContext;
    BattleQueueEntry* poppedAction;
    u8 issuingActorID;
    AIBattleContext* battleAIContext;
} ActionContextEvent;

typedef struct {
    u8 actorIdx;
    BattleModelState* ownerModelState;
    BattleModelStateSmall* ownerModelState74;
} ModelAnimationEvent;

typedef struct {
    u8 enemyIdx;
    u8 characterIdx;
    ActorBattleState* ownerState;
    bool isEnemy;
} InitBattleActorEvent;


typedef struct {
    u8 summonIdx;
    PartySummonCtx summonCtx;
    PartyMemberState* summonState;
} InitSummonEvent;

typedef struct {
    u8 characterIdx;
    PartyMemberState* partyState;
} InitPartyMemberEvent;


typedef struct {
    ActorBattleState* srActor;
} UpdateActorTimersEvent;

typedef struct {
    bool fromScene;
    u16 sceneIdx;
    u16 formationIdx;
    SrEnemyData* enemyState;
} InitEnemyEvent;

typedef struct {
    SrArmor* armor;
} InitArmorEvent;

typedef struct {
    SrStat* stat;
} InitStatEvent;

typedef struct {
    SrCharacter* character;
} InitCharacterEvent;

typedef struct {
    SrWeapon* weapon;
} InitWeaponEvent;

typedef struct {
    SrCommand* command;
} InitCommandEvent;

typedef struct {
    SrAttack* attack;
} InitAttackEvent;

typedef struct {
    u8 actorID;
    u8 animationType;
    u8 animationEffectID;
    u8 commandIdx;
    u16 actionIdx;
    u16 targetMask;
} AnimEffectEvent;

typedef struct {
    DamageEvent* damageEvent;
    ImpactEvent* impactEvent;
    SrExtendedImpactEvent* srExtendedEvent;
    DamageCalculationEvent* damageCtx;
} SrActionImpactSetupEvent;

typedef struct {
    const u8 characterIdx;
    const MateriaInventoryEntry materia;
    const MateriaData materiaData;
    const u8 materiaLevel;
} EnableAbilitiesEvent;

typedef struct {
    const u8 characterIdx;
} EnableDefaultAbilitiesEvent;

typedef struct {
    const u8 characterIdx;
    const MateriaInventoryEntry supportMateria;
    const u8 supportMateriaLevel;
    const MateriaData SupportMateriaData;
    const MateriaInventoryEntry pairedMateria;
    const u8 pairedMateriaLevel;
    const MateriaData pairedData;
    SrGameGearType gearType;
} ApplySupportEvent;

typedef void(*SRPFNCMDSELECTCALLBACK)(SelectCommandEvent*);
typedef void(*SRPFNCOMMANDSETUP)(CommandSetupEvent&);

#pragma pack(push, 1)
typedef struct {
    u8 attackerID;
    u8 activeAllies;
    u8 spellEffectID;
    u8 commandIndex;
    u8 actionFlags;
    u8 animationScriptID;
    u16 actionIndex;
    u16 cameraData;
    u16 damageEventQueueIdx;
} AnimationEvent;
#pragma pack(pop)

#endif // !SR_EVENTS_H
