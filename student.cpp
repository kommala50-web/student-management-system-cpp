#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
    int id;
    char name[50];
    int age;
    char course[50];

public:
    void input() {
        cout << "Enter ID: ";
        cin >> id;

        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();
        cout << "Enter Course: ";
        cin.getline(course, 50);
    }

    void display() const {
        cout << "\nID: " << id
             << "\nName: " << name
             << "\nAge: " << age
             << "\nCourse: " << course
             << "\n-------------------------\n";
    }

    int getId() const {
        return id;
    }
};

// Check duplicate ID
bool isDuplicate(int id) {
    Student s;
    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getId() == id) {
            return true;
        }
    }
    return false;
}

// Add student
void addStudent() {
    Student s;

    cout << "\nEnter Student Details:\n";
    s.input();

    if (isDuplicate(s.getId())) {
        cout << "Error: ID already exists!\n";
        return;
    }

    ofstream file("students.dat", ios::binary | ios::app);
    file.write((char*)&s, sizeof(s));

    cout << "Student added successfully!\n";
}

// Display all
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "No records found.\n";
        return;
    }

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }
}

// Search student
void searchStudent() {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    Student s;
    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getId() == id) {
            cout << "\nStudent Found:\n";
            s.display();
            return;
        }
    }

    cout << "Student not found.\n";
}

// Update student
void updateStudent() {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;

    fstream file("students.dat", ios::binary | ios::in | ios::out);
    Student s;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getId() == id) {
            cout << "Enter new details:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "Record updated successfully!\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

// Delete student
void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    Student s;
    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getId() == id) {
            found = true;
            continue;
        }
        temp.write((char*)&s, sizeof(s));
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully!\n";
    else
        cout << "Student not found.\n";
}

// Menu
int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}