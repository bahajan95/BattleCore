/* ScriptData
SDName: Argent Challenge Encounter.
SD%Complete: 50 %
SDComment: 
SDCategory: Trial of the Champion
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "trial_of_the_champion.h"
#include "ScriptedEscortAI.h"

enum Spells
{
    // Eadric the Pure
    SPELL_EADRIC_ACHIEVEMENT    = 68197,
    SPELL_HAMMER_JUSTICE        = 66863,
    SPELL_HAMMER_RIGHTEOUS      = 66867,
    SPELL_RADIANCE              = 66935,
    SPELL_VENGEANCE             = 66865,

    // Paletress
    SPELL_SMITE                 = 66536,
    SPELL_SMITE_H               = 67674,
    SPELL_HOLY_FIRE             = 66538,
    SPELL_HOLY_FIRE_H           = 67676,
    SPELL_RENEW                 = 66537,
    SPELL_RENEW_H               = 67675,
    SPELL_HOLY_NOVA             = 66546,
    SPELL_SHIELD                = 66515,
    SPELL_CONFESS               = 66680,
    SPELL_SUMMON_MEMORY         = 66545,

    // Memory of X (Summon)
    SPELL_MEMORY_ALGALON        = 66715,
    SPELL_MEMORY_ARCHIMONDE     = 66704,
    SPELL_MEMORY_CHROMAGGUS     = 66697,
    SPELL_MEMORY_CYANIGOSA      = 66709,
    SPELL_MEMORY_DELRISSA       = 66706,
    SPELL_MEMORY_ECK            = 66710,
    SPELL_MEMORY_ENTROPIUS      = 66707,
    SPELL_MEMORY_GRUUL          = 66702,
    SPELL_MEMORY_HAKKAR         = 66698,
    SPELL_MEMORY_HEIGAN         = 66712,
    SPELL_MEMORY_HEROD          = 66694,
    SPELL_MEMORY_HOGGER         = 66543,
    SPELL_MEMORY_IGNIS          = 66713,
    SPELL_MEMORY_ILLIDAN        = 66705,
    SPELL_MEMORY_INGVAR         = 66708,
    SPELL_MEMORY_KALITHRESH     = 66700,
    SPELL_MEMORY_LUCIFRON       = 66695,
    SPELL_MEMORY_MALCHEZAAR     = 66701,
    SPELL_MEMORY_MUTANUS        = 66692,
    SPELL_MEMORY_ONYXIA         = 66711,
    SPELL_MEMORY_THUNDERAAN     = 66696,
    SPELL_MEMORY_VANCLEEF       = 66691,
    SPELL_MEMORY_VASHJ          = 66703,
    SPELL_MEMORY_VEKNILASH      = 66699,
    SPELL_MEMORY_VEZAX          = 66714,

    // Memory
    SPELL_OLD_WOUNDS            = 66620,
    SPELL_OLD_WOUNDS_H          = 67679,
    SPELL_SHADOWS_PAST          = 66619,
    SPELL_SHADOWS_PAST_H        = 67678,
    SPELL_WAKING_NIGHTMARE      = 66552,
    SPELL_WAKING_NIGHTMARE_H    = 67677,
	
	//Npc_argent_soldier
    SPELL_STRIKE                = 67237,
    SPELL_CLEAVE                = 15284,
    SPELL_PUMMEL                = 67235,
    SPELL_PAIN                  = 34942,
    SPELL_MIND                  = 67229,
    SPELL_SSMITE                = 67289,
    SPELL_LIGHT                 = 67290,
    SPELL_FLURRY                = 67233,
    SPELL_FINAL                 = 67255,
    SPELL_DIVINE                = 67251,
    SPELL_FONT                  = 67194,
	SPELL_FONT_HEAL             = 71864,
	SPELL_FONT_HEAL_H           = 71866
};

class OrientationCheck : public std::unary_function<Unit*, bool>
{
    public:
        explicit OrientationCheck(Unit* _caster) : caster(_caster) { }
        bool operator()(WorldObject* object)
        {
            return !object->isInFront(caster, 2.5f) || !object->IsWithinDist(caster, 40.0f);
        }

    private:
        Unit* caster;
};

class spell_eadric_radiance : public SpellScriptLoader
{
    public:
        spell_eadric_radiance() : SpellScriptLoader("spell_eadric_radiance") { }
        class spell_eadric_radiance_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_eadric_radiance_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                unitList.remove_if(OrientationCheck(GetCaster()));
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_eadric_radiance_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_eadric_radiance_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_eadric_radiance_SpellScript();
        }
};

enum EventsEadric
{
	EVENT_EADRIC_VENGANCE = 1,
	EVENT_EADRIC_RADIANCE,
	EVENT_EADRIC_HAMMERJUSTICE
};

class boss_eadric : public CreatureScript
{
public:
    boss_eadric() : CreatureScript("boss_eadric") { }

    struct boss_eadricAI : public ScriptedAI
    {
        boss_eadricAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
			
			done = false;
			
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        InstanceScript* instance;
		EventMap events;
		
		bool done;

        void Reset() override
        {
        }

		void DespawnCreatures(uint32 entry)
		{
			std::list<Creature*> creatures;
			GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

			if (creatures.empty())
				return;

			for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
				(*iter)->DespawnOrUnsummon();
		}
		
		void EnterEvadeMode()
		{
			if (!done)
			{
				ScriptedAI::_EnterEvadeMode();
				events.Reset();
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				me->setFaction(35);
				me->GetMotionMaster()->MovePoint(2, 746.82f, 665.208f, 411.746f);
				DespawnCreatures(NPC_ARGENT_LIGHWIELDER);
				DespawnCreatures(NPC_ARGENT_MONK);
				DespawnCreatures(NPC_PRIESTESS);
			}
		}

        void DamageTaken(Unit* /*done_by*/, uint32 &damage) override
        {
            if (damage >= me->GetHealth())
            {
                damage = 0;
				done = true;
				me->GetMotionMaster()->MovePoint(0, 745.374f, 628.197f, 411.172f);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->setFaction(35);
				me->DeleteThreatList();
				me->CombatStop(true);
				events.Reset();
				TalkToMap(6);
            }
        }
		
		void EnterCombat(Unit* /*who*/) override
		{
			TalkToMap(1);
			DoZoneInCombat(me, 1000.f);
			events.ScheduleEvent(EVENT_EADRIC_VENGANCE, 10000);
			events.ScheduleEvent(EVENT_EADRIC_RADIANCE, 16000);
			events.ScheduleEvent(EVENT_EADRIC_HAMMERJUSTICE, 25000);
		}

        void MovementInform(uint32 moveType, uint32 pointId) override
        {
            if (moveType != POINT_MOTION_TYPE)
                return;
				
			switch (pointId)
			{
			case 0: // Done
				instance->SetData(BOSS_ARGENT_CHALLENGE, DONE);
				me->SetSpeed(MOVE_RUN, 0.5f);
				me->SetOrientation(ORIENTATION);
				me->SendMovementFlagUpdate();
				break;
			case 1: // Move To Gate Done
				me->DespawnOrUnsummon(2000);
				break;
			case 2: // EnterEvadeMode
				instance->SetData(BOSS_ARGENT_CHALLENGE, FAIL);
				instance->SetData(DATA_ARGENT_SOLDIER_DEFEATED, NOT_STARTED);
				me->DespawnOrUnsummon(2000);
				break;
			case 3:
				TalkToMap(0); // Intro
				if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetGuidData(DATA_MAIN_GATE)))
					instance->HandleGameObject(go->GetGUID(), false);
				me->SetSpeed(MOVE_RUN, 1.5f);
				break;
			}
        }
		
		void KilledUnit(Unit* victim)
		{
            TalkToMap(5);
		}

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_EADRIC_HAMMERJUSTICE:
					me->InterruptNonMeleeSpells(true);
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 250, true))
					{
						if (target && target->IsAlive())
						{
							DoCast(target, SPELL_HAMMER_JUSTICE);
							DoCast(target, SPELL_HAMMER_RIGHTEOUS);
							TalkToMap(3, target);
							TalkToMap(4);
						}
					}
					events.ScheduleEvent(EVENT_EADRIC_HAMMERJUSTICE, 25000);
					break;
				case EVENT_EADRIC_VENGANCE:
					DoCast(me, SPELL_VENGEANCE);
					events.ScheduleEvent(EVENT_EADRIC_VENGANCE, 10000);
					break;
				case EVENT_EADRIC_RADIANCE:
					DoCastAOE(SPELL_RADIANCE);
					TalkToMap(2);
					events.ScheduleEvent(EVENT_EADRIC_RADIANCE, 16000);
					break;
				}
			}

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<boss_eadricAI>(creature);
    }
};

