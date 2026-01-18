#include "ConsoleView.h"

// ===== Приватные методы =====
int ConsoleView::inputInt(const string& prompt, int min, int max)
{
    int number;
    while (true)
    {
        cout << prompt;
        if (cin >> number)
        {
            if (number >= min && number <= max)
            {
                return number;
            }
            else
            {
                cout << "Число должно быть в диапазоне [" << min << ".." << max << "]\n";
            }
        }
        else
        {
            cout << "Некорректный ввод. Попробуйте снова.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string ConsoleView::inputString(const string& prompt)
{
    string s;
    cout << prompt;
    getline(cin >> ws, s); // ws убирает любые пробельные символы и \n

    while (s.empty())
    {
        cout << "Строка не может быть пустой. Повторите ввод: ";
        getline(cin >> ws, s);
    }
    return s;
}

// ===== Главное меню =====
void ConsoleView::showMainMenu()
{
    cout << "\n===== Главное меню =====\n";
    cout << "1. Добавить студента\n";
    cout << "2. Удалить студента\n";
    cout << "3. Изменить данные студента\n";
    cout << "4. Показать всех студентов\n";
    cout << "5. Поиск студента по фамилии\n";
    cout << "6. Фильтр по группе\n";
    cout << "7. Сортировка\n";
    cout << "0. Выход\n";
}

int ConsoleView::getMainMenuChoice()
{
    return inputInt("Выберите пункт меню: ", MIN_MENU_OPTION, MAX_MENU_OPTION);
}

// ===== Меню редактирования студента =====
void ConsoleView::showStudentEditMenu()
{
    cout << "\n=== Меню редактирования студента ===\n";
    cout << "1. Изменить фамилию\n";
    cout << "2. Изменить имя\n";
    cout << "3. Изменить номер группы\n";
    cout << "4. Заменить вектор оценок\n";
    cout << "5. Очистить вектор оценок\n";
    cout << "6. Добавить новую оценку\n";
    cout << "0. Назад\n";
}

int ConsoleView::getStudentEditChoice()
{
    return inputInt("Выберите действие: ", MIN_MENU_OPTION, MAX_EDIT_CHOICE);
}

// ===== Меню сортировки =====
void ConsoleView::showSortMenu()
{
    cout << "\n=== Меню сортировки ===\n";
    cout << "1. По фамилии (алфавит)\n";
    cout << "2. По среднему баллу\n";
    cout << "0. Назад\n";
}

int ConsoleView::getSortChoice()
{
    return inputInt("Выберите сортировку: ", MIN_MENU_OPTION, MAX_SORT_CHOICE);
}

// ===== Ввод данных =====
StudentInputData ConsoleView::inputStudentData()
{
    StudentInputData data;
    data.surname = inputString("Фамилия: ");
    data.name = inputString("Имя: ");
    data.groupNumber = inputString("Номер группы: ");

    int count = inputInt("Введите количество оценок: ", 0, MAX_GRADES_COUNT);
    for (int i = 0; i < count; i++)
    {
        int grade = inputInt("Введите оценку: ", MIN_GRADE, MAX_GRADE);
        data.grades.push_back(grade);
    }
    return data;
}

string ConsoleView::inputSurname()
{
    return inputString("Введите фамилию: ");
}

string ConsoleView::inputName()
{
    return inputString("Введите имя: ");
}

string ConsoleView::inputGroupNumber()
{
    return inputString("Введите номер группы: ");
}

vector<int> ConsoleView::inputGrades()
{
    vector<int> grades;
    int count = inputInt("Введите количество оценок: ", 0, MAX_GRADES_COUNT);
    for (int i = 0; i < count; i++)
    {
        int grade = inputInt("Введите оценку: ", MIN_GRADE, MAX_GRADE);
        grades.push_back(grade);
    }
    return grades;
}

int ConsoleView::inputSingleGrade()
{
    return inputInt("Введите оценку: ", MIN_GRADE, MAX_GRADE);
}

// ===== Выбор студента =====
size_t ConsoleView::inputStudentIndex(size_t maxIndex)
{
    return inputInt("Введите индекс студента (1.." + to_string(maxIndex) + "): ", MIN_STUDENT_INDEX, maxIndex);
}

string ConsoleView::inputSearchSurname()
{
    return inputString("Введите фамилию для поиска: ");
}

string ConsoleView::inputFilterGroup()
{
    return inputString("Введите номер группы для фильтрации: ");
}

// ===== Вывод =====
void ConsoleView::showMessage(const string& message)
{
    cout << message << endl;
}

void ConsoleView::showStudent(const string& studentInfo)
{
    cout << studentInfo << endl;
}

void ConsoleView::showStudents(const vector<string>& studentsInfo)
{
    if (studentsInfo.empty())
    {
        cout << "Список студентов пуст." << endl;
        return;
    }

    for (int i = 0; i < studentsInfo.size(); ++i)
    {
        cout << i+1 << ". " << studentsInfo.at(i) << endl;
    }
}

