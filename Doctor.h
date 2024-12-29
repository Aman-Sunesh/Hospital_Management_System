#ifndef DOCTOR_H
#define DOCTOR_H

#include "Staff.h"
#include "SharedTypes.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

class Patient; // Forward declaration
class PatientManager; // Forward declaration

class Doctor : public Staff
{
private:
    map<int, Appointment> requestedAppointments;    
    map<int, Appointment> scheduledAppointments;
    vector<string> feedback;
    vector <Patient*> patientList;

public:
    // Constructors
    Doctor() = default;
    Doctor(const string& name, int ID,
           const string& gender,
           const string& email, 
           const string& mobile,
           const string& department);

    // Overridden methods
    virtual string getRole() const override;

    void displayMenu(PatientManager* pm) ;

    // Doctor-specific functions
    void manageAppointments(PatientManager* pm); // Used to approve or cancel appointment requests by patients & drop completed appointments
    void viewScheduledAppointments(PatientManager* pm);
    void viewPatientDetails(); // General Details & Medical History
    void addPostConsultationNotes();
    void prescribeMedication();
    void viewFeedback();
    
    void addFeedback(const string& Feedback);
    void addRequestedAppointment(const Appointment& appointment, int ID);

};

#endif // DOCTOR_H
