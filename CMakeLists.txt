cmake_minimum_required(VERSION 3.26)
project(AED_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED_Project main.cpp
        Classes/Student.cpp
        Classes/Student.h
        Classes/Class.cpp
        Classes/Class.h
        Classes/Schedule.cpp
        Classes/Schedule.h
        Classes/Lesson.cpp
        Classes/Lesson.h
)
