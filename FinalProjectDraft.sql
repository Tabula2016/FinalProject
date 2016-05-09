-- MySQL dump 10.13  Distrib 5.5.47, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: TicketingSystem
-- ------------------------------------------------------
-- Server version	5.5.47-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Assignment`
--

DROP TABLE IF EXISTS `Assignment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Assignment` (
  `AssignmentID` int(11) NOT NULL AUTO_INCREMENT,
  `TicketID_FK` int(10) DEFAULT NULL,
  `AssignedUser_FK` int(10) DEFAULT NULL,
  PRIMARY KEY (`AssignmentID`),
  KEY `AssignedUser_FK_idx` (`AssignedUser_FK`),
  KEY `TicketID_FK_idx` (`TicketID_FK`),
  CONSTRAINT `AssignedUser_FK` FOREIGN KEY (`AssignedUser_FK`) REFERENCES `login` (`LoginID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `TicketID_FK` FOREIGN KEY (`TicketID_FK`) REFERENCES `Tickets` (`TicketID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Assignment`
--

LOCK TABLES `Assignment` WRITE;
/*!40000 ALTER TABLE `Assignment` DISABLE KEYS */;
INSERT INTO `Assignment` VALUES (5,21,NULL),(9,30,24),(10,31,23),(11,32,NULL);
/*!40000 ALTER TABLE `Assignment` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CommentsTable`
--

DROP TABLE IF EXISTS `CommentsTable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CommentsTable` (
  `TicketID_FK_1` int(10) DEFAULT NULL,
  `comments` varchar(255) DEFAULT NULL,
  `CommentsID` int(10) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`CommentsID`),
  KEY `TicketID_FK_1_idx` (`TicketID_FK_1`),
  CONSTRAINT `TicketID_FK_1` FOREIGN KEY (`TicketID_FK_1`) REFERENCES `Tickets` (`TicketID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CommentsTable`
--

LOCK TABLES `CommentsTable` WRITE;
/*!40000 ALTER TABLE `CommentsTable` DISABLE KEYS */;
INSERT INTO `CommentsTable` VALUES (19,'Hello, this is a comment for ticket 19 #1',3),(19,'Hello, this is a comment for ticket 19 #2',4);
/*!40000 ALTER TABLE `CommentsTable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Tickets`
--

DROP TABLE IF EXISTS `Tickets`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Tickets` (
  `TicketID` int(10) NOT NULL AUTO_INCREMENT,
  `title` varchar(255) DEFAULT NULL,
  `Category` enum('Hardware','Software','Networking') DEFAULT NULL,
  `Severity` enum('1','2','3','4','5') DEFAULT NULL,
  `Createdby` varchar(32) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `status` enum('Open','Closed','Acknowledged','Active','Resolved') DEFAULT NULL,
  PRIMARY KEY (`TicketID`)
) ENGINE=InnoDB AUTO_INCREMENT=44 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tickets`
--

LOCK TABLES `Tickets` WRITE;
/*!40000 ALTER TABLE `Tickets` DISABLE KEYS */;
INSERT INTO `Tickets` VALUES (19,'Mouse not working','Hardware','4','user3','Mice are not fun and stupid','Open'),(20,'testticket1','Hardware','5','mohmmad','this is a test ticket','Closed'),(21,'testticket1','Hardware','5','mohmmad','this is a test ticket','Open'),(30,'printer not working 3','Hardware','3','user3','Printer is broken 3','Open'),(31,'testticket5','Software','1','mohmmad','this is a test ticket 2','Open'),(32,'testticket6','Software','2','mohmmad','this is a test ticket 6','Open');
/*!40000 ALTER TABLE `Tickets` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `login`
--

DROP TABLE IF EXISTS `login`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `login` (
  `LoginID` int(10) NOT NULL AUTO_INCREMENT,
  `username` varchar(32) DEFAULT NULL,
  `password` varchar(32) DEFAULT NULL,
  `privilegeLevel` enum('admin','manager','user') DEFAULT NULL,
  `reportsto` varchar(30) DEFAULT NULL,
  `AssignedTickets` int(11) NOT NULL,
  PRIMARY KEY (`LoginID`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `login`
--

LOCK TABLES `login` WRITE;
/*!40000 ALTER TABLE `login` DISABLE KEYS */;
INSERT INTO `login` VALUES (1,'Paul','e77722d198f0aea70e70','manager',NULL,0),(2,'mohmmad','971e25d7fa089f774e0f','admin',NULL,1),(21,'user1','e77722d198f0aea70e70','admin','mohmmad',0),(22,'user2','e77722d198f0aea70e70','user','Paul',0),(23,'user3','e77722d198f0aea70e70','user','Paul',2),(24,'user4','e77722d198f0aea70e70','user','Paul',1);
/*!40000 ALTER TABLE `login` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-05-09  5:08:37
