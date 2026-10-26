# Hospital Management System - Interview Q&A
*Short, easy-to-remember answers for technical interviews.*

## 1. Architecture & Design

**Q: How does your app work from start to finish?**
**A:** The user types in the terminal. The C++ logic processes the input and sends an SQL string to my `Database` wrapper class. The class then saves it permanently into a local SQLite `.db` file.

**Q: Why SQLite instead of MySQL?**
**A:** SQLite is lightweight, serverless, and runs locally. It was the perfect, fast choice for a standalone desktop application.

**Q: How would you scale this for 50 hospitals?**
**A:** I would move the database from a local SQLite file to a cloud database (like MySQL on AWS). I would also build an API backend so multiple computers could access the database over the internet.

---

## 2. Object-Oriented Programming (OOP)

**Q: How did you use Inheritance in this project?**
**A:** I created a base `Person` class for shared details (like name and contact). Then, `Patient` and `Doctor` classes inherit from it, adding their own specific details (like ailment or specialization).

**Q: Why use a Database Wrapper class instead of writing SQL directly in `main.cpp`?**
**A:** It hides the messy database code from the main app (Abstraction/Encapsulation). If I ever switch to a different database later, I only have to update one file, not the entire project.

**Q: What is RAII and how did you use it?**
**A:** "Resource Acquisition Is Initialization." My `Database` constructor automatically opens the database connection when created, and the destructor automatically closes it when the program stops. This completely prevents memory and file leaks.

---

## 3. Database & SQL

**Q: C++ doesn't understand SQL tables. How does it read the data?**
**A:** I used a built-in SQLite "callback function." It reads the database row-by-row and translates the data into a standard C++ list (`std::vector` of Maps) that my program can easily print.

**Q: How did you link Patients and Doctors in appointments?**
**A:** I used an SQL `JOIN` query. The `Appointments` table only stores the `patient_id` and `doctor_id`. When viewing appointments, I join them with the `Patients` and `Doctors` tables to display their actual names on the screen.

---

## 4. Security & Debugging

**Q: Tell me about a difficult bug you fixed.**
**A:** When building the login system, users hitting 'Enter' accidentally added a hidden carriage return (`\r`) to their password string, which broke the SQL query. I fixed it by writing C++ code to trim any invisible characters from the string before checking the database.

**Q: Is your system vulnerable to SQL Injection?**
**A:** Currently, yes, because I combine strings to build SQL queries. To fix it for a production environment, I would upgrade the code to use SQL "Prepared Statements" which safely separate user input from the SQL command.
