SET @NPC_FRYE := 36272;
SET @NPC_HUMMEL := 36296;
SET @NPC_BAXTER := 36565;
SET @NPC_CRAZED := 36568;

UPDATE `creature_template` SET `AIName`='',`ScriptName`='npc_apothecary_frye' WHERE `entry`=@NPC_FRYE;
UPDATE `creature_template` SET `AIName`='',`ScriptName`='npc_apothecary_hummel' WHERE `entry`=@NPC_HUMMEL;
UPDATE `creature_template` SET `AIName`='',`ScriptName`='npc_apothecary_baxter' WHERE `entry`=@NPC_BAXTER;
UPDATE `creature_template` SET `AIName`='',`ScriptName`='npc_crazed_apothecary' WHERE `entry`=@NPC_CRAZED;

DELETE FROM `creature_text` WHERE `entry` IN (@NPC_FRYE,@NPC_HUMMEL,@NPC_BAXTER);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@NPC_HUMMEL,0,0,"Did they bother to tell you who I am and why I am doing this?",12,0,100,0,0,0,"say text"),
(@NPC_HUMMEL,1,0,"...or are they just using you like they do everybody else?",12,0,100,0,0,0,"say text"),
(@NPC_HUMMEL,2,0,"But what does it matter. It is time for this to end.",12,0,100,0,0,0,"say text"),
(@NPC_HUMMEL,3,0,"Baxter! Get in here and help! NOW!",12,0,100,0,0,0,"say text"),
(@NPC_HUMMEL,4,0,"It is time, Frye! Attack!",12,0,100,0,0,0,"say text"),
(@NPC_HUMMEL,5,0,"Apothecaries! Give your life for The Crown!",12,0,100,0,0,0,"say text"),
(@NPC_FRYE,0,0,"Great. We're not gutless, we're incompetent.",12,0,100,0,0,0,"say text"),
(@NPC_BAXTER,0,0,"It has been the greatest honor of my life to server with you, Hummel.",12,0,100,0,0,0,"say text");

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (68530,68529);
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(68530,-68529,0,'Remove Perfume Immune when Cologne Immune is applied'),
(68529,-68530,0,'Remove Cologne Immune when Perfume Immune is applied');


-- Hummel's Loot Template currently holds everything (all necklaces, mount, pet and rest of the stuff)
-- Delete items from Apothecary Hummel that should be inside the Heart-Shaped Box
DELETE FROM `creature_loot_template` WHERE `entry`=36296 AND `item` IN (49715,50250,50471,50446,50741);
-- Insert items into Heart-Shaped Box
SET @BOX := 54537; -- Heart-Shaped Box
DELETE FROM `item_loot_template` WHERE `entry`=@BOX;
INSERT INTO `item_loot_template` (`entry`, `item`, `Chance`, `lootmode`, `groupid`, `Mincount`, `Maxcount`) VALUES
(@BOX,50250,2,1,0,1,1), -- Big Love Rocket
(@BOX,50446,2,1,0,1,1), -- Toxic Wasteling
(@BOX,50471,5,1,0,1,1), -- The Heartbreaker
(@BOX,50741,5,1,0,1,1), -- Vile Fumigator's Mask
(@BOX,49715,5,1,0,1,1), -- Forever-Lovely Rose
(@BOX,49426,100,1,1,2,2); -- 1-2 Emblems of Frost
