#include <iostream>
#include <vector>

using namespace std;

void add_student(vector<vector<string>> &students_table)
{
    string student_name;
    vector<string> student_info;

    cout << "Enter student name: ";
    cin >> student_name;
    
    student_info.push_back(student_name);

    for (int i = 0; i < 3; i++)
    {
        string student_grade;
        cout << "Enter student grade: ";
        cin >> student_grade;
        student_info.push_back(student_grade);
    }

    students_table.push_back(student_info);

}

void print_table_of_students(const vector<vector<string>> &students_table)
{
    cout << "\n----------------------------\n";
    cout << "Name         | Average Grade\n";
    cout << "----------------------------\n";

    for (auto student : students_table)
    {
        string name = student[0];
        double sum = 0;
        for (int i = 1; i < student.size(); i++)
        {
            sum += stoi(student[i]); // перетворюємо оцінку з string у int
        }
        double average = sum / (student.size() - 1);

        cout << name << string(13 - name.size(), ' ') << "| " << average << endl;
    }

    cout << "----------------------------\n";
}

void print_students_by_category()
{
    cout << "Categories: \nNumber of bad students: \nNumber of medium students: \nNumber of good students: \n";
}

void get_medium_of_group()
{
    cout << "Medium: sum / cout of students";
}

int print_particular_student_grades(string student_name, vector<vector<string>> &students_table)
{
    for (int i = 0; i < students_table.size(); i++)
    {
        if (students_table[i][0] == student_name)
        {
            float student_medium_grade = (float) (stoi(students_table[i][1]) + stoi(students_table[i][2]) + stoi(students_table[i][3])) / 3;

            cout << student_name << "'s grades: " << students_table[i][1] << " " << students_table[i][2] << " " << students_table[i][3] << endl;
            cout << student_name << "'s medium grade: " << student_medium_grade;
            
            return 0;
        }
    }

    cout << "Student not found!" << endl;
    return 1;
}

int main()
{
    vector<vector<string>> students_table;
    int choice;

    while (true)
    {
        cout << "\n1 - Add student\n2 - Show table\n0 - Exit\nChoose: ";
        cin >> choice;

        if (choice == 1)
            add_student(students_table);
        else if (choice == 2)
            print_table_of_students(students_table);
        else if (choice == 0)
            break;
        else
            cout << "Invalid choice!\n";
    }

    return 0;
}
