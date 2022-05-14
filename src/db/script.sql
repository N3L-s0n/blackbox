-- MySQL dump 10.19  Distrib 10.3.34-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: blackboxDB
-- ------------------------------------------------------
-- Server version	10.3.34-MariaDB-0ubuntu0.20.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Cart`
--

DROP TABLE IF EXISTS `Cart`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Cart` (
  `Id` int(11) NOT NULL,
  `PayDate` date NOT NULL,
  `UserEmail` varchar(100) CHARACTER SET utf8 NOT NULL,
  `CardNumber` varchar(20) CHARACTER SET utf8 DEFAULT NULL,
  PRIMARY KEY (`Id`),
  KEY `fk_cart_user` (`UserEmail`),
  CONSTRAINT `fk_cart_user` FOREIGN KEY (`UserEmail`) REFERENCES `User` (`Email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Cart`
--

LOCK TABLES `Cart` WRITE;
/*!40000 ALTER TABLE `Cart` DISABLE KEYS */;
INSERT INTO `Cart` VALUES (1,'2022-05-14','jane.doe@gmail.com','111111111111');
/*!40000 ALTER TABLE `Cart` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Product`
--

DROP TABLE IF EXISTS `Product`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Product` (
  `Name` varchar(200) CHARACTER SET utf8 NOT NULL,
  `Price` int(11) NOT NULL,
  `Stock` bit(1) NOT NULL,
  `Description` varchar(3000) CHARACTER SET utf8 DEFAULT NULL,
  `Image` varchar(100) CHARACTER SET utf8 DEFAULT NULL,
  PRIMARY KEY (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Product`
--

LOCK TABLES `Product` WRITE;
/*!40000 ALTER TABLE `Product` DISABLE KEYS */;
INSERT INTO `Product` VALUES ('Black box',100,'','A black box','./www/imgs/blackbox.png');
/*!40000 ALTER TABLE `Product` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ProductIsINCart`
--

DROP TABLE IF EXISTS `ProductIsINCart`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ProductIsINCart` (
  `ProductName` varchar(200) CHARACTER SET utf8 NOT NULL,
  `CartId` int(11) NOT NULL,
  PRIMARY KEY (`ProductName`,`CartId`),
  KEY `fk_cart_id` (`CartId`),
  CONSTRAINT `fk_cart_id` FOREIGN KEY (`CartId`) REFERENCES `Cart` (`Id`),
  CONSTRAINT `fk_product_name` FOREIGN KEY (`ProductName`) REFERENCES `Product` (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ProductIsINCart`
--

LOCK TABLES `ProductIsINCart` WRITE;
/*!40000 ALTER TABLE `ProductIsINCart` DISABLE KEYS */;
INSERT INTO `ProductIsINCart` VALUES ('Black box',1);
/*!40000 ALTER TABLE `ProductIsINCart` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Questions`
--

DROP TABLE IF EXISTS `Questions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Questions` (
  `Email` varchar(100) CHARACTER SET utf8 NOT NULL,
  `Date` date NOT NULL,
  `Subject` varchar(200) CHARACTER SET utf8 NOT NULL,
  `Description` varchar(3000) CHARACTER SET utf8 NOT NULL,
  PRIMARY KEY (`Email`,`Date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Questions`
--

LOCK TABLES `Questions` WRITE;
/*!40000 ALTER TABLE `Questions` DISABLE KEYS */;
INSERT INTO `Questions` VALUES ('abc@gmail.com','2022-05-14','How do I log out?','I dont know how to log out of my account.');
/*!40000 ALTER TABLE `Questions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `User`
--

DROP TABLE IF EXISTS `User`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `User` (
  `Email` varchar(100) CHARACTER SET utf8 NOT NULL,
  `Name` varchar(100) CHARACTER SET utf8 NOT NULL,
  `FirstLastName` varchar(100) CHARACTER SET utf8 DEFAULT NULL,
  `SecondLastName` varchar(100) CHARACTER SET utf8 DEFAULT NULL,
  `Password` varchar(150) CHARACTER SET utf8 NOT NULL,
  `Address` varchar(200) CHARACTER SET utf8 DEFAULT NULL,
  `Phone` varchar(20) CHARACTER SET utf8 DEFAULT NULL,
  PRIMARY KEY (`Email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `User`
--

LOCK TABLES `User` WRITE;
/*!40000 ALTER TABLE `User` DISABLE KEYS */;
INSERT INTO `User` VALUES ('jane.doe@gmail.com','Jane','Doe','','Contrasena12.','Costa Rica','88888888'),('joe.doe@gmail.com','Joe','Doe','','Contrasena12.','Costa Rica','88888881');
/*!40000 ALTER TABLE `User` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-05-14 12:16:30
