cmake_minimum_required(VERSION 3.25)
project(L4_SortedList_LSI_DynamicTable)

set(CMAKE_CXX_STANDARD 14)

include_directories("Proiect C++")
include_directories(Teste)

add_executable(L4_SortedList_LSI_DynamicTable
        "Proiect C++/App.cpp"
        "Proiect C++/IteratorLO.cpp"
        "Proiect C++/IteratorLO.h"
        "Proiect C++/LO.cpp"
        "Proiect C++/LO.h"
        Teste/TestExtins.cpp
        Teste/TestExtins.h
        Teste/TestScurt.cpp
        Teste/TestScurt.h)