enum EventsPaletress
{
	EVENT_PALETRESS_HOLY_FIRE = 1,
	EVENT_PALETRESS_HOLY_SMITE,
	EVENT_RENEW
};

class boss_paletress : public CreatureScript
{
public:
    boss_paletress() : CreatureScript("boss_paletress") { }

    struct boss_paletressAI : public ScriptedAI
    {
        boss_paletressAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();

			done = false;
			health = false;
			uiSayTimer = 0;

            creature->SetReactState(REACT_PASSIVE);
			creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        InstanceScript* instance;
		EventMap events;
        ObjectGuid MemoryGUID;

        bool done;
		bool health;
		
		uint32 uiSayTimer;

        void Reset() override
        {
        }

		void DespawnCreatures(uint32 entry)
		{
			std::list<Creature*> creatures;
			GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

			if (creatures.empty())
				return;

			for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
				(*iter)->DespawnOrUnsummon();
		}

		void EnterEvadeMode()
		{
			if (!done)
			{
				ScriptedAI::_EnterEvadeMode();
				events.Reset();
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				me->setFaction(35);
				me->GetMotionMaster()->MovePoint(2, 746.82f, 665.208f, 411.746f);

				if (Creature* pMemory = ObjectAccessor::GetCreature(*me, MemoryGUID))
					pMemory->DespawnOrUnsummon();

				DespawnCreatures(NPC_ARGENT_LIGHWIELDER);
				DespawnCreatures(NPC_ARGENT_MONK);
				DespawnCreatures(NPC_PRIESTESS);
			}
		}

