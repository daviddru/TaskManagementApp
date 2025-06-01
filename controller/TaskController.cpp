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

std::vector<Task> TaskController::filterTasks(const Specification& spec) const {
    std::vector<Task> result;
    for (const Task& task : repo.getAllTasks()) {
        if (spec.isSatisfiedBy(task)) {
            result.push_back(task);
        }
    }
    return result;
}