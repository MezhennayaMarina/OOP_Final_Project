#include "StudentManager.h"

// --- Конструктор ---
StudentManager::StudentManager() {
    students.reserve(BASIC_CAPACITY);
}

// --- Добавление студента ---
bool StudentManager::addStudent(const Student& student)
{
    if (!StudentValidator::isValidName(student.getName()) ||
        !StudentValidator::isValidSurname(student.getSurname()) ||
        !StudentValidator::isValidGroupNumber(student.getGroupNumber()) ||
        !StudentValidator::areValidGrades(student.getGrades()))
    {
        return false; // данные невалидные
    }

    students.push_back(student);
    return true;
}

// --- Удаление студента ---
bool StudentManager::removeStudent(int index) // здесь index от 0 до size-1
{
    if (index >= students.size())
        return false;

    students.erase(students.begin() + index);
    return true;
}

// --- Обновление студента ---
bool StudentManager::updateStudent(int index, const Student& student)
{
    if (index >= students.size())
        return false;

    if (!StudentValidator::isValidName(student.getName()) ||
        !StudentValidator::isValidSurname(student.getSurname()) ||
        !StudentValidator::isValidGroupNumber(student.getGroupNumber()) ||
        !StudentValidator::areValidGrades(student.getGrades()))
    {
        return false; // данные невалидные
    }

    students.at(index) = student;
    return true;
}

// --- Поиск по фамилии ---
vector<Student> StudentManager::findBySurname(const string& surname) const
{
    vector<Student> result;
    for (int i = 0; i < students.size(); i++)
    {
        if (students.at(i).getSurname() == surname)
        {
            result.push_back(students.at(i));
        }
    }
    return result;
}

// --- Фильтрация по группе ---
vector<Student> StudentManager::filterByGroup(const string& groupNumber) const
{
    vector<Student> result;
    for (int i = 0; i < students.size(); i++)
    {
        if (students.at(i).getGroupNumber() == groupNumber)
        {
            result.push_back(students.at(i));
        }
    }
    return result;
}

// --- Сортировки ---
void StudentManager::sortBySurname()
{
    sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.getSurname() < b.getSurname();
        });
}

void StudentManager::sortByAverageGrade()
{
    sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.calculateAverageGrade() > b.calculateAverageGrade();
        });
}

// --- Получение студента ---
Student StudentManager::getStudent(int index)
{
    return students.at(index); // выброс std::out_of_range при неверном индексе
}

// --- Количество студентов ---
int StudentManager::getStudentsCount() const
{
    return students.size();
}

// --- Доступ ко всей коллекции ---
const vector<Student>& StudentManager::getAllStudents() const
{
    return students;
}

void StudentManager::setStudents(const vector<Student>& loadedStudents)
{
    students = loadedStudents;
}

