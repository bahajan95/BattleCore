/* ScriptData
SDName: boss_grand_champions
SD%Complete: ~98 %
SDComment: Нужно добавить тексты зрителей после выхода босса.
SDCategory: Trial Of the Champion
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"
#include "trial_of_the_champion.h"
#include "Player.h"

enum Spells
{
    //Vehicle
    SPELL_CHARGE                    = 63010,
    SPELL_SHIELD_BREAKER            = 68504,
    SPELL_SHIELD                    = 62552,

    // Marshal Jacob Alerius && Mokra the Skullcrusher || Warrior
    SPELL_MORTAL_STRIKE             = 68783,
    SPELL_MORTAL_STRIKE_H           = 68784,
    SPELL_BLADESTORM                = 63784,
    SPELL_INTERCEPT                 = 67540,
    SPELL_ROLLING_THROW             = 47115, //not implemented in the AI yet...

    // Ambrose Boltspark && Eressea Dawnsinger || Mage
    SPELL_FIREBALL                  = 66042,
    SPELL_FIREBALL_H                = 68310,
    SPELL_BLAST_WAVE                = 66044,
    SPELL_BLAST_WAVE_H              = 68312,
    SPELL_HASTE                     = 66045,
    SPELL_POLYMORPH                 = 66043,
    SPELL_POLYMORPH_H               = 68311,

    // Colosos && Runok Wildmane || Shaman
    SPELL_CHAIN_LIGHTNING           = 67529,
    SPELL_CHAIN_LIGHTNING_H         = 68319,
    SPELL_EARTH_SHIELD              = 67530,
    SPELL_HEALING_WAVE              = 67528,
    SPELL_HEALING_WAVE_H            = 68318,
    SPELL_HEX_OF_MENDING            = 67534,

    // Jaelyne Evensong && Zul'tore || Hunter
    SPELL_DISENGAGE                 = 68340, //not implemented in the AI yet...
    SPELL_LIGHTNING_ARROWS          = 66083,
    SPELL_MULTI_SHOT                = 66081,
    SPELL_SHOOT                     = 65868,
    SPELL_SHOOT_H                   = 67988,

    // Lana Stouthammer Evensong && Deathstalker Visceri || Rouge
    SPELL_EVISCERATE                = 67709,
    SPELL_EVISCERATE_H              = 68317,
    SPELL_FAN_OF_KNIVES             = 67706,
    SPELL_POISON_BOTTLE             = 67701,
	
	// Other
	SPELL_TRAMPLED                  = 67868
};

enum Seats
{
    SEAT_ID_0                       = 0
};

bool GrandChampionsOutVehicle(Creature* me)
{
    InstanceScript* instance = me->GetInstanceScript();

    if (!instance)
        return false;

    Creature* pGrandChampion1 = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_GRAND_CHAMPION_1));
    Creature* pGrandChampion2 = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_GRAND_CHAMPION_2));
    Creature* pGrandChampion3 = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_GRAND_CHAMPION_3));

    if (pGrandChampion1 && pGrandChampion2 && pGrandChampion3)
    {
        if (!pGrandChampion1->HasUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT) &&
            !pGrandChampion2->HasUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT) &&
            !pGrandChampion3->HasUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT))
            return true;
    }

    return false;
}

class generic_vehicle_toc5 : public CreatureScript
{
public:
    generic_vehicle_toc5() : CreatureScript("generic_vehicle_toc5") { }

    struct generic_vehicle_toc5AI : public npc_escortAI
    {
        generic_vehicle_toc5AI(Creature* creature) : npc_escortAI(creature), vehicle(creature->GetVehicleKit())
        {
            Initialize();
            SetDespawnAtEnd(false);

			uiWaypointPath = 0;
			uiDataVehicle = 0;
			uiOrientationId = 0;
			seatPlayer = false;
			noShield = false;
			isMove = false;
			me->SetReactState(REACT_PASSIVE);
			
            instance = creature->GetInstanceScript();
        }

        void Initialize()
        {
            uiChargeTimer = 5000;
            uiShieldBreakerTimer = 8000;
            uiBuffTimer = 0;
			uiMoveTimer = 6000;
			uiStunTimer = 2000;
        }

        InstanceScript* instance;
		Vehicle* vehicle;

        uint32 uiChargeTimer;
        uint32 uiShieldBreakerTimer;
        uint32 uiBuffTimer;
		uint32 uiStunTimer;
		uint32 uiMoveTimer;

        uint32 uiWaypointPath;
		uint32 uiDataVehicle;
		uint32 uiOrientationId;
		
		bool seatPlayer;
		bool noShield;
		bool isMove;

        void Reset() override
        {
			ASSERT(vehicle);
            Initialize();
			me->SetSpeed(MOVE_RUN, 1.385f);
		}

		void PassengerBoarded(Unit* who, int8 seatId, bool apply) override
		{
			if (me->GetEntry() == VEHICLE_ARGENT_WARHORSE || me->GetEntry() == VEHICLE_ARGENT_BATTLEWORG)
			{
				if (who->GetTypeId() == TYPEID_PLAYER)
					seatPlayer = true;
				else
				{
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetReactState(REACT_AGGRESSIVE);
					me->AddAura(67870, me);
					who->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					who->ToCreature()->SetReactState(REACT_AGGRESSIVE);
					who->SetHealth(who->GetMaxHealth() * 27 / 100); // 27 % health (official)
					who->SetSpeed(MOVE_RUN, 1.428f);
					DoZoneInCombat(NULL, 1000.f);
					DoZoneInCombat(who->ToCreature(), 1000.f);
					noShield = true;
				}
			}
			else
				me->AddAura(67870, me);
		}

		void DoAction(int32 /*action*/)
		{
			npc_escortAI::_EnterEvadeMode();
			me->SetReactState(REACT_PASSIVE);
			me->GetMotionMaster()->MovePoint(3, me->GetRandomNearPosition(30.f));
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		}

		void EnterEvadeMode()
		{
			if (seatPlayer)
				return;
					
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
				instance->SetData(BOSS_GRAND_CHAMPIONS, FAIL);
			else
				DoZoneInCombat(me, 1000.f);
		}

		void SetData(uint32 point, uint32 type)
		{
			for (uint8 i = 0; i < 3; ++i)
				AddWaypoint(i, VehicleMove[point + i].GetPositionX(), VehicleMove[point + i].GetPositionY(), VehicleMove[point + i].GetPositionZ());

			uiOrientationId = point + 2;
			uiDataVehicle = type;
			switch (type)
			{
			case 1:
			case 4:
				uiWaypointPath = 1;
				break;
			case 2:
			case 5:
				uiWaypointPath = 2;
				break;
			case 3:
			case 6:
				uiWaypointPath = 3;
				break;
			}

			Start(false, true);
		}
		
		void MovementInform(uint32 type, uint32 pointId) override
		{
			npc_escortAI::MovementInform(type, pointId);
			 if (type != POINT_MOTION_TYPE)
                return;
				
			if (pointId == 3)
				me->DespawnOrUnsummon();
			if (pointId == 4)
				isMove = false;
		}

        void WaypointReached(uint32 waypointId) override
        {
            switch (waypointId)
            {
				case 0:
					me->SetSpeed(MOVE_RUN, 0.5f);
					if (Creature* announcer = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_ANNOUNCER)))
						announcer->AI()->SetData(DATA_CHANGE_SPEED, uiWaypointPath);
					break;
                case 2:
					me->SetSpeed(MOVE_RUN, 1.385f);
					me->SetOrientation(VehicleMove[uiOrientationId].GetOrientation());
					if (Creature* announcer = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_ANNOUNCER)))
						announcer->AI()->SetData(DATA_RESET_SPEED, uiDataVehicle);
					me->SendMovementFlagUpdate();
                    instance->SetData(DATA_MOVEMENT_DONE, instance->GetData(DATA_MOVEMENT_DONE)+1);
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/) override
        {
        }

		void UpdateEscortAI(uint32 const /*diff*/) override
		{
		}

        void UpdateAI(uint32 uiDiff) override
        {
			if (seatPlayer)
				return;

            npc_escortAI::UpdateAI(uiDiff);

			if (!noShield)
			{
				if (uiBuffTimer <= uiDiff)
				{
					if (Unit* passenger = vehicle->GetPassenger(SEAT_ID_0))
						passenger->AddAura(SPELL_SHIELD, passenger);

					uiBuffTimer = urand(5000, 15000);
				}
				else
					uiBuffTimer -= uiDiff;
			}
			
			if (!UpdateVictim())
				return;

			if (uiMoveTimer <= uiDiff)
			{
				uiMoveTimer = urand(6000, 12000);
				Position pos = me->GetRandomNearPosition(30.f);
				me->GetMotionMaster()->MoveCharge(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), 10.385f, 4);
				isMove = true;
			}
			else
				uiMoveTimer -= uiDiff;

			if (isMove)
				return;

			if (uiChargeTimer <= uiDiff)
            {
				Map::PlayerList const& players = me->GetMap()->GetPlayers();

				if (me->GetMap()->IsDungeon() && !players.isEmpty())
				{
					for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
					{
						Player* player = itr->GetSource();
						if (!player)
							continue;

						Unit* target = player->GetVehicleBase();
						if (!target)
							target = player;

						if (me->IsInRange(target, 8.f, 25.f, false))
						{
							DoCast(target, SPELL_CHARGE, false);
							break;
						}
					}
				}

				uiChargeTimer = 5000;
            }
			else
				uiChargeTimer -= uiDiff;
				
            if (uiShieldBreakerTimer <= uiDiff)
            {
				Map::PlayerList const& players = me->GetMap()->GetPlayers();
					
				if (Unit* passenger = vehicle->GetPassenger(SEAT_ID_0))
				{
					if (me->GetMap()->IsDungeon() && !players.isEmpty())
					{
						for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
						{
							Player* player = itr->GetSource();
							if (!player)
								continue;

							Unit* target = player->GetVehicleBase();
							if (!target)
								target = player;

							if (me->IsInRange(target, 10.f, 30.f, false))
							{
								passenger->GetAI()->DoCast(target, SPELL_SHIELD_BREAKER, true);
								break;
							}
						}
					}
				}

				uiShieldBreakerTimer = 7000;
            }
			else
				uiShieldBreakerTimer -= uiDiff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
		return GetInstanceAI<generic_vehicle_toc5AI>(creature);
    }
};

