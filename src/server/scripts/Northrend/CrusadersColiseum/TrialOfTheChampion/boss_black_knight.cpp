/*
 * Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Boss Black Knight
SD%Complete: 80%
SDComment: missing yells. not sure about timers.
SDCategory: Trial of the Champion
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"
#include "trial_of_the_champion.h"

enum Spells
{
    //phase 1
    SPELL_PLAGUE_STRIKE     = 67884,
    SPELL_PLAGUE_STRIKE_2   = 67724,
    SPELL_ICY_TOUCH_H       = 67881,
    SPELL_ICY_TOUCH         = 67718,
    SPELL_DEATH_RESPITE     = 67745,
	SPELL_DEATH_PUSH        = 66797,
    SPELL_DEATH_RESPITE_FOR_AN = 66798,
    SPELL_OBLITERATE_H      = 67883,
    SPELL_OBLITERATE        = 67725,
	SPELL_RAISE_DEAD_EXPLORE = 67754,
    //in this phase should rise herald (the spell is missing)

    //phase 2 - During this phase, the Black Knight will use the same abilities as in phase 1, except for Death's Respite
	SPELL_ARMY_DEAD         = 67761,
    SPELL_DESECRATION       = 67778,
    SPELL_DESECRATION_2     = 67778,
    SPELL_GHOUL_EXPLODE     = 67751,

    //phase 3
    SPELL_DEATH_BITE_H      = 67875,
    SPELL_DEATH_BITE        = 67808,
    SPELL_MARKED_DEATH      = 67882,
    SPELL_MARKED_DEATH_2    = 67823,

    SPELL_BLACK_KNIGHT_RES  = 67693,

	// Spell Raise Dead
    SPELL_LEAP              = 67749,
	SPELL_CLAW              = 67774,
	SPELL_EXPLORE           = 67729,
	
	RAISE_DEAD_ARELAS_BRIGHTSTAR = 67705,
	RAISE_DEAD_JAEREN_SUNSWORN   = 67715,

	SPELL_KILL_CREDIT       = 68663
};

enum Events
{
};

enum Models
{
    MODEL_SKELETON = 29846,
    MODEL_GHOST    = 21300
};

enum Phases
{
    PHASE_UNDEAD    = 1,
    PHASE_SKELETON  = 2,
    PHASE_GHOST     = 3
};

class boss_black_knight : public CreatureScript
{
public:
    boss_black_knight() : CreatureScript("boss_black_knight") { }

    struct boss_black_knightAI : public ScriptedAI
    {
        boss_black_knightAI(Creature* creature) : ScriptedAI(creature), summons(creature)
        {
            Initialize();
            instance = creature->GetInstanceScript();
			creature->SetSpeed(MOVE_RUN, 0.5f);
			creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
        }

        void Initialize()
        {
            bEventInProgress = false;
            bEvent = false;
            bSummonArmy = false;
            bDeathArmyDone = false;

            uiPhase = PHASE_UNDEAD;

            uiIcyTouchTimer = urand(5000, 9000);
            uiPlagueStrikeTimer = urand(10000, 13000);
            uiDeathRespiteTimer = urand(15000, 16000);
            uiObliterateTimer = urand(17000, 19000);
            uiDesecration = urand(15000, 16000);
            uiDeathArmyCheckTimer = 7000;
            uiResurrectTimer = 4000;
            uiGhoulExplodeTimer = 8000;
            uiDeathBiteTimer = urand(2000, 4000);
			uiMarkedDeathTimer = urand(5000, 7000);
			uiDeathRespite3Timer = 0;
        }

        InstanceScript* instance;

        SummonList summons;

        bool bEventInProgress;
        bool bEvent;
        bool bSummonArmy;
        bool bDeathArmyDone;

        uint8 uiPhase;

        uint32 uiPlagueStrikeTimer;
        uint32 uiIcyTouchTimer;
        uint32 uiDeathRespiteTimer;
        uint32 uiObliterateTimer;
        uint32 uiDesecration;
        uint32 uiResurrectTimer;
        uint32 uiDeathArmyCheckTimer;
        uint32 uiGhoulExplodeTimer;
        uint32 uiDeathBiteTimer;
        uint32 uiMarkedDeathTimer;
		uint32 uiDeathRespite3Timer;

        void Reset() override
        {
            summons.DespawnAll();
            me->SetDisplayId(me->GetNativeDisplayId());
			me->SetTarget(instance->GetGuidData(DATA_ANNOUNCER));
            me->ClearUnitState(UNIT_STATE_ROOT | UNIT_STATE_STUNNED);
			me->LoadEquipment(1);
            Initialize();
        }

		void EnterEvadeMode() override
		{
			ScriptedAI::EnterEvadeMode();
		}

		void SetData(uint32 type, uint32 data)
		{
			if (type == DATA_START)
			{
				switch (data)
				{
				case 0: // Intro
					TalkToMap(0);
					uiDeathRespite3Timer = 1000;
					break;
				case 1: // Aggro
					TalkToMap(3);
					me->SetHomePosition(me->GetPosition());
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetReactState(REACT_AGGRESSIVE);
					me->SetSpeed(MOVE_RUN, 1.14f);
					DoZoneInCombat(me, 1000.f);
					break;
				}
			}
		}

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
			summon->AI()->DoZoneInCombat();
        }

        void SummonedCreatureDespawn(Creature* summon) override
        {
            summons.Despawn(summon);
        }
		
		void EnterCombat(Unit* target) override
		{
			if (Creature* announcer = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_ANNOUNCER)))
			{
				switch (announcer->GetEntry())
				{
				case NPC_JAEREN:
					DoCastAOE(RAISE_DEAD_JAEREN_SUNSWORN, false);
					break;
				case NPC_ARELAS:
					DoCastAOE(RAISE_DEAD_ARELAS_BRIGHTSTAR, false);
					break;
				default:
					break;
				}
			}
			DoZoneInCombat(me, 1000.f);
		}
		
		void KilledUnit(Unit* victim)
		{
            TalkToMap(6);
		}

        void UpdateAI(uint32 uiDiff) override
        {
			if (uiDeathRespite3Timer != 0)
			{
				if (uiDeathRespite3Timer <= uiDiff)
				{
					uiDeathRespite3Timer = 0;
					DoCastAOE(SPELL_DEATH_RESPITE_FOR_AN, false);
				}
				else
					uiDeathRespite3Timer -= uiDiff;
			}

            //Return since we have no target
            if (!UpdateVictim())
                return;

            if (bEventInProgress)
            {
                if (uiResurrectTimer <= uiDiff)
                {
                    me->SetFullHealth();
                    DoCast(me, SPELL_BLACK_KNIGHT_RES, true);
                    uiPhase++;
					TalkToMap(uiPhase + 2);
                    uiResurrectTimer = 4000;
                    bEventInProgress = false;
                    me->ClearUnitState(UNIT_STATE_ROOT | UNIT_STATE_STUNNED);
                } 
				else
					uiResurrectTimer -= uiDiff;
            }

			if (bEventInProgress)
				return;
			
            switch (uiPhase)
            {
                case PHASE_UNDEAD:
                case PHASE_SKELETON:
                {
                    if (uiIcyTouchTimer <= uiDiff)
                    {
                        DoCastVictim(SPELL_ICY_TOUCH);
                        uiIcyTouchTimer = urand(5000, 7000);
                    } 
					else
						uiIcyTouchTimer -= uiDiff;
						
                    if (uiPlagueStrikeTimer <= uiDiff)
                    {
                        DoCastVictim(SPELL_ICY_TOUCH);
                        uiPlagueStrikeTimer = urand(12000, 15000);
                    }
					else
						uiPlagueStrikeTimer -= uiDiff;
						
                    if (uiObliterateTimer <= uiDiff)
                    {
                        DoCastVictim(SPELL_OBLITERATE);
                        uiObliterateTimer = urand(17000, 19000);
                    }
					else 
						uiObliterateTimer -= uiDiff;
						
                    switch (uiPhase)
                    {
                        case PHASE_UNDEAD:
                        {
                            if (uiDeathRespiteTimer <= uiDiff)
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                                {
                                    if (target && target->IsAlive())
                                        DoCast(target, SPELL_DEATH_RESPITE);
                                }
                                uiDeathRespiteTimer = urand(15000, 16000);
                            } 
							else
								uiDeathRespiteTimer -= uiDiff;
                            break;
                        }
                        case PHASE_SKELETON:
                        {
                            if (!bSummonArmy)
                            {
                                bSummonArmy = true;
                                me->AddUnitState(UNIT_STATE_ROOT | UNIT_STATE_STUNNED);
                                DoCast(me, SPELL_ARMY_DEAD);
                            }
                            if (!bDeathArmyDone)
                            {
                                if (uiDeathArmyCheckTimer <= uiDiff)
                                {
                                    me->ClearUnitState(UNIT_STATE_ROOT | UNIT_STATE_STUNNED);
                                    uiDeathArmyCheckTimer = 0;
                                    bDeathArmyDone = true;
                                } 
								else
									uiDeathArmyCheckTimer -= uiDiff;
                            }
                            if (uiDesecration <= uiDiff)
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                                {
                                    if (target && target->IsAlive())
                                        DoCast(target, SPELL_DESECRATION);
                                }
                                uiDesecration = urand(15000, 16000);
                            } 
							else
								uiDesecration -= uiDiff;
                            if (uiGhoulExplodeTimer <= uiDiff)
                            {
                                DoCast(me, SPELL_GHOUL_EXPLODE);
                                uiGhoulExplodeTimer = 8000;
                            } 
							else
								uiGhoulExplodeTimer -= uiDiff;
                            break;
                        }
                        break;
                    }
                    break;
                }
                case PHASE_GHOST:
                {
                    if (uiDeathBiteTimer <= uiDiff)
                    {
                        DoCastAOE(SPELL_DEATH_BITE);
                        uiDeathBiteTimer = urand(2000, 4000);
                    } 
					else 
						uiDeathBiteTimer -= uiDiff;
                    if (uiMarkedDeathTimer <= uiDiff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        {
                            if (target && target->IsAlive())
                                DoCast(target, SPELL_MARKED_DEATH);
                        }
                        uiMarkedDeathTimer = urand(5000, 7000);
                    } 
					else
						uiMarkedDeathTimer -= uiDiff;
                    break;
                }
            }
                
			if (!me->HasUnitState(UNIT_STATE_ROOT) && !me->HealthBelowPct(1))
				DoMeleeAttackIfReady();
        }

        void DamageTaken(Unit* /*pDoneBy*/, uint32& uiDamage) override
        {
            if (uiDamage > me->GetHealth() && uiPhase <= PHASE_SKELETON)
            {
                uiDamage = 0;
                me->SetHealth(0);
                me->AddUnitState(UNIT_STATE_ROOT | UNIT_STATE_STUNNED);
                switch (uiPhase)
                {
                    case PHASE_UNDEAD:
					{
						SummonList::const_iterator itr = summons.begin();
                        me->SetDisplayId(MODEL_SKELETON);
						for (SummonList::const_iterator itr = summons.begin(); itr != summons.end(); ++itr)
							if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
								summon->CastSpell(summon, SPELL_RAISE_DEAD_EXPLORE, true);
                        break;
					}
                    case PHASE_SKELETON:
                        me->SetDisplayId(MODEL_GHOST);
						me->LoadEquipment(2);
						summons.DespawnAll();
                        break;
                }
                bEventInProgress = true;
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
            DoCast(me, SPELL_KILL_CREDIT);
			
			TalkToMap(7);

            instance->SetData(BOSS_BLACK_KNIGHT, DONE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<boss_black_knightAI>(creature);
    }
};

class npc_risen_ghoul : public CreatureScript
{
public:
    npc_risen_ghoul() : CreatureScript("npc_risen_ghoul") { }

    struct npc_risen_ghoulAI : public ScriptedAI
    {
        npc_risen_ghoulAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            uiAttackTimer = 3000;
			uiLeapTimer = 3500;
        }

        uint32 uiAttackTimer;
		uint32 uiLeapTimer;

        void Reset() override
        {
            Initialize();
        }

        void UpdateAI(uint32 uiDiff) override
        {
            if (!UpdateVictim())
                return;

			if (uiAttackTimer <= uiDiff)
			{
				DoCastVictim(SPELL_CLAW);

				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
					me->SetTarget(target->GetGUID());
				uiAttackTimer = 3000;
			}
			else
				uiAttackTimer -= uiDiff;

			if (uiLeapTimer <= uiDiff)
            {
				if (Unit* target = me->GetVictim())
				    if (target->IsAlive() && me->IsInRange(target, 5.f, 30.f, false))
					{
					    DoCast(target, SPELL_LEAP);
						uiLeapTimer = 3500;
					}
					else 
						uiLeapTimer = 1000;
			}
			else
				uiLeapTimer -= uiDiff;

			DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_risen_ghoulAI(creature);
    }
};

class npc_black_knight_skeletal_gryphon : public CreatureScript
{
public:
    npc_black_knight_skeletal_gryphon() : CreatureScript("npc_black_knight_skeletal_gryphon") { }

    struct npc_black_knight_skeletal_gryphonAI : public npc_escortAI
    {
        npc_black_knight_skeletal_gryphonAI(Creature* creature) : npc_escortAI(creature)
        {
            Start(false, true);
			reached = false;
        }

		bool reached;

        void WaypointReached(uint32 pointId) override
		{
			if (pointId == 13)
				if (Vehicle* vehicle = me->GetVehicleKit())
					if (Creature* passenger = vehicle->GetPassenger(0)->ToCreature())
					{
						passenger->AI()->SetData(DATA_START, 0);
						reached = true;
					}
		}
		
        void UpdateAI(uint32 uiDiff) override
        {
            npc_escortAI::UpdateAI(uiDiff);

            UpdateVictim();
        }

	};

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_black_knight_skeletal_gryphonAI(creature);
    }
};

