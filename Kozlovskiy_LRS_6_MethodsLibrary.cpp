#ifndef _KOZLOVSKIY_LRS_6_METHODS_LIBRARY_H
#define _KOZLOVSKIY_LRS_6_METHODS_LIBRARY_H

#include "Kozlovskiy_LRS_6_AbstractBook.h"
#include "Kozlovskiy_LRS_6_ChildNovel.h"
#include "Kozlovskiy_LRS_6_ChildScienceBook.h"
#include "Kozlovskiy_LRS_6_MultiAudioBook.h"
#include <vector>
#include <memory>
#include <map>

using namespace std;

// Вектор книг
vector<unique_ptr<Book>> libraryBooks;

// Функция для отображения списка книг
void showBooks() {
    if (libraryBooks.empty()) {
        cout << "Library is empty!\n";
        return;
    }
    
    cout << "=== Library Catalog ===\n";
    for (size_t i = 0; i < libraryBooks.size(); ++i) {
        cout << i << ": " << *libraryBooks[i];
    }
    cout << "=======================\n";
}

// Вспомогательная функция для выбора книги
Book* selectBook(const string& type) {
    showBooks();
    int index = -1;
    EnterNumber(cin, index, "Select " + type + " book index")();
    
    if (index < 0 || index >= libraryBooks.size()) {
        cerr << "Invalid book index!\n";
        return nullptr;
    }
    return libraryBooks[index].get();
}

// Функции для работы с Novel
void createNewNovel() {
    Novel* novel = new Novel();
    cin >> *novel;
    libraryBooks.emplace_back(novel);
}

void createCopyNovel() {
    Novel* source = dynamic_cast<Novel*>(selectBook("Novel"));
    if (!source) {
        cerr << "Selected book is not a Novel!\n";
        return;
    }
    Novel* copy = new Novel(*source);
    libraryBooks.emplace_back(copy);
}

void combineNovels() {
    Novel* first = dynamic_cast<Novel*>(selectBook("first Novel"));
    if (!first) {
        cerr << "First book is not a Novel!\n";
        return;
    }
    
    Novel* second = dynamic_cast<Novel*>(selectBook("second Novel"));
    if (!second) {
        cerr << "Second book is not a Novel!\n";
        return;
    }
    
    try {
        Novel combined = *first + *second;
        libraryBooks.emplace_back(make_unique<Novel>(combined));
        cout << "Novels combined successfully!\n";
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << "\n";
    }
}

// Функции для работы с ScienceBook
void createNewScienceBook() {
    ScienceBook* book = new ScienceBook();
    cin >> *book;
    libraryBooks.emplace_back(book);
}

void createCopyScienceBook() {
    ScienceBook* source = dynamic_cast<ScienceBook*>(selectBook("ScienceBook"));
    if (!source) {
        cerr << "Selected book is not a ScienceBook!\n";
        return;
    }
    ScienceBook* copy = new ScienceBook(*source);
    libraryBooks.emplace_back(copy);
}

void addTagToScienceBook() {
    ScienceBook* book = dynamic_cast<ScienceBook*>(selectBook("ScienceBook"));
    if (!book) {
        cerr << "Selected book is not a ScienceBook!\n";
        return;
    }
    
    string tag;
    EnterString(cin, tag, "Enter tag to add")();
    *book += tag;
    cout << "Tag added successfully!\n";
}

// Функции для работы с AudioBook
void createNewAudioBook() {
    AudioBook* book = new AudioBook();
    cin >> *book;
    libraryBooks.emplace_back(book);
}

void createCopyAudioBook() {
    AudioBook* source = dynamic_cast<AudioBook*>(selectBook("AudioBook"));
    if (!source) {
        cerr << "Selected book is not an AudioBook!\n";
        return;
    }
    AudioBook* copy = new AudioBook(*source);
    libraryBooks.emplace_back(copy);
}

void playAudioBookSample() {
    AudioBook* book = dynamic_cast<AudioBook*>(selectBook("AudioBook"));
    if (!book) {
        cerr << "Selected book is not an AudioBook!\n";
        return;
    }
    book->playSample();
}

// Демонстрация полиморфизма
void demonstratePolymorphism() {
    cout << "=== Polymorphism Demonstration ===\n";
    for (const auto& book : libraryBooks) {
        cout << *book;
        cout << "Genre: " << book->getGenre() << "\n";
        cout << "Late fee per day: " << book->calculateLateFee() << " RUB\n";
        
        if (auto novel = dynamic_cast<Novel*>(book.get())) {
            cout << "Author bio: " << novel->getAuthorBio() << "\n";
        }
        else if (auto science = dynamic_cast<ScienceBook*>(book.get())) {
            cout << "Is relevant: " << (science->checkRelevance() ? "Yes" : "No") << "\n";
        }
        else if (auto audio = dynamic_cast<AudioBook*>(book.get())) {
            cout << "Chapter 1: " << (*audio)[1] << "\n";
        }
        cout << "----------------------------\n";
    }
}

#endif // _KOZLOVSKIY_LRS_6_METHODS_LIBRARY_H