Position const ChampionMove[18] =
{
	{ 710.737f, 600.84f, 411.864f, 0.287f },
	{ 709.457f, 605.592f, 411.88f, 0.287f },
	{ 708.363f, 610.435f, 411.882f, 0.287f },

	{ 706.741f, 622.064f, 411.892f, 6.093f },
	{ 708.178f, 627.004f, 411.897f, 6.093f },
	{ 709.516f, 631.601f, 411.91f, 6.093f },

	{ 713.398f, 645.631f, 411.935f, 5.747f },
	{ 717.646f, 646.656f, 411.921f, 5.747f },
	{ 719.829f, 651.063f, 411.927f, 5.747f },

	{ 787.259f, 629.129f, 411.923f, 3.458f },
	{ 785.042f, 633.785f, 411.925f, 3.615f },
	{ 783.584f, 637.321f, 411.93f, 3.717f },

	{ 779.553f, 647.798f, 412.f, 4.081f },
	{ 776.264f, 649.269f, 411.9f, 4.081f },
	{ 773.91f, 652.067f, 411.9f, 4.081f },

	{ 787.92f, 615.083f, 411.9f, 3.225f },
	{ 788.119f, 618.577f, 411.9f, 3.225f },
	{ 788.337f, 622.384f, 411.9f, 3.225f }
};

