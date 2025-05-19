SELECT TOP(100) *
FROM Users


SELECT *
FROM Accommodations


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

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Destinatie Test', 'TaraTest', 'OrasTest', 'DescriereTest', 'ClimatTest', 1)

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Destinatie Test2', 'TaraTest2', 'OrasTest2', 'DescriereTest2', 'ClimatTest2', 1)

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Destinatie Test3', 'TaraTest3', 'OrasTest3', 'DescriereTest3', 'ClimatTest3', 1)


SELECT *
FROM Destinations

SELECT DestinationID, Name, Country, City, Description, Climate , IsActive FROM Destinations WHERE DestinationID = 2 ORDER BY DestinationID DESC

CREATE TABLE Attractions (
    AttractionID INT PRIMARY KEY IDENTITY(1,1),
    DestinationID INT FOREIGN KEY REFERENCES Destinations(DestinationID),
    Name NVARCHAR(100) NOT NULL,
    Description NVARCHAR(MAX),
    Category NVARCHAR(50),
    TicketPrice DECIMAL(10,2),
    Image NVARCHAR(255)
);

SELECt * from Attractions

INSERT INTO Attractions(DestinationID, Name, Description, Category, TicketPrice, Image) VALUES
(2, 'Castelul Corvinilor', 'Printre cele mai fotografiate obiective turistice din Romania, castelul Corvinilor este un monument arhitectural ce dateaza din secolul al XVI-lea si este reprezentativ pentru arta feudala gotica din Europa. Printre legendele castelului, de mentionat ar fi Legenda Fantanii si Groapa Ursilor.
' , 'CULTURAL', 50,  'D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\cultural1.jpg')


INSERT INTO Attractions(DestinationID, Name, Description, Category, TicketPrice, Image) VALUES
(3, 'Concert UNTOLD Editia X', 'Un lineup diversificat, care include artisti mainstream si undergorund, show-uri vizuale impresionante, fiecare editie a festivalului UNTOLD se transforma intr-un univers, care atrage anual zeci de mii de fani din toate colturile lumii, pentru ca muzica are o magie unica, capabila sa transmita senzatii pe care cuvintele pur si simplu nu le pot reda.
' , 'MUSICAL', 200,  'D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\musical1.jpg')

INSERT INTO Attractions(DestinationID, Name, Description, Category, TicketPrice, Image) VALUES
(1, 'Manastirea Putna', 'Manastirea Putna este unul din cele mai importante centre culturale, religioase si artistice romanesti ridicata de domnitorul Stefan Cel Mare, fiind un lacas monarhal orthodox, supranumit “Ierusalimul Neamului Romanesc”, prima ctitorie a domnitorului, unul din promoterii stilului moldovenesc care il stim azi…'
, 'RELIGIOUS', 30,'D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\religious1.jpg' )

--DEASUPRA O SA TREBUIASCA SA SCHIMB DESTINATIILE CU UN UPDATE

Update Attractions
Set Description = 'Gol'
Where AttractionID =5


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

INSERT INTO Accommodations(DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(1, 'CazareTest', 'HOTEL', 'adresa test', 'descriere test', 20, 'facilitati test')

INSERT INTO Accommodations(DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(2, 'CazareTest2', 'HOTEL2', 'adresa test2', 'descriere test2', 40, 'facilitati test2')

INSERT INTO Accommodations(DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(2, 'CazareTest3', 'APARTAMENT', 'adresa test3', 'descriere test3', 40, 'facilitati test3')

INSERT INTO Accommodations(DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(2, 'CazareTest4', 'PENSIUNE', 'adresa test4', 'descriere test34', 40, 'facilitati test4')


INSERT INTO Accommodations(DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(2, 'CazareTest5', 'PENSIUNE', 'adresa test4', 'descriere test34', 40, 'facilitati test4')

INSERT INTO Accommodations(DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(2, 'CazareTest6', 'PENSIUNE', 'adresa test4', 'descriere test34', 40, 'facilitati test4')

INSERT INTO Accommodations(DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(2, 'CazareTest7', 'PENSIUNE', 'adresa test4', 'descriere test34', 40, 'facilitati test4')

INSERT INTO Accommodations(DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(2, 'CazareTest8', 'PENSIUNE', 'adresa test4', 'descriere test34', 40, 'facilitati test4')


UPDATE Accommodations
SET Image ='C:\Users\albua\OneDrive\Pictures\windows.jpg'
WHERE AccommodationID=5;
UPDATE Accommodations
SET Image ='C:\Users\albua\OneDrive\Pictures\windows.jpg'
WHERE AccommodationID=6;
UPDATE Accommodations
SET Image ='C:\Users\albua\OneDrive\Pictures\windows.jpg'
WHERE AccommodationID=7;
UPDATE Accommodations
SET Image ='C:\Users\albua\OneDrive\Pictures\windows.jpg'
WHERE AccommodationID=8;





UPDATE Accommodations
SET Image ='C:\Users\albua\OneDrive\Pictures\Capture.PNG'
WHERE AccommodationID=4;


UPDATE Accommodations
SET Image ='C:\Users\albua\OneDrive\Pictures\windows.jpg',
DestinationID = 3
WHERE AccommodationID=3;

UPDATE Accommodations
SET Image ='C:\Users\albua\OneDrive\Pictures\2.jpg'
WHERE AccommodationID=1;

UPDATE Accommodations
SET Image ='C:\Users\albua\OneDrive\Pictures\3.jpg',
Type = 'HOTEL' 
WHERE AccommodationID=2;

CREATE TABLE Transportation (
    TransportationID INT PRIMARY KEY IDENTITY(1,1),
    Type NVARCHAR(50) NOT NULL, 
    Company NVARCHAR(100),
    Description NVARCHAR(MAX),
    PricePerKm DECIMAL(10,2),
    Capacity INT,
    ComfortLevel NVARCHAR(50) -- Economic, Business, etc.
);

ALTER TABLE Transportation
ADD Image VARCHAR(200);


INSERT INTO Transportation(Type, Company, Description, PricePerKm, Capacity, ComfortLevel, Image) VALUES
('PLANE' , 'WIZZ AIR', 'Wizz Air este o companie aeriana low-cost originara din Ungaria, fondata in 2003, care opereaza zboruri in principal in Europa, dar si catre Orientul Mijlociu, Asia Centrala si nordul Africii. Cu o flota moderna formata in mare parte din aeronave Airbus A320 si A321, Wizz Air ofera zboruri la preturi accesibile si se concentreaza pe eficienta operationala si costuri reduse.',
0.5, 100, 'Economic','D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\avion1.png' )

INSERT INTO Transportation(Type, Company, Description, PricePerKm, Capacity, ComfortLevel, Image) VALUES
('TRAIN', 'CFR CALATORI', 'CFR Calatori este operatorul national de transport feroviar de pasageri din Romania, oferind servicii de calatorie la nivel local, regional si national, cu scopul de a asigura mobilitatea cetatenilor printr-o retea extinsa de trenuri.',
0.2, 500, 'ECONOMIC', 'D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\tren1.jpg')

INSERT INTO Transportation(Type, Company, Description, PricePerKm, Capacity, ComfortLevel, Image) VALUES
('TRAIN', 'TransRegio', 'Acesta asigura servicii de transport feroviar si rutier de calatori, inclusiv curse regulate si speciale, in colaborare cu autoritatile locale si regionale. TransRegio are rolul de a conecta localitatile din judetul Bihor si din judetele invecinate, facilitand mobilitatea cetatenilor si integrarea acestora in sistemul de transport public national.',
0.2, 500, 'ECONOMIC', 'D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\tren2.jpg')

UPDATE Transportation
SET ComfortLevel = 'Economic'
WHERE TransportationID = 2

UPDATE Transportation
Set Description = 'Gol'
WHERE TransportationID = 4


SELECT * FROM Transportation

SELECT * From Attractions

CREATE VIEW Cazari AS
SELECT A.*, D.Name as DestinationName, D.City, D.Country
FROM Accommodations as A
INNER JOIN Destinations as D
ON D.DestinationID = A.DestinationID


CREATE TABLE RoutesTransportation
(
	RouteID int PRIMARY KEY IDENTITY(1,1),
	TransportationID int FOREIGN KEY REFERENCES Transportation(TransportationID) not null,
	CityDeparture varchar(50) not null,
	CityArrival varchar(50) not null,
	Distance decimal not null,
	Duration decimal not null
);

SELECT *
FROM Transportation

INSERT INTO RoutesTransportation(TransportationID, CityDeparture, CityArrival, Distance, Duration) VALUES
(1, 'Bucuresti', 'Milano', 1000, 5),
(2, 'Roman', 'Bucuresti', 300, 6),
(2, 'Suceava', 'Roman', 100, 2)



CREATE TABLE Trips
(
	TripID int PRIMARY KEY IDENTITY(1,1),
	UserID int FOREIGN KEY REFERENCES Users(ID) not null,
	StartDate datetime not null,
	EndDate datetime not null,
	Duration decimal not null,	--durata in numar de zile
	isConfirmed bit not null DEFAULT 0,
	totalCost float not null default 0
);


Create table GeneratedTrips
(
	TripID int PRIMARY KEY IDENTITY(1,1),
	UserID int FOREIGN KEY REFERENCES Users(ID) not null,
	StartDate datetime not null,
	EndDate datetime not null,
	Duration decimal not null,	--durata in numar de zile
	isConfirmed bit not null DEFAULT 0,
	totalCost float not null default 0

)




SELECT *
FROM Users

CREATE TABLE TripsDays
(
	ID int PRIMARY KEY IDENTITY(1,1),
	TripID int FOREIGN KEY REFERENCES Trips(TripID) not null,
	DayNumber decimal not null,
	AccommodationID int FOREIGN KEY References Accommodations(AccommodationID) not null,
	AttractionID int FOREIGN KEY References Attractions(AttractionID) not null,
	RouteID int FOREIGN KEY References RoutesTransportation(RouteID) not null,
);




CREATE TABLE GeneratedTripsDays
(
	ID int PRIMARY KEY IDENTITY(1,1),
	TripID int FOREIGN KEY REFERENCES GeneratedTrips(TripID) not null,
	DayNumber decimal not null,
	AccommodationID int FOREIGN KEY References Accommodations(AccommodationID) not null,
	AttractionID int FOREIGN KEY References Attractions(AttractionID) not null,
	RouteID int FOREIGN KEY References RoutesTransportation(RouteID) not null,
);


IF OBJECT_ID('CreateTrip', 'P') is not null
	DROP PROC CreateTrip;
GO
CREATE PROCEDURE CreateTrip
	@UID int ,
	@startDate datetime,
	@endDate datetime ,
	@duration decimal ,
	@isConfirmed bit = 0,
	@totalCost float =0
AS
BEGIN
	INSERT INTO Trips(UserID, StartDate, EndDate, Duration, isConfirmed, totalCost) VALUES
	(@UID, @startDate, @endDate, @duration, @isConfirmed, @totalCost)
END;


IF OBJECT_ID('CreateGeneratedTrip', 'P') is not null
	DROP PROC CreateGeneratedTrip;
GO
CREATE PROCEDURE CreateGeneratedTrip
	@UID int ,
	@startDate datetime,
	@endDate datetime ,
	@duration decimal ,
	@isConfirmed bit = 0,
	@totalCost float =0
AS
BEGIN
	INSERT INTO GeneratedTrips(UserID, StartDate, EndDate, Duration, isConfirmed, totalCost) VALUES
	(@UID, @startDate, @endDate, @duration, @isConfirmed, @totalCost)
END;



IF OBJECT_ID('AddDayTrip', 'P') is not null
	DROP PROCEDURE AddDayTrip;
GO
CREATE PROCEDURE AddDayTrip 
	@TripID int,
	@DayNumber decimal,
	@AccommodationID int,
	@AttractionID int,
	@RouteID int
AS
BEGIN
	INSERT INTO TripsDays(TripID, DayNumber, AccommodationID, AttractionID, RouteID) VALUES
	(@TripID, @DayNumber, @AccommodationID, @AttractionID, @RouteID)
END;


IF OBJECT_ID('AddGeneratedDayTrip', 'P') is not null
	DROP PROCEDURE AddGeneratedDayTrip;
GO
CREATE PROCEDURE AddGeneratedDayTrip 
	@TripID int,
	@DayNumber decimal,
	@AccommodationID int,
	@AttractionID int,
	@RouteID int
AS
BEGIN
	INSERT INTO GeneratedTripsDays(TripID, DayNumber, AccommodationID, AttractionID, RouteID) VALUES
	(@TripID, @DayNumber, @AccommodationID, @AttractionID, @RouteID)
END;




SELECT *
FROM Trips

DELETE FROM Trips

SELECT *
From TripsDays

TRUNCATE Table TripsDays

SELECT *
FROM Attractions

SELECT *
FROM RoutesTransportation

SELECT *
FROM Transportation


CREATE TRIGGER trg_RecalculateTotalCost_AfterInsert
ON TripsDays
AFTER INSERT
AS
BEGIN
    SET NOCOUNT ON;
    UPDATE T
    SET totalCost = ISNULL(Total.Total, 0)
    FROM Trips T
    INNER JOIN (
        SELECT
            TD.TripID,
            SUM(
                ISNULL(A.PricePerNight, 0) + 
                ISNULL(AT.TicketPrice, 0) + 
                ISNULL(TS.PricePerKm * R.Distance, 0)  
            ) AS Total
        FROM TripsDays TD
        LEFT JOIN Accommodations A ON TD.AccommodationID = A.AccommodationID
        LEFT JOIN Attractions AT ON TD.AttractionID = AT.AttractionID
        LEFT JOIN RoutesTransportation R ON TD.RouteID = R.RouteID
        LEFT JOIN Transportation TS ON R.TransportationID = TS.TransportationID  
        WHERE TD.TripID IN (SELECT DISTINCT TripID FROM inserted)
        GROUP BY TD.TripID
    ) AS Total ON T.TripID = Total.TripID;
END;




IF OBJECT_ID('MoveGeneratedTripToTrips', 'P') IS NOT NULL
	DROP PROCEDURE MoveGeneratedTripToTrips;
GO
CREATE PROCEDURE MoveGeneratedTripToTrips
	@GeneratedTripID INT
AS
BEGIN
	SET NOCOUNT ON;
	INSERT INTO Trips (UserID, StartDate, EndDate, Duration, isConfirmed, totalCost)
	SELECT UserID, StartDate, EndDate, Duration, isConfirmed, totalCost
	FROM GeneratedTrips
	WHERE TripID = @GeneratedTripID;

END;
IF OBJECT_ID('MoveGeneratedTripDays', 'P') IS NOT NULL
    DROP PROCEDURE MoveGeneratedTripDays;
GO

CREATE PROCEDURE MoveGeneratedTripDays
    @GeneratedTripID INT
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @UserID INT,
            @StartDate DATETIME,
            @EndDate DATETIME,
            @Duration DECIMAL,
            @IsConfirmed BIT,
            @TotalCost FLOAT,
            @NewTripID INT;
    SELECT 
        @UserID = UserID,
        @StartDate = StartDate,
        @EndDate = EndDate,
        @Duration = Duration,
        @IsConfirmed = isConfirmed,
        @TotalCost = totalCost
    FROM GeneratedTrips
    WHERE TripID = @GeneratedTripID;
    INSERT INTO Trips(UserID, StartDate, EndDate, Duration, isConfirmed, totalCost)
    VALUES (@UserID, @StartDate, @EndDate, @Duration, @IsConfirmed, @TotalCost);

    SET @NewTripID = SCOPE_IDENTITY();
    INSERT INTO TripsDays(TripID, DayNumber, AccommodationID, AttractionID, RouteID)
    SELECT 
        @NewTripID,
        DayNumber,
        AccommodationID,
        AttractionID,
        RouteID
    FROM GeneratedTripsDays
    WHERE TripID = @GeneratedTripID;
END;

INSERT INTO GeneratedTrips(UserID,StartDate,EndDate, Duration, isConfirmed, totalCost) VALUES
(12, '2025-02-03', '2025-02-05', 3, 0, 0)

SELECT *
FROM GeneratedTrips

SELECT *
frOM GeneratedTripsDays

SELECT *
FROM Trips

SELECT *
from TripsDays

EXEC MoveGeneratedTripDays 1


IF OBJECT_ID('ConfirmTrip', 'P') IS NOT NULL
    DROP PROCEDURE ConfirmTrip;
GO

CREATE PROCEDURE ConfirmTrip
    @TripID INT
AS
BEGIN
    SET NOCOUNT ON;

    UPDATE Trips
    SET isConfirmed = 1
    WHERE TripID = @TripID;
END;



SELECT 
    A.AttractionID, 
    A.Name, 
    A.Description, 
    A.Category, 
    A.TicketPrice, 
    D.DestinationID,
    D.Name AS DestinationName,
    D.Country,
    D.City,
    D.Climate
FROM 
    Attractions A
INNER JOIN 
    Destinations D ON A.DestinationID = D.DestinationID
WHERE D.IsActive = 1

UPDATE Destinations
SET Climate ='Sunny'



SELECT 
    A.AccommodationID, 
    A.Name, 
    A.Type, 
    A.Address, 
    A.Description, 
    A.PricePerNight, 
    A.Facilities, 
    D.DestinationID,
    D.Name AS DestinationName,
    D.Country,
    D.City,
    D.Climate
FROM 
    Accommodations A
INNER JOIN 
    Destinations D ON A.DestinationID = D.DestinationID
WHERE D.IsActive = 1


SELECT *
FROM RoutesTransportation


SELECT *
FROM Destinations

SELECT *
From Attractions

SELECT *
FROM Accommodations


Update Destinations
SET Name = 'Castelul Huniazilor',
Country = 'Romania',
City = 'Hunedoara', 
Climate = 'Sunny',
Description = 'Aceasta este o zona plina de turisti si reprezinta pentru romani o adevarata valoare nationala'
WHERE DestinationID = 2

Update Destinations
SET Name = 'Complex UNTOLD',
Country = 'Romania',
City = 'Cluj-Napoca', 
Climate = 'Sunny',
Description = 'Zona din orasul Cluj-Napoca cu foarte multi turisti. Este populara datorita concertului anual UNTOLD'
WHERE DestinationID = 3


Update Destinations
SET Name = 'Complex UNTOLD',
Country = 'Romania',
City = 'Cluj-Napoca', 
Climate = 'Sunny',
Description = 'Zona din orasul Cluj-Napoca cu foarte multi turisti. Este populara datorita concertului anual UNTOLD'
WHERE DestinationID = 3


UPDATE Destinations
SET Name = 'Putna',
    Country = 'Romania',
    City = 'Putna',
    Climate = 'Sunny',
    Description = 'Zona rurala linistita din nordul Moldovei, aproape de granita cu Ucraina, cunoscuta pentru peisajele naturale si traditiile autentice'
WHERE DestinationID = 1;



INSERT INTO Destinations (name, description)
VALUES
  ('Bucuresti', 'Capitala Romaniei, centru cultural si economic.'),
  ('Brasov', 'Oras medieval inconjurat de Muntii Carpati.'),
  (4, 'Sibiu', 'Oras istoric cu influente sasesti.'),
  (5, 'Constanta', 'Oras port la Marea Neagra.');


INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Sinaia', 'Romania', 'Sinaia', 'Un oras turistic cunoscut pentru Castelul Peles si pentru muntii din jur.', 'Snowing', 1);

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Brasov', 'Romania', 'Brasov', 'Un oras medieval cu un centru istoric pitoresc, inconjurat de muntii Carpati.', 'Snowing', 1);

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Bucuresti', 'Romania', 'Bucuresti', 'Capitala tarii, un mix intre vechi si modern, cu multe locuri istorice si culturale.', 'Sunny', 1);

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Timisoara', 'Romania', 'Timisoara', 'Un oras cu influente europene, cunoscut pentru arhitectura sa si istoria sa ca centru cultural.', 'Sunny', 1);

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Constanta', 'Romania', 'Constanta', 'Un oras de la malul marii, cunoscut pentru plajele sale si pentru istoria antica.', 'Sunny', 1);

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Iasi', 'Romania', 'Iasi', 'Un oras cultural, cu traditie si istorie, cunoscut pentru universitatile sale si cladirile istorice.', 'Sunny', 1);

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Sighisoara', 'Romania', 'Sighisoara', 'Un oras medieval bine conservat, faimos pentru cetatea sa si pentru legendele lui Dracula.', 'Snowing', 1);

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Bistrita', 'Romania', 'Bistrita', 'Un oras mic si linistit, cunoscut pentru traditiile sale si pentru peisajele montane din jur.', 'Snowing', 1);

INSERT INTO Destinations(Name, Country, City, Description, Climate, IsActive) VALUES
('Vama Veche', 'Romania', 'Vama Veche', 'Un loc popular pe litoralul romanesc, cunoscut pentru atmosfera sa relaxata si pentru plajele sale.', 'Sunny', 1);




INSERT INTO Attractions (DestinationID, Name, Description, Category, TicketPrice) VALUES (4, 'Castelul Peles', 'Un castel regal impresionant, simbol al arhitecturii europene din secolul 19.', 'CULTURAL', 40.00);
INSERT INTO Attractions (DestinationID, Name, Description, Category, TicketPrice) VALUES (5, 'Piata Sfatului Brasov', 'Un loc emblematic al orasului Brasov, plin de istorie si cultura.', 'CULTURAL', 10.00);
INSERT INTO Attractions (DestinationID, Name, Description, Category, TicketPrice) VALUES (6, 'Ateneul Roman', 'Un loc simbolic al culturii romanesti, gazduind evenimente muzicale si culturale de amploare.', 'MUSICAL', 50.00);
INSERT INTO Attractions (DestinationID, Name, Description, Category, TicketPrice) VALUES (7, 'Catedrala Mitropolitana Timisoara', 'O catedrala impresionanta, un loc de cult si un simbol al istoriei religioase din vestul Romaniei.', 'RELIGIOUS', 20.00);
INSERT INTO Attractions (DestinationID, Name, Description, Category, TicketPrice) VALUES (8, 'Plaja Mamaia', 'Una dintre cele mai populare destinatii de pe litoralul romanesc, fiind cunoscuta pentru plajele sale si evenimentele culturale.', 'CULTURAL', 30.00);
INSERT INTO Attractions (DestinationID, Name, Description, Category, TicketPrice) VALUES (9, 'Teatrul National Iasi', 'Un loc de cultura ce gazduieste spectacole teatrale si evenimente artistice.', 'MUSICAL', 40.00);
INSERT INTO Attractions (DestinationID, Name, Description, Category, TicketPrice) VALUES (10, 'Cetatea Sighisoara', 'Un loc de o importanta istorica majora, cu o atmosfera medievala autentica.', 'CULTURAL', 25.00);
INSERT INTO Attractions (DestinationID, Name, Description, Category, TicketPrice) VALUES (11, 'Biserica Evanghelica Bistrita', 'Un loc de cult cu o istorie indelungata, reprezentand un simbol al religiozitatii in regiunea Bistrita.', 'RELIGIOUS', 15.00);
INSERT INTO Attractions (DestinationID, Name, Description, Category, TicketPrice) VALUES (12, 'Vama Veche Beach', 'Un loc relaxant si plin de tineret, unde se organizeaza evenimente muzicale si activitati culturale.', 'MUSICAL', 50.00);



INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(1, 'Pensiunea Casa Isabela Putna', 'PENSIUNE', 'Strada Principala 123, Putna', 'Pensiune rustica, intr-o zona linistita, ideala pentru relaxare.', 100.00, 'Wi-Fi, Parcare gratuita, Terasa, Mic dejun inclus');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(2, 'Astoria Hotel & SPA Hunedoara', 'HOTEL', 'Strada Tudor Vladimirescu 45, Hunedoara', 'Hotel de 4 stele cu SPA si servicii premium.', 150.00, 'Wi-Fi, SPA, Piscina, Restaurant, Parcare gratuita');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(3, 'AD Apartments Cluj-Napoca', 'APARTAMENT', 'Strada Napoca 78, Cluj-Napoca', 'Apartament modern situat in centrul orasului, perfect pentru o vacanta urbana.', 120.00, 'Wi-Fi, Bucatarie, Parcare privata');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(4, 'Hotel International Sinaia', 'HOTEL', 'Strada Zamora 12, Sinaia', 'Hotel de 5 stele cu vederi spectaculoase asupra muntilor.', 200.00, 'Wi-Fi, SPA, Restaurant, Parcare privata, Piscina');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(5, 'Pensiunea KronSoul Brasov', 'PENSIUNE', 'Strada Muntele Rosu 19, Brasov', 'Pensiune traditionala, situata la poalele muntelui Tampa.', 90.00, 'Wi-Fi, Mic dejun, Parcare gratuita');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(6, 'Hotel Athenee Bucuresti', 'HOTEL', 'Strada Stirbei Voda 21, Bucuresti', 'Hotel elegant situat in centrul capitalei, cu servicii de 4 stele.', 130.00, 'Wi-Fi, Restaurant, Parcare privata, Centrul de fitness');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(7, 'Pensiunea Casa Timisoara', 'PENSIUNE', 'Strada Vasile Alecsandri 44, Timisoara', 'Pensiune moderna, perfecta pentru familii si cupluri.', 80.00, 'Wi-Fi, Mic dejun, Parcare privata');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(8, 'Hotel Mamaia Constanta', 'HOTEL', 'Strada Dacia 25, Mamaia, Constanta', 'Hotel situat pe malul marii, ideal pentru vacante pe litoral.', 180.00, 'Wi-Fi, Piscina, Restaurant, Parcare gratuita, Plaja privata');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(9, 'Iasi Apartments', 'APARTAMENT', 'Strada Calea Tandarei 19, Iasi', 'Apartament elegant, situat in apropiere de centrul orasului Iasi.', 110.00, 'Wi-Fi, Bucatarie, Parcare gratuita');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(10, 'Pensiunea Drumul Sarii Sighisoara', 'PENSIUNE', 'Strada Sighisoara 40, Sighisoara', 'Pensiune traditionala in centrul istoric al orasului Sighisoara.', 85.00, 'Wi-Fi, Mic dejun, Parcare gratuita');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(11, 'Pensiunea Doru Bistrita', 'PENSIUNE', 'Strada Pietei 12, Bistrita', 'Pensiune de familie cu un decor traditional si camere confortabile.', 75.00, 'Wi-Fi, Mic dejun, Parcare gratuita');
INSERT INTO Accommodations (DestinationID, Name, Type, Address, Description, PricePerNight, Facilities) VALUES
(12, 'Hotel Vega Vama Veche', 'HOTEL', 'Strada Marii 25, Vama Veche', 'Hotel pe plaja, ideal pentru vacante de vara la mare.', 160.00, 'Wi-Fi, Piscina, Restaurant, Parcare privata, Plaja privata');



SELECT *
FROM Accommodations

SELECT *
FROM Attractions

UPDATE Attractions
SET Image='D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\peles.jpg'
WHERE AttractionID = 7


UPDATE Attractions
SET Image='D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\mamaia.jpg'
WHERE AttractionID = 14


SELECT *
FROM  RoutesTransportation

DELETE 
FROM RoutesTransportation

SELECT *
FROM Destinations


UPDATE Accommodations
SET Image='D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\vega-min.jpg'
WHERE AccommodationID = 20

SELECT *
FROM Transportation


INSERT INTO Transportation(Type, Company, Description, PricePerKm, Capacity, ComfortLevel, Image)
VALUES
('BUS', 'Societatea Transporturilor Bucuresti', 'Mijloc de transport in comun ce asigura deplasarea cetatenilor in diverse locatii', 1,50, 'Economic','D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\bus1.png'),
('BUS', 'None', 'Null', 0, 0, 'Economic', 'D:\travel-app\travel-app\3_Solution\Server\travel-app-server\images\none.jpg')



SELECT *
FROM Transportation

INSERT INTO RoutesTransportation(TransportationID, CityDeparture, CityArrival, Distance, Duration) VALUES
(5, 'Anywhere', 'Anywhere', 0,0);


SELECT *
FROM Accommodations

SELECT *
FROM GeneratedTripsDays

SELECT *
FROM GeneratedTrips

SELECT *
FROM TripsDays



SELECT *
FROM Trips

DELETE FROM GeneratedTrips

SELECT *
FROM Users

DELETE 
FROM Trips

EXEC CreateGeneratedTrip 12, '2025-05-22','2025-05-23', 2.000000, 0, 320.000000;
