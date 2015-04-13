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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Vehicle.h"
#include "CombatAI.h"
#include "Player.h"
#include "WorldSession.h"

/////////////////////
///npc_injured_goblin
/////////////////////

enum InjuredGoblinMiner
{
    QUEST_BITTER_DEPARTURE     = 12832,
    SAY_QUEST_ACCEPT           = 0,
    SAY_END_WP_REACHED         = 1,
    GOSSIP_ID                  = 9859,
    GOSSIP_OPTION_ID           = 0
};

class npc_injured_goblin : public CreatureScript
{
public:
    npc_injured_goblin() : CreatureScript("npc_injured_goblin") { }

    struct npc_injured_goblinAI : public npc_escortAI
    {
        npc_injured_goblinAI(Creature* creature) : npc_escortAI(creature) { }

        void WaypointReached(uint32 waypointId) override
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
                case 26:
                    Talk(SAY_END_WP_REACHED, player);
                    break;
                case 27:
                    player->GroupEventHappens(QUEST_BITTER_DEPARTURE, me);
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/) override { }

        void Reset() override { }

        void JustDied(Unit* /*killer*/) override
        {
            Player* player = GetPlayerForEscort();
            if (HasEscortState(STATE_ESCORT_ESCORTING) && player)
                player->FailQuest(QUEST_BITTER_DEPARTURE);
        }

       void UpdateAI(uint32 uiDiff) override
        {
            npc_escortAI::UpdateAI(uiDiff);
            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }

        void sGossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            if (sender == GOSSIP_ID && action == GOSSIP_OPTION_ID)
            {
                player->CLOSE_GOSSIP_MENU();
                me->setFaction(113);
                npc_escortAI::Start(true, true, player->GetGUID());
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_injured_goblinAI(creature);
    }

    bool OnQuestAccept(Player* /*player*/, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_BITTER_DEPARTURE)
            creature->AI()->Talk(SAY_QUEST_ACCEPT);

        return false;
    }
};

/*######
## npc_roxi_ramrocket
######*/

enum RoxiRamrocket
{
    SPELL_MECHANO_HOG               = 60866,
    SPELL_MEKGINEERS_CHOPPER        = 60867
};

class npc_roxi_ramrocket : public CreatureScript
{
public:
    npc_roxi_ramrocket() : CreatureScript("npc_roxi_ramrocket") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        //Quest Menu
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        //Trainer Menu
        if ( creature->IsTrainer() )
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

        //Vendor Menu
        if ( creature->IsVendor() )
            if (player->HasSpell(SPELL_MECHANO_HOG) || player->HasSpell(SPELL_MEKGINEERS_CHOPPER))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_TRAIN:
            player->GetSession()->SendTrainerList(creature->GetGUID());
            break;
        case GOSSIP_ACTION_TRADE:
            player->GetSession()->SendListInventory(creature->GetGUID());
            break;
        }
        return true;
    }
};

/*######
## npc_brunnhildar_prisoner
######*/

enum BrunnhildarPrisoner
{
    SPELL_ICE_PRISON           = 54894,
    SPELL_ICE_LANCE            = 55046,
    SPELL_FREE_PRISONER        = 55048,
    SPELL_RIDE_DRAKE           = 55074,
    SPELL_SHARD_IMPACT         = 55047
};

class npc_brunnhildar_prisoner : public CreatureScript
{
public:
    npc_brunnhildar_prisoner() : CreatureScript("npc_brunnhildar_prisoner") { }

    struct npc_brunnhildar_prisonerAI : public ScriptedAI
    {
        npc_brunnhildar_prisonerAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            freed = false;
        }

        bool freed;

        void Reset() override
        {
            Initialize();
            me->CastSpell(me, SPELL_ICE_PRISON, true);
        }

        void JustRespawned() override
        {
            Reset();
        }

        void UpdateAI(uint32 /*diff*/) override
        {
            if (!freed)
                return;

            if (!me->GetVehicle())
                me->DespawnOrUnsummon();
        }

        void SpellHit(Unit* caster, const SpellInfo* spell) override
        {
            if (spell->Id != SPELL_ICE_LANCE)
                return;

            if (caster->GetVehicleKit()->GetAvailableSeatCount() != 0)
            {
                me->CastSpell(me, SPELL_FREE_PRISONER, true);
                me->CastSpell(caster, SPELL_RIDE_DRAKE, true);
                me->CastSpell(me, SPELL_SHARD_IMPACT, true);
                freed = true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_brunnhildar_prisonerAI(creature);
    }
};

/*######
## npc_freed_protodrake
######*/

enum FreedProtoDrake
{
    NPC_DRAKE                           = 29709,

