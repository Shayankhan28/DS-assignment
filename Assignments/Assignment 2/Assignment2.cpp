#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Patient ka structure define kiya gaya hai jisme uska naam, arrival order, condition aur priority hoti hai
struct Patient {
    string name;
    int arrivalOrder;
    string condition;
    int priority;

    // Constructor banaya gaya hai taake object create karte waqt values assign ho sakein
    Patient(string n, int order, string cond, int prio)
        : name(n), arrivalOrder(order), condition(cond), priority(prio) {}
};

// Priority queue ke liye custom comparator banaya gaya hai
struct ComparePatient {
    // Ye operator overload karta hai taake priority queue patients ko sahi tarah sort kare
    bool operator()(const Patient& p1, const Patient& p2) {
        // Pehle priority compare karte hain (choti number wali priority ka matlab zyada emergency)
        if (p1.priority != p2.priority) {
            return p1.priority > p2.priority;
        }
        // Agar priority same ho toh arrival order dekhte hain (jo pehle aaya usay pehle treat karna chahiye)
        return p1.arrivalOrder > p2.arrivalOrder;
    }
};

// Function jo current treatment order print karta hai
void printTreatmentOrder(priority_queue<Patient, vector<Patient>, ComparePatient> pq) {
    int position = 1;
    cout << "\nCurrent Treatment Order:\n";
    cout << "------------------------------------------------------------\n";
    cout << left << setw(10) << "Position" << setw(15) << "Patient Name"
         << setw(20) << "Condition" << setw(10) << "Priority"
         << setw(15) << "Arrival Order" << endl;
    cout << "------------------------------------------------------------\n";

    // Queue ke andar jitne patients hain un sab ko ek ek karke nikaalte hain aur print karte hain
    while (!pq.empty()) {
        Patient p = pq.top(); // Sabse pehle priority wala patient nikaal rahe hain
        cout << left << setw(10) << position++
             << setw(15) << p.name
             << setw(15) << p.arrivalOrder
             << setw(20) << p.condition
             << setw(10) << p.priority
             << endl;
        pq.pop(); // Current patient ko queue se hata dete hain
    }
    cout << "------------------------------------------------------------\n";
}

int main() {
    // Priority queue banayi gayi hai jisme patients treat honge unki priority ke hisaab se
    priority_queue<Patient, vector<Patient>, ComparePatient> treatmentQueue;
    int arrivalCounter = 1; // Ye har naye patient ka arrival order track karega

    cout << "=== Hospital Patient Treatment System ===\n";

    // Infinite loop chal raha hai jab tak user exit nahi karta
    while (true) {
        // Menu display kar rahe hain
        cout << "\nMenu:\n";
        cout << "1. Add Patient\n";
        cout << "2. View Current Treatment Order\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        // Agar user patient add karna chahta hai
        if (choice == 1) {
            string name, condition;
            int priority;

            // Patient ka naam aur condition pooch rahe hain
            cout << "\nEnter patient name: ";
            cin.ignore(); // Input buffer clear kar rahe hain taake getline sahi se kaam kare
            getline(cin, name);

            cout << "Enter emergency condition: ";
            getline(cin, condition);

            // Condition ke hisaab se priority set kar rahe hain
            if (condition == "Heart Attack" || condition == "Stroke") {
                priority = 1; // Sabse zyada emergency
            } else if (condition == "Broken Leg" || condition == "Severe Burn" || condition == "Fractured Arm") {
                priority = 2;
            } else if (condition == "Fever" || condition == "Food Poisoning" || condition == "Migraine") {
                priority = 3;
            } else {
                priority = 4; // Agar koi aur halka condition ho
            }

            // Naya patient queue mein add kar rahe hain
            treatmentQueue.push(Patient(name, arrivalCounter++, condition, priority));

            cout << "\nPatient added successfully!\n";
            // Current queue print karte hain
            printTreatmentOrder(treatmentQueue);

        } else if (choice == 2) {
            // Agar queue khali hai toh message dete hain
            if (treatmentQueue.empty()) {
                cout << "\nNo patients in the queue.\n";
            } else {
                // Agar patients hain toh unka treatment order dikhate hain
                printTreatmentOrder(treatmentQueue);
            }
        } else if (choice == 3) {
            // Program se exit karne ka option
            cout << "\nExiting system. Goodbye!\n";
            break;
        } else {
            // Galat input dene par message
            cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}