class champion_toc5 : public CreatureScript
{
public:
    champion_toc5() : CreatureScript("champion_toc5") { }

	struct champion_toc5AI : public ScriptedAI
    {
        champion_toc5AI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
			me->SetReactState(REACT_PASSIVE);
            instance = creature->GetInstanceScript();
        }

        void Initialize()
        {
			me->SetSpeed(MOVE_RUN, 1.385f);
            uiChargeTimer = 5000;
			uiBuffTimer = 0;
			uiPoint = 0;
        }

        InstanceScript* instance;

        uint32 uiChargeTimer;
		uint32 uiBuffTimer;
		uint32 uiPoint;

        void Reset() override
        {
            Initialize();
        }

		void SetData(uint32 uiType, uint32 point)
        {
			me->GetMotionMaster()->MovePoint(0, ChampionMove[point]);
			uiPoint = point;
		}
		
		void MovementInform(uint32 type, uint32 pointId) override
		{
			if (type != POINT_MOTION_TYPE)
				return;

			switch (pointId)
			{
			case 0:
				me->SetSpeed(MOVE_RUN, 1.385f);
				me->SetOrientation(ChampionMove[uiPoint].GetOrientation());
				me->SendMovementFlagUpdate();
				break;
			}
		}
		
		void KilledUnit(Unit* victim)
		{
			if (victim->GetTypeId() == TYPEID_UNIT)
				instance->SetData(BOSS_GRAND_CHAMPIONS, FAIL);
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
				instance->SetData(BOSS_GRAND_CHAMPIONS, FAIL);
			else
				DoZoneInCombat(me, 1000.f);
		}

        void EnterCombat(Unit* /*who*/) override
        {
			uiChargeTimer = 5000;
        }

        void UpdateAI(uint32 uiDiff) override
        {
			if (uiBuffTimer <= uiDiff)
            {
				if (!me->HasAura(SPELL_SHIELD))
					me->AddAura(SPELL_SHIELD, me);

                uiBuffTimer = urand(5000, 15000);
            }
			else
				uiBuffTimer -= uiDiff;

			if (!UpdateVictim())
				return;

            if (uiChargeTimer <= uiDiff)
            {
				Map::PlayerList const& players = me->GetMap()->GetPlayers();

				if (me->GetMap()->IsDungeon() && !players.isEmpty())
				{
					for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
					{
						Player* player = itr->GetSource();
						if (!player)
							continue;

						Unit* target = player->GetVehicleBase();
						if (!target)
							target = player;

						if (me->IsInRange(target, 8.f, 25.f, false))
						{
							DoCast(target, SPELL_CHARGE, false);
							break;
						}
					}
				}

                uiChargeTimer = 5000;
            }
			else
				uiChargeTimer -= uiDiff;
				
			DoMeleeAttackIfReady();
        }

		void JustDied(Unit* /*killer*/) override
		{
			me->Dismount();
		}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<champion_toc5AI>(creature);
    }
};

enum EventsWarrior
{
	EVENT_BLADESTORM = 1,
	EVENT_INTERCEPT,
	EVENT_MORTAL_STRIKE
};

class boss_warrior_toc5 : public CreatureScript
{
public:
    boss_warrior_toc5() : CreatureScript("boss_warrior_toc5") { }

    // Marshal Jacob Alerius && Mokra the Skullcrusher || Warrior
    struct boss_warrior_toc5AI : public ScriptedAI
    {
        boss_warrior_toc5AI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();

			phase = 1;
			uiResetTimer = 0;

            me->SetReactState(REACT_PASSIVE);
            // THIS IS A HACK, SHOULD BE REMOVED WHEN THE EVENT IS FULL SCRIPTED
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
			me->LoadEquipment(2);
        }

        InstanceScript* instance;
		EventMap events;

		uint8 phase;
		uint32 uiResetTimer;
		ObjectGuid newHorseGUID;
		
		void DoAction(int32 action) override
		{
			switch (action)
			{
				case 0:
					me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
					me->LoadEquipment(1);
					me->GetMotionMaster()->MovePoint(0, 746.634f, 666.458f, 414.484f);
					break;
			}
		}

		void DamageTaken(Unit* /*done_by*/, uint32 &damage) override
		{
			switch (phase)
			{
			case 1:
				if (damage >= me->GetHealth())
				{
					damage = 0;
					if (me->GetVehicle())
					{
						Creature* creature = me->GetVehicleCreatureBase();
						me->ExitVehicle();
						creature->AI()->DoAction(0);
					}

					if (me->HasAura(SPELL_SHIELD))
						me->RemoveAura(SPELL_SHIELD);

					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
					me->DeleteThreatList();
					me->CombatStop(true);
					instance->SetData(DATA_GRAND_CHAMPIONS_PHASE, DONE);
					uiResetTimer = 5000;
				}
				break;
			case 2:
				if (damage >= me->GetHealth())
				{
					damage = 0;

					me->SetOrientation(ORIENTATION);
					me->UpdateMovementFlags();
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetByteFlag(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_KNEEL);
					me->SetSpeed(MOVE_RUN, 0.6f);
					me->DeleteThreatList();
					me->CombatStop(true);
					events.Reset();

					instance->SetData(BOSS_GRAND_CHAMPIONS, DONE);
				}
			}
		}

