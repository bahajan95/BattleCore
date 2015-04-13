-- Sindragosa
UPDATE creature_template SET InhabitType=7 WHERE entry=36853;
INSERT INTO `disables` VALUES ('7', '36853', '0', '', '', 'Ignore mmaps sindragosa');

-- Fix quest 13003
UPDATE `creature_template` SET `unit_flags` = 32896, `spell1` = 60533, `spell2` = 56704, `spell3` = 56690, `spell4` = 60586, `ScriptName` = 'npc_wild_wyrm_vehicle' WHERE `entry` = 30275;

DELETE FROM spell_script_names WHERE spell_id IN (60864, 60533, 60776, 60587, 56690, 60586);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('60864', 'spell_wild_wyrm_jaws_of_death'),
('60533', 'spell_wild_wyrm_grip_on'),
('60776', 'spell_wild_wyrm_claw_swipe'),
('60587', 'spell_wild_wyrm_fatal_strike'),
('56690', 'spell_wild_wyrm_spells'),
('60586', 'spell_wild_wyrm_spells');

-- wintergrasp tower cannon
REPLACE INTO `creature_template` VALUES (28366, 0, 0, 0, 0, 0, 27101, 0, 0, 0, 'Wintergrasp Tower Cannon', '', 'Gunner', 0, 80, 80, 0, 35, 16777216, 0, 0, 1, 0, 0, 2000, 2000, 1, 1, 4, 32772, 2048, 0, 0, 0, 0, 0, 0, 9, 262184, 0, 0, 0, 0, 0, 0, 0, 0, 0, 51421, 0, 0, 0, 0, 0, 0, 0, 0, 244, 0, 0, '', 0, 3, 1, 9.35979, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 121, 1, 344276858, 0, '', 12340);


--Fix achievement 207
update achievement_criteria_data set value1=23335 where criteria_id=5605 and type = 7;
update achievement_criteria_data set value1=4572 where criteria_id=5605 and type = 6;

update achievement_criteria_data set value1=23333 where criteria_id=5606 and type = 7;
update achievement_criteria_data set value1=4571 where criteria_id=5606 and type = 6;

-- Fix range_attack time + add pin in the air
UPDATE `creature_template` SET `RangeAttackTime` = 2500, `unit_flags` = 32772 WHERE `entry` = 29747;

-- FIX kolco lbdaa

DELETE FROM `creature_queststarter` WHERE `quest` = 10069;
DELETE FROM `gameobject_queststarter` WHERE `quest` = 10069;
UPDATE `item_template` SET `StartQuest`=0 WHERE `StartQuest` = 10069;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES (15280, 10069);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` = 15280;
DELETE FROM `creature_questender` WHERE `quest` = 10069;
DELETE FROM `gameobject_questender` WHERE `quest` = 10069;
INSERT INTO `creature_questender` (`id`, `quest`) VALUES (15295, 10069);
UPDATE `quest_template` SET `PrevQuestId` = 9676 WHERE `Id` = 10069;

DELETE FROM `creature_queststarter` WHERE `quest` = 10068;
DELETE FROM `gameobject_queststarter` WHERE `quest` = 10068;
UPDATE `item_template` SET `StartQuest`=0 WHERE `StartQuest` = 10068;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES (15279, 10068);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` = 15279;
DELETE FROM `creature_questender` WHERE `quest` = 10068;
DELETE FROM `gameobject_questender` WHERE `quest` = 10068;
INSERT INTO `creature_questender` (`id`, `quest`) VALUES (15295, 10068);
UPDATE `quest_template` SET `PrevQuestId` = 8328 WHERE `Id` = 10068;

-- Highlord Demitrian locales gossip RU
UPDATE `npc_text` SET `BroadcastTextID0`='9299' WHERE `ID`='6843';
UPDATE `npc_text` SET `BroadcastTextID0`='9301' WHERE `ID`='6844';
UPDATE `npc_text` SET `BroadcastTextID0`='9331' WHERE `ID`='6867';
UPDATE `npc_text` SET `BroadcastTextID0`='9337' WHERE `ID`='6870';

-- locales RU
UPDATE `locales_quest` SET `OfferRewardText_loc8` = 'Даже во сне я не чаял увидеть этот день.$B$BЗри же, смертный.$B$BУЗРИ ТОГО, КТО СТАРШЕ СУЩЕГО!$B$BУЗРИ ТОГО, КТО СРАЖАЛСЯ С ТИТАНОМ И БОГОМ!$B$BВОССТАНЬ, МОЙ ПОВЕЛИТЕЛЬ! ОТРИНЬ ОКОВЫ! ' WHERE `Id` = 7786;

-- hack need OFF data
DELETE FROM `gossip_menu_option` WHERE `menu_id`='5689' AND `id`=1;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`) VALUES 
('5689', '1', 'RE-Summon  Prince Thunderaan', '0', '1', '1');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND  `SourceGroup`=5689;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 5689, 0, 0, 0, 8, 0, 7785, 0, 0, 1, 0, 0, '', 'Gossip Awailable only if quest 7785 isn\'t rewarded'),
(15, 5689, 0, 0, 0, 2, 0, 19016, 0, 0, 1, 0, 0, '', 'Gossip awailable if item not in the bag'),
(15, 5689, 1, 0, 0, 8, 0, 7786, 0, 0, 0, 0, 0, '', 'Summon if quest rewarded\r\n Prince Thunderaan'),
(15, 5689, 1, 0, 0, 8, 0, 7787, 0, 0, 1, 0, 0, '', 'Summot until quest rewarded'),
(15, 5689, 1, 0, 0, 2, 0, 19018, 1, 0, 1, 0, 0, '', 'Show gossip until item not in the bag');

DELETE FROM `smart_scripts` WHERE (`entryorguid`=14347 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(14347, 0, 0, 3, 62, 0, 100, 0, 5704, 0, 0, 0, 85, 22958, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Highlord Demitrian - On Gossip Complete - Cast Summon Vessel of Rebirth DND"),
(14347, 0, 1, 0, 20, 0, 100, 0, 7786, 0, 0, 0, 12, 14435, 6, 60000, 0, 0, 0, 8, 0, 0, 0, -6241.77, 1717.14, 4.25042, 0.680879, "Highlord Demitrian - On Quest Thunderaan the Windseeker Finished - Summon Creature Prince Thunderaan at XYZO"),
(14347, 0, 2, 3, 62, 0, 100, 0, 5689, 1, 0, 0, 12, 14435, 6, 60000, 0, 0, 0, 8, 0, 0, 0, -6241.77, 1717.14, 4.25042, 0.680879, "Highlord Demitrian - On Gossip Thunderaan the Windseeker Finished - Summon Creature Prince Thunderaan at XYZO"),
(14347, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Highlord Demitrian - close gossip");

-- FIX Valkiria 
UPDATE `creature_template` SET `speed_walk` = 0.442857, `speed_run` = 0.442857, `InhabitType` = 5, `flags_extra` = 0, `mechanic_immune_mask` = 12582928 WHERE `entry` IN (36609, 39120, 39121, 39122);