// 66798 - Death Respite
class spell_death_respite_toc5 : public SpellScriptLoader
{
public:
	spell_death_respite_toc5() : SpellScriptLoader("spell_death_respite_toc5") { }

	class spell_death_respite_toc5_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_death_respite_toc5_AuraScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			if (!sSpellMgr->GetSpellInfo(SPELL_DEATH_PUSH))
				return false;
			return true;
		}

		void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
		{
			InstanceScript* instance;
			Unit* target = GetTarget();
			Unit* caster = GetCaster();

			if (!caster && !target)
				return;
				
			instance = caster->GetInstanceScript();
			if (!instance)
				return;
				
			if (Creature* highLord = ObjectAccessor::GetCreature(*caster, instance->GetGuidData(DATA_HIGHLORD)))
				highLord->AI()->TalkToMap(56);

			caster->CastSpell(target, SPELL_DEATH_PUSH, true);
			target->RemoveAurasDueToSpell(GetId());
		}

		void Register() override
		{
			OnEffectPeriodic += AuraEffectPeriodicFn(spell_death_respite_toc5_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_death_respite_toc5_AuraScript();
	}
};

// 67754
class spell_raise_dead_explore : public SpellScriptLoader
{
public:
	spell_raise_dead_explore() : SpellScriptLoader("spell_raise_dead_explore") { }

	class spell_raise_dead_explore_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_raise_dead_explore_SpellScript);

		void HandleScript(SpellEffIndex /*effIndex*/)
		{
			if (Unit* caster = GetCaster())
				caster->CastSpell(caster, SPELL_EXPLORE, false);
		}

		void Register() override
		{
			OnEffectHit += SpellEffectFn(spell_raise_dead_explore_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_raise_dead_explore_SpellScript();
	}
};

void AddSC_boss_black_knight()
{
    new boss_black_knight();
    new npc_risen_ghoul();
    new npc_black_knight_skeletal_gryphon();
	new spell_death_respite_toc5();
	new spell_raise_dead_explore();
}
