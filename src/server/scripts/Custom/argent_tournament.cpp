/*######
## npc_valiant_melee 
######*/

enum Valiant
{
    QUEST_GRAND_MELEE_1             = 13665,
    QUEST_GRAND_MELEE_2             = 13745,
    QUEST_GRAND_MELEE_3             = 13750,
    QUEST_GRAND_MELEE_4             = 13756,
    QUEST_GRAND_MELEE_5             = 13761,
    QUEST_GRAND_MELEE_6             = 13767,
    QUEST_GRAND_MELEE_7             = 13772,
    QUEST_GRAND_MELEE_8             = 13777,
    QUEST_GRAND_MELEE_9             = 13782,
    QUEST_GRAND_MELEE_10            = 13787,

    SPELL_MOUNTED_MELEE_VICTORY     = 62724,
    SPELL_RIDE_VEHICLE              = 63151,
    SPELL_LANCE_EQUIPPED            = 62853,
    SPELL_VALIANT_CHARGE            = 63010,
    SPELL_VALIANT_SHIELD_BREAKER    = 65147,
    SPELL_VALIANT_DEFEND            = 62719,
    SPELL_VALIANT_THRUST            = 62544,
    SPELL_YELLOW_ROSE_FIREWORK      = 11544,
    SPELL_PLAYER_ON_AT_MOUNT        = 63034,
    
    NPC_STORMWIND_VALIANT           = 33561,
    NPC_DARNASSUS_VALIANT           = 33559,
    NPC_EXODAR_VALIANT              = 33562,
    NPC_GNOMEREGAN_VALIANT          = 33558,
    NPC_IRONFORGE_VALIANT           = 33564,
    NPC_ORGRIMMAR_VALIANT           = 33306,
    NPC_SENJIN_VALIANT              = 33285,
    NPC_SILVERMOON_VALIANT          = 33382,
    NPC_UNDERCITY_VALIANT           = 33384,
    NPC_THUNDER_BLUFF_VALIANT       = 33383,

    FACTION_FRIENDLY                = 35,
    FACTION_HOSTILE                 = 14,

    POINT_FIRE                      = 10,
};

#define GRAND_MELEE_GOSSIP_VALIANT "I am ready to fight."
#define GRAND_MELEE_SAY_START_1 "On your guard!"
#define GRAND_MELEE_SAY_START_2 "Prepare yourself!"
#define GRAND_MELEE_SAY_END "I have been defeated. Good Fight!"
#define GRAND_MELEE_SAY_VICTORY "I am victorious!"

class the_grand_melee : public CreatureScript
{
    private:
        enum Events
        {
            EVENT_MOVE = 1,
            EVENT_CAST = 2,
        };

    public:
        the_grand_melee() : CreatureScript("npc_valiant_melee") { }

        struct the_grand_meleeAI : public ScriptedAI
        {
            the_grand_meleeAI(Creature* _Creature) : ScriptedAI(_Creature) 
            { 
                Challenger = NULL;
            }
            
            void Reset()
            {
                Events.Reset();

                me->setFaction(FACTION_FRIENDLY);
                me->SetReactState(REACT_PASSIVE);
            }
         
            void EnterCombat(Unit* /*who*/)
            {
                Events.ScheduleEvent(EVENT_MOVE, urand(5000, 6000));
                Events.ScheduleEvent(EVENT_CAST, urand(1000, 2000));
            }
            
            void DamageTaken(Unit* DoneBy, uint32& Damage)
            {
                if (Damage > me->GetHealth())
                {
                    Damage = 0;

                    me->CastSpell(me, SPELL_YELLOW_ROSE_FIREWORK , true);
                    me->Say(GRAND_MELEE_SAY_END, LANG_UNIVERSAL, 0);
                    me->setFaction(FACTION_FRIENDLY);
                    me->DespawnOrUnsummon(4000);

                    DoneBy->CastSpell(DoneBy, SPELL_MOUNTED_MELEE_VICTORY, true);
                }
            }

            void DamageDealt(Unit* Victim, uint32& DamageDone, DamageEffectType /*DamageType*/)
            {
                if (DamageDone > Victim->GetHealth())
                {
                    DamageDone = Victim->GetHealth() - 1;
                    me->Say(GRAND_MELEE_SAY_VICTORY, LANG_UNIVERSAL, 0);
                    EnterEvadeMode();
                }
            }

