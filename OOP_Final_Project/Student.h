#pragma once

#include <string>
#include <vector>
#include "StudentValidator.h" // обновление после реализации StudentValidator

using namespace std;

class Student
{
private:
    string surname;
    string name;
    string groupNumber;
    vector<int> grades;

public:
    // Конструкторы
    Student();
    Student(const string& surname,
        const string& name,
        const string& groupNumber,
        const vector<int>& grades = {});

    // Геттеры
    string getSurname() const;// const запрещает методу изменять состояние объекта
    string getName() const;
    string getGroupNumber() const;
    vector<int> getGrades() const;

    // Сеттеры
    bool setSurname(const string& newSurname);
    bool setName(const string& newName);
    bool setGroupNumber(const string& newGroupNumber);
    bool setGrades(const vector<int>& newGrades);

    // Работа с оценками
    bool addGrade(int grade);
    void clearGrades();

    // Расчет ср.арифм.оценки
    double calculateAverageGrade() const;
};