		void EnterCombat(Unit* /*who*/) override
		{
			TalkToMap(2);
			DoZoneInCombat(me, 1000.f);
			events.ScheduleEvent(EVENT_PALETRESS_HOLY_FIRE, urand(9000, 12000));
			events.ScheduleEvent(EVENT_PALETRESS_HOLY_SMITE, urand(5000, 7000));
		}

        void SetData(uint32 uiId, uint32 /*uiValue*/) override
        {
			if (uiId == 1)
			{
				me->RemoveAura(SPELL_SHIELD);
				TalkToMap(4);
				me->ClearUnitState(UNIT_STATE_ROOT);
			}
        }
		
		void KilledUnit(Unit* victim)
		{
            TalkToMap(5);
		}

        void DamageTaken(Unit* /*done_by*/, uint32 &damage) override
        {
            if (damage >= me->GetHealth())
            {
				if (!health)
					damage = 0;
				else
				{
					damage = 0;

					if (Creature* pMemory = ObjectAccessor::GetCreature(*me, MemoryGUID))
						pMemory->DespawnOrUnsummon();

					done = true;
					me->GetMotionMaster()->MovePoint(0, 745.374f, 628.197f, 411.172f);
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					me->setFaction(35);
					me->DeleteThreatList();
					me->CombatStop(true);
					events.Reset();
					TalkToMap(6);
				}
            }
        }

