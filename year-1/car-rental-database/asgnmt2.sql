-- Drop Trigger if it exists
--DROP TRIGGER IF EXISTS UpdatePaymentReceipt ON Payment;

-- Drop view if it exists
--DROP VIEW IF EXISTS CustomerPayments CASCADE;

-- Drop tables if they exist
--DROP TABLE IF EXISTS Payment_Receipt CASCADE;
--DROP TABLE IF EXISTS Payment CASCADE;
--DROP TABLE IF EXISTS Payment_Report CASCADE;
--DROP TABLE IF EXISTS Invoice CASCADE;
--DROP TABLE IF EXISTS Customer CASCADE;
--DROP TABLE IF EXISTS Vendor CASCADE;
--DROP TABLE IF EXISTS Finance_Officer CASCADE;
--DROP TABLE IF EXISTS Manager CASCADE;
--DROP TABLE IF EXISTS Staff CASCADE;
--DROP TABLE IF EXISTS Car_Model CASCADE;
--DROP TABLE IF EXISTS Car_Rental_Location CASCADE;

-- Create Car_Rental_Location table 
CREATE TABLE Car_Rental_Location ( 
  Location_ID VARCHAR(10) PRIMARY KEY, 
  Address VARCHAR(100) NOT NULL 
); 

-- Create Car_Model table 
CREATE TABLE Car_Model ( 
  License_Plate VARCHAR(15) PRIMARY KEY, 
  Location_ID VARCHAR(10) NOT NULL, 
  Model_ID VARCHAR(10) NOT NULL, 
  Model_Name VARCHAR(50), 
  Model_Year INT, 
  FOREIGN KEY (Location_ID) REFERENCES Car_Rental_Location(Location_ID) 
); 

-- Create Staff table 
CREATE TABLE Staff ( 
  Staff_ID VARCHAR(10) PRIMARY KEY, 
  Location_ID VARCHAR(10) NOT NULL, 
  Staff_Name VARCHAR(50) NOT NULL, 
  Staff_Phone VARCHAR(15) NOT NULL, 
  FOREIGN KEY (Location_ID) REFERENCES Car_Rental_Location(Location_ID) 
); 

-- Create Manager table 
CREATE TABLE Manager ( 
  Manager_ID VARCHAR(10) PRIMARY KEY, 
  Location_ID VARCHAR(10) NOT NULL, 
  Manager_Phone VARCHAR(15) NOT NULL, 
  Manager_Name VARCHAR(50) NOT NULL, 
  FOREIGN KEY (Location_ID) REFERENCES Car_Rental_Location(Location_ID) 
); 

-- Create Finance_Officer table 
CREATE TABLE Finance_Officer ( 
  Officer_ID VARCHAR(10) PRIMARY KEY, 
  Location_ID VARCHAR(10) NOT NULL, 
  Officer_Name VARCHAR(50) NOT NULL, 
  Officer_Phone VARCHAR(15) NOT NULL, 
  FOREIGN KEY (Location_ID) REFERENCES Car_Rental_Location(Location_ID) 
); 

-- Create Vendor table 
CREATE TABLE Vendor ( 
  Vendor_ID VARCHAR(10) PRIMARY KEY, 
  Officer_ID VARCHAR(10) NOT NULL, 
  Vendor_Phone VARCHAR(15) NOT NULL, 
  Vendor_Name VARCHAR(50) NOT NULL, 
  Vendor_Address VARCHAR(100) NOT NULL, 
  FOREIGN KEY (Officer_ID) REFERENCES Finance_Officer(Officer_ID) 
); 

-- Create Customer table 
CREATE TABLE Customer ( 
  Customer_ID VARCHAR(10) PRIMARY KEY, 
  Customer_Name VARCHAR(50) NOT NULL, 
  Staff_ID VARCHAR(10) NOT NULL, 
  Customer_Phone VARCHAR(15) NOT NULL, 
  FOREIGN KEY (Staff_ID) REFERENCES Staff(Staff_ID) 
); 

-- Create Invoice table 
CREATE TABLE Invoice ( 
  Invoice_ID VARCHAR(10) PRIMARY KEY, 
  Vendor_ID VARCHAR(10) NOT NULL, 
  Customer_ID VARCHAR(10) NOT NULL, 
  Invoice_Date DATE NOT NULL, 
  FOREIGN KEY (Vendor_ID) REFERENCES Vendor(Vendor_ID), 
  FOREIGN KEY (Customer_ID) REFERENCES Customer(Customer_ID) 
); 