    AREA_VALLEY_OF_ANCIENT_WINTERS      = 4437,

    TEXT_EMOTE                          = 0,

    SPELL_KILL_CREDIT_PRISONER          = 55144,
    SPELL_SUMMON_LIBERATED              = 55073,
    SPELL_KILL_CREDIT_DRAKE             = 55143,

    EVENT_CHECK_AREA                    = 1,
    EVENT_REACHED_HOME                  = 2,
};

class npc_freed_protodrake : public CreatureScript
{
public:
    npc_freed_protodrake() : CreatureScript("npc_freed_protodrake") { }

    struct npc_freed_protodrakeAI : public VehicleAI
    {
        npc_freed_protodrakeAI(Creature* creature) : VehicleAI(creature) { }

        EventMap events;

        void Reset() override
        {
            events.ScheduleEvent(EVENT_CHECK_AREA, 5000);
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != WAYPOINT_MOTION_TYPE)
                return;

            if (id == 15)
            // drake reached village
            events.ScheduleEvent(EVENT_REACHED_HOME, 2000);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            switch (events.ExecuteEvent())
            {
                case EVENT_CHECK_AREA:
                    if (me->GetAreaId() == AREA_VALLEY_OF_ANCIENT_WINTERS)
                    {
                        if (Vehicle* vehicle = me->GetVehicleKit())
                            if (Unit* passenger = vehicle->GetPassenger(0))
                            {
                                Talk(TEXT_EMOTE, passenger);
                                me->GetMotionMaster()->MovePath(NPC_DRAKE, false);
                            }
                    }
                    else
                        events.ScheduleEvent(EVENT_CHECK_AREA, 5000);
                    break;
                case EVENT_REACHED_HOME:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* player = vehicle->GetPassenger(0))
                            if (player->GetTypeId() == TYPEID_PLAYER)
                            {
                                // for each prisoner on drake, give credit
                                for (uint8 i = 1; i < 4; ++i)
                                    if (Unit* prisoner = me->GetVehicleKit()->GetPassenger(i))
                                    {
                                        if (prisoner->GetTypeId() != TYPEID_UNIT)
                                            return;
                                        prisoner->CastSpell(player, SPELL_KILL_CREDIT_PRISONER, true);
                                        prisoner->CastSpell(prisoner, SPELL_SUMMON_LIBERATED, true);
                                        prisoner->ExitVehicle();
                                    }
                                me->CastSpell(me, SPELL_KILL_CREDIT_DRAKE, true);
                                player->ExitVehicle();
                            }
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_freed_protodrakeAI(creature);
    }
};

class npc_icefang : public CreatureScript
{
public:
    npc_icefang() : CreatureScript("npc_icefang") { }

    struct npc_icefangAI : public npc_escortAI
    {
        npc_icefangAI(Creature* creature) : npc_escortAI(creature) { }

        void AttackStart(Unit* /*who*/) override { }
        void EnterCombat(Unit* /*who*/) override { }
        void EnterEvadeMode() override { }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply) override
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                if (apply)
                    Start(false, true, who->GetGUID());
            }
        }

        void WaypointReached(uint32 /*waypointId*/) override { }
        void JustDied(Unit* /*killer*/) override { }
        void OnCharmed(bool /*apply*/) override { }

        void UpdateAI(uint32 diff) override
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_icefangAI(creature);
    }
};

class npc_hyldsmeet_protodrake : public CreatureScript
{
    enum NPCs
    {
        NPC_HYLDSMEET_DRAKERIDER = 29694
    };

    public:
        npc_hyldsmeet_protodrake() : CreatureScript("npc_hyldsmeet_protodrake") { }

        class npc_hyldsmeet_protodrakeAI : public CreatureAI
        {
            public:
                npc_hyldsmeet_protodrakeAI(Creature* creature) : CreatureAI(creature), _accessoryRespawnTimer(0), _vehicleKit(creature->GetVehicleKit()) { }

                void PassengerBoarded(Unit* who, int8 /*seat*/, bool apply) override
                {
                    if (apply)
                        return;

                    if (who->GetEntry() == NPC_HYLDSMEET_DRAKERIDER)
                        _accessoryRespawnTimer = 5 * MINUTE * IN_MILLISECONDS;
                }