		void EnterCombat(Unit* who) override
		{
			if (phase == 1)
				return;

			events.ScheduleEvent(EVENT_BLADESTORM, urand(15000, 20000));
			events.ScheduleEvent(EVENT_INTERCEPT, 7000);
			events.ScheduleEvent(EVENT_MORTAL_STRIKE, urand(8000, 12000));
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
				instance->SetData(BOSS_GRAND_CHAMPIONS, FAIL);
			else
				DoZoneInCombat(me, 1000.f);
		}

		void MovementInform(uint32 type, uint32 pointId) override
		{
			if (type != POINT_MOTION_TYPE)
				return;

			switch (pointId)
			{
			case 0:
				switch (phase)
				{
					case 1:
						me->SetVisible(false);
						instance->SetData(DATA_GRAND_CHAMPIONS_MOVEMENT, DONE);
						break;
					case 2:
						me->DespawnOrUnsummon();
						break;
				}
				break;
			case 1:
				me->SetHealth(me->GetMaxHealth());
				me->SetVisible(true);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
				phase = 2;
				break;
			case 2:
				if (Creature* vehicle = ObjectAccessor::GetCreature(*me, newHorseGUID))
					me->EnterVehicle(vehicle);
				break;
			}
		}

        void UpdateAI(uint32 diff) override
        {
			if (uiResetTimer != 0)
			{
				if (uiResetTimer <= diff)
				{
					uiResetTimer = 0;
					if (Creature* creature = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_GRAND_CHAMPION_VEHICLE)))
					{
						newHorseGUID = creature->GetGUID();
						instance->SetGuidData(DATA_GRAND_CHAMPION_VEHICLE_R, newHorseGUID);
						me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
						me->SetSpeed(MOVE_RUN, 0.6f);
						me->GetMotionMaster()->MovePoint(2, creature->GetPosition());
						instance->SetData(DATA_GRAND_CHAMPIONS_PHASE, FAIL);
					}
				}
				else
					uiResetTimer -= diff;
			}
		
            if (!UpdateVictim())
                return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_INTERCEPT:
				{
					Map::PlayerList const& players = me->GetMap()->GetPlayers();
					if (me->GetMap()->IsDungeon() && !players.isEmpty())
					{
						for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
						{
							Player* player = itr->GetSource();
							if (player && !player->IsGameMaster() && me->IsInRange(player, 8.0f, 25.0f, false))
							{
								DoCast(player, SPELL_INTERCEPT, true);
								break;
							}
						}
					}
					events.ScheduleEvent(EVENT_INTERCEPT, 7000);
					break;
				}
				case EVENT_BLADESTORM:
					DoCastVictim(SPELL_BLADESTORM);
					events.ScheduleEvent(EVENT_BLADESTORM, urand(15000, 20000));
					break;
				case EVENT_MORTAL_STRIKE:
					DoCastVictim(SPELL_MORTAL_STRIKE);
					events.ScheduleEvent(EVENT_MORTAL_STRIKE, urand(8000, 12000));
					break;
				}
			}

			if (me->GetVehicle() || phase == 2)
				DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) override
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<boss_warrior_toc5AI>(creature);
    }
};

enum EventMage
{
	EVENT_FIREBALL = 1,
	EVENT_POLYMORPH,
	EVENT_BLASTWAVE,
	EVENT_HASTE,
};

class boss_mage_toc5 : public CreatureScript
{
public:
    boss_mage_toc5() : CreatureScript("boss_mage_toc5") { }

    // Ambrose Boltspark && Eressea Dawnsinger || Mage
    struct boss_mage_toc5AI : public ScriptedAI
    {
        boss_mage_toc5AI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();

			phase = 1;
			uiResetTimer = 0;

            me->SetReactState(REACT_PASSIVE);
            // THIS IS A HACK, SHOULD BE REMOVED WHEN THE EVENT IS FULL SCRIPTED
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
			me->LoadEquipment(2);
        }

        InstanceScript* instance;
		EventMap events;

		uint8 phase;
		uint32 uiResetTimer;
		ObjectGuid newHorseGUID;

		void DoAction(int32 action) override
		{
			switch (action)
			{
				case 0:
					me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
					me->LoadEquipment(1);
					me->GetMotionMaster()->MovePoint(0, 746.634f, 666.458f, 414.484f);
					break;
			}
		}

		void DamageTaken(Unit* /*done_by*/, uint32 &damage) override
		{
			switch (phase)
			{
			case 1:
				if (damage >= me->GetHealth())
				{
					damage = 0;
					if (me->GetVehicle())
					{
						Creature* creature = me->GetVehicleCreatureBase();
						me->ExitVehicle();
						creature->AI()->DoAction(0);
					}

					if (me->HasAura(SPELL_SHIELD))
						me->RemoveAura(SPELL_SHIELD);

					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
					me->DeleteThreatList();
					me->CombatStop(true);
					instance->SetData(DATA_GRAND_CHAMPIONS_PHASE, DONE);
					uiResetTimer = 5000;
				}
				break;
			case 2:
				if (damage >= me->GetHealth())
				{
					damage = 0;

					me->SetOrientation(ORIENTATION);
					me->UpdateMovementFlags();
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetByteFlag(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_KNEEL);
					me->SetSpeed(MOVE_RUN, 0.6f);
					me->DeleteThreatList();
					me->CombatStop(true);
					events.Reset();

					instance->SetData(BOSS_GRAND_CHAMPIONS, DONE);
				}
			}
		}

		void EnterCombat(Unit* who) override
		{
			if (phase == 1)
				return;

			events.ScheduleEvent(EVENT_FIREBALL, 5000);
			events.ScheduleEvent(EVENT_POLYMORPH, 8000);
			events.ScheduleEvent(EVENT_BLASTWAVE, 12000);
			events.ScheduleEvent(EVENT_HASTE, 22000);
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
				instance->SetData(BOSS_GRAND_CHAMPIONS, FAIL);
			else
				DoZoneInCombat(me, 1000.f);
		}