		void MovementInform(uint32 moveType, uint32 pointId) override
        {
			if (moveType != POINT_MOTION_TYPE)
				return;

			switch (pointId)
			{
			case 0: // Done
				instance->SetData(BOSS_ARGENT_CHALLENGE, DONE);
				me->SetSpeed(MOVE_RUN, 0.5f);
				me->SetOrientation(ORIENTATION);
				me->SendMovementFlagUpdate();
				break;
			case 1: // Move To Gate Done
				me->DespawnOrUnsummon(2000);
				break;
			case 2: // EnterEvadeMode
				instance->SetData(BOSS_ARGENT_CHALLENGE, FAIL);
				instance->SetData(DATA_ARGENT_SOLDIER_DEFEATED, NOT_STARTED);
				me->DespawnOrUnsummon(2000);
				break;
			case 3:
				TalkToMap(0); // Intro
				if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetGuidData(DATA_MAIN_GATE)))
					instance->HandleGameObject(go->GetGUID(), false);
				me->SetSpeed(MOVE_RUN, 1.5f);
				uiSayTimer = 7000;
				break;
			}
        }

        void UpdateAI(uint32 diff) override
        {
			if (uiSayTimer != 0)
			{
				if (uiSayTimer <= diff)
				{
					TalkToMap(1);
					uiSayTimer = 0;
				}
				else 
					uiSayTimer -= diff;
			}
				
            if (!UpdateVictim())
                return;

			if (!health && !HealthAbovePct(25))
			{
				TalkToMap(3);
				me->InterruptNonMeleeSpells(true);
				DoCastAOE(SPELL_HOLY_NOVA, false);
				DoCast(me, SPELL_SHIELD);
				DoCastAOE(SPELL_SUMMON_MEMORY, false);
				DoCastAOE(SPELL_CONFESS, false);
				events.ScheduleEvent(EVENT_RENEW, urand(2000, 5000));
				me->AddUnitState(UNIT_STATE_ROOT);
				health = true;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_PALETRESS_HOLY_FIRE:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 250, true))
					{
						if (target && target->IsAlive())
							DoCast(target, SPELL_HOLY_FIRE);
					}
					if (me->HasAura(SPELL_SHIELD))
						events.ScheduleEvent(EVENT_PALETRESS_HOLY_FIRE, 13000);
					else
						events.ScheduleEvent(EVENT_PALETRESS_HOLY_FIRE, urand(9000, 12000));
					break;
				case EVENT_PALETRESS_HOLY_SMITE:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 250, true))
					{
						if (target && target->IsAlive())
							DoCast(target, SPELL_SMITE);
					}
					if (me->HasAura(SPELL_SHIELD))
						events.ScheduleEvent(EVENT_PALETRESS_HOLY_SMITE, 9000);
					else
						events.ScheduleEvent(EVENT_PALETRESS_HOLY_SMITE, urand(5000, 7000));
					break;
				case EVENT_RENEW:
					if (me->HasAura(SPELL_SHIELD))
					{
						me->InterruptNonMeleeSpells(true);
						uint8 uiTarget = urand(0, 1);
						switch (uiTarget)
						{
						case 0:
							DoCast(me, SPELL_RENEW);
							break;
						case 1:
							if (Creature* pMemory = ObjectAccessor::GetCreature(*me, MemoryGUID))
								if (pMemory->IsAlive())
									DoCast(pMemory, SPELL_RENEW);
							break;
						}
						events.ScheduleEvent(EVENT_RENEW, urand(15000, 17000));
					}
					else
						events.CancelEvent(EVENT_RENEW);
					break;
				default:
					break;
				}
			}

			if (!me->HasUnitState(UNIT_STATE_ROOT))
				DoMeleeAttackIfReady();
        }

        void JustSummoned(Creature* summon) override
        {
            MemoryGUID = summon->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<boss_paletressAI>(creature);
    }
};

class npc_memory : public CreatureScript
{
public:
    npc_memory() : CreatureScript("npc_memory") { }

    struct npc_memoryAI : public ScriptedAI
    {
        npc_memoryAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            uiOldWoundsTimer = 12000;
            uiShadowPastTimer = 5000;
            uiWakingNightmare = 7000;
        }

        uint32 uiOldWoundsTimer;
        uint32 uiShadowPastTimer;
        uint32 uiWakingNightmare;

        void Reset() override
        {
            Initialize();
        }

		void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

			if (uiOldWoundsTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                {
                    if (target && target->IsAlive())
                        DoCast(target, SPELL_OLD_WOUNDS);
                }
                uiOldWoundsTimer = 12000;
			}
			else 
				uiOldWoundsTimer -= diff;

