DELETE FROM vehicle_template_accessory WHERE entry IN (33318, 33319, 33316, 33317, 33217, 33324, 33322, 33320, 33323, 33321, 33297, 33416, 33298,
35637, 35633, 35768, 34658, 35636, 35638, 35635, 35640, 35641, 35634);

DELETE FROM gameobject WHERE id IN (195709, 195710, 195374, 195375, 195323, 195324);

INSERT INTO `vehicle_template_accessory` VALUES ('35637', '34705', '0', '0', 'Marshal Jacob Alerius\' Mount', '8', '0');
INSERT INTO `vehicle_template_accessory` VALUES ('35633', '34702', '0', '0', 'Ambrose Boltspark\'s Mount', '8', '0');
INSERT INTO `vehicle_template_accessory` VALUES ('35768', '34701', '0', '0', 'Colosos\' Mount', '8', '0');
INSERT INTO `vehicle_template_accessory` VALUES ('34658', '34657', '0', '0', 'Jaelyne Evensong\'s Mount', '8', '0');
INSERT INTO `vehicle_template_accessory` VALUES ('35636', '34703', '0', '0', 'Lana Stouthammer\'s Mount', '8', '0');
INSERT INTO `vehicle_template_accessory` VALUES ('35638', '35572', '0', '0', 'Mokra the Skullcrusher\'s Mount', '8', '0');
INSERT INTO `vehicle_template_accessory` VALUES ('35635', '35569', '0', '0', 'Eressea Dawnsinger\'s Mount', '8', '0');
INSERT INTO `vehicle_template_accessory` VALUES ('35640', '35571', '0', '0', 'Runok Wildmane\'s Mount', '8', '0');
INSERT INTO `vehicle_template_accessory` VALUES ('35641', '35570', '0', '0', 'Zul\'tore\'s Mount', '8', '0');
INSERT INTO `vehicle_template_accessory` VALUES ('35634', '35617', '0', '0', 'Deathstalker Visceri\'s Mount', '8', '0');

UPDATE creature_template SET ScriptName='generic_vehicle_toc5' WHERE entry IN (35637, 35633, 35768, 34658, 35636, 35638, 35635, 35640,
35641, 35634);

UPDATE creature_template_addon SET mount =29255 WHERE entry=35330;
UPDATE creature_template_addon SET mount =29256 WHERE entry=35332;
UPDATE creature_template_addon SET mount =29258 WHERE entry=35329;
UPDATE creature_template_addon SET mount =28571 WHERE entry=35331;
UPDATE creature_template_addon SET mount =28912 WHERE entry=35328;
UPDATE creature_template_addon SET mount =29257 WHERE entry=35327;
UPDATE creature_template_addon SET mount =29259 WHERE entry=35325;
UPDATE creature_template_addon SET mount =29260 WHERE entry=35314;
UPDATE creature_template_addon SET mount =29262 WHERE entry=35326;
UPDATE creature_template_addon SET mount =29261 WHERE entry=35323;

DELETE FROM `creature_onkill_reputation` WHERE creature_id IN (35330, 35332, 35329, 35331, 35328, 35327, 35325, 35314, 35326, 35323);
INSERT INTO `creature_onkill_reputation` VALUES ('35332', '0', '1052', '0', '0', '0', '7', '0', '3', '1');
INSERT INTO `creature_onkill_reputation` VALUES ('35331', '0', '1052', '0', '0', '0', '7', '0', '3', '1');
INSERT INTO `creature_onkill_reputation` VALUES ('35330', '0', '1052', '0', '0', '0', '7', '0', '3', '1');
INSERT INTO `creature_onkill_reputation` VALUES ('35329', '0', '1052', '0', '0', '0', '7', '0', '3', '1');
INSERT INTO `creature_onkill_reputation` VALUES ('35328', '0', '1052', '0', '0', '0', '7', '0', '3', '1');
INSERT INTO `creature_onkill_reputation` VALUES ('35327', '1037', '0', '7', '0', '3', '0', '0', '0', '1');
INSERT INTO `creature_onkill_reputation` VALUES ('35326', '1037', '0', '7', '0', '3', '0', '0', '0', '1');
INSERT INTO `creature_onkill_reputation` VALUES ('35325', '1037', '0', '7', '0', '3', '0', '0', '0', '1');
INSERT INTO `creature_onkill_reputation` VALUES ('35323', '1037', '0', '7', '0', '3', '0', '0', '0', '1');
INSERT INTO `creature_onkill_reputation` VALUES ('35314', '1037', '0', '7', '0', '3', '0', '0', '0', '1');

