#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../include/Book.h"
#include "../include/Member.h"
#include "../include/Library.h"
#include <fstream>

// Função auxiliar para limpar arquivos de teste
void cleanTestFiles() {
    std::ofstream bookFile("../../data/library_books.txt", std::ios::trunc);
    std::ofstream memberFile("../../data/library_members.txt", std::ios::trunc);
    bookFile.close();
    memberFile.close();
}

TEST_CASE("Book Class Tests", "[book]") {
    Book book(1, "O Senhor dos Anéis", "J.R.R. Tolkien");

    SECTION("Constructor and Getters") {
        REQUIRE(book.getId() == 1);
        REQUIRE(book.getTitle() == "O Senhor dos Anéis");
        REQUIRE(book.getAuthor() == "J.R.R. Tolkien");
        REQUIRE(book.isAvailable() == true);
    }

    SECTION("Borrow and Return") {
        REQUIRE(book.isAvailable() == true);
        book.borrowBook();
        REQUIRE(book.isAvailable() == false);
        book.returnBook();
        REQUIRE(book.isAvailable() == true);
    }
}

TEST_CASE("Member Class Tests", "[member]") {
    Member member(1, "João Silva");

    SECTION("Constructor and Getters") {
        REQUIRE(member.getId() == 1);
        REQUIRE(member.getName() == "João Silva");
        REQUIRE(member.getBorrowedBooks().empty());
    }

    SECTION("Borrow and Return Books") {
        member.borrowBook(1);
        REQUIRE(member.getBorrowedBooks().size() == 1);
        REQUIRE(member.getBorrowedBooks().front() == 1);

        member.returnBook(1);
        REQUIRE(member.getBorrowedBooks().empty());
    }
}

TEST_CASE("Library Class Tests", "[library]") {
    cleanTestFiles();  // Limpa os arquivos antes dos testes
    Library& library = Library::getInstance();

    SECTION("Add and Remove Book") {
        Book book(1, "Dom Casmurro", "Machado de Assis");
        library.addBook(book);
        
        // Verifica se o livro foi adicionado corretamente
        std::ifstream bookFile("../../data/library_books.txt");
        std::string line;
        std::getline(bookFile, line);
        REQUIRE(line == "1,Dom Casmurro,Machado de Assis,1");
        bookFile.close();

        // Testa remoção
        library.removeBook(1);
        bookFile.open("../../data/library_books.txt");
        REQUIRE(!std::getline(bookFile, line));  // Arquivo deve estar vazio
        bookFile.close();
    }

    SECTION("Add and Remove Member") {
        Member member(1, "Maria Oliveira");
        library.addMember(member);
        
        // Verifica se o membro foi adicionado corretamente
        std::ifstream memberFile("../../data/library_members.txt");
        std::string line;
        std::getline(memberFile, line);
        REQUIRE(line == "1,Maria Oliveira");
        memberFile.close();

        // Testa remoção
        library.removeMember(1);
        memberFile.open("../../data/library_members.txt");
        REQUIRE(!std::getline(memberFile, line));  // Arquivo deve estar vazio
        memberFile.close();
    }

    SECTION("Borrow and Return Book") {
        Book book(1, "1984", "George Orwell");
        Member member(1, "Pedro Santos");
        
        library.addBook(book);
        library.addMember(member);

        REQUIRE(library.borrowBook(1, 1) == true);  // Deve conseguir emprestar
        REQUIRE(library.borrowBook(1, 1) == false); // Não deve conseguir emprestar novamente
        REQUIRE(library.returnBook(1) == true);     // Deve conseguir devolver
        REQUIRE(library.returnBook(1) == false);    // Não deve conseguir devolver novamente
    }

    SECTION("Data Persistence") {
        // Adiciona dados
        Book book(1, "Memórias Póstumas", "Machado de Assis");
        Member member(1, "Ana Silva");
        
        library.addBook(book);
        library.addMember(member);
        library.borrowBook(1, 1);

        // Cria nova instância para testar carregamento
        Library& newLibrary = Library::getInstance();
        
        // Verifica se os dados foram carregados corretamente
        std::ifstream bookFile("../../data/library_books.txt");
        std::string line;
        std::getline(bookFile, line);
        REQUIRE(line == "1,Memórias Póstumas,Machado de Assis,0");
        bookFile.close();

        std::ifstream memberFile("../../data/library_members.txt");
        std::getline(memberFile, line);
        REQUIRE(line == "1,Ana Silva,1");
        memberFile.close();
    }

    cleanTestFiles();  // Limpa os arquivos após os testes
}

TEST_CASE("Edge Cases", "[edge]") {
    cleanTestFiles();
    Library& library = Library::getInstance();

    SECTION("Invalid Operations") {
        REQUIRE(library.borrowBook(999, 999) == false);  // Livro e membro inexistentes
        REQUIRE(library.returnBook(999) == false);       // Livro inexistente
        
        Book book(1, "Livro Teste", "Autor Teste");
        library.addBook(book);
        REQUIRE(library.borrowBook(1, 999) == false);    // Membro inexistente
    }

    SECTION("Empty Library Operations") {
        library.displayBooks();      // Não deve crashar
        library.displayMembers();    // Não deve crashar
        library.displayMemberBooks(1); // Não deve crashar
    }

    cleanTestFiles();
}