            void MovementInform(uint32 Type, uint32 Id)
            {
                if (Type != POINT_MOTION_TYPE)
                    return;

                if (Id == POINT_FIRE)
                {
                    if (urand(0,4) >= 3)
                        DoCast(SPELL_VALIANT_CHARGE);
                    else
                        DoCast(SPELL_VALIANT_SHIELD_BREAKER);

                    me->GetMotionMaster()->MoveChase(me->GetVictim());
                }
                
            }
            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                Events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 EventId = Events.ExecuteEvent())
                {
                    switch (EventId)
                    {
                        case EVENT_MOVE:
                        {
                            Position MovePos = me->GetPosition();
                            me->GetFirstCollisionPosition(frand(9.0f, 12.0f), frand(0, M_PI));
                            me->GetMotionMaster()->MovePoint(POINT_FIRE, MovePos);
                            Events.ScheduleEvent(EVENT_MOVE, urand(7000, 10000));
                        }
                            break;
                        case EVENT_CAST:
                            if (urand(0,4) == 4)
                                DoCastVictim(SPELL_VALIANT_SHIELD_BREAKER, true);
                            else
                                DoCast(SPELL_VALIANT_DEFEND);

                            Events.ScheduleEvent(EVENT_CAST, urand(9000, 12000));
                        default:
                            break;
                    }
                }

                DoSpellAttackIfReady(SPELL_VALIANT_THRUST);
            }

            private:
                EventMap Events;
                Unit* Challenger;
        };

        /*bool OnGossipHello(Player* _Player, Creature* _Creature)
        {
            if (_Creature->isQuestGiver())
                _Player->PrepareQuestMenu(_Creature->GetGUID());
            
            if (((_Player->GetQuestStatus(QUEST_GRAND_MELEE_1) == QUEST_STATUS_INCOMPLETE) ||
                (_Player->GetQuestStatus(QUEST_GRAND_MELEE_2) == QUEST_STATUS_INCOMPLETE) ||
                (_Player->GetQuestStatus(QUEST_GRAND_MELEE_3) == QUEST_STATUS_INCOMPLETE) ||
                (_Player->GetQuestStatus(QUEST_GRAND_MELEE_4) == QUEST_STATUS_INCOMPLETE) ||
                (_Player->GetQuestStatus(QUEST_GRAND_MELEE_5) == QUEST_STATUS_INCOMPLETE) ||
                (_Player->GetQuestStatus(QUEST_GRAND_MELEE_6) == QUEST_STATUS_INCOMPLETE) ||
                (_Player->GetQuestStatus(QUEST_GRAND_MELEE_7) == QUEST_STATUS_INCOMPLETE) ||
                (_Player->GetQuestStatus(QUEST_GRAND_MELEE_8) == QUEST_STATUS_INCOMPLETE) ||
                (_Player->GetQuestStatus(QUEST_GRAND_MELEE_9) == QUEST_STATUS_INCOMPLETE) ||
                (_Player->GetQuestStatus(QUEST_GRAND_MELEE_10) == QUEST_STATUS_INCOMPLETE)) &&
                (_Player->HasAura(SPELL_RIDE_VEHICLE)) &&
                (_Player->HasAura(SPELL_PLAYER_ON_AT_MOUNT)) &&
                (_Player->HasAura(SPELL_LANCE_EQUIPPED)))
            {
                if ((_Creature->GetEntry() == NPC_STORMWIND_VALIANT) || (_Creature->GetEntry() == NPC_DARNASSUS_VALIANT) ||
                    (_Creature->GetEntry() == NPC_EXODAR_VALIANT) || (_Creature->GetEntry() == NPC_GNOMEREGAN_VALIANT) ||
                    (_Creature->GetEntry() == NPC_IRONFORGE_VALIANT))
                {
                    if (_Player->GetTeam() == ALLIANCE)
                    {
                        _Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GRAND_MELEE_GOSSIP_VALIANT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                        _Player->SEND_GOSSIP_MENU(_Player->GetGossipTextId(_Creature), _Creature->GetGUID());
                    }
                    else
                        return false;
                
                }
                else
                {
                    if (_Player->GetTeam() == HORDE)
                    {
                        _Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GRAND_MELEE_GOSSIP_VALIANT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                        _Player->SEND_GOSSIP_MENU(_Player->GetGossipTextId(_Creature), _Creature->GetGUID());
                    }
                    else
                        return false;
                }
                return true;
            }
            return false;
        }*/
        
        bool OnGossipSelect(Player* pPlayer, Creature* _Creature, uint32 /*uiSender*/, uint32 /*action*/)
        {
            if (!pPlayer)
                return false;

            _Creature->setFaction(FACTION_HOSTILE);
            _Creature->SetReactState(REACT_AGGRESSIVE);
            _Creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
            _Creature->Say(urand(0,1) ? GRAND_MELEE_SAY_START_1 : GRAND_MELEE_SAY_START_2, LANG_UNIVERSAL, 0);
            _Creature->AI()->AttackStart(pPlayer->GetVehicleCreatureBase());

            //pPlayer->CLOSE_GOSSIP_MENU();
            return true;
        }
        
        CreatureAI* GetAI(Creature* _Creature) const
        {
            return new the_grand_meleeAI(_Creature);
        }
};

