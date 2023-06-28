
CREATE TABLE IF NOT EXISTS
users(
	userID INT PRIMARY KEY,
	firstName VARCHAR(40),
	lastName VARCHAR(40),
	gender VARCHAR(1),
	username VARCHAR(40),
	password VARCHAR(40),
	age INT,
	favouriteGenre VARCHAR(40)
);

SELECT * FROM users;