		void MovementInform(uint32 type, uint32 pointId) override
		{
			if (type != POINT_MOTION_TYPE)
				return;

			switch (pointId)
			{
			case 0:
				switch (phase)
				{
					case 1:
						me->SetVisible(false);
						instance->SetData(DATA_GRAND_CHAMPIONS_MOVEMENT, DONE);
						break;
					case 2:
						me->DespawnOrUnsummon();
						break;
				}
				break;
			case 1:
				me->SetHealth(me->GetMaxHealth());
				me->SetVisible(true);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
				phase = 2;
				break;
			case 2:
				if (Creature* vehicle = ObjectAccessor::GetCreature(*me, newHorseGUID))
					me->EnterVehicle(vehicle);
				break;
			}
		}

		void UpdateAI(uint32 diff) override
        {
			if (uiResetTimer != 0)
			{
				if (uiResetTimer <= diff)
				{
					uiResetTimer = 0;
					if (Creature* creature = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_GRAND_CHAMPION_VEHICLE)))
					{
						newHorseGUID = creature->GetGUID();
						instance->SetGuidData(DATA_GRAND_CHAMPION_VEHICLE_R, newHorseGUID);
						me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
						me->SetSpeed(MOVE_RUN, 0.6f);
						me->GetMotionMaster()->MovePoint(2, creature->GetPosition());
						instance->SetData(DATA_GRAND_CHAMPIONS_PHASE, FAIL);
					}
				}
				else
					uiResetTimer -= diff;
			}

			if (!UpdateVictim())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_FIREBALL:
					DoCastVictim(SPELL_FIREBALL);
					events.ScheduleEvent(EVENT_FIREBALL, 5000);
					break;
				case EVENT_POLYMORPH:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
						DoCast(target, SPELL_POLYMORPH);
					events.ScheduleEvent(EVENT_POLYMORPH, 8000);
					break;
				case EVENT_BLASTWAVE:
					DoCastAOE(SPELL_BLAST_WAVE, false);
					events.ScheduleEvent(EVENT_BLASTWAVE, 13000);
					break;
				case EVENT_HASTE:
					me->InterruptNonMeleeSpells(true);
					DoCast(me, SPELL_HASTE);
					events.ScheduleEvent(EVENT_HASTE, 22000);
					break;
				}
			}

			if (me->GetVehicle() || phase == 2)
				DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) override
        {
            instance->SetData(BOSS_GRAND_CHAMPIONS, DONE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<boss_mage_toc5AI>(creature);
    }
};

enum EventShaman
{
	EVENT_CHAIN_LIGHTNING = 1,
	EVENT_EART_SHIELD,
	EVENT_HEALING_WAVE,
	EVENT_HEX_MENDING
};

class boss_shaman_toc5 : public CreatureScript
{
public:
    boss_shaman_toc5() : CreatureScript("boss_shaman_toc5") { }

    // Colosos && Runok Wildmane || Shaman
    struct boss_shaman_toc5AI : public ScriptedAI
    {
        boss_shaman_toc5AI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();

			phase = 1;
			uiResetTimer = 0;

            me->SetReactState(REACT_PASSIVE);
            // THIS IS A HACK, SHOULD BE REMOVED WHEN THE EVENT IS FULL SCRIPTED
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
			me->LoadEquipment(2);
        }

        InstanceScript* instance;
		EventMap events;

		uint8 phase;
		uint32 uiResetTimer;
		ObjectGuid newHorseGUID;

		void DoAction(int32 action) override
		{
			switch (action)
			{
				case 0:
					me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
					me->LoadEquipment(1);
					me->GetMotionMaster()->MovePoint(0, 746.634f, 666.458f, 414.484f);
					break;
			}
		}

		void DamageTaken(Unit* /*done_by*/, uint32 &damage) override
		{
			switch (phase)
			{
			case 1:
				if (damage >= me->GetHealth())
				{
					damage = 0;
					if (me->GetVehicle())
					{
						Creature* creature = me->GetVehicleCreatureBase();
						me->ExitVehicle();
						creature->AI()->DoAction(0);
					}

					if (me->HasAura(SPELL_SHIELD))
						me->RemoveAura(SPELL_SHIELD);

					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
					me->DeleteThreatList();
					me->CombatStop(true);
					instance->SetData(DATA_GRAND_CHAMPIONS_PHASE, DONE);
					uiResetTimer = 5000;
				}
				break;
			case 2:
				if (damage >= me->GetHealth())
				{
					damage = 0;

					me->SetOrientation(ORIENTATION);
					me->UpdateMovementFlags();
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetByteFlag(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_KNEEL);
					me->SetSpeed(MOVE_RUN, 0.6f);
					me->DeleteThreatList();
					me->CombatStop(true);
					events.Reset();

					instance->SetData(BOSS_GRAND_CHAMPIONS, DONE);
				}
			}
		}

        void EnterCombat(Unit* who) override
        {
			if (phase == 1)
				return;

			events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 16000);
			events.ScheduleEvent(EVENT_HEALING_WAVE, 12000);
			events.ScheduleEvent(EVENT_EART_SHIELD, urand(30000, 35000));
			events.ScheduleEvent(EVENT_HEX_MENDING, urand(20000, 25000));

