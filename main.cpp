#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <iomanip>
#include <limits>
#include <cstdlib>

using namespace std;

struct Student
{
    string name;
    vector<int> grades;
};

vector<Student> students_list;

void press_enter_to_continue()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double calculate_average(const Student &student)
{
    if (student.grades.empty())
    {
        return 0.0;
    }
    double sum = accumulate(student.grades.begin(), student.grades.end(), 0.0);
    return sum / student.grades.size();
}

void add_student()
{
    Student new_student;
    string grade_str;

    cout << "\n=========================================\n";
    cout << "             Add New Student\n";
    cout << "=========================================\n";

    cout << "Enter student name: ";
    getline(cin, new_student.name);

    cout << "\n--- Enter 3 grades for " << new_student.name << " ---\n";

    for (int i = 0; i < 3; i++)
    {
        while (true)
        {
            cout << "Grade " << (i + 1) << ": ";
            getline(cin, grade_str);

            try
            {
                int grade_num = stoi(grade_str);
                if (grade_num < 0 || grade_num > 100)
                {
                    cout << "Please enter a valid grade (0-100).\n";
                }
                else
                {
                    new_student.grades.push_back(grade_num);
                    break;
                }
            }
            catch (const invalid_argument &e)
            {
                cout << "Invalid input. Please enter a number.\n";
            }
        }
    }

    students_list.push_back(new_student);

    cout << "\nStudent '" << new_student.name << "' added successfully!\n";
    cout << "=========================================\n";
}

void print_table_of_students()
{
    if (students_list.empty())
    {
        cout << "\nNo students have been added yet!\n";
        return;
    }

    cout << "\n=======================================================================================\n";
    cout << left << setw(20) << "Name"
         << "| " << setw(18) << "Average Grade"
         << "| " << setw(18) << "Grade 1"
         << "| " << setw(18) << "Grade 2"
         << "| " << setw(18) << "Grade 3" << endl;
    cout << "---------------------------------------------------------------------------------------\n";

    cout << fixed << setprecision(2);

    for (const auto &student : students_list)
    {
        cout << left << setw(20) << student.name
             << "| " << setw(18) << calculate_average(student)
             << "| " << setw(18) << student.grades[0]
             << "| " << setw(18) << student.grades[1]
             << "| " << setw(18) << student.grades[2]
             << endl;
    }

    cout << "=======================================================================================\n";
}

