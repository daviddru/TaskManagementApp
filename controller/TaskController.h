//
// Created by David Druja on 28.05.2025.
//

#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H

#include "../repository/CSVTaskRepository.h"
#include "../repository/JSONTaskRepository.h"

class TaskController {
private:
    JSONTaskRepository& repo;
    // CSVTaskRepository& repo;

public:
    TaskController(JSONTaskRepository& repo) : repo(repo) {}
    // TaskController(CSVTaskRepository& repo) : repo(repo) {}

    void addTask(const QString& description);
    void removeTask(int index);
    void updateTask(int index, const QString& description);
    void toggleCompletion(int index);
    const std::vector<Task>& getAllTasks() const;
};



#endif //TASKCONTROLLER_H