			if (uiWakingNightmare <= diff)
            {
                DoCast(me, SPELL_WAKING_NIGHTMARE);
                uiWakingNightmare = 7000;
			}
			else
				uiWakingNightmare -= diff;

			if (uiShadowPastTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1))
                {
                    if (target && target->IsAlive())
                        DoCast(target, SPELL_SHADOWS_PAST);
                }
                uiShadowPastTimer = 5000;
			}
			else
				uiShadowPastTimer -= diff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (TempSummon* summ = me->ToTempSummon())
                if (Unit* summoner = summ->GetSummoner())
                    if (summoner->IsAlive())
                        summoner->GetAI()->SetData(1, 0);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_memoryAI(creature);
    }
};

class npc_argent_soldier : public CreatureScript
{
public:
    npc_argent_soldier() : CreatureScript("npc_argent_soldier") { }

    // THIS AI NEEDS MORE IMPROVEMENTS
    struct npc_argent_soldierAI : public npc_escortAI
    {
        npc_argent_soldierAI(Creature* creature) : npc_escortAI(creature)
        {
            instance = creature->GetInstanceScript();
            me->SetReactState(REACT_DEFENSIVE);

			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
			
            SetDespawnAtEnd(false);
            uiWaypoint = 0;
        }

        InstanceScript* instance;

		uint8 uiWaypoint;

        uint32 uiStrikeTimer;
    	uint32 uiCleaveTimer;
        uint32 uiPummelTimer;
    	uint32 uiPainTimer;
        uint32 uiMindTimer;
    	uint32 uiSsmiteTimer;
        uint32 uiFontTimer;
        uint32 uiLightTimer;
    	uint32 uiFlurryTimer;
        uint32 uiFinalTimer;
        uint32 uiDivineTimer;
    	uint32 uiResetTimer;
    	
        void Reset()
        {
          	uiStrikeTimer = 4000;	
          	uiCleaveTimer = 5000;
            uiPummelTimer = 8000;
          	uiPainTimer = 6000;
            uiMindTimer = 7000;
          	uiSsmiteTimer = 9000;
    	
    		uiResetTimer = 3000;
            uiLightTimer = 2000;
    		uiFontTimer = 30000;
       	    uiFlurryTimer = 14000;
            uiFinalTimer = 21000;
            uiDivineTimer = 20000;	
        }
    	
        void WaypointReached(uint32 uiPoint)
        {
            if (uiPoint == 0)
            {
                switch(uiWaypoint)
                {
                    case 1:
						me->SetFacingTo(4.6f);
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
    			        me->SetReactState(REACT_AGGRESSIVE);
                        break;
                }
    		}	
    		if (uiPoint == 1)
            {
                switch(uiWaypoint)
                {
                    case 0:
						me->SetFacingTo(5.81f);
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
    			        me->SetReactState(REACT_AGGRESSIVE);
                        break;
                    case 2:
						me->SetFacingTo(3.39f);
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
    			        me->SetReactState(REACT_AGGRESSIVE);
                        break;
                }
            }
			me->SendMeleeAttackStart(me);
        }

        void SetData(uint32 uiType, uint32 uiData)
        {
            switch(me->GetEntry())
            {
                case NPC_ARGENT_LIGHWIELDER:
                    switch(uiType)
                    {
                        case 0:
    					    AddWaypoint(0,737.14f,655.42f,412.88f);
                            AddWaypoint(1,712.14f,628.42f,411.88f);
                            break;
                        case 1:
                            AddWaypoint(0,742.44f,650.29f,411.79f);
                            break;
                        case 2:
    					    AddWaypoint(0,756.14f,655.42f,411.88f);
                            AddWaypoint(1,781.626f, 629.383f, 411.892f);
                            break;
                    }
                    break;
                case NPC_ARGENT_MONK:
                    switch(uiType)
                    {
                        case 0:
    					    AddWaypoint(0,737.14f,655.42f,412.88f);
                            AddWaypoint(1,713.12f,632.97f,411.90f);
                            break;
                        case 1:
                            AddWaypoint(0,746.73f,650.24f,411.56f);
                            break;
                        case 2:
    					    AddWaypoint(0,756.14f,655.42f,411.88f);
                            AddWaypoint(1,781.351f, 633.146f, 411.907f);
                            break;
                    }
                    break;
                case NPC_PRIESTESS:
                    switch(uiType)
                    {
                        case 0:
    					    AddWaypoint(0,737.14f,655.42f,412.88f);
                            AddWaypoint(1,715.06f,637.07f,411.91f);
                            break;
                        case 1:
                            AddWaypoint(0,750.72f,650.20f,411.77f);
                            break;
                        case 2:
    					    AddWaypoint(0,756.14f,655.42f,411.88f);
                            AddWaypoint(1,780.439f, 636.681f, 411.918f);
                            break;
                    }
                    break;
            }

			me->SetSpeed(MOVE_RUN, 0.4f);
            Start(false,true);
            uiWaypoint = uiType;
        }

