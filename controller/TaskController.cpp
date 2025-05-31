//
// Created by David Druja on 28.05.2025.
//

#include "TaskController.h"

void TaskController::addTask(const QString& description) {
    repo.addTask(description);
}

void TaskController::removeTask(int index) {
    repo.removeTask(index);
}

void TaskController::updateTask(int index, const QString& description) {
    repo.updateTask(index, description);
}

void TaskController::toggleCompletion(int index) {
    repo.toggleCompletion(index);
}

const std::vector<Task>& TaskController::getAllTasks() const {
    return repo.getAllTasks();
}