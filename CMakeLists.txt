cmake_minimum_required(VERSION 3.5)

project(OtusHomework_11_DB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(OtusHomework_11_DB
    main.cpp
    sqlite/sqlite3.c
    sqlite/sqlite3.h
)


install(TARGETS OtusHomework_11_DB
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
