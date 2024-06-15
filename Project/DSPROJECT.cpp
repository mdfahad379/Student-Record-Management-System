#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Student {
    int id;
    string name;
    float gpa;
    Student* next;

    Student(int id, const string& name, float gpa, Student* next = nullptr)
        : id(id), name(name), gpa(gpa), next(next) {}
};

class StudentRecord {
private:
    Student* head;
public:
    StudentRecord() : head(nullptr) {}

    void addStudent(int id, const string& name, float gpa) {
        Student* newStudent = new Student(id, name, gpa, head);
        head = newStudent;
        cout << "Student added: " << name << endl << endl;
    }

    void displayStudents() {
        Student* current = head;
        if (current == nullptr) {
            cout << "No student records available." << endl << endl;
            return;
        }
        while (current != nullptr) {
            cout << "ID: " << current->id << ", Name: " << current->name << ", GPA: " << current->gpa << endl << endl;
            current = current->next;
        }
    }

    void searchStudent(int id) {
        Student* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                cout << "Student found: " << endl;
                cout << "ID: " << current->id << ", Name: " << current->name << ", GPA: " << current->gpa << endl << endl;
                return;
            }
            current = current->next;
        }
        cout << "Student with ID " << id << " not found." << endl << endl;
    }

    void deleteStudent(int id) {
        Student* current = head;
        Student* prev = nullptr;

        while (current != nullptr && current->id != id) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Student with ID " << id << " not found." << endl << endl;
            return;
        }

        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        cout << "Student with ID " << id << " deleted." << endl << endl;
    }

    void updateStudent(int id, const string& name, float gpa) {
        Student* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                current->name = name;
                current->gpa = gpa;
                cout << "Student record updated." << endl << endl;
                return;
            }
            current = current->next;
        }
        cout << "Student with ID " << id << " not found." << endl << endl;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Unable to open file for writing." << endl << endl;
            return;
        }

        Student* current = head;
        while (current != nullptr) {
            file << current->id << '\n' << current->name << '\n' << current->gpa << '\n';
            current = current->next;
        }

        file.close();
        cout << "Records saved to " << filename << endl << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Unable to open file for reading." << endl << endl;
            return;
        }

        int id;
        string name;
        float gpa;
        while (file >> id) {
            file.ignore(); // Ignore the newline character after ID
            getline(file, name);
            file >> gpa;
            addStudent(id, name, gpa);
        }

        file.close();
        cout << "Records loaded from " << filename << endl << endl;
    }

    void calculateAverageGPA() {
        if (head == nullptr) {
            cout << "No student records available." << endl << endl;
            return;
        }

        Student* current = head;
        float totalGPA = 0;
        int count = 0;
        while (current != nullptr) {
            totalGPA += current->gpa;
            count++;
            current = current->next;
        }

        cout << "Average GPA: " << totalGPA / count << endl << endl;
    }
};

int main() {
    StudentRecord sr;
    int choice, id;
    string name;
    float gpa;
    string filename = "students.txt";

    do {
        cout << "\n--- Student Record Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Save Records\n";
        cout << "7. Load Records\n";
        cout << "8. Calculate Average GPA\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Student ID: ";
                cin >> id;
                cout << "Enter Student Name: ";
                cin.ignore(); // Ignore the newline character left by `cin`
                getline(cin, name);
                cout << "Enter Student GPA: ";
                cin >> gpa;
                sr.addStudent(id, name, gpa);
                break;
            case 2:
                sr.displayStudents();
                break;
            case 3:
                cout << "Enter Student ID to search: ";
                cin >> id;
                sr.searchStudent(id);
                break;
            case 4:
                cout << "Enter Student ID to delete: ";
                cin >> id;
                sr.deleteStudent(id);
                break;
            case 5:
                cout << "Enter Student ID to update: ";
                cin >> id;
                cout << "Enter new Student Name: ";
                cin.ignore(); // Ignore the newline character left by `cin`
                getline(cin, name);
                cout << "Enter new Student GPA: ";
                cin >> gpa;
                sr.updateStudent(id, name, gpa);
                break;
            case 6:
                sr.saveToFile(filename);
                break;
            case 7:
                sr.loadFromFile(filename);
                break;
            case 8:
                sr.calculateAverageGPA();
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
