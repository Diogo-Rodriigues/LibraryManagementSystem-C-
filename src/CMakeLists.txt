# Lista de arquivos fonte do programa principal
set(SOURCES
    Book.cpp
    Member.cpp
    Library.cpp
    main.cpp
)

# Cria o executável principal
add_executable(library_manager ${SOURCES})

# Adiciona suporte ao filesystem
target_link_libraries(library_manager PRIVATE stdc++fs)