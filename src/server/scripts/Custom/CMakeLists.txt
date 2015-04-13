# Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# file(GLOB_RECURSE sources_Custom Custom/*.cpp Custom/*.h)

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Custom/custom.cpp
  Custom/duel_reset.cpp
  Custom/hourglass_of_eternity.cpp
  Custom/skytalon_molts.cpp
  Custom/Transmogrification.h
  Custom/Transmogrification.cpp
  Custom/Transmogrifier.cpp
  Custom/npc_teleporter.cpp
  Custom/chat_censure.cpp
  Custom/WorldEvents/boss_apothecary_trio.cpp
  Custom/reward_lvl.cpp
  Custom/player_awards_for_time.cpp
  Custom/argent_tournament.cpp

#  ${sources_Custom}
)

message("  -> Prepared: Custom")