                void UpdateAI(uint32 diff) override
                {
                    //! We need to manually reinstall accessories because the vehicle itself is friendly to players,
                    //! so EnterEvadeMode is never triggered. The accessory on the other hand is hostile and killable.
                    if (_accessoryRespawnTimer && _accessoryRespawnTimer <= diff && _vehicleKit)
                    {
                        _vehicleKit->InstallAllAccessories(true);
                        _accessoryRespawnTimer = 0;
                    }
                    else
                        _accessoryRespawnTimer -= diff;
                }

            private:
                uint32 _accessoryRespawnTimer;
                Vehicle* _vehicleKit;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_hyldsmeet_protodrakeAI(creature);
        }
};

/*#####
# npc_brann_bronzebeard for Quest 13285 "Forging the Keystone"
#####*/

enum BrannBronzebeard
{
    NPC_BRANN_BRONZEBEARD = 31810,
    NPC_A_DISTANT_VOICE   = 31814,
    OBJECT_TOL_SIGNAL_1   = 193590,
    OBJECT_TOL_SIGNAL_2   = 193591,
    OBJECT_TOL_SIGNAL_3   = 193592,
    OBJECT_TOL_SIGNAL_4   = 193593,
    OBJECT_TOL_SIGNAL_5   = 193594,
    SPELL_RESURRECTION    = 58854,
    SAY_BRANN_1           = 0,
    SAY_BRANN_2           = 1,
    SAY_BRANN_3           = 2,
    SAY_VOICE_1           = 0,
    SAY_VOICE_2           = 1,
    SAY_VOICE_3           = 2,
    SAY_VOICE_4           = 3,
    SAY_VOICE_5           = 4,

    EVENT_SCRIPT_1        = 3,
    EVENT_SCRIPT_2        = 4,
    EVENT_SCRIPT_3        = 5,
    EVENT_SCRIPT_4        = 6,
    EVENT_SCRIPT_5        = 7,
    EVENT_SCRIPT_6        = 8,
    EVENT_SCRIPT_7        = 9,
    EVENT_SCRIPT_8        = 10,
    EVENT_SCRIPT_9        = 11,
    EVENT_SCRIPT_10       = 12,
    EVENT_SCRIPT_11       = 13,
    EVENT_SCRIPT_12       = 14,
    EVENT_SCRIPT_13       = 15
};

class npc_brann_bronzebeard_keystone : public CreatureScript
{
public:
    npc_brann_bronzebeard_keystone() : CreatureScript("npc_brann_bronzebeard_keystone") { }

    struct npc_brann_bronzebeard_keystoneAI : public ScriptedAI
    {
        npc_brann_bronzebeard_keystoneAI(Creature* creature) : ScriptedAI(creature)
        {
            objectCounter = 0;
        }

        void Reset() override
        {
            for (ObjectGuid& guid : objectGUID)
                guid.Clear();

            playerGUID.Clear();
            voiceGUID.Clear();
            objectCounter = 0;
        }

