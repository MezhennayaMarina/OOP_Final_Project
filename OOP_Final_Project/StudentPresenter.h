#pragma once

#include <string>
#include <vector>

#include "ConsoleView.h"
#include "StudentManager.h"
#include "StudentValidator.h"
#include "StudentFileHandler.h"

using namespace std;

class StudentPresenter
{
private:
    StudentManager& manager;
    ConsoleView& view;
    StudentFileHandler& fileHandler;

public:
    StudentPresenter(
        StudentManager& manager,
        ConsoleView& view,
        StudentFileHandler& fileHandler
    );

    void run(); // основной цикл программы

private:
    // === Действия пользователя ===
    void addStudent();
    void removeStudent();
    void editStudent();
    void showAllStudents();
    void searchBySurname();
    void filterByGroup();
    void sortStudents();

    // === Работа с файлом ===
    void loadFromFile();
    void saveToFile();

    // === Редактирование ===
    void editStudentField(int index);

    // === Форматирование ===
    string formatStudent(const Student& student);
};
