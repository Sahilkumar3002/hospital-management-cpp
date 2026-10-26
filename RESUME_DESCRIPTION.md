# Resume Description: Hospital Management System (C++)

Here are a few ways to describe this project on your resume, depending on how much space you have.

---

## Option 1: Standard Bullet Points (Best for most resumes)

**Hospital Management System | C++, SQLite, Git**
*   Built a robust backend application using **C++** and **SQLite** to manage patient records, doctor information, and appointment scheduling.
*   Implemented **Object-Oriented Programming (OOP)** principles including **Inheritance** (from a base `Person` class), **Polymorphism** (virtual functions for record display), and **Encapsulation** for data security.
*   Designed a relational database schema for persistent storage, utilizing the **SQLite C-API** to perform CRUD operations (Create, Read, Update, Delete).
*   Optimized data retrieval by using **SQL queries** to fetch and display formatted patient and appointment data in a Command Line Interface (CLI).
*   Developed a custom **callback-based data mapper** to translate raw SQLite data into C++ Standard Template Library (STL) containers, simplifying data processing for the business logic layer.

---

## Option 2: Technical Focus (For "Key Projects" or Portfolio)

### **Hospital Management System (C++ Backend)**
**Technologies:** C++, SQLite3, Header-only library architecture, Batch scripting for build automation.

*   **Architecture:** Developed a multi-layered architecture separating core business logic (`Person`, `Patient`, `Doctor` modules) from the database persistence layer (`Database.cpp`).
*   **Database Integration:** Integrated a light-weight SQLite engine directly into the binary to enable local data persistence without requiring a standalone server.
*   **Advanced OOP:** Utilized an **Abstract Base Class (ABC)** for the `Person` model to ensure strict implementation of the `displayInfo()` method across all specialized sub-classes.
*   **Result:** Created a functional, production-ready backend tool capable of handling hundreds of concurrent records with instant search capability and zero data loss on program termination.

---

## Option 3: Concise (For one-line summaries)

**C++ Hospital Management System:** A full-stack CLI application using C++ and SQLite for healthcare data management, featuring inheritance-based models and persistent relational database storage for patients and staff.

---

## "What can I talk about in the interview?" (Cheat Sheet)

If an interviewer asks about this project, mention these three things:

1.  **The Persistence Challenge:** "I moved from temporary RAM storage to a real SQL database. This meant I had to learn the `sqlite3.h` library and how to bridge the gap between C++ objects and SQL rows."
2.  **The Class Hierarchy:** "I used Inheritance for the `Person` class. This prevented code duplication between Doctors and Patients, making the codebase much cleaner and easier to expand (e.g., adding a 'Nurse' class would take 2 minutes)."
3.  **The Build Process:** "I wrote a custom `build.bat` script to automate the compilation of multiple `.cpp` files with the SQLite engine, demonstrating my understanding of the C++ compilation pipeline."

---

## Skills to list under this project:
- **Languages:** C++ (Core), SQL
- **Database:** SQLite3
- **Tools:** GCC/MinGW, CLI, Batch Scripting
- **Concepts:** Object-Oriented Programming (OOP), RAII, Relational Databases, CRUD Architecture.