        void sGossipSelect(Player* player, uint32 /*sender*/, uint32 /*action*/) override
        {
            player->CLOSE_GOSSIP_MENU();
            playerGUID = player->GetGUID();
            events.ScheduleEvent(EVENT_SCRIPT_1, 100);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SCRIPT_1:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                            Talk(SAY_BRANN_1, player);
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        if (Creature* voice = me->SummonCreature(NPC_A_DISTANT_VOICE, 7863.43f, -1396.585f, 1538.076f, 2.949606f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 49000))
                            voiceGUID = voice->GetGUID();
                        events.ScheduleEvent(EVENT_SCRIPT_2, 4000);
                        break;
                    case EVENT_SCRIPT_2:
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovePoint(0, 7861.488f, -1396.376f, 1534.059f, false);
                        events.ScheduleEvent(EVENT_SCRIPT_3, 6000);
                        break;
                    case EVENT_SCRIPT_3:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_WORK_MINING);
                        events.ScheduleEvent(EVENT_SCRIPT_4, 6000);
                        break;
                    case EVENT_SCRIPT_4:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                        if (Creature* voice = ObjectAccessor::GetCreature(*me, voiceGUID))
                        {
                            voice->CastSpell(voice, SPELL_RESURRECTION);
                            if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                                voice->AI()->Talk(SAY_VOICE_1, player);
                        }
                        if (GameObject* go = me->SummonGameObject(OBJECT_TOL_SIGNAL_1, 7860.273f, -1383.622f, 1538.302f, -1.658062f, 0, 0,  -0.737277f, 0.6755905f, 0))
                            objectGUID[objectCounter++] = go->GetGUID();
                        events.ScheduleEvent(EVENT_SCRIPT_5, 6000);
                        break;
                    case EVENT_SCRIPT_5:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                            if (Creature* voice = ObjectAccessor::GetCreature(*me, voiceGUID))
                                voice->AI()->Talk(SAY_VOICE_2, player);
                        if (GameObject* go = me->SummonGameObject(OBJECT_TOL_SIGNAL_2, 7875.67f, -1387.266f, 1538.323f, -2.373644f, 0, 0,  -0.9271832f, 0.3746083f, 0))
                            objectGUID[objectCounter++] = go->GetGUID();
                        events.ScheduleEvent(EVENT_SCRIPT_6, 6000);
                        break;
                    case EVENT_SCRIPT_6:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                            if (Creature* voice = ObjectAccessor::GetCreature(*me, voiceGUID))
                                voice->AI()->Talk(SAY_VOICE_3, player);
                        if (GameObject* go = me->SummonGameObject(OBJECT_TOL_SIGNAL_3, 7879.212f, -1401.175f, 1538.279f, 2.967041f, 0, 0,  0.9961939f, 0.08716504f, 0))
                            objectGUID[objectCounter++] = go->GetGUID();
                        events.ScheduleEvent(EVENT_SCRIPT_7, 6000);
                        break;
                    case EVENT_SCRIPT_7:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                            if (Creature* voice = ObjectAccessor::GetCreature(*me, voiceGUID))
                                voice->AI()->Talk(SAY_VOICE_4, player);
                        if (GameObject* go = me->SummonGameObject(OBJECT_TOL_SIGNAL_4, 7868.944f, -1411.18f, 1538.213f, 2.111848f, 0, 0,  0.8703556f, 0.4924237f, 0))
                            objectGUID[objectCounter++] = go->GetGUID();
                        events.ScheduleEvent(EVENT_SCRIPT_8, 6000);
                        break;
                    case EVENT_SCRIPT_8:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                            if (Creature* voice = ObjectAccessor::GetCreature(*me, voiceGUID))
                                voice->AI()->Talk(SAY_VOICE_5, player);
                        if (GameObject* go = me->SummonGameObject(OBJECT_TOL_SIGNAL_5, 7855.11f, -1406.839f, 1538.42f, 1.151916f, 0, 0,  0.5446386f, 0.8386708f, 0))
                            objectGUID[objectCounter] = go->GetGUID();
                        events.ScheduleEvent(EVENT_SCRIPT_9, 6000);
                        break;
                    case EVENT_SCRIPT_9:
                        if (Creature* voice = ObjectAccessor::GetCreature(*me, voiceGUID))
                            voice->CastSpell(voice, SPELL_RESURRECTION);
                        events.ScheduleEvent(EVENT_SCRIPT_10, 6000);
                        break;
                    case EVENT_SCRIPT_10:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                        {
                            Talk(SAY_BRANN_2, player);
                            player->KilledMonsterCredit(me->GetEntry());
                        }
                        events.ScheduleEvent(EVENT_SCRIPT_11, 6000);
                        break;
                    case EVENT_SCRIPT_11:
                        me->SetFacingTo(2.932153f);
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                            Talk(SAY_BRANN_3, player);

                        for (uint8 i = 0; i < 5; ++i)
                            if (GameObject* go = ObjectAccessor::GetGameObject(*me, objectGUID[i]))
                                go->Delete();

                        events.ScheduleEvent(EVENT_SCRIPT_12, 6000);
                        break;
                    case EVENT_SCRIPT_12:
                        me->GetMotionMaster()->Clear();
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(0, 7799.908f, -1413.561f, 1534.829f, false);
                        events.ScheduleEvent(EVENT_SCRIPT_13, 10000);
                        break;
                    case EVENT_SCRIPT_13:
                        me->DisappearAndDie();
                        break;
                }
            }
        }

    private:
        EventMap events;
        ObjectGuid playerGUID;
        ObjectGuid objectGUID[5];
        ObjectGuid voiceGUID;
        uint8 objectCounter;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_brann_bronzebeard_keystoneAI(creature);
    }
};

/*#####
# Quest 13010 Krolmir, Hammer of Storms
#####*/

