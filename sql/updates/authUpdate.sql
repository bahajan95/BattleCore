-- TrinityCore\sql\updates\auth\2014_10_18_00_auth.sql 
DELETE FROM `rbac_permissions` WHERE `id` IN (795, 796);
INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(795, 'Command: .instance setbossstate'),
(796, 'Command: .instance getbossstate');

DELETE FROM `rbac_linked_permissions` WHERE `linkedId` IN (795, 796);
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES
(192, 795),
(192, 796);
 
-- TrinityCore\sql\updates\auth\2014_10_18_01_auth.sql 
/* drop then create account_muted table */
DROP TABLE IF EXISTS `account_muted`;

CREATE TABLE `account_muted` (
	`guid` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
	`mutedate` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`mutetime` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`mutedby` VARCHAR(50) NOT NULL,
	`mutereason` VARCHAR(255) NOT NULL,
	PRIMARY KEY (`guid`, `mutedate`)
)
COMMENT='mute List' ENGINE=InnoDB;

/* add rbac permissions to new commands */
DELETE FROM `rbac_permissions` WHERE `id`=632;
INSERT INTO `rbac_permissions` (`id`,`name`) VALUES
(632, 'Command: .mutehistory');
 
/* adds qc to players */
DELETE FROM `rbac_linked_permissions` WHERE `id`=632;
INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
/* add mutehistory to gms */
(194, 632);
 
