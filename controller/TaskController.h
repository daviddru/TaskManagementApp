//
// Created by David Druja on 28.05.2025.
//

#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H

#include "../repository/CSVTaskRepository.h"
#include "../repository/JSONTaskRepository.h"
#include "../domain/Specification.h"

class TaskController {
private:
    TaskRepository& repo;

public:
    TaskController(TaskRepository& repo) : repo(repo) {}

    void addTask(const QString& description);
    void removeTask(int index);
    void updateTask(int index, const QString& description);
    void toggleCompletion(int index);
    void insertTaskAt(int index, const Task& task);
    const std::vector<Task>& getAllTasks() const;

    std::vector<Task> filterTasks(const Specification& spec) const;
};



#endif //TASKCONTROLLER_H