		void EnterEvadeMode()
		{
			uint32 count = 0;
			Map::PlayerList const& players = me->GetMap()->GetPlayers();
			if (me->GetMap()->IsDungeon() && !players.isEmpty())
			{
				for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
				{
					Player* player = itr->GetSource();
					if (player->IsGameMaster())
						continue;

					if (!player->IsAlive())
						continue;

					++count;
				}
			}
			if (count == 0)
			{
				if (Creature* boss = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_ARGENT_CHAMPION)))
				if (!boss->IsInEvadeMode())
					boss->AI()->EnterEvadeMode();
			}
			else
				DoZoneInCombat(me, 1000.f);
		}

		void EnterCombat(Unit* /*who*/) override
		{
			me->SetSpeed(MOVE_RUN, 1.3f);
			DoZoneInCombat(me, 1000.f);
		}

        void UpdateAI(uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);

            if (!UpdateVictim())
                return;
    	
			switch(me->GetEntry())
			{
				case NPC_ARGENT_LIGHWIELDER:
				{
					if (uiCleaveTimer <= uiDiff)
					{
						if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
							DoCast(pTarget,SPELL_STRIKE);				
							uiCleaveTimer = 20000;
					} else uiCleaveTimer -= uiDiff;	
					
					if (uiStrikeTimer <= uiDiff)
					{
						if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
							DoCast(pTarget,SPELL_CLEAVE);				
							uiStrikeTimer = 25000;
					} else uiStrikeTimer -= uiDiff;	
					
					if (uiLightTimer <= uiDiff)
					{
							DoCast(me,SPELL_LIGHT);
							uiLightTimer = urand (15000, 17000);
					} else uiLightTimer -= uiDiff;
					break;
				}
				case NPC_ARGENT_MONK:
				{		
					if (uiDivineTimer <= uiDiff)
					{
							DoCast(me,SPELL_DIVINE);
							uiDivineTimer = 85000;
					} else uiDivineTimer -= uiDiff;
					
					if (uiFinalTimer <= uiDiff)
					{
							DoCast(me,SPELL_FINAL);
							uiFinalTimer = 70000;
					} else uiFinalTimer -= uiDiff;
					
					if (uiPummelTimer <= uiDiff)
					{
						if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
							DoCast(pTarget,SPELL_PUMMEL);				
							uiPummelTimer = 35000;
					} else uiPummelTimer -= uiDiff;	
					
					if (uiFlurryTimer <= uiDiff)
					{
							DoCast(me,SPELL_FLURRY);
							uiFlurryTimer = 22000;
					} else uiFlurryTimer -= uiDiff;	
					break;
				}
				case NPC_PRIESTESS:
				{
					if (uiFontTimer <= uiDiff)
					{
							DoCast(me,SPELL_FONT);
							uiFontTimer = urand (15000, 17000);
					} else uiFontTimer -= uiDiff;
					
					if (uiPainTimer <= uiDiff)
					{
						if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
							DoCast(pTarget,SPELL_PAIN);				
							uiPainTimer = 30000;
					} else uiPainTimer -= uiDiff;	
				
					if (uiMindTimer <= uiDiff)
					{
						if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
							DoCast(pTarget,SPELL_MIND);				
							uiMindTimer = 90000;
					} else uiMindTimer -= uiDiff;
					
					if (uiSsmiteTimer <= uiDiff)
					{
						if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
							DoCast(pTarget,SPELL_SSMITE);				
							uiSsmiteTimer = 25000;
					} 
					else
						uiSsmiteTimer -= uiDiff;					
					break;
				}		
			}			
    			
            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* killer)
        {
			instance->SetData(DATA_ARGENT_SOLDIER_DEFEATED, instance->GetData(DATA_ARGENT_SOLDIER_DEFEATED) + 1);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_argent_soldierAI>(creature);
    }
};

