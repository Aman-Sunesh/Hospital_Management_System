#include "Patient.h"
#include "Staff.h"
#include "StaffManager.h"
#include "Utility.h"
#include <iostream>
#include <iterator>

using namespace std;

// Constructor
Patient::Patient(const string& name, int ID,
                 const string& gender,
                 const string& email,
                 const string& mobile)
: Person(name, ID, gender, email, mobile)
{
    // If you want to default other fields, do so
}

// Overridden methods
string Patient::getRole() const
{
    return "Patient";
}



vector<string> Patient::getAilments()
{
    return ailments;
}


void Patient::displayMenu()
{

}


void Patient::displayMenu(StaffManager* S) {

    do
    {
        cout << endl;
        cout << "------------------------------------------------\n";
        cout << "|               Patient Menu                   |\n";
        cout << "| 1. View Personal Details                     |\n";
        cout << "| 2. Select Preferred Doctor                   |\n";
        cout << "| 3. View Scheduled Appointments               |\n";
        cout << "| 4. Update Contact Information                |\n";
        cout << "| 5. View Medical Prescription                 |\n";
        cout << "| 6. View Doctor's Post-Consultation Notes     |\n";
        cout << "| 7. Submit Feedback on Treatment              |\n";
        cout << "| 8. Log Out                                   |\n";
        cout << "------------------------------------------------\n";

        int choice;

        do {
            cout << "Enter your choice(1-8): ";

            if (isInvalidInput(choice)) // If the input is invalid, isInvalidInput will handle the error message
            {
                continue; // Skip the rest of the loop and prompt the user again
            }

            if (choice < 1 || choice > 8)  // Check if the choice is outside the valid range
            {
                cout << "Error! Invalid Choice. Please enter a number between 1 and 8." << endl;
            }

        } while (choice < 1 || choice > 8); // Repeat until a valid choice is entered


        switch (choice)
        {
            case 1:
            {
                viewDetails();
                break;
            }

            case 2:
            {
                selectDoctor(S);
                break;
            }

            case 3:
            {
                viewScheduledAppointments();
                break;
            }

            case 4:
            {
                string newEmail, newMobileNo;

                cout << "Enter new email ID: ";
                cin >> newEmail;
                cout << endl;

                cout << "Enter new mobile no. : ";
                cin >> newMobileNo;
                cout << endl;

                updateContactInfo(newEmail, newMobileNo);
                break;
            }

            case 5:
            {
                viewMedicalPrescription();
                break;
            }

            case 6:
            {
                viewPostConsultationNotes();
                break;
            }

            case 7:
            {
                submitFeedback(S);
                break;
            }


            case 8:
            {
                cout << "Exiting Patient Menu...\n";
                return;  
            }

            default:
            {
                cout << "Invalid Input! Please try again.\n";
            }
        }
    } while (true);

}

void Patient::viewDetails() const
{
    cout << "------------------------------------" << endl;
    cout << "Name: " << name << endl;
    cout << "ID: " << ID << endl;
    cout << "Email ID: " << email << endl;
    cout << "Mobile No.: " << mobile << endl;

    cout << "Ailments: ";
    if (!ailments.empty()) {
        for (size_t i = 0; i < ailments.size(); ++i) {
            cout << ailments[i];
            if (i < ailments.size() - 1) {
                cout << ", "; // Add a comma for all but the last ailment
            }
        }
    } else {
        cout << "None";
    }
    cout << endl;

    cout << "------------------------------------" << endl;
    cout << endl;
}


