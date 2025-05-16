#ifndef _KOZLOVSKIY_LRS_6_DEF_LIBRARY_H
#define _KOZLOVSKIY_LRS_6_DEF_LIBRARY_H

#include <iomanip>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <memory>
#include <map>
using namespace std;

// Функция проверки корректности ввода целого положительного числа
bool UserInputInt(string input) {
    if (input.empty()) return false;
    try {
        int number = stoi(input);
        if (number < 0) return false;
    }
    catch (...) { 
        return false; 
    }
    return true;
}

// Функция проверки корректности ввода строки
bool UserInputStr(string input) {
    return !input.empty();
}

// Вспомогательная функция для ввода целых чисел
function<void()> EnterNumber(istream& myistream, int& varLink, string label) {
    return [&myistream, &varLink, label]() {
        string raw_input;
        cout << label << " = ";
        getline(myistream, raw_input);
        while (!UserInputInt(raw_input)) {
            cout << label << " = ";
            getline(myistream, raw_input);
        }
        varLink = stoi(raw_input);
    };
}

// Вспомогательная функция для ввода строк
function<void()> EnterString(istream& myistream, string& varLink, string label) {
    return [&myistream, &varLink, label]() {
        cout << label << " = ";
        getline(myistream, varLink);
        while (!UserInputStr(varLink)) {
            cout << label << " = ";
            getline(myistream, varLink);
        }
    };
}

#endif // _KOZLOVSKIY_LRS_6_DEF_LIBRARY_H