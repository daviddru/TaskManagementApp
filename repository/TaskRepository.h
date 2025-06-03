//
// Created by David Druja on 28.05.2025.
//

#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H

#include "../domain/Task.h"
#include <vector>

class TaskRepository {
public:
    virtual void addTask(const Task& task) = 0;
    virtual void removeTask(int index) = 0;
    virtual void updateTask(int index, const Task& task) = 0;
    virtual void toggleCompletion(int index) = 0;
    virtual void insertTaskAt(int index, const Task& task) = 0;
    virtual const std::vector<Task>& getAllTasks() const = 0;

    virtual void save() const = 0;
    virtual void load() = 0;

    virtual ~TaskRepository() = default;
};



#endif //TASKREPOSITORY_H
