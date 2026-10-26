#ifndef HOSPITAL_SYSTEM_H
#define HOSPITAL_SYSTEM_H

#include "Database.h"
#include "Person.h"
#include <string>

class HospitalSystem {
private:
    Database db;

    void initializeDatabase();

public:
    HospitalSystem(const std::string& dbPath);

    // Patient Operations
    void addPatient(const PatientModule& patient);
    void viewPatients();

    // Doctor Operations
    void addDoctor(const DoctorModule& doctor);
    void viewDoctors();

    // Appointment Operations
    void scheduleAppointment(int patientId, int doctorId, const std::string& dateStr);
    void viewAppointments();

    // Authentication
    bool login(const std::string& username, const std::string& password);
};

#endif // HOSPITAL_SYSTEM_H
