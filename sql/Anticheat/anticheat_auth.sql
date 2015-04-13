DELETE FROM rbac_linked_permissions WHERE id = 194 and linkedId=805;
INSERT INTO `rbac_linked_permissions` VALUES ('194', '805');
DELETE FROM rbac_linked_permissions WHERE id = 196 and linkedId IN(800, 802, 803);
INSERT INTO `rbac_linked_permissions` VALUES ('196', '800');
INSERT INTO `rbac_linked_permissions` VALUES ('196', '802');
INSERT INTO `rbac_linked_permissions` VALUES ('196', '803');
DELETE FROM rbac_linked_permissions WHERE id = 198 and linkedId IN(799, 801, 804);
INSERT INTO `rbac_linked_permissions` VALUES ('198', '799');
INSERT INTO `rbac_linked_permissions` VALUES ('198', '801');
INSERT INTO `rbac_linked_permissions` VALUES ('198', '804');

DELETE FROM rbac_permissions WHERE id IN (799, 800, 801, 802, 803, 804, 805);
INSERT INTO `rbac_permissions` VALUES ('799', 'Command: .anticheat');
INSERT INTO `rbac_permissions` VALUES ('800', 'Command: .anticheat global');
INSERT INTO `rbac_permissions` VALUES ('801', 'Command: .anticheat player');
INSERT INTO `rbac_permissions` VALUES ('802', 'Command: .anticheat delete');
INSERT INTO `rbac_permissions` VALUES ('803', 'Command: .anticheat handle');
INSERT INTO `rbac_permissions` VALUES ('804', 'Command: .anticheat jail');
INSERT INTO `rbac_permissions` VALUES ('805', 'Skip check anticheat');