DELETE FROM `creature_template_addon` WHERE entry IN (34705, 34702, 34701, 34657, 34703, 35572, 35569, 35571, 35570, 35617);
DELETE FROM `creature_equip_template` WHERE entry IN (35451, 34705, 34702, 34701, 34657, 34703, 35572, 35569, 35571, 35570, 35617);
INSERT INTO `creature_equip_template` VALUES ('34657', '1', '35779', '0', '52058', '18019');
INSERT INTO `creature_equip_template` VALUES ('34701', '1', '29709', '24331', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('34702', '1', '45129', '28487', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('34703', '1', '49024', '49024', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('34705', '1', '39659', '21572', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35569', '1', '34182', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35570', '1', '45204', '45204', '52058', '18019');
INSERT INTO `creature_equip_template` VALUES ('35571', '1', '45203', '45203', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35572', '1', '49020', '46092', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35617', '1', '45222', '45222', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('34657', '2', '46106', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('34701', '2', '46106', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('34702', '2', '46106', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('34703', '2', '46106', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('34705', '2', '46106', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35569', '2', '46106', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35570', '2', '46106', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35571', '2', '46106', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35572', '2', '46106', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35617', '2', '46106', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35451', '1', '40343', '0', '0', '18019');
INSERT INTO `creature_equip_template` VALUES ('35451', '2', '0', '0', '0', '18019');

UPDATE creature_template SET RegenHealth = 0 WHERE entry IN (34705, 34702, 34701, 34657, 34703, 35572, 35569, 35571, 35570, 35617);

UPDATE creature_template SET unit_flags = 0, faction = 14 WHERE entry IN (33318, 33319, 33316, 33317, 33217, 33324, 33322, 33320, 33323,
33321, 33297, 33416, 33298);
UPDATE creature_template SET unit_flags = 0, faction = 14, ScriptName='champion_toc5', AIName='' WHERE entry IN (35330, 35332, 35329, 35331, 35328, 35327, 35325, 35314,
35326, 35323);

UPDATE `creature_template` SET `AIName` = '', unit_flags = 0, faction = 14, VehicleId = 486, spell4 = 62552, ScriptName = 'generic_vehicle_toc5' WHERE `entry` = 35644;
UPDATE `creature_template` SET `AIName` = '', unit_flags = 0, faction = 14, ScriptName = 'generic_vehicle_toc5' WHERE `entry` = 36558;
UPDATE `creature_template` SET `gossip_menu_id` = 10614 WHERE `entry` = 35005;
UPDATE `creature_template` SET `speed_run` = 0.6 WHERE entry IN (35004, 35005);

UPDATE `gameobject_template` SET `flags` = 0 WHERE entry IN (195709, 195710, 195374, 195375, 195323, 195324);

DELETE FROM `spell_script_names` where `spell_id` = '67830' AND `ScriptName` = 'spell_ride_vehicle_toc5';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('67830', 'spell_ride_vehicle_toc5');

DELETE FROM `spell_script_names` where `spell_id` = '66798' AND `ScriptName` = 'spell_death_respite_toc5';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('66798', 'spell_death_respite_toc5');

DELETE FROM `spell_script_names` where `spell_id` = '67754' AND `ScriptName` = 'spell_raise_dead_explore';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('67754', 'spell_raise_dead_explore');

DELETE FROM `spell_script_names` where `spell_id` = '67868' AND `ScriptName` = 'spell_trampled_toc5';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('67868', 'spell_trampled_toc5');

UPDATE `creature_template` SET `unit_flags` = 258, `InhabitType` = 4  WHERE `entry` = 35491;

UPDATE `creature_template` SET `unit_flags` = 64 WHERE `entry` IN (35451, 35490);

UPDATE `creature_template` SET `ScriptName` = 'npc_fountain_of_light_toc5' WHERE `entry` = 35311;

DELETE FROM `script_waypoint` WHERE entry = 35491;
INSERT INTO `script_waypoint` VALUES ('35491', '1', '781.513', '657.99', '466.821', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '2', '759.005', '665.142', '462.541', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '3', '732.937', '657.164', '452.678', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '4', '717.491', '646.009', '440.137', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '5', '707.57', '628.978', '431.129', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '6', '705.164', '603.628', '422.957', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '7', '716.351', '588.49', '420.802', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '8', '741.703', '580.168', '420.523', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '9', '761.634', '586.383', '422.206', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '10', '775.983', '601.992', '423.606', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '11', '769.051', '624.686', '420.035', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '12', '756.582', '631.692', '412.53', '0', '');
INSERT INTO `script_waypoint` VALUES ('35491', '13', '744.841', '634.505', '411.575', '0', '');

DELETE FROM `conditions` where `SourceTypeOrReferenceId` = '13' AND `SourceGroup` = '1' AND `SourceEntry` = '66798';
INSERT INTO `conditions` VALUES ('13', '1', '66798', '0', '0', '31', '0', '3', '35004', '0', '0', '0', '0', '', 'Death Repite - target announcer TOC5');
INSERT INTO `conditions` VALUES ('13', '1', '66798', '0', '1', '31', '0', '3', '35005', '0', '0', '0', '0', '', 'Death Repite - target announcer TOC5');

DELETE FROM `conditions` where `SourceTypeOrReferenceId` = '13' AND `SourceGroup` = '1' AND `SourceEntry` IN (67715, 67705);
INSERT INTO `conditions` VALUES ('13', '1', '67715', '0', '0', '31', '0', '3', '35004', '0', '0', '0', '0', '', 'Raise Dead Jaeren Sunsworn - TOC5');
INSERT INTO `conditions` VALUES ('13', '1', '67705', '0', '0', '31', '0', '3', '35005', '0', '0', '0', '0', '', 'Raise Dead Arelas Brightstar - TOC5');

DELETE FROM `spell_dbc` WHERE Id IN (68572, 68574, 68575);
INSERT INTO `spell_dbc` VALUES ('68572', '0', '0', '545259776', '5', '268697600', '0', '16777216', '0', '0', '0', '0', '0', '0', '1', '0', '0', '101', '0', '0', '0', '0', '0', '13', '0', '-1', '0', '0', '3', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '28', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Grand Champions credit marker');
INSERT INTO `spell_dbc` VALUES ('68574', '0', '0', '545259776', '5', '268697600', '0', '16777216', '0', '0', '0', '0', '0', '0', '1', '0', '0', '101', '0', '0', '0', '0', '0', '13', '0', '-1', '0', '0', '3', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '28', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Argent Champion credit marker');
INSERT INTO `spell_dbc` VALUES ('68575', '0', '0', '545259776', '5', '268697600', '0', '16777216', '0', '0', '0', '0', '0', '0', '1', '0', '0', '101', '0', '0', '0', '0', '0', '13', '0', '-1', '0', '0', '3', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '28', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 'Argent Champion credit marker');