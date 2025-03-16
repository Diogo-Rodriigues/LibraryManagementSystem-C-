cmake_minimum_required(VERSION 3.10)
project(LibraryManager VERSION 1.0)

# Define o standard do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define onde os executáveis serão gerados
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Adiciona os diretórios dos headers
include_directories(include)

# Adiciona os subdiretórios
add_subdirectory(src)
add_subdirectory(tests)