            DoCast(me, SPELL_EARTH_SHIELD);
            DoCast(who, SPELL_HEX_OF_MENDING);
        };
		
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
				instance->SetData(BOSS_GRAND_CHAMPIONS, FAIL);
			else
				DoZoneInCombat(me, 1000.f);
		}

		void MovementInform(uint32 type, uint32 pointId) override
		{
			if (type != POINT_MOTION_TYPE)
				return;

			switch (pointId)
			{
			case 0:
				switch (phase)
				{
					case 1:
						me->SetVisible(false);
						instance->SetData(DATA_GRAND_CHAMPIONS_MOVEMENT, DONE);
						break;
					case 2:
						me->DespawnOrUnsummon();
						break;
				}
				break;
			case 1:
				me->SetHealth(me->GetMaxHealth());
				me->SetVisible(true);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
				phase = 2;
				break;
			case 2:
				if (Creature* vehicle = ObjectAccessor::GetCreature(*me, newHorseGUID))
					me->EnterVehicle(vehicle);
				break;
			}
		}

		void UpdateAI(uint32 diff) override
        {
			if (uiResetTimer != 0)
			{
				if (uiResetTimer <= diff)
				{
					uiResetTimer = 0;
					if (Creature* creature = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_GRAND_CHAMPION_VEHICLE)))
					{
						newHorseGUID = creature->GetGUID();
						instance->SetGuidData(DATA_GRAND_CHAMPION_VEHICLE_R, newHorseGUID);
						me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
						me->SetSpeed(MOVE_RUN, 0.6f);
						me->GetMotionMaster()->MovePoint(2, creature->GetPosition());
						instance->SetData(DATA_GRAND_CHAMPIONS_PHASE, FAIL);
					}
				}
				else
					uiResetTimer -= diff;
			}

			if (!UpdateVictim())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_CHAIN_LIGHTNING:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
						DoCast(target, SPELL_CHAIN_LIGHTNING);
					events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 16000);
					break;
				case EVENT_HEALING_WAVE:
				{
					bool bChance = roll_chance_i(50);

					if (!bChance)
					{
						if (Unit* pFriend = DoSelectLowestHpFriendly(40))
							DoCast(pFriend, SPELL_HEALING_WAVE);
					}
					else
						DoCast(me, SPELL_HEALING_WAVE);
					break;
				}
				case EVENT_EART_SHIELD:
					DoCast(me, SPELL_EARTH_SHIELD);
					events.ScheduleEvent(EVENT_EART_SHIELD, urand(30000, 35000));
					break;
				case EVENT_HEX_MENDING:
					DoCastVictim(SPELL_HEX_OF_MENDING, true);
					events.ScheduleEvent(EVENT_HEX_MENDING, urand(20000, 25000));
					break;
				}
			}

			if (me->GetVehicle() || phase == 2)
				DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) override
        {
            instance->SetData(BOSS_GRAND_CHAMPIONS, DONE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<boss_shaman_toc5AI>(creature);
    }
};

enum EventHunter
{
	EVENT_SHOOT = 1,
	EVENT_MULTI_SHOT,
	EVENT_LIGHTNING_ARROWS
};

class boss_hunter_toc5 : public CreatureScript
{
public:
    boss_hunter_toc5() : CreatureScript("boss_hunter_toc5") { }

    // Jaelyne Evensong && Zul'tore || Hunter
    struct boss_hunter_toc5AI : public ScriptedAI
    {
        boss_hunter_toc5AI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
            instance = creature->GetInstanceScript();

			phase = 1;
			uiResetTimer = 0;

            me->SetReactState(REACT_PASSIVE);
            // THIS IS A HACK, SHOULD BE REMOVED WHEN THE EVENT IS FULL SCRIPTED
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
			me->LoadEquipment(2);
        }

        void Initialize()
        {
			targetGUID.Clear();
			newHorseGUID.Clear();
        }

        InstanceScript* instance;
		EventMap events;

		uint8 phase;
		uint32 uiResetTimer;
		ObjectGuid newHorseGUID;

		ObjectGuid targetGUID;

        void Reset() override
        {
            Initialize();
        }

		void DoAction(int32 action) override
		{
			switch (action)
			{
				case 0:
					me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
					me->LoadEquipment(1);
					me->GetMotionMaster()->MovePoint(0, 746.634f, 666.458f, 414.484f);
					break;
			}
		}

		void DamageTaken(Unit* /*done_by*/, uint32 &damage) override
		{
			switch (phase)
			{
			case 1:
				if (damage >= me->GetHealth())
				{
					damage = 0;
					if (me->GetVehicle())
					{
						Creature* creature = me->GetVehicleCreatureBase();
						me->ExitVehicle();
						creature->AI()->DoAction(0);
					}

					if (me->HasAura(SPELL_SHIELD))
						me->RemoveAura(SPELL_SHIELD);

					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
					me->DeleteThreatList();
					me->CombatStop(true);
					instance->SetData(DATA_GRAND_CHAMPIONS_PHASE, DONE);
					uiResetTimer = 5000;
				}
				break;
			case 2:
				if (damage >= me->GetHealth())
				{
					damage = 0;

					me->SetOrientation(ORIENTATION);
					me->UpdateMovementFlags();
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetByteFlag(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_KNEEL);
					me->SetSpeed(MOVE_RUN, 0.6f);
					me->DeleteThreatList();
					me->CombatStop(true);
					events.Reset();

					instance->SetData(BOSS_GRAND_CHAMPIONS, DONE);
				}
			}
		}

