#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Each Request stores the information for one document request.
struct Request {
    int id;
    string studentID;
    string studentName;
    string documentType;
    string status;
};

vector<Request> requests;
int nextID = 1;

const string STUDENT_ID = "STU001";
const string STUDENT_PASSWORD = "1234";
const string STUDENT_NAME = "Sample Student";
const string STAFF_USERNAME = "admin";
const string STAFF_PASSWORD = "admin123";
const string DATA_FILE = "requests.txt";

int readNumber();
void loadRequests();
void saveRequests();
void studentMenu();
void staffMenu();
void requestDocument();
void trackRequests();
void viewHistory();
void viewAllRequests();
void reviewRequests();
void processRequests();
void completeRequests();

int main() {
    loadRequests();

    int choice;
    do {
        cout << "\n====================================\n";
        cout << "        STUDENT RECORDS SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Student Login\n";
        cout << "2. Office Staff Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        choice = readNumber();

        if (choice == 1) {
            string id, password;
            cout << "\nSTUDENT LOGIN\n";
            cout << "Student ID: ";
            getline(cin, id);
            cout << "Password: ";
            getline(cin, password);

            if (id == STUDENT_ID && password == STUDENT_PASSWORD) {
                cout << "\nLogin successful. Welcome, " << STUDENT_NAME << "!\n";
                studentMenu();
            } else {
                cout << "\nInvalid student ID or password.\n";
            }
        } else if (choice == 2) {
            string username, password;
            cout << "\nOFFICE STAFF LOGIN\n";
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);

            if (username == STAFF_USERNAME && password == STAFF_PASSWORD) {
                cout << "\nLogin successful. Welcome, Office Staff!\n";
                staffMenu();
            } else {
                cout << "\nInvalid username or password.\n";
            }
        } else if (choice == 3) {
            saveRequests();
            cout << "\nThank you for using the Student Records System!\n";
        } else {
            cout << "\nInvalid menu choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

// Reads a whole-number menu choice and rejects invalid input.
int readNumber() {
    string input;
    int number;
    char extra;

    while (true) {
        getline(cin, input);
        stringstream ss(input);

        if ((ss >> number) && !(ss >> extra)) {
            return number;
        }
        cout << "Please enter a valid whole number: ";
    }
}

// Student dashboard.
void studentMenu() {
    int choice;
    do {
        cout << "\n========== STUDENT DASHBOARD ==========\n";
        cout << "1. Request Document\n";
        cout << "2. Track Request Status\n";
        cout << "3. View Request History\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        choice = readNumber();

        switch (choice) {
            case 1: requestDocument(); break;
            case 2: trackRequests(); break;
            case 3: viewHistory(); break;
            case 4: cout << "\nYou have logged out.\n"; break;
            default: cout << "\nInvalid menu choice.\n";
        }
    } while (choice != 4);
}

// Creates a new request and gives it a unique ID.
void requestDocument() {
    Request newRequest;
    int choice;

    cout << "\n========== REQUEST DOCUMENT ==========\n";
    cout << "1. Certificate\n";
    cout << "2. Transcript of Records\n";
    cout << "3. Enrollment Document\n";
    cout << "Choose document type: ";
    choice = readNumber();

    if (choice == 1) {
        newRequest.documentType = "Certificate";
    } else if (choice == 2) {
        newRequest.documentType = "Transcript of Records";
    } else if (choice == 3) {
        newRequest.documentType = "Enrollment Document";
    } else {
        cout << "\nInvalid document type. No request was submitted.\n";
        return;
    }

    newRequest.id = nextID++;
    newRequest.studentID = STUDENT_ID;
    newRequest.studentName = STUDENT_NAME;
    newRequest.status = "Pending";

    requests.push_back(newRequest);
    saveRequests();

    cout << "\nRequest submitted successfully!\n";
    cout << "Your Request ID is: " << newRequest.id << "\n";
    cout << "Current status: Pending\n";
}

// Shows the current status of the sample student's requests.
void trackRequests() {
    cout << "\n========== TRACK REQUEST STATUS ==========\n";
    bool found = false;

    for (const Request &r : requests) {
        if (r.studentID == STUDENT_ID) {
            cout << "\nRequest ID: " << r.id
                 << "\nDocument: " << r.documentType
                 << "\nStatus: " << r.status << "\n";
            found = true;
        }
    }

    if (!found) cout << "\nYou have no requests yet.\n";
}

// Shows the student's request history.
void viewHistory() {
    cout << "\n========== REQUEST HISTORY ==========\n";
    bool found = false;

    for (const Request &r : requests) {
        if (r.studentID == STUDENT_ID) {
            cout << "\nRequest ID: " << r.id
                 << "\nStudent: " << r.studentName
                 << "\nDocument: " << r.documentType
                 << "\nStatus: " << r.status << "\n";
            found = true;
        }
    }

    if (!found) cout << "\nNo request history is available.\n";
}

// Staff dashboard.
void staffMenu() {
    int choice;
    do {
        cout << "\n========== OFFICE STAFF DASHBOARD ==========\n";
        cout << "1. View Submitted Requests\n";
        cout << "2. Review and Approve/Reject Requests\n";
        cout << "3. Process Approved Requests\n";
        cout << "4. Mark Documents as Completed\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
        choice = readNumber();

        switch (choice) {
            case 1: viewAllRequests(); break;
            case 2: reviewRequests(); break;
            case 3: processRequests(); break;
            case 4: completeRequests(); break;
            case 5: cout << "\nYou have logged out.\n"; break;
            default: cout << "\nInvalid menu choice.\n";
        }
    } while (choice != 5);
}

// Displays all requests for office staff.
void viewAllRequests() {
    cout << "\n========== ALL SUBMITTED REQUESTS ==========\n";

    if (requests.empty()) {
        cout << "\nThere are no submitted requests.\n";
        return;
    }

    for (const Request &r : requests) {
        cout << "\nRequest ID: " << r.id
             << "\nStudent ID: " << r.studentID
             << "\nStudent Name: " << r.studentName
             << "\nDocument: " << r.documentType
             << "\nStatus: " << r.status << "\n";
    }
}

// Staff reviews a pending request and approves or rejects it.
void reviewRequests() {
    viewAllRequests();
    if (requests.empty()) return;

    cout << "\nEnter the Request ID to review: ";
    int id = readNumber();
    bool found = false;

    for (Request &r : requests) {
        if (r.id == id && r.status == "Pending") {
            found = true;
            cout << "1. Approve\n2. Reject\nChoose action: ";
            int choice = readNumber();

            if (choice == 1) {
                r.status = "Processing";
                cout << "\nRequest approved. Status: Processing\n";
            } else if (choice == 2) {
                r.status = "Rejected";
                cout << "\nRequest rejected.\n";
            } else {
                cout << "\nInvalid action. The status was not changed.\n";
                return;
            }

            saveRequests();
            return;
        }
    }

    if (!found) cout << "\nRequest ID not found or request was already reviewed.\n";
}

// Staff marks an approved request as ready for pickup.
void processRequests() {
    cout << "\n========== PROCESS APPROVED REQUESTS ==========\n";
    bool found = false;

    for (const Request &r : requests) {
        if (r.status == "Processing") {
            cout << "\nRequest ID: " << r.id
                 << "\nDocument: " << r.documentType << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\nThere are no approved requests waiting to be processed.\n";
        return;
    }

    cout << "\nEnter the Request ID when the document is ready: ";
    int id = readNumber();

    for (Request &r : requests) {
        if (r.id == id && r.status == "Processing") {
            r.status = "Ready for Pickup";
            saveRequests();
            cout << "\nStatus updated to Ready for Pickup.\n";
            return;
        }
    }

    cout << "\nRequest ID not found in the Processing status.\n";
}

// Staff marks a request completed after the student collects the document.
void completeRequests() {
    cout << "\n========== COMPLETE REQUEST ==========\n";
    bool found = false;

    for (const Request &r : requests) {
        if (r.status == "Ready for Pickup") {
            cout << "\nRequest ID: " << r.id
                 << "\nDocument: " << r.documentType << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\nThere are no documents waiting for pickup.\n";
        return;
    }

    cout << "\nEnter the Request ID after the student has picked it up: ";
    int id = readNumber();

    for (Request &r : requests) {
        if (r.id == id && r.status == "Ready for Pickup") {
            r.status = "Completed";
            saveRequests();
            cout << "\nRequest status updated to Completed.\n";
            return;
        }
    }

    cout << "\nRequest ID not found or document is not ready for pickup.\n";
}

// Saves all requests to a local text file.
void saveRequests() {
    ofstream file(DATA_FILE.c_str());

    if (!file) {
        cout << "\nWarning: Unable to save requests to " << DATA_FILE << ".\n";
        return;
    }

    for (const Request &r : requests) {
        file << r.id << "|"
             << r.studentID << "|"
             << r.studentName << "|"
             << r.documentType << "|"
             << r.status << "\n";
    }
}

// Loads saved requests and sets the next available request ID.
void loadRequests() {
    ifstream file(DATA_FILE.c_str());
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Request r;
        string idText;

        if (!getline(ss, idText, '|') ||
            !getline(ss, r.studentID, '|') ||
            !getline(ss, r.studentName, '|') ||
            !getline(ss, r.documentType, '|') ||
            !getline(ss, r.status)) {
            continue;
        }

        stringstream idStream(idText);
        char extra;
        if (!(idStream >> r.id) || (idStream >> extra)) continue;

        requests.push_back(r);
        if (r.id >= nextID) nextID = r.id + 1;
    }
}
