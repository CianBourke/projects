-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Sep 09, 2026 at 02:11 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `assignmentproject`
--

-- --------------------------------------------------------

--
-- Table structure for table `books`
--

CREATE TABLE `books` (
  `ISBN` varchar(13) NOT NULL,
  `BookTitle` varchar(200) NOT NULL,
  `Author` varchar(100) DEFAULT NULL,
  `Edition` varchar(100) DEFAULT NULL,
  `Book_Year` int(11) DEFAULT NULL,
  `CategoryID` varchar(10) DEFAULT NULL,
  `reserved` char(1) DEFAULT 'N'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `books`
--

INSERT INTO `books` (`ISBN`, `BookTitle`, `Author`, `Edition`, `Book_Year`, `CategoryID`, `reserved`) VALUES
('093-403992', 'Computers in Business', 'Alicia Oneill', '3', 1997, '003', 'Y'),
('23472-8729', 'Exploring Peru', 'Stephanie Birchi', '4', 2005, '005', 'N'),
('237-34823', 'Business Strategy', 'Joe Peppard', '2', 2002, '002', 'N'),
('23u8-923849', 'A guide to nutrition', 'John Thorpe', '2', 1997, '001', 'Y'),
('2983-3494', 'Cooking for children', 'Anabelle Sharpe', '1', 2003, '007', 'Y'),
('82n8-308', 'computers for idiots', 'Susan O\'Neill', '5', 1998, '004', 'N'),
('9823-23984', 'My life in picture', 'Kevin Graham', '8', 2004, '001', 'Y'),
('9823-2403-0', 'DaVinci Code', 'Dan Brown', '1', 2003, '008', 'N'),
('9823-98345', 'How to cook Italian food', 'Jamie Oliver', '2', 2005, '007', 'Y'),
('9823-98487', 'Optimising your business', 'Cleo Blair', '1', 2001, '002', 'N'),
('98234-029384', 'My ranch in Texas', 'George Bush', '1', 2005, '001', 'Y'),
('988745-234', 'Tara Road', 'Maeve Binchy', '4', 2002, '008', 'N'),
('993-004-00', 'My life in bits', 'John Smith', '1', 2001, '001', 'Y'),
('9987-0039882', 'Shooting History', 'Jon Snow', '1', 2003, '001', 'N');

-- --------------------------------------------------------

--
-- Table structure for table `category`
--

CREATE TABLE `category` (
  `CategoryID` varchar(10) NOT NULL,
  `CategoryDescription` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `category`
--

INSERT INTO `category` (`CategoryID`, `CategoryDescription`) VALUES
('001', 'Health'),
('002', 'Biography'),
('003', 'Business'),
('004', 'Technology'),
('005', 'Travel'),
('006', 'Self-Help'),
('007', 'Cookery'),
('008', 'Fiction');

-- --------------------------------------------------------

--
-- Table structure for table `reservedbooks`
--

CREATE TABLE `reservedbooks` (
  `reservationID` int(11) NOT NULL,
  `Username` varchar(50) DEFAULT NULL,
  `ISBN` varchar(13) DEFAULT NULL,
  `reservation_date` date DEFAULT curdate()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `reservedbooks`
--

INSERT INTO `reservedbooks` (`reservationID`, `Username`, `ISBN`, `reservation_date`) VALUES
(1, 'joecrotty', '98234-029384', '2008-10-11'),
(2, 'tommy100', '9823-98345', '2008-10-11'),
(3, 'tommy100', '093-403992', '2025-12-01'),
(5, 'CianBourke_59', '2983-3494', '2025-12-02'),
(6, 'CianBourke_59', '23u8-923849', '2025-12-03'),
(9, 'Milad', '9823-23984', '2025-12-05'),
(11, 'Milad', '993-004-00', '2025-12-05');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `Username` varchar(50) NOT NULL,
  `Password` varchar(255) NOT NULL,
  `Email` varchar(100) DEFAULT NULL,
  `First_name` varchar(100) DEFAULT NULL,
  `Second_name` varchar(100) DEFAULT NULL,
  `address_line` varchar(100) DEFAULT NULL,
  `address_line2` varchar(100) DEFAULT NULL,
  `city` varchar(50) DEFAULT NULL,
  `telephone` varchar(20) DEFAULT NULL,
  `mobile` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`Username`, `Password`, `Email`, `First_name`, `Second_name`, `address_line`, `address_line2`, `city`, `telephone`, `mobile`) VALUES
('alanjmckenna', '1234$', NULL, 'Alan', 'McKenna', '38 Cranley Road', 'Fairview', 'Dublin', '9988377', '85652557'),
('CianBourke_59', '123456', 'bob59@gmail.com', 'cian', 'burke', 'nefinvrnvr', 'nriivnrivrnivr', 'dooblin', '08979585949', '1234567891'),
('joecrotty', 'kj7899', NULL, 'Joseph', 'Crotty', 'Apt 5 Clyde Road', 'Donnybrook', 'Dublin', '8887888', '87665456'),
('Milad', '123456', 'sldfkh@google.com', 'kdsjb', 'sljbh', 'skdjfb', 'vsjb', 'jskfb', '12312', '1234567890'),
('tommy100', '12345', NULL, 'Tom', 'Behan', '14 Hyde Road', 'dalkey', 'Dublin', '9983747', '876738782');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `books`
--
ALTER TABLE `books`
  ADD PRIMARY KEY (`ISBN`),
  ADD KEY `CategoryID` (`CategoryID`);

--
-- Indexes for table `category`
--
ALTER TABLE `category`
  ADD PRIMARY KEY (`CategoryID`);

--
-- Indexes for table `reservedbooks`
--
ALTER TABLE `reservedbooks`
  ADD PRIMARY KEY (`reservationID`),
  ADD KEY `Username` (`Username`),
  ADD KEY `ISBN` (`ISBN`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`Username`),
  ADD UNIQUE KEY `Email` (`Email`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `reservedbooks`
--
ALTER TABLE `reservedbooks`
  MODIFY `reservationID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `books`
--
ALTER TABLE `books`
  ADD CONSTRAINT `books_ibfk_1` FOREIGN KEY (`CategoryID`) REFERENCES `category` (`CategoryID`);

--
-- Constraints for table `reservedbooks`
--
ALTER TABLE `reservedbooks`
  ADD CONSTRAINT `reservedbooks_ibfk_1` FOREIGN KEY (`Username`) REFERENCES `users` (`Username`),
  ADD CONSTRAINT `reservedbooks_ibfk_2` FOREIGN KEY (`ISBN`) REFERENCES `books` (`ISBN`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
