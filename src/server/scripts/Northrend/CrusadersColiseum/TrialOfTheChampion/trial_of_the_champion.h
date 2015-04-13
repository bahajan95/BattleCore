/*
 * Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

#ifndef DEF_TOC_H
#define DEF_TOC_H

#define DataHeader "TC"

#define ORIENTATION             4.714f

Position const VehicleMove[18] =
{
	// alliance pos
	{ 746.939f, 636.44f, 411.572f },
	{ 713.916f, 618.34f, 411.6f },
	{ 702.543f, 603.127f, 412.391f, 0.287f },
	
	{ 746.939f, 636.44f, 411.572f },
	{ 713.916f, 618.34f, 411.6f },
	{ 701.311f, 629.274f, 412.391f, 6.093f },
	
	{ 746.939f, 636.44f, 411.572f },
	{ 713.916f, 618.34f, 411.6f },
	{ 712.752f, 651.843f, 412.391f, 5.747f },
	
	// Horde pos
	{ 746.939f, 636.44f, 411.572f },
	{ 779.179f, 618.306f, 411.602f },
	{ 792.046f, 637.086f, 412.391f, 3.615f },
	{ 746.939f, 636.44f, 411.572f },
	{ 779.179f, 618.306f, 411.602f },
	{ 779.587f, 654.756f, 412.392f, 4.081f },
	{ 746.939f, 636.44f, 411.572f },
	{ 779.179f, 618.306f, 411.602f },
	{ 795.753f, 618.142f, 412.394f, 3.225f }
};

enum Actions
{
	ACTION_FAST = 0,
	ACTION_GRAND_CHAMPIONS_MOVE_TO_GATE = 1,
	ACTION_GRAND_CHAMPIONS_MOVE = 2,
	ACTION_ARGENT_CHAMPION_DONE = 3,
	ACTION_BLACK_KNIGHT_DEAD = 4,
	ACTION_DESPAWN_CHAMPIONS = 5
};

enum Data
{
    BOSS_GRAND_CHAMPIONS,
    BOSS_ARGENT_CHALLENGE,
    BOSS_BLACK_KNIGHT,
	DATA_GRAND_CHAMPIONS_PHASE,
	DATA_GRAND_CHAMPIONS_MOVEMENT,
    DATA_MOVEMENT_DONE,
    DATA_LESSER_CHAMPIONS_DEFEATED,
    DATA_START,
    DATA_IN_POSITION,
    DATA_ARGENT_SOLDIER_DEFEATED,
	DATA_CHANGE_SPEED,
	DATA_RESET_SPEED
};

enum Data64
{
    DATA_ANNOUNCER,
    DATA_MAIN_GATE,
	DATA_MAIN_GATE_DOOR,
	
	DATA_TRALL,
	DATA_GARROSH,
	DATA_KING,
	DATA_LADY,
	DATA_HIGHLORD,

	DATA_GRAND_CHAMPION_VEHICLE,
    DATA_GRAND_CHAMPION_VEHICLE_1,
    DATA_GRAND_CHAMPION_VEHICLE_2,
    DATA_GRAND_CHAMPION_VEHICLE_3,
	DATA_GRAND_CHAMPION_VEHICLE_R, // Remove Vehicle list

    DATA_GRAND_CHAMPION_1,
    DATA_GRAND_CHAMPION_2,
    DATA_GRAND_CHAMPION_3,
	
	DATA_ARGENT_CHAMPION,

	DATA_BLACK_KNIGHT,
	
	DATA_SPECTATOR_HORDE,
	DATA_SPECTATOR_ALLIANCE,
	DATA_SPECTATOR_BLOOD_ELVES,
	DATA_SPECTATOR_TAUREN,
	DATA_SPECTATOR_TROLL,
	DATA_SPECTATOR_ORCS,
	DATA_SPECTATOR_FORSAKEN,
	DATA_SPECTATOR_DWARVES,
	DATA_SPECTATOR_GNOMES,
	DATA_SPECTATOR_HUMANS,
	DATA_SPECTATOR_NIGHT_ELVES,
	DATA_SPECTATOR_DRAENEI
};

enum CreatureIds
{
    // Horde Champions
    NPC_MOKRA                    = 35572,
    NPC_ERESSEA                  = 35569,
    NPC_RUNOK                    = 35571,
    NPC_ZULTORE                  = 35570,
    NPC_VISCERI                  = 35617,

    // Alliance Champions
    NPC_JACOB                    = 34705,
    NPC_AMBROSE                  = 34702,
    NPC_COLOSOS                  = 34701,
    NPC_JAELYNE                  = 34657,
    NPC_LANA                     = 34703,

	// Crusader Champions
    NPC_EADRIC                   = 35119,
    NPC_PALETRESS                = 34928,

	// Crusader mobs
    NPC_ARGENT_LIGHWIELDER       = 35309,
    NPC_ARGENT_MONK              = 35305,
    NPC_PRIESTESS                = 35307,

	// Black Knight
    NPC_BLACK_KNIGHT             = 35451,

	// Announcer
    NPC_JAEREN                   = 35004,
    NPC_ARELAS                   = 35005,
	
	NPC_TRALL                    = 34994, 
    NPC_GARROSH                  = 34995, 
    NPC_KING                     = 34990, 
    NPC_LADY                     = 34992, 
    NPC_HIGHLORD                 = 34996
};

enum Spectators
{
	SPECTATOR_HORDE 			 = 34883,
	SPECTATOR_ALLIANCE 			 = 34887,
	SPECTATOR_BLOOD_ELVES 	 	 = 34904, 
	SPECTATOR_TAUREN			 = 34903,
	SPECTATOR_TROLL 			 = 34902,
	SPECTATOR_ORCS 				 = 34901, 
	SPECTATOR_FORSAKEN 			 = 34905,
	SPECTATOR_DWARVES 			 = 34906, 
	SPECTATOR_GNOMES 			 = 34910, 
	SPECTATOR_HUMANS 			 = 34900, 
	SPECTATOR_NIGHT_ELVES 		 = 34909,
	SPECTATOR_DRAENEI 			 = 34908
};

enum GameObjects
{
    GO_MAIN_GATE                = 195647,
	GO_MAIN_GATE_DOOR           = 195650,

    GO_CHAMPIONS_LOOT           = 195709,
    GO_CHAMPIONS_LOOT_H         = 195710,

    GO_EADRIC_LOOT              = 195374,
    GO_EADRIC_LOOT_H            = 195375,

    GO_PALETRESS_LOOT           = 195323,
    GO_PALETRESS_LOOT_H         = 195324
};

enum Vehicles
{
    //Grand Champions Alliance Vehicles
    VEHICLE_MARSHAL_JACOB_ALERIUS_MOUNT             = 35637,
    VEHICLE_AMBROSE_BOLTSPARK_MOUNT                 = 35633,
    VEHICLE_COLOSOS_MOUNT                           = 35768,
    VEHICLE_EVENSONG_MOUNT                          = 34658,
    VEHICLE_LANA_STOUTHAMMER_MOUNT                  = 35636,
    //Faction Champions (ALLIANCE)
    VEHICLE_DARNASSIA_NIGHTSABER                    = 35332,
    VEHICLE_EXODAR_ELEKK                            = 35330,
    VEHICLE_STORMWIND_STEED                         = 35328,
    VEHICLE_GNOMEREGAN_MECHANOSTRIDER               = 35331,
    VEHICLE_IRONFORGE_RAM                           = 35329,
    //Grand Champions Horde Vehicles
    VEHICLE_MOKRA_SKILLCRUSHER_MOUNT                = 35638,
    VEHICLE_ERESSEA_DAWNSINGER_MOUNT                = 35635,
    VEHICLE_RUNOK_WILDMANE_MOUNT                    = 35640,
    VEHICLE_ZUL_TORE_MOUNT                          = 35641,
    VEHICLE_DEATHSTALKER_VESCERI_MOUNT              = 35634,
    //Faction Champions (HORDE)
    VEHICLE_FORSAKE_WARHORSE                        = 35327,
    VEHICLE_THUNDER_BLUFF_KODO                      = 35325,
    VEHICLE_ORGRIMMAR_WOLF                          = 35314,
    VEHICLE_SILVERMOON_HAWKSTRIDER                  = 35326,
    VEHICLE_DARKSPEAR_RAPTOR                        = 35323,

    VEHICLE_ARGENT_WARHORSE                         = 35644,
    VEHICLE_ARGENT_BATTLEWORG                       = 36558,

    VEHICLE_BLACK_KNIGHT                            = 35491
};

#endif
