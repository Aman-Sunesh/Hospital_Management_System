#include "Doctor.h"
#include "PatientManager.h"
#include "Patient.h"
#include "Utility.h"

using namespace std;

// Constructor
Doctor::Doctor(const string& name, int ID,
               const string& gender,
               const string& email,
               const string& mobile,
               const string& department)
: Staff(name, ID, gender, email, mobile, department)
{
    // ...
}
// Overridden methods
string Doctor::getRole() const
{
    return "Doctor";
}


void Doctor::displayMenu(PatientManager* pm) {

    do
    {
        cout << endl;
        cout << "------------------------------------------------\n";
        cout << "|                 Doctor Menu                  |\n";
        cout << "| 1. Manage Appointments                       |\n";
        cout << "| 2. View Scheduled Appointments               |\n";
        cout << "| 3. View Patient Details                      |\n";
        cout << "| 4. Add Post-Consultation Notes               |\n";
        cout << "| 5. Prescribe Medication                      |\n";
        cout << "| 6. View Feedback from Patients               |\n";
        cout << "| 7. Log Out                                   |\n";
        cout << "------------------------------------------------\n";

        int choice;

        do {
            cout << "Enter your choice(1-7): ";

            if (isInvalidInput(choice)) // If the input is invalid, isInvalidInput will handle the error message
            {
                continue; // Skip the rest of the loop and prompt the user again
            }

            if (choice < 1 || choice > 7)  // Check if the choice is outside the valid range
            {
                cout << "Error! Invalid Choice. Please enter a number between 1 and 6." << endl;
            }

        } while (choice < 1 || choice > 7); // Repeat until a valid choice is entered

        switch (choice)
        {
            case 1:
            {
                manageAppointments(pm);
                break;
            }

            case 2:
            {
                viewScheduledAppointments(pm);
                break;
            }

            case 3:
            {
                viewPatientDetails();
                break;
            }

            case 4:
            {
                addPostConsultationNotes();
                break;
            }

            case 5:
            {
                prescribeMedication();
                break;
            }

            case 6:
            {
                viewFeedback();
                break;
            }

            case 7:
            {
                cout << "Exiting Doctor Menu...\n";
                return;  // Exit the menu loop
            }

            default:
            {
                cout << "Invalid Input! Please try again.\n";
            }
        }
    } while (true);
}

void Doctor::manageAppointments(PatientManager* pm) 
{
    cout << "1. View Appointments" << endl;
    cout << "2. Accept/Reject Appointments" << endl;
    cout << "3. Delete Appointments" << endl;

    int choice;

    cout << "Enter your choice (1-3): " << endl;
    cin >> choice;

    if(choice == 1)
    {
        map<int, Appointment>:: iterator it = requestedAppointments.begin();
        int counter = 1;

        cout << "Requested Appointments: " << endl;

        if (requestedAppointments.empty()) {
            cout << "No requested appointments at the moment." << endl;
            return;
        }

        // Iterate through the map and print the elements
        while (it != requestedAppointments.end()) {
            int patientID = it->first;              // Patient ID
            Appointment appointment = it->second;  // Appointment details

            Patient* patient = pm->findPatientByID(patientID);

            cout << counter << ". Patient ID: " << patientID << endl;

            if (patient) 
            {
                cout << "   Name: " << patient->getName() << endl; // Fetch patient name
            } 
            
            else 
            {
                cout << "   Name: Unknown (Patient not found)" << endl;
            }

            cout << "   Appointment Time: " 
                 << appointment.appointmentTime.day << "/"
                 << appointment.appointmentTime.month << "/"
                 << appointment.appointmentTime.year << " at "
                 << appointment.appointmentTime.hour << ":"
                 << appointment.appointmentTime.minute << endl;
            cout << "   Reason: " << appointment.reason << endl;

            ++it;
            counter++;
        }
    }

    else if (choice == 2)
    {
        int patientID;

        cout << "Enter patient ID: ";
        cin >> patientID;
        cout << endl;

        auto it = requestedAppointments.find(patientID);

        if (it == requestedAppointments.end()) {
            cout << "No requested appointment found for Patient ID: " << patientID << endl;
            return;
        }

        Appointment appointment = it->second;

        cout << "1. Accept Appointment" << endl;
        cout << "2. Decline Appointment" << endl;

        int subChoice;
        cout << "Enter your choice (1-2): ";
        cin >> subChoice;
        cout << endl;

        if (subChoice == 1)
        {
            Patient* patient = pm->findPatientByID(patientID);
            
            if (patient)
            {
                scheduledAppointments[patientID] = appointment;
                requestedAppointments.erase(patientID);
                patient->addAppointment(this->name, appointment);
                patientList.push_back(patient);
                requestedAppointments.erase(patientID);
            }

            cout << "Appointment has been booked!";
        }

        else if (subChoice == 2)
        {
            scheduledAppointments.erase(patientID);

            cout << "Requested appointment has been declined." << endl;
        }

        else{
            cout << "Invalid choice. Returning to menu..." << endl;
        }
    
    }
    

    else if (choice == 3) // Delete Appointments
    {
        int patientID;

        cout << "Enter patient ID: ";
        cin >> patientID;
        cout << endl;

        

        auto it = scheduledAppointments.find(patientID);
        if (it == scheduledAppointments.end()) {
            cout << "No scheduled appointment found for Patient ID: " << patientID << endl;
            return;
        }

        scheduledAppointments.erase(patientID); // Remove appointment

        Patient* patient = pm->findPatientByID(patientID);
            
        if (patient)
        {
            patient->deleteAppointment(this->name);
        }

        cout << "Scheduled appointment has been cancelled." << endl;
    } 
    else 
    {
        cout << "Invalid choice. Returning to menu." << endl;
    }
        
}


