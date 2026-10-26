#include "HospitalSystem.h"
#include <iostream>
#include <string>
#include <limits>

void displayMenu() {
    std::cout << "\n=== Hospital Management System ===\n";
    std::cout << "1. Add Patient\n";
    std::cout << "2. View Patients\n";
    std::cout << "3. Add Doctor\n";
    std::cout << "4. View Doctors\n";
    std::cout << "5. Schedule Appointment\n";
    std::cout << "6. View Appointments\n";
    std::cout << "7. Logout\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    HospitalSystem hospital("hospital.db");
    
    bool isRunning = true;
    while (isRunning) {
        std::cout << "=== Hospital Management System Login ===\n";
        std::string username, password;
        bool loggedIn = false;
    
    while (!loggedIn) {
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::cout << "Password: ";
        std::getline(std::cin, password);
        
        if (hospital.login(username, password)) {
            std::cout << "Login successful!\n";
            loggedIn = true;
        } else {
            std::cout << "Invalid credentials. Please try again.\n\n";
        }
    }

    int choice;

    do {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear newline

        switch (choice) {
            case 1: {
                std::string name, gender, contact, ailment;
                int age;
                std::cout << "Enter Patient Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Age: ";
                std::cin >> age;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Gender: ";
                std::getline(std::cin, gender);
                std::cout << "Enter Contact: ";
                std::getline(std::cin, contact);
                std::cout << "Enter Ailment: ";
                std::getline(std::cin, ailment);
                
                hospital.addPatient(PatientModule(name, age, gender, contact, ailment));
                break;
            }
            case 2:
                hospital.viewPatients();
                break;
            case 3: {
                std::string name, spec, contact;
                std::cout << "Enter Doctor Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Specialization: ";
                std::getline(std::cin, spec);
                std::cout << "Enter Contact: ";
                std::getline(std::cin, contact);
                
                hospital.addDoctor(DoctorModule(name, spec, contact));
                break;
            }
            case 4:
                hospital.viewDoctors();
                break;
            case 5: {
                int patientId, doctorId;
                std::string date;
                std::cout << "Enter Patient ID: ";
                std::cin >> patientId;
                std::cout << "Enter Doctor ID: ";
                std::cin >> doctorId;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Appointment Date (YYYY-MM-DD HH:MM): ";
                std::getline(std::cin, date);
                
                hospital.scheduleAppointment(patientId, doctorId, date);
                break;
            }
            case 6:
                hospital.viewAppointments();
                break;
            case 7:
                std::cout << "Logging out...\n\n";
                loggedIn = false;
                break;
            case 0:
                std::cout << "Exiting system. Goodbye!\n";
                isRunning = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0 && loggedIn);
    }

    return 0;
}