		void EnterCombat(Unit* who) override
		{
			if (phase == 1)
				return;

			events.ScheduleEvent(EVENT_SHOOT, 12000);
			events.ScheduleEvent(EVENT_LIGHTNING_ARROWS, 7000);

			DoCast(me, SPELL_EARTH_SHIELD);
			DoCast(who, SPELL_HEX_OF_MENDING);
		};

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
				instance->SetData(BOSS_GRAND_CHAMPIONS, FAIL);
			else
				DoZoneInCombat(me, 1000.f);
		}
		
		void MovementInform(uint32 type, uint32 pointId) override
		{
			if (type != POINT_MOTION_TYPE)
				return;

			switch (pointId)
			{
			case 0:
				switch (phase)
				{
					case 1:
						me->SetVisible(false);
						instance->SetData(DATA_GRAND_CHAMPIONS_MOVEMENT, DONE);
						break;
					case 2:
						me->DespawnOrUnsummon();
						break;
				}
				break;
			case 1:
				me->SetHealth(me->GetMaxHealth());
				me->SetVisible(true);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
				phase = 2;
				break;
			case 2:
				if (Creature* vehicle = ObjectAccessor::GetCreature(*me, newHorseGUID))
					me->EnterVehicle(vehicle);
				break;
			}
		}

		void UpdateAI(uint32 diff) override
        {
			if (uiResetTimer != 0)
			{
				if (uiResetTimer <= diff)
				{
					uiResetTimer = 0;
					if (Creature* creature = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_GRAND_CHAMPION_VEHICLE)))
					{
						newHorseGUID = creature->GetGUID();
						instance->SetGuidData(DATA_GRAND_CHAMPION_VEHICLE_R, newHorseGUID);
						me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
						me->SetSpeed(MOVE_RUN, 0.6f);
						me->GetMotionMaster()->MovePoint(2, creature->GetPosition());
						instance->SetData(DATA_GRAND_CHAMPIONS_PHASE, FAIL);
					}
				}
				else
					uiResetTimer -= diff;
			}

            if (!UpdateVictim())
                return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_LIGHTNING_ARROWS:
					DoCastAOE(SPELL_LIGHTNING_ARROWS, false);
					events.ScheduleEvent(EVENT_LIGHTNING_ARROWS, 7000);
					break;
				case EVENT_SHOOT:
					if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 30.0f))
					{
						targetGUID = target->GetGUID();
						DoCast(target, SPELL_SHOOT);
					}
					events.ScheduleEvent(EVENT_SHOOT, 12000);
					events.ScheduleEvent(EVENT_MULTI_SHOT, 3000);
					break;
				case EVENT_MULTI_SHOT:
				{
					Unit* target = ObjectAccessor::GetUnit(*me, targetGUID);

					if (target && me->IsInRange(target, 5.0f, 30.0f, false))
					{
						DoCast(target, SPELL_MULTI_SHOT);
					}
					else
					{
						Map::PlayerList const& players = me->GetMap()->GetPlayers();
						if (me->GetMap()->IsDungeon() && !players.isEmpty())
						{
							for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
							{
								Player* player = itr->GetSource();
								if (player && !player->IsGameMaster() && me->IsInRange(player, 5.0f, 30.0f, false))
								{
									DoCast(player, SPELL_MULTI_SHOT);
									break;
								}
							}
						}
					}
					break;
				}
				}
			}

            if (me->GetVehicle() || phase == 2)
				DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) override
        {
            instance->SetData(BOSS_GRAND_CHAMPIONS, DONE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<boss_hunter_toc5AI>(creature);
    }
};

enum EventRogue
{
	EVENT_EVISCERATE = 1,
	EVENT_FAN_KIVES,
	EVENT_POSION_BOTTLE
};

class boss_rouge_toc5 : public CreatureScript
{
public:
    boss_rouge_toc5() : CreatureScript("boss_rouge_toc5") { }

    // Lana Stouthammer Evensong && Deathstalker Visceri || Rouge
    struct boss_rouge_toc5AI : public ScriptedAI
    {
        boss_rouge_toc5AI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();

			phase = 1;
			uiResetTimer = 0;

            me->SetReactState(REACT_PASSIVE);
            // THIS IS A HACK, SHOULD BE REMOVED WHEN THE EVENT IS FULL SCRIPTED
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
			me->LoadEquipment(2);
        }

        InstanceScript* instance;
		EventMap events;

		uint8 phase;
		uint32 uiResetTimer;
		ObjectGuid newHorseGUID;

		void DoAction(int32 action) override
		{
			switch (action)
			{
				case 0:
					me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
					me->LoadEquipment(1);
					me->GetMotionMaster()->MovePoint(0, 746.634f, 666.458f, 414.484f);
					break;
			}
		}
		
		void DamageTaken(Unit* /*done_by*/, uint32 &damage) override
		{
			switch (phase)
			{
			case 1:
				if (damage >= me->GetHealth())
				{
					damage = 0;
					if (me->GetVehicle())
					{
						Creature* creature = me->GetVehicleCreatureBase();
						me->ExitVehicle();
						creature->AI()->DoAction(0);
					}

					if (me->HasAura(SPELL_SHIELD))
						me->RemoveAura(SPELL_SHIELD);

					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
					me->DeleteThreatList();
					me->CombatStop(true);
					instance->SetData(DATA_GRAND_CHAMPIONS_PHASE, DONE);
					uiResetTimer = 5000;
				}
				break;
			case 2:
				if (damage >= me->GetHealth())
				{
					damage = 0;
					
					me->SetOrientation(ORIENTATION);
					me->UpdateMovementFlags();
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
					me->SetByteFlag(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_KNEEL);
					me->SetSpeed(MOVE_RUN, 0.6f);
					me->DeleteThreatList();
					me->CombatStop(true);
					events.Reset();

					instance->SetData(BOSS_GRAND_CHAMPIONS, DONE);
				}
			}
		}

