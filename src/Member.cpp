#include "../include/Member.h"

Member::Member(int id, const std::string& name) : id(id), name(name) {}

int Member::getId() const {
    return id;
}

std::string Member::getName() const {
    return name;
}

void Member::borrowBook(int bookId) {
    borrowedBooks.push_back(bookId);  // Adicionar o livro emprestado à lista
}

void Member::returnBook(int bookId) {
    borrowedBooks.remove(bookId);  // Remover o livro da lista de emprestados
}

const std::list<int>& Member::getBorrowedBooks() const {
    return borrowedBooks;
}