class npc_fountain_of_light_toc5 : public CreatureScript
{
public:
	npc_fountain_of_light_toc5() : CreatureScript("npc_fountain_of_light_toc5") { }

	struct npc_fountain_of_light_toc5AI : public ScriptedAI
	{
		npc_fountain_of_light_toc5AI(Creature* creature) : ScriptedAI(creature)
		{
			me->SetReactState(REACT_DEFENSIVE);
			me->AddUnitState(UNIT_STATE_ROOT);
		}

		uint32 uiHealTimer;

		void Reset()
		{
			uiHealTimer = 6000;
		}

		void UpdateAI(uint32 uiDiff)
		{
			if (uiHealTimer <= uiDiff)
			{
				DoCast(me, me->GetMap()->IsHeroic() ? SPELL_FONT_HEAL_H : SPELL_FONT_HEAL);
				uiHealTimer = 6000;
			}
			else
				uiHealTimer -= uiDiff;
		}

		void JustDied(Unit* killer)
		{
			me->DespawnOrUnsummon(4000);
		}
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return GetInstanceAI<npc_fountain_of_light_toc5AI>(creature);
	}
};

uint32 const memorySpellId[25] =
{
    SPELL_MEMORY_ALGALON,
    SPELL_MEMORY_ARCHIMONDE,
    SPELL_MEMORY_CHROMAGGUS,
    SPELL_MEMORY_CYANIGOSA,
    SPELL_MEMORY_DELRISSA,
    SPELL_MEMORY_ECK,
    SPELL_MEMORY_ENTROPIUS,
    SPELL_MEMORY_GRUUL,
    SPELL_MEMORY_HAKKAR,
    SPELL_MEMORY_HEIGAN,
    SPELL_MEMORY_HEROD,
    SPELL_MEMORY_HOGGER,
    SPELL_MEMORY_IGNIS,
    SPELL_MEMORY_ILLIDAN,
    SPELL_MEMORY_INGVAR,
    SPELL_MEMORY_KALITHRESH,
    SPELL_MEMORY_LUCIFRON,
    SPELL_MEMORY_MALCHEZAAR,
    SPELL_MEMORY_MUTANUS,
    SPELL_MEMORY_ONYXIA,
    SPELL_MEMORY_THUNDERAAN,
    SPELL_MEMORY_VANCLEEF,
    SPELL_MEMORY_VASHJ,
    SPELL_MEMORY_VEKNILASH,
    SPELL_MEMORY_VEZAX
};

// 66545 - Summon Memory
class spell_paletress_summon_memory : public SpellScriptLoader
{
    public:
        spell_paletress_summon_memory() : SpellScriptLoader("spell_paletress_summon_memory") { }

        class spell_paletress_summon_memory_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_paletress_summon_memory_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                for (uint8 i = 0; i < 25; ++i)
                    if (!sSpellMgr->GetSpellInfo(memorySpellId[i]))
                        return false;
                return true;
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                WorldObject* target = Trinity::Containers::SelectRandomContainerElement(targets);
                targets.clear();
                targets.push_back(target);
            }

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                GetHitUnit()->CastSpell(GetHitUnit(), memorySpellId[urand(0, 24)], true, NULL, NULL, GetCaster()->GetGUID());
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_paletress_summon_memory_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_paletress_summon_memory_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_paletress_summon_memory_SpellScript();
        }
};

void AddSC_boss_argent_challenge()
{
    new boss_eadric();
    new spell_eadric_radiance();
    new boss_paletress();
    new npc_memory();
    new npc_argent_soldier();
    new spell_paletress_summon_memory();
	new npc_fountain_of_light_toc5();
}
