#include <iostream>
#include <windows.h>

#include "StudentManager.h"
#include "ConsoleView.h"
#include "StudentPresenter.h"
#include "StudentFileHandler.h"

using namespace std;

// === Глобальные константы приложения ===
const string STUDENTS_FILE_PATH = "students.txt";

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    StudentManager manager;
    ConsoleView view;
    StudentFileHandler fileHandler(STUDENTS_FILE_PATH);

    StudentPresenter presenter(manager, view, fileHandler);
    presenter.run();

    return 0;
}