-- Create Payment_Report table 
CREATE TABLE Payment_Report ( 
  Report_ID VARCHAR(10) PRIMARY KEY, 
  Invoice_ID VARCHAR(10) NOT NULL, 
  Manager_ID VARCHAR(10) NOT NULL, 
  Report_Date DATE NOT NULL, 
  FOREIGN KEY (Invoice_ID) REFERENCES Invoice(Invoice_ID), 
  FOREIGN KEY (Manager_ID) REFERENCES Manager(Manager_ID) 
); 

-- Create Payment table 
CREATE TABLE Payment ( 
  Payment_ID VARCHAR(10) PRIMARY KEY, 
  Invoice_ID VARCHAR(10) NOT NULL, 
  Payment_Amount DECIMAL(13,2) NOT NULL, 
  Payment_Date DATE NOT NULL, 
  Payment_Method VARCHAR(50), 
  FOREIGN KEY (Invoice_ID) REFERENCES Invoice(Invoice_ID) 
); 

-- Create Payment_Receipt table 
CREATE TABLE Payment_Receipt ( 
  Receipt_ID VARCHAR(10) PRIMARY KEY, 
  Payment_ID VARCHAR(10) NOT NULL, 
  Customer_ID VARCHAR(10) NOT NULL, 
  Vendor_ID VARCHAR(10) NOT NULL, 
  Receipt_Date DATE NOT NULL, 
  Receipt_Amount DECIMAL(13,2) NOT NULL, 
  FOREIGN KEY (Payment_ID) REFERENCES Payment(Payment_ID), 
  FOREIGN KEY (Customer_ID) REFERENCES Customer(Customer_ID), 
  FOREIGN KEY (Vendor_ID) REFERENCES Vendor(Vendor_ID) 
);

-- Insert data into Car_Rental_Location 
INSERT INTO Car_Rental_Location (Location_ID, Address) VALUES 
('00001', '123 Main St'), 
('00002', '456 Elm St'), 
('00003', '789 Oak St'), 
('00004', '101 Pine St'), 
('00005', '202 Maple St'), 
('00006', '303 Cedar St'); 

-- Insert data into Car_Model 
INSERT INTO Car_Model (License_Plate, Location_ID, Model_ID, Model_Name, Model_Year) VALUES 
('ABC123', '00001', '10001', 'Toyota Camry', 2020), 
('DEF456', '00002', '10002', 'Honda Accord', 2019), 
('GHI789', '00003', '10003', 'Ford Focus', 2018), 
('JKL012', '00004', '10004', 'Chevrolet Malibu', 2021), 
('MNO345', '00005', '10005', 'Nissan Altima', 2022), 
('PQR678', '00006', '10006', 'Hyundai Sonata', 2023), 
('STU901', '00001', '10007', 'BMW 3 Series', 2021), 
('VWX234', '00002', '10008', 'Audi A4', 2020), 
('YZA567', '00003', '10009', 'Mercedes C-Class', 2019), 
('BCD890', '00004', '10010', 'Tesla Model 3', 2022); 

-- Insert data into Staff 
INSERT INTO Staff (Staff_ID, Location_ID, Staff_Name, Staff_Phone) VALUES 
('20001', '00001', 'Alice Johnson', '555-1234'), 
('20002', '00002', 'Bob Smith', '555-5678'), 
('20003', '00003', 'Carol Davis', '555-9101'), 
('20004', '00004', 'David Brown', '555-1123'), 
('20005', '00005', 'Eve Wilson', '555-1314'), 
('20006', '00006', 'Frank Clark', '555-1516'); 

-- Insert data into Manager 
INSERT INTO Manager (Manager_ID, Location_ID, Manager_Phone, Manager_Name) VALUES 
('30001', '00001', '555-2121', 'Grace Lee'), 
('30002', '00002', '555-2323', 'Henry Kim'), 
('30003', '00003', '555-2525', 'Ivy Martinez'), 
('30004', '00004', '555-2727', 'Jack Miller'), 
('30005', '00005', '555-2929', 'Karen Anderson'), 
('30006', '00006', '555-3131', 'Leo Thomas'); 

-- Insert data into Finance_Officer 
INSERT INTO Finance_Officer (Officer_ID, Location_ID, Officer_Name, Officer_Phone) VALUES 
('40001', '00001', 'Mia Taylor', '555-4141'), 
('40002', '00002', 'Noah Moore', '555-4343'), 
('40003', '00003', 'Olivia Jackson', '555-4545'), 
('40004', '00004', 'Paul Harris', '555-4747'), 
('40005', '00005', 'Quinn White', '555-4949'), 
('40006', '00006', 'Ruth King', '555-5151'); 

