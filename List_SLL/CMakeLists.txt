cmake_minimum_required(VERSION 3.25)
project(Lab2___Lista_LSI_BUN_)

set(CMAKE_CXX_STANDARD 14)

include_directories("Proiect C++")
include_directories(Teste)

add_executable(Lab2___Lista_LSI_BUN_
        "Proiect C++/App.cpp"
        "Proiect C++/IteratorLI.cpp"
        "Proiect C++/IteratorLI.h"
        "Proiect C++/LI.cpp"
        "Proiect C++/LI.h"
        Teste/TestExtins.cpp
        Teste/TestExtins.h
        Teste/TestScurt.cpp
        Teste/TestScurt.h)