enum JokkumScriptcast
{
    NPC_KINGJOKKUM                   = 30331,
    NPC_THORIM                       = 30390,
    PATH_JOKKUM                      = 2072200,
    PATH_JOKKUM_END                  = 2072201,
    SAY_HOLD_ON                      = 0,
    SAY_JOKKUM_1                     = 1,
    SAY_JOKKUM_2                     = 2,
    SAY_JOKKUM_3                     = 3,
    SAY_JOKKUM_4                     = 4,
    SAY_JOKKUM_5                     = 5,
    SAY_JOKKUM_6                     = 6,
    SAY_JOKKUM_7                     = 7,
    SAY_JOKKUM_8                     = 8,
    SAY_THORIM_1                     = 0,
    SAY_THORIM_2                     = 1,
    SAY_THORIM_3                     = 2,
    SAY_THORIM_4                     = 3,
    SPELL_JOKKUM_SUMMON              = 56541,
    SPELL_JOKKUM_KILL_CREDIT         = 56545,
    SPELL_EJECT_ALL_PASSENGERS       = 50630,
    SPELL_PLAYER_CAST_VERANUS_SUMMON = 56650,
    SPELL_SUMMON_VERANUS_AND_THORIM  = 56649,
    EVENT_KROLMIR_1                  = 16,
    EVENT_KROLMIR_2                  = 17,
    EVENT_KROLMIR_3                  = 18,
    EVENT_KROLMIR_4                  = 19,
    EVENT_KROLMIR_5                  = 20,
    EVENT_KROLMIR_6                  = 21,
    EVENT_KROLMIR_7                  = 22,
    EVENT_KROLMIR_8                  = 23,
    EVENT_KROLMIR_9                  = 24,
};

class npc_king_jokkum_vehicle : public CreatureScript
{
public:
    npc_king_jokkum_vehicle() : CreatureScript("npc_king_jokkum_vehicle") { }

    struct npc_king_jokkum_vehicleAI : public VehicleAI
    {
        npc_king_jokkum_vehicleAI(Creature* creature) : VehicleAI(creature)
        {
            pathEnd = false;
        }

        void Reset() override
        {
            playerGUID.Clear();
            pathEnd    = false;
        }

        void OnCharmed(bool /*apply*/) override { }

        void PassengerBoarded(Unit* who, int8 /*seat*/, bool apply) override
        {
            if (apply)
            {
                playerGUID = who->GetGUID();
                Talk(SAY_HOLD_ON, who);
                me->CastSpell(who, SPELL_JOKKUM_KILL_CREDIT, true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                me->GetMotionMaster()->MovePath(PATH_JOKKUM, false);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != WAYPOINT_MOTION_TYPE)
                return;

            if (pathEnd)
            {
                if (id == 4)
                {

                }
            }
            else
            {
                if (id == 19)
                {
                    pathEnd = true;
                    me->SetFacingTo(0.418879f);
                    Talk(SAY_JOKKUM_1);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                        me->CastSpell(player, SPELL_PLAYER_CAST_VERANUS_SUMMON);
                    me->CastSpell(me, SPELL_EJECT_ALL_PASSENGERS);

                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!pathEnd)
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_KROLMIR_1:
                        Talk(SAY_JOKKUM_2);
                        events.ScheduleEvent(EVENT_KROLMIR_2, 4000);
                        break;
                }
            }
        }

    private:
        EventMap events;
        ObjectGuid playerGUID;
        bool pathEnd;

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_king_jokkum_vehicleAI(creature);
    }
};

Position const WildWyrnMovePosition[8] =
{
	{ 7081.765f, -1968.013f, 920.187f },
	{ 7091.057f, -2060.715f, 881.015f },
	{ 7151.225f, -2203.255f, 900.593f },
	{ 7180.513f, -2288.469f, 944.239f },
	{ 7070.415f, -2246.682f, 1017.335f },
	{ 6876.318f, -2219.448f, 1056.235f },
	{ 6927.351f, -2083.386f, 988.975f },
	{ 7018.587f, -1982.362f, 917.869f }
};

enum EventsWildWyrm
{
	EVENT_DAMAGE_START = 1,
	EVENT_DAMAGE_END
};

class npc_wild_wyrm_vehicle : public CreatureScript
{
public:
    npc_wild_wyrm_vehicle() : CreatureScript("npc_wild_wyrm_vehicle") { }

	struct npc_wild_wyrm_vehicleAI : public npc_escortAI
    {
		npc_wild_wyrm_vehicleAI(Creature* creature) : npc_escortAI(creature)
        {
			Initialize();
        }
		
		bool phase2;
		bool startEvent;
		float SpeedValue[8];
		bool done;
		bool changeSeat;

		void Initialize()
		{
			enemy = NULL;
			phase2 = false;
			done = false;
			startEvent = false;
			changeSeat = false;
			for (uint8 i = 0; i < 8; ++i)
				SpeedValue[i] = 3.6f; // Standart speed
		}