-- Insert data into Vendor 
INSERT INTO Vendor (Vendor_ID, Officer_ID, Vendor_Phone, Vendor_Name, Vendor_Address) VALUES 
('50001', '40001', '555-6161', 'Auto Supplies Inc.', '400 Auto St'), 
('50002', '40002', '555-1234', 'Car Parts Co.', '401 Auto St'), 
('50003', '40003', '555-5678', 'Motor Shop', '402 Auto St'), 
('50004', '40004', '555-9876', 'Vehicle Needs', '403 Auto St'), 
('50005', '40005', '555-4321', 'Auto Accessories', '404 Auto St'), 
('50006', '40006', '555-8765', 'Car Services', '405 Auto St'), 
('50007', '40001', '555-2468', 'Quality Auto', '406 Auto St'), 
('50008', '40002', '555-1357', 'Prime Auto Parts', '407 Auto St'), 
('50009', '40003', '555-3690', 'Superior Motors', '408 Auto St'), 
('50010', '40004', '555-7890', 'Auto World', '409 Auto St'); 

-- Insert data into Customer 
INSERT INTO Customer (Customer_ID, Customer_Name, Staff_ID, Customer_Phone) VALUES 
('60001', 'Sophia Hall', '20001', '555-7171'), 
('60002', 'James Allen', '20002', '555-7272'), 
('60003', 'Emily Young', '20003', '555-7373'), 
('60004', 'Michael Scott', '20004', '555-7474'), 
('60005', 'Ava Green', '20005', '555-7575'), 
('60006', 'William Lewis', '20006', '555-7676'), 
('60007', 'Olivia Brown', '20001', '555-7777'), 
('60008', 'Lucas White', '20002', '555-7878'), 
('60009', 'Isabella Harris', '20003', '555-7979'), 
('60010', 'Mason Clark', '20004', '555-8080'); 

-- Insert data into Invoice 
INSERT INTO Invoice (Invoice_ID, Vendor_ID, Customer_ID, Invoice_Date) VALUES 
('70001', '50001', '60001', '2023-01-01'), 
('70002', '50002', '60002', '2023-02-01'), 
('70003', '50003', '60003', '2023-03-01'), 
('70004', '50004', '60004', '2023-04-01'), 
('70005', '50005', '60005', '2023-05-01'), 
('70006', '50006', '60006', '2023-06-01'); 

-- Insert data into Payment_Report 
INSERT INTO Payment_Report (Report_ID, Invoice_ID, Manager_ID, Report_Date) VALUES 
('80001', '70001', '30001', '2023-01-02'), 
('80002', '70002', '30002', '2023-02-02'), 
('80003', '70003', '30003', '2023-03-02'), 
('80004', '70004', '30004', '2023-04-02'), 
('80005', '70005', '30005', '2023-05-02'), 
('80006', '70006', '30006', '2023-06-02'); 

-- Insert data into Payment 
INSERT INTO Payment (Payment_ID, Invoice_ID, Payment_Amount, Payment_Date, Payment_Method) VALUES 
('90001', '70001', 100.00, '2023-01-03', 'Credit Card'), 
('90002', '70002', 200.00, '2023-02-03', 'Cash'), 
('90003', '70003', 300.00, '2023-03-03', 'Debit Card'), 
('90004', '70004', 400.00, '2023-04-03', 'Bank Transfer'), 
('90005', '70005', 500.00, '2023-05-03', 'PayPal'), 
('90006', '70006', 600.00, '2023-06-03', 'Credit Card'); 

-- Insert data into Payment_Receipt 
INSERT INTO Payment_Receipt (Receipt_ID, Payment_ID, Customer_ID, Vendor_ID, Receipt_Date, Receipt_Amount) VALUES 
('100001', '90001', '60001', '50001', '2023-01-04', 100.00), 
('100002', '90002', '60002', '50002', '2023-02-04', 200.00), 
('100003', '90003', '60003', '50003', '2023-03-04', 300.00), 
('100004', '90004', '60004', '50004', '2023-04-04', 400.00), 
('100005', '90005', '60005', '50005', '2023-05-04', 500.00), 
('100006', '90006', '60006', '50006', '2023-06-04', 600.00); 

-- Two Queries with Aggregate Functions
-- Query 1
SELECT Customer_ID, SUM(Payment_Amount) AS Total_Payments
FROM Payment
GROUP BY Customer_ID;

-- Query 2
SELECT Invoice_ID, AVG(Payment_Amount) AS Average_Payment
FROM Payment
GROUP BY Invoice_ID;

