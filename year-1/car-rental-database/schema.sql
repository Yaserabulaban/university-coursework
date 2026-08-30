-- Drop tables if they exist
DROP TABLE IF EXISTS Payment_Receipt CASCADE;
DROP TABLE IF EXISTS Payment CASCADE;
DROP TABLE IF EXISTS Payment_Report CASCADE;
DROP TABLE IF EXISTS Invoice CASCADE;
DROP TABLE IF EXISTS Customer CASCADE;
DROP TABLE IF EXISTS Vendor CASCADE;
DROP TABLE IF EXISTS Finance_Officer CASCADE;
DROP TABLE IF EXISTS Manager CASCADE;
DROP TABLE IF EXISTS Staff CASCADE;
DROP TABLE IF EXISTS Car_Model CASCADE;
DROP TABLE IF EXISTS Car_Rental_Location CASCADE;

-- Create Car_Rental_Location table 
CREATE TABLE Car_Rental_Location ( 
  Location_ID CHAR(5) NOT NULL PRIMARY KEY, 
  Address VARCHAR(100) NOT NULL 
); 

-- Create Car_Model table
CREATE TABLE Car_Model ( 
License_Plate VARCHAR(15) not null primary key, 
  Location_ID CHAR(5) not null, 
  Model_ID CHAR(5) not null, 
  Model_Name VARCHAR(50), 
  Model_Year CHAR(4), 
  foreign key (Location_ID) references Car_Rental_Location(Location_ID)
  );

-- Create Staff table 
CREATE TABLE Staff ( 
  Staff_ID CHAR(5) NOT NULL PRIMARY KEY, 
  Location_ID CHAR(5) NOT NULL, 
  Staff_Name VARCHAR(50) NOT NULL, 
  Staff_Phone VARCHAR(15) NOT NULL, 
  FOREIGN KEY (Location_ID) REFERENCES Car_Rental_Location(Location_ID) 
); 

-- Create Manager table 

CREATE TABLE Manager ( 
  Manager_ID CHAR(5) NOT NULL PRIMARY KEY, 
  Location_ID CHAR(5) NOT NULL, 
  Manager_Phone VARCHAR(15) NOT NULL, 
  Manager_Name VARCHAR(50) NOT NULL, 
  FOREIGN KEY (Location_ID) REFERENCES Car_Rental_Location(Location_ID) 
); 

-- Create Finance_Officer table
CREATE TABLE Finance_Officer ( 
  Officer_ID CHAR(5) NOT NULL PRIMARY KEY, 
  Location_ID CHAR(5) NOT NULL, 
  Officer_Name VARCHAR(50) NOT NULL, 
  Officer_Phone VARCHAR(15) NOT NULL, 
  FOREIGN KEY (Location_ID) REFERENCES Car_Rental_Location(Location_ID) 
); 

-- Create Vendor table 
CREATE TABLE Vendor ( 
  Vendor_ID CHAR(5) NOT NULL PRIMARY KEY, 
  Officer_ID CHAR(5) NOT NULL, 
  Vendor_Phone VARCHAR(15) NOT NULL, 
  Vendor_Name VARCHAR(50) NOT NULL, 
  Vendor_Address VARCHAR(100) NOT NULL, 
  FOREIGN KEY (Officer_ID) REFERENCES Finance_Officer(Officer_ID) 
); 

-- Create Customer table 
CREATE TABLE Customer ( 
  Customer_ID CHAR(5) NOT NULL PRIMARY KEY, 
  Customer_Name VARCHAR(50) NOT NULL, 
  Staff_ID CHAR(5) NOT NULL, 
  Customer_Phone VARCHAR(15) NOT NULL, 
  FOREIGN KEY (Staff_ID) REFERENCES Staff(Staff_ID) 
); 

