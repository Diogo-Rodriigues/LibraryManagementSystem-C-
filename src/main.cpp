#include <iostream>
#include <string>
#include "../include/Library.h"
#include "../include/Book.h"
#include "../include/Member.h"

Library& library = Library::getInstance(); // Agora é uma variável global

void showViewingMenu() {
    while (true) {
        std::cout << "\n=========================\n";
        std::cout << "     Menu de Visualização \n";
        std::cout << "=========================\n";
        std::cout << "1. Listar Membros\n";
        std::cout << "2. Listar Livros\n";
        std::cout << "3. Ver Livros de um Membro\n";
        std::cout << "0. Voltar ao Menu Principal\n";
        std::cout << "=========================\n";
        std::cout << "Escolha uma opção: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                library.displayMembers();
                break;
            case 2:
                library.displayBooks();
                break;
            case 3: {
                int memberId;
                std::cout << "\nDigite o ID do membro: ";
                std::cin >> memberId;
                library.displayMemberBooks(memberId); 
                break;
            }
            case 0:
                return;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
                break;
        }
    }
}

void showManagementMenu() {
    while (true) {
        std::cout << "\n=========================\n";
        std::cout << "     Menu de Gerenciamento \n";
        std::cout << "=========================\n";
        std::cout << "1. Adicionar Livro\n";
        std::cout << "2. Adicionar Membro\n";
        std::cout << "3. Emprestar Livro\n";
        std::cout << "4. Devolver Livro\n";
        std::cout << "5. Remover Livro\n";
        std::cout << "6. Remover Membro\n";
        std::cout << "0. Voltar ao Menu Principal\n";
        std::cout << "=========================\n";
        std::cout << "Escolha uma opção: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore();
                std::string title, author;
                int id;

                std::cout << "\nDigite o ID do livro: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Digite o título do livro: ";
                std::getline(std::cin, title);
                std::cout << "Digite o autor do livro: ";
                std::getline(std::cin, author);

                Book book(id, title, author);
                library.addBook(book);

                std::cout << "Livro adicionado com sucesso!\n";
                break;
            }
            case 2: {
                std::cin.ignore();
                std::string name;
                int id;

                std::cout << "\nDigite o ID do membro: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Digite o nome do membro: ";
                std::getline(std::cin, name);

                Member member(id, name);
                library.addMember(member);

                std::cout << "Membro adicionado com sucesso!\n";
                break;
            }
            case 3: {
                int bookId, memberId;

                std::cout << "\nDigite o ID do livro para empréstimo: ";
                std::cin >> bookId;
                std::cout << "Digite o ID do membro: ";
                std::cin >> memberId;

                if (library.borrowBook(bookId, memberId)) {
                    std::cout << "Livro emprestado com sucesso!\n";
                } else {
                    std::cout << "Falha no empréstimo. O livro pode não estar disponível.\n";
                }
                break;
            }
            case 4: {
                int bookId;
                std::cout << "\nDigite o ID do livro para devolução: ";
                std::cin >> bookId;

                if (library.returnBook(bookId)) {
                    std::cout << "Livro devolvido com sucesso!\n";
                } else {
                    std::cout << "Falha na devolução. O livro pode já estar disponível.\n";
                }
                break;
            }
            case 5: {
                int bookId;
                std::cout << "\nDigite o ID do livro a ser removido: ";
                std::cin >> bookId;

                library.removeBook(bookId);
                break;
            }
            case 6: {
                int memberId;
                std::cout << "\nDigite o ID do membro a ser removido: ";
                std::cin >> memberId;

                library.removeMember(memberId);
                break;
            }
            case 0:
                return;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
                break;
        }
    }
}

void showMainMenu() {
    std::cout << "\n=========================\n";
    std::cout << "       Menu Principal    \n";
    std::cout << "=========================\n";
    std::cout << "1. Visualização\n";
    std::cout << "2. Gerenciamento\n";
    std::cout << "0. Sair\n";
    std::cout << "=========================\n";
    std::cout << "Escolha uma opção: ";
}

int main() {
    int choice;
    while (true) {
        showMainMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                showViewingMenu();
                break;
            case 2:
                showManagementMenu();
                break;
            case 0:
                std::cout << "Saindo...\n";
                return 0;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
                break;
        }
    }
    return 0;
}