void Doctor::viewScheduledAppointments(PatientManager* pm)
{
    map<int, Appointment>:: iterator it = scheduledAppointments.begin();
    int counter = 1;

    cout << "Scheduled Appointments: " << endl;

    if (scheduledAppointments.empty()) {
        cout << "No scheduled appointments at the moment." << endl;
        return;
    }

    // Iterate through the map and print the elements
    while (it != scheduledAppointments.end()) {
        int patientID = it->first;              // Patient ID
        Appointment appointment = it->second;  // Appointment details

        Patient* patient = pm->findPatientByID(patientID);

        cout << counter << ". Patient ID: " << patientID << endl;

        if (patient) 
        {
            cout << "   Name: " << patient->getName() << endl; // Fetch patient name
        } 
        
        else 
        {
            cout << "   Name: Unknown (Patient not found)" << endl;
        }

        cout << "   Appointment Time: " 
                << appointment.appointmentTime.day << "/"
                << appointment.appointmentTime.month << "/"
                << appointment.appointmentTime.year << " at "
                << appointment.appointmentTime.hour << ":"
                << appointment.appointmentTime.minute << endl;
        cout << "   Reason: " << appointment.reason << endl;

        ++it;
        counter++;
    }
}

void Doctor::viewPatientDetails()
{
    if (patientList.empty())
    {
        cout << "You currently do not have any patients.\n";
        return;
    }

    cout << "Patient Details:\n";

    for (size_t i = 0 ; i < patientList.size() ; i++)
    {
        Patient* patient = patientList[i];

        cout << "----------------------------------\n";
        cout << "ID: " << patient->getID() << endl;
        cout << "Name: " << patient->getName() << endl;
        
        const vector<string>& ailments = patient->getAilments();

        cout << "Ailments: ";


        for (size_t j = 0 ; j < ailments.size() ; j++)
        {
            cout << ailments[j];
            if (j < ailments.size() - 1) {
                cout << ", "; // Add a comma for all but the last ailment
            }
        }

        cout << endl;
    }
}

void Doctor::addPostConsultationNotes()
{
    int patientID;

    cout << "Enter patient ID: ";
    cin >> patientID;
    cout << endl;

    for (size_t i = 0 ; i < patientList.size() ; i++)
    {
        if (patientList[i]->getID() == patientID)
        {
            Patient* patient = patientList[i];
            string note;

            cout << "Post-Consultation Notes: ";
            cin.ignore();
            getline(cin, note);
            cout << endl;

            // Get the current date and time
            DateTime date_time;
            time_t now = time(nullptr);
            tm* localTime = localtime(&now);

            date_time.day = localTime->tm_mday;
            date_time.month = localTime->tm_mon + 1;
            date_time.year = localTime->tm_year + 1900;
            date_time.hour = localTime->tm_hour;
            date_time.minute = localTime->tm_min;

            // Add post-consultation notes with doctor's name
            patient->addPostConsultationNotes(date_time, note, this->getName());

            cout << "Post-consultation notes successfully added for Patient ID: " << patientID << "." << endl;
            return;

        }
    }

    // If the patient was not found in the list
    cout << "Patient with ID " << patientID << " not found in your records." << endl;
}

void Doctor::prescribeMedication()
{
    int patientID;

    // Prompt for the patient ID
    cout << "Enter patient ID: ";
    cin >> patientID;
    cout << endl;

    // Search for the patient in the doctor's patient list
    for (size_t i = 0; i < patientList.size(); i++)
    {
        if (patientList[i]->getID() == patientID)
        {
            Patient* patient = patientList[i];
            string prescription;

            // Prompt for the prescription details
            cout << "Prescription Notes: ";
            cin.ignore(); // Clear the input buffer
            getline(cin, prescription);
            cout << endl;

            // Get the current date and time
            DateTime date_time;
            time_t now = time(nullptr);
            tm* localTime = localtime(&now);

            date_time.day = localTime->tm_mday;
            date_time.month = localTime->tm_mon + 1;
            date_time.year = localTime->tm_year + 1900;
            date_time.hour = localTime->tm_hour;
            date_time.minute = localTime->tm_min;

            // Add the prescription to the patient's record with doctor's name
            patient->addPrescription(date_time, prescription, this->getName());

            cout << "Prescription successfully added for Patient ID: " << patientID << "." << endl;
            return;
        }
    }

    // If the patient was not found in the list
    cout << "Patient with ID " << patientID << " not found in your records." << endl;
}

void Doctor::viewFeedback()
{
    if (feedback.empty())
    {
        cout << "No feedback available for you at the moment." << endl;
        return;
    }

    for (size_t i = 0; i < feedback.size(); i++)
    {
        cout << "Feedback " << i + 1 << ": " << endl;  // Fixed index
        cout << feedback[i] << endl;
        cout << "---------------------------------" << endl; // Separator for better readability
    }
}


void Doctor::addFeedback(const string& Feedback)
{
    feedback.push_back(Feedback);
}

void Doctor::addRequestedAppointment(const Appointment& appointment, int ID)
{
    if (requestedAppointments.find(ID) != requestedAppointments.end()) 
    {
        cout << "Appointment with this ID already exists.\n";
        return;
    }

    requestedAppointments[ID] = appointment;
}
