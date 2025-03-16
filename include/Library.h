#pragma once
#include <map>
#include <list>
#include <memory>
#include "../include/Book.h"
#include "../include/Member.h"

class Library {
public:
    static Library& getInstance();  // Método Singleton para acessar a única instância
    
    void addBook(const Book& book);
    void addMember(const Member& member);
    bool borrowBook(int bookId, int memberId);
    bool returnBook(int bookId);

    void removeBook(int bookId);     // Nova função para remover livros
    void removeMember(int memberId); // Nova função para remover membros

    void displayBooks();        // Mostrar todos os livros
    void displayMembers();      // Mostrar todos os membros
    void displayMemberBooks(int memberId); // Mostrar livros emprestados por um membro

    void saveData();  // Salvar dados em arquivos .txt
    void loadData();  // Carregar dados de arquivos .txt

private:
    Library();  // Construtor privado para Singleton
    std::map<int, std::unique_ptr<Book>> books;
    std::map<int, std::unique_ptr<Member>> members;
};