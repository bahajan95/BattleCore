#include "ScriptPCH.h"
#include "Player.h"
#include "ScriptedCreature.h"

enum datastorespell
{
    SPELL_SUM_INF_ASSALIANT = 49900, // Summon Infinite Assailant
    SPELL_SUM_INF_DESTROYER = 49901, // Summon Infinite Destroyer
    SPELL_SUM_INF_CHRONO_MAGUS = 49902, //Summon Infinite Chrono - Magus
    SPELL_SUM_TIMERENDER = 49905, //Summon Infinite Timerender
    SPELL_SUM_FUTURE_YOU = 49942, //Mystery of the Infinite : Summon Future You
};

enum datatore
{
    wave1,
    wave2,
    wave3,
    wave4,
};

class hourglass_of_eternity : public CreatureScript
{
public:
    hourglass_of_eternity() : CreatureScript("hourglass_of_eternity") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new hourglass_of_eternityAI(creature);
    }

    struct hourglass_of_eternityAI : public ScriptedAI
    {
        hourglass_of_eternityAI(Creature* creature) : ScriptedAI(creature) {}

        void Scedule()
        {
            events.ScheduleEvent(wave1, 7000, 0, 0);
            events.ScheduleEvent(wave2, 55000, 0, 0);
            events.ScheduleEvent(wave3, 107000, 0, 0);
            events.ScheduleEvent(wave4, 162000, 0, 0);
        }
        
        void Reset() override
        {
            trigerred = false;
        }

        void UpdateAI(uint32 uiDiff) override
        {
            if (!trigerred)
            {
                Scedule();
                trigerred = true;
            }

            events.Update(uiDiff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case wave1:
                    me->CastSpell(me, SPELL_SUM_INF_ASSALIANT, false);
                    me->CastSpell(me, SPELL_SUM_INF_DESTROYER, false);
                    break;
                case wave2:
                    me->CastSpell(me, SPELL_SUM_INF_DESTROYER, false);
                    me->CastSpell(me, SPELL_SUM_INF_CHRONO_MAGUS, false);
                    break;
                case wave3:
                    me->CastSpell(me, SPELL_SUM_INF_ASSALIANT, false);
                    me->CastSpell(me, SPELL_SUM_INF_DESTROYER, false);
                    me->CastSpell(me, SPELL_SUM_INF_CHRONO_MAGUS, false);
                    break;
                case wave4:
                    me->CastSpell(me, SPELL_SUM_TIMERENDER, false);
                    break;
                default:
                    break;
                }

            }
        }
    private:
        bool trigerred;
        EventMap events;

    };
};

void AddSC_hourglass_of_eternity()
{
    new hourglass_of_eternity();
}