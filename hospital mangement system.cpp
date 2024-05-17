#include <iostream>
#include <map>
#include <string>

using namespace std;

struct PatientRecord {
    string name;
    string address;
    int age;
    char sex;
    string diseaseDescription;
    int specialistRoomNumber;
};

class PatientRecordManager {
private:
    map<int, PatientRecord> patientRecords;
    int nextRecordNumber = 1;

public:
    void addNewPatientRecord() {
        PatientRecord newRecord;
        cout << "Enter patient details:\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, newRecord.name);
        cout << "Address: ";
        getline(cin, newRecord.address);
        cout << "Age: ";
        cin >> newRecord.age;
        cout << "Sex (M/F): ";
        cin >> newRecord.sex;
        cout << "Disease Description: ";
        cin.ignore();
        getline(cin, newRecord.diseaseDescription);
        cout << "Specialist Room Number: ";
        cin >> newRecord.specialistRoomNumber;

        patientRecords[nextRecordNumber++] = newRecord;
        cout << "Patient record added for Record Number " << nextRecordNumber - 1 << ".\n";
    }

    void searchOrEditPatientRecord(int recordNumber) {
        auto it = patientRecords.find(recordNumber);
        if (it != patientRecords.end()) {
            printPatientRecord(it->second);
        }
        else {
            cout << "No patient record found for Record Number " << recordNumber << ".\n";
        }
    }

    void searchOrEditPatientRecord(const string& fullName) {
        bool found = false;
        for (const auto& entry : patientRecords) {
            if (entry.second.name == fullName) {
                printPatientRecord(entry.second);
                found = true;
            }
        }
        if (!found) {
            cout << "No patient record found for full name: " << fullName << ".\n";
        }
    }

    void listPatientRecords() {
        if (patientRecords.empty()) {
            cout << "No patient records available.\n";
            return;
        }

        cout << "Listing patient records:\n";
        for (const auto& entry : patientRecords) {
            cout << "Record Number " << entry.first << ":\n";
            printPatientRecord(entry.second);
        }
    }

    void deletePatientRecord(int recordNumber) {
        auto it = patientRecords.find(recordNumber);
        if (it != patientRecords.end()) {
            patientRecords.erase(it);
            cout << "Patient record deleted for Record Number " << recordNumber << ".\n";
        }
        else {
            cout << "No patient record found for Record Number " << recordNumber << ". Cannot delete.\n";
        }
    }

private:
    void printPatientRecord(const PatientRecord& record) {
        cout << "Patient Record:\n";
        cout << "Name: " << record.name << "\n";
        cout << "Address: " << record.address << "\n";
        cout << "Age: " << record.age << "\n";
        cout << "Sex: " << record.sex << "\n";
        cout << "Disease Description: " << record.diseaseDescription << "\n";
        cout << "Specialist Room Number: " << record.specialistRoomNumber << "\n";
        cout << "-------------------------\n";
    }
};

class Menu {
public:
    int displayMainMenu() {
        cout << "Hospital Management System\n";
        cout << "1. Add a New Patient Record\n";
        cout << "2. List Patient Records\n";
        cout << "3. Search/Edit Patient Record\n";
        cout << "4. Delete Patient Record\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        return choice;
    }

    string getFullNameInput() {
        string fullName;
        cout << "Enter full name: ";
        cin.ignore();
        getline(cin, fullName);
        return fullName;
    }

    int getRecordNumberInput() {
        int recordNumber;
        cout << "Enter record number: ";
        cin >> recordNumber;
        return recordNumber;
    }
};

int main() {
    PatientRecordManager patientRecordManager;
    Menu menu;

    while (true) {
        int choice = menu.displayMainMenu();

        switch (choice) {
        case 1:
            patientRecordManager.addNewPatientRecord();
            break;
        case 2:
            patientRecordManager.listPatientRecords();
            break;
        case 3: {
            cout << "Search by Record Number (1) or Full Name (2): ";
            int searchChoice;
            cin >> searchChoice;
            if (searchChoice == 1) {
                int recordNumber = menu.getRecordNumberInput();
                patientRecordManager.searchOrEditPatientRecord(recordNumber);
            }
            else if (searchChoice == 2) {
                string fullName = menu.getFullNameInput();
                patientRecordManager.searchOrEditPatientRecord(fullName);
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 4: {
            int recordNumber = menu.getRecordNumberInput();
            patientRecordManager.deletePatientRecord(recordNumber);
            break;
        }
        case 5:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}