/*######
## npc_valiant_champions 
######*/

enum SpellGral
{
    SHIELD_BREAKER                          = 62626,
    CHARGE                                  = 68321,
    THRUST                                  = 62544,
    DEFEND                                  = 62552,
    RIDE_VEHICLE                            = 63151,
    PLAYER_ON_TOURNAMENT_MOUNT              = 63034,
    LANCE_EQUIPPED                          = 62853,
    SHIELD_LEVEL1                           = 62719,
    SHIELD_LEVEL2                           = 64100,
    SHIELD_LEVEL3                           = 63132,
};

enum TimersGral
{
    TIMER_SPELL_MIN         = 1000,
    TIMER_SPELL_MAX         = 2000,
    TIMER_MoviTimer_MIN     = 1000,
    TIMER_MoviTimer_MAX     = 2000
};

#define GOSSIP_VALIANT_1    "I am ready to fight."
//#define GOSSIP_VALIANT_GOSS "Are you sure you ready to fight a champion?"
#define SAY_START_1         "On your guard!"
#define SAY_START_2         "Prepare yourself!"
#define SAY_END             "I have been defeated. Good Fight !"

enum ValiantQuest
{
    QUEST_AMONG_THECHAMPIONS_A      = 13790,
    QUEST_AMONG_THECHAMPIONS_H      = 13811,
    QUEST_AMONG_THECHAMPIONS_A2     = 13793,
    QUEST_AMONG_THECHAMPIONS_H2     = 13814,
    MOUNTED_MELEE_VICTORY           = 63596

};

class among_the_champions : public CreatureScript
{
public:
    among_the_champions() : CreatureScript("npc_valiant_champions") { }

    struct among_the_championsAI : public ScriptedAI
    {
        Unit *pTarget;
        uint32 SpellTimer,MoviTimer;
        int8 x,y;    
       
        among_the_championsAI(Creature* pCreature) : ScriptedAI(pCreature){}
       
        void Deffend()
        {
            if (Aura *cAura = me->GetAura(DEFEND))
            {
                switch (cAura->GetStackAmount())
                {
                    case 1:
                        me->RemoveAura(SHIELD_LEVEL2);
                        me->RemoveAura(SHIELD_LEVEL3);
                        me->CastSpell(me, SHIELD_LEVEL1, true);
                        break;
                    case 2:
                        me->RemoveAura(SHIELD_LEVEL1);
                        me->RemoveAura(SHIELD_LEVEL3);
                        me->CastSpell(me, SHIELD_LEVEL2, true);
                        break;
                    case 3:
                        me->RemoveAura(SHIELD_LEVEL2);
                        me->RemoveAura(SHIELD_LEVEL1);
                        me->CastSpell(me, SHIELD_LEVEL3, true);
                        break;
                }
            }
        }

        void Reset()
        {
            me->setFaction(35);
            me->SetReactState(REACT_PASSIVE);
            me->SetVisible(true);
        }
       
        void EnterCombat(Unit* /*who*/)
        {
            SpellTimer= urand(TIMER_SPELL_MIN,TIMER_SPELL_MAX );
            MoviTimer = urand(TIMER_MoviTimer_MIN,TIMER_MoviTimer_MAX);
        }
       
        void JustDied(Unit* /*Killer*/)
        {
            me->Say(SAY_END, LANG_UNIVERSAL, 0);
            me->setFaction(35);
            me->SetHealth(1);
            pTarget->CastSpell(pTarget, MOUNTED_MELEE_VICTORY, true);

            me->DespawnOrUnsummon(4000);
        }
       
        void KilledUnit(Unit* /*victim*/)
        {
            Reset();
            EnterEvadeMode();
        }
       
        void SpellHit(Unit* /*caster*/, SpellInfo const* spell)
        {
            if ((spell->Id == SHIELD_BREAKER)||(spell->Id == CHARGE))
            {
                if (Aura *cAura = me->GetAura(DEFEND))
                {
                    switch (cAura->GetStackAmount())
                    {
                        case 0:
                        case 1:
                            me->RemoveAura(DEFEND);
                            me->RemoveAura(SHIELD_LEVEL2);
                            me->RemoveAura(SHIELD_LEVEL3);
                            me->RemoveAura(SHIELD_LEVEL1);
                            break;
                        case 2:
                            cAura->SetStackAmount(1);
                            break;
                        case 3:
                            cAura->SetStackAmount(2);
                            break;
                    }
                }
                Deffend();
            }
        }

