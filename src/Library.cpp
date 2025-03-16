#include "../include/Library.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

Library& Library::getInstance() {
    static Library instance;  // Instância estática
    return instance;
}

// Construtor que carrega os dados dos arquivos de texto
Library::Library() {
    // Cria o diretório data se não existir
    std::filesystem::create_directories("../../data");
    loadData();
}

// Adicionando um livro à biblioteca
void Library::addBook(const Book& book) {
    books[book.getId()] = std::make_unique<Book>(book);
    saveData(); 
}


// Adicionando um membro à biblioteca
void Library::addMember(const Member& member) {
    members[member.getId()] = std::make_unique<Member>(member);
    saveData(); 
}

// Empréstimo de um livro
bool Library::borrowBook(int bookId, int memberId) {
    if (books.count(bookId) && members.count(memberId)) {
        Book& book = *books[bookId];
        if (book.isAvailable()) {
            book.borrowBook();
            members[memberId]->borrowBook(bookId);
            saveData(); 
            return true;
        }
    }
    return false;
}

// Devolução de um livro
bool Library::returnBook(int bookId) {
    if (books.count(bookId)) {
        Book& book = *books[bookId];
        if (!book.isAvailable()) {
            book.returnBook();
            for (auto& [id, member] : members) {
                member->returnBook(bookId);
            }
            saveData(); 
            return true;
        }
    }
    return false;
}
// Exibir todos os livros
void Library::displayBooks() {
    std::cout << "\n--- Livros Disponíveis ---\n";
    for (const auto& [id, book] : books) {
        std::cout << "ID: " << book->getId() << ", Título: " << book->getTitle() 
                  << ", Autor: " << book->getAuthor() 
                  << ", Disponível: " << (book->isAvailable() ? "Sim" : "Não") << '\n';
    }
}

// Exibir todos os membros
void Library::displayMembers() {
    std::cout << "\n--- Membros Cadastrados ---\n";
    for (const auto& [id, member] : members) {
        std::cout << "ID: " << member->getId() << ", Nome: " << member->getName() << '\n';
    }
}

// Exibir os livros emprestados por um membro
void Library::displayMemberBooks(int memberId) {
    if (members.count(memberId)) {
        const Member& member = *members[memberId];
        std::cout << "\n--- Livros Emprestados pelo Membro: " << member.getName() << " ---\n";
        const auto& borrowedBooks = member.getBorrowedBooks();
        if (borrowedBooks.empty()) {
            std::cout << "Nenhum livro emprestado.\n";
        } else {
            for (int bookId : borrowedBooks) {
                const Book& book = *books[bookId];
                std::cout << "ID: " << book.getId() << ", Título: " << book.getTitle() << '\n';
            }
        }
    } else {
        std::cout << "Membro não encontrado.\n";
    }
}

// Salvar os dados em arquivos de texto
void Library::saveData() {
    std::ofstream bookFile("../../data/library_books.txt", std::ios::trunc);
    if (!bookFile.is_open()) {
        std::cerr << "Erro ao abrir arquivo de livros para escrita!\n";
        return;
    }
    for (const auto& [id, book] : books) {
        bookFile << book->getId() << ',' << book->getTitle() << ',' << book->getAuthor() 
                << ',' << book->isAvailable() << '\n';
    }
    bookFile.close();

    // Salvando os membros
    std::ofstream memberFile("../../data/library_members.txt", std::ios::trunc);
    if (!memberFile.is_open()) {
        std::cerr << "Erro ao abrir arquivo de membros para escrita!\n";
        return;
    }
    for (const auto& [id, member] : members) {
        memberFile << member->getId() << ',' << member->getName();
        const auto& borrowedBooks = member->getBorrowedBooks();
        for (int bookId : borrowedBooks) {
            memberFile << ',' << bookId;
        }
        memberFile << '\n';
    }
    memberFile.close();
}

// Carregar os dados dos arquivos de texto
void Library::loadData() {
    std::ifstream bookFile("../../data/library_books.txt");
    if (!bookFile.is_open()) {
        std::cerr << "Arquivo de livros não encontrado!\n";
        return;
    }
    std::string line;
    while (std::getline(bookFile, line)) {
        std::stringstream ss(line);
        std::string part;
        int id;
        std::string title, author;
        bool available;

        std::getline(ss, part, ',');
        id = std::stoi(part);
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, part, ',');
        available = std::stoi(part);

        Book book(id, title, author);
        if (!available) {
            book.borrowBook();
        }
        books[id] = std::make_unique<Book>(book);
    }
    bookFile.close();

    // Carregar os membros
    std::ifstream memberFile("../../data/library_members.txt");
    if (!memberFile.is_open()) {
        std::cerr << "Arquivo de membros não encontrado!\n";
        return;
    }
    while (std::getline(memberFile, line)) {
        std::stringstream ss(line);
        std::string part;
        int id;
        std::string name;

        std::getline(ss, part, ',');
        id = std::stoi(part);
        std::getline(ss, name, ',');

        Member member(id, name);
        while (std::getline(ss, part, ',')) {
            int bookId = std::stoi(part);
            member.borrowBook(bookId);
        }
        members[id] = std::make_unique<Member>(member);
    }
    memberFile.close();
}
    
// Função para remover um livro
void Library::removeBook(int bookId) {
    if (books.count(bookId)) {
        for (auto& [id, member] : members) {
            member->returnBook(bookId);  
        }
        books.erase(bookId);  
        saveData();  
        std::cout << "Livro removido com sucesso!\n";
    } else {
        std::cout << "Erro: Livro não encontrado.\n";
    }
}
// Função para remover um membro
void Library::removeMember(int memberId) {
    if (members.count(memberId)) {
        // Primeiro devolve todos os livros emprestados
        Member& member = *members[memberId];
        auto borrowedBooks = member.getBorrowedBooks(); // Cria cópia para iterar
        
        for (int bookId : borrowedBooks) {
            if (books.count(bookId)) {
                books[bookId]->returnBook();
            }
        }
        // Remove o membro
        members.erase(memberId);
        // Salva as alterações nos arquivos
        saveData();
        std::cout << "Membro removido com sucesso!\n";
    } else {
        std::cout << "Erro: Membro não encontrado.\n";
    }
}