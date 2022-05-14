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
    Phone NVARCHAR(20) NULL
);

CREATE TABLE Cart
(
	Id INT NOT NULL PRIMARY KEY, 
    PayDate DATE NOT NULL,
    UserEmail NVARCHAR(100) NOT NULL,
    CardNumber NVARCHAR(20),
    CONSTRAINT `fk_cart_user`
    FOREIGN KEY (UserEmail) REFERENCES User (Email)
);


CREATE TABLE Product
(
	Name NVARCHAR(200) NOT NULL PRIMARY KEY, 
    Price INT NOT NULL,
    Stock BIT NOT NULL,
    Description NVARCHAR(3000) NULL,
    Image NVARCHAR(100) NULL
);

CREATE TABLE ProductIsINCart
(
	ProductName NVARCHAR(200) NOT NULL,
    CartId INT NOT NULL,
    PRIMARY KEY (ProductName,CartId),

    CONSTRAINT `fk_product_name`
    FOREIGN KEY (ProductName) REFERENCES Product (Name),

    CONSTRAINT `fk_cart_id`
    FOREIGN KEY (CartId) REFERENCES Cart (Id)
);


INSERT INTO Questions
(Email, Date, Subject, Description)
VALUES 
("abc@gmail.com","2022-05-14","How do I log out?", "I dont know how to log out of my account.");

INSERT INTO User
(Email,Name,FirstLastName,SecondLastName,Password,Address,Phone)
VALUES
("jane.doe@gmail.com","Jane","Doe","","Contrasena12.","Costa Rica","88888888"),
("joe.doe@gmail.com","Joe","Doe","","Contrasena12.","Costa Rica","88888881");

INSERT INTO Cart
(Id, PayDate, UserEmail, CardNumber)
VALUES 
(1,"2022-05-14","jane.doe@gmail.com","111111111111");

INSERT INTO Product
(Name, Price, Stock, Description, Image)
VALUES 
("Black box",100,1,"A black box","./www/imgs/blackbox.png");

INSERT INTO ProductIsINCart
(ProductName,CartId)
VALUES
("Black box",1);


