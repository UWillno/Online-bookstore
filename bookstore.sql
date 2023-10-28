/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80033 (8.0.33)
 Source Host           : localhost:3306
 Source Schema         : bookstore

 Target Server Type    : MySQL
 Target Server Version : 80033 (8.0.33)
 File Encoding         : 65001

 Date: 28/10/2023 20:44:17
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for account
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `ISBN` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `delta` int NOT NULL,
  `time` datetime NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `1`(`ISBN` ASC) USING BTREE,
  CONSTRAINT `1` FOREIGN KEY (`ISBN`) REFERENCES `book` (`ISBN`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 11 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of account
-- ----------------------------
INSERT INTO `account` VALUES (1, '978-7-121-28930-9', 20, '2023-10-28 19:40:51');
INSERT INTO `account` VALUES (2, '978-7-111-53958-2', 19, '2023-10-28 19:42:09');
INSERT INTO `account` VALUES (7, '978-7-301-10315-9', 9, '2023-10-28 19:49:45');
INSERT INTO `account` VALUES (8, '978-7-5327-6496-9', 69, '2023-10-28 19:51:14');
INSERT INTO `account` VALUES (9, '978-7-01-018873-7', 32, '2023-10-28 19:52:03');
INSERT INTO `account` VALUES (10, '978-7-111-53958-2', -5, '2023-10-28 20:39:58');

-- ----------------------------
-- Table structure for book
-- ----------------------------
DROP TABLE IF EXISTS `book`;
CREATE TABLE `book`  (
  `ISBN` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `author` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `time` datetime NOT NULL,
  `type` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `count` int UNSIGNED NOT NULL COMMENT '数量',
  `price` decimal(10, 2) NOT NULL COMMENT '价格',
  `profile` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`ISBN`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of book
-- ----------------------------
INSERT INTO `book` VALUES ('978-7-01-018873-7', '马克思主义、革命与乌托邦', '赫伯特·马尔库塞', '2019-01-01 00:00:00', '其它', 32, 66.50, '无');
INSERT INTO `book` VALUES ('978-7-111-53958-2', '\nAndroid APP开发入门: 使用Android Studio环境', '施威铭', '2016-01-01 00:00:00', '计算机', 14, 8.50, '本书共分16章，内容包括使用AndroidStudio开发AndroidApp、Android程序设计基础讲座、应用程序界面设计、事件处理、用户界面的基本组件、高级UI组件、即时信息对话框、用Intent启动程序中的其他Activity、用Intent启动手机内的各种程序、拍照与显示照片等。');
INSERT INTO `book` VALUES ('978-7-121-28930-9', 'Android应用程序开发教程: Android Studio版', '罗文龙', '2016-01-01 00:00:00', '计算机', 20, 5.50, '本书基于Google最新推出的Android IDE - Android Studio和最新的Android模拟器Genymotion作为开发环境进行编写，全面介绍了Android应用开发的相关知识，内容覆盖了Android系统与开发环境、Android UI设计、基本程序单元Activity、Android应用核心Intent和Filters、Android事件处理、Android服务、Android广播接收器、ContentProvider实现数据共享、图形图像与多媒体、Android的网络编程基础、Android数据存储、GPS应用开发与百度地图等。');
INSERT INTO `book` VALUES ('978-7-301-10315-9', '英语语境语法. 3B', 'N.Elbaum', '2000-01-01 00:00:00', '英语', 9, 0.50, '本书教给学生通过语境学习英语语言，书中将英语语法学习与美国文化语境结合起来，按循序渐进的原则安排语法点，每个语法点以图表方式解释其形式、用途、语序、主语、相关结构等。本册话题包括工作、好莱坞、灾难与悲剧、消费者警告、肯尼迪家族、计算机与互联网等。');
INSERT INTO `book` VALUES ('978-7-5327-6496-9', '单向度的人: 发达工业社会意识形态研究', '赫伯特·马尔库塞', '2014-01-01 00:00:00', '其它', 69, 66.50, '本书除作者通过对政治、生活、思想、文化、语言等领域的分析、批判, 指出发达工业社会是如何成功地压制了人们内心中的否定性、批判性、超越性的向度, 使这个社会成为单向度的社会, 而生活于其中的人成了单向度的人, 这种人丧失了自由和创造力, 不再想像或追求与现实生活不同的另一种生活。');

-- ----------------------------
-- Table structure for comment
-- ----------------------------
DROP TABLE IF EXISTS `comment`;
CREATE TABLE `comment`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `userId` bigint NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `content` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `replyId` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `name`(`name` ASC) USING BTREE,
  INDEX `a`(`userId` ASC) USING BTREE,
  INDEX `comment_ibfk_2`(`replyId` ASC) USING BTREE,
  CONSTRAINT `a` FOREIGN KEY (`userId`) REFERENCES `user` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `comment_ibfk_2` FOREIGN KEY (`replyId`) REFERENCES `comment` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 44 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of comment
-- ----------------------------
INSERT INTO `comment` VALUES (41, 11111111111, '刘召辉是沙雕', '测试', NULL);
INSERT INTO `comment` VALUES (42, 11111111111, '刘召辉是沙雕', '测试测试测试测试测试测试', NULL);
INSERT INTO `comment` VALUES (43, 44910244, 'UWillno', '？？？？？？', 42);

-- ----------------------------
-- Table structure for news
-- ----------------------------
DROP TABLE IF EXISTS `news`;
CREATE TABLE `news`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `time` datetime NOT NULL,
  `content` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 9 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of news
-- ----------------------------
INSERT INTO `news` VALUES (1, '2023-10-19 19:27:00', '<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:\'Microsoft YaHei UI\'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22.5pt; font-weight:700; color:#aaaaff;\">这是什么垃圾网上书店！！</span></p></body></html>');
INSERT INTO `news` VALUES (7, '2023-10-28 19:37:07', '<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:\'Microsoft YaHei UI\'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22.5pt; font-weight:700; color:#00ff00;\">这是什么垃圾网上书店！！</span></p></body></html>');
INSERT INTO `news` VALUES (8, '2023-10-28 20:43:10', '<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:\'Microsoft YaHei UI\'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:\'Noto Sans SC\'; font-size:27.5pt; font-weight:700; font-style:italic; text-decoration: underline overline; color:#ffaa7f;\"> Are you ok ?</span></p></body></html>');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `id` bigint NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `name`(`name` ASC) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (44910244, 'UWillno', '6f9ed50efb36d8a0cc3525d1ca716a75');
INSERT INTO `user` VALUES (11111111111, '刘召辉是沙雕', 'be922252f31d95fd28c7a3e74a8bdc98');

-- ----------------------------
-- Triggers structure for table book
-- ----------------------------
DROP TRIGGER IF EXISTS `T1`;
delimiter ;;
CREATE TRIGGER `T1` AFTER INSERT ON `book` FOR EACH ROW INSERT account VALUES (NULL,NEW.ISBN,NEW.count,NOW())
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table book
-- ----------------------------
DROP TRIGGER IF EXISTS `T2`;
delimiter ;;
CREATE TRIGGER `T2` AFTER UPDATE ON `book` FOR EACH ROW INSERT into account VALUES (NULL,NEW.ISBN,CAST(NEW.count AS signed) - CAST(OLD.count AS signed),NOW())
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table comment
-- ----------------------------
DROP TRIGGER IF EXISTS `userNameT`;
delimiter ;;
CREATE TRIGGER `userNameT` BEFORE INSERT ON `comment` FOR EACH ROW set NEW.name = (SELECT name FROM `user`  WHERE id = New.userId)
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table comment
-- ----------------------------
DROP TRIGGER IF EXISTS `userNameT1`;
delimiter ;;
CREATE TRIGGER `userNameT1` BEFORE UPDATE ON `comment` FOR EACH ROW set NEW.name = (SELECT name FROM `user`  WHERE id = New.userId)
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table user
-- ----------------------------
DROP TRIGGER IF EXISTS `md5pwd`;
delimiter ;;
CREATE TRIGGER `md5pwd` BEFORE INSERT ON `user` FOR EACH ROW set NEW.password = MD5(NEW.password)
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table user
-- ----------------------------
DROP TRIGGER IF EXISTS `md5pwd1`;
delimiter ;;
CREATE TRIGGER `md5pwd1` BEFORE UPDATE ON `user` FOR EACH ROW set NEW.password = MD5(NEW.password)
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