void Patient::selectDoctor(StaffManager* staffMgr)
{
    Doctor* doctor = nullptr;
    string choice, dept, doctorName;

    cout << "Do you want to view the available doctors (Yes/No): ";
    cin >> choice;
    cout << endl;

    // Convert choice to lowercase for case-insensitive comparison
    transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

    // If user wants to view doctors by department
    if (choice == "yes") 
    {
        // 1) Ask StaffManager for all department names
        vector<string> departments = staffMgr->displayDepartments();

        if (departments.empty()) {
            cout << "No departments available at the moment.\n";
            return;
        }

        // Show available departments
        cout << "Departments:\n";
        for (size_t i = 0; i < departments.size(); i++) {
            cout << i + 1 << ": " << departments[i] << endl;
        }
        cout << endl;

        cout << "Select preferred department (Enter Name of Dept.): ";
        cin >> dept;
        cout << endl;

        // Validate the department
        if (find(departments.begin(), departments.end(), dept) == departments.end()) {
            cout << "Invalid department. Please try again.\n";
            return;
        }

        // 2) Show all doctors in that department
        // We get the entire doctor list from StaffManager:
        vector<Doctor*> allDoctors = staffMgr->getDoctors();

        // We'll gather only those matching `dept`
        vector<Doctor*> departmentDoctors;
        for (auto* d : allDoctors) {
            if (d->getDepartment() == dept) {
                departmentDoctors.push_back(d);
            }
        }

        if (departmentDoctors.empty()) {
            cout << "No doctors available in the " << dept << " department.\n";
            return;
        }

        cout << "List of doctors in " << dept << " department:\n";
        for (size_t i = 0; i < departmentDoctors.size(); i++) {
            cout << i + 1 << ": " << departmentDoctors[i]->getName() << endl;
        }
        cout << endl;
    }

    // 3) Regardless of “yes” or “no,” we let the user type a doctor name
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter the name of the doctor: ";
    getline(cin, doctorName);
    cout << endl;

    // 4) Find the chosen doctor by name in the entire staff manager list
    vector<Doctor*> allDocs = staffMgr->getDoctors();
    for (auto* d : allDocs) {
        if (d->getName() == doctorName) {
            doctor = d;
            break;
        }
    }

    if (!doctor) {
        cout << "Doctor not found. Please try again.\n";
        return;
    }

    // 5) Create and populate the appointment
    Appointment appointment;
    cout << "Enter the reason for the appointment: ";
    getline(cin, appointment.reason);

    cout << "Enter appointment day (DD MM YYYY HH MM): ";
    cin >> appointment.appointmentTime.day
        >> appointment.appointmentTime.month
        >> appointment.appointmentTime.year
        >> appointment.appointmentTime.hour
        >> appointment.appointmentTime.minute;

    // If your Doctor class has a method like addRequestedAppointment(...):
    // We pass this Patient's ID:
    doctor->addRequestedAppointment(appointment, this->getID());

    cout << "Request for appointment with Dr. " << doctorName << " has been placed." << endl;
}


void Patient::viewScheduledAppointments() const {
    if (scheduledAppointments.empty()) {
        std::cout << "No scheduled appointments at the moment." << std::endl;
        return;
    }

    std::cout << "Scheduled Appointments: " << std::endl;
    for (const auto& pair : scheduledAppointments) {
        const std::string& doctorName = pair.first;
        const auto& appointments = pair.second; // appointments is now vector<Appointment>
        for (const auto& appointment : appointments) { // Valid now
            std::cout << "Doctor Name: " << doctorName << std::endl;
            std::cout << "   Appointment Time: "
                      << appointment.appointmentTime.day << "/"
                      << appointment.appointmentTime.month << "/"
                      << appointment.appointmentTime.year << " at "
                      << appointment.appointmentTime.hour << ":"
                      << (appointment.appointmentTime.minute < 10 ? "0" : "") 
                      << appointment.appointmentTime.minute << std::endl;
            std::cout << "   Reason: " << appointment.reason << std::endl;
            std::cout << "---------------------------------" << std::endl;
        }
    }
}


void Patient::updateContactInfo(const string& emailID, const string& mobileNo)
{
    this->email = emailID;
    this->mobile = mobileNo;

    cout << "Contact Information has been updated successfully!" << endl;
    cout << endl;
}

void Patient::viewMedicalPrescription() const
{
    if (prescriptions.empty())
    {
        cout << "No medical prescriptions available." << endl;
        return;
    }

    cout << "Medical Prescriptions:" << endl;
    cout << "---------------------------------" << endl;

    for (const auto& prescription : prescriptions)
    {
        const DateTime& date_time = prescription.dateTime;
        const string& notes = prescription.notes;
        const string& doctorName = prescription.doctorName;

        cout << "Date: " << date_time.day << "/" << date_time.month << "/" << date_time.year
             << " Time: " << date_time.hour << ":" 
             << (date_time.minute < 10 ? "0" : "") << date_time.minute << endl;
        cout << "Doctor: Dr. " << doctorName << endl;
        cout << "Prescription: " << notes << endl;
        cout << "---------------------------------" << endl;
    }
}

void Patient::viewPostConsultationNotes() const
{
    if (postConsultationNotes.empty())
    {
        cout << "No post-consultation notes available." << endl;
        return;
    }

    cout << "Post-Consultation Notes:" << endl;
    cout << "---------------------------------" << endl;

    for (const auto& note : postConsultationNotes)
    {
        const DateTime& date_time = note.dateTime;
        const string& notes = note.notes;
        const string& doctorName = note.doctorName;

        cout << "Date: " << date_time.day << "/" << date_time.month << "/" << date_time.year
             << " Time: " << date_time.hour << ":" 
             << (date_time.minute < 10 ? "0" : "") << date_time.minute << endl;
        cout << "Doctor: Dr. " << doctorName << endl;
        cout << "Notes: " << notes << endl;
        cout << "---------------------------------" << endl;
    }
}


void Patient::submitFeedback(StaffManager* S) const
{
    string doctorName;
    Doctor* doctor = nullptr;

    cout << "Enter the name of the doctor: ";
    cin >> doctorName;

    doctor = S->findDoctorByName(doctorName);

    if (doctor == nullptr)
    {
        cout << "Doctor not found, please try again!";
        return;
    }

    else
    {
        string feedback;

        cout << "Enter feedback for Dr." << doctorName << " : ";
        cin.ignore(); // Clear leftover input
        getline(cin, feedback); // Read a full line of feedback
        cout << endl;

        doctor->addFeedback(feedback);
        cout << "Feedback submitted successfully for Dr. " << doctorName << "!" << endl;
    }


}


void Patient::addAppointment(const string& doctorName, const Appointment& appt)
{
    scheduledAppointments[doctorName].push_back(appt); // Add to the vector
}


void Patient::deleteAppointment(const string& doctorName)
{
    scheduledAppointments.erase(doctorName);
}

void Patient::addPostConsultationNotes(const DateTime& date_time, const string& notes, const string& doctorName)
{
    PostConsultationNote newNote = { date_time, notes, doctorName };
    postConsultationNotes.push_back(newNote);

    cout << "Post-consultation notes from Dr. " << doctorName << " have been successfully added for "
         << date_time.day << "/" << date_time.month << "/" << date_time.year
         << " at " << date_time.hour << ":" 
         << (date_time.minute < 10 ? "0" : "") << date_time.minute << "." << endl;
}

void Patient::addPrescription(const DateTime& date_time, const string& notes, const string& doctorName)
{
    Prescription newPrescription = { date_time, notes, doctorName };
    prescriptions.push_back(newPrescription);

    cout << "Medical prescription from Dr. " << doctorName << " for patient " << getName() 
         << " has been successfully added for "
         << date_time.day << "/" << date_time.month << "/" << date_time.year
         << " at " << date_time.hour << ":" 
         << (date_time.minute < 10 ? "0" : "") << date_time.minute << "." << endl;
}


// Setter for name
void Patient::setName(const string& newName) {
    if (!newName.empty()) {
        name = newName;
    } else {
        cerr << "Error: Name cannot be empty.\n";
    }
}

string Patient::trimAndLower(const string& str) {
    string trimmed = regex_replace(str, regex("^\\s+|\\s+$"), ""); // Remove leading and trailing spaces
    transform(trimmed.begin(), trimmed.end(), trimmed.begin(), ::tolower); // Convert to lowercase
    return trimmed;
}