        void Reset() override
        {
			npc_escortAI::Reset();
			Initialize();
			InitializeVehicleSpell(NULL, 0);
			me->SetReactState(REACT_PASSIVE);
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
			me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
			events.Reset();
        }

		void OnCharmed(bool /*apply*/) override { }

		void SpellHit(Unit* who, SpellInfo const * spellInfo) override
		{
			if (enemy)
				return;

			if (spellInfo->Id == 56671)
			{
				AttackStart(who);
				me->GetMotionMaster()->MovePoint(100, who->GetPositionX(), who->GetPositionY(), who->GetPositionZ() + 10.f);
				enemy = who;
			}
		}

		void InitializeVehicleSpell(Unit* passenger, uint8 phase)
		{
			me->ClearAllSpells();
			switch (phase)
			{
			case 0:
				me->SetSpell(0, 60533);
				me->SetSpell(1, 56704);
				me->SetSpell(2, 56690);
				me->SetSpell(3, 60586);
				break;
			case 1:
				me->SetSpell(0, 56706);
				me->SetSpell(2, 60587);
				break;
			case 2:
				break;
			default:
				break;
			}
			if (passenger)
				passenger->ToPlayer()->VehicleSpellInitialize();
		}

        void PassengerBoarded(Unit* who, int8 seat, bool apply) override
        {
			if (changeSeat)
			{
				changeSeat = false;
				return;
			}

			if (apply && !startEvent)
			{
				for (uint8 i = 0; i < 8; ++i)
				{
					AddWaypoint(i, WildWyrnMovePosition[i].GetPositionX(), WildWyrnMovePosition[i].GetPositionY(), WildWyrnMovePosition[i].GetPositionZ(), roll_chance_i(25) ? urand(1500, 3000) : 0);
					SpeedValue[i] = frand(3.6f, 6.f);
				}
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
				Start(false, true, ObjectGuid::Empty, 0, false, true, false);
				DoCast(60533);
				events.ScheduleEvent(EVENT_DAMAGE_START, 2000);
				startEvent = true;
			}

			if (!apply)
				me->DespawnOrUnsummon(5000);
        }

        void MovementInform(uint32 type, uint32 id) override
        {
			npc_escortAI::MovementInform(type, id);
			if (type == 16 && id == 0)
			if (enemy)
				enemy->Kill(me);
				
			if (type != POINT_MOTION_TYPE)
				return;

			switch (id)
			{
			case 100:
				if (enemy)
					enemy->CastSpell(me, 56673);
				break;
			}
        }

		void DamageTaken(Unit* /*done_by*/, uint32 &damage) override
		{
			if (!startEvent && !enemy && done)
				return;

			if (damage >= me->GetHealth())
			{
				damage = 0;
				me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
				done = true;
				me->RemoveAura(56692);
				me->GetMotionMaster()->Clear(false);
				me->GetMotionMaster()->MoveFall();
				InitializeVehicleSpell(enemy, 2);
				events.CancelEvent(EVENT_DAMAGE_START);
				events.CancelEvent(EVENT_DAMAGE_END);
			}
		}

		void WaypointReached(uint32 waypointId) override
		{
			if (!startEvent && !enemy)
				return;

			me->SetSpeed(MOVE_FLIGHT, SpeedValue[waypointId]);
		}

		void UpdateEscortAI(uint32 const /*diff*/) override { }

        void UpdateAI(uint32 diff) override
        {
			npc_escortAI::UpdateAI(diff);

			if (!startEvent && !enemy)
				return;

            events.Update(diff);

			if (!phase2 && HealthBelowPct(25))
			{
				phase2 = true;
				DoCast(enemy, 56692);
				events.CancelEvent(EVENT_DAMAGE_START);
				events.CancelEvent(EVENT_DAMAGE_END);
				me->RemoveAura(56689);
				if (Vehicle* vehicle = me->GetVehicleKit())
					if (Unit* passenger = vehicle->GetPassenger(0))
						if (passenger->GetTypeId() == TYPEID_PLAYER)
						{
							changeSeat = true;
							passenger->ChangeSeat(1, false);
							InitializeVehicleSpell(passenger, 1);
						}
			}

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
				case EVENT_DAMAGE_START:
					me->Talk(32763, CHAT_MSG_RAID_BOSS_WHISPER, 100.f, enemy);
					events.ScheduleEvent(EVENT_DAMAGE_END, 2000);
					break;
				case EVENT_DAMAGE_END:
					if (!enemy->HasAura(56704))
						DoCast(enemy, 60776, true);
					else
						me->Talk(32794, CHAT_MSG_RAID_BOSS_WHISPER, 100.f, enemy);

					if (!me->HasAura(56689))
					{
						enemy->ExitVehicle();
						enemy = NULL;
					}
					events.ScheduleEvent(EVENT_DAMAGE_START, 5000);
					break;
                }
            }
        }

		void JustDied(Unit* killer) override
		{
			if (killer->GetTypeId() == TYPEID_PLAYER)
				killer->ToPlayer()->KilledMonsterCredit(30415);
		}

    private:
        EventMap events;
        Unit* enemy;

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
		return new npc_wild_wyrm_vehicleAI(creature);
    }
};

