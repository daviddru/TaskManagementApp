cmake_minimum_required(VERSION 3.16)
project(TaskManagement)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "/Users/daviddruja/Qt/6.9.0/macos")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(TaskManagement main.cpp
        domain/Task.h
        repository/TaskRepository.h
        controller/TaskController.cpp
        controller/TaskController.h
        ui/mainwindow.cpp
        ui/mainwindow.h
        repository/CSVTaskRepository.cpp
        repository/CSVTaskRepository.h
        repository/JSONTaskRepository.cpp
        repository/JSONTaskRepository.h
        domain/Specification.h
        ui/FilterDialog.cpp
        ui/FilterDialog.h
        domain/Command.h
        controller/AddTaskCommand.h
        controller/CommandManager.h
        controller/RemoveTaskCommand.h
        controller/UpdateTaskCommand.h
        tests/test.cpp
        tests/test.h
)

target_link_libraries(TaskManagement Qt6::Widgets)