		void EnterCombat(Unit* who) override
		{
			if (phase == 1)
				return;

			events.ScheduleEvent(EVENT_EVISCERATE, 8000);
			events.ScheduleEvent(EVENT_FAN_KIVES, 14000);
			events.ScheduleEvent(EVENT_POSION_BOTTLE, 19000);

			DoCast(me, SPELL_EARTH_SHIELD);
			DoCast(who, SPELL_HEX_OF_MENDING);
		};
		
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
				instance->SetData(BOSS_GRAND_CHAMPIONS, FAIL);
			else
				DoZoneInCombat(me, 1000.f);
		}

		void MovementInform(uint32 type, uint32 pointId) override
		{
			if (type != POINT_MOTION_TYPE)
				return;

			switch (pointId)
			{
			case 0:
				switch (phase)
				{
					case 1:
						me->SetVisible(false);
						instance->SetData(DATA_GRAND_CHAMPIONS_MOVEMENT, DONE);
						break;
					case 2:
						me->DespawnOrUnsummon();
						break;
				}
				break;
			case 1:
				me->SetHealth(me->GetMaxHealth());
				me->SetVisible(true);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
				phase = 2;
				break;
			case 2:
				if (Creature* vehicle = ObjectAccessor::GetCreature(*me, newHorseGUID))
					me->EnterVehicle(vehicle);
				break;
			}
		}

        void UpdateAI(uint32 diff) override
        {
			if (uiResetTimer != 0)
			{
				if (uiResetTimer <= diff)
				{
					uiResetTimer = 0;
					if (Creature* creature = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_GRAND_CHAMPION_VEHICLE)))
					{
						newHorseGUID = creature->GetGUID();
						instance->SetGuidData(DATA_GRAND_CHAMPION_VEHICLE_R, newHorseGUID);
						me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
						me->SetSpeed(MOVE_RUN, 0.6f);
						me->GetMotionMaster()->MovePoint(2, creature->GetPosition());
						instance->SetData(DATA_GRAND_CHAMPIONS_PHASE, FAIL);
					}
				}
				else
					uiResetTimer -= diff;
			}

			if (!UpdateVictim())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_EVISCERATE:
					DoCastVictim(SPELL_EVISCERATE);
					events.ScheduleEvent(EVENT_EVISCERATE, 8000);
					break;
				case EVENT_FAN_KIVES:
					DoCastAOE(SPELL_FAN_OF_KNIVES, false);
					events.ScheduleEvent(EVENT_FAN_KIVES, 14000);
					break;
				case EVENT_POSION_BOTTLE:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
						DoCast(target, SPELL_POISON_BOTTLE);
					events.ScheduleEvent(EVENT_POSION_BOTTLE, 19000);
					break;
				}
			}

			if (me->GetVehicle() || phase == 2)
				DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) override
        {
            instance->SetData(BOSS_GRAND_CHAMPIONS, DONE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<boss_rouge_toc5AI>(creature);
    }
};

// 67830 - Ride Vehicle
class spell_ride_vehicle_toc5 : public SpellScriptLoader
{
public:
	spell_ride_vehicle_toc5() : SpellScriptLoader("spell_ride_vehicle_toc5") { }

	class spell_ride_vehicle_toc5_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_ride_vehicle_toc5_SpellScript);

		SpellCastResult CheckCast()
		{
			Unit* caster = GetCaster();

			if (caster->GetMapId() != 650)
				return SPELL_CAST_OK;

			if (Player* player = caster->ToPlayer())
				if (player->HasItemOrGemWithIdEquipped(46106, 1))
					return SPELL_CAST_OK;

			SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_HAVE_LANCE_EQUIPPED);
			return SPELL_FAILED_CUSTOM_ERROR;
		}

		void Register() override
		{
			OnCheckCast += SpellCheckCastFn(spell_ride_vehicle_toc5_SpellScript::CheckCast);
		}
	};

	class spell_ride_vehicle_toc5_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_ride_vehicle_toc5_AuraScript);

		void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			Unit* target = GetTarget();
			Unit* caster = GetCaster();

			if (target->GetMapId() != 650)
				return;

			if (caster->HasAura(SPELL_SHIELD))
				caster->RemoveAura(SPELL_SHIELD);

			if (!target->ToCreature())
				return;

			target->GetMotionMaster()->MoveTargetedHome();
			target->ToCreature()->DespawnOrUnsummon(2000);
		}

		void Register() override
		{
			AfterEffectRemove += AuraEffectRemoveFn(spell_ride_vehicle_toc5_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_CONTROL_VEHICLE, AURA_EFFECT_HANDLE_REAL);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_ride_vehicle_toc5_SpellScript();
	}

	AuraScript* GetAuraScript() const override
	{
		return new spell_ride_vehicle_toc5_AuraScript();
	}
};

// 67868
class spell_trampled_toc5 : public SpellScriptLoader
{
    public:
        spell_trampled_toc5() : SpellScriptLoader("spell_trampled_toc5") { }

        class spell_trampled_toc5_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_trampled_toc5_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targetList)
            {
				_targets.clear();
                for (std::list<WorldObject*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                {
					if (Unit* unit = (*itr)->ToUnit())
					{
						if (!GetCaster()->IsInCombat())
							continue;

						if (unit->HasAuraType(SPELL_AURA_CONTROL_VEHICLE))
							continue;

						if (unit->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED))
							continue;

						if (unit->HasAura(SPELL_TRAMPLED))
							continue;

						_targets.push_back(unit);
					}
                }
				targetList.clear();
				targetList = _targets;
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_trampled_toc5_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
			
		private:
			std::list<WorldObject*> _targets;
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_trampled_toc5_SpellScript();
        }
};

void AddSC_boss_grand_champions()
{
	new generic_vehicle_toc5();
	new champion_toc5();
    new boss_warrior_toc5();
    new boss_mage_toc5();
    new boss_shaman_toc5();
    new boss_hunter_toc5();
    new boss_rouge_toc5();
	new spell_ride_vehicle_toc5();
	new spell_trampled_toc5();
}