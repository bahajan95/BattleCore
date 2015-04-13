-- Fix leeeroy jenkins
UPDATE `gameobject_template` SET data7 = 2 WHERE entry = "175124";
DELETE FROM `gameobject_template` WHERE entry = "175622";
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, 
`flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, 
`data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, 
`data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `AIName`, `ScriptName`, 
`VerifiedBuild`) VALUES('175622','22','0','Rookery Whelp Summoner','','','','0','4','1','0','0','0','0','0','0','15745','1','0','0','0','0','-1','0',
'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','','1');
UPDATE `creature_template` SET unit_flags = "8" WHERE entry = "10161";

-- CrossBg
UPDATE creature_template SET faction = 1 WHERE entry IN (4255,4257,5134,5135,5139,11948,11949,11997,12050,12096,12127,13086,13096,13138,13216,13257,13296,13298,13299,13317,13318,13319,13320,13326,13327,13331,13422,13437,13438,13439,13442,13443,13447,13546,13576,13577,13598,13617,13797,14187,14188,14284,14762,14763,14765,14766,14768,14769,12047,13396,13358,13080,13078);
UPDATE creature_template SET faction = 2 WHERE entry IN (2225,3343,3625,10364,10367,11946,11947,11998,12051,12052,12053,12097,12121,12122,13088,13089,13097,13137,13140,13143,13144,13145,13146,13147,13152,13153,13154,13176,13179,13180,13181,13218,13236,13284,13316,13359,13377,13397,13425,13428,13441,13448,13536,13539,13545,13597,13616,13618,13798,14185,14186,14282,14285,14772,14773,14774,14775,14776,14777,13332,13099,13079);

-- Fix item 44430
delete from broadcast_text where id in (77900, 77901, 77902);
delete from locales_broadcast_text where id in (77900, 77901, 77902);
delete from spell_script_names where spell_id = 60476;
INSERT INTO `locales_broadcast_text` VALUES ('77900', null, null, null, null, null, null, null, 'небрежно подкидывает в воздух свою |cFF0070DD|Hitem:44430|h[Титановая печать Даларана]|h|r!', null, null, null, null, null, null, null, 'небрежно подкидывает в воздух свою |cFF0070DD|Hitem:44430|h[Титановая печать Даларана]|h|r!', '18019');
INSERT INTO `locales_broadcast_text` VALUES ('77901', null, null, null, null, null, null, null, 'обнаруживает что монета упала орлом!', null, null, null, null, null, null, null, 'обнаруживает что монета упала орлом!', '18019');
INSERT INTO `locales_broadcast_text` VALUES ('77902', null, null, null, null, null, null, null, 'обнаруживает что монета упала решкой!', null, null, null, null, null, null, null, 'обнаруживает что монета упала решкой!', '18019');
INSERT INTO `broadcast_text` VALUES ('77900', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', '0', '18019');
INSERT INTO `broadcast_text` VALUES ('77901', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', '0', '18019');
INSERT INTO `broadcast_text` VALUES ('77902', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', '0', '18019');
INSERT INTO `spell_script_names` VALUES ('60476', 'spell_gen_toss_your_luck');

-- Fix item 46051
UPDATE `spell_proc_event` SET `ppmRate`=0 WHERE `entry`=64999;

-- Fix Event 18223 Realization
UPDATE `item_template` SET `ScriptName` = 'skytalon_molts' WHERE `entry` = 37881;
UPDATE `creature_template` SET `unit_flags` = 33024 WHERE `entry` = 27249;

DELETE FROM `gameobject` WHERE `id`=190033;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`,`VerifiedBuild`) VALUES
(99753, 190033, 571, 0, 0, 1, 1, 2629.2, 8.1333, 26.2631, 0.401426, 0, 0, 0.199368, 0.979925, 25, 0, 1, 0),
(255347, 190033, 571, 0, 0, 1, 1, 2684.44, -3.65769, 2.98284, 2.89276, 0, 0, 0.99227, 0.124097, 300, 0, 1, 0);

-- fix loot oko vechnosti
UPDATE `creature` SET `position_z` = 266.17 WHERE `guid` = 234834;
UPDATE `smart_scripts` SET `target_z` = 300 WHERE `entryorguid` = 32295;

-- fix kalecgos
UPDATE creature_template SET lootid = 24892 WHERE entry = 24850;

-- Fix Lord_Marrowgar
-- 10N loot fix
UPDATE `creature_template` SET `lootid` = 36612 WHERE `entry` = 36612;
UPDATE `creature_template` SET `lootid` = 36855 WHERE `entry` = 36855;
UPDATE `creature_template` SET `lootid` = 37970 WHERE `entry` = 37970;
UPDATE `creature_template` SET `lootid` = 37955 WHERE `entry` = 37955;
UPDATE `creature_template` SET `lootid` = 36627 WHERE `entry` = 36627;
UPDATE `creature_template` SET `lootid` = 36626 WHERE `entry` = 36626;
UPDATE `creature_template` SET `lootid` = 36678 WHERE `entry` = 36678;
UPDATE `creature_template` SET `unit_flags` = 33554432 WHERE `entry` = 36678;
UPDATE `creature_template` SET `lootid` = 36853 WHERE `entry` = 36853;
UPDATE `creature_template` SET `lootid` = 36597 WHERE `entry` = 36597;

-- DBCreature
DELETE FROM `creature_addon` WHERE `guid` IN (26310,54733);
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(26310, 263100),
(54733, 547330);

-- Fix Enchanted Bridle
UPDATE `npc_spellclick_spells` SET `spell_id`='47020' WHERE (`npc_entry`='33519') AND (`spell_id`='63163');
UPDATE `creature_template` SET `exp` = 2, `npcflag` = 16777216, `speed_run` = 1.14286, `RangeAttackTime` = 0, `unit_flags` = 0, `VehicleId` = 369, `InhabitType` = 3 WHERE `entry` = 33519;

DELETE FROM `waypoints` WHERE `entry`=33519;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(33519, 1, 8521.27, 569.596, 552.838, 'Black Knight\'s Gryphon'),
(33519, 2, 8517.86, 579.109, 553.213, 'Black Knight\'s Gryphon'),
(33519, 3, 8513.15, 594.672, 551.213, 'Black Knight\'s Gryphon'),
(33519, 4, 8505.26, 606.557, 550.418, 'Black Knight\'s Gryphon'),
(33519, 5, 8503.02, 628.419, 547.418, 'Black Knight\'s Gryphon'),
(33519, 6, 8480.27, 652.708, 547.418, 'Black Knight\'s Gryphon'),
(33519, 7, 8459.12, 686.143, 547.418, 'Black Knight\'s Gryphon'),
(33519, 8, 8436.8, 713.869, 547.343, 'Black Knight\'s Gryphon'),
(33519, 9, 8405.38, 740.005, 547.418, 'Black Knight\'s Gryphon'),
(33519, 10, 8386.14, 770.601, 547.588, 'Black Knight\'s Gryphon'),
(33519, 11, 8374.3, 802.253, 547.93, 'Black Knight\'s Gryphon'),
(33519, 12, 8374.27, 847.036, 548.043, 'Black Knight\'s Gryphon'),
(33519, 13, 8385.99, 868.988, 548.049, 'Black Knight\'s Gryphon'),
(33519, 14, 8413.03, 867.857, 547.299, 'Black Knight\'s Gryphon'),
(33519, 15, 8452.55, 869.034, 547.299, 'Black Knight\'s Gryphon'),
(33519, 16, 8473.06, 875.201, 547.295, 'Black Knight\'s Gryphon'),
(33519, 17, 8472.28, 912.313, 547.417, 'Black Knight\'s Gryphon'),
(33519, 18, 8479.67, 954.165, 547.33, 'Black Knight\'s Gryphon'),
(33519, 19, 8477.35, 1001.37, 547.337, 'Black Knight\'s Gryphon'),
(33519, 20, 8484.54, 1025.8, 547.462, 'Black Knight\'s Gryphon'),
(33519, 21, 8525.36, 1029.28, 547.418, 'Black Knight\'s Gryphon'),
(33519, 22, 8532.81, 1052.9, 548.168, 'Black Knight\'s Gryphon'),
(33519, 23, 8537.36, 1077.93, 554.579, 'Black Knight\'s Gryphon'),
(33519, 24, 8540.53, 1083.38, 569.683, 'Black Knight\'s Gryphon'),
(33519, 25, 8563.64, 1140.96, 569.683, 'Black Knight\'s Gryphon'),
(33519, 26, 8594.9, 1205.46, 569.683, 'Black Knight\'s Gryphon'),
(33519, 27, 8617.1, 1257.4, 566.183, 'Black Knight\'s Gryphon'),
(33519, 28, 8648.5, 1329.35, 558.019, 'Black Knight\'s Gryphon'),
(33519, 29, 8667.72, 1388.41, 546.188, 'Black Knight\'s Gryphon'),
(33519, 30, 8699.14, 1474.9, 528.22, 'Black Knight\'s Gryphon'),
(33519, 31, 8726.87, 1546.01, 501.774, 'Black Knight\'s Gryphon'),
(33519, 32, 8739.06, 1592.16, 478.551, 'Black Knight\'s Gryphon'),
(33519, 33, 8750.8, 1636.77, 455.08, 'Black Knight\'s Gryphon'),
(33519, 34, 8760.01, 1669.48, 423.221, 'Black Knight\'s Gryphon'),
(33519, 35, 8783.31, 1701.85, 375.887, 'Black Knight\'s Gryphon'),
(33519, 36, 8817.34, 1735.73, 343.332, 'Black Knight\'s Gryphon'),
(33519, 37, 8882.32, 1789.75, 301.581, 'Black Knight\'s Gryphon'),
(33519, 38, 8958.6, 1841.81, 259.914, 'Black Knight\'s Gryphon'),
(33519, 39, 9045.89, 1908.08, 233.414, 'Black Knight\'s Gryphon'),
(33519, 40, 9107.18, 1964.59, 215.97, 'Black Knight\'s Gryphon'),
(33519, 41, 9134.76, 2036.93, 175.193, 'Black Knight\'s Gryphon'),
(33519, 42, 9128.61, 2089.09, 141.359, 'Black Knight\'s Gryphon'),
(33519, 43, 9093.36, 2128.38, 99.3868, 'Black Knight\'s Gryphon'),
(33519, 44, 9050.71, 2123.66, 60.248, 'Black Knight\'s Gryphon');

