# Hospital Management System: Project Breakdown

## 1. Introduction

### Conversational/Short Version
"I built a Hospital Management System using C++ and SQLite to efficiently manage patient records, doctor profiles, and appointments. I recently integrated a complete login and logout system to securely gate access for hospital staff. To keep the code clean and scalable, I heavily relied on Object-Oriented Programming. I used **Inheritance** to share common traits between doctors and patients, and **Encapsulation** to protect sensitive data. I also used **Abstraction** to hide the complex database code from the main application, and applied **RAII** to automatically manage database connections so the system never leaks memory."

### Detailed Breakdown
I have developed a **Hospital Management System** using **C++** and **SQLite**. This system is designed to streamline healthcare operations by managing patient records, doctor profiles, and appointment scheduling through a persistent database. It also features a robust **Login and Logout authentication system** to ensure only authorized personnel can access or modify hospital data.

In this project, I have implemented several core **Object-Oriented Programming (OOP)** concepts to ensure the code is modular, scalable, and maintainable:
- **Inheritance**: Implemented a base `Person` class to share common attributes like name and contact details between `Patient` and `Doctor` models.
- **Encapsulation**: Used private data members and public methods to protect internal states and ensure data integrity.
- **Abstraction**: Hidden complex SQLite C-API logic behind high-level C++ methods, separating the database layer from the business logic.
- **RAII**: Managed database connections using class constructors and destructors to prevent resource leaks.

## 2. Hook
"Managing a hospital's records manually is slow and insecure. To solve this, I built a fast C++ application that talks directly to an SQL database. I recently implemented a secure login and logout system so that only authorized receptionists can safely manage doctors, patients, and book appointments, demonstrating my ability to build secure, end-to-end backend applications from scratch."

## 3. Architecture
The flow of the project is split cleanly into three parts: the User Interface, the C++ Logic, and the Database Storage.

```text
[User Typing in Terminal Menu] 
      │ 
      ▼
[Authentication System] ───▶ Validates Credentials
      │ 
      ▼
[C++ HospitalSystem (The Brain/Logic)] 
      │
      ▼
[C++ Database Manager (The Translator)] ───▶ Converts C++ to SQL Commands
      │
      ▼
[SQLite File (.db)] ───▶ Permanent Database Storage
```

## 4. Core Explanation
- **Authentication System:** A secure loop at the start of the program requires users to input a valid username and password (verified against the `Users` table in the database) before granting access. It also includes full logout functionality to return to the login screen.
- **The Main Menu:** The `HospitalSystem` file runs a continuous loop on the terminal, asking the user what they want to do (e.g., Add Patient, Book Appointment).
- **OOP Hierarchy (Inheritance):** I used an inheritance model where a base `Person` class handles common fields, and derived `PatientModule` and `DoctorModule` classes handle specific data.
- **Saving Data (SQL):** Instead of storing data temporarily in RAM, the `Database.cpp` file takes those C++ Objects and turns them into `INSERT INTO` SQL commands. This securely saves them to the computer's hard drive.
- **Reading Data:** When viewing appointments, the program sends a `SELECT` SQL command to the database, gets the data back, and prints it in a neat table on the screen.

## 5. Interview Question: "Tell me about your objects"
If an interviewer asks, **"Tell me about the objects/classes in your project and how you used OOP,"** here is the exact breakdown you can give:

1. **`Person` (Abstract Base Class)**: This is the foundation. It holds common data that any individual would have, like `name` and `contact`. I made it an **Abstract Class** using a pure virtual function `displayInfo()`, meaning you can't just create a generic "Person"—they have to be a specific type.
2. **`PatientModule` & `DoctorModule` (Derived Objects)**: These are the core business objects. They inherit from `Person` (**Inheritance**). 
   - `PatientModule` adds fields like `age`, `gender`, and `ailment`.
   - `DoctorModule` adds `specialization`.
   Both override the `displayInfo()` function to print their own specific details differently, which demonstrates **Polymorphism**.
3. **`Database` Object**: This object encapsulates all the complex, low-level SQLite C-API logic (**Encapsulation**). It ensures the database connection is safely opened and closed using constructors and destructors (**RAII pattern**).
4. **`HospitalSystem` Object**: This is the "Orchestrator" object. It contains an instance of the `Database` inside it (**Composition**) and manages the user interface and high-level functions like adding patients or booking appointments.

