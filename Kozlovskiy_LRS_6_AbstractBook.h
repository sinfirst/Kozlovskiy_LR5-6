#ifndef _KOZLOVSKIY_LRS_6_ABSTRACT_BOOK_H
#define _KOZLOVSKIY_LRS_6_ABSTRACT_BOOK_H

#include "Kozlovskiy_LRS_6_defLibrary.h"

class Book {
protected:
    string ISBN;
    string title;
    int publicationYear;
    
    virtual ostream& print(ostream& myostream) const {
        myostream << "Book [ISBN = " << ISBN << ", title = " << title 
                  << ", year = " << publicationYear << "]\n";
        return myostream;
    }
    
    virtual istream& input(istream& myistream);

public:
    // Конструкторы и деструктор
    Book() : ISBN(""), title(""), publicationYear(0) {
        cout << "Default constructor Book\n";
        print(cout); // Вывод информации при создании
    }
    
    Book(const Book &other) : ISBN(other.ISBN), title(other.title), 
                             publicationYear(other.publicationYear) {
        cout << "Copy constructor Book\n";
        print(cout); // Вывод информации при копировании
    }
    
    // Конструктор преобразования по ISBN
    explicit Book(const string& isbn) : ISBN(isbn), title(""), publicationYear(0) {
        cout << "Transformation constructor Book (ISBN)\n";
        print(cout); // Вывод информации при преобразовании
    }
    
    virtual ~Book() {
        cout << "Book destroyed: "; 
        print(cout); // Вывод информации при уничтожении
    }


    // Геттеры и сеттеры
    string getISBN() const { return ISBN; }
    string getTitle() const { return title; }
    int getPublicationYear() const { return publicationYear; }
    
    void setISBN(const string& isbn) { ISBN = isbn; }
    void setTitle(const string& t) { title = t; }
    void setPublicationYear(int year) { publicationYear = year; }

    // Чисто виртуальные методы
    virtual string getGenre() const = 0;
    virtual double calculateLateFee() const = 0;

    // Переопределяемые методы
    virtual bool validate() const {
        return publicationYear >= 1800;
    }

    // Перегрузка операторов
    virtual bool operator==(const Book& other) const {
        return ISBN == other.ISBN;
    }

    // Дружественные операторы ввода/вывода
    friend ostream& operator<<(ostream& myostream, const Book& book) {
        return book.print(myostream);
    }

    friend istream& operator>>(istream& myistream, Book& book) {
        return book.input(myistream);
    }
};

istream& Book::input(istream& myistream) {
    EnterString(myistream, ISBN, "Enter ISBN: ")();
    EnterString(myistream, title, "Enter title: ")();
    
    int year;
    EnterNumber(myistream, year, "Enter publication year: ")();
    publicationYear = year;
    
    return myistream;
}

#endif // _KOZLOVSKIY_LRS_6_ABSTRACT_BOOK_H


//Добавить описание print родителя
//Конструктор преобразования для наследника по title, isbn
//Род класс Конструктор преобразования по isbn
//Использовать validate при добавлении в общий vector