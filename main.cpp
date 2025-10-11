#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;


void add_student(vector<vector<string>> &students_table)
{
    string name;
    vector<string> info;
    string grade;

    cout << "\n=========================================\n";
    cout << "            Add New Student\n";
    cout << "=========================================\n";

    cout << "Enter student name: ";
    getline(cin, name);
    info.push_back(name);

    cout << "\n--- Enter 3 grades for " << name << " ---\n";

    for (int i = 0; i < 3; i++)
    {
        while (true)
        {
            cout << "Grade " << (i + 1) << ": ";
            getline(cin, grade);

            bool valid = (grade.size() > 0);
            for (int j = 0; j < (int)grade.size(); j++)
            {
                if (!isdigit(grade[j]))
                {
                    valid = false;
                    break;
                }
            }

            int num = 0;
            if (valid)
                num = stoi(grade);

            if (!valid || num < 0 || num > 100)
            {
                cout << "Please enter a valid grade (0-100).\n";
            }
            else
            {
                info.push_back(grade);
                break;
            }
        }
    }

    students_table.push_back(info);

    cout << "\nStudent '" << name << "' added successfully!\n";
    cout << "=========================================\n";
    cin.get();
}

void print_table_of_students(const vector<vector<string>> &students_table)
{
    if (students_table.empty())
    {
        cout << "\nNo students added yet!\n";
        cin.get();
        return;
    }

    cout << "\n===============================================================================================================\n";
    cout << "Name" << string(16, ' ') << "| Average Grade      | Grade 1            | Grade 2            | Grade 3            \n";
    cout << "\n---------------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < students_table.size(); i++)
    {
        string name = students_table[i][0];
        string g1 = students_table[i][1];
        string g2 = students_table[i][2];
        string g3 = students_table[i][3];

        float avg = (stoi(students_table[i][1]) + stoi(students_table[i][2]) + stoi(students_table[i][3])) / 3.0f;
        string avg_str = to_string(avg);

        cout << name << string(20 - name.size(), ' ') 
             << "| " << avg_str << string(19 - avg_str.size(), ' ') 
             << "| " << g1 << string(19 - g1.size(), ' ') 
             << "| " << g2 << string(19 - g2.size(), ' ') 
             << "| " << g3 << string(19 - g3.size(), ' ') 
             << endl;
    }

    cout << "===============================================================================================================\n";
    cin.get();
}

void print_students_by_category(const vector<vector<string>> &students_table)
{
    if (students_table.empty())
    {
        cout << "\nNo students added yet!\n";
        cin.get();
        return;
    }

    cout << "\n=============================================\n";
    cout << "Name" << string(16, ' ') << "| Category\n";
    cout << "---------------------------------------------\n";

    for (int i = 0; i < students_table.size(); i++)
    {
        string name = students_table[i][0];
        string category;
        
        float avg = (stoi(students_table[i][1]) \
                    + stoi(students_table[i][2]) \
                    + stoi(students_table[i][3])) 
                    / 3.0f;

        if (avg < 50) category = "Bad student";
        else if (avg < 80) category = "Medium student";
        else category = "Excellent student";

        cout << name << string(20 - name.size(), ' ') << "| " << category << endl;
    }

    cout << "=============================================\n";
    cin.get();
}

void print_particular_student_grades(string name, const vector<vector<string>> &students_table)
{
    for (int i = 0; i < (int)students_table.size(); i++)
    {
        if (students_table[i][0] == name)
        {
            float avg = (stoi(students_table[i][1]) + stoi(students_table[i][2]) + stoi(students_table[i][3])) / 3.0f;

            cout << "\n=============================================\n";
            cout << "             Student Information\n";
            cout << "=============================================\n";
            cout << "Name: " << name << "\n";
            cout << "---------------------------------------------\n";
            cout << "| Grade 1 | Grade 2 | Grade 3 |  Average    \n";
            cout << "---------------------------------------------\n";

            string g1 = students_table[i][1];
            string g2 = students_table[i][2];
            string g3 = students_table[i][3];

            cout << "|  " << g1 << string(7 - g1.size(), ' ')
                 << "|  " << g2 << string(7 - g2.size(), ' ')
                 << "|  " << g3 << string(7 - g3.size(), ' ')
                 << "|   " << avg
                 << endl;

            cout << "---------------------------------------------\n";
            cout << "Performance: ";

            if (avg < 50)
                cout << "Bad student";
            else if (avg < 80)
                cout << "Medium student";
            else
                cout << "Excellent student";

            cout << "\n=============================================\n";
            cin.get();
            return;
        }
    }

    cout << "\n   Student not found!\n";
    cin.get();
}

void get_medium_of_group(const vector<vector<string>> &students_table)
{
    double total_sum = 0;
    int grade_count = 0;

    for (const auto& student : students_table)
    {
        for (int i = 1; i < student.size(); i++) 
        {
            int grade = stoi(student[i]); 
            total_sum += grade;
            grade_count++;
        }
    }

    cout << "\n=============================================\n";
    cout << "           Group Average Grade\n";
    cout << "=============================================\n";

    if (grade_count > 0)
    {
        double average = total_sum / grade_count;
        cout << "Group Average: " << average << "\n";
    }
    else
    {
        cout << "No grades available to calculate average.\n";
    }

    cout << "=============================================\n";
    cin.get();
}

int main()
{
    vector<vector<string>> students_table;
    string choice;

    while (true)
    {
        system("cls");
        cout << "\n=========== MENU ===========\n";
        cout << "1 - Add student\n";
        cout << "2 - Show table of averages\n";
        cout << "3 - Show students by category\n";
        cout << "4 - Show grades of a student\n";
        cout << "5 - Show group average\n";
        cout << "0 - Exit\n";
        cout << "============================\n";
        cout << "Choose: ";
        getline(cin, choice);

        if (choice == "1")
        {
            add_student(students_table);
        }
        else if (choice == "2")
        {
            print_table_of_students(students_table);
        }
        else if (choice == "3")
        {
            print_students_by_category(students_table);
        }
        else if (choice == "4")
        {
            string name;
            cout << "Enter student name: ";
            getline(cin, name);
            print_particular_student_grades(name, students_table);
        }
        else if (choice == "5") {
            get_medium_of_group(students_table);
        }
        else if (choice == "0")
        {
            cout << "Exiting...\n";
            break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}