### 5.1 Interview Question: "Why didn't you use Polymorphism more heavily?"
**If an interviewer asks why you didn't rely on Polymorphism (like lists of `Person*` pointers) everywhere:**
"I used basic polymorphism, but kept it minimal because my app relies on a **database**, not memory. Instead of managing complex lists of pointers in RAM, I instantly save objects to SQLite. Fetching data with SQL queries is much safer and more scalable than storing it all in memory."

## 6. Interview Question: "Database Connection & Rollbacks"
**If an interviewer asks how you connected the database or how you handle errors:**
- **Connecting C++ and SQLite:** "I compiled the SQLite engine (`sqlite3.c`) directly into my application. Instead of connecting to an external server, my C++ program has the database engine built right inside it, using `sqlite3_open()` to start the connection and `sqlite3_exec()` to send queries."
- **How it applies to your project (Rollbacks):** Right now, your app does simple, one-step actions (like adding one patient at a time), so if an action fails, nothing gets saved anyway. But if an interviewer asks, you can tell them: *"A rollback is an undo button. I would use it if I had to update two different tables at the exact same time, to make sure that if one fails, the other one gets canceled too."*

## 7. Interview Question: "Why C++ and SQLite? Why not other technologies?"
**If an interviewer asks why you didn't use easier languages like Python or Java, or bigger databases like MySQL:**

- **Why C++?** "While Python or Java are easier, building this in C++ proves I understand how things actually work under the hood. C++ is extremely fast and forces me to properly use Object-Oriented principles and manage memory. It shows I have strong fundamental programming skills, not just the ability to use pre-built shortcuts."
- **Why SQLite instead of MySQL/PostgreSQL?** "For a standalone local application, a massive database like MySQL is overkill. It requires setting up a whole separate server, managing ports, and configuring passwords. SQLite is lightweight, requires zero setup, and stores the entire database in a single local file (`hospital.db`). This makes the app incredibly easy to share and run instantly on any computer, while still proving I know how to write standard SQL queries."

## 8. Problems Faced While Building
- **Hidden Input Characters (Carriage Returns):** When building the login system, users' `Enter` key presses added hidden `\r` (carriage return) characters to their passwords, causing database lookups to fail. I solved this by explicitly sanitizing and trimming string inputs in C++ before querying the database.
- **Connecting C++ to SQL:** C++ cannot understand SQL by default. I had to learn how to properly link the `sqlite3` library files and use advanced features like pointer callbacks to translate raw Database data into readable C++ lists.
- **Compiling Multiple Files:** Because I organized my code professionally into multiple headers (`.h`) and `.cpp` files, getting them all to compile together at the same time was tricky at first.

## 9. Project Structure
```text
C++project/
├── build.bat              # Script to help compile all the files easily
├── Database.h / .cpp      # The code that talks exclusively to the SQL database
├── HospitalSystem.h/.cpp  # The main logic and user-menu interface
└── sqlite3.h / .c         # The official database engine files
```

## 10. Improvements
- **Visual Interface (GUI):** I would love to upgrade the black-and-white terminal into a real clickable visual app using tools like Qt or ImGui.
- **Role-Based Access Control:** Now that there is a login system, I want to add user roles (Admin vs Standard User) so that only admins can delete or modify records.
- **Online Database:** Upgrading from a local `.db` file to an online cloud database (like MySQL or AWS) so multiple computers could use the app at once.
- **Data Validation & Error Handling:** Adding stricter input validation (e.g., ensuring phone numbers are exactly 10 digits) and creating custom C++ Exceptions for database errors.
- **Search & Filter Functionality:** Building a feature to quickly search for a specific patient by ID/Name, or filter the doctors list by their specialization.
- **Billing Module:** Integrating a billing system that automatically generates an invoice or tracks payments when an appointment is marked as "Completed."

## 11. Key Learnings
Building this taught me how to write clean, professional C++ code by splitting it into multiple files. Most importantly, I learned exactly how backend programming works by successfully making a C++ application communicate directly with a Relational Database using SQL queries.

## 12. Closing Statement
"This project proves that I can do more than just write basic code—I can actually connect multiple technologies together to build a permanent, working backend application. I am excited to bring these software-building skills to a real professional team."
