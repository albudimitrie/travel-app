SELECT TOP(100) *
FROM Users

CREATE TABLE Wallet
(
	ID int PRIMARY KEY IDENTITY(1,1),
	username int FOREIGN KEY REFERENCES Users(ID) not null,
	balance real not null CHECK(balance>=0) 
);

CREATE TABLE Destinations (
    DestinationID INT PRIMARY KEY IDENTITY(1,1),
    Name NVARCHAR(100) NOT NULL,
    Country NVARCHAR(50) NOT NULL,
    City NVARCHAR(50) NOT NULL,
    Description NVARCHAR(MAX),
    Climate NVARCHAR(50),
    Image NVARCHAR(255),
    IsActive BIT DEFAULT 1 --poate fi vizitat
);

CREATE TABLE Attractions (
    AttractionID INT PRIMARY KEY IDENTITY(1,1),
    DestinationID INT FOREIGN KEY REFERENCES Destinations(DestinationID),
    Name NVARCHAR(100) NOT NULL,
    Description NVARCHAR(MAX),
    Category NVARCHAR(50),
    TicketPrice DECIMAL(10,2),
    Image NVARCHAR(255)
);

CREATE TABLE Accommodations (
    AccommodationID INT PRIMARY KEY IDENTITY(1,1),
    DestinationID INT FOREIGN KEY REFERENCES Destinations(DestinationID),
    Name NVARCHAR(100) NOT NULL,
    Type NVARCHAR(50) NOT NULL, -- Hotel, Pensiune, Apartament
    Address NVARCHAR(255),
    Description NVARCHAR(MAX),
    PricePerNight DECIMAL(10,2) NOT NULL,
    Facilities NVARCHAR(MAX), --ce facilitati dispune cazarea
    Image NVARCHAR(255) -- path imagine
);

CREATE TABLE Transportation (
    TransportationID INT PRIMARY KEY IDENTITY(1,1),
    Type NVARCHAR(50) NOT NULL, 
    Company NVARCHAR(100),
    Description NVARCHAR(MAX),
    PricePerKm DECIMAL(10,2),
    Capacity INT,
    ComfortLevel NVARCHAR(50) -- Economic, Business, etc.
);

CREATE VIEW Cazari AS
SELECT A.*, D.Name as DestinationName, D.City, D.Country
FROM Accommodations as A
INNER JOIN Destinations as D
ON D.DestinationID = A.DestinationID


