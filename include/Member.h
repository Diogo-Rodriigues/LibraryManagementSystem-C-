#pragma once
#include <string>
#include <list>

class Member {
public:
    Member(int id, const std::string& name);
    
    int getId() const;
    std::string getName() const;

    void borrowBook(int bookId);     // Adicionar o ID do livro aos livros emprestados
    void returnBook(int bookId);     // Remover o ID do livro dos livros emprestados
    const std::list<int>& getBorrowedBooks() const;  // Retornar lista de IDs de livros emprestados

private:
    int id;
    std::string name;
    std::list<int> borrowedBooks;   // Lista de IDs de livros emprestados
};