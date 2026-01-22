#include "Student.h"

// Делегирующий конструктор по умолчанию
Student::Student()
    : Student("", "", "", {})
{
}

// Основной конструктор
Student::Student(const string& surname,
    const string& name,
    const string& groupNumber,
    const vector<int>& grades)
    : surname(surname),
    name(name),
    groupNumber(groupNumber),
    grades({})
{
    setGrades(grades); // проверка через Validator
}

// Геттеры
string Student::getSurname() const
{
    return surname;
}

string Student::getName() const
{
    return name;
}

string Student::getGroupNumber() const
{
    return groupNumber;
}

vector<int> Student::getGrades() const
{
    return grades;
}

// Сеттеры
bool Student::setSurname(const string& newSurname)
{
    if (!StudentValidator::isValidSurname(newSurname))
        return false;
    surname = newSurname;
    return true;
}

bool Student::setName(const string& newName)
{
    if (!StudentValidator::isValidName(newName))
        return false;
    name = newName;
    return true;
}

bool Student::setGroupNumber(const string& newGroupNumber)
{
    if (!StudentValidator::isValidGroupNumber(newGroupNumber))
        return false;
    groupNumber = newGroupNumber;
    return true;
}

bool Student::setGrades(const vector<int>& newGrades)
{
    if (!StudentValidator::areValidGrades(newGrades))
        return false;
    grades = newGrades;
    return true;
}


// Работа с оценками
bool Student::addGrade(int grade)
{
    if (!StudentValidator::isValidGrade(grade))
        return false;
    grades.push_back(grade);
    return true;
}

void Student::clearGrades()
{
    grades.clear();
}

// Расчет ср.арифм.оценки
double Student::calculateAverageGrade() const
{
    if (grades.empty())
    {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < grades.size(); i++)
    {
        sum += grades.at(i);
    }
    return (double)sum / grades.size();
}