-- Fix issuse 49
UPDATE `quest_template` SET `RequiredSkillId` = 0 WHERE `Id` = 10965;
UPDATE `quest_template` SET `RequiredSkillId` = 0 WHERE `Id` = 10964;
DELETE FROM `creature` WHERE `id`=22916;
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` = 22916;
UPDATE `smart_scripts` SET  `event_phase_mask`=0 WHERE `entryorguid`=22834 AND `source_type`=0 AND `id`=1;

-- Fix Killcredit29800
UPDATE `creature_template` SET `KillCredit2` = 29800 WHERE `entry` = 29694;

-- Fix mimmiron tram
UPDATE `gameobject_template` SET `flags` = 32, `data2` = 3000, `ScriptName` = 'go_call_tram' WHERE `entry` IN (194914, 194912, 194437);
DELETE FROM gameobject WHERE id = '194437';
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('194437','603','1','1','2306.87','274.237','424.288','1.52255','0','0','0.689847','0.723956','300','0','1');
DELETE FROM gameobject_template WHERE entry = '194438';
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES
('194438','1','8504','Activate Tram','','','','0','32','1','0','0','0','0','0','0','0','0','3000','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','go_call_tram');
DELETE FROM gameobject WHERE id = '194438';
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(194438, 603, 1,1,2306.99, 2589.35, 424.382, 4.71676, 0, 0, 0.705559, -0.708651, 300, 0, 1);

-- Fix npc 12435
-- set not-selectable flag for BlackWing Lair 1-st boss eggs
UPDATE gameobject_template SET flags = 16 WHERE entry = 177807;

-- Fix up5 
-- Fix Issue #17 hide second door
-- Issue #26
DELETE FROM `gameobject` WHERE `id`=194911;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`,`VerifiedBuild`) VALUES
(256, 194911, 603, 0, 0, 3, 17, 1632.02, -182.921, 427.668, 3.14159, 0, 0, 8.74228E-8, 1, -10, 255, 1, 0);

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39048;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39048 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(39048, 0, 0, 0, 1, 0, 100, 1, 100, 100, 0, 0, 4, 10896, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "play sound Lament_of_the_Highborne");

-- Fix Zulg
REPLACE INTO `gameobject` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
('186304','568','0','0','1','1','123.256','914.421','34.1441','-1.57952','0','0','0.99999','0.004363','180','100','1','0');
DELETE FROM `creature` WHERE `id` = '24239';
REPLACE INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
('24239','568','0','0','1','1','22332','1','117.883','921.279','33.8883','1.5696','259200','0','0','573615','67740','0','0','0','0','0');
UPDATE `creature_equip_template` SET `itemEntry1`='33494' WHERE `entry`='24239';
UPDATE `gameobject_template` SET `faction`='0' WHERE `entry`='186305';

-- Fix floating stealth creatures
DELETE FROM `creature_addon` WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id` = 2586);
DELETE FROM `creature_template_addon` WHERE `entry`=2586;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(2586, 0, 0, 131072, 1, 0, "");
UPDATE `creature_template_addon` SET `bytes1`=131072, `bytes2`=1 WHERE `entry` IN ( 6035, 22060, 18116, 16928, 16170, 11792, 6886, 4798, 2522, 25484, 4850, 1040, 579, 4834, 215, 1713, 938, 768, 17949);
DELETE FROM `creature_addon` WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id` = 11792);
DELETE FROM `creature_addon` WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id` = 4798);
DELETE FROM `creature_addon` WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id` = 2242);
DELETE FROM `creature_template_addon` WHERE `entry`=2242;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(2242, 0, 0, 131072, 1, 0, "");
DELETE FROM `creature_addon` WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id` = 2246);
DELETE FROM `creature_template_addon` WHERE `entry`=2246;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(2246, 0, 0, 131072, 1, 0, "");
DELETE FROM `creature_addon` WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id` = 2926);
DELETE FROM `creature_template_addon` WHERE `entry`=2926;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(2926, 0, 0, 131072, 1, 0, "");
DELETE FROM `creature_addon` WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id` = 7110);
DELETE FROM `creature_template_addon` WHERE `entry`=7110;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(7110, 0, 0, 131072, 1, 0, "");

-- Fix npc 14517 
UPDATE `creature_template` SET `InhabitType` = 5 WHERE `entry` = 14517;

-- Fix npc 24239
UPDATE creature SET equipment_id = 99999 WHERE id = 24239;
REPLACE INTO `creature_equip_template` (`entry`, `itementry1`, `itementry2`, `itementry3`) VALUES (99999, 22332, 0, 0);

-- Fix Leatherworking skill
UPDATE `npc_trainer` SET `spell`=2154 WHERE `entry`=201029 AND `spell`=3104;

-- Fix npc 17592
UPDATE creature_template SET InhabitType=4, unit_flags=64 WHERE Entry=17592;
DELETE FROM `smart_scripts` WHERE `entryorguid`=17592 AND `source_type`=0 AND `id`IN(5, 6, 7);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(17592, 0, 5, 6, 40, 0, 100, 0, 10, 17592, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Razormaw - On Waypoint 10 Reached - Set Home Position'),
(17592, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Razormaw - On Waypoint 10 Reached - Set Agressive'),
(17592, 0, 7, 0, 11, 0, 100, 0, 0, 0, 0, 0, 18, 256, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Razormaw - On Respawn - Add unit_flag');

-- Fix npc 21318
DELETE FROM `creature` WHERE `id`=21318;
INSERT INTO `creature` (`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`,`VerifiedBuild`) VALUES
(21318, 530, 0, 0, 1, 1, 0, 0, -3800.38, 2601.1, 90.143, 5.48163, 180, 0, 0, 6986, 0, 0, 0, 0, 0, 0);
UPDATE `creature_template` SET `gossip_menu_id` = 8287 WHERE `entry` = 21318;
DELETE FROM `creature_template_addon` WHERE (`entry`=21318);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(21318, 0, 0, 0, 0, 0, 49414);
DELETE FROM `spell_area` WHERE `spell`=49416 AND `area`=3752;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
('49416', '3752', '10528', '0', '0', '0', '2', '1', '64', '0');
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 21318;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=21318 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(21318, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, "txt");
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 21292;
DELETE FROM `creature_text` WHERE `entry`=21318 AND `groupid`=0;
INSERT INTO `creature_text` (`entry`, `groupid`, `type`, `BroadcastTextId`) VALUES ('21318', '0', '12', '18993');
DELETE FROM `smart_scripts` WHERE (`entryorguid`=21292 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(21292, 0, 0, 0, 20, 0, 100, 0, 10528, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 21318, 10, 0, 0, 0, 0, 0, "init txt");

-- Fix npc 25038(Felmyst_Sunwell_Boss)
UPDATE `creature_template` SET `dynamicflags`='8' WHERE `entry`='25038';
UPDATE `creature_template` SET `flags_extra`='1' WHERE `entry`='25038';
UPDATE `creature_template` SET `mechanic_immune_mask`='751796095' WHERE `entry`='25038';

-- Fix npc 32404
UPDATE `creature` SET `phaseMask` = 3 WHERE `guid` = 62066;

-- Fix npc 35498 
UPDATE `creature_template` SET `faction`=2007 WHERE `entry` IN (35496,35498);
UPDATE `creature` SET `position_x`=5957.267, `position_y`=566.4926 WHERE `guid`=116668 AND `id` = 29657;

-- Fix npc 37552
UPDATE `creature_template` SET `KillCredit2` = 37601, `npcflag` = 1, `gossip_menu_id` = 37552, `unit_flags` = 537166592, `AIName` = 'SmartAI' WHERE `entry` = 37552;
DELETE FROM `creature_template_addon` WHERE (`entry`=37552);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (37552, 0, 0, 0, 0, 0, 29266);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=37552 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=37552 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(37552, 0, 0, 1, 62, 0, 100, 0, 37552, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Thalorien Dawnseeker - On gossip option 0 select - Close gossip"),
(37552, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 85, 70265, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Thalorien Dawnseeker - On gossip option 0 select - Player cast credit on self"),
(37552, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 12, 37205, 2, 120000, 0, 0, 0, 8, 0, 0, 0, 11792, -7065.79, 25.94, 5.009, "Thalorien Dawnseeker - On gossip option 0 select - summon ghost"),
(37552, 0, 3, 1, 62, 0, 100, 0, 37552, 1, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Thalorien Dawnseeker - On gossip option 1 select - Close gossip");
DELETE FROM `gossip_menu_option` WHERE `menu_id`='37552';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
('37552', '0', '0', 'Examine remains.', '37149', '1', '1', '0', '0', '0', '0', '', '0'),
('37552', '1', '0', 'Examine remains.', '37149', '1', '1', '0', '0', '0', '0', '', '0');
DELETE FROM `smart_scripts` WHERE (`entryorguid`=37205 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(37205, 0, 3, 0, 1, 0, 100, 1, 14000, 14000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "start intro 3"),
(37205, 0, 2, 0, 1, 0, 100, 1, 10000, 10000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "start intro 3"),
(37205, 0, 1, 0, 1, 0, 100, 1, 5000, 5000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "start intro 2"),
(37205, 0, 0, 0, 1, 0, 100, 1, 10, 10, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "start intro 1");
DELETE FROM `creature_text` WHERE `entry`=37205 AND `groupid`=0;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `probability`, `sound`, `BroadcastTextId`, `comment`) VALUES 
('37205', '0', '0', 'I... I wasn\'t meant to survive this attack.', '12', '100', '16775', '37196', 'Thalorien Dawnseeker txt 1'),
('37205', '1', '0', 'Why has this happened? Why have you come here?', '12', '100', '16776', '37197', 'Thalorien Dawnseeker txt 2'),
('37205', '2', '0', 'It\'s Quel\'Delar! You possess the sword!', '12', '100', '16777', '37198', 'Thalorien Dawnseeker txt 3'),
('37205', '3', '0', 'I don\'t know how, but the blade has chosen you to be its new wielder. Take it with my blessing, and wield it against the Scourge as I once did.', '12', '100', '16778', '37199', 'Thalorien Dawnseeker txt 4');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=37552;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
('15', '37552', '1', '0', '0', '9', '0', '24563', '0', '0', '0', '0', '0', '', ''),
('15', '37552', '0', '0', '0', '9', '0', '24535', '0', '0', '0', '0', '0', '', '');

-- Fix npc 39712
DELETE FROM `smart_scripts` WHERE `entryorguid`= 39712 AND `source_type`=0 AND `id` IN (6, 7);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(39712, 0, 6, 7, 63, 0, 100, 0, 0, 0, 0, 0, 11, 74206, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Tinker Mekkatorque - Just created - cast spell'),
(39712, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 44816, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Tinker Mekkatorque - Just created - cast spell');

-- Fix npc 15516
UPDATE `creature_template` SET `BaseAttackTime` = 1200 WHERE `entry` = 15516;

-- Fix Add missing quest taker
DELETE FROM `creature` WHERE `id`=29077;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`,`VerifiedBuild`) VALUES
(214779, 29077, 609, 0, 0, 1, 68, 0, 0, 1320.41, -6124.84, 14.6075, 2.05698, 300, 0, 0, 96100, 19854, 0, 0, 0, 0, 0);

