#include "../include/Book.h"

Book::Book(int id, const std::string& title, const std::string& author)
    : id(id), title(title), author(author), available(true) {}
int Book::getId() const {
    return id;
}
std::string Book::getTitle() const {
    return title;
}
std::string Book::getAuthor() const {
    return author;
}
bool Book::isAvailable() const {
    return available;
}
void Book::borrowBook() {
    if (available) {
        available = false;
    }
}
void Book::returnBook() {
    available = true;
}