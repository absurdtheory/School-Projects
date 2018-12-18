-- dog queries

-- get all dog columns  and name of adopter and food to populate Manage Dogs page and Browse Dogs page

SELECT d.id, name, birthdate, breed, sex, adoptedBy, foodType, image, a.fname, a.lname, f.bname, f.pname FROM Dogs d INNER JOIN Adopters a ON d.adoptedBy = a.id INNER JOIN FoodSupply f ON d.foodType = f.id ORDER BY d.id;

-- get dog id and name to populate dropdown on Works page

SELECT id, name FROM Dogs;

-- get all dog columns for Browse dog page base on search critera

SELECT id, name, birthdate, breed, sex, adoptedBy, foodType, image FROM Dogs WHERE name = :nameInput, birthdate = :birthdateInput, breed = :breedInput, sex = :sexInput, adoptedBy = :adoptedByInputFromDropDown, foodType = :foodTypeInputFromDropDown;

-- add a new dog

INSERT INTO Dogs (name, birthdate, breed, sex, foodType, image) VALUES (:nameInput, :birthdateInput, :breedInput, :sexInput, :foodTypeInputFromDropDown, :imageInput);

-- delete a dog

DELETE FROM Dogs WHERE id = :idSelectedFromManageDogsPage;

-- autopopulate edit dog Page

SELECT name, birthdate, breed, sex, adoptedby, foodtype, image FROM Dogs WHERE id= :idFromEditButton;

-- edit a dog

UPDATE Dogs SET name = :nameInput, birthdate = :birthdateInput, breed = :breedInput, sex = :sexInput, adoptedBy = :adoptedByIDFromDropDown, foodType = :foodTypeIDFromDropDown, image = :imageInput WHERE id = :idFromDogUpdateButton;

-- adopter queries

-- get all adopter columns to populate Adopters page, use count to dynamically populate number of dogs adopted for one-to-many relationship

SELECT Adopters.id, fname, lname, saddress, city, state, zip, phone, COUNT(d.id) as nad FROM Adopters LEFT JOIN Dogs d ON Adopters.id = d.adoptedBy GROUP BY Adopters.id;

-- get adopter id, fname, and lname columns in Adopters to populate a dropdown for searching by adopter on Browse Dogs page and edit dog page

SELECT id, fname, lname FROM Adopters;

-- add a new adopter

INSERT INTO Adopters (fname, lname, saddress, city, state, zip, phone) VALUES (:fnameInput, :lnameInput, :saddressInput, :cityInput, :stateInput, :zipInput, :phoneInput);

-- delete an adopter

DELETE FROM Adopters WHERE id = :idSelectedfromAdoptersPage;

-- autopopulate adopter edit page

SELECT fname, lname, saddress, city, state, zip, phone FROM Adopters WHERE id = :idFromEditButton;

-- edit an adopter

UPDATE Adopters SET fname = :fnameInput, lname = :lnameInput, saddress = :saddressInput, city = :cityInput, state = :stateInput, zip = :zipInput, phone = :phoneInput WHERE id = idFromAdopterEditButton;

-- Employee queries

-- get all Employee columns to populate Employee page

SELECT id, fname, lname, fsa, phone, title, IF(fsa = 1, 'Yes', 'No') as auth FROM Employees;


-- get employeeID, fname, lname columns of only employes able to order food to populate dropdown on Food Orders page

SELECT id, fname, lname FROM Employees WHERE fsa = TRUE;

-- get employeeID, fname, lname clumns of employess to populate dropdown on Works page

SELECT id, fname, lname FROM Employees;

-- add a new Employee

INSERT INTO Employees (fname, lname, fsa, phone, title) VALUES (:fnameInput, :lnameInput, :fsaInput, :phoneInput, :titleInput);

-- delete an employee

DELETE FROM Employees WHERE id = :idSelectedFromEmployeePage;

-- autopopulate edit employee page;

SELECT id, fname, lname, fsa, phone, title, IF(fsa = 1, 'Yes', 'No') as auth FROM Employees WHERE id=:idFromEditButton;

-- Edit an employee

UPDATE Employees SET fname = :fnameInput, lname = :lnameInput, fsa = :fsaInput, phone = :phoneInput, title = :titleInput WHERE id = :idFromEmployeeEditButton;

-- Food Supply Queries

-- get all columns from FoodSupply to populate Food Supply Page, use count to dynamically calculated the number of dogs on a food type

SELECT f.id, bname, pname, COUNT(d.id) AS numberd, amount FROM FoodSupply f LEFT JOIN Dogs d ON f.id = d.foodType GROUP BY f.id

-- get id, bname, and lname from FoodSupply to populate dropdowns on Order Food Page and Manage Dog page

SELECT id, bname, pname FROM FoodSupply;

-- add a new Food Supply

INSERT INTO FoodSupply (bname, pname) VALUES (:bnameInput, :pnameInput);

-- delete a food supply

DELETE FROM FoodSupply WHERE id = :idSelectedFromFoodSupplyPage;

-- autopopulate food supply edit page

SELECT bname, pname, quantity FROM FoodSupply WHERE id = :idFromEditButton;

-- edit food supply

UPDATE FoodSupply SET bname = :bnameInput, pname = :pnameInput, quantity = :amountInput WHERE id = :idFromFoodSupplyEditButton; 

-- food order queries

-- add a new Food order

INSERT INTO Orders (FoodSupplyID, EmployeeID, quantity) VALUES (:foodInputFromDropDown, :idInput, :quantityInput);

-- delete from food order (M-to-N relationship)

DELETE FROM Orders WHERE EmployeeID = :pidSelectedFromOrdersPage and FoodSupplyID = :fidSelectedFromOrdersPage;

-- get employee id, fname, lname, and foodsupply bname, pname, and orders quantity and date ordered to display on Food Orders page
SELECT Employees.id as eid, fname, lname, FoodSupply.id as fid, bname, pname, Orders.quantity, DATE_FORMAT(dateOrdered, '%Y-%m-%d %H:%i:%s') AS newDate FROM Employees INNER JOIN Orders ON Employees.id = Orders.EmployeeID INNER JOIN FoodSupply ON FoodSupply.id = Orders.FoodSupplyID ORDER BY Orders.dateOrdered;

-- Work Queries

-- add a new work relationship

INSERT IGNORE INTO Works (EmployeeID, DogID) VALUES (:pidInput, :didInput);

-- delete from works (M-to-N relationship)

DELETE FROM Works WHERE EmployeeID = :pidSelectedFromWorksPage and DogID = :didSelectedFromWorksPage;

-- get employee id, fname, lname and dog id, name to display on Works Page
SELECT Employees.id, fname, lname, title, Dogs.id, name FROM Employees INNER JOIN Works ON Employees.id = Works.EmployeeID INNER JOIN Dogs ON Dogs.id = Works.DogID;
