#include <iostream>
#include <vector>

using namespace std;

void add_student(std::vector<vector<string>> &students_table)
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

void print_table_of_students()
{
    cout << "Table";
}

void print_students_by_category()
{
    cout << "Categories: \nNumber of bad students: \nNumber of medium students: \nNumber of good students: \n";
}

void get_medium_of_group()
{
    cout << "Medium: sum / cout of students";
}

void print_particular_student_grades()
{
    cout << "Andrew's grade: ";
}

int main()
{
    vector<vector<string>> students_table;

    cout << "Select operation:" << endl;
    cout << "1. Add student" << endl;

    add_student(students_table);
    
    for (int i = 0; i < students_table.size(); i++)
    {
        for (int j = 0; j < students_table[i].size(); j++)
        {
            cout << students_table[i][j] << endl;
        }
    }

    return 0;
}