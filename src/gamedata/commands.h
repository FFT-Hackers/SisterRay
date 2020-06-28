#ifndef COMMANDS_H
#define COMMANDS_H

#include <SisterRay/types.h>
#include <SisterRay/SisterRay.h>
#include "../sr_named_registry.h"
#include "game_data_interface.h"
#include "command_callbacks.h"
#include "cmd_select_callbacks.h"
#include "gdata_utils.h"
#include "attacks.h"
#include "formulas.h"

#define KERNEL_COMMAND_COUNT 32

struct SrCommand_ {
    EncodedString name;
    EncodedString description;
    std::vector<std::string> attackElements;
    std::vector<StatusInfliction> statusAttack;
    std::unordered_map<std::string, SrBoostedStat> stats;
    std::vector<SRPFNCOMMANDSETUP> setupCallbacks;
    std::vector<SRPFNCMDSELECTCALLBACK> selectCallbacks;
    DamageType damageType;
    u16 damageFormula;
    std::unordered_set<DamageModifiers> dmgFormulaModifiers;
    u16 hitFormula;
    std::unordered_set<HitModifiers> hitFormulaModifiers;

    CommandData gameCommand;
    AuxCommandData auxData;
    u16 actionCount;
    bool hasSubCommands;
    bool isTechnique;
    std::vector<u16> subCommands; //vector of indexes into the commands table. Can define recursive command structures, i.e techniques command
    std::vector<u16> commandActions; //vector of indexes into the attacks table. Game engine fetches attack data through this
    std::vector<u16> swapActions;
};

class SrCommandRegistry : public SrNamedResourceRegistry<SrCommand, std::string> {
public:
    SrCommandRegistry(SrKernelStream* stream);
    SrCommandRegistry() : SrNamedResourceRegistry<SrCommand, std::string>() {}
};

void runSetupCallbacks(ActionContextEvent& actionEvent);
void runActionSetupCallbacks(ActionContextEvent& actionEvent);
void runSelectCallbacks(EnabledCommand& command, Menu* menu);
void initCommands(SrKernelStream* stream);
u16 getDefaultCmdAnimScript(u16 idx);
u8 getDefaultCmdDamage(u16 commandIdx);
u16 getDefaultCmdFlags(u16 commandIdx);
u16 getDefaultHasActions(u16 commandIdx);
void registerDefaultCallbacks(u16 commandIdx, SrCommand& auxCommand);
void registerSelectCallbacks(u16 commandIdx, SrCommand& auxCommand);

const SrCommand& getCommand(u8 commandIdx);
const SrAttack& getCommandAction(u8 commandIdx, u16 actionIdx);
void addCommandAction(const std::string commandKey, const std::string actionKey);
void setCommandAction(const std::string commandKey, const std::string actionKey, u32 actionIndex);
void addCommandSwapAction(const std::string commandKey, const std::string actionKey);

#endif
