#include "HospitalSystem.h"
#include <iostream>
#include <iomanip>

HospitalSystem::HospitalSystem(const std::string& dbPath) : db(dbPath) {
    initializeDatabase();
}

void HospitalSystem::initializeDatabase() {
    db.execute("CREATE TABLE IF NOT EXISTS Users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "username TEXT UNIQUE NOT NULL, "
               "password TEXT NOT NULL);");
               
    db.execute("INSERT OR IGNORE INTO Users (username, password) VALUES ('admin', 'admin123');");

    db.execute("CREATE TABLE IF NOT EXISTS Patients ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "age INTEGER NOT NULL, "
               "gender TEXT NOT NULL, "
               "contact TEXT NOT NULL, "
               "ailment TEXT NOT NULL);");

    db.execute("CREATE TABLE IF NOT EXISTS Doctors ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "specialization TEXT NOT NULL, "
               "contact TEXT NOT NULL);");

    db.execute("CREATE TABLE IF NOT EXISTS Appointments ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "patient_id INTEGER, "
               "doctor_id INTEGER, "
               "appointment_date TEXT NOT NULL, "
               "status TEXT DEFAULT 'Scheduled', "
               "FOREIGN KEY(patient_id) REFERENCES Patients(id), "
               "FOREIGN KEY(doctor_id) REFERENCES Doctors(id));");
}

void HospitalSystem::addPatient(const PatientModule& patient) {
    std::string query = "INSERT INTO Patients (name, age, gender, contact, ailment) VALUES ('" + 
                        patient.getName() + "', " + std::to_string(patient.getAge()) + ", '" + 
                        patient.getGender() + "', '" + patient.getContact() + "', '" + patient.getAilment() + "');";
    if (db.execute(query)) {
        std::cout << "Patient added successfully.\n";
    }
}

void HospitalSystem::viewPatients() {
    auto results = db.query("SELECT * FROM Patients;");
    if (results.empty()) {
        std::cout << "No patients found.\n";
        return;
    }
    
    std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Name" << std::setw(5) << "Age" 
              << std::setw(10) << "Gender" << std::setw(15) << "Contact" << "Ailment\n";
    std::cout << std::string(70, '-') << "\n";
    
    for (const auto& row : results) {
        std::cout << std::left << std::setw(5) << row.at("id") << std::setw(20) << row.at("name") 
                  << std::setw(5) << row.at("age") << std::setw(10) << row.at("gender") 
                  << std::setw(15) << row.at("contact") << row.at("ailment") << "\n";
    }
}

void HospitalSystem::addDoctor(const DoctorModule& doctor) {
    std::string query = "INSERT INTO Doctors (name, specialization, contact) VALUES ('" + 
                        doctor.getName() + "', '" + doctor.getSpecialization() + "', '" + doctor.getContact() + "');";
    if (db.execute(query)) {
        std::cout << "Doctor added successfully.\n";
    }
}

void HospitalSystem::viewDoctors() {
    auto results = db.query("SELECT * FROM Doctors;");
    if (results.empty()) {
        std::cout << "No doctors found.\n";
        return;
    }
    
    std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Name" 
              << std::setw(20) << "Specialization" << "Contact\n";
    std::cout << std::string(60, '-') << "\n";
    
    for (const auto& row : results) {
        std::cout << std::left << std::setw(5) << row.at("id") << std::setw(20) << row.at("name") 
                  << std::setw(20) << row.at("specialization") << row.at("contact") << "\n";
    }
}

void HospitalSystem::scheduleAppointment(int patientId, int doctorId, const std::string& dateStr) {
    std::string query = "INSERT INTO Appointments (patient_id, doctor_id, appointment_date) VALUES (" + 
                        std::to_string(patientId) + ", " + std::to_string(doctorId) + ", '" + dateStr + "');";
    if (db.execute(query)) {
        std::cout << "Appointment scheduled successfully.\n";
    }
}

void HospitalSystem::viewAppointments() {
    std::string query = "SELECT Appointments.id, Patients.name AS patient_name, Doctors.name AS doctor_name, "
                        "Appointments.appointment_date, Appointments.status "
                        "FROM Appointments "
                        "JOIN Patients ON Appointments.patient_id = Patients.id "
                        "JOIN Doctors ON Appointments.doctor_id = Doctors.id;";
    
    auto results = db.query(query);
    if (results.empty()) {
        std::cout << "No appointments found.\n";
        return;
    }

    std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Patient" 
              << std::setw(20) << "Doctor" << std::setw(20) << "Date" << "Status\n";
    std::cout << std::string(80, '-') << "\n";
    
    for (const auto& row : results) {
        std::cout << std::left << std::setw(5) << row.at("id") << std::setw(20) << row.at("patient_name") 
                  << std::setw(20) << row.at("doctor_name") << std::setw(20) << row.at("appointment_date") 
                  << row.at("status") << "\n";
    }
}

bool HospitalSystem::login(const std::string& username, const std::string& password) {
    std::string user = username;
    std::string pass = password;
    
    // Trim trailing whitespace and carriage returns
    user.erase(user.find_last_not_of(" \n\r\t") + 1);
    pass.erase(pass.find_last_not_of(" \n\r\t") + 1);

    std::string query = "SELECT * FROM Users WHERE username = '" + user + "' AND password = '" + pass + "';";
    auto results = db.query(query);
    return !results.empty();
}
