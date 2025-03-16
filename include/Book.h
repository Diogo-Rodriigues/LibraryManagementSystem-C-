#pragma once
#include <string>

class Book {
public:
    Book(int id, const std::string& title, const std::string& author);
    
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    bool isAvailable() const;

    void borrowBook();
    void returnBook();

private:
    int id;
    std::string title;
    std::string author;
    bool available;
};