#include "Kozlovskiy_LRS_6_MethodsLibrary.cpp"
#include <functional>
#include <map>

using namespace std;

// Структура для пункта меню
struct MenuItem {
    string title;
    function<void()> action;
};

int main() {
    // Создание меню
    map<int, MenuItem> menu = {
        {1, {"Show all books", showBooks}},
        {2, {"Add new Novel", createNewNovel}},
        {3, {"Copy existing Novel", createCopyNovel}},
        {4, {"Combine two Novels", combineNovels}},
        {5, {"Add new ScienceBook", createNewScienceBook}},
        {6, {"Copy existing ScienceBook", createCopyScienceBook}},
        {7, {"Add tag to ScienceBook", addTagToScienceBook}},
        {8, {"Add new AudioBook", createNewAudioBook}},
        {9, {"Copy existing AudioBook", createCopyAudioBook}},
        {10, {"Play AudioBook sample", playAudioBookSample}},
        {11, {"Demonstrate polymorphism", demonstratePolymorphism}},
        {12, {"Create novel by title", createNovelByTitleISBN}}
    };

    int choice = 0;
    
    while (true) {
        cout << "\n=== Library Management System ===\n";
        for (const auto& item : menu) {
            cout << item.first << ". " << item.second.title << "\n";
        }
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        
        string input;
        getline(cin, input);
        try {
            choice = stoi(input);
        } catch (...) {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 0) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }

        auto it = menu.find(choice);
        if (it != menu.end()) {
            cout << "\n=== " << it->second.title << " ===\n";
            it->second.action();
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}