        void SpellHitTarget(Unit *pTarget, SpellInfo const* spell)
        {
            if ((spell->Id == SHIELD_BREAKER)||(spell->Id == CHARGE))
            {
                if (Aura *pAura = pTarget->GetAura(DEFEND))
                {
                    switch (pAura->GetStackAmount())
                    {
                        case 0:
                            pTarget->RemoveAura(DEFEND);
                            break;
                        case 1:
                            pAura->SetStackAmount(0);
                            break;
                        case 2:
                            pAura->SetStackAmount(1);
                            break;
                        case 3:
                            pAura->SetStackAmount(2);
                            break;
                    }
                }
            }
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            pTarget = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 200, true);
               
            if (SpellTimer<=uiDiff)
            {
                if (pTarget && me->IsInRange(pTarget,5,40,false))
                {
                    switch (urand(0,7))
                    {
                        case 0: 
                        case 1: 
                        case 2: 
                            DoCastAOE(SHIELD_BREAKER, true);
                            break;
                        case 3: 
                        case 4:
                        case 5:
                        case 6:
                            DoCastAOE(CHARGE, true);
                            break;
                        case 7:
                            me->CastSpell(me, DEFEND, true);
                            Deffend();
                            break;
                    }
                }
                else
                {
                    switch (urand(0,4))
                    {
                        case 0: 
                            me->CastSpell(me, DEFEND, true);
                            Deffend();
                            break;
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                            DoCastAOE(THRUST, true);
                            break;
                    }
                }
                SpellTimer= urand(TIMER_SPELL_MIN,TIMER_SPELL_MAX );
            } else 
                SpellTimer -= uiDiff;
            if (MoviTimer<=uiDiff)
            {
                x =urand(0,7);
                y =urand(0,7);
                switch (urand(0,3))
                {
                    case 0:
                        me->GetMotionMaster()->MovePoint(0, (pTarget->GetPositionX()+x), (pTarget->GetPositionY()+y), pTarget->GetPositionZ());
                        break;
                    case 1: 
                        me->GetMotionMaster()->MovePoint(0, (pTarget->GetPositionX()-x), (pTarget->GetPositionY()+y), pTarget->GetPositionZ());
                        break;
                    case 2: 
                        me->GetMotionMaster()->MovePoint(0, (pTarget->GetPositionX()+x), (pTarget->GetPositionY()-y), pTarget->GetPositionZ());
                        break;
                    case 3: 
                        me->GetMotionMaster()->MovePoint(0, (pTarget->GetPositionX()-x), (pTarget->GetPositionY()-y), pTarget->GetPositionZ());
                        break;
                }
                MoviTimer = urand(TIMER_MoviTimer_MIN,TIMER_MoviTimer_MAX);
                } else 
                    MoviTimer -= uiDiff;

                DoMeleeAttackIfReady();
        }
    };

    /*bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        if (((pPlayer->GetQuestStatus(QUEST_AMONG_THECHAMPIONS_H) == QUEST_STATUS_INCOMPLETE)  ||
            (pPlayer->GetQuestStatus(QUEST_AMONG_THECHAMPIONS_H2) == QUEST_STATUS_INCOMPLETE) ||
            (pPlayer->GetQuestStatus(QUEST_AMONG_THECHAMPIONS_A) == QUEST_STATUS_INCOMPLETE)  ||
            (pPlayer->GetQuestStatus(QUEST_AMONG_THECHAMPIONS_A2) == QUEST_STATUS_INCOMPLETE)) &&
            (pPlayer->HasAura(RIDE_VEHICLE)) &&
            (pPlayer->HasAura(PLAYER_ON_TOURNAMENT_MOUNT)) &&
            (pPlayer->HasAura(LANCE_EQUIPPED)))

        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VALIANT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
            return true;
        }
        return false;
    }*/

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 /*action*/)
    {
        if (!player)
            return false;

        //player->PlayerTalkClass->ClearMenus();

        //player->CLOSE_GOSSIP_MENU();
        creature->setFaction(14);
        creature->SetReactState(REACT_AGGRESSIVE);
        creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE  | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
        creature->Say(urand(0,1) ? SAY_START_1 : SAY_START_2, LANG_UNIVERSAL, 0);
        creature->AI()->AttackStart(player->GetVehicleCreatureBase());
        creature->AddThreat(player, 0.0f);
        creature->SetInCombatWith(player);

        return true;
    }        
            
    CreatureAI* GetAI(Creature* creature) const
    {
        return new among_the_championsAI (creature);
    }
};

void AddSC_argent_tournamet_custom()
{
	new the_grand_melee();
    new among_the_champions();
}