#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class student {
private:
    int rollno;
    int age;
    string name;

public:
    student(int stdRollno, string stdName, int stdAge) {
        rollno = stdRollno;
        name = stdName;
        age = stdAge;
    }

    void setRollno(int stdRollno) {
        rollno = stdRollno;
    }

    int getRollno() const {
        return rollno;
    }

    void setName(string stdName) {
        name = stdName;
    }

    string getName() const {
        return name;
    }

    void setAge(int stdAge) {
        age = stdAge;
    }

    int getAge() const {
        return age;
    }
    void displayStudent() const {
        cout << "Roll no: " << rollno << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

void readStudentDataFromFile(vector<student>& students, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    int rollno, age;
    string name;

    while (inFile >> rollno >> name >> age) 
    {
        student newStudent(rollno, name, age);
        students.push_back(newStudent);
    }

    inFile.close();
}

void writeStudentDataToFile(const vector<student>& students, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }
  
    for (const auto& s : students) {
        outFile << s.getRollno() << " " << s.getName() << " " << s.getAge() << endl;
    }

    outFile.close();
}

void updateStudent(vector<student>& students) {
    string sname;
    bool found = false;
    int choice;
    cout << "\t Enter name to update Record :";
    cin.ignore();
    getline(cin, sname);
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getName() == sname) {
            found = true;
            cout << "\t--- student found----" << endl;
            cout << "\t 1.update Rollno" << endl;
            cout << "\t 2.update Name " << endl;
            cout << "\t 3.update age" << endl;
            cout << "Enter your choice :";
            cin >> choice;
            switch (choice) {
                case 1: {
                    int rno;
                    cout << "\t Enter new rollno :" << endl;
                    cin >> rno;
                    students[i].setRollno(rno);
                    break;
                }
                case 2: {
                    string name;
                    cout << "\t Enter new name :" << endl;
                    cin.ignore();
                    getline(cin, name);
                    students[i].setName(name);
                    break;
                }
                case 3: {
                    int age;
                    cout << "\t Enter new age :";
                    cin >> age;
                    students[i].setAge(age);
                    break;
                }
                default:
                    cout << "\t Invalid choice" << endl;
            }
        }
    }
    if (!found) {
        cout << "\t Record not found" << endl;
    }
}

void SearchStudent(vector<student>& students) {
    int rollno;
    cout << "Enter Roll no :";
    cin >> rollno;
    bool found = false;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getRollno() == rollno) {
            found = true;
            cout << "\t-------student found ------" << endl;
            students[i].displayStudent();
        }
    }
    if (!found) {
        cout << "\t Student not found" << endl;
    }
}

void DisplayAllStudent(vector<student>& students) {
    if (students.empty()) {
        cout << "\t No student found " << endl;
        return;
    }
    for (int i = 0; i < students.size(); i++) {
        students[i].displayStudent();
        cout << endl;
    }
}

void addNewStudent(vector<student>& students) {
    int age, rollno;
    string name;
    cout << "Enter ROLL no:";
    cin >> rollno;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getRollno() == rollno) {
            cout << "student already exists..." << endl;
            return;
        }
    }
    cout << "Enter Name:" << endl;
    cin >> name;
    cout << "Enter age:\n";
    cin >> age;
    student newstudent(rollno, name, age);
    students.push_back(newstudent);
    cout << "student added successfully..." << endl;
}

void deleteStudent(vector<student>& students) {
    string name;
    cout << "Enter name to delete :";
    cin.ignore();
    getline(cin, name);
    bool found = false;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getName() == name) {
            found = true;
            students.erase((students.begin() + i));
            cout << "\t Student removed successfully " << endl;
        }
    }
    if (!found) {
        cout << "\t Student not found" << endl;
    }
}



int main() {
    vector<student> students;

    readStudentDataFromFile(students, "student_data.txt");

   string choice;
    do {
        int op;
        cout << "\t\t---------------------------" << endl;
        cout << "\t\tStudent Management System" << endl;
        cout << "\t\t---------------------------" << endl;
        cout << "\t\t1. Add new student " << endl;
        cout << "\t\t2. Display All students " << endl;
        cout << "\t\t3. Search student" << endl;
        cout << "\t\t4. Update student" << endl;
        cout << "\t\t5. Delete student" << endl;
        cout << "\t\t6. Exit" << endl;
        cout << " Enter your choice: ";
        cin >> op;

        switch (op) {
            case 1:
                addNewStudent(students);
                writeStudentDataToFile(students, "student_data.txt");
                break;
            case 2:
                DisplayAllStudent(students);
                break;
            case 3:
                SearchStudent(students);
                break;
            case 4:
                updateStudent(students);
                writeStudentDataToFile(students, "student_data.txt");
                break;
            case 5:
                deleteStudent(students);
                writeStudentDataToFile(students, "student_data.txt");
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice" << endl;
        }

        cout << "If you want to continue press yes or YES: ";
        cin>>choice;
    } while (choice == "yes" || choice == "YES");

    return 0;
}