-- Create Invoice table 
CREATE TABLE Invoice ( 
  Invoice_ID CHAR(5) NOT NULL PRIMARY KEY, 
  Vendor_ID CHAR(5) NOT NULL, 
  Customer_ID CHAR(5) NOT NULL, 
  Invoice_Date DATE NOT NULL, 
  FOREIGN KEY (Vendor_ID) REFERENCES Vendor(Vendor_ID), 
  FOREIGN KEY (Customer_ID) REFERENCES Customer(Customer_ID) 
); 

-- Create Payment_Report table 
CREATE TABLE Payment_Report ( 
  Report_ID CHAR(5) NOT NULL PRIMARY KEY, 
  Invoice_ID CHAR(5) NOT NULL, 
  Manager_ID CHAR(5) NOT NULL, 
  Report_Date DATE NOT NULL, 
  FOREIGN KEY (Invoice_ID) REFERENCES Invoice(Invoice_ID), 
  FOREIGN KEY (Manager_ID) REFERENCES Manager(Manager_ID) 
); 

-- Create Payment table 
CREATE TABLE Payment ( 
  Payment_ID CHAR(5) NOT NULL PRIMARY KEY, 
  Invoice_ID CHAR(5) NOT NULL, 
  Payment_Amount DECIMAL(13,2) NOT NULL, 
  Payment_Date DATE NOT NULL, 
  Payment_Method VARCHAR(50), 
  FOREIGN KEY (Invoice_ID) REFERENCES Invoice(Invoice_ID) 
); 

-- Create Payment_Receipt table
CREATE TABLE Payment_Receipt ( 
  Receipt_ID CHAR(6) NOT NULL PRIMARY KEY, 
  Payment_ID CHAR(5) NOT NULL, 
  Customer_ID CHAR(5) NOT NULL, 
  Vendor_ID CHAR(5) NOT NULL, 
  Receipt_Date DATE NOT NULL, 
  Receipt_Amount DECIMAL(13,2) NOT NULL, 
  FOREIGN KEY (Payment_ID) REFERENCES Payment(Payment_ID), 
  FOREIGN KEY (Customer_ID) REFERENCES Customer(Customer_ID), 
  FOREIGN KEY (Vendor_ID) REFERENCES Vendor(Vendor_ID) 
); 

-- Insert data into Car_Rental_Location 
INSERT INTO Car_Rental_Location (Location_ID, Address) VALUES 
('00001', '123 Jalan Utama'), 
('00002', '456 Jalan Bunga'), 
('00003', '789 Jalan Ros'), 
('00004', '101 Jalan Mawar'), 
('00005', '202 Jalan Orkid'), 
('00006', '303 Jalan Selangor');

-- Insert data into Car_Model 
INSERT INTO Car_Model (License_Plate, Location_ID, Model_ID, Model_Name, Model_Year) VALUES 
('ABC123', '00001', '10001', 'Perodua Myvi', 2020), 
('DEF456', '00002', '10002', 'Proton Saga', 2019), 
('GHI789', '00003', '10003', 'Honda City', 2018), 
('JKL012', '00004', '10004', 'Toyota Vios', 2021), 
('MNO345', '00005', '10005', 'Nissan Almera', 2022), 
('PQR678', '00006', '10006', 'Hyundai Elantra', 2023), 
('STU901', '00001', '10007', 'BMW 3 Series', 2021), 
('VWX234', '00002', '10008', 'Audi A4', 2020), 
('YZA567', '00003', '10009', 'Mercedes C-Class', 2019), 
('BCD890', '00004', '10010', 'Tesla Model 3', 2022); 

-- Insert data into Staff 
INSERT INTO Staff (Staff_ID, Location_ID, Staff_Name, Staff_Phone) VALUES 
('20001', '00001', 'Khairul Anwar', ''), 
('20002', '00002', 'Basil Aiman', ''), 
('20003', '00003', 'Chen Wei', ''), 
('20004', '00004', 'David Tan', ''), 
('20005', '00005', 'Evelyn Wong', ''), 
('20006', '00006', 'Faizal Rahman', ''); 