-- View: Customer Payments
CREATE VIEW CustomerPayments AS
SELECT c.Customer_ID, c.Customer_Name, p.Payment_ID, p.Payment_Amount, p.Payment_Date
FROM Customer c
JOIN Payment_Receipt pr ON c.Customer_ID = pr.Customer_ID
JOIN Payment p ON pr.Payment_ID = p.Payment_ID;

-- One Subquery/Nested Query
SELECT Customer_ID, Customer_Name
FROM Customer
WHERE Customer_ID IN (
    SELECT Customer_ID
    FROM Payment
    GROUP BY Customer_ID
    HAVING SUM(Payment_Amount) > (
        SELECT AVG(SUM_Payments)
        FROM (
            SELECT SUM(Payment_Amount) AS SUM_Payments
            FROM Payment
            GROUP BY Customer_ID
        ) AS SubQuery
    )
);

-- One Query with GROUP BY and HAVING Clauses
SELECT Vendor_ID, SUM(Payment_Amount) AS Total_Payments
FROM Payment
GROUP BY Vendor_ID
HAVING SUM(Payment_Amount) > 1000;

-- Triggers
CREATE OR REPLACE FUNCTION update_payment_receipt() 
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO Payment_Receipt (Receipt_ID, Payment_ID, Customer_ID, Vendor_ID, Receipt_Date, Receipt_Amount)
    VALUES (
        'R' || NEW.Payment_ID,  -- Assuming Receipt_ID follows a specific format
        NEW.Payment_ID,
        (SELECT Customer_ID FROM Invoice WHERE Invoice_ID = NEW.Invoice_ID),
        (SELECT Vendor_ID FROM Invoice WHERE Invoice_ID = NEW.Invoice_ID),
        NEW.Payment_Date,
        NEW.Payment_Amount
    );
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER UpdatePaymentReceipt
AFTER INSERT ON Payment
FOR EACH ROW
EXECUTE FUNCTION update_payment_receipt();

-- Stored Procedure
CREATE OR REPLACE PROCEDURE InsertPayment (
    p_Invoice_ID VARCHAR(10),
    p_Payment_Amount DECIMAL(13,2),
    p_Payment_Date DATE,
    p_Payment_Method VARCHAR(50)
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_Payment_ID VARCHAR(10);
BEGIN
    -- Insert payment
    INSERT INTO Payment (Payment_ID, Invoice_ID, Payment_Amount, Payment_Date, Payment_Method)
    VALUES (substring(md5(random()::text) from 1 for 10), p_Invoice_ID, p_Payment_Amount, p_Payment_Date, p_Payment_Method)
    RETURNING Payment_ID INTO v_Payment_ID;

    -- Insert payment receipt
    INSERT INTO Payment_Receipt (Receipt_ID, Payment_ID, Customer_ID, Vendor_ID, Receipt_Date, Receipt_Amount)
    VALUES (
        'R' || v_Payment_ID,
        v_Payment_ID,
        (SELECT Customer_ID FROM Invoice WHERE Invoice_ID = p_Invoice_ID),
        (SELECT Vendor_ID FROM Invoice WHERE Invoice_ID = p_Invoice_ID),
        p_Payment_Date,
        p_Payment_Amount
    );
END;
$$;

-- Four Additional Queries
-- Query 1: Display Top 3 Customers by Total Payment
SELECT Customer_ID, SUM(Payment_Amount) AS Total_Payments
FROM Payment
GROUP BY Customer_ID
ORDER BY Total_Payments DESC
LIMIT 3;

-- Query 2: Auto Increment by 1 for Each New Row Inserted
-- Assume we have a sequence for generating IDs
CREATE SEQUENCE PaymentSeq START 1 INCREMENT 1;

-- Use the sequence in insert statement
INSERT INTO Payment (Payment_ID, Invoice_ID, Payment_Amount, Payment_Date, Payment_Method)
VALUES (nextval('PaymentSeq'), '70001', 100.00, '2023-01-03', 'Credit Card');

-- Query 3: Customers with More Than One Payment
SELECT Customer_ID, COUNT(Payment_ID) AS Payment_Count
FROM Payment
GROUP BY Customer_ID
HAVING COUNT(Payment_ID) > 1;

-- Query 4: Vendor Invoices in the Last Month
SELECT Vendor_ID, COUNT(Invoice_ID) AS Invoice_Count
FROM Invoice
WHERE Invoice_Date >= CURRENT_DATE - INTERVAL '1 month'
GROUP BY Vendor_ID;
