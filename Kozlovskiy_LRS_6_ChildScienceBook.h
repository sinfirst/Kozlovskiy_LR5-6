#ifndef _KOZLOVSKIY_LRS_6_CHILD_SCIENCE_BOOK_H
#define _KOZLOVSKIY_LRS_6_CHILD_SCIENCE_BOOK_H

#include "Kozlovskiy_LRS_6_AbstractBook.h"

class ScienceBook final : public Book {
protected:
    string field;
    bool isPeerReviewed;
    
    ostream& print(ostream& myostream) const override;
    istream& input(istream& myistream) override;

public:
    // Конструкторы
    ScienceBook() : field(""), isPeerReviewed(false) {
        cout << "Default constructor ScienceBook\n";
    }
    
    ScienceBook(const ScienceBook &other) : Book(other), field(other.field), 
                                         isPeerReviewed(other.isPeerReviewed) {
        cout << "Copy constructor ScienceBook\n";
    }
    
    ScienceBook(const string& isbn) : Book(isbn), field(""), isPeerReviewed(false) {
        cout << "Transformation constructor ScienceBook\n";
    }
    
    ~ScienceBook() {
        cout << "ScienceBook destroyed: " << title << endl;
    }

    // Геттеры и сеттеры
    string getField() const { return field; }
    bool getIsPeerReviewed() const { return isPeerReviewed; }
    
    void setField(const string& f) { field = f; }
    void setIsPeerReviewed(bool reviewed) { isPeerReviewed = reviewed; }

    // Переопределение виртуальных методов
    string getGenre() const override {
        return "Science";
    }
    
    double calculateLateFee() const override {
        double fee = 5.0; // 5 руб./день
        if (isPeerReviewed) {
            fee += 20.0; // +20 руб. за рецензированные
        }
        return fee;
    }
    
    bool validate() const override {
        return Book::validate() && !field.empty();
    }

    // Дополнительный метод
    bool checkRelevance() const {
        return publicationYear >= 2010;
    }

    // Перегрузка операторов
    ScienceBook& operator+=(const string& tag) {
        title += " [" + tag + "]";
        return *this;
    }
};

ostream& ScienceBook::print(ostream& myostream) const {
    myostream << "ScienceBook [ISBN = " << ISBN << ", title = " << title 
              << ", field = " << field << ", peer-reviewed = " 
              << (isPeerReviewed ? "Yes" : "No") 
              << ", year = " << publicationYear << "]\n";
    return myostream;
}

istream& ScienceBook::input(istream& myistream) {
    Book::input(myistream);
    EnterString(myistream, field, "Enter field: ")();
    
    string reviewed;
    cout << "Is peer-reviewed? (yes/no): ";
    getline(cin, reviewed);
    isPeerReviewed = (reviewed == "yes");
    
    return myistream;
}

#endif // _KOZLOVSKIY_LRS_6_CHILD_SCIENCE_BOOK_H