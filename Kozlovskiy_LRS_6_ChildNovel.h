#ifndef _KOZLOVSKIY_LRS_6_CHILD_NOVEL_H
#define _KOZLOVSKIY_LRS_6_CHILD_NOVEL_H

#include "Kozlovskiy_LRS_6_AbstractBook.h"

class Novel : public Book {
protected:
    string author;
    int pageCount;
    
    ostream& print(ostream& myostream) const override {
        Book::print(myostream); // Вызов родительского print
        myostream << "  Novel details [author = " << author 
                  << ", pages = " << pageCount << "]\n";
        return myostream;
    }
    
    istream& input(istream& myistream) override;

public:
    // Конструкторы
    Novel() : author(""), pageCount(0) {
        cout << "Default constructor Novel\n";
        print(cout);
    }
    
    Novel(const Novel &other) : Book(other), author(other.author), 
                              pageCount(other.pageCount) {
        cout << "Copy constructor Novel\n";
        print(cout);
    }
    
    // Конструктор преобразования по title и ISBN
    Novel(const string& isbn, const string& t) : Book(isbn), author(""), pageCount(0) {
        title = t;
        cout << "Transformation constructor Novel (ISBN, title)\n";
        print(cout);
    }
    
    virtual ~Novel() {
        cout << "Novel destroyed: ";
        print(cout);
    }


    // Геттеры и сеттеры
    string getAuthor() const { return author; }
    int getPageCount() const { return pageCount; }
    
    void setAuthor(const string& a) { author = a; }
    void setPageCount(int count) { pageCount = count; }

    // Переопределение виртуальных методов
    string getGenre() const override {
        return "Novel";
    }
    
    double calculateLateFee() const override {
        return 10.0; // 10 руб./день за просрочку
    }
    
    bool validate() const override {
        return Book::validate() && pageCount >= 50;
    }

    // Дополнительный метод
    string getAuthorBio() const {
        return "Brief biography of " + author + " (placeholder)";
    }

    // Перегрузка операторов
    Novel operator+(const Novel& other) const {
        if (author != other.author) {
            throw invalid_argument("Can only combine novels by the same author");
        }
        
        Novel combined(*this);
        combined.title = title + " & " + other.title;
        combined.pageCount += other.pageCount;
        return combined;
    }
};

istream& Novel::input(istream& myistream) {
    Book::input(myistream);
    EnterString(myistream, author, "Enter author: ")();
    
    int pages;
    EnterNumber(myistream, pages, "Enter page count: ")();
    pageCount = pages;
    
    return myistream;
}

#endif // _KOZLOVSKIY_LRS_6_CHILD_NOVEL_H