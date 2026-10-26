# Easy Guide: Hospital System Architecture

**Elevator Pitch (Architecture, Database & Relationships):**
My project uses a 3-layer architecture: a terminal interface (`main.cpp`), an OOP logic manager (`HospitalSystem.cpp`), and a secure database translator (`Database.cpp`). It saves data into an SQLite database with four tables: Users, Patients, Doctors, and Appointments. Every patient and doctor is assigned a unique **Primary Key**. Because a doctor sees many patients and a patient sees many doctors, they share a **Many-to-Many** relationship. To handle this efficiently without duplicating data, the Appointments table acts as a bridge, storing just the patient and doctor IDs as **Foreign Keys**. When I need to display a full schedule, the system uses SQL **JOIN** commands to stitch the tables back together, ensuring the database remains fast, clean, and relational.

This guide breaks down the complex parts of your project into very simple concepts and analogies so you can easily understand and explain them in your interviews.

---

## 1. How the Code is Organized (The Architecture)
Think of your code like a restaurant:
1. **The Menu (`main.cpp`):** This is what the user sees on their black-and-white terminal. It takes their order (like adding a patient or typing a password).
2. **The Manager (`HospitalSystem.cpp`):** This is the brain. It takes the user's order and applies the rules. It uses OOP (Inheritance) to organize Patients and Doctors neatly.
3. **The Kitchen Staff (`Database.cpp`):** C++ doesn't know how to talk to a database. This file acts as a **translator**. It takes commands from the Manager and turns them into SQL so the database can understand them.

---

## 2. How the Data is Saved (Database & IDs)
Your database has 4 simple tables (like Excel spreadsheets):
* **Users** (for login)
* **Patients**
* **Doctors**
* **Appointments**

**How these tables connect (SQL Relationships):**
* **Primary Keys:** Every person gets a unique, permanent ID number. For example, John is Patient `id = 1` and Dr. Smith is Doctor `id = 5`.
* **1-to-Many:** A single `Patient` can have many `Appointments`. Similarly, a single `Doctor` can have many `Appointments`. 
* **Many-to-Many:** Because one doctor sees many patients, and one patient can see many doctors, `Patients` and `Doctors` have a **Many-to-Many** relationship.
* **The Bridge (Foreign Keys):** To link them together, the `Appointments` table acts as a "bridge". Instead of storing the doctor's full name and patient's full name over and over for every single appointment, it just stores their IDs (e.g., `patient_id = 1`, `doctor_id = 5`). These are called **Foreign Keys**.
* **JOIN Commands:** When you want to show an appointment on the screen, your code uses a `JOIN` command. It takes the `patient_id` from the Appointments table, goes to the Patients table to find out the name is "John", and combines them. This is how relational databases prevent you from saving duplicate data!

**How do IDs work?** 
You don't have to manually figure out what ID to give a new patient. We used a feature called **`AUTOINCREMENT`**. This means the database just counts up automatically. The first patient is ID 1, the next is ID 2, and so on. Even if you delete Patient 2, the next one will still be ID 3.

---

## 3. Database Sessions & Connection Pooling
**What we are doing now (RAII):** 
Opening a database takes time. Instead of opening and closing it every time you add a single patient, our `Database` class opens the connection *once* when the program starts, and strictly closes it when you exit the app. 

**The Interview Answer for "Connection Pooling":**
If an interviewer asks, *"What if 5,000 hospital receptionists use this online?"*, you answer with **Connection Pooling**. 
* **Analogy:** Imagine a bank. Instead of hiring a new teller every time a customer walks in (which is slow), you keep 10 tellers ready in a "pool". When a customer comes, they go to a free teller. When they finish, the teller goes back to the pool, ready for the next person. Connection Pooling does this exact same thing for database connections to make websites incredibly fast.

---

## 4. SQL Injection (Hacking the Login)
**The Problem (Manual Injection):** Right now, we build our SQL queries by gluing strings together (e.g., `"... WHERE username = '" + username + "'"`). This is dangerous. A hacker could type a password like `' OR '1'='1`. Because 1 is always equal to 1, the database gets confused and says "Okay, let them in!" even without a password.

**The Fix:** If an interviewer asks how to fix this, say you would use **Prepared Statements**. This is a secure feature that strictly separates the SQL code from the text the user types, making it impossible to trick the database.

---

## 5. Cool Technical Details to Mention
* **The Invisible "Enter" Bug:** Talk about how hitting the "Enter" key on Windows added an invisible `\r` (carriage return) character to the password. It caused logins to fail because the database saw `"admin\r"` instead of `"admin"`. You fixed it by writing C++ code to trim off invisible spaces.
* **The Callback Function:** Explain that to read data from the database back into C++, you used a C-API "Callback Function". This is just a special function that automatically reads the database row-by-row and neatly packages the data so C++ can print it on the screen.
