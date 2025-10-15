#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Структура для представлення студента
struct Student
{
    string name;
    vector<int> grades;
};

vector<Student> students_list;

// Розраховує середній бал студента
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

// Очікує на введення від користувача для продовження
void wait_for_user()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Додає нового студента до списку
void add_student()
{
    Student new_student;

    cout << "\n=========================================\n";
    cout << "                  Add New Student\n";
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

// Виводить таблицю з усіма студентами та їхніми оцінками
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
        cout.width(20);
        cout << left << student.name << " | ";
        cout.width(7);
        cout << left << calculate_average(student) << " | ";
        cout.width(3);
        cout << left << student.grades[0] << " | ";
        cout.width(3);
        cout << left << student.grades[1] << " | ";
        cout.width(3);
        cout << left << student.grades[2] << endl;
    }

    cout << "================================================\n";
}

// Виводить детальну інформацію про конкретного студента
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

            if (avg <= 50)
                category = "Bad student (1-50)";
            else if (avg < 70)
                category = "Normal student (51-69)";
            else if (avg < 88)
                category = "Stipend student (70-87)";
            else
                category = "Excellent student (88-100)";

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

// Розраховує та виводить середній бал по всій групі
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

// Універсальна функція для виводу групи студентів за діапазоном оцінок
void print_group_by_range(const string &title, int min_score, int max_score)
{
    if (students_list.empty())
    {
        cout << "\nStudent list is currently empty!\n";
        return;
    }

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

// --- НОВІ ФУНКЦІЇ ДЛЯ МЕНЮ ---
// Виводить студентів з низькими балами
void show_bad_students()
{
    print_group_by_range("Bad Students (1-50)", 1, 50);
}

// Виводить студентів, які отримують стипендію
void show_stipend_students()
{
    print_group_by_range("Stipend Students (70-100)", 70, 100);
}

// Виводить відмінників
void show_excellent_students()
{
    print_group_by_range("Excellent Students (88-100)", 88, 100);
}
// -----------------------------

// Виводить найкращого та найгіршого студента
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

// Змінює оцінку обраного студента
void change_student_grade()
{
    if (students_list.empty())
    {
        cout << "\nStudent list is currently empty! Cannot change grade.\n";
        return;
    }

    cout << "\n=========================================\n";
    cout << "              Change Student Grade\n";
    cout << "=========================================\n";

    string student_name;
    int student_index = -1;

    cin.ignore();
    while (student_index == -1)
    {
        cout << "Enter student name: ";
        getline(cin, student_name);

        for (int i = 0; i < students_list.size(); i++)
        {
            if (students_list[i].name == student_name)
            {
                student_index = i;
                break;
            }
        }
        if (student_index == -1)
        {
            cout << "Student with name '" << student_name << "' not found. Try again.\n";
        }
    }

    const Student &student = students_list[student_index];

    cout << endl
         << student.name << "'s grades:" << endl;
    for (int i = 0; i < student.grades.size(); i++)
    {
        cout << i + 1 << " - " << student.grades[i] << endl;
    }
    cout << endl;

    int grade_number;
    int new_grade;

    while (true)
    {
        cout << "Enter number of grade to change (1-" << student.grades.size() << "): ";
        if (!(cin >> grade_number) || grade_number < 1 || grade_number > student.grades.size())
        {
            cout << "Invalid input. Please enter a number from 1 to " << student.grades.size() << ".\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        cout << "Enter new grade (0-100): ";
        if (!(cin >> new_grade) || new_grade < 0 || new_grade > 100)
        {
            cout << "Invalid input. Please enter a number from 0 to 100.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            break;
        }
    }

    int old_grade = students_list[student_index].grades[grade_number - 1];
    students_list[student_index].grades[grade_number - 1] = new_grade;

    cout << endl
         << student.name << "'s grade #" << grade_number << " changed from " << old_grade << " to " << new_grade << endl;
    cout << "=========================================\n";
}

int main()
{
    while (true)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << endl
             << endl
             << R"(
          /$$$$$$   /$$                               /$$                                  /$$$$$$$  /$$$$$$$ 
         /$$__  $$ | $$                              | $$                                 | $$__  $$| $$__  $$
        | $$  \__/ /$$$$$$   /$$   /$$  /$$$$$$$   /$$$$$$   /$$$$$$$        | $$  \ $$| $$  \ $$
        |  $$$$$$ |_  $$_/  | $$  | $$ /$$__  $$ /$$__  $$| $$__  $$        | $$  | $$| $$$$$$$ 
         \____  $$ | $$    | $$  | $$| $$  | $$| $$$$$$$$| $$  \ $$        | $$  | $$| $$__  $$
         /$$  \ $$ | $$ /$$| $$  | $$| $$  | $$| $$_____/| $$  | $$        | $$  | $$| $$  \ $$
        |  $$$$$$/ |  $$$$/|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$  | $$        | $$$$$$$/| $$$$$$$/
         \______/   \___/   \______/  \_______/ \_______/|__/  |__/         \_______/ |_______/ 
         )"
             << endl
             << endl;

        string choice;

        cout << "\n=========== MENU ===========\n";
        cout << "1 - Add Student\n";
        cout << "2 - Show Grades Table\n";
        cout << "3 - Show Bad Students (1-50)\n";
        cout << "4 - Show Stipend Students (70+)\n";
        cout << "5 - Show Excellent Students (88+)\n";
        cout << "6 - Show Specific Student Grades\n";
        cout << "7 - Show Group Average Grade\n";
        cout << "8 - Show Best and Worst Student\n";
        cout << "9 - Change Student Grade\n";
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
            show_bad_students();
            wait_for_user();
        }
        else if (choice == "4")
        {
            show_stipend_students();
            wait_for_user();
        }
        else if (choice == "5")
        {
            show_excellent_students();
            wait_for_user();
        }
        else if (choice == "6")
        {
            print_particular_student_grades();
            wait_for_user();
        }
        else if (choice == "7")
        {
            get_average_of_group();
            wait_for_user();
        }
        else if (choice == "8")
        {
            print_best_and_worst_student();
            wait_for_user();
        }
        else if (choice == "9")
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