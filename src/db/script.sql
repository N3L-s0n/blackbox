CREATE DATABASE IF NOT EXISTS blackboxDB;
CREATE USER IF NOT EXISTS 'blackbox'@'localhost'
    IDENTIFIED BY '2uwejs45KSdf8!4$';

GRANT SELECT, INSERT, UPDATE
    ON blackboxDB.*
    TO 'blackbox'@'localhost';

USE blackboxDB;


CREATE TABLE IF NOT EXISTS Question
(
	Email NVARCHAR(100) NOT NULL, 
    Date DATE NOT NULL, 
    Subject NVARCHAR(200) NOT NULL, 
    Description NVARCHAR(3000) NOT NULL,
    PRIMARY KEY (Email,Date)
);

CREATE TABLE IF NOT EXISTS User
(
    Email NVARCHAR(100) NOT NULL PRIMARY KEY, 
    Name NVARCHAR(100) NOT NULL,
    FirstLastName NVARCHAR(100) NULL,
    SecondLastName NVARCHAR(100) NULL,
    Password NVARCHAR(150) NOT NULL,
    Address NVARCHAR(200) NULL,
    Phone NVARCHAR(20) NULL,
    Token NVARCHAR(200) NULL
);

CREATE TABLE IF NOT EXISTS Cart
(
	Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
    PayDate DATE NOT NULL,
    UserEmail NVARCHAR(100) NOT NULL,
    CardNumber NVARCHAR(20) NULL,
    CONSTRAINT `fk_cart_user`
    FOREIGN KEY (UserEmail) REFERENCES User (Email)
);

CREATE TABLE IF NOT EXISTS CreditCard
(
    CartId INT NOT NULL PRIMARY KEY,
    CardNumber NVARCHAR(20) NULL,
    ExpirationDate NVARCHAR(10) NULL,
    CSV INT NULL,
    CardOwner NVARCHAR(200) NULL,
    FOREIGN KEY (CartId) REFERENCES Cart (Id)
);


CREATE TABLE IF NOT EXISTS Product
(
	Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
    Name NVARCHAR(200) NOT NULL, 
    Price INT NOT NULL,
    Stock INT NOT NULL,
    Description NVARCHAR(3000) NULL,
    Image NVARCHAR(100) NULL
);

CREATE TABLE IF NOT EXISTS ProductIsINCart
(
	ProductId INT NOT NULL,
    CartId INT NOT NULL,
    PRIMARY KEY (ProductId,CartId),

    CONSTRAINT `fk_product_ID`
    FOREIGN KEY (ProductId) REFERENCES Product (Id),

    CONSTRAINT `fk_cart_id`
    FOREIGN KEY (CartId) REFERENCES Cart (Id)
);


INSERT IGNORE INTO Question
(Email, Date, Subject, Description)
VALUES 
("abc@gmail.com","2022-05-14","How do I log out?", "I dont know how to log out of my account.");

INSERT IGNORE INTO User
(Email,Name,FirstLastName,SecondLastName,Password,Address,Phone,Token)
VALUES
("jane.doe@gmail.com","Jane","Doe","","Contrasena12.","Costa Rica","88888888",NULL),
("joe.doe@gmail.com","Joe","Doe","","Contrasena12.","Costa Rica","88888881",NULL);

INSERT IGNORE INTO Cart
(Id, PayDate, UserEmail)
VALUES 
(1, "2022-05-14","jane.doe@gmail.com");

INSERT IGNORE INTO CreditCard
(CartId, CardNumber, ExpirationDate, CSV, CardOwner)
VALUES
(1, "1111111111111111","12/25",123, "Jane Doe");

INSERT IGNORE INTO Product
(Id, Name, Price, Stock, Description, Image)
VALUES 
(1, "Black box",100,1,"A black box","images/blackbox.png");

INSERT IGNORE INTO ProductIsINCart
(ProductId,CartId)
VALUES
(1,1);


