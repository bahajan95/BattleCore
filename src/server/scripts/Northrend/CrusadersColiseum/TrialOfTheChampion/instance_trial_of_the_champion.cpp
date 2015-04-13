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
SDName: Instance Trial of the Champion
SDComment:
SDCategory: Trial Of the Champion
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "InstanceScript.h"
#include "trial_of_the_champion.h"
#include "Player.h"
#include "Vehicle.h"

#define MAX_ENCOUNTER  3

class instance_trial_of_the_champion : public InstanceMapScript
{
public:
    instance_trial_of_the_champion() : InstanceMapScript("instance_trial_of_the_champion", 650) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_trial_of_the_champion_InstanceMapScript(map);
    }

    struct instance_trial_of_the_champion_InstanceMapScript : public InstanceScript
    {
        instance_trial_of_the_champion_InstanceMapScript(Map* map) : InstanceScript(map)
        {
            SetHeaders(DataHeader);
            uiMovementDone = 0;
            uiGrandChampionsDeaths = 0;
			uiGrandChampionsPhaseDone = 0;
			uiGrandChampionsMovementDone = 0;
            uiArgentSoldierDeaths = 0;
			uiGrandChampionCount = 0;
			uiArgentChampionEntry = 0;

            memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
        }

        uint32 m_auiEncounter[MAX_ENCOUNTER];

        uint16 uiMovementDone;
        uint16 uiGrandChampionsDeaths;
		uint16 uiGrandChampionsPhaseDone;
		uint16 uiGrandChampionsMovementDone;
        uint8 uiArgentSoldierDeaths;
		uint8 uiGrandChampionCount;
		uint32 uiArgentChampionEntry;

		ObjectGuid uiBlackKnightGUID;
        ObjectGuid uiAnnouncerGUID;
        ObjectGuid uiMainGateGUID;
		ObjectGuid uiMainGateDoorGUID;
        ObjectGuid uiGrandChampionVehicleGUID[3];
        ObjectGuid uiGrandChampionGUID[3];
        ObjectGuid uiChampionLootGUID;
        ObjectGuid uiArgentChampionGUID;
		
		// 
		ObjectGuid uiTrallGUID;
		ObjectGuid uiGarroshGUID;
		ObjectGuid uiKingGUID;
		ObjectGuid uiLadyGUID;
		ObjectGuid uiHighLordGUID;
		
		// Spectators
		ObjectGuid uiSpecHordeGUID;
		ObjectGuid uiSpecAllianceGUID;
		ObjectGuid uiSpecBloodElvesGUID;
		ObjectGuid uiSpecTaurenGUID;
		ObjectGuid uiSpecTrollGUID;
		ObjectGuid uiSpecOrcsGUID;
		ObjectGuid uiSpecForsakenGUID;
		ObjectGuid uiSpecDwarvesGUID;
		ObjectGuid uiSpecGnomesGUID;
		ObjectGuid uiSpecHumansGUID;
		ObjectGuid uiSpecNightElvesGUID;
		ObjectGuid uiSpecDraeneiGUID;

        GuidList VehicleList;
		GuidList VehicleBossList;

        std::string str_data;

        bool IsEncounterInProgress() const override
        {
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                if (m_auiEncounter[i] == IN_PROGRESS)
                    return true;
            }

            return false;
        }

        void OnCreatureCreate(Creature* creature) override
        {
            Map::PlayerList const &players = instance->GetPlayers();
            uint32 TeamInInstance = 0;

            if (!players.isEmpty())
            {
                if (Player* player = players.begin()->GetSource())
                    TeamInInstance = player->GetTeam();
            }

            switch (creature->GetEntry())
            {
                // Champions
                case VEHICLE_MOKRA_SKILLCRUSHER_MOUNT:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(VEHICLE_MARSHAL_JACOB_ALERIUS_MOUNT);
						creature->LoadCreaturesAddon();
					}
                    break;
                case VEHICLE_ERESSEA_DAWNSINGER_MOUNT:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(VEHICLE_AMBROSE_BOLTSPARK_MOUNT);
						creature->LoadCreaturesAddon();
					}
                    break;
                case VEHICLE_RUNOK_WILDMANE_MOUNT:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(VEHICLE_COLOSOS_MOUNT);
						creature->LoadCreaturesAddon();
					}
                    break;
                case VEHICLE_ZUL_TORE_MOUNT:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(VEHICLE_EVENSONG_MOUNT);
						creature->LoadCreaturesAddon();
					}
                    break;
                case VEHICLE_DEATHSTALKER_VESCERI_MOUNT:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(VEHICLE_LANA_STOUTHAMMER_MOUNT);
						creature->LoadCreaturesAddon();
					}
                    break;
				case NPC_MOKRA:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(NPC_JACOB);
						creature->LoadCreaturesAddon();
						creature->AddAura(62727, creature);
					}
					else
						creature->AddAura(63444, creature);
					uiGrandChampionGUID[uiGrandChampionCount++] = creature->GetGUID();
					break;
				case NPC_ERESSEA:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(NPC_AMBROSE);
						creature->LoadCreaturesAddon();
						creature->AddAura(63442, creature);
					}
					else
						creature->AddAura(63438, creature);
					uiGrandChampionGUID[uiGrandChampionCount++] = creature->GetGUID();
					break;
				case NPC_RUNOK:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(NPC_COLOSOS);
						creature->LoadCreaturesAddon();
						creature->AddAura(63439, creature);
					}
					else
						creature->AddAura(63445, creature);
					uiGrandChampionGUID[uiGrandChampionCount++] = creature->GetGUID();
					break;
				case NPC_ZULTORE:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(NPC_JAELYNE);
						creature->LoadCreaturesAddon();
						creature->AddAura(63443, creature);
					}
					else
						creature->AddAura(63446, creature);
					uiGrandChampionGUID[uiGrandChampionCount++] = creature->GetGUID();
					break;
				case NPC_VISCERI:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(NPC_LANA);
						creature->LoadCreaturesAddon();
						creature->AddAura(63440, creature);
					}
					else
						creature->AddAura(63441, creature);
					uiGrandChampionGUID[uiGrandChampionCount++] = creature->GetGUID();
					break;
    			case VEHICLE_ORGRIMMAR_WOLF:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(VEHICLE_STORMWIND_STEED);
						creature->LoadCreaturesAddon();
					}
                    break;
    			case VEHICLE_SILVERMOON_HAWKSTRIDER:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(VEHICLE_GNOMEREGAN_MECHANOSTRIDER);
						creature->LoadCreaturesAddon();
					}
                    break;
    			case VEHICLE_THUNDER_BLUFF_KODO:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(VEHICLE_EXODAR_ELEKK);
						creature->LoadCreaturesAddon();
					}
                    break;
    			case VEHICLE_DARKSPEAR_RAPTOR:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(VEHICLE_DARNASSIA_NIGHTSABER);
						creature->LoadCreaturesAddon();
					}
                    break;	
    			case VEHICLE_FORSAKE_WARHORSE:
					if (TeamInInstance == HORDE)
					{
						creature->UpdateEntry(VEHICLE_IRONFORGE_RAM);
						creature->LoadCreaturesAddon();
					}
                    break;	
                // Coliseum Announcer
                case NPC_JAEREN:
					uiAnnouncerGUID = creature->GetGUID();
                    if (TeamInInstance == ALLIANCE)
                        creature->UpdateEntry(NPC_ARELAS);
					if (m_auiEncounter[BOSS_GRAND_CHAMPIONS] == DONE
						&& m_auiEncounter[BOSS_ARGENT_CHALLENGE] == NOT_STARTED
						&& m_auiEncounter[BOSS_BLACK_KNIGHT] == NOT_STARTED)
						creature->SetPosition(741.884f, 630.238f, 411.172f, ORIENTATION);
					if (m_auiEncounter[BOSS_ARGENT_CHALLENGE] == DONE
						&& m_auiEncounter[BOSS_BLACK_KNIGHT] == NOT_STARTED)
						creature->SetPosition(743.611f, 621.98f, 411.417f, ORIENTATION);
					if (m_auiEncounter[BOSS_BLACK_KNIGHT] == DONE)
					{
						creature->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
						creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					}
                    break;			
                case VEHICLE_ARGENT_WARHORSE:
					if (!creature->IsAlive())
						creature->Respawn();
					if (m_auiEncounter[BOSS_GRAND_CHAMPIONS] == DONE)
						creature->SetVisible(false);
					VehicleList.push_back(creature->GetGUID());
					if (TeamInInstance == ALLIANCE)
						creature->setFaction(35);
					else
					{
						creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
						VehicleBossList.push_back(creature->GetGUID());
					}
					break;
                case VEHICLE_ARGENT_BATTLEWORG:
					if (!creature->IsAlive())
						creature->Respawn();
					if (m_auiEncounter[BOSS_GRAND_CHAMPIONS] == DONE)
						creature->SetVisible(false);
                    VehicleList.push_back(creature->GetGUID());
					if (TeamInInstance == HORDE)
						creature->setFaction(35);
					else
					{
						creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
						VehicleBossList.push_back(creature->GetGUID());
					}
					break;
                case NPC_EADRIC:
                case NPC_PALETRESS:
					uiArgentChampionEntry = creature->GetEntry();
                    uiArgentChampionGUID = creature->GetGUID();
                    break;
                case NPC_BLACK_KNIGHT:
                    uiBlackKnightGUID = creature->GetGUID();
                    break;
				case NPC_TRALL:
					uiTrallGUID = creature->GetGUID();
					break;
				case NPC_GARROSH:
					uiGarroshGUID = creature->GetGUID();
					break;
				case NPC_KING:
					uiKingGUID = creature->GetGUID();
					break;
				case NPC_LADY:
					uiLadyGUID = creature->GetGUID();
					break;
				case NPC_HIGHLORD:
					uiHighLordGUID = creature->GetGUID();
					break;
				// Spectators
				case SPECTATOR_BLOOD_ELVES:
					uiSpecBloodElvesGUID = creature->GetGUID();
					break;
				case SPECTATOR_TAUREN:
					uiSpecTaurenGUID = creature->GetGUID();
					break;
				case SPECTATOR_TROLL:
					uiSpecTrollGUID = creature->GetGUID();
					break;
				case SPECTATOR_ORCS:
					uiSpecOrcsGUID = creature->GetGUID();
					break;
				case SPECTATOR_FORSAKEN:
					uiSpecForsakenGUID = creature->GetGUID();
					break;
				case SPECTATOR_DWARVES:
					uiSpecDwarvesGUID = creature->GetGUID();
					break;
				case SPECTATOR_GNOMES:
					uiSpecGnomesGUID = creature->GetGUID();
					break;
				case SPECTATOR_HUMANS:
					uiSpecHumansGUID = creature->GetGUID();
					break;
				case SPECTATOR_NIGHT_ELVES:
					uiSpecNightElvesGUID = creature->GetGUID();
					break;
				case SPECTATOR_DRAENEI:
					uiSpecDraeneiGUID = creature->GetGUID();
					break;
            }
        }

        void OnGameObjectCreate(GameObject* go) override
        {
            switch (go->GetEntry())
            {
                case GO_MAIN_GATE:
                    uiMainGateGUID = go->GetGUID();
                    break;
				case GO_MAIN_GATE_DOOR:
                    uiMainGateDoorGUID = go->GetGUID();
                    break;
                case GO_CHAMPIONS_LOOT:
                case GO_CHAMPIONS_LOOT_H:
                    uiChampionLootGUID = go->GetGUID();
                    break;
            }
        }

        void SetData(uint32 uiType, uint32 uiData) override
        {
            switch (uiType)
            {
				case BOSS_GRAND_CHAMPIONS:
					if (uiData == DONE)
					{
						++uiGrandChampionsDeaths;
						if (uiGrandChampionsDeaths == 3)
						{
							m_auiEncounter[0] = uiData;
							HandleGameObject(uiMainGateDoorGUID, true);
							if (Creature* highLord = instance->GetCreature(uiHighLordGUID))
								highLord->AI()->Talk(53);
									
							if (Creature* pAnnouncer = instance->GetCreature(uiAnnouncerGUID))
							{
								pAnnouncer->GetMotionMaster()->MovePoint(0, 741.884f, 630.238f, 411.172f);
								pAnnouncer->AI()->DoAction(ACTION_GRAND_CHAMPIONS_MOVE_TO_GATE);

								pAnnouncer->SummonGameObject(instance->IsHeroic() ? GO_CHAMPIONS_LOOT_H : GO_CHAMPIONS_LOOT, 744.721f, 618.307f, 411.089f, 1.535f, 0, 0, 0, 0, 90000);
							}
						}
					}
					if (uiData == FAIL)
					{
						Map::PlayerList const &players = instance->GetPlayers();
						uint32 TeamInInstance = 0;

						if (!players.isEmpty())
						{
							if (Player* player = players.begin()->GetSource())
								TeamInInstance = player->GetTeam();
						}

						HandleGameObject(uiMainGateDoorGUID, true);
						if (Creature* pAnnouncer = instance->GetCreature(uiAnnouncerGUID))
						{
							pAnnouncer->NearTeleportTo(pAnnouncer->GetHomePosition());
							pAnnouncer->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
							pAnnouncer->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
							pAnnouncer->AI()->DoAction(ACTION_DESPAWN_CHAMPIONS);
							for (uint8 i = 0; i < 3; ++i)
							{
								if (Creature* boss = instance->GetCreature(uiGrandChampionGUID[i]))
								{
									boss->ExitVehicle();
									boss->DespawnOrUnsummon();
								}
								uiGrandChampionGUID[i].Clear();
							}
							for (uint8 i = 0; i < 3; ++i)
							{
								if (Creature* vehicle = instance->GetCreature(uiGrandChampionVehicleGUID[i]))
									vehicle->DespawnOrUnsummon();
								uiGrandChampionVehicleGUID[i].Clear();
							}
							for (GuidList::const_iterator itr = VehicleList.begin(); itr != VehicleList.end(); ++itr)
								if (Creature* vehicle = instance->GetCreature(*itr))
								{
									vehicle->setDeathState(JUST_RESPAWNED);
									vehicle->SetVisible(true);
								}

							uiMovementDone = 0;
							uiGrandChampionCount = 0;
							uiGrandChampionsDeaths = 0;
							uiGrandChampionsPhaseDone = 0;
							uiGrandChampionsMovementDone = 0;
						}
					}
					break;
				case BOSS_ARGENT_CHALLENGE:
					if (uiData == DONE || uiData == FAIL)
					{
						if (uiData == FAIL)
							uiData = NOT_STARTED;

						if (Creature* pAnnouncer = instance->GetCreature(uiAnnouncerGUID))
						{
							pAnnouncer->GetMotionMaster()->MovePoint(0, 743.611f, 621.98f, 411.417f);
							if (uiData == DONE)
								pAnnouncer->AI()->DoAction(ACTION_ARGENT_CHAMPION_DONE);

							HandleGameObject(uiMainGateDoorGUID, true);
							if (uiData == DONE)
							{
								switch (uiArgentChampionEntry)
								{
								case NPC_EADRIC:
									DoCastSpellOnPlayers(68575);
									pAnnouncer->SummonGameObject(instance->IsHeroic() ? GO_EADRIC_LOOT_H : GO_EADRIC_LOOT, 748.76f, 618.309f, 411.089f, 1.588f, 0, 0, 0, 0, 90000);
									break;
								case NPC_PALETRESS:
									DoCastSpellOnPlayers(68574);
									pAnnouncer->SummonGameObject(instance->IsHeroic() ? GO_PALETRESS_LOOT_H : GO_PALETRESS_LOOT, 748.76f, 618.309f, 411.089f, 1.588f, 0, 0, 0, 0, 90000);
									break;
								}
							}
						}
					}
					m_auiEncounter[1] = uiData;
					break;
				case BOSS_BLACK_KNIGHT:
					m_auiEncounter[2] = uiData;
					if (Creature* announcer = instance->GetCreature(uiAnnouncerGUID))
						announcer->AI()->DoAction(ACTION_BLACK_KNIGHT_DEAD);
					HandleGameObject(uiMainGateDoorGUID, true);
					break;
                case DATA_MOVEMENT_DONE:
                    uiMovementDone = uiData;
                    if (uiMovementDone == 3)
                    {
                        if (Creature* pAnnouncer =  instance->GetCreature(uiAnnouncerGUID))
                            pAnnouncer->AI()->SetData(DATA_IN_POSITION, 0);
                    }
                    break;
				case DATA_GRAND_CHAMPIONS_PHASE:
					if (uiData == DONE)
					{
						++uiGrandChampionsPhaseDone;
						if (uiGrandChampionsPhaseDone == 3)
						{
							Map::PlayerList const &playerList = instance->GetPlayers();
							
							if (Creature* pAnnouncer = instance->GetCreature(uiAnnouncerGUID))
								pAnnouncer->AI()->DoAction(ACTION_GRAND_CHAMPIONS_MOVE_TO_GATE);
								
							for (GuidList::const_iterator itr = VehicleList.begin(); itr != VehicleList.end(); ++itr)
								if (Creature* summon = instance->GetCreature(*itr))
									summon->SetVisible(false);

							if (playerList.isEmpty())
								break;

							for (Map::PlayerList::const_iterator i = playerList.begin(); i != playerList.end(); ++i)
								if (Player* player = i->GetSource())
									player->ExitVehicle();
						}
					}
					else
						uiGrandChampionsPhaseDone--;
					break;
				case DATA_GRAND_CHAMPIONS_MOVEMENT:
					if (uiData == DONE)
					{
						++uiGrandChampionsMovementDone;
						if (uiGrandChampionsMovementDone == 3)
						{
							if (Creature* pAnnouncer = instance->GetCreature(uiAnnouncerGUID))
								pAnnouncer->AI()->DoAction(ACTION_GRAND_CHAMPIONS_MOVE);
							DoCastSpellOnPlayers(68572);
						}
					}
					break;
                case DATA_ARGENT_SOLDIER_DEFEATED:
                    uiArgentSoldierDeaths = uiData;
                    if (uiArgentSoldierDeaths == 9)
                    {
                        if (Creature* pBoss =  instance->GetCreature(uiArgentChampionGUID))
                        {
							pBoss->setFaction(14);
                            pBoss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
							pBoss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            pBoss->SetReactState(REACT_AGGRESSIVE);
							pBoss->AI()->DoZoneInCombat(pBoss, 1000.0f);
                        }
                    }
                    break;
            }

			if (uiType == BOSS_GRAND_CHAMPIONS
				|| uiType == BOSS_ARGENT_CHALLENGE
				|| uiType == BOSS_BLACK_KNIGHT)
                SaveToDB();
        }

        uint32 GetData(uint32 uiData) const override
        {
            switch (uiData)
            {
                case BOSS_GRAND_CHAMPIONS:  return m_auiEncounter[0];
                case BOSS_ARGENT_CHALLENGE: return m_auiEncounter[1];
                case BOSS_BLACK_KNIGHT: return m_auiEncounter[2];

                case DATA_MOVEMENT_DONE: return uiMovementDone;
                case DATA_ARGENT_SOLDIER_DEFEATED: return uiArgentSoldierDeaths;
            }

            return 0;
        }

        ObjectGuid GetGuidData(uint32 uiData) const override
        {
            switch (uiData)
            {
                case DATA_ANNOUNCER: return uiAnnouncerGUID;
                case DATA_MAIN_GATE: return uiMainGateGUID;
				case DATA_MAIN_GATE_DOOR: return uiMainGateDoorGUID;
				
				case DATA_TRALL: return uiTrallGUID;
				case DATA_GARROSH: return uiGarroshGUID;
				case DATA_KING: return uiKingGUID;
				case DATA_LADY: return uiLadyGUID;
				case DATA_HIGHLORD: return uiHighLordGUID;

				case DATA_GRAND_CHAMPION_VEHICLE:
				{
					GuidList vehicleAliveList;
					if (uiGrandChampionsPhaseDone == 3)
						return ObjectGuid::Empty;
					for (GuidList::const_iterator itr = VehicleBossList.begin(); itr != VehicleBossList.end(); ++itr)
					{
						if (Creature* vehicle = instance->GetCreature(*itr))
						if (vehicle->IsAlive())
							vehicleAliveList.push_back(vehicle->GetGUID());
					}
					if (vehicleAliveList.empty())
						return ObjectGuid::Empty;
					Trinity::Containers::RandomResizeList(vehicleAliveList, 1);
					GuidList::const_iterator itr = vehicleAliveList.begin();
					return *itr;
				}
				
				case DATA_GRAND_CHAMPION_VEHICLE_1: return uiGrandChampionVehicleGUID[0];
                case DATA_GRAND_CHAMPION_VEHICLE_2: return uiGrandChampionVehicleGUID[1];
                case DATA_GRAND_CHAMPION_VEHICLE_3: return uiGrandChampionVehicleGUID[2];
				
                case DATA_GRAND_CHAMPION_1: return uiGrandChampionGUID[0];
                case DATA_GRAND_CHAMPION_2: return uiGrandChampionGUID[1];
                case DATA_GRAND_CHAMPION_3: return uiGrandChampionGUID[2];
				
				case DATA_ARGENT_CHAMPION: return uiArgentChampionGUID;
				
				case DATA_BLACK_KNIGHT: return uiBlackKnightGUID;
				
				// Get guid spectators
                case DATA_SPECTATOR_BLOOD_ELVES: return uiSpecBloodElvesGUID;
                case DATA_SPECTATOR_TAUREN: return uiSpecTaurenGUID;
                case DATA_SPECTATOR_TROLL: return uiSpecTrollGUID;
                case DATA_SPECTATOR_ORCS: return uiSpecOrcsGUID;
                case DATA_SPECTATOR_FORSAKEN: return uiSpecForsakenGUID;
                case DATA_SPECTATOR_DWARVES: return uiSpecDwarvesGUID;
                case DATA_SPECTATOR_GNOMES: return uiSpecGnomesGUID;
                case DATA_SPECTATOR_HUMANS: return uiSpecHumansGUID;
                case DATA_SPECTATOR_NIGHT_ELVES: return uiSpecNightElvesGUID;
                case DATA_SPECTATOR_DRAENEI: return uiSpecDraeneiGUID;
            }

            return ObjectGuid::Empty;
        }

        void SetGuidData(uint32 uiType, ObjectGuid uiData) override
        {
            switch (uiType)
            {
                case DATA_GRAND_CHAMPION_1:
					uiGrandChampionGUID[0] = uiData;
                    break;
                case DATA_GRAND_CHAMPION_2:
					uiGrandChampionGUID[1] = uiData;
                    break;
                case DATA_GRAND_CHAMPION_3:
					uiGrandChampionGUID[2] = uiData;
                    break;
				case DATA_GRAND_CHAMPION_VEHICLE_1:
					uiGrandChampionVehicleGUID[0] = uiData;
                    break;
                case DATA_GRAND_CHAMPION_VEHICLE_2:
					uiGrandChampionVehicleGUID[1] = uiData;
                    break;
                case DATA_GRAND_CHAMPION_VEHICLE_3:
					uiGrandChampionVehicleGUID[2] = uiData;
                    break;
				case DATA_GRAND_CHAMPION_VEHICLE_R:
					VehicleBossList.remove(uiData);
					break;
            }
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;

			saveStream << "T C " << m_auiEncounter[0]
				<< ' ' << m_auiEncounter[1]
				<< ' ' << m_auiEncounter[2];

            str_data = saveStream.str();

            OUT_SAVE_INST_DATA_COMPLETE;
            return str_data;
        }

        void Load(const char* in) override
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char dataHead1, dataHead2;
			uint16 data[MAX_ENCOUNTER];

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> data[0] >> data[1] >> data[2];

            if (dataHead1 == 'T' && dataHead2 == 'C')
            {
				for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
					m_auiEncounter[i] = data[i];

            } else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };

};

void AddSC_instance_trial_of_the_champion()
{
    new instance_trial_of_the_champion();
}
