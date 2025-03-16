# Library Management System

A comprehensive C++ application designed for managing a library's collection of books and members. This system allows librarians to track books, register members, manage borrowing operations, and maintain records efficiently.

## Features

- **Book Management**: Add, remove, and display all books in the library
- **Member Management**: Register, remove, and list all library members
- **Borrowing System**: Track book loans and returns
- **Member History**: View books currently borrowed by each member
- **Data Persistence**: All data is automatically saved to text files
- **User-friendly Interface**: Console menu system for easy navigation
- **Singleton Pattern**: Ensures a single library instance throughout the application

## Prerequisites

To build and run this project, you need:

- CMake (version 3.10 or higher)
- C++ compiler with C++17 support
- Catch2 (version 3) for running tests

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Diogo-Rodriigues/LibraryManagementSystem-Cpp.git
   cd library-management
   ```

2. Create a build directory and compile the project:
   ```bash
   mkdir -p build
   cd build
   cmake ..
   make
   ```

3. Run the application:
   ```bash
   ./bin/library_manager
   ```

## Usage

### Main Menu
The application provides a simple menu-driven interface:
- **Viewing Menu**: Access information about books and members
- **Management Menu**: Perform operations like adding/removing books and members, borrowing/returning books

### Example Operations

#### Adding a Book
1. Select "Management" from the main menu
2. Choose "Add Book"
3. Enter the book's ID, title, and author when prompted

#### Borrowing a Book
1. Select "Management" from the main menu
2. Choose "Borrow Book"
3. Enter the book ID and member ID when prompted

#### Viewing Member's Borrowed Books
1. Select "Viewing" from the main menu
2. Choose "View Books of a Member"
3. Enter the member ID when prompted

## Project Structure

```
library_manager/
├── include/               # Header files
│   ├── Book.h             # Book class definition
│   ├── Member.h           # Member class definition
│   ├── Library.h          # Library singleton class definition
├── src/                   # Source files
│   ├── CMakeLists.txt     # CMake configuration for source
│   ├── Book.cpp           # Book class implementation
│   ├── Member.cpp         # Member class implementation
│   ├── Library.cpp        # Library class implementation
│   ├── main.cpp           # Main program entry point
├── tests/                 # Unit tests
│   ├── CMakeLists.txt     # CMake configuration for tests
│   ├── TestMain.cpp       # Test cases using Catch2
├── data/                  # Data storage
│   ├── library_books.txt  # Book records
│   ├── library_members.txt# Member records
├── build/                 # Build directory (generated)
├── CMakeLists.txt         # Main CMake configuration
├── README.md              # Project documentation
```

## Contributing

Contributions to improve the Library Management System are welcome. Please follow these steps:

1. Fork the repository:
   ![fork](https://github.com/user-attachments/assets/40a18cf5-031e-4134-bd73-e87cf22b57aa)
2. Clone the fork (`git clone repository_link`)
3. Navigate to the project directory (`cd LibraryManagementSystem-Cpp`)
4. Create a new branch (`git checkout -b feature/feature_name`)
5. Make your changes
6. Run the tests to ensure everything works (`./bin/run_tests`)
7. Commit your changes (`git add file_name`) | (`git commit -m "description"`)
8. Push to the branch (`git push origin feature/feature_name`)
9. Open a Pull Request
   ![pr](https://github.com/user-attachments/assets/0fb5947b-2a31-4240-b00d-12c9de24eee7)
10. Add a title and description for your Pull Request:
    ![submmit](https://github.com/user-attachments/assets/a30c6f0a-8752-43c4-965a-279220b01279)

### Contribution Guidelines

- Follow the existing code style and conventions
- Add unit tests for new features
- Ensure all tests pass before submitting pull requests
- Update documentation as needed

## Testing

The project includes comprehensive unit tests for all components. To run the tests:

```bash
cd build
./bin/run_tests
```

## Data Storage

All data is stored in text files in the `data/` directory:
- `library_books.txt` - Information about all books
- `library_members.txt` - Information about members and their borrowed books

## License

This project is licensed under the MIT License - see the LICENSE file for details.
