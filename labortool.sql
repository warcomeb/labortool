-- phpMyAdmin SQL Dump
-- version 4.2.7.1
-- http://www.phpmyadmin.net
--
-- Host: localhost:3306
-- Generation Time: Set 23, 2014 alle 10:31
-- Versione del server: 5.5.39
-- PHP Version: 5.4.32

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `labortool`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `production`
--

CREATE TABLE IF NOT EXISTS `production` (
`ProductionId` int(11) NOT NULL,
  `ProductionBoardName` varchar(100) NOT NULL,
  `ProductionQuantity` int(5) NOT NULL,
  `ProductionDescription` text NOT NULL,
  `ProductionWorkCode` varchar(12) NOT NULL,
  `ProductionOutputCode` varchar(20) NOT NULL,
  `ProductionDeadline` date NOT NULL,
  `ProductionStatus` enum('NotStarted','InProgress','Ended','Postponed','Waiting') NOT NULL,
  `ProductionEmployee` int(11) NOT NULL,
  `ProductionSupplier` int(11) NOT NULL,
  `ProductionActivityId` int(12) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struttura della tabella `activity`
--

CREATE TABLE IF NOT EXISTS `activity` (
`ActivityId` int(11) NOT NULL,
  `ActivityTitle` varchar(100) NOT NULL,
  `ActivityDescription` text NOT NULL,
  `ActivityWorkCode` varchar(12) NOT NULL,
  `ActivityDeadline` date NOT NULL,
  `ActivityPriority` enum('Low','Medium','High','Now') NOT NULL DEFAULT 'Medium',
  `ActivityStatus` enum('NotStarted','InProgress','Ended','Postponed','Waiting') NOT NULL,
  `ActivityType` enum('Board','Repair','Support','Firmware','Production') NOT NULL,
  `ActivityEmployee` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struttura della tabella `employee`
--

CREATE TABLE IF NOT EXISTS `employee` (
`EmployeeId` int(11) NOT NULL,
  `EmployeeName` varchar(50) NOT NULL,
  `EmployeeSurname` varchar(50) NOT NULL,
  `EmployeeUsername` varchar(20) NOT NULL,
  `EmployeePassword` varchar(40) NOT NULL,
  `EmployeeNote` text NOT NULL,
  `EmployeeRole` enum('Coordinator','SeniorDesigner','Designer','Technician','Student') NOT NULL,
  `EmployeeSysRole` enum('Administrator','Editor','User') NOT NULL,
  `EmployeeCompany` enum('Aea','Gi','Extern') NOT NULL,
  `EmployeeActive` enum('Yes','No') NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `activity`
--
ALTER TABLE `activity`
 ADD PRIMARY KEY (`ActivityId`), ADD UNIQUE KEY `ActivityId` (`ActivityId`);

--
-- Indexes for table `production`
--
ALTER TABLE `production`
 ADD PRIMARY KEY (`ProductionId`), ADD UNIQUE KEY `ProductionId` (`ProductionId`);

--
-- Indexes for table `employee`
--
ALTER TABLE `employee`
 ADD PRIMARY KEY (`EmployeeId`), ADD UNIQUE KEY `EmployeeId` (`EmployeeId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `production`
--
ALTER TABLE `production`
MODIFY `ProductionId` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `activity`
--
ALTER TABLE `activity`
MODIFY `ActivityId` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `employee`
--
ALTER TABLE `employee`
MODIFY `EmployeeId` int(11) NOT NULL AUTO_INCREMENT;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
