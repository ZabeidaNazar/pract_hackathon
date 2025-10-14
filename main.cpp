#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student
{
    string name;
    vector<int> grades;
};

vector<Student> students_list;

double calculate_average(const Student &student)
{
    if (student.grades.empty())
    {
        return 0.0;
    }

    int sum = 0;
    for (int grade : student.grades)
    {
        sum += grade;
    }

    return (double)sum / student.grades.size();
}

void wait_for_user()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void add_student()
{
    Student new_student;

    cout << "\n=========================================\n";
    cout << "                         Add New Student\n";
    cout << "=========================================\n";

    cin.ignore();

    cout << "Enter student name: ";
    getline(cin, new_student.name);

    cout << "\n--- Enter 3 grades (0-100) for " << new_student.name << " ---\n";

    for (int i = 0; i < 3; i++)
    {
        int grade_num;
        while (true)
        {
            cout << "Grade " << (i + 1) << ": ";
            if (!(cin >> grade_num))
            {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else if (grade_num < 0 || grade_num > 100)
            {
                cout << "Please enter a valid grade (0-100).\n";
            }
            else
            {
                new_student.grades.push_back(grade_num);
                break;
            }
        }
    }

    students_list.push_back(new_student);

    cout << "\nStudent '" << new_student.name << "' successfully added!\n";
    cout << "=========================================\n";
}

void print_table_of_students()
{
    if (students_list.empty())
    {
        cout << "\nStudent list is currently empty!\n";
        return;
    }

    cout << "\n================================================\n";
    cout << "Name                 | Avg. Gr | G.1 | G.2 | G.3\n";
    cout << "------------------------------------------------\n";

    for (const Student &student : students_list)
    {
        cout << student.name << "\t\t| "
             << calculate_average(student) << "\t | "
             << student.grades[0] << " | "
             << student.grades[1] << " | "
             << student.grades[2] << endl;
    }

    cout << "================================================\n";
}

void print_particular_student_grades()
{
    string name;

    cout << "Enter student name to search: ";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (const Student &student : students_list)
    {
        if (student.name == name)
        {
            double avg = calculate_average(student);
            string category;

            if (avg < 51)
                category = "Unsatisfactory (1-50)";
            else if (avg <= 80)
                category = "Good (51-80)";
            else
                category = "Excellent (81-100)";

            cout << "\n--- Student Information ---\n";
            cout << "Name: " << student.name << "\n";
            cout << "Grades: " << student.grades[0] << ", " << student.grades[1] << ", " << student.grades[2] << "\n";
            cout << "Average Grade: " << avg << "\n";
            cout << "Category: " << category << endl;
            cout << "---------------------------------\n";
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nStudent not found!\n";
    }
}

void get_average_of_group()
{
    if (students_list.empty())
    {
        cout << "\nNo grades to calculate group average.\n";
        return;
    }

    double total_sum = 0;
    int grade_count = 0;

    for (const Student &student : students_list)
    {
        for (int grade : student.grades)
        {
            total_sum += grade;
            grade_count++;
        }
    }

    double group_avg = total_sum / grade_count;

    cout << "\n=============================================\n";
    cout << "                 Group Average Grade\n";
    cout << "=============================================\n";
    cout << "Average Grade: " << group_avg << "\n";
    cout << "=============================================\n";
}

void print_group_by_range(const string &title, int min_score, int max_score)
{
    vector<Student> group;

    for (const Student &student : students_list)
    {
        double avg = calculate_average(student);
        if (avg >= min_score && avg <= max_score)
        {
            group.push_back(student);
        }
    }

    cout << "\n----- Group: " << title << " -----\n";
    if (group.empty())
    {
        cout << "No students in this category.\n";
    }
    else
    {
        for (const Student &student : group)
        {
            cout << student.name << " (Average: " << calculate_average(student) << ")\n";
        }
        cout << "----------------------------------------\n";
        cout << "Total: " << group.size() << " students.\n";
    }
}

void print_all_categories()
{
    if (students_list.empty())
    {
        cout << "\nStudent list is currently empty!\n";
        return;
    }

    cout << "\n========== RESULTS BY ALL GROUPS ==========\n";
    print_group_by_range("Unsatisfactory (1-50)", 1, 50);
    print_group_by_range("Good (51-80)", 51, 80);
    print_group_by_range("Excellent (81-100)", 81, 100);
}

void print_best_and_worst_student()
{
    cout << "\n========== BEST AND WORST STUDENT ==========\n";
    if (students_list.empty())
    {
        cout << "Student list is empty.\n";
        return;
    }

    size_t best_student_index = 0;
    size_t worst_student_index = 0;
    double max_avg = calculate_average(students_list[0]);
    double min_avg = calculate_average(students_list[0]);

    for (size_t i = 1; i < students_list.size(); ++i)
    {
        double current_avg = calculate_average(students_list[i]);

        if (current_avg > max_avg)
        {
            max_avg = current_avg;
            best_student_index = i;
        }
        if (current_avg < min_avg)
        {
            min_avg = current_avg;
            worst_student_index = i;
        }
    }

    cout << "\nBest student:\n";
    cout << students_list[best_student_index].name << " (Average Grade: " << max_avg << ")\n";

    cout << "\nWorst student:\n";
    cout << students_list[worst_student_index].name << " (Average Grade: " << min_avg << ")\n";
}

void show_category_menu()
{
    if (students_list.empty())
    {
        cout << "\nStudent list is currently empty! Cannot display categories.\n";
        return;
    }

    string category_choice;

    cout << "\n--- Select Category to View ---\n";
    cout << "1 - Excellent (81-100)\n";
    cout << "2 - Good (51-80)\n";
    cout << "3 - Unsatisfactory (1-50)\n";
    cout << "4 - Show All Categories\n";
    cout << "0 - Back to Main Menu\n";
    cout << "Select option: ";

    if (!(cin >> category_choice))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (category_choice == "1")
    {
        print_group_by_range("Excellent (81-100)", 81, 100);
    }
    else if (category_choice == "2")
    {
        print_group_by_range("Good (51-80)", 51, 80);
    }
    else if (category_choice == "3")
    {
        print_group_by_range("Unsatisfactory (1-50)", 1, 50);
    }
    else if (category_choice == "4")
    {
        print_all_categories();
    }
    else if (category_choice == "0")
    {
        cout << "Returning to main menu...\n";
    }
    else
    {
        cout << "Invalid choice!\n";
    }
}

void change_student_grade()
{
    if (students_list.empty())
    {
        cout << "\nStudent list is currently empty! Cannot change grade.\n";
        return;
    }

    cout << "\n=========================================\n";
    cout << "            Change Student Grade\n";
    cout << "=========================================\n";

    Student student;
    string user_input;
    int student_number = -1;

    cin.ignore();
    bool validInput = false;
    while (!validInput)
    {
        cout << "Enter student name: ";
        getline(cin, user_input);

        if (!user_input.length())
        {
            continue;
        }

        bool found_student = false;
        for (int i = 0; i < students_list.size(); i++)
        {
            if (students_list[i].name == user_input)
            {
                student = students_list[i];
                student_number = i;
                validInput = true;
                found_student = true;
                break;
            }
        }

        if (!found_student)
        {
            cout << "Student with name '" << user_input << "' not found." << endl;
        }
    }

    cout << endl
         << student.name << "'s grades:" << endl;
    for (size_t i = 0; i < student.grades.size(); i++)
    {
        cout << i + 1 << " - " << student.grades[i] << endl;
    }
    cout << endl;

    int grade_number;
    int new_grade;

    while (true)
    {
        cout << "Enter number of grade to change: ";
        cin >> grade_number;

        if (cin.fail())
        {
            cin.clear();
            getline(cin, user_input);
            cout << "It must be number, not '" << user_input << "'" << endl;
            continue;
        }

        if (grade_number >= 1 && grade_number <= student.grades.size())
        {
            break;
        }
        else
        {
            cout << "Grade number must be in range 1 - " << student.grades.size() << endl;
        }
    }

    while (true)
    {
        cout << "Enter new grade: ";
        cin >> new_grade;

        if (cin.fail())
        {
            cin.clear();
            getline(cin, user_input);
            cout << "It must be number, not '" << user_input << "'" << endl;
            continue;
        }

        if (new_grade >= 0 && new_grade <= 100)
        {
            break;
        }
        else
        {
            cout << "Grade must be in range 0 - 100" << endl;
        }
    }

    int old_grade = students_list[student_number].grades[grade_number - 1];
    students_list[student_number].grades[grade_number - 1] = new_grade;

    cout << endl
         << students_list[student_number].name << "'s grade changed from " << old_grade << " to " << new_grade << endl;
    cout << "=========================================\n";
}

int main()
{
    cout << endl
         << endl
         << R"(
      /$$$$$$  /$$                     /$$                        /$$                     /$$$$$$$  /$$$$$$$ 
     /$$__  $$| $$                    | $$                       | $$                    | $$__  $$| $$__  $$
    | $$  \__//$$$$$$   /$$   /$$ /$$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$$       | $$  \ $$| $$  \ $$
    |  $$$$$$|_  $$_/  | $$  | $$ /$$__  $$ /$$__  $$| $$__  $$|_  $$_/  /$$_____/       | $$  | $$| $$$$$$$ 
     \____  $$ | $$    | $$  | $$| $$  | $$| $$$$$$$$| $$  \ $$  | $$   |  $$$$$$        | $$  | $$| $$__  $$
     /$$  \ $$ | $$ /$$| $$  | $$| $$  | $$| $$_____/| $$  | $$  | $$ /$$\____  $$       | $$  | $$| $$  \ $$
    |  $$$$$$/ |  $$$$/|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$  | $$  |  $$$$//$$$$$$$/       | $$$$$$$/| $$$$$$$/
     \______/   \___/   \______/  \_______/ \_______/|__/  |__/   \___/ |_______/        |_______/ |_______/ 
    )" << endl
         << endl;

    string choice;

    while (true)
    {
        cout << "\n=========== MENU ===========\n";
        cout << "1 - Add Student\n";
        cout << "2 - Show Grades Table\n";
        cout << "3 - Show Students by Categories\n";
        cout << "4 - Show Specific Student Grades\n";
        cout << "5 - Show Group Average Grade\n";
        cout << "6 - Show Best and Worst Student\n";
        cout << "7 - Change Student Grade\n";
        cout << "0 - Exit\n";
        cout << "============================\n";
        cout << "Select option: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == "1")
        {
            add_student();
            wait_for_user();
        }
        else if (choice == "2")
        {
            print_table_of_students();
            wait_for_user();
        }
        else if (choice == "3")
        {
            show_category_menu();
            wait_for_user();
        }
        else if (choice == "4")
        {
            print_particular_student_grades();
            wait_for_user();
        }
        else if (choice == "5")
        {
            get_average_of_group();
            wait_for_user();
        }
        else if (choice == "6")
        {
            print_best_and_worst_student();
            wait_for_user();
        }
        else if (choice == "7")
        {
            change_student_grade();
            wait_for_user();
        }
        else if (choice == "0")
        {
            cout << "Exiting program...\n";
            break;
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
            wait_for_user();
        }
    }

    return 0;
}