-- Fix Up4 
DELETE FROM `creature` WHERE `id`=15083;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`,`VerifiedBuild`) VALUES
(220422, 15083, 309, 0, 0, 1, 1, 0, 1, -11900.9, -1905.93, 65.3385, 0.962286, 259200, 0, 0, 266500, 5240, 0, 0, 0, 0, 0);

UPDATE `disables` SET `flags`='0' WHERE (`sourceType`='2') AND (`entry`='650');

-- Quest FiX 

-- Fix confliting guid 
-- Quest - Iron Rune Constructs and You: Collecting Data
SET @GUID := 49220;
SET @SUMMON := 49986;
SET @GOLEM := 24821;
SET @BENCH := 186958;
DELETE FROM `spell_target_position` WHERE `id` in (49988);
INSERT INTO `spell_target_position` (`id`,`target_map`,`target_position_x`,`target_position_y`,`target_position_z`,`target_orientation`) VALUES
(49988, 571, 478.951782, -5941.529297, 308.749969, 0.419872);
UPDATE `creature_template` SET `spell1`=44550, `AIName`='SmartAI' WHERE `entry`=@GOLEM;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GOLEM AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@BENCH AND `source_type`=1 AND `id` IN (2,3);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@BENCH,1,2,3,62,0,100,0,9024,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Work Bench - Gossip select - Close gossip'),
(@BENCH,1,3,0,61,0,100,0,0,0,0,0,85,@SUMMON,2,0,0,0,0,7,0,0,0,0,0,0,0,'Work Bench - Gossip select - Summon Iron Rune Construct');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=44550;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 44550, 0, 31, 3, 24820, 0, 0, '', 'Collect Data target');
DELETE FROM `creature` WHERE `id`=24820;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`) VALUES
(@GUID, 24820, 571, 1, 1, 466.754089, -5921.273926, 309.139404, 0.751123, 120);

-- fix quest 10540
DELETE FROM `creature` WHERE `id`=21292;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`,`VerifiedBuild`) VALUES
(84607, 21292, 530, 0, 0, 1, 1, 0, 0, -3795.83, 2595.23, 94.1175, 4.79965, 120, 0, 0, 6986, 0, 0, 0, 0, 0, 0);

DELETE FROM `creature` WHERE `id`=21292;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`,`VerifiedBuild`) VALUES
(84607, 21292, 530, 0, 0, 1, 1, 0, 0, -3795.83, 2595.23, 94.1175, 4.79965, 120, 0, 0, 6986, 0, 0, 0, 0, 0, 0);

-- fix hellscreams Vigil
UPDATE `quest_template` SET `PrevQuestId` = 10172, `ExclusiveGroup` = 11585 WHERE `Id` = 11586;
UPDATE `quest_template` SET `ExclusiveGroup` = 11585 WHERE `Id` = 11585;
UPDATE `locales_quest` SET `OfferRewardText_loc8` = 'Не думай, что я забыл, что ты сделал для моего народа в Награнде, $N. Адский Крик ничего не забывает.$BС тех пор я в долгу у тебя, и поэтому сейчас я даю тебе этот шанс: беги. Покинь это место и не оглядывайся.$BВозвращайся домой и молись за тех, кто погибнет.' WHERE `Id` = 11586;
UPDATE `locales_quest` SET `OfferRewardText_loc8` = 'Герой Орды, ты?$B$B<Гаррош обнюхивает воздух вокруг вас.>$B$BСтрахом пахнет…$B$B<Гаррош презрительно сплевывает.>$B$BТы долго не продержишься. ' WHERE `Id` = 11585;

