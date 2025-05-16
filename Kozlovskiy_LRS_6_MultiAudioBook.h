#ifndef _KOZLOVSKIY_LRS_6_MULTI_AUDIO_BOOK_H
#define _KOZLOVSKIY_LRS_6_MULTI_AUDIO_BOOK_H

#include "Kozlovskiy_LRS_6_AbstractBook.h"
#include "Kozlovskiy_LRS_6_ParentAudioPlayer.h"

class AudioBook : public Book, public AudioPlayer {
protected:
    double duration; // в часах
    string narrator;
    
    ostream& print(ostream& myostream) const override;
    istream& input(istream& myistream) override;

public:
    // Конструкторы
    AudioBook() : duration(0.0), narrator("") {
        audioFormat = "MP3";
        bitrate = 128;
        cout << "Default constructor AudioBook\n";
    }
    
    AudioBook(const AudioBook &other) : Book(other), AudioPlayer(other), 
                                      duration(other.duration), narrator(other.narrator) {
        cout << "Copy constructor AudioBook\n";
    }
    
    AudioBook(const string& isbn) : Book(isbn), duration(0.0), narrator("") {
        audioFormat = "MP3";
        bitrate = 128;
        cout << "Transformation constructor AudioBook\n";
    }
    
    ~AudioBook() {
        cout << "AudioBook destroyed: " << title << endl;
    }

    // Геттеры и сеттеры
    double getDuration() const { return duration; }
    string getNarrator() const { return narrator; }
    
    void setDuration(double d) { duration = d; }
    void setNarrator(const string& n) { narrator = n; }

    // Переопределение виртуальных методов
    string getGenre() const override {
        return "AudioBook";
    }
    
    double calculateLateFee() const override {
        return 7.5; // 7.5 руб./день за аудиокниги
    }
    
    bool validate() const override {
        return Book::validate() && duration >= 0.5 && 
               (audioFormat == "MP3" || audioFormat == "AAC");
    }

    // Переопределение метода из AudioPlayer
    void playSample() const override {
        cout << "Playing audio book sample: " << title << " narrated by " << narrator << "\n";
    }

    // Перегрузка операторов
    string operator[](int chapter) const {
        return "Chapter " + to_string(chapter) + " of " + title;
    }
};

ostream& AudioBook::print(ostream& myostream) const {
    myostream << "AudioBook [ISBN = " << ISBN << ", title = " << title 
              << ", narrator = " << narrator << ", duration = " << duration 
              << " hours, format = " << audioFormat << ", bitrate = " << bitrate 
              << " kbps, year = " << publicationYear << "]\n";
    return myostream;
}

istream& AudioBook::input(istream& myistream) {
    Book::input(myistream);
    EnterString(myistream, narrator, "Enter narrator: ")();
    
    string dur;
    cout << "Enter duration (hours): ";
    getline(cin, dur);
    try {
        duration = stod(dur);
    } catch (...) {
        duration = 0.0;
    }
    
    EnterString(myistream, audioFormat, "Enter audio format (MP3/AAC): ")();
    
    int rate;
    EnterNumber(myistream, rate, "Enter bitrate (kbps): ")();
    bitrate = rate;
    
    return myistream;
}

#endif // _KOZLOVSKIY_LRS_6_MULTI_AUDIO_BOOK_H