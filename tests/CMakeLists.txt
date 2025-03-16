# Enable testing
enable_testing()

# Lista de arquivos fonte dos testes
set(TEST_SOURCES
    TestMain.cpp
)

# Adiciona os arquivos fonte do projeto (exceto main.cpp)
set(LIB_SOURCES
    ${CMAKE_SOURCE_DIR}/src/Book.cpp
    ${CMAKE_SOURCE_DIR}/src/Member.cpp
    ${CMAKE_SOURCE_DIR}/src/Library.cpp
)

# Cria o executável de testes
add_executable(run_tests ${TEST_SOURCES} ${LIB_SOURCES})

# Encontra e liga o Catch2
find_package(Catch2 3 REQUIRED)
target_link_libraries(run_tests PRIVATE Catch2::Catch2WithMain stdc++fs)

# Adiciona o teste ao CTest
include(CTest)
include(Catch)
catch_discover_tests(run_tests)