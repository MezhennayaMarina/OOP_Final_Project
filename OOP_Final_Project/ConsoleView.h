#pragma once

#include <iostream>
#include <limits> // для numeric_limits<streamsize>::max()
#include <string>
#include <vector>

using namespace std;

// слой view не знает о классе Student, поэтому модель данных задаем структурой
struct StudentInputData
{
    string surname;
    string name;
    string groupNumber;
    vector<int> grades;
};

class ConsoleView
{
private:
    // ===== Константы =====
    static const int MAX_GRADES_COUNT = 100;
    static const int MIN_GRADE = 1;
    static const int MAX_GRADE = 10;
    static const int MIN_MENU_OPTION = 0;
    static const int MAX_MENU_OPTION = 7;
    static const int MAX_EDIT_CHOICE = 6;
    static const int MAX_SORT_CHOICE = 2;
    static const int MIN_STUDENT_INDEX = 1;

    // ===== Приватные методы =====
    int inputInt(const string& prompt, int min, int max);
    string inputString(const string& prompt);

public:
    // ===== Главное меню =====
    void showMainMenu();
    int getMainMenuChoice();

    // ===== Меню редактирования студента =====
    void showStudentEditMenu();
    int getStudentEditChoice();

    // ===== Меню сортировки =====
    void showSortMenu();
    int getSortChoice();

    // ===== Ввод данных =====
    StudentInputData inputStudentData();
    
    string inputSurname();
    string inputName();
    string inputGroupNumber();
    vector<int> inputGrades();
    int inputSingleGrade();

    // ===== Выбор =====
    size_t inputStudentIndex(size_t maxIndex);
    string inputSearchSurname(); // фамилия для поиска
    string inputFilterGroup();   // номер группы для фильтрации

    // ===== Вывод =====
    void showMessage(const string& message); // вывод требуемого сообщения
    void showStudent(const string& studentInfo); // вывод строки с информацией об одном студенте
    void showStudents(const vector<string>& studentsInfo); // вывод вектора строк о студентах

};