void print_particular_student_grades()
{
    string name;
    cout << "Enter the name of the student to search for: ";
    getline(cin, name);

    bool found = false;
    for (const auto &student : students_list)
    {
        if (student.name == name)
        {
            double avg = calculate_average(student);
            string category;
            if (avg < 51)
                category = "Unsatisfactory";
            else if (avg < 81)
                category = "Good";
            else
                category = "Excellent";

            cout << "\n=============================================\n";
            cout << "            Student Information\n";
            cout << "=============================================\n";
            cout << "Name: " << student.name << "\n";
            cout << "---------------------------------------------\n";
            cout << "| Grade 1  | Grade 2  | Grade 3  | Average\n";
            cout << "---------------------------------------------\n";
            cout << "| " << setw(8) << student.grades[0]
                 << "| " << setw(8) << student.grades[1]
                 << "| " << setw(8) << student.grades[2]
                 << "| " << fixed << setprecision(2) << avg << endl;
            cout << "---------------------------------------------\n";
            cout << "Category: " << category << endl;
            cout << "=============================================\n";
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n   Student not found!\n";
    }
}

void get_average_of_group()
{
    if (students_list.empty())
    {
        cout << "\nNo grades are available to calculate the group average.\n";
        return;
    }

    double total_sum = 0;
    int grade_count = 0;

    for (const auto &student : students_list)
    {
        for (int grade : student.grades)
        {
            total_sum += grade;
            grade_count++;
        }
    }

    cout << "\n=============================================\n";
    cout << "            Group Average Grade\n";
    cout << "=============================================\n";
    cout << "Group Average: " << fixed << setprecision(2) << (total_sum / grade_count) << "\n";
    cout << "=============================================\n";
}

void print_low_achievers()
{
    vector<Student> group_low;
    for (const auto &student : students_list)
    {
        double avg = calculate_average(student);
        if (avg >= 1 && avg <= 50)
        {
            group_low.push_back(student);
        }
    }

    cout << "\n----- Group (Score 1-50) -----\n";
    if (group_low.empty())
    {
        cout << "There are no students in this category.\n";
    }
    else
    {
        for (const auto &student : group_low)
        {
            cout << left << setw(20) << student.name
                 << "Average Score: " << fixed << setprecision(2) << calculate_average(student) << endl;
        }
        cout << "----------------------------------------\n";
        cout << "Total students in this category: " << group_low.size() << endl;
    }
}

void print_medium_achievers()
{
    vector<Student> group_medium;
    for (const auto &student : students_list)
    {
        double avg = calculate_average(student);
        if (avg > 50 && avg <= 80)
        {
            group_medium.push_back(student);
        }
    }

    cout << "\n----- Group (Score 51-80) -----\n";
    if (group_medium.empty())
    {
        cout << "There are no students in this category.\n";
    }
    else
    {
        for (const auto &student : group_medium)
        {
            cout << left << setw(20) << student.name
                 << "Average Score: " << fixed << setprecision(2) << calculate_average(student) << endl;
        }
        cout << "----------------------------------------\n";
        cout << "Total students in this category: " << group_medium.size() << endl;
    }
}

void print_high_achievers()
{
    vector<Student> group_high;
    for (const auto &student : students_list)
    {
        double avg = calculate_average(student);
        if (avg > 80 && avg <= 100)
        {
            group_high.push_back(student);
        }
    }

    cout << "\n----- Group (Score 81-100) -----\n";
    if (group_high.empty())
    {
        cout << "There are no students in this category.\n";
    }
    else
    {
        for (const auto &student : group_high)
        {
            cout << left << setw(20) << student.name
                 << "Average Score: " << fixed << setprecision(2) << calculate_average(student) << endl;
        }
        cout << "----------------------------------------\n";
        cout << "Total students in this category: " << group_high.size() << endl;
    }
}

void print_all_categories()
{
    if (students_list.empty())
    {
        cout << "\nNo students have been added yet!\n";
        return;
    }
    cout << "\n========== RESULTS ACROSS ALL GROUPS ==========\n";
    print_low_achievers();
    print_medium_achievers();
    print_high_achievers();
}

void print_best_and_worst_student()
{
    cout << "\n========== BEST AND WORST STUDENTS ==========\n";
    if (students_list.empty())
    {
        cout << "The student list is empty.\n";
        return;
    }

    const Student *best_student = &students_list[0];
    const Student *worst_student = &students_list[0];
    double max_avg = calculate_average(*best_student);
    double min_avg = calculate_average(*worst_student);

    for (size_t i = 1; i < students_list.size(); ++i)
    {
        const auto &student = students_list[i];
        double current_avg = calculate_average(student);
        if (current_avg > max_avg)
        {
            max_avg = current_avg;
            best_student = &student;
        }
        if (current_avg < min_avg)
        {
            min_avg = current_avg;
            worst_student = &student;
        }
    }

    cout << "\nBest Student:\n";
    cout << left << setw(20) << best_student->name
         << "Average Score: " << fixed << setprecision(2) << max_avg << endl;

    cout << "\nWorst Student:\n";
    cout << left << setw(20) << worst_student->name
         << "Average Score: " << fixed << setprecision(2) << min_avg << endl;
}

int main()
{
    string choice;

    while (true)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        cout << "\n=========== MENU ===========\n";
        cout << "1 - Add Student\n";
        cout << "2 - Show Grade Table\n";
        cout << "3 - Show Students by Category\n";
        cout << "4 - Show a Specific Student's Grades\n";
        cout << "5 - Show Group Average\n";
        cout << "6 - Show Best and Worst Student\n";
        cout << "0 - Exit\n";
        cout << "============================\n";
        cout << "Choose an option: ";
        getline(cin, choice);

        if (choice == "1")
        {
            add_student();
            press_enter_to_continue();
        }
        else if (choice == "2")
        {
            print_table_of_students();
            press_enter_to_continue();
        }
        else if (choice == "3")
        {
            print_all_categories();
            press_enter_to_continue();
        }
        else if (choice == "4")
        {
            print_particular_student_grades();
            press_enter_to_continue();
        }
        else if (choice == "5")
        {
            get_average_of_group();
            press_enter_to_continue();
        }
        else if (choice == "6")
        {
            print_best_and_worst_student();
            press_enter_to_continue();
        }
        else if (choice == "0")
        {
            cout << "Exiting...\n";
            break;
        }
        else
        {
            cout << "Invalid choice! Please try again.\n";
            press_enter_to_continue();
        }
    }

    return 0;
}