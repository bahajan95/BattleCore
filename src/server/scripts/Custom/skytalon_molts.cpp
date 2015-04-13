#include "ScriptMgr.h"
#include "Creature.h"
#include "Player.h"

// Event 18223 Realization
enum creatures
{
    ALYSTROS_THE_VERDANT_KEEPER = 27249,
};

Position pos = { 2629.2f, 8.1333f, 26.347f, 0.401426f };

class skytalon_molts : public ItemScript
{
public:
    skytalon_molts() : ItemScript("skytalon_molts") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
    {
        if (Creature* creature = player->FindNearestCreature(ALYSTROS_THE_VERDANT_KEEPER, 100.0f, true))
        {
            if (Creature* newcreature = creature->SummonCreature(ALYSTROS_THE_VERDANT_KEEPER, pos, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
            {
                creature->DespawnOrUnsummon();
                newcreature->RemoveAllAuras();
                newcreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                newcreature->GetMotionMaster()->Initialize();
                newcreature->GetMotionMaster()->MovePoint(0, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ() + 5.0f);
            }
        }

        return false;
    }
};

void AddSC_skytalon_molts()
{
    new skytalon_molts();
}