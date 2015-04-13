#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "trial_of_the_champion.h"
#include "Vehicle.h"
#include "Player.h"
#include "CreatureTextMgr.h"

Position const SpawnPosition[3] =
{
	{ 746.822f, 689.569f, 412.363f, 4.761f }, // Center for doors
	{ 755.877f, 689.12f, 412.368f, 4.761f  },
	{ 738.f, 689.377f, 412.366f, 4.761f }
};

class npc_announcer_toc5 : public CreatureScript
{
public:
    npc_announcer_toc5() : CreatureScript("npc_announcer_toc5") { }

    struct npc_announcer_toc5AI : public ScriptedAI
    {
		npc_announcer_toc5AI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();

            uiSummonTimes = 0;
            uiLesserChampions = 0;

            uiFirstBoss = 0;
            uiSecondBoss = 0;
            uiThirdBoss = 0;
			
			moveId = me->GetEntry() == NPC_JAEREN ? 1 : 0;

            uiArgentChampion = 0;

            uiPhase = 0;
            uiTimer = 0;
			uiCloseDoorTimer = 0;

			ostentation = false;

            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            SetGrandChampionsForEncounter();
            SetArgentChampion();
        }

        uint8 uiSummonTimes;
        uint8 uiLesserChampions;

        uint32 uiArgentChampion;

        uint32 uiFirstBoss;
        uint32 uiSecondBoss;
        uint32 uiThirdBoss;
		
		uint32 moveId;

		bool ostentation;

        uint32 uiPhase;
        uint32 uiTimer;
		uint32 uiCloseDoorTimer;

        ObjectGuid uiVehicle1GUID;
        ObjectGuid uiVehicle2GUID;
        ObjectGuid uiVehicle3GUID;

        GuidList Champion1List;
        GuidList Champion2List;
        GuidList Champion3List;

		InstanceScript* instance;

		Creature* GetCreature(uint32 data)
		{
			if (!instance)
				return NULL;

			return ObjectAccessor::GetCreature(*me, instance->GetGuidData(data));
		}
		
		void HandleGameObject(uint32 data, bool state)
		{
			if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetGuidData(data)))
				instance->HandleGameObject(go->GetGUID(), state);
		}

		void DoAction(int32 action)
		{
			switch(action)
			{
			case ACTION_FAST:
				ostentation = true;
				me->GetMotionMaster()->MovePoint(1, 735.81f, 661.92f, 412.39f);
				StartEncounter();
				break;
			case ACTION_GRAND_CHAMPIONS_MOVE_TO_GATE:
				NextStep(4000, false, 14);
				break;
			case ACTION_GRAND_CHAMPIONS_MOVE:
				NextStep(12000, false, 15);
				break;
			case ACTION_ARGENT_CHAMPION_DONE:
				NextStep(7000, false, 21);
				break;
			case ACTION_BLACK_KNIGHT_DEAD:
				NextStep(7000, false, 28);
				break;
			case ACTION_DESPAWN_CHAMPIONS:
				for (GuidList::const_iterator itr = Champion1List.begin(); itr != Champion1List.end(); ++itr)
				if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
					summon->DespawnOrUnsummon();

				for (GuidList::const_iterator itr = Champion2List.begin(); itr != Champion2List.end(); ++itr)
				if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
					summon->DespawnOrUnsummon();

				for (GuidList::const_iterator itr = Champion3List.begin(); itr != Champion3List.end(); ++itr)
				if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
					summon->DespawnOrUnsummon();

				Champion1List.clear();
				Champion2List.clear();
				Champion3List.clear();
				uiVehicle1GUID.Clear();
				uiVehicle2GUID.Clear();
				uiVehicle3GUID.Clear();
				uiSummonTimes = 0;
				uiLesserChampions = 0;
				ostentation = false;
				break;
			}
		}

        void NextStep(uint32 uiTimerStep, bool bNextStep = true, uint8 uiPhaseStep = 0)
        {
            uiTimer = uiTimerStep;
            if (bNextStep)
                ++uiPhase;
            else
                uiPhase = uiPhaseStep;
        }

        void SetData(uint32 uiType, uint32 uiData) override
        {
            switch (uiType)
            {
                case DATA_START:
					if (ostentation)
						NextStep(5000, false, 1);
					else
					{
						HandleGameObject(DATA_MAIN_GATE, true);
						uiCloseDoorTimer = 10000;
						NextStep(15000, false, 1);
					}
                    DoSummonGrandChampion(uiFirstBoss);
                    break;
                case DATA_IN_POSITION: // movement done.
					me->GetMotionMaster()->MovePoint(1, 735.81f, 661.92f, 412.39f);
                    HandleGameObject(DATA_MAIN_GATE, false);
                    NextStep(15000, false, 3);
                    break;
                case DATA_LESSER_CHAMPIONS_DEFEATED:
                {
                    ++uiLesserChampions;
                    GuidList TempList;
                    if (uiLesserChampions == 3 || uiLesserChampions == 6)
                    {
                        switch (uiLesserChampions)
                        {
                            case 3:
                                TempList = Champion2List;
                                break;
                            case 6:
                                TempList = Champion3List;
                                break;
                        }

                        for (GuidList::const_iterator itr = TempList.begin(); itr != TempList.end(); ++itr)
                            if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
                                AggroAllPlayers(summon);
								
                    } else if (uiLesserChampions == 9)
                        StartGrandChampionsAttack();

                    break;
                }
				case DATA_CHANGE_SPEED:
					switch (uiData)
					{
						case 1:
							for (GuidList::const_iterator itr = Champion1List.begin(); itr != Champion1List.end(); ++itr)
								if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
									summon->SetSpeed(MOVE_RUN, 0.5f);
							break;
						case 2:
							for (GuidList::const_iterator itr = Champion2List.begin(); itr != Champion2List.end(); ++itr)
								if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
									summon->SetSpeed(MOVE_RUN, 0.5f);
							break;
						case 3:
							for (GuidList::const_iterator itr = Champion3List.begin(); itr != Champion3List.end(); ++itr)
								if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
									summon->SetSpeed(MOVE_RUN, 0.5f);
							break;
					}
					break;
				case DATA_RESET_SPEED:
				{
					uint32 point = 3;
					switch (uiData)
					{
						case 1:
						case 4:
							point = 0;
							if (uiData == 4)
								point = 9;
								
							for (GuidList::const_iterator itr = Champion1List.begin(); itr != Champion1List.end(); ++itr)
								if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
									summon->AI()->SetData(uiData-1, point++);
							break;
						case 2:
						case 5:
							if (uiData == 5)
								point = 12;
								
							for (GuidList::const_iterator itr = Champion2List.begin(); itr != Champion2List.end(); ++itr)
								if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
									summon->AI()->SetData(uiData-1, point++);
							break;
						case 3:
						case 6:
							if (uiData == 6)
								point = 15;
							else point = 6;
							
							for (GuidList::const_iterator itr = Champion3List.begin(); itr != Champion3List.end(); ++itr)
								if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
									summon->AI()->SetData(uiData-1, point++);
							break;
					}
					break;
				}
            }
        }

        void StartGrandChampionsAttack()
        {
            Creature* pGrandChampion1 = ObjectAccessor::GetCreature(*me, uiVehicle1GUID);
            Creature* pGrandChampion2 = ObjectAccessor::GetCreature(*me, uiVehicle2GUID);
            Creature* pGrandChampion3 = ObjectAccessor::GetCreature(*me, uiVehicle3GUID);

            if (pGrandChampion1 && pGrandChampion2 && pGrandChampion3)
            {
                AggroAllPlayers(pGrandChampion1);
                AggroAllPlayers(pGrandChampion2);
                AggroAllPlayers(pGrandChampion3);
            }
			me->PlayDirectSound(8574);
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
			if (type == 16) // Move Knock back
			{
				me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				NextStep(3000, false, 24);
			}

            if (type != POINT_MOTION_TYPE)
                return;

			switch (pointId)
			{
			case 0:
				me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				break;
			case 1:
				me->SetOrientation(ORIENTATION);
				me->SendMovementFlagUpdate();
				break;
			case 2:
				HandleGameObject(DATA_MAIN_GATE, true);
				HandleGameObject(DATA_MAIN_GATE_DOOR, false);
				DoStartArgentChampionEncounter();
				NextStep(4000, false, 16); // Summon Boss
				break;
			}
        }

        void DoSummonGrandChampion(uint32 uiBoss)
        {
            ++uiSummonTimes;
			uint8 multiplier = moveId == 0 ? 3 : 12;
			uint32 minus = 1;
			if (uiSummonTimes == 2 && moveId == 1)
				minus = 10;
			if (uiSummonTimes == 3 && moveId == 1)
				minus = 19;
			Position spawnPos = ostentation ? VehicleMove[uiSummonTimes * multiplier - minus] : SpawnPosition[0];
            uint32 VEHICLE_TO_SUMMON1 = 0;
            uint32 VEHICLE_TO_SUMMON2 = 0;
			//uint32 spectator = 0;
			bool check = me->GetEntry() == NPC_JAEREN ? true : false;
            switch (uiBoss)
            {
                case 0:
                    VEHICLE_TO_SUMMON1 = VEHICLE_MOKRA_SKILLCRUSHER_MOUNT;
                    VEHICLE_TO_SUMMON2 = VEHICLE_ORGRIMMAR_WOLF;

					if (!ostentation)
						TalkToMap(check ? 6 : 5);
					//spectator = check ? DATA_SPECTATOR_HUMANS : DATA_SPECTATOR_ORCS;
                    break;
                case 1:
                    VEHICLE_TO_SUMMON1 = VEHICLE_ERESSEA_DAWNSINGER_MOUNT;
                    VEHICLE_TO_SUMMON2 = VEHICLE_SILVERMOON_HAWKSTRIDER;

					if (!ostentation)
						TalkToMap(check ? 5 : 3);
					//spectator = check ? DATA_SPECTATOR_GNOMES : DATA_SPECTATOR_BLOOD_ELVES;
                    break;
                case 2:
                    VEHICLE_TO_SUMMON1 = VEHICLE_RUNOK_WILDMANE_MOUNT;
                    VEHICLE_TO_SUMMON2 = VEHICLE_THUNDER_BLUFF_KODO;

					if (!ostentation)
						TalkToMap(check ? 3 : 7);
					//spectator = check ? DATA_SPECTATOR_NIGHT_ELVES : DATA_SPECTATOR_TAUREN;
                    break;
                case 3:
                    VEHICLE_TO_SUMMON1 = VEHICLE_ZUL_TORE_MOUNT;
                    VEHICLE_TO_SUMMON2 = VEHICLE_DARKSPEAR_RAPTOR;

					if (!ostentation)
						TalkToMap(check ? 4 : 4);
					//spectator = check ? DATA_SPECTATOR_DRAENEI : DATA_SPECTATOR_TROLL;
                    break;
                case 4:
                    VEHICLE_TO_SUMMON1 = VEHICLE_DEATHSTALKER_VESCERI_MOUNT;
                    VEHICLE_TO_SUMMON2 = VEHICLE_FORSAKE_WARHORSE;

					if (!ostentation)
						TalkToMap(check ? 7 : 6);
					//spectator = check ? DATA_SPECTATOR_DWARVES : DATA_SPECTATOR_FORSAKEN;
                    break;
                default:
                    return;
            }

            if (Creature* pBoss = me->SummonCreature(VEHICLE_TO_SUMMON1, spawnPos))
            {
				uint32 point = 0;
				uint32 type = 0;

                switch (uiSummonTimes)
                {
                    case 1:
                    {
                        uiVehicle1GUID = pBoss->GetGUID();
						switch (moveId)
						{
						case 0:
							point = 0;
							type = 1;
							break;
						case 1:
							point = 9;
							type = 4;
							break;
						}
						if (!ostentation)
							pBoss->AI()->SetData(point, type);
						instance->SetGuidData(DATA_GRAND_CHAMPION_VEHICLE_1, uiVehicle1GUID);
                        break;
                    }
                    case 2:
                    {
                        uiVehicle2GUID = pBoss->GetGUID();
						switch (moveId)
						{
						case 0:
							point = 3;
							type = 2;
							break;
						case 1:
							point = 12;
							type = 5;
							break;
						}
						if (!ostentation)
							pBoss->AI()->SetData(point, type);
                        instance->SetGuidData(DATA_GRAND_CHAMPION_VEHICLE_2, uiVehicle2GUID);
                        break;
                    }
                    case 3:
                    {
                        uiVehicle3GUID = pBoss->GetGUID();
						switch (moveId)
						{
						case 0:
							point = 6;
							type = 3;
							break;
						case 1:
							point = 15;
							type = 6;
							break;
						}
						if (!ostentation)
							pBoss->AI()->SetData(point, type);
                        instance->SetGuidData(DATA_GRAND_CHAMPION_VEHICLE_3, uiVehicle3GUID);
                        break;
                    }
                    default:
                        return;
                }

                for (uint8 i = 0; i < 3; ++i)
                {
                    if (Creature* pAdd = me->SummonCreature(VEHICLE_TO_SUMMON2, spawnPos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
                    {
                        switch (uiSummonTimes)
                        {
                            case 1:
                                Champion1List.push_back(pAdd->GetGUID());
                                break;
                            case 2:
                                Champion2List.push_back(pAdd->GetGUID());
                                break;
                            case 3:
                                Champion3List.push_back(pAdd->GetGUID());
                                break;
                        }

                        switch (i)
                        {
                            case 0:
								if (ostentation)
									SetData(DATA_RESET_SPEED, type);
								else
									pAdd->GetMotionMaster()->MoveFollow(pBoss, 2.0f, float(M_PI));
                                break;
                            case 1:
								if (ostentation)
									SetData(DATA_RESET_SPEED, type);
								else
									pAdd->GetMotionMaster()->MoveFollow(pBoss, 2.0f, float(M_PI) / 2);
                                break;
                            case 2:
								if (ostentation)
									SetData(DATA_RESET_SPEED, type);
								else
									pAdd->GetMotionMaster()->MoveFollow(pBoss, 2.0f, float(M_PI) / 2 + float(M_PI));
                                break;
                        }
                    }

                }
            }
        }

        void DoStartArgentChampionEncounter()
        {
			for (uint8 i = 0; i < 3; ++i)
			{
				if (Creature* trash = me->SummonCreature(NPC_ARGENT_LIGHWIELDER, SpawnPosition[2], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
					trash->AI()->SetData(i, 0);
				if (Creature* trash = me->SummonCreature(NPC_ARGENT_MONK, SpawnPosition[0], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
					trash->AI()->SetData(i, 0);
				if (Creature* trash = me->SummonCreature(NPC_PRIESTESS, SpawnPosition[1], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
					trash->AI()->SetData(i, 0);
			}
        }

        void SetGrandChampionsForEncounter()
        {
            uiFirstBoss = urand(0, 4);

            while (uiSecondBoss == uiFirstBoss || uiThirdBoss == uiFirstBoss || uiThirdBoss == uiSecondBoss)
            {
                uiSecondBoss = urand(0, 4);
                uiThirdBoss = urand(0, 4);
            }
        }

        void SetArgentChampion()
        {
           uint8 uiTempBoss = urand(0, 1);
           switch (uiTempBoss)
           {
                case 0:
                    uiArgentChampion = NPC_EADRIC;
                    break;
                case 1:
                    uiArgentChampion = NPC_PALETRESS;
                    break;
           }
        }

		void StartEncounter()
        {
			if (!instance)
				return;

            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

			if (instance->GetData(BOSS_BLACK_KNIGHT) == NOT_STARTED)
			{
				if (instance->GetData(BOSS_ARGENT_CHALLENGE) == NOT_STARTED)
                {
                    if (instance->GetData(BOSS_GRAND_CHAMPIONS) == NOT_STARTED)
					{
						if (ostentation)
							NextStep(1000, false, 7);
						else
							NextStep(1000, false, 4);
					}

                    if (instance->GetData(BOSS_GRAND_CHAMPIONS) == DONE)
                        me->GetMotionMaster()->MovePoint(2, 745.502f, 621.218f, 411.09f);

					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				}

				if ((instance->GetData(BOSS_GRAND_CHAMPIONS) == DONE &&
					instance->GetData(BOSS_ARGENT_CHALLENGE) == DONE))
					NextStep(1000, false, 22); // Start Event Black Knight
			}
		}

		void AggroAllPlayers(Creature* temp)
        {
			temp->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
			temp->SetReactState(REACT_AGGRESSIVE);
			DoZoneInCombat(temp, 1000.0f);

			if (Vehicle* vehicle = temp->GetVehicleKit())
			{
				if (Creature* temp2 = vehicle->GetPassenger(0)->ToCreature())
				{
					temp2->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
					temp2->SetReactState(REACT_AGGRESSIVE);
					DoZoneInCombat(temp2, 1000.0f);
				}
			}
        }

        void UpdateAI(uint32 uiDiff) override
        {
            ScriptedAI::UpdateAI(uiDiff);

			UpdateVictim();
			
            if (uiTimer <= uiDiff)
            {
                switch (uiPhase)
                {
                    case 1:
						if (!ostentation)
						{
							HandleGameObject(DATA_MAIN_GATE, true);
							uiCloseDoorTimer = 10000;
						}
                        DoSummonGrandChampion(uiSecondBoss);
						if (ostentation)
							NextStep(5000, true);
						else
							NextStep(15000, true);
                        break;
                    case 2:
						if (!ostentation)
						{
							HandleGameObject(DATA_MAIN_GATE, true);
							uiCloseDoorTimer = 10000;
						}
                        DoSummonGrandChampion(uiThirdBoss);
						if (ostentation)
							NextStep(5000, false, 3);
						else
							NextStep(0, false);
                        break;
                    case 3:
						HandleGameObject(DATA_MAIN_GATE_DOOR, false);
						if (GetCreature(DATA_HIGHLORD))
							GetCreature(DATA_HIGHLORD)->AI()->TalkToMap(52);

                        if (!Champion1List.empty())
                        {
							for (GuidList::const_iterator itr = Champion1List.begin(); itr != Champion1List.end(); ++itr)
								if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
									AggroAllPlayers(summon);

                            NextStep(0, false);
                        }
                        break;
					case 4:
						me->HandleEmoteCommand(2);
						NextStep(2000, true);
						break;
					case 5:
						TalkToMap(2);
						NextStep(30000, true);
						break;
					case 6:
					{
						Map::PlayerList const &playerList = me->GetMap()->GetPlayers();
						if (!playerList.isEmpty())
						{
							for (Map::PlayerList::const_iterator i = playerList.begin(); i != playerList.end(); ++i)
							{
								if (Player* player = i->GetSource())
								{
									if (player->IsGameMaster())
										continue;

									TalkToMap(9, player);
								}
							}
						}
						NextStep(30000, true);
						break;
					}
					case 7:
						if (GetCreature(DATA_HIGHLORD))
							GetCreature(DATA_HIGHLORD)->AI()->TalkToMap(50);
						if (ostentation)
							NextStep(12000, false, 12);
						else
							NextStep(12000, true);
						break;
					case 8:
						if (IsHeroic())
						{
							if (GetCreature(DATA_KING))
								GetCreature(DATA_KING)->AI()->TalkToMap(52);
						}
						else
						{
							if (GetCreature(DATA_KING))
								GetCreature(DATA_KING)->AI()->TalkToMap(50);
						}
						NextStep(5000, true);
						break;
					case 9:
						if (IsHeroic())
						{
							if (GetCreature(DATA_LADY))
								GetCreature(DATA_LADY)->Talk(35329, CHAT_MSG_MONSTER_SAY, 100.0f, NULL);
						}
						else
						{
							if (GetCreature(DATA_LADY))
								GetCreature(DATA_LADY)->Talk(35323, CHAT_MSG_MONSTER_SAY, 100.0f, NULL);
						}
						NextStep(5000, true);
						break;
					case 10:
						if (IsHeroic())
						{
							if (GetCreature(DATA_GARROSH))
								GetCreature(DATA_GARROSH)->AI()->TalkToMap(50);
						}
						else
						{
							if (GetCreature(DATA_GARROSH))
								GetCreature(DATA_GARROSH)->AI()->TalkToMap(52);
						}
						NextStep(5000, true);
						break;
					case 11:
						if (IsHeroic())
						{
							if (GetCreature(DATA_TRALL))
								GetCreature(DATA_TRALL)->AI()->TalkToMap(0);
						}
						else
						{
							if (GetCreature(DATA_TRALL))
								GetCreature(DATA_TRALL)->AI()->TalkToMap(2);
						}
						NextStep(8000, true);
						break;
					case 12:
						if (GetCreature(DATA_HIGHLORD))
							GetCreature(DATA_HIGHLORD)->AI()->TalkToMap(51);
						if (ostentation)
							NextStep(4000, true);
						else
							NextStep(15000, true);
						break;
					case 13:
						SetData(DATA_START, 0);
						break;
					case 14: // Grand Champions Move To Gate
						if (GetCreature(DATA_GRAND_CHAMPION_1))
							GetCreature(DATA_GRAND_CHAMPION_1)->AI()->DoAction(0);
						if (GetCreature(DATA_GRAND_CHAMPION_2))
							GetCreature(DATA_GRAND_CHAMPION_2)->AI()->DoAction(0);
						if (GetCreature(DATA_GRAND_CHAMPION_3))
							GetCreature(DATA_GRAND_CHAMPION_3)->AI()->DoAction(0);
						NextStep(0, false);
						break;
					case 15: // Grand Champions Move
						if (GetCreature(DATA_GRAND_CHAMPION_1))
							GetCreature(DATA_GRAND_CHAMPION_1)->GetMotionMaster()->MovePoint(1, 739.678f, 662.541f, 412.393f);
						if (GetCreature(DATA_GRAND_CHAMPION_2))
							GetCreature(DATA_GRAND_CHAMPION_2)->GetMotionMaster()->MovePoint(1, 746.71f, 661.02f, 411.69f);
						if (GetCreature(DATA_GRAND_CHAMPION_3))
							GetCreature(DATA_GRAND_CHAMPION_3)->GetMotionMaster()->MovePoint(1, 754.34f, 660.70f, 412.39f);
						NextStep(0, false);
						break;
					case 16:
						if (Unit* pBoss = me->SummonCreature(uiArgentChampion, SpawnPosition[0]))
							pBoss->SetSpeed(MOVE_RUN, 0.4f);
						NextStep(1000, false, 17);
						break;
					case 17:
						switch (uiArgentChampion)
						{
							case NPC_EADRIC:
								TalkToMap(0);
								break;
							case NPC_PALETRESS:
								TalkToMap(1);
								break;
						}
						NextStep(3000, false, 18);
						break;
					case 18:
						if (GetCreature(DATA_ARGENT_CHAMPION))
							GetCreature(DATA_ARGENT_CHAMPION)->GetMotionMaster()->MovePoint(3, 746.529f, 659.775f, 411.69f);
						NextStep(7000, false, 19);
						break;
					case 19:
						me->GetMotionMaster()->MovePoint(1, 734.396f, 673.536f, 412.371f);
						NextStep(20000, false, 20);
						break;
					case 20:
						if (GetCreature(DATA_HIGHLORD))
							GetCreature(DATA_HIGHLORD)->AI()->TalkToMap(54);
						NextStep(0, false);
						break;
					case 21:
						if (GetCreature(DATA_ARGENT_CHAMPION))
							GetCreature(DATA_ARGENT_CHAMPION)->GetMotionMaster()->MovePoint(1, 746.82f, 665.208f, 411.746f);
						NextStep(0, false);
						break;
					case 22:
						if (GetCreature(DATA_HIGHLORD))
							GetCreature(DATA_HIGHLORD)->AI()->TalkToMap(55);
						me->GetMotionMaster()->MovePoint(3, 744.698f, 627.782f, 411.172f);
						NextStep(3000, false, 23);
						break;
					case 23:
						if (Creature* pBlackKnight = me->SummonCreature(VEHICLE_BLACK_KNIGHT, 781.513f, 657.99f, 466.821f, 3.04f))
						{
							pBlackKnight->SetReactState(REACT_DEFENSIVE);
							me->SetTarget(pBlackKnight->GetGUID());
						}
						TalkToMap(8);
						NextStep(0, false);
						break;
					case 24:
						if (GetCreature(DATA_BLACK_KNIGHT))
							GetCreature(DATA_BLACK_KNIGHT)->AI()->TalkToMap(1);
						me->SetFacingTo(ORIENTATION);
						HandleGameObject(DATA_MAIN_GATE_DOOR, false);
						NextStep(1000, false, 25);
						break;
					case 25:
						if (GetCreature(DATA_BLACK_KNIGHT))
							GetCreature(DATA_BLACK_KNIGHT)->GetMotionMaster()->MovePoint(0, 746.984f, 623.306f, 411.417f);
						NextStep(10000, false, 26);
						break;
					case 26:
						if (GetCreature(DATA_BLACK_KNIGHT))
							GetCreature(DATA_BLACK_KNIGHT)->AI()->Talk(2);
						NextStep(4000, false, 27);
						break;
					case 27:
						if (GetCreature(DATA_BLACK_KNIGHT))
							GetCreature(DATA_BLACK_KNIGHT)->AI()->SetData(DATA_START, 1);
						switch (me->GetEntry())
						{
							case NPC_JAEREN:
								if (GetCreature(DATA_GARROSH))
									GetCreature(DATA_GARROSH)->AI()->TalkToMap(51);
								break;
							case NPC_ARELAS:
								if (GetCreature(DATA_KING))
									GetCreature(DATA_KING)->AI()->TalkToMap(51);
								break;
						}
						NextStep(0, false);
						break;
					case 28:
						if (GetCreature(DATA_HIGHLORD))
							GetCreature(DATA_HIGHLORD)->AI()->TalkToMap(57);
						NextStep(7000, false, 29);
						break;
					case 29: // End
						if (GetCreature(DATA_HIGHLORD))
							GetCreature(DATA_HIGHLORD)->AI()->TalkToMap(58);
						NextStep(0, false);
						break;
                }
            } 
			else
				uiTimer -= uiDiff;
				
			if (uiCloseDoorTimer != 0)
			{
				if (uiCloseDoorTimer <= uiDiff)
				{
					HandleGameObject(DATA_MAIN_GATE, false);
					uiCloseDoorTimer = 0;
				}
				else
					uiCloseDoorTimer -= uiDiff;
			}

			if (!UpdateVictim())
				return;
        }

        void JustSummoned(Creature* summon) override
        {
            if (instance->GetData(BOSS_GRAND_CHAMPIONS) == NOT_STARTED)
            {
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                summon->SetReactState(REACT_PASSIVE);
            }
        }

        void SummonedCreatureDespawn(Creature* summon) override
        {
            switch (summon->GetEntry())
            {
                case VEHICLE_DARNASSIA_NIGHTSABER:
                case VEHICLE_EXODAR_ELEKK:
                case VEHICLE_STORMWIND_STEED:
                case VEHICLE_GNOMEREGAN_MECHANOSTRIDER:
                case VEHICLE_IRONFORGE_RAM:
                case VEHICLE_FORSAKE_WARHORSE:
                case VEHICLE_THUNDER_BLUFF_KODO:
                case VEHICLE_ORGRIMMAR_WOLF:
                case VEHICLE_SILVERMOON_HAWKSTRIDER:
                case VEHICLE_DARKSPEAR_RAPTOR:
                    SetData(DATA_LESSER_CHAMPIONS_DEFEATED, 0);
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_announcer_toc5AI>(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        InstanceScript* instance = creature->GetInstanceScript();

        if (instance && (instance->GetData(BOSS_GRAND_CHAMPIONS) == DONE &&
            instance->GetData(BOSS_BLACK_KNIGHT) == DONE &&
            instance->GetData(BOSS_ARGENT_CHALLENGE) == DONE))
            return false;

        if (instance &&
			instance->GetData(BOSS_GRAND_CHAMPIONS) == NOT_STARTED &&
            instance->GetData(BOSS_ARGENT_CHALLENGE) == NOT_STARTED &&
            instance->GetData(BOSS_BLACK_KNIGHT) == NOT_STARTED)
		{
			player->ADD_GOSSIP_ITEM_DB(10614, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1); // Start challenge
			player->ADD_GOSSIP_ITEM_DB(10614, 3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2); // Start challenge. However, I'd like to skip the pageantry. Not work!
		}
		else if (instance && instance->GetData(BOSS_ARGENT_CHALLENGE) == NOT_STARTED)
			player->ADD_GOSSIP_ITEM_DB(10614, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1); // Next challenge
		else if (instance)
			player->ADD_GOSSIP_ITEM_DB(10614, 2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1); // I am ready

		player->SEND_GOSSIP_MENU(player->GetGossipTextId(10614, creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();

		InstanceScript* instance = creature->GetInstanceScript();

		if (instance && instance->GetData(BOSS_GRAND_CHAMPIONS) == NOT_STARTED)
		{
			if (!player->IsGameMaster())
			{
				if (!player->GetVehicle())
				{
					OnGossipHello(player, creature);
					creature->Talk(35861, CHAT_MSG_MONSTER_SAY, 100.0f, player);
					return false;
				}
			}
		}

        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            player->CLOSE_GOSSIP_MENU();
            ENSURE_AI(npc_announcer_toc5::npc_announcer_toc5AI, creature->AI())->StartEncounter();
        }

		if (action == GOSSIP_ACTION_INFO_DEF + 2)
		{
			player->CLOSE_GOSSIP_MENU();
			ENSURE_AI(npc_announcer_toc5::npc_announcer_toc5AI, creature->AI())->DoAction(ACTION_FAST);
		}

        return true;
    }
};

void AddSC_trial_of_the_champion()
{
    new npc_announcer_toc5();
}