-- Insert data into Manager 
INSERT INTO Manager (Manager_ID, Location_ID, Manager_Phone, Manager_Name) VALUES 
('30001', '00001', '', 'Grace Lim'), 
('30002', '00002', '', 'Alex Tan'), 
('30003', '00003', '', 'Ivy Leong'), 
('30004', '00004', '', 'Jack Ng'), 
('30005', '00005', '', 'Karen Tan'), 
('30006', '00006', '', 'Leon Wong'); 

-- Insert data into Finance_Officer 
INSERT INTO Finance_Officer (Officer_ID, Location_ID, Officer_Name, Officer_Phone) VALUES 
('40001', '00001', 'Mia Yap', ''), 
('40002', '00002', 'Noah Lim', ''), 
('40003', '00003', 'Olivia Tan', ''), 
('40004', '00004', 'Paul Chong', ''), 
('40005', '00005', 'Quinn Chew', ''), 
('40006', '00006', 'Ruth Mah', ''); 

-- Insert data into Vendor 
INSERT INTO Vendor (Vendor_ID, Officer_ID, Vendor_Phone, Vendor_Name, Vendor_Address) VALUES 
('50001', '40001', '', 'Auto Supplies Sdn Bhd', '400 Jalan Auto'), 
('50002', '40002', '', 'Car Parts Sdn Bhd', '401 Jalan Auto'), 
('50003', '40003', '', 'Motor Shop Sdn Bhd', '402 Jalan Auto'), 
('50004', '40004', '', 'Vehicle Needs Sdn Bhd', '403 Jalan Auto'), 
('50005', '40005', '', 'Auto Accessories Sdn Bhd', '404 Jalan Auto'), 
('50006', '40006', '', 'Car Services Sdn Bhd', '405 Jalan Auto'), 
('50007', '40001', '', 'Quality Auto Sdn Bhd', '406 Jalan Auto'), 
('50008', '40002', '', 'Prime Auto Parts Sdn Bhd', '407 Jalan Auto'), 
('50009', '40003', '', 'Superior Motors Sdn Bhd', '408 Jalan Auto'), 
('50010', '40004', '', 'Auto World Sdn Bhd', '409 Jalan Auto'); 

-- Insert data into Customer 
INSERT INTO Customer (Customer_ID, Customer_Name, Staff_ID, Customer_Phone) VALUES 
('60001', 'Siti Nurhaliza', '20001', ''), 
('60002', 'Ahmad Ali', '20002', ''), 
('60003', 'Lim Mei', '20003', ''), 
('60004', 'John Lee', '20004', ''), 
('60005', 'Aisyah Rahman', '20005', ''), 
('60006', 'William Tan', '20006', ''), 
('60007', 'Nurul Izzah', '20001', ''), 
('60008', 'Lucas Lim', '20002', ''), 
('60009', 'Isabella Wong', '20003', ''), 
('60010', 'Mason Chong', '20004', ''); 

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
('90001', '70001', 420.00, '2023-01-03', 'Credit Card'), 
('90002', '70002', 850.00, '2023-02-03', 'Cash'), 
('90003', '70003', 1250.00, '2023-03-03', 'Debit Card'), 
('90004', '70004', 1600.00, '2023-04-03', 'Bank Transfer'), 
('90005', '70005', 2100.00, '2023-05-03', 'PayPal'), 
('90006', '70006', 2700.00, '2023-06-03', 'Credit Card'); 

-- Insert data into Payment_Receipt 
INSERT INTO Payment_Receipt (Receipt_ID, Payment_ID, Customer_ID, Vendor_ID, Receipt_Date, Receipt_Amount) VALUES 
('100001', '90001', '60001', '50001', '2023-01-04', 420.00), 
('100002', '90002', '60002', '50002', '2023-02-04', 850.00), 
('100003', '90003', '60003', '50003', '2023-03-04', 1250.00), 
('100004', '90004', '60004', '50004', '2023-04-04', 1600.00), 
('100005', '90005', '60005', '50005', '2023-05-04', 2100.00), 
('100006', '90006', '60006', '50006', '2023-06-04', 2700.00); 

