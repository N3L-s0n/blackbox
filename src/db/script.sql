CREATE DATABASE blackboxDB;

USE blackboxDB;


CREATE TABLE Questions
(
	Email NVARCHAR(100) NOT NULL, 
    Date DATE NOT NULL, 
    Subject NVARCHAR(200) NOT NULL, 
    Description NVARCHAR(3000) NOT NULL,
    PRIMARY KEY (Email,Date)
);

CREATE TABLE User
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

CREATE TABLE Cart
(
	Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
    PayDate DATE NOT NULL,
    UserEmail NVARCHAR(100) NOT NULL,
    CardNumber NVARCHAR(20) NULL,
    CONSTRAINT `fk_cart_user`
    FOREIGN KEY (UserEmail) REFERENCES User (Email)
);


CREATE TABLE Product
(
	Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
    Name NVARCHAR(200) NOT NULL, 
    Price INT NOT NULL,
    Stock BIT NOT NULL,
    Description NVARCHAR(3000) NULL,
    Image NVARCHAR(100) NULL
);

CREATE TABLE ProductIsINCart
(
	ProductId INT NOT NULL,
    CartId INT NOT NULL,
    PRIMARY KEY (ProductId,CartId),

    CONSTRAINT `fk_product_ID`
    FOREIGN KEY (ProductId) REFERENCES Product (Id),

    CONSTRAINT `fk_cart_id`
    FOREIGN KEY (CartId) REFERENCES Cart (Id)
);


INSERT INTO Questions
(Email, Date, Subject, Description)
VALUES 
("abc@gmail.com","2022-05-14","How do I log out?", "I dont know how to log out of my account.");

INSERT INTO User
(Email,Name,FirstLastName,SecondLastName,Password,Address,Phone,Token)
VALUES
("jane.doe@gmail.com","Jane","Doe","","Contrasena12.","Costa Rica","88888888",NULL),
("joe.doe@gmail.com","Joe","Doe","","Contrasena12.","Costa Rica","88888881",NULL);

INSERT INTO Cart
(PayDate, UserEmail, CardNumber)
VALUES 
("2022-05-14","jane.doe@gmail.com","111111111111");

INSERT INTO Product
(Name, Price, Stock, Description, Image)
VALUES 
("Black box",100,1,"A black box","./www/imgs/blackbox.png");

INSERT INTO ProductIsINCart
(ProductId,CartId)
VALUES
(1,1);


