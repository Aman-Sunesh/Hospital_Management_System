#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <unordered_map> 
#include "SharedTypes.h"
#include "Person.h"

using namespace std;

class Doctor;
class StaffManager;


class Patient : public Person
{
    private:
        vector <string> ailments;
        vector <Staff*> assignedDoctors;
        map<string, vector<Appointment>> scheduledAppointments;
        vector<Prescription> prescriptions; 
        vector<PostConsultationNote> postConsultationNotes; 
        

    public:
        Patient() = default;
        Patient(const string& name, int ID, const string& gender, const string& email, const string& mobile);

        // Overridden methods from User
        virtual string getRole() const override;
        virtual void displayMenu();
        void displayMenu(StaffManager* S);
        void setName(const string& newName);
        void viewDetails() const;
        void selectDoctor(StaffManager* staffMgr);
        void viewScheduledAppointments() const;
        void updateContactInfo(const string& emailID, const string& mobileNo);
        void viewMedicalHistory() const;
        void viewMedicalPrescription() const;
        void viewPostConsultationNotes() const;
        void submitFeedback(StaffManager* S) const;

        void assignDoctor(Staff* doctor);
        void updateAilment(const string& ailment);

        vector<string> getAilments();
        void addAppointment(const string& doctorName, const Appointment& appt);
        void deleteAppointment(const string& doctorName);
        void addPostConsultationNotes(const DateTime& date_time, const string& notes, const string& doctorName);
        void addPrescription(const DateTime& date_time, const string& notes, const string& doctorName);
        string trimAndLower(const string& str);
};

#endif // PATIENT_H