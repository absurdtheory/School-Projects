DROP TABLE IF EXISTS `Orders`;
DROP TABLE IF EXISTS `Works`;
DROP TABLE IF EXISTS `Dogs`;
DROP TABLE IF EXISTS `Adopters`;
DROP TABLE IF EXISTS `FoodSupply`;
DROP TABLE IF EXISTS `Employees`;

CREATE TABLE `Adopters` (
`id` int NOT NULL AUTO_INCREMENT,
`fname` varchar(255) NOT NULL,
`lname` varchar(255) NOT NULL,
`saddress` varchar(255) NOT NULL,
`city` varchar(255) NOT NULL,
`state` varchar(255) NOT NULL,
`zip` varchar(255) NOT NULL,
`phone` varchar(255) NOT NULL,
PRIMARY KEY (`id`)
) ENGINE=InnoDB;


INSERT INTO `Adopters` (`id`, `fname`, `lname`, `saddress`, `city`, `state`, `zip`, `phone`) VALUES
(1, 'Alexis', 'Tucker', '12345 Abc Street', 'Fairfax', 'Virginia', '12345', '(111)222-3333'),
(2, 'Gabrielle', 'Mamani', '1600 Pennsylvania Ave.', 'Washington DC', 'Washington DC', '12344', '(444)555-6666'),
(3, 'Nicolas', 'Scherrs', '1826 MidNowhere Lane', 'Eau Claire', 'Wisconsin', '56431', '(566)123-4567');


CREATE TABLE `Employees` (
`id` int NOT NULL AUTO_INCREMENT,
`fname` varchar(255) NOT NULL,
`lname` varchar(255) NOT NULL,
`fsa` boolean NOT NULL DEFAULT FALSE,
`phone` varchar(255) NOT NULL,
`title` varchar(255) NOT NULL,
PRIMARY KEY (`id`)
) ENGINE=InnoDB;


INSERT INTO `Employees` (`id`, `fname`, `lname`, `fsa`, `phone`, `title`) VALUES
(1, 'Nick', 'Haase', 1, '(222) 333-4444', 'CEO'),
(2, 'Chelsea', 'Norod', 0, '(777)888-9999', 'Vet'),
(3, 'Robin', 'DeRosa', 1, '(123)456-7890', 'Event Coordinator'),
(12, 'Rebecca', 'Cole', 1, '(345)134-2345', 'Manager');



CREATE TABLE `FoodSupply` (
`id` int NOT NULL AUTO_INCREMENT,
`bname` varchar(255) NOT NULL,
`pname` varchar(255) NOT NULL,
`amount` int NOT NULL DEFAULT '0',
PRIMARY KEY (`id`)
) ENGINE=InnoDB;


INSERT INTO `FoodSupply` (`id`, `bname`, `pname`, `amount`) VALUES
(1, 'Natural Balance', 'Sweet Potato & Fish', 5),
(2, 'Performatin Ultra', 'Chicken and Sweet Potato', 5),
(3, 'Performatin Ultra', 'Limited Ingredient Venison & Sweet Potato', 15);



CREATE TABLE `Dogs` (
`id` int NOT NULL AUTO_INCREMENT,
`name` varchar(255) NOT NULL,
`birthdate` date NOT NULL,
`breed` varchar(255) NOT NULL,
`sex` varchar(255) NOT NULL,
`adoptedBy` int,
`foodType` int NOT NULL,
`image` varchar(255),
PRIMARY KEY (`id`),
FOREIGN KEY (`adoptedBy`) REFERENCES Adopters(`id`) ON DELETE SET NULL,
FOREIGN KEY (`foodType`) REFERENCES FoodSupply(`id`)
) ENGINE=InnoDB;


INSERT INTO `Dogs` (`id`, `name`, `birthdate`, `breed`, `sex`, `adoptedBy`, `foodType`, `image`) VALUES
(1, 'Natalia', '2014-04-04', 'Papillion/ Pekingese Mix', 'Female', 2, 1, '/static/images/natasha.jpg'),
(2, 'Kingston', '2014-12-14', 'Cockapoo', 'Male', NULL, 2, '/static/images/kingston.jpg'),
(3, 'Loki', '2012-06-06', 'Norwegian Elkhound', 'Male', 2, 2, NULL),
(5, 'Milla', '2012-12-05', 'Husky Mix', 'Female', 3, 2, '/static/images/milla.jpg'),
(6, 'Gypsy', '2014-07-13', 'Blue Heeler Mix', 'Female', 3, 1, ''),
(10, 'Oliver', '2018-02-21', 'Papillion', 'Male', NULL, 1, '/static/images/papillon.jpg'),
(11, 'Fluffy', '2016-10-12', 'Poodle', 'Female', NULL, 2, 'https://images.unsplash.com/photo-1505044197374-4d4ae3f9d566?ixlib=rb-0.3.5&ixid=eyJhcHBfaWQiOjEyMDd9&s=af3dab3922f397a5fde45b3145a0cbdb&auto=format&fit=crop&w=1868&q=80'),
(12, 'Rex', '2016-12-25', 'Golden Retriever', 'Female', NULL, 3, 'https://s3.amazonaws.com/cdn-origin-etr.akc.org/wp-content/uploads/2017/11/12232719/Golden-Retriever-On-White-05.jpg'),
(14, 'Spudz ', '2016-12-25', 'chocolate lab', 'Male', NULL, 1, '');


CREATE TABLE `Orders` (
`FoodSupplyID` int NOT NULL,
`EmployeeID` int NOT NULL,
`DateOrdered` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
`quantity` int NOT NULL,
PRIMARY KEY(`FoodSupplyID`, `EmployeeID`, `DateOrdered`),
FOREIGN KEY(`FoodSupplyID`) REFERENCES `FoodSupply`(`id`) ON DELETE CASCADE ON UPDATE CASCADE,
FOREIGN KEY(`EmployeeID`) REFERENCES `Employees`(`id`) ON DELETE CASCADE ON UPDATE CASCADE
)ENGINE=InnoDB; 


INSERT INTO `Orders` VALUES (1, 1, DEFAULT, 5), (1, 2, DEFAULT, 10);


CREATE TABLE `Works` (
`EmployeeID` int NOT NULL,
`DogID` int NOT NULL,
PRIMARY KEY(`EmployeeID`, `DogID`),
FOREIGN KEY(`EmployeeID`) REFERENCES `Employees`(`id`) ON DELETE CASCADE,
FOREIGN KEY(`DogID`) REFERENCES `Dogs`(`id`) ON DELETE CASCADE
) ENGINE=InnoDB;

INSERT INTO `Works` (`EmployeeID`, `DogID`) VALUES
(1, 1),
(1, 2),
(1, 11),
(2, 3),
(12, 6);


