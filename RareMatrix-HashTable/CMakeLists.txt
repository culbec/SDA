cmake_minimum_required(VERSION 3.25)
project(L6_RareMatrix_HashTable)

set(CMAKE_CXX_STANDARD 14)

include_directories("Proiect C++")
include_directories(Teste)

add_executable(L6_RareMatrix_HashTable
        "Proiect C++/App.cpp"
        "Proiect C++/Matrice.cpp"
        "Proiect C++/Matrice.h"
        Teste/TestExtins.cpp
        Teste/TestExtins.h
        Teste/TestScurt.cpp
        Teste/TestScurt.h)