// 60864 Jaws of Death
class spell_wild_wyrm_jaws_of_death : public SpellScriptLoader
{
public:
	spell_wild_wyrm_jaws_of_death() : SpellScriptLoader("spell_wild_wyrm_jaws_of_death") { }

	class spell_wild_wyrm_jaws_of_death_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_wild_wyrm_jaws_of_death_SpellScript);

		void HandleDamage(SpellEffIndex /*effIndex*/)
		{
			Vehicle* vehicle = GetCaster()->GetVehicleKit();

			if (!vehicle)
				return;

			Unit* passenger = vehicle->GetPassenger(1);

			if (!passenger)
				return;

			int32 value = int32(passenger->CountPctFromMaxHealth(3));
			SetHitDamage(value);
		}

		void Register() override
		{
			OnEffectHitTarget += SpellEffectFn(spell_wild_wyrm_jaws_of_death_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_wild_wyrm_jaws_of_death_SpellScript();
	}
};

// 60533 Grab On
class spell_wild_wyrm_grip_on : public SpellScriptLoader
{
public:
	spell_wild_wyrm_grip_on() : SpellScriptLoader("spell_wild_wyrm_grip_on") { }

	class spell_wild_wyrm_grip_on_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_wild_wyrm_grip_on_SpellScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			if (!sSpellMgr->GetSpellInfo(56689)) // grip
				return false;
			return true;
		}

		void HandleScript(SpellEffIndex /*effIndex*/)
		{
			Unit* caster = GetCaster();
			uint32 newStack = 0;

			if (caster->HasAura(56689))
			{
				newStack = caster->GetAura(56689)->GetStackAmount() + 10;
				if (newStack >= 99)
					newStack = 99;
				caster->GetAura(56689)->SetStackAmount(newStack);
			}
			else
				caster->AddAura(56689, caster)->SetStackAmount(50);
		}

		void Register() override
		{
			OnEffectHitTarget += SpellEffectFn(spell_wild_wyrm_grip_on_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_wild_wyrm_grip_on_SpellScript();
	}
};

// 60776 Claw Swipe
class spell_wild_wyrm_claw_swipe : public SpellScriptLoader
{
public:
	spell_wild_wyrm_claw_swipe() : SpellScriptLoader("spell_wild_wyrm_claw_swipe") { }

	class spell_wild_wyrm_claw_swipe_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_wild_wyrm_claw_swipe_SpellScript);

		void HandleDamage(SpellEffIndex /*effIndex*/)
		{
			Vehicle* vehicle = GetCaster()->GetVehicleKit();

			if (!vehicle)
				return;

			Unit* passenger = vehicle->GetPassenger(0);

			if (!passenger)
				return;

			int32 value = int32(passenger->CountPctFromMaxHealth(8));
			SetHitDamage(value);
		}

		void Register() override
		{
			OnEffectHitTarget += SpellEffectFn(spell_wild_wyrm_claw_swipe_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_wild_wyrm_claw_swipe_SpellScript();
	}
};

// 60587 fatal strike
class spell_wild_wyrm_fatal_strike : public SpellScriptLoader
{
public:
	spell_wild_wyrm_fatal_strike() : SpellScriptLoader("spell_wild_wyrm_fatal_strike") { }

