//
// Created by David Druja on 28.05.2025.
//

#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H

#include "../domain/Task.h"
#include <vector>

class TaskRepository {
private:
    std::vector<Task> tasks;

public:
    void addTask(const Task& task);
    void removeTask(int index);
    void updateTask(int index, const Task& task);
    void toggleCompletion(int index);
    std::vector<Task>& getAllTasks();
};



#endif //TASKREPOSITORY_H
