#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "Student.h"
#include "StudentValidator.h" // обновление после реализации StudentValidator

using namespace std;

class StudentManager
{
private:
    vector<Student> students;   // композиция

    static const int BASIC_CAPACITY = 10;

public:
    StudentManager();

    bool addStudent(const Student& student); // обновление после реализации StudentValidator
    bool removeStudent(int index);
    bool updateStudent(int index, const Student& updatedStudent);

    // Поиск и фильтрация
    vector<Student> findBySurname(const string& surname) const;
    vector<Student> filterByGroup(const string& groupNumber) const;

    // Сортировки
    void sortBySurname();
    void sortByAverageGrade();

    // Запрос копии отдельного студента
    Student getStudent(int index);
    // Запрос количества студентов
    int getStudentsCount() const;
    // Доступ ко всей коллекции через константную ссылку (только чтение)
    const vector<Student>& getAllStudents() const;

    void setStudents(const vector<Student>& loadedStudents);
};