REPLACE INTO `command` (`name`,`permission`,`help`) VALUES ('anticheat global', '800', 'Syntax: .anticheat 
global returns the total amount reports and the average. (top three players)'), ('anticheat player', '801', 
'Syntax: .anticheat player $name returns the players''s total amount of warnings, the average and the 
amount of each cheat type.'), ('anticheat handle', '803', 'Syntax: .anticheat handle [on|off] Turn on/off the 
AntiCheat-Detection .'),
('anticheat delete', '802', 'Syntax: .anticheat delete [deleteall|$name] Deletes the report records of all the players or deletes all the reports of player $name.');

DELETE FROM trinity_string WHERE entry = 11100;
INSERT INTO `trinity_string` VALUES ('11100', '|cFFFFFC00[AntiCheat]|cFF00FFFF[|cFF60FF00%s|cFF00FFFF] Possible uses %s!', null, null, null, null, null, null, null, '|cFFFFFC00[АНТИЧИТ]|cFF00FFFF[|cFF60FF00%s|cFF00FFFF] Возможно использует %s!');