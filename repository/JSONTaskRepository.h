//
// Created by David Druja on 01.06.2025.
//

#ifndef JSONTASKREPOSITORY_H
#define JSONTASKREPOSITORY_H

#include "TaskRepository.h"
#include <QString>
#include <vector>

class JSONTaskRepository : public TaskRepository {
private:
    QString filePath;
    std::vector<Task> tasks;

public:
    explicit JSONTaskRepository(const QString& filePath);

    void addTask(const Task& task) override;
    void removeTask(int index) override;
    void updateTask(int index, const Task& task) override;
    void toggleCompletion(int index) override;
    const std::vector<Task>& getAllTasks() const override;
    void insertTaskAt(int index, const Task &task) override;

    void save() const override;
    void load() override;
};

#endif // JSONTASKREPOSITORY_H
