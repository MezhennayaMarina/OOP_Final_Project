#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Student.h"

using namespace std;

class StudentFileHandler
{
private:
    string filePath;

public:
    StudentFileHandler(const string& path);

    vector<Student> load() const;
    void save(const vector<Student>& students) const;
};