	class spell_wild_wyrm_fatal_strike_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_wild_wyrm_fatal_strike_SpellScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			if (!sSpellMgr->GetSpellInfo(60881) || // fatal strike damage
				!sSpellMgr->GetSpellInfo(56706)) // Pry Jaws Open
				return false;
			return true;
		}

		void HandleDummy(SpellEffIndex /*effIndex*/)
		{
			Unit* caster = GetCaster();
			Vehicle* vehicle = caster->GetVehicleKit();
			if (!vehicle && !caster)
				return;
			Unit* passenger = vehicle->GetPassenger(1);
			if (Aura* aura = caster->GetAura(56706))
			if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetAmount()))
				caster->CastSpell(caster, 60881, true);
			else if (passenger)
				caster->Talk(32795, CHAT_MSG_RAID_BOSS_WHISPER, 100.f, passenger);
		}

		void Register() override
		{
			OnEffectHitTarget += SpellEffectFn(spell_wild_wyrm_fatal_strike_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_wild_wyrm_fatal_strike_SpellScript();
	}
};

// 56690 | 60586 
class spell_wild_wyrm_spells : public SpellScriptLoader
{
public:
	spell_wild_wyrm_spells() : SpellScriptLoader("spell_wild_wyrm_spells") { }

	class spell_wild_wyrm_spells_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_wild_wyrm_spells_SpellScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			if (!sSpellMgr->GetSpellInfo(56689)) // grip
				return false;
			return true;
		}

		void HandleScript(SpellEffIndex /*effIndex*/)
		{
			Unit* caster = GetCaster();
			uint8 stack = 0;
			int32 basePoints = GetSpellInfo()->Id == 56690 ? 5 : 15;
			if (caster->HasAura(56689))
			{
				stack = caster->GetAura(56689)->GetStackAmount();
				if (stack <= basePoints)
					caster->RemoveAura(56689);
				else
					caster->GetAura(56689)->SetStackAmount(stack - basePoints);
			}
		}

		void Register() override
		{
			OnEffectHitTarget += SpellEffectFn(spell_wild_wyrm_spells_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_wild_wyrm_spells_SpellScript();
	}
};

class spell_jokkum_scriptcast : public SpellScriptLoader
{
    public: spell_jokkum_scriptcast() : SpellScriptLoader("spell_jokkum_scriptcast") { }

        class spell_jokkum_scriptcast_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_jokkum_scriptcast_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_JOKKUM_SUMMON))
                    return false;
                return true;
            }

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                    target->CastSpell(target, SPELL_JOKKUM_SUMMON, true);
            }

            void Register() override
            {
                OnEffectApply += AuraEffectApplyFn(spell_jokkum_scriptcast_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_jokkum_scriptcast_AuraScript();
        }
};

class spell_veranus_summon : public SpellScriptLoader
{
    public: spell_veranus_summon() : SpellScriptLoader("spell_veranus_summon") { }

        class spell_veranus_summon_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_veranus_summon_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SUMMON_VERANUS_AND_THORIM))
                    return false;
                return true;
            }

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                    target->CastSpell(target, SPELL_SUMMON_VERANUS_AND_THORIM, true);
            }

            void Register() override
            {
                OnEffectApply += AuraEffectApplyFn(spell_veranus_summon_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_veranus_summon_AuraScript();
        }
};

enum CloseRift
{
    SPELL_DESPAWN_RIFT          = 61665
};

class spell_close_rift : public SpellScriptLoader
{
    public:
        spell_close_rift() : SpellScriptLoader("spell_close_rift") { }

        class spell_close_rift_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_close_rift_AuraScript);

        public:
            spell_close_rift_AuraScript()
            {
                _counter = 0;
            }

        private:
            bool Validate(SpellInfo const* /*spell*/) override
            {
                return sSpellMgr->GetSpellInfo(SPELL_DESPAWN_RIFT) != nullptr;
            }

            void HandlePeriodic(AuraEffect const* /* aurEff */)
            {
                if (++_counter == 5)
                    GetTarget()->CastSpell((Unit*)NULL, SPELL_DESPAWN_RIFT, true);
            }

            void Register() override
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_close_rift_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }

        private:
            uint8 _counter;

        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_close_rift_AuraScript();
        }
};

void AddSC_storm_peaks()
{
    new npc_injured_goblin();
    new npc_roxi_ramrocket();
    new npc_brunnhildar_prisoner();
    new npc_freed_protodrake();
    new npc_icefang();
    new npc_hyldsmeet_protodrake();
    new npc_brann_bronzebeard_keystone();
    new npc_king_jokkum_vehicle();
    new spell_jokkum_scriptcast();
    new spell_veranus_summon();
    new spell_close_rift();
	new npc_wild_wyrm_vehicle();
	new spell_wild_wyrm_grip_on();
	new spell_wild_wyrm_spells();
	new spell_wild_wyrm_claw_swipe();
	new spell_wild_wyrm_fatal_strike();
	new spell_wild_wyrm_jaws_of_death();
}