SELECT *
FROM Vendor
WHERE Vendor_ID IN (
    SELECT DISTINCT Vendor_ID
    FROM Invoice
);


-- Aggregrate 
SELECT Location_ID, COUNT(License_Plate) AS Total_Cars 
FROM Car_Model 
GROUP BY Location_ID; 
SELECT AVG(Invoice_Amount) AS Avg_Invoice_Amount 
FROM Invoice i 
JOIN (SELECT i.VENDOR_ID ,sum(payment_amount) AS Invoice_Amount  
FROM Payment p 
JOIN Invoice i  
on i.invoice_id = p.invoice_id  
GROUP BY i.vendor_id) y  
ON i.vendor_id = y.vendor_id; 

 

-- View 
CREATE VIEW Customer_Payment_View AS 
SELECT c.Customer_ID, c.Customer_Name, p.Payment_ID, p.Payment_Amount, p.Payment_Date 
FROM Customer c 
JOIN Invoice i ON c.Customer_ID = i.Customer_ID 
JOIN payment p ON p.invoice_id = i.invoice_id; 
SELECT * from Customer_Payment_View; 
DROP VIEW Customer_Payment_View; 

 
-- Subquery 
SELECT v.Vendor_Name, MAX(y.Invoice_Amount) AS Max_Invoice_Amount 
FROM ( 
SELECT i.Vendor_ID, MAX(x.Invoice_Amount) AS Invoice_Amount 
FROM Invoice i 
JOIN (SELECT i.VENDOR_ID ,sum(payment_amount) AS Invoice_Amount  
FROM Payment p 
JOIN Invoice i  
on i.invoice_id = p.invoice_id  
GROUP BY i.vendor_id) x 
ON i.vendor_id = x.vendor_id 
GROUP BY i.vendor_id)y 
JOIN Vendor v  
ON y.Vendor_ID = v.Vendor_ID 
GROUP BY v.Vendor_Name; 

 
-- Group by/Having 
SELECT TO_CHAR(p.Payment_Date, 'Month') AS Payment_Month, p.Payment_Method, COUNT(*) AS Payment_Count 
FROM Payment p 
GROUP BY TO_CHAR(p.Payment_Date, 'Month'), p.Payment_Method 
HAVING TO_CHAR(p.Payment_Date, 'Month') = 'April' 
ORDER BY Payment_Month, Payment_Method;

 
-- Triggers 
CREATE OR REPLACE FUNCTION update_payment_method()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.Payment_Method IS NULL THEN
        NEW.Payment_Method := 'Debit Card';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE TRIGGER payment_method_update
BEFORE INSERT ON Payment
FOR EACH ROW
EXECUTE FUNCTION update_payment_method();


-- Stored Prodcedure 
CREATE OR REPLACE PROCEDURE InsertCustomerInfo(
    IN p_customer_id CHAR(5),
    IN p_customer_name VARCHAR(50),
    IN p_staff_id CHAR(5),
    IN p_customer_phone VARCHAR(15)
)
LANGUAGE plpgsql
AS $$
BEGIN
    INSERT INTO Customer (Customer_ID, Customer_Name, Staff_ID, Customer_Phone)
    VALUES (p_customer_id, p_customer_name, p_staff_id, p_customer_phone);
END;
$$;


-- Queries not covered 
SELECT c.Customer_ID,c.Customer_Name,p.Payment_ID,p.Payment_Date,p.Payment_Amount, SUM(p.Payment_Amount)  
OVER (PARTITION BY c.Customer_ID ORDER BY p.Payment_Date) AS Cumulative_Payment 
FROM Customer c 
JOIN Invoice i ON c.Customer_ID = i.Customer_ID 
JOIN Payment p ON i.Invoice_ID = p.Invoice_ID 
ORDER BY c.Customer_ID, p.Payment_Date; 
