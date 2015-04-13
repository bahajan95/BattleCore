#include "ScriptPCH.h"

/* This is where custom scripts' loading functions should be declared. */
void AddSC_DuelReset(); //For Duel Reset
void AddSC_hourglass_of_eternity();
void AddSC_skytalon_molts();
void AddSC_PWS_Transmogrification(); //For Transmogrification
void AddSC_CS_Transmogrification(); //For Transmogrification
void AddSC_TeLe_gossip_codebox();
void AddSC_System_Censure();
void AddSC_boss_apothecary_trio();
void AddSC_rewarded_player();
void AddSC_AwardsForTime();
void AddSC_argent_tournamet_custom();

/* This is where custom scripts should be added. */
void AddSC_custom()
{
    AddSC_DuelReset(); //For Duel Reset
    AddSC_hourglass_of_eternity();
    AddSC_skytalon_molts();
    AddSC_PWS_Transmogrification(); //For Transmogrification
    AddSC_CS_Transmogrification(); //For Transmogrification
    AddSC_TeLe_gossip_codebox();
    AddSC_System_Censure();
	AddSC_boss_apothecary_trio();
	AddSC_rewarded_player();
	AddSC_AwardsForTime();
    AddSC_argent_tournamet_custom();
}
