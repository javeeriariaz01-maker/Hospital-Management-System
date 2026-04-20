#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;

// ===== STRUCTS =====

struct Doctor {
    int id;
    string name;
    string specialization;
    bool available;
};
queue<Doctor> doctorQueue;

struct Nurse {
    int id;
    string name;
    bool available;
};

struct Patient {
    int id;
    string name;
    string condition;
    int priority;
    bool operator<(const Patient& other) const {
    	return priority < other.priority; // max heap
	}
};
priority_queue<Patient> patientQueue;

// ===== FUNCTIONS =====

// Add Doctor
void addDoctor() {
    Doctor d;

    cout << "Enter Doctor ID: ";
    cin >> d.id;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, d.name);

    cout << "Enter Specialization: ";
    getline(cin, d.specialization);

    d.available = true;

	ofstream file("data/doctors.txt", ios::app);

    file << d.id << ","
         << d.name << ","
         << d.specialization << ","
         << d.available << endl;

    file.close();

    cout << "Doctor added successfully!\n";
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
// Add Nurse
void addNurse() {
    Nurse n;

    cout << "Enter Nurse ID: ";
    cin >> n.id;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, n.name);

    n.available = true;

    ofstream file("data/nurses.txt", ios::app);

    file << n.id << ","
         << n.name << ","
         << n.available << endl;

    file.close();

    cout << "Nurse added successfully!\n";
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
// Add Patient
void addPatient() {
    Patient p;

    cout << "Enter Patient ID: ";
    cin >> p.id;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, p.name);

    cout << "Enter Condition (Critical/Normal): ";
    getline(cin, p.condition);
    if (p.condition == "Critical" || p.condition == "critical") {
    p.priority = 10;
} else {
    p.priority = 1;
}

patientQueue.push(p);

    ofstream file("data/patients.txt", ios::app);

    file << p.id << ","
         << p.name << ","
         << p.condition << endl;

    file.close();

    cout << "Patient added successfully!\n";
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
void viewDoctors() {
    ifstream file("data/doctors.txt");

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    string line;

    cout << "\n===== DOCTORS LIST =====\n";

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, spec, avail;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, spec, ',');
        getline(ss, avail, ',');

        cout << "ID: " << id
             << " | Name: " << name
             << " | Specialization: " << spec
             << " | Available: " << avail << endl;
 
    }
    bool isEmpty = true;

while (getline(file, line)) {
    isEmpty = false;
    // existing code
}

if (isEmpty) {
    cout << "No doctors found.\n";
}

    file.close();
    
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
void viewNurses() {
    ifstream file("data/nurses.txt");

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    string line;

    cout << "\n===== NURSES LIST =====\n";

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, avail;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, avail, ',');

        cout << "ID: " << id
             << " | Name: " << name
             << " | Available: " << avail << endl;
    }
    bool isEmpty = true;

while (getline(file, line)) {
    isEmpty = false;
    // existing code
}

if (isEmpty) {
    cout << "No Nurses found.\n";
}

    file.close();

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
void viewPatients() {
    ifstream file("data/patients.txt");

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    string line;

    cout << "\n===== PATIENTS LIST =====\n";

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, condition;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, condition, ',');

        cout << "ID: " << id
             << " | Name: " << name
             << " | Condition: " << condition << endl;
    }
    bool isEmpty = true;

while (getline(file, line)) {
    isEmpty = false;
    // existing code
}

if (isEmpty) {
    cout << "No patient found.\n";
}

    file.close();

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void servePatient() {
    if (patientQueue.empty()) {
        cout << "No patients in queue!\n";
        return;
    }

    Patient p = patientQueue.top();
    patientQueue.pop();

    cout << "\nServing Patient:\n";
    cout << "ID: " << p.id
         << " | Name: " << p.name
         << " | Condition: " << p.condition << endl;

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    
    cout << "Remaining Patients in Queue: " << patientQueue.size() << endl;
}
void loadDoctorsToQueue() {
    ifstream file("data/doctors.txt");

    if (!file) {
        cout << "Error opening doctors file!\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Doctor d;
        string temp;

        getline(ss, temp, ',');
        if (temp.empty()) continue;

        try {
            d.id = stoi(temp);
         } catch (...) {
    continue; // skip bad data
}

        getline(ss, d.name, ',');
        getline(ss, d.specialization, ',');
        getline(ss, temp, ',');
        d.available = stoi(temp);

        doctorQueue.push(d);
    }

    file.close();

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    
    int count = 0;

    // inside loop:
    count++;

    // after loop:
    cout << count << " doctors loaded into system.\n";
}
void assignDuty() {
    if (doctorQueue.empty()) {
        cout << "No doctors available!\n";
        return;
    }

    Doctor d = doctorQueue.front();
    doctorQueue.pop();

    cout << "\nDoctor on Duty:\n";
    cout << "ID: " << d.id
         << " | Name: " << d.name
         << " | Specialization: " << d.specialization << endl;

    // Rotate back to queue
    doctorQueue.push(d);

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ===== MENU =====

void showMenu() {
    cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====\n";
    cout << "1. Add Doctor\n";
    cout << "2. Add Nurse\n";
    cout << "3. Add Patient\n";
    cout << "4. View Doctors\n";
    cout << "5. View Nurses\n";
    cout << "6. View Patient\n";
    cout << "7. Serve Next Patient\n";
    cout << "8. Assign Doctor (Duty Roster)\n";
    cout << "9. Exist\n";
    cout << "Enter choice: ";
}

// ===== MAIN =====

int main() {
    int choice;
    loadDoctorsToQueue();

    while (true) {
        showMenu();
        cin >> choice;
        if (cin.fail()) {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid input! Enter number only.\n";
    continue;
}

        switch (choice) {

            case 1:
                addDoctor();
                break;

            case 2:
                addNurse();
                break;

            case 3:
                addPatient();
                break;

            case 4:
                viewDoctors();
                break;

            case 5:
                viewNurses();
                break;

            case 6:
                viewPatients();
                break;

            case 7:
	            servePatient(); 
	            break;
	        case 8:
			    assignDuty();
				break;
			case 9:
			    cout << "Existing...\n";
				break; 
            default:
                cout << "Invalid choice!\n";
        }
    }
    return 0;
}
