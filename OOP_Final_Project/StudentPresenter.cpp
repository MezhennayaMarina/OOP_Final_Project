#include "StudentPresenter.h"

// ===== Конструктор =====
StudentPresenter::StudentPresenter(
    StudentManager& manager,
    ConsoleView& view,
    StudentFileHandler& fileHandler
)
    : manager(manager), view(view), fileHandler(fileHandler)
{
}

// ===== Основной цикл =====
void StudentPresenter::run()
{
    loadFromFile();

    bool running = true;
    while (running)
    {
        view.showMainMenu();
        int choice = view.getMainMenuChoice();

        switch (choice)
        {
        case 1: addStudent(); break;
        case 2: removeStudent(); break;
        case 3: editStudent(); break;
        case 4: showAllStudents(); break;
        case 5: searchBySurname(); break;
        case 6: filterByGroup(); break;
        case 7: sortStudents(); break;
        case 0:
            saveToFile();
            running = false; 
            break;
        default:
            view.showMessage("Некорректный пункт меню.");
        }
    }
}

// ===== Работа с файлом =====
void StudentPresenter::loadFromFile()
{
    vector<Student> students = fileHandler.load();
    manager.setStudents(students);
}

void StudentPresenter::saveToFile()
{
    fileHandler.save(manager.getAllStudents());
}

// ===== Форматирование студента =====
string StudentPresenter::formatStudent(const Student& s) 
{
    return
        s.getSurname() + " " +
        s.getName() +
        " | Группа: " + s.getGroupNumber() +
        " | Средний балл: " + to_string(s.calculateAverageGrade());
}

// ===== Добавление =====
void StudentPresenter::addStudent()
{
    StudentInputData data = view.inputStudentData();

    if (StudentValidator::isValidName(data.name) &&
        StudentValidator::isValidSurname(data.surname) &&
        StudentValidator::isValidGroupNumber(data.groupNumber) &&
        StudentValidator::areValidGrades(data.grades))
    {
        Student s(data.surname, data.name, data.groupNumber, data.grades);
        manager.addStudent(s);
        view.showMessage("Студент добавлен.");
    }
    else
    {
        view.showMessage("Ошибка: введены некорректные данные.");
    }
}

// ===== Удаление =====
void StudentPresenter::removeStudent()
{
    size_t count = manager.getStudentsCount();
    if (count == 0)
    {
        view.showMessage("Список студентов пуст.");
        return;
    }

    showAllStudents();
    size_t index = view.inputStudentIndex(count);
    index--; // перевод в 0-based

    if (manager.removeStudent(index))
        view.showMessage("Студент удалён.");
    else
        view.showMessage("Ошибка удаления студента.");
}

// ===== Редактирование =====
void StudentPresenter::editStudent()
{
    size_t count = manager.getStudentsCount();
    if (count == 0)
    {
        view.showMessage("Список студентов пуст.");
        return;
    }

    showAllStudents();
    size_t index = view.inputStudentIndex(count);
    index--; // перевод в 0-based

    editStudentField(index);
}

void StudentPresenter::editStudentField(int index)
{
    bool editing = true;

    while (editing)
    {
        view.showStudentEditMenu();
        int choice = view.getStudentEditChoice();

        Student s = manager.getStudent(index); // работа с копией

        switch (choice)
        {
        case 1:
        {
            string surname = view.inputSurname();
            if (StudentValidator::isValidSurname(surname))
            {
                s.setSurname(surname);
                manager.updateStudent(index, s);
                view.showMessage("Фамилия изменена.");
            }
            else view.showMessage("Некорректная фамилия.");
            break;
        }
        case 2:
        {
            string name = view.inputName();
            if (StudentValidator::isValidName(name))
            {
                s.setName(name);
                manager.updateStudent(index, s);
                view.showMessage("Имя изменено.");
            }
            else view.showMessage("Некорректное имя.");
            break;
        }
        case 3:
        {
            string group = view.inputGroupNumber();
            if (StudentValidator::isValidGroupNumber(group))
            {
                s.setGroupNumber(group);
                manager.updateStudent(index, s);
                view.showMessage("Группа изменена.");
            }
            else view.showMessage("Некорректный номер группы.");
            break;
        }
        case 4:
        {
            vector<int> grades = view.inputGrades();
            if (StudentValidator::areValidGrades(grades))
            {
                s.setGrades(grades);
                manager.updateStudent(index, s);
                view.showMessage("Оценки заменены.");
            }
            else view.showMessage("Некорректные оценки.");
            break;
        }
        case 5:
            s.clearGrades();
            manager.updateStudent(index, s);
            view.showMessage("Оценки очищены.");
            break;

        case 6:
        {
            int grade = view.inputSingleGrade();
            if (StudentValidator::isValidGrade(grade))
            {
                s.addGrade(grade);
                manager.updateStudent(index, s);
                view.showMessage("Оценка добавлена.");
            }
            else view.showMessage("Некорректная оценка.");
            break;
        }
        case 0:
            editing = false;
            break;

        default:
            view.showMessage("Некорректный выбор.");
        }
    }
}

// ===== Вывод =====
void StudentPresenter::showAllStudents()
{
    vector<Student> students = manager.getAllStudents();
    vector<string> infos;

    for (size_t i = 0; i < students.size(); i++)
    {
        infos.push_back(formatStudent(students.at(i)));
    }

    view.showStudents(infos);
}

// ===== Поиск и фильтрация =====
void StudentPresenter::searchBySurname()
{
    string surname = view.inputSearchSurname();
    vector<Student> result = manager.findBySurname(surname);

    if (result.empty())
        view.showMessage("Студенты не найдены.");
    else
    {
        vector<string> infos;
        for (size_t i = 0; i < result.size(); ++i)
        {
            infos.push_back(formatStudent(result.at(i)));
        }
        view.showStudents(infos);
    }
}

void StudentPresenter::filterByGroup()
{
    string group = view.inputFilterGroup();
    vector<Student> result = manager.filterByGroup(group);

    if (result.empty())
        view.showMessage("Студенты не найдены.");
    else
    {
        vector<string> infos;
        for (size_t i = 0; i < result.size(); i++)
        {
            infos.push_back(formatStudent(result.at(i)));
        }
        view.showStudents(infos);
    }
}

// ===== Сортировка =====
void StudentPresenter::sortStudents()
{
    view.showSortMenu();
    int choice = view.getSortChoice();

    switch (choice)
    {
    case 1:
        manager.sortBySurname();
        view.showMessage("Сортировка по фамилии выполнена.");
        break;
    case 2:
        manager.sortByAverageGrade();
        view.showMessage("Сортировка по среднему баллу выполнена.");
        break;
    case 0:
        break;
    default:
        view.showMessage("Некорректный выбор.");
    }
}
