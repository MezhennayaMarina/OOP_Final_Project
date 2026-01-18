#include "StudentFileHandler.h"

StudentFileHandler::StudentFileHandler(const string& path)
    : filePath(path)
{
}

// ===== ЧТЕНИЕ ИЗ ФАЙЛА =====
vector<Student> StudentFileHandler::load() const
{
    vector<Student> students;

    ifstream fin(filePath);
    if (!fin.is_open())
        return students;

    string surname, name, group;
    int gradeCount;

    while (fin >> surname >> name >> group >> gradeCount)
    {
        vector<int> grades;
        for (int i = 0; i < gradeCount; ++i)
        {
            int g;
            fin >> g;
            grades.push_back(g);
        }

        students.emplace_back(surname, name, group, grades);
    }

    fin.close();
    return students;
}

// ===== ЗАПИСЬ В ФАЙЛ =====
void StudentFileHandler::save(const vector<Student>& students) const
{
    ofstream fout(filePath);
    if (!fout.is_open())
    {
        cout << "Ошибка открытия файла для записи." << endl;
        return;
    }

    for (size_t i = 0; i < students.size(); ++i)
    {
        const Student& s = students[i];

        fout << s.getSurname() << " "
            << s.getName() << " "
            << s.getGroupNumber() << " "
            << s.getGrades().size();

        for (int grade : s.getGrades())
            fout << " " << grade;

        if (i + 1 < students.size())
            fout << endl;
    }

    fout.close();
    cout << "Данные сохранены в файл." << endl;
}