-- fix purification of queldelar
UPDATE `creature_template` SET `gossip_menu_id` = 37523, `npcflag` = 1, `AIName` = 'SmartAI' WHERE `entry` = 37523;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=37523 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(37523, 0, 0, 0, 62, 0, 100, 0, 37523, 0, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Script  for http://ru.wowhead.com/npc=37523"),
(37523, 0, 1, 0, 62, 0, 100, 0, 37523, 1, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Script  for http://ru.wowhead.com/npc=37523"),
(37523, 0, 2, 0, 62, 0, 100, 0, 37523, 2, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Script  for http://ru.wowhead.com/npc=37523"),
(37523, 0, 3, 0, 62, 0, 100, 0, 37523, 3, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Script  for http://ru.wowhead.com/npc=37523"),
(37523, 0, 4, 0, 62, 0, 100, 0, 37523, 4, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Script  for http://ru.wowhead.com/npc=37523"),
(37523, 0, 5, 0, 62, 0, 100, 0, 37523, 5, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Script  for http://ru.wowhead.com/npc=37523");

DELETE FROM `gossip_menu_option` WHERE `menu_id`=37523;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
(37523, 0, 0, 'I\'m ready to enter the Sunwell.', 37806, 1, 1, 0, 0, 0, 0, NULL, 0),
(37523, 1, 0, 'I\'m ready to enter the Sunwell.', 37806, 1, 1, 0, 0, 0, 0, NULL, 0),
(37523, 2, 0, 'I\'m ready to enter the Sunwell.', 37806, 1, 1, 0, 0, 0, 0, NULL, 0),
(37523, 3, 0, 'I\'m ready to enter the Sunwell.', 37806, 1, 1, 0, 0, 0, 0, NULL, 0),
(37523, 4, 0, 'I\'m ready to enter the Sunwell.', 37806, 1, 1, 0, 0, 0, 0, NULL, 0),
(37523, 5, 0, 'I\'m ready to enter the Sunwell.', 37806, 1, 1, 0, 0, 0, 0, NULL, 0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=37523;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 37523, 5, 0, 0, 9, 0, 24564, 0, 0, 0, 0, 0, '', NULL),
(15, 37523, 4, 0, 0, 9, 0, 24594, 0, 0, 0, 0, 0, '', NULL),
(15, 37523, 3, 0, 0, 9, 0, 24596, 0, 0, 0, 0, 0, '', NULL),
(15, 37523, 2, 0, 0, 9, 0, 24598, 0, 0, 0, 0, 0, '', NULL),
(15, 37523, 1, 0, 0, 9, 0, 24553, 0, 0, 0, 0, 0, '', NULL),
(15, 37523, 0, 0, 0, 9, 0, 24595, 0, 0, 0, 0, 0, '', NULL);

DELETE FROM `spell_target_position` WHERE `id`='70746';
INSERT INTO `spell_target_position`(`id`,`target_map`,`target_position_x` ,`target_position_y`,`target_position_z`,`target_orientation`) VALUES
('70746', '580', '1788.911865', '648.928284', '71.204185', '2.171664');

DELETE FROM `event_scripts` WHERE `id`=22833;
INSERT INTO `event_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES 
('22833', '0', '10', '37745', '15000', '0', '1692.225', '615.916', '27.935', '0.927');

DELETE FROM `smart_scripts` WHERE (`entryorguid`=37745 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(37745, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 11, 72796, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "sparks"),
(37745, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 70, 60, 0, 0, 0, 0, 0, 15, 201794, 10, 0, 0, 0, 0, 0, "respawn queldelar loot");

DELETE FROM `gameobject` WHERE `id`=201794;
INSERT INTO `gameobject` (`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`,`VerifiedBuild`) VALUES
(201794, 580, 0, 0, 15, 65535, 1693.24, 616.182, 29.4822, 1.12974, 0, 0, 0.535305, 0.844659, -10, 0, 1, 0);
DELETE FROM `gameobject` WHERE `id`=201796;
INSERT INTO `gameobject` (`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`,`VerifiedBuild`) VALUES
(201796, 580, 0, 0, 15, 65535, 1698.81, 627.657, 27.5464, 0.862705, 0, 0, 0.4181, 0.908401, 300, 0, 1, 0);

UPDATE `quest_template` SET `Type` = 62, `Flags` = 128 WHERE `Id` IN (24553, 24564, 24594, 24595, 24596, 24598);

DELETE FROM `spell_area` WHERE `spell`=70193;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
('70193', '4075', '24553', '0', '0', '0', '2', '1', '8', '0'),
('70193', '4075', '24564', '0', '0', '0', '2', '1', '8', '0'),
('70193', '4075', '24594', '0', '0', '0', '2', '1', '8', '0'),
('70193', '4075', '24595', '0', '0', '0', '2', '1', '8', '0'),
('70193', '4075', '24596', '0', '0', '0', '2', '1', '8', '0'),
('70193', '4075', '24598', '0', '0', '0', '2', '1', '8', '0');

-- fix quest 272
UPDATE quest_poi_points SET x = '-10173', y = '2391' WHERE questId = 272 AND id = 2;
UPDATE quest_poi SET worldmapareaid=39 WHERE questId = 272 AND id = 2;

-- fix quest 1789
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=20 AND `SourceEntry`=1789;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(20, 0, 1789, 0, 9, 1783, 0, 0, 0, '', 'Show the quest if 1783 is taken');

-- fix quest 10344
DELETE FROM `smart_scripts` WHERE `entryorguid`=20234 AND `source_type`=0 AND `id`=3;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(20234,0,3,0,19,0,100,0,10344,0,0,0,11,35237,0,0,0,0,0,7,0,0,0,0,0,0,0,"Runetog Wildhammer - On Quest accept - Cast spell");

-- fix quest 10438
UPDATE `gameobject` SET `position_z`=402.410004 WHERE `guid`=99956;

-- fix quest 10935
UPDATE `creature_template` SET `gossip_menu_id` = 8539, `AIName` = 'SmartAI' WHERE `entry` = 22431;
DELETE FROM `gossip_menu_option` WHERE `menu_id`=8539;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
('8539', '0', '0', 'I am ready, Anchorite.  Let us begin the exorcism.', '20396', '1', '1', '0', '0', '0', '0', '', '0');
UPDATE `creature_template` SET `gossip_menu_id` = 8554, `InhabitType` = 7, `AIName` = 'SmartAI' WHERE `entry` = 22432;

DELETE FROM `creature_text` WHERE `entry`='22431';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
('22431', '0', '0', 'It is time.  The rite of exorcism will now commence...', '12', '0', '100', '0', '0', '0', '20400', '0', 'Anchorite Barada'),
('22431', '1', '0', 'Prepare yourself.  Do not allow the ritual to be interrupted or we may lose our patient...', '12', '0', '100', '0', '0', '0', '20401', '0', 'Anchorite Barada'),
('22431', '2', '0', 'Back, foul beings of darkness!  You have no power here!', '12', '0', '100', '0', '0', '0', '20404', '0', 'Anchorite Barada'),
('22431', '3', '0', 'I... must not...falter!', '12', '0', '100', '0', '0', '0', '20407', '0', 'Anchorite Barada'),
('22431', '3', '1', 'Be cleansed with Light, human!  Let not the demonic corruption overwhelm you.', '12', '0', '100', '0', '0', '0', '20403', '0', 'Anchorite Barada'),
('22431', '3', '2', 'I will tear your soul into morsels and slow roast them over demon fire!', '12', '0', '100', '0', '0', '0', '20417', '0', 'Anchorite Barada'),
('22431', '4', '0', 'Back!  I cast you back... corrupter of faith!  Author of pain!  Do not return, or suffer the same fate as you did here today!', '12', '0', '100', '0', '0', '0', '20419', '0', 'Anchorite Barada');

DELETE FROM `creature_text` WHERE `entry`='22432';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
('22432', '0', '0', 'Keep away. The fool is mine.', '12', '0', '100', '0', '0', '0', '20402', '0', 'Colonel Jules'),
('22432', '1', '0', 'No!  Not yet!  This soul is ours!', '12', '0', '100', '0', '0', '0', '20412', '0', 'Colonel Jules');

DELETE FROM `waypoints` WHERE `entry`=22432;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(22432, 0, -713.532, 2750.65, 104.186, ''),
(22432, 1, -713.897, 2746.35, 104.971, ''),
(22432, 2, -713.167, 2744.27, 104.861, ''),
(22432, 3, -710.41, 2741.56, 104.641, ''),
(22432, 4, -706.938, 2744.21, 104.421, ''),
(22432, 5, -707.039, 2748.58, 104.201, ''),
(22432, 6, -707.55, 2750.74, 104.42, ''),
(22432, 7, -711.213, 2751.81, 104.229, ''),
(22432, 8, -714.669, 2747.88, 104.968, ''),
(22432, 9, -714.091, 2743.44, 104.742, ''),
(22432, 10, -710.973, 2741.51, 104.556, ''),
(22432, 11, -709.216, 2743.61, 104.417, ''),
(22432, 12, -706.675, 2746.83, 104.208, ''),
(22432, 13, -706.934, 2750.19, 104.04, ''),
(22432, 14, -707.816, 2753.45, 104.871, ''),
(22432, 15, -711.19, 2755.01, 104.367, ''),
(22432, 16, -712.631, 2751.79, 104.997, ''),
(22432, 17, -713.852, 2748.11, 104.997, ''),
(22432, 18, -712.963, 2743.34, 104.628, ''),
(22432, 19, -709.964, 2743.6, 104.628, ''),
(22432, 20, -706.701, 2745.55, 104.628, ''),
(22432, 21, -705.712, 2750.12, 104.338, ''),
(22432, 22, -710.403, 2750.84, 104.338, ''),
(22432, 23, -715.069, 2748.71, 104.338, ''),
(22432, 24, -712.331, 2744.1, 104.338, ''),
(22432, 25, -709.2, 2741.64, 104.334, ''),
(22432, 26, -707.323, 2746.4, 104.325, ''),
(22432, 27, -707.365, 2750.77, 104.325, ''),
(22432, 28, -709.572, 2751, 104.325, ''),
(22432, 29, -713.678, 2749.01, 104.325, ''),
(22432, 30, -710.756, 2741.44, 104.325, ''),
(22432, 31, -710.755, 2741.48, 105.008, ''),
(22432, 32, -711.107, 2746.76, 104.278, ''),
(22432, 33, -710.911, 2751.93, 103.159, ''),
(22432, 34, -710.728, 2754.86, 102.1, 0);

DELETE FROM `smart_scripts` WHERE (`entryorguid`=22432 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(22432, 0, 0, 1, 38, 0, 100, 0, 1, 1, 1000, 1000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 11, 39294, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 22431, 15, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 3, 7, 61, 0, 100, 0, 0, 0, 0, 0, 11, 55173, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - levitate"),
(22432, 0, 4, 5, 38, 0, 100, 0, 1, 2, 3000, 3000, 11, 39284, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 11, 39295, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 22432, 0, 10935, 120000, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 5, 68, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - levitate"),
(22432, 0, 8, 9, 40, 0, 100, 0, 3, 22432, 0, 0, 12, 22507, 1, 60000, 0, 0, 0, 8, 0, 0, 0, -710.67, 2752.28, 105.01, 4.62, "The Exorcism of Colonel Jules"),
(22432, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 12, 22507, 1, 60000, 0, 0, 0, 8, 0, 0, 0, -710.67, 2752.28, 105.01, 4.62, "The Exorcism of Colonel Jules"),
(22432, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 12, 22507, 1, 60000, 0, 0, 0, 8, 0, 0, 0, -710.67, 2752.28, 105.01, 4.62, "The Exorcism of Colonel Jules"),
(22432, 0, 11, 10, 40, 0, 100, 0, 16, 22432, 0, 0, 12, 22507, 1, 60000, 0, 0, 0, 8, 0, 0, 0, -710.67, 2752.28, 105.01, 4.62, "The Exorcism of Colonel Jules"),
(22432, 0, 12, 10, 40, 0, 100, 0, 27, 22432, 0, 0, 12, 22506, 1, 60000, 0, 0, 0, 18, 10, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 13, 14, 40, 0, 100, 0, 32, 22432, 0, 0, 33, 22432, 0, 0, 0, 0, 0, 18, 10, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 14, 15, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 15, 16, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 0, 0, 0, 0, 0, 11, 22431, 15, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 16, 17, 61, 0, 100, 0, 0, 0, 0, 0, 28, 39284, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 17, 0, 61, 0, 100, 0, 0, 0, 0, 0, 28, 39295, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules"),
(22432, 0, 18, 14, 40, 0, 100, 0, 20, 22432, 0, 0, 33, 22432, 0, 0, 0, 0, 0, 18, 10, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules");

DELETE FROM `smart_scripts` WHERE (`entryorguid`=22431 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(22431, 0, 0, 1, 62, 0, 100, 0, 8539, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - event begin"),
(22431, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, -710.21, 2747.03, 101.59, 1.485, "The Exorcism of Colonel Jules - event begin"),
(22431, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - event begin"),
(22431, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - event begin"),
(22431, 0, 4, 5, 1, 1, 100, 1, 3000, 3000, 0, 0, 66, 4, 0, 0, 0, 0, 0, 19, 22432, 10, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - "),
(22431, 0, 5, 6, 61, 1, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - event begin"),
(22431, 0, 6, 0, 61, 1, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 22432, 15, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - event begin"),
(22431, 0, 7, 8, 38, 1, 100, 0, 1, 1, 2000, 2000, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - "),
(22431, 0, 8, 9, 61, 1, 100, 0, 0, 0, 0, 0, 45, 1, 2, 0, 0, 0, 0, 11, 22432, 15, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - "),
(22431, 0, 9, 0, 61, 1, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - "),
(22431, 0, 10, 0, 1, 2, 100, 0, 10000, 30000, 15000, 29000, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - rnd txt"),
(22431, 0, 11, 12, 38, 2, 100, 0, 1, 0, 10, 10, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - "),
(22431, 0, 12, 0, 61, 2, 100, 0, 0, 0, 10, 10, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "The Exorcism of Colonel Jules - ");

DELETE FROM `smart_scripts` WHERE (`entryorguid`=22507 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(22507, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 11, 39303, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ""),
(22507, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 89, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ""),
(22507, 0, 3, 0, 0, 0, 100, 0, 1000, 5000, 5000, 7000, 11, 39303, 3, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, "");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=8539;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=8554;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
('15', '8539', '0', '0', '3', '9', '0', '10935', '0', '0', '0', '0', '0', '', 'show gossip on quest 10935 taken'),
('15', '8554', '0', '0', '3', '9', '0', '10935', '0', '0', '0', '0', '0', '', 'show gossip on quest 10935 taken');

-- fix quest 11309
-- Anton waypoints
DELETE FROM `creature_addon` WHERE `guid`=117689;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(117689, 1176890, 0, 131072, 1, 0, "");
UPDATE `creature` SET `MovementType`=2 WHERE  `guid`=117689;
DELETE FROM `waypoint_data` WHERE `id`=1176890;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES 
(1176890, 1, 153.249817, -4549.366211, 261.364685, 0, 0, 0, 0, 100, 0),
(1176890, 2, 156.098114, -4532.821289, 258.803101, 0, 0, 0, 0, 100, 0),
(1176890, 3, 156.068008, -4517.755371, 257.193939, 0, 0, 0, 0, 100, 0),
(1176890, 4, 144.178497, -4462.812500, 253.617325, 0, 0, 0, 0, 100, 0),
(1176890, 5, 141.329361, -4455.471191, 253.578766, 0, 0, 0, 0, 100, 0),
(1176890, 6, 125.436966, -4434.860840, 254.323639, 0, 0, 0, 0, 100, 0),
(1176890, 7, 122.155800, -4418.455566, 255.509537, 0, 0, 0, 0, 100, 0),
(1176890, 8, 121.316132, -4389.046387, 257.141205, 0, 0, 0, 0, 100, 0),
(1176890, 9, 124.869438, -4371.796875, 258.335938, 0, 0, 0, 0, 100, 0),
(1176890, 10, 128.642212, -4362.238281, 258.747375, 0, 0, 0, 0, 100, 0),
(1176890, 11, 141.832169, -4345.334473, 257.867676, 0, 0, 0, 0, 100, 0),
(1176890, 12, 150.246857, -4335.993652, 257.498810, 0, 0, 0, 0, 100, 0),
(1176890, 13, 160.376022, -4316.970703, 256.535919, 0, 0, 0, 0, 100, 0),
(1176890, 14, 168.596313, -4308.797363, 254.645386, 0, 0, 0, 0, 100, 0),
(1176890, 15, 178.860077, -4304.438477, 252.472916, 0, 0, 0, 0, 100, 0),
(1176890, 16, 195.836517, -4286.464355, 248.749603, 0, 0, 0, 0, 100, 0),
(1176890, 17, 213.626450, -4276.384766, 248.502441, 0, 0, 0, 0, 100, 0),
(1176890, 18, 238.895004, -4276.655762, 248.606018, 0, 0, 0, 0, 100, 0),
(1176890, 19, 245.764877, -4272.171387, 248.920975, 0, 0, 0, 0, 100, 0),
(1176890, 20, 264.235840, -4250.840332, 250.916733, 0, 0, 0, 0, 100, 0),
(1176890, 21, 282.604492, -4236.683594, 252.033737, 0, 0, 0, 0, 100, 0),
(1176890, 22, 288.971344, -4223.116211, 252.916443, 0, 0, 0, 0, 100, 0),
(1176890, 23, 291.303375, -4196.310547, 254.307571, 0, 0, 0, 0, 100, 0),
(1176890, 24, 294.156342, -4189.324707, 254.992859, 0, 0, 0, 0, 100, 0),
(1176890, 25, 291.303375, -4196.310547, 254.307571, 0, 0, 0, 0, 100, 0),
(1176890, 26, 288.971344, -4223.116211, 252.916443, 0, 0, 0, 0, 100, 0),
(1176890, 27, 282.604492, -4236.683594, 252.033737, 0, 0, 0, 0, 100, 0),
(1176890, 28, 264.235840, -4250.840332, 250.916733, 0, 0, 0, 0, 100, 0),
(1176890, 29, 245.764877, -4272.171387, 248.920975, 0, 0, 0, 0, 100, 0),
(1176890, 30, 238.895004, -4276.655762, 248.606018, 0, 0, 0, 0, 100, 0),
(1176890, 31, 213.626450, -4276.384766, 248.502441, 0, 0, 0, 0, 100, 0),
(1176890, 32, 195.836517, -4286.464355, 248.749603, 0, 0, 0, 0, 100, 0),
(1176890, 33, 178.860077, -4304.438477, 252.472916, 0, 0, 0, 0, 100, 0),
(1176890, 34, 168.596313, -4308.797363, 254.645386, 0, 0, 0, 0, 100, 0),
(1176890, 35, 160.376022, -4316.970703, 256.535919, 0, 0, 0, 0, 100, 0),
(1176890, 36, 150.246857, -4335.993652, 257.498810, 0, 0, 0, 0, 100, 0),
(1176890, 37, 141.832169, -4345.334473, 257.867676, 0, 0, 0, 0, 100, 0),
(1176890, 38, 128.642212, -4362.238281, 258.747375, 0, 0, 0, 0, 100, 0),
(1176890, 39, 124.869438, -4371.796875, 258.335938, 0, 0, 0, 0, 100, 0),
(1176890, 40, 121.316132, -4389.046387, 257.141205, 0, 0, 0, 0, 100, 0),
(1176890, 41, 122.155800, -4418.455566, 255.509537, 0, 0, 0, 0, 100, 0),
(1176890, 42, 125.436966, -4434.860840, 254.323639, 0, 0, 0, 0, 100, 0),
(1176890, 43, 141.329361, -4455.471191, 253.578766, 0, 0, 0, 0, 100, 0),
(1176890, 44, 144.178497, -4462.812500, 253.617325, 0, 0, 0, 0, 100, 0),
(1176890, 45, 156.068008, -4517.755371, 257.193939, 0, 0, 0, 0, 100, 0),
(1176890, 46, 156.098114, -4532.821289, 258.803101, 0, 0, 0, 0, 100, 0),
(1176890, 47, 153.249817, -4549.366211, 261.364685, 0, 0, 0, 0, 100, 0);

-- fix quest 11358
SET @Geant:=24385;
SET @Megalithe:=24381; 

UPDATE `event_scripts` SET `x`=2406.492188 , `y`=-5738.995605, `z`=274.020172 , `o`=0.703918 WHERE `id`=15939;
UPDATE `creature_template` SET `unit_flags`=33600, `AIName`='SmartAI' WHERE `entry` IN (@Geant,@Megalithe);

DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (@Geant,@Megalithe);
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid` IN (@Geant*100,@Megalithe*100);

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@Megalithe, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 80, @Megalithe*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Megalithe - On Just summoned - action list'),
(@Megalithe*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 24385, 7, 0, 0, 0, 0, 8, 0, 0, 0, 2410.138184, -5727.264648, 270.985870, 4.287692, 'Megalithe - action liste -Summon'),
(@Megalithe*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 24385, 7, 0, 0, 0, 0, 8, 0, 0, 0, 2414.860596, -5729.499512, 272.095459, 3.982957, 'Megalithe - action liste -Summon'),
(@Megalithe*100, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 24385, 7, 0, 0, 0, 0, 8, 0, 0, 0, 2417.339844, -5733.230957, 273.028992, 3.603609, 'Megalithe - action liste -Summon'),
(@Megalithe*100, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 24385, 7, 0, 0, 0, 0, 8, 0, 0, 0, 2419.397705, -5738.032227, 274.121246, 3.241538, 'Megalithe - action liste -Summon'),
(@Megalithe*100, 9, 4, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Megalithe - action liste - Talk'),
(@Megalithe*100, 9, 5, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Megalithe - action liste - Talk'),
(@Megalithe*100, 9, 6, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Megalithe - action liste - Talk'),
(@Megalithe*100, 9, 7, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 80, @Geant*100, 0, 0, 0, 0, 0, 11, @Geant, 30, 0, 0, 0, 0, 0, 'Megalithe - action liste - Action List'),
(@Megalithe*100, 9, 8, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 43693, 0, 0, 0, 0, 0, 21, 40, 0, 0, 0, 0, 0, 0, 'Megalithe - action liste - Cast Credit Quest'),
(@Megalithe*100, 9, 9, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Megalithe - action liste - Talk'),
(@Megalithe*100, 9, 10, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Megalithe - action liste - Talk'),
(@Geant*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Geant - action liste - Run off'),
(@Geant*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 2515.453369, -5670.358398, 298.778076, 0.618311, 'Geant - action liste - Gotopos'), 
(@Geant*100, 9, 2, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Geant - action liste - Despawnn');

DELETE FROM `creature_text` WHERE `entry` IN (@Megalithe);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES
(@Megalithe, 0, 0, 'Arise from the earth, my brothers!', 12, 0, 100, 0, 0, 0, 'Megalithe', 23311),
(@Megalithe, 1, 0, 'Our iron masters have a mission for us!', 12, 0, 100, 0, 0, 0, 'Megalithe', 23312),
(@Megalithe, 2, 0, 'Follow me into the mountains to carry out the plan of the masters!', 12, 0, 100, 0, 0, 0, 'Megalithe', 23315),
(@Megalithe, 3, 0, 'We will not fail!', 12, 0, 100, 0, 0, 0, 'Megalithe', 23332);

-- fix quest 11485
-- Quest - Iron Rune Constructs and You: Rocket Jumping
SET @SUMMON := 49985;
SET @GOLEM := 24806;
SET @RUNE := 186956;
SET @BENCH := 186958;
SET @Stanwad := 24717;
SET @Gwendolyn := 24719;
SET @Needlemeyer := 24720;
SET @Walt := 24807;
SET @Lebronski := 24718;
DELETE FROM `spell_target_position` WHERE `id` in (49984);
INSERT INTO `spell_target_position` (`id`,`target_map`,`target_position_x`,`target_position_y`,`target_position_z`,`target_orientation`) VALUES
(49984, 571, 478.951782, -5941.529297, 308.749969, 0.419872);
UPDATE `creature_template` SET `spell1`=44498, `AIName`='SmartAI', `InhabitType`=5 WHERE `entry`=@GOLEM;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Stanwad;
UPDATE `gameobject_template` SET `AIName`='SmartGameObjectAI' WHERE `entry`=@BENCH;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GOLEM AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@Stanwad*100 AND `source_type`=9;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@BENCH AND `source_type`=1 AND `id` IN (0,1);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@BENCH,1,0,1,62,0,100,0,9024,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Work Bench - Gossip select - Close gossip'),
(@BENCH,1,1,0,61,0,100,0,0,0,0,0,85,@SUMMON,2,0,0,0,0,7,0,0,0,0,0,0,0,'Work Bench - Gossip select - Summon Iron Rune Construct'),
(@GOLEM,0,0,1,25,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Iron Rune Construct - Just Summoned - Set phase 1'),
(@GOLEM,0,1,0,61,0,100,0,0,0,0,0,50,186952,60,0,0,0,0,1,0,0,0,0,0,0,0,'Iron Rune Construct - Just Summoned - SummonGob'),
(@GOLEM,0,2,3,8,1,100,0,44498,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Iron Rune Construct - spell hit - Say text'),
(@GOLEM,0,3,4,61,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Iron Rune Construct - spell hit - Set phase 2'),
(@GOLEM,0,4,5,61,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Iron Rune Construct - spell hit - Set fly'),
(@GOLEM,0,5,6,61,0,100,0,0,0,0,0,53,1,@GOLEM,0,0,0,0,1,0,0,0,0,0,0,0,'Iron Rune Construct - spell hit - WP start'),
(@GOLEM,0,6,7,61,0,100,0,0,0,0,0,9,0,0,0,0,0,0,14,65653,@RUNE,0,0,0,0,0,'Iron Rune Construct - spell hit - Activate Gobject'),
(@GOLEM,0,7,0,61,0,100,0,0,0,0,0,80,@Stanwad*100,0,0,0,0,0,19,@Stanwad,30,0,0,0,0,0,'Iron Rune Construct - spell hit - ActionList'),
(@GOLEM,0,8,9,40,0,100,0,5,@GOLEM,0,0,11,44499,0,0,0,0,0,23,0,0,0,0,0,0,0,'Iron Rune Construct - Waypoint reached - cast credit spell'),
(@GOLEM,0,9,10,61,0,100,0,0,0,0,0,22,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'Iron Rune Construct - Waypoint reached - Set phase 3'),
(@GOLEM,0,10,0,61,0,100,0,0,0,0,0,9,0,0,0,0,0,0,14,65654,186957,0,0,0,0,0,'Iron Rune Construct - Just Summoned - Activate gob'),
(@GOLEM,0,11,0,1,4,100,1,7000,7000,0,0,28,46598,0,0,0,0,0,1,0,0,0,0,0,0,0,'Iron Rune Construct - OOC (phase 3) - Remove Vehicle aura'),
(@Stanwad*100,9,0,0,0,0,100,0,3000,3000,0,0,1,0,0,0,0,0,0,19,@Walt,20,0,0,0,0,0,'Stanwad - Action list - TALK'),
(@Stanwad*100,9,1,0,0,0,100,0,3000,3000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stanwad - Action list - TALK'),
(@Stanwad*100,9,2,0,0,0,100,0,12000,12000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stanwad - Action list - TALK'),
(@Stanwad*100,9,3,0,0,0,100,0,1000,1000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stanwad - Action list - TALK'),
(@Stanwad*100,9,4,0,0,0,100,0,6000,6000,0,0,1,0,0,0,0,0,0,19,@Gwendolyn,20,0,0,0,0,0,'Stanwad - Action list - TALK'),
(@Stanwad*100,9,5,0,0,0,100,0,6000,6000,0,0,1,0,0,0,0,0,0,19,@Needlemeyer,20,0,0,0,0,0,'Stanwad - Action list - TALK'),
(@Stanwad*100,9,6,0,0,0,100,0,6000,6000,0,0,1,0,0,0,0,0,0,19,@Lebronski,20,0,0,0,0,0,'Stanwad - Action list - TALK'),
(@Stanwad*100,9,7,0,0,0,100,0,7000,7000,0,0,1,1,0,0,0,0,0,19,@Walt,20,0,0,0,0,0,'Stanwad - Action list - TALK');
DELETE FROM `creature_text` WHERE `entry`IN (@GOLEM, @Walt, @Stanwad, @Gwendolyn, @Needlemeyer, @Lebronski);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`, `BroadcastTextID`) VALUES
(@GOLEM,0,0,"Launching.",12,0,100,0,0,0,'Iron Rune Construct', 23860),
(@Walt,0,0,"Behold my perfect creation!",12,7,100,0,0,0,'Walt', 23873),
(@Stanwad,0,0,"WHOA, WHOA, WHOA! Hold everything fellas!",12,7,100,0,0,0,'Stanwad', 23875),
(@Stanwad,1,0,"Oh dear lords of stone and steel, what... I repeat... WHAT are ya gonna do with that?",12,7,100,0,0,0,'Stanwad', 23878),
(@Stanwad,2,0,"The dwarves all burst out in laughter.",16,7,100,0,0,0,'Stanwad', 23876),
(@Gwendolyn,0,0,"I'm cryin' here! Please, make the funny stop!",12,7,100,0,0,0,'Gwendolyn', 23885),
(@Needlemeyer,0,0,"If only our pappy were alive to see this!",12,0,100,0,0,0,'Needlemeyer', 23889),
(@Lebronski,0,0,"Man, that will never work. The iron dwarves are never gonna fall for that hunk o' junk!",12,7,100,0,0,0,'Lebronski', 23880),
(@Walt,1,0,"You're out of your element, Lebronski! Uncalled for! Those iron dwarves won't know what hit 'em! Now why don't you get back to uncovering the mystery of the gigantic turd on your rug and leave the real scientists to their work! ",12,7,100,0,0,0,'Walt', 23883);
DELETE FROM `waypoints` WHERE `entry`=@GOLEM;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@GOLEM,1, 479.1233, -5941.48, 316.7,'Iron Rune Construct'),
(@GOLEM,2, 479.1461, -5941.515, 339.7554,'Iron Rune Construct'),
(@GOLEM,3, 496.1333, -5940.065, 344.5331,'Iron Rune Construct'),
(@GOLEM,4, 511.516, -5936.729, 339.7554,'Iron Rune Construct'),
(@GOLEM,5, 514.5781, -5936.898, 314.1444,'Iron Rune Construct');

-- fix quest 11489
-- Quest - Iron Rune Constructs and You: Collecting Data
SET @GUID := 21202; -- Set by TC
SET @SUMMON := 49986;
SET @GOLEM := 24821;
SET @BENCH := 186958;
DELETE FROM `spell_target_position` WHERE `id` in (49988);
INSERT INTO `spell_target_position` (`id`,`target_map`,`target_position_x`,`target_position_y`,`target_position_z`,`target_orientation`) VALUES
(49988, 571, 478.951782, -5941.529297, 308.749969, 0.419872);
UPDATE `creature_template` SET `spell1`=44550, `AIName`='SmartAI' WHERE `entry`=@GOLEM;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GOLEM AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@BENCH AND `source_type`=1 AND `id` IN (2,3);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@BENCH,1,2,3,62,0,100,0,9024,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Work Bench - Gossip select - Close gossip'),
(@BENCH,1,3,0,61,0,100,0,0,0,0,0,85,@SUMMON,2,0,0,0,0,7,0,0,0,0,0,0,0,'Work Bench - Gossip select - Summon Iron Rune Construct');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=44550;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 44550, 0, 31, 3, 24820, 0, 0, '', 'Collect Data target');

-- Fix quest 11491

SET @SUMMON := 49989;
SET @GOLEM := 24823;
SET @BENCH := 186958;
SET @Lebronski := 24718;
DELETE FROM `spell_target_position` WHERE `id` IN (49990);
INSERT INTO `spell_target_position` (`id`,`target_map`,`target_position_x`,`target_position_y`,`target_position_z`,`target_orientation`) VALUES
(49990, 571, 478.951782, -5941.529297, 308.749969, 0.419872);
UPDATE `creature_template` SET `spell1`=44562, `AIName`='SmartAI' WHERE `entry`=@GOLEM;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Lebronski;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GOLEM*100 AND `source_type`=9;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@Lebronski AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@Lebronski*100 AND `source_type`=9;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@Lebronski*100+1 AND `source_type`=9;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@BENCH AND `source_type`=1 AND `id` IN (4,5);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@BENCH,1,4,5,62,0,100,0,9024,2,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Work Bench - Gossip select - Close gossip'),
(@BENCH,1,5,0,61,0,100,0,0,0,0,0,85,@SUMMON,2,0,0,0,0,7,0,0,0,0,0,0,0,'Work Bench - Gossip select - Summon Iron Rune Construct'),
(@Lebronski,0,0,0,10,0,100,0,1,5,60000,60000,80,@Lebronski*100,0,0,0,0,0,1,0,0,0,0,0,0,0,'Turd - LOS - Action list'),
(@Lebronski*100,9,0,0,0,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stanwad - Action list - TALK'),
(@Lebronski*100,9,1,0,0,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stanwad - Action list - Set Event phase1'),
(@Lebronski*100,9,2,0,0,0,100,0,0,0,0,0,103,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stanwad - Action list - Root'),
(@Lebronski*100,9,3,0,0,0,100,0,0,0,0,0,66,0,0,0,0,0,0,19,@GOLEM,20,0,0,0,0,0,'Stanwad - Action list - Set Orientation'),
(@Lebronski*100,9,4,0,0,0,100,0,30000,30000,0,0,103,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stanwad - Action list - remove root'),
(@Lebronski,0,1,0,8,1,100,0,44562,0,0,0,80,@Lebronski*100+1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Lebronski - spell hit - action list'),
(@Lebronski*100+1,9,0,0,0,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stanwad - Action list - Set Event phase 0'),
(@Lebronski*100+1,9,1,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,19,@GOLEM,20,0,0,0,0,0,'Stanwad - Action list - TALK'),
(@Lebronski*100+1,9,2,0,0,0,100,0,5000,5000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stanwad - Action list - TALK'),
(@Lebronski*100+1,9,3,0,0,0,100,0,0,0,0,0,80,@GOLEM*100,0,0,0,0,0,19,@GOLEM,20,0,0,0,0,0,'Stanwad - Action list - Action list'),
(@Lebronski*100+1,9,4,0,0,0,100,0,10000,10000,0,0,103,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stanwad - Action list - Pause wp'),
(@GOLEM*100,9,0,0,0,0,100,0,0,0,0,0,11,44569,0,0,0,0,0,23,0,0,0,0,0,0,0,'Stanwad - Action list - Cast Credit');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceGroup`=1 AND `SourceEntry`=@Lebronski;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`, `ErrorTextId`,`ScriptName`,`Comment`) VALUES
(22,1,@Lebronski,0,31,3,24823,0,0,'','event require npc 24823');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=44562;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 44562, 0, 31, 3, 24718, 0, 0, '', 'Bluff target');
DELETE FROM `creature_text` WHERE `entry`IN (@GOLEM);
DELETE FROM `creature_text` WHERE `entry`IN (@Lebronski) AND `groupid` IN (1, 2);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`, `BroadcastTextID`) VALUES
(@GOLEM,0,0,"Model U-9207 Iron Rune Construct does not appreciate your tone of voice. Commencing total annihilation of your rug, Lebronski.",12,0,100,0,0,0,'Iron Rune Construct', 23892),
(@Lebronski,1,0,"What do you think you're doing, man? Lebronski does NOT appreciate you dragging your loose metal parts all over his rug.",12,7,100,0,0,0,'Lebronski', 23890),
(@Lebronski,2,0,"Far out, man. This bucket of bolts might make it after all...",12,7,100,0,0,0,'Lebronski', 23891);

-- fix quest 11681
UPDATE `creature_addon` SET `mount`=0 WHERE `guid`=97508;
/* questgiver */
-- Warmage Anzim SAI
SET @ENTRY := 25356;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,19,0,100,0,11681,0,0,0,85,45883,0,0,0,0,0,7,0,0,0,0,0,0,0,"Warmage Anzim - On Quest 'Rescuing Evanor' Taken - Invoker Cast 'Amber Ledge to Beryl Point'"),
(@ENTRY,0,1,0,61,0,100,0,11681,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Anzim - On Quest 'Rescuing Evanor' Taken - Run Script");
-- Actionlist SAI
SET @ENTRY := 2535600;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,83,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Anzim - On Script - Remove Npc Flag Questgiver"),
(@ENTRY,9,1,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,118574,27888,0,0,0,0,0,"Warmage Anzim - On Script - Set Data 1 1"),
(@ENTRY,9,2,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,107998,25732,0,0,0,0,0,"Warmage Anzim - On Script - Set Data 1 1"),
(@ENTRY,9,3,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,108027,25733,0,0,0,0,0,"Warmage Anzim - On Script - Set Data 1 1"),
(@ENTRY,9,4,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,107602,25727,0,0,0,0,0,"Warmage Anzim - On Script - Set Data 1 1"),
(@ENTRY,9,5,0,0,0,100,0,180000,180000,0,0,82,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Anzim - On Script - Add Npc Flag Questgiver");
/* dragons */
-- Warmage Archus SAI
SET @ENTRY := 27888;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,38,0,100,0,1,1,0,0,53,1,@ENTRY,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Archus - On Data Set 1 1 - Start Waypoint"),
(@ENTRY,0,1,0,61,0,100,0,1,1,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Archus - On Data Set 1 1 - Set Active On"),
(@ENTRY,0,2,0,40,0,100,0,1,@ENTRY,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Moran - On Waypoint 1 Reached - Pause Waypoint");
-- Warmage Preston SAI
SET @ENTRY := 25732;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,38,0,100,0,1,1,0,0,53,1,@ENTRY,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Preston - On Data Set 1 1 - Start Waypoint"),
(@ENTRY,0,1,0,61,0,100,0,1,1,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Preston - On Data Set 1 1 - Set Active On"),
(@ENTRY,0,2,0,40,0,100,0,1,@ENTRY,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Moran - On Waypoint 1 Reached - Pause Waypoint");
-- Warmage Austin SAI
SET @ENTRY := 25733;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,38,0,100,0,1,1,0,0,53,1,@ENTRY,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Austin - On Data Set 1 1 - Start Waypoint"),
(@ENTRY,0,1,0,61,0,100,0,1,1,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Austin - On Data Set 1 1 - Set Active On"),
(@ENTRY,0,2,0,40,0,100,0,1,@ENTRY,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Moran - On Waypoint 1 Reached - Pause Waypoint");
-- Warmage Moran SAI
SET @ENTRY := 25727;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,38,0,100,0,1,1,0,0,53,1,25727,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Moran - On Data Set 1 1 - Start Waypoint"),
(@ENTRY,0,1,0,61,0,100,0,1,1,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Moran - On Data Set 1 1 - Set Active On"),
(@ENTRY,0,2,3,40,0,100,0,1,25727,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warmage Moran - On Waypoint 1 Reached - Pause Waypoint"),
(@ENTRY,0,3,0,61,0,100,0,1,25727,0,0,75,42726,0,0,0,0,0,9,25724,0,100,0,0,0,0,"Warmage Moran - On Waypoint 1 Reached - Add Aura 'Cosmetic - Immolation (Whole Body)'");
-- Ascended Mage Hunter SAI
SET @ENTRY := 25724;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ascended Mage Hunter - On Respawn - Set Reactstate Passive"),
(@ENTRY,0,1,0,1,0,100,1,1000,1000,1000,1000,11,45940,0,0,0,0,0,9,25594,0,10,0,0,0,0,"Ascended Mage Hunter - Out of Combat - Cast 'Evanor's Prison Chains' (No Repeat)"),
(@ENTRY,0,2,3,23,0,100,1,42726,1,0,0,89,5,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ascended Mage Hunter - On Has Aura 'Cosmetic - Immolation (Whole Body)' - Start Random Movement (No Repeat)"),
(@ENTRY,0,3,0,61,0,100,1,42726,1,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Ascended Mage Hunter - On Has Aura 'Cosmetic - Immolation (Whole Body)' - Run Script (No Repeat)"),
(@ENTRY,0,4,0,6,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,114368,24771,0,0,0,0,0,"Ascended Mage Hunter - On Just Died - Set Data 1 1");
-- Actionlist SAI
SET @ENTRY := 2572400;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,3000,3000,0,0,37,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Kill Self");
-- Coldarra Invisman SAI
SET @ENTRY := 24771;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,1,1,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Coldarra Invisman - On Data Set 1 1 - Run Script (No Repeat)");
-- Actionlist SAI
SET @ENTRY := 2477100;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,4000,4000,0,0,9,0,0,0,0,0,0,20,187884,20,0,0,0,0,0,"Coldarra Invisman - On Script - activate Game Object"),
(@ENTRY,9,1,0,0,0,100,0,4000,4000,0,0,11,46013,2,0,0,0,0,1,0,0,0,0,0,0,0,"Coldarra Invisman - On Script - Cast 'Summon Lady Evanor'");
-- Archmage Evanor SAI
SET @ENTRY := 25784;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,54,0,100,0,0,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Archmage Evanor - On Just Summoned - Run Script");
-- Actionlist SAI
SET @ENTRY := 2578400;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Archmage Evanor - On Script - Say Line 0"),
(@ENTRY,9,1,0,0,0,100,0,3000,3000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Archmage Evanor - On Script - Say Line 1"),
(@ENTRY,9,2,0,0,0,100,0,0,0,0,0,11,46018,0,0,0,0,0,1,0,0,0,0,0,0,0,"Archmage Evanor - On Script - Cast 'Teleport'"),
(@ENTRY,9,3,0,0,0,100,0,8000,8000,0,0,41,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Archmage Evanor - On Script - Despawn Instant");
DELETE FROM `creature_text` WHERE `entry`=25784;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(25784, 0, 0, 'I thank you, friend of Dalaran.', 12, 0, 100, 0, 0, 0, 24995, 0, 'Archmage Evanor'),
(25784, 1, 0, 'We mustn''t tarry here... stay close - I''ll take us somewhere safe.', 12, 0, 100, 0, 0, 0, 24996, 0, 'Archmage Evanor');
DELETE FROM `spell_target_position` WHERE `id`=46018;
INSERT INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`, `VerifiedBuild`) VALUES
(46018, 0, 571, 3646.895, 5893.2773, 174.48, 0.674, 0);
/* waypoint datas */
DELETE FROM `waypoints` WHERE `entry`=25727;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(25727, 1,3195.641,6102.673,147.5568, 'Warmage Moran'),
(25727, 2,3437.590576,5915.928711,145.554291, 'Warmage Moran');
DELETE FROM `waypoints` WHERE `entry`=25733;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(25733, 1,3224.336,6105.71,146.7791, 'Warmage Austin'),
(25733, 2,3435.270,5889.899,151.063, 'Warmage Austin');
DELETE FROM `waypoints` WHERE `entry`=25732;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(25732, 1,3224.749,6083.038,147.5568, 'Warmage Preston'),
(25732, 2,3460.500,5877.4399,149.537, 'Warmage Preston');
DELETE FROM `waypoints` WHERE `entry`=27888;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(27888, 1,3200.99,6074.898,144.9736, 'Warmage Archus'),
(27888, 2,3457.750,5892.669,147.380, 'Warmage Archus');
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (25727, 25733, 25732, 27888);

-- fix quest 12097
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` = 29426;
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` = 30147;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=30147 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(30147, 0, 0, 0, 9, 0, 100, 0, 0, 5, 5000, 9000, 11, 50306, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Garhal - Within 0-5 Range - Cast 'Thrash Kick' (Phase 4) (No Repeat)"),
(30147, 0, 1, 2, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "talk"),
(30147, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, 118746, 29426, 0, 0, 0, 0, 0, "start combat mode"),
(30147, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 2, 1, 0, 0, 0, 0, 10, 118747, 29426, 0, 0, 0, 0, 0, "start combat mode");

DELETE FROM `creature_text` WHERE `entry`=30147;
INSERT INTO `creature_text` (`entry`, `text`, `type`, `probability`, `BroadcastTextId`, `comment`) VALUES 
('30147', 'Get Them!', '12', '100', '29345', 'say on agro Garhal');

DELETE FROM `smart_scripts` WHERE (`entryorguid`=29426 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(29426, 0, 0, 0, 0, 0, 100, 0, 3000, 7000, 11000, 16000, 11, 30931, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Hyldnir Overseer - In Combat - Cast 'Battle Shout' (Phase 1)"),
(29426, 0, 1, 0, 8, 0, 100, 0, 0, 5, 6000, 9000, 11, 46182, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Hyldnir Overseer - On Spellhit - Cast 'Snap Kick' (Phase 1)"),
(29426, 0, 3, 0, 38, 0, 100, 0, 2, 1, 0, 0, 11, 3606, 3, 0, 0, 0, 0, 10, 118804, 29427, 0, 0, 0, 0, 0, "begin battle"),
(29426, 0, 2, 0, 38, 0, 100, 0, 1, 1, 0, 0, 11, 3606, 3, 0, 0, 0, 0, 10, 118803, 29427, 0, 0, 0, 0, 0, "begin battle");

-- FiX quest 12893
UPDATE `locales_quest` SET `ObjectiveText2_loc8` = 'Леди Найтсвуд обращена', `ObjectiveText3_loc8` = 'Прыгун обращен' WHERE `Id` = 12893;
UPDATE smart_scripts SET `action_param1` = 58042 WHERE `entryorguid` = 29840 AND `source_type`=0 AND id=5;
UPDATE smart_scripts SET `action_param1` = 58042 WHERE `entryorguid` = 29769 AND `source_type`=0 AND id=5;
UPDATE smart_scripts SET `action_param1` = 58042 WHERE `entryorguid` = 29770 AND `source_type`=0 AND id=5;

-- Fix quest 13082
UPDATE `creature_template` SET `InhabitType` = 7 WHERE `entry` = 30694;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=30562 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(30562, 0, 0, 0, 20, 0, 100, 0, 13082, 0, 0, 0, 86, 57786, 3, 7, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Crusader Bridenbrad - On Quest 'The Boon of A'dal' Finished - Cast 'Summon K'uri'"),
(30562, 0, 1, 0, 20, 0, 100, 0, 13082, 0, 0, 0, 86, 57782, 3, 7, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Crusader Bridenbrad - On Quest 'The Boon of A'dal' Finished - Cast 'Summon M'ori'"),
(30562, 0, 2, 0, 20, 0, 100, 0, 13082, 0, 0, 0, 86, 57746, 3, 7, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Crusader Bridenbrad - On Quest 'The Boon of A'dal' Finished - Cast 'Summon A'dal'"),
(30562, 0, 3, 0, 20, 0, 100, 0, 13082, 0, 0, 0, 86, 57747, 3, 7, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Crusader Bridenbrad - On Quest 'The Boon of A'dal' Finished - Cast 'Summon Spirit of Bridenbrad'"),
(30562, 0, 4, 0, 20, 0, 100, 0, 13082, 0, 0, 0, 86, 57773, 3, 7, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Crusader Bridenbrad - On Quest 'The Boon of A'dal' Finished - Cast 'Summon Light Bunny'");

DELETE FROM `smart_scripts` WHERE (`entryorguid`=30691 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(30691, 0, 0, 0, 1, 0, 100, 1, 6000, 6000, 6000, 6000, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "A'dal - Out of Combat - Despawn Instant (No Repeat) (Dungeon)"),
(30691, 0, 1, 0, 1, 0, 100, 1, 500, 500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "A'dal - Out of Combat - txt1"),
(30691, 0, 2, 0, 1, 0, 100, 1, 2500, 2500, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "A'dal - Out of Combat - txt2"),
(30691, 0, 3, 0, 1, 0, 100, 1, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "A'dal - Out of Combat - txt3");

DELETE FROM `smart_scripts` WHERE (`entryorguid`=30691 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(30691, 0, 0, 0, 1, 0, 100, 1, 6000, 6000, 6000, 6000, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "A'dal - Out of Combat - Despawn Instant (No Repeat) (Dungeon)"),
(30691, 0, 1, 0, 1, 0, 100, 1, 500, 500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "A'dal - Out of Combat - txt1"),
(30691, 0, 2, 0, 1, 0, 100, 1, 2500, 2500, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "A'dal - Out of Combat - txt2"),
(30691, 0, 3, 0, 1, 0, 100, 1, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "A'dal - Out of Combat - txt3");

DELETE FROM `creature_text` WHERE `entry`='30691';
INSERT INTO `creature_text` (`entry`, `groupid`, `text`, `type`, `probability`, `BroadcastTextId`, `comment`) VALUES 
('30691', '0', 'Fear not, young one, for this crusader shall not taste death.', '12', '100', '31434', 'A\'dal event - q13082'),
('30691', '1', 'In life, Bridenbrad was the bearer of great deeds. Now, in passing, he shall taste only paradise.', '12', '100', '31435', 'A\'dal event - q13082'),
('30691', '2', 'The light does not abandon its champions.', '12', '100', '31436', 'A\'dal event - q13082');

-- Fix quest 13216
UPDATE `creature_template` SET `vehicleid`=60 WHERE `entry`=30159;
UPDATE `smart_scripts` SET `action_param2`=0 WHERE `entryorguid`=31242 AND `source_type`=0 AND `id`=14;
UPDATE `creature_template_addon` SET `mount`=0 WHERE `entry`=31242;

-- Fix quest 13308
UPDATE `quest_template` SET `PrevQuestId`=0 WHERE `Id`=13308;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN(19,20) AND `SourceEntry`=13308;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(19, 0, 13308, 0, 0, 8, 0, 13224, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires Orgrims Hammer Rewarded or'),
(20, 0, 13308, 0, 0, 8, 0, 13224, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires Orgrims Hammer Rewarded or'),
(19, 0, 13308, 0, 1, 9, 0, 13224, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires Orgrims Hammer Taken or'),
(20, 0, 13308, 0, 1, 9, 0, 13224, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires Orgrims Hammer Taken or'),
(19, 0, 13308, 0, 2, 28, 0, 13224, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires Orgrims Hammer Complete or'),
(20, 0, 13308, 0, 2, 28, 0, 13224, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires Orgrims Hammer Complete or'),
(19, 0, 13308, 0, 3, 8, 0, 13225, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires The Skybreaker Rewarded or'),
(20, 0, 13308, 0, 3, 8, 0, 13225, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires The Skybreaker Rewarded or'),
(19, 0, 13308, 0, 4, 9, 0, 13225, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires The Skybreaker Taken or'),
(20, 0, 13308, 0, 4, 9, 0, 13225, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires The Skybreaker Taken or'),
(19, 0, 13308, 0, 5, 28, 0, 13225, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires The Skybreaker Complete or'),
(20, 0, 13308, 0, 5, 28, 0, 13225, 0, 0, 0, 0, 0, '', 'Mind Tricks Requires The Skybreaker Complete or');

-- Fix quest 13343
UPDATE `creature_template` SET `unit_flags` = 4, `AIName` = '', `ScriptName` = 'hourglass_of_eternity' WHERE `entry` = 32327;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=27900 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(27900, 0, 0, 0, 0, 0, 100, 0, 5000, 6000, 12000, 17000, 11, 51020, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Infinite Timerender - In Combat - Cast 'Time Lapse'"),
(27900, 0, 1, 0, 6, 0, 100, 0, 0, 0, 0, 0, 45, 2, 1, 0, 0, 0, 0, 19, 27840, 20, 0, 0, 0, 0, 0, "Infinite Timerender - On Just Died - Set Data 2 1"),
(27900, 0, 2, 0, 2, 0, 100, 0, 1, 10, 0, 0, 15, 13343, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Infinite Timerender - quest credit");

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`='60808';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES 
('60808', '49942', 'Summon Future Self');

DELETE FROM `smart_scripts` WHERE (`entryorguid`=27899 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(27899, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 85, 49889, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Just Summoned - Invoker Cast 'Mystery of the Infinite: Future You's Mirror Image Aura' (No Repeat)"),
(27899, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 11, 27840, 10, 0, 0, 0, 0, 0, "Future You - On Just Summoned - Set Orientation Closest Creature 'Hourglass of Eternity' (No Repeat)"),
(27899, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 11, 50037, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 1 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Random'"),
(27899, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 21, 10, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 1 - Say Line 1"),
(27899, 0, 4, 5, 1, 0, 100, 1, 3000, 3000, 0, 0, 11, 50037, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 2 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Random'"),
(27899, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 2 - Say Line 2"),
(27899, 0, 6, 7, 38, 0, 100, 0, 1, 3, 0, 0, 11, 50037, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 3 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Random'"),
(27899, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 3 - Say Line 3"),
(27899, 0, 8, 9, 38, 0, 100, 0, 1, 4, 0, 0, 11, 50037, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 4 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Random'"),
(27899, 0, 9, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 4 - Say Line 4"),
(27899, 0, 10, 11, 38, 0, 100, 0, 1, 5, 0, 0, 11, 50037, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 5 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Random'"),
(27899, 0, 11, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 5 - Say Line 5"),
(27899, 0, 12, 13, 38, 0, 100, 0, 1, 6, 0, 0, 11, 50037, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 6 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Random'"),
(27899, 0, 13, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 6 - Say Line 6"),
(27899, 0, 14, 15, 38, 0, 100, 0, 1, 7, 0, 0, 11, 50037, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 7 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Random'"),
(27899, 0, 15, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 7 - Say Line 7"),
(27899, 0, 16, 17, 38, 0, 100, 0, 1, 8, 0, 0, 11, 50037, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 8 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Random'"),
(27899, 0, 17, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 8 - Say Line 8"),
(27899, 0, 18, 19, 38, 0, 100, 0, 1, 9, 0, 0, 11, 50037, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 9 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Random'"),
(27899, 0, 19, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 9, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 9 - Say Line 9"),
(27899, 0, 20, 21, 38, 0, 100, 0, 1, 10, 0, 0, 11, 50037, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 10 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Random'"),
(27899, 0, 21, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 1 10 - Say Line 10"),
(27899, 0, 22, 23, 38, 0, 100, 0, 2, 1, 0, 0, 11, 50014, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 2 1 - Cast 'Mystery of the Infinite: Future You's Whisper to Controller - Nozdormu'"),
(27899, 0, 23, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 11, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 2 1 - Say Line 11"),
(27899, 0, 24, 25, 38, 0, 100, 0, 2, 2, 0, 0, 1, 12, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 2 2 - Say Line 12"),
(27899, 0, 25, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 3000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Data Set 2 2 - Despawn In 3000 ms"),
(27899, 0, 26, 27, 7, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Future You - On Evade - Despawn Instant"),
(27899, 0, 27, 0, 61, 0, 100, 0, 0, 0, 0, 0, 85, 49942, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Future You - On Evade - Invoker Cast 'Mystery of the Infinite: Force Cast to Player of Summon Future You'");

-- Fix quest 27409

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN (4331, 4329);
DELETE FROM `smart_scripts` WHERE `entryorguid`= 4328 AND `source_type`=0 AND `id` IN (3);
DELETE FROM `smart_scripts` WHERE `entryorguid`= 4331 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`= 4329 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4328, 0, 3, 0, 8, 0, 100, 0, 42411, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Firemane Scalebane - On spell hit  - Despawn'),
(4331, 0, 0, 0, 8, 0, 100, 0, 42411, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Firemane Ash Tail - On spell hit  - Despawn'),
(4331, 0, 1, 0, 0, 0, 100, 0, 4000, 6000, 6000, 8000, 11, 11969, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Firemane Ash Tail - Icc  - Cast Fire Nova'),
(4331, 0, 2, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 18968, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Firemane Ash Tail - On aggr  - cast Fire Shield'),
(4329, 0, 0, 0, 8, 0, 100, 0, 42411, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Firemane Scout - On spell hit  - Despawn'),
(4329, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 18968, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Firemane Scout - On aggr  - cast Fire Shield');

-- FiX quest frostmourne
-- partial for issue #44
UPDATE `locales_quest` SET `OfferRewardText_loc8` = 'Залы Отражений... Наконец-то.$B$BДай мне знать, когда будешь готов идти дальше. Возможно, Артаса там нет, но я не стала бы надеяться на то, что он оставит Ледяную Скорбь без должной охраны. ' WHERE `Id` = 24713;
UPDATE `locales_quest` SET `OfferRewardText_loc8` = 'Залы Отражений... Наконец-то.$B$BДай мне знать, когда будешь готов идти дальше. Возможно, Артаса там нет, но я не стала бы надеяться на то, что он оставит Ледяную Скорбь без должной охраны. ' WHERE `Id` = 24711;

-- Fix The Valiants Challenge
DELETE FROM `creature_text`  WHERE `entry`=33707;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(33707, 0, 0, '', 12, 0, 100, 0, 0, 0, 33788, 0, 'The Valiant\'s Challenge'),
(33707, 1, 0, '', 12, 0, 100, 0, 0, 0, 33782, 0, 'The Valiant\'s Challenge');

UPDATE `creature_template` SET `AIName` = 'SmartAI', `RegenHealth` = 0 WHERE `entry` = 33707;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=33707 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(33707, 0, 0, 9, 54, 0, 100, 0, 0, 0, 0, 0, 2, 14, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "set faction"),
(33707, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 1, 0, 5, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "talk"),
(33707, 0, 2, 3, 2, 0, 100, 1, 1, 10, 0, 0, 2, 35, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "friendly"),
(33707, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "talk"),
(33707, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "despawn"),
(33707, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 33, 33708, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "quest credit"),
(33707, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "stop combat"),
(33707, 0, 7, 0, 0, 0, 75, 0, 5000, 6000, 4000, 6000, 11, 62552, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "shield"),
(33707, 0, 8, 0, 0, 0, 70, 0, 1000, 5000, 3000, 7000, 11, 62575, 3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "shield break"),
(33707, 0, 9, 0, 61, 0, 100, 0, 0, 0, 0, 0, 46, 30, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "moveforward");

DELETE FROM `smart_scripts` WHERE (`entryorguid`=33518 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(33518, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "close gossip"),
(33518, 0, 0, 1, 62, 0, 100, 0, 10343, 0, 0, 0, 12, 33707, 1, 120000, 0, 1, 0, 8, 0, 0, 0, 8581.552, 1086.92, 556.79, 2.335, "summon Argent Champion");

-- fix Tooga's Quest
UPDATE `quest_template` SET `SpecialFlags`=2 WHERE  `Id`=1560;

-- fix up3
-- fix localization
UPDATE `locales_quest` SET `Title_loc8` = 'Нападение на лагерь кобольдов' WHERE `Id` = 7;

-- add queststarter/ender for Warlock Imp
DELETE FROM `creature_queststarter` WHERE `quest` = 1598;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES (459, 1598);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` = 459;
DELETE FROM `creature_questender` WHERE `quest` = 1598;
INSERT INTO `creature_questender` (`id`, `quest`) VALUES (459, 1598);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry`=459;

DELETE FROM `creature_queststarter` WHERE `quest` = 1599;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES (460, 1599);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` = 460;
DELETE FROM `creature_questender` WHERE `quest` = 1599;
INSERT INTO `creature_questender` (`id`, `quest`) VALUES (460, 1599);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry`=460;

DELETE FROM `creature_queststarter` WHERE `quest` = 1470;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES (5667, 1470);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` = 5667;
DELETE FROM `creature_questender` WHERE `quest` = 1470;
INSERT INTO `creature_questender` (`id`, `quest`) VALUES (5667, 1470);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry`=5667;

DELETE FROM `creature_queststarter` WHERE `quest` = 1485;
UPDATE `item_template` SET `StartQuest`=0 WHERE `StartQuest` = 1485;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES (5765, 1485);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` = 5765;
DELETE FROM `creature_questender` WHERE `quest` = 1485;
INSERT INTO `creature_questender` (`id`, `quest`) VALUES (5765, 1485);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry`=5765;

DELETE FROM `creature_queststarter` WHERE `quest` = 8344;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES (15283, 8344);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` = 15283;
DELETE FROM `creature_questender` WHERE `quest` = 8344;
INSERT INTO `creature_questender` (`id`, `quest`) VALUES (15283, 8344);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry`=15283;

-- spell fix 
DELETE FROM `spell_linked_spell` WHERE `spell_effect`=69706;

-- spell 3607
DELETE FROM `spell_bonus_data` WHERE `entry`=3607;
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES 
(3607, 0, 0, 0, 0, 'Yenniku Soul Gem');

-- spell 58913
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`='13' AND `SourceGroup`='7' AND `SourceEntry`='58913';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
('13', '7', '58913', '0', '0', '31', '0', '3', '31254', '0', '0', '0', '0', '', 'The Prodigal Leader target for spell');

--Fix Event - Stranglethorn Fishing Extravaganza
UPDATE `game_event` SET `start_time`='2015-03-15 13:00:00' WHERE `eventEntry`='62';
UPDATE `game_event` SET `start_time`='2015-03-15 13:00:00' WHERE `eventEntry`='14';
UPDATE `game_event` SET `start_time`='2015-03-15 13:00:00' WHERE `eventEntry`='15';
DELETE FROM `game_event_gameobject` WHERE `eventEntry`=62;
INSERT INTO `game_event_gameobject` (`eventEntry`, `guid`) VALUES 
('62', '20385'),
('62', '15062'),
('62', '20412'),
('62', '20379'),
('62', '20382'),
('62', '20415'),
('62', '18132'),
('62', '18133'),
('62', '11453'),
('62', '18143'),
('62', '14715'),
('62', '20419'),
('62', '20423'),
('62', '20425'),
('62', '20438'),
('62', '20441'),
('62', '20447'),
('62', '20448'),
('62', '20449'),
('62', '20450'),
('62', '20451'),
('62', '20452'),
('62', '20456'),
('62', '20462'),
('62', '12529'),
('62', '11480'),
('62', '13231'),
('62', '12528'),
('62', '17292'),
('62', '13048'),
('62', '20388'),
('62', '11012'),
('62', '20413'),
('62', '12361'),
('62', '16917'),
('62', '20391'),
('62', '20392'),
('62', '17289'),
('62', '12758'),
('62', '20387'),
('62', '20410'),
('62', '20414'),
('62', '13376'),
('62', '12678'),
('62', '20416'),
('62', '15215'),
('62', '12891'),
('62', '13047'),
('62', '18135'),
('62', '18136'),
('62', '18134'),
('62', '18137');
