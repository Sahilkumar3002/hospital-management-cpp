#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

// Base Class - Demonstrating Inheritance
class Person {
protected:
    std::string name;
    std::string contact;

public:
    Person(const std::string& n, const std::string& c) : name(n), contact(c) {}
    virtual ~Person() {}

    // Pure virtual function makes this an Abstract Base Class (ABC)
    virtual void displayInfo() const = 0; 

    std::string getName() const { return name; }
    std::string getContact() const { return contact; }
};

// Derived Class: Patient
class PatientModule : public Person {
private:
    int age;
    std::string gender;
    std::string ailment;

public:
    PatientModule(const std::string& n, int a, const std::string& g, const std::string& c, const std::string& ail)
        : Person(n, c), age(a), gender(g), ailment(ail) {}

    void displayInfo() const override {
        std::cout << "[Patient] Name: " << name << ", Ailment: " << ailment << std::endl;
    }

    int getAge() const { return age; }
    std::string getGender() const { return gender; }
    std::string getAilment() const { return ailment; }
};

// Derived Class: Doctor
class DoctorModule : public Person {
private:
    std::string specialization;

public:
    DoctorModule(const std::string& n, const std::string& spec, const std::string& c)
        : Person(n, c), specialization(spec) {}

    void displayInfo() const override {
        std::cout << "[Doctor] Name: " << name << ", Specialization: " << specialization << std::endl;
    }

    std::string getSpecialization() const { return specialization; }
};

#endif // PERSON_H
