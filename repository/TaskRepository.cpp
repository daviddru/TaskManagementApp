//
// Created by David Druja on 28.05.2025.
//

#include "TaskRepository.h"

void TaskRepository::addTask(const Task& task) {
    tasks.push_back(task);
}

void TaskRepository::removeTask(int index) {
    if (index >=0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
    }
}

void TaskRepository::updateTask(int index, const Task& task) {
    if (index >=0 && index < tasks.size()) {
        tasks[index] = task;
    }
}

void TaskRepository::toggleCompletion(int index) {
    if (index >=0 && index < tasks.size()) {
        tasks[index].setCompleted(!tasks[index].getCompleted());
    }
}

std::vector<Task>& TaskRepository::getAllTasks() {
    return tasks;
}