//
// Created by David Druja on 01.06.2025.
//

#ifndef CSVTASKREPOSITORY_H
#define CSVTASKREPOSITORY_H
#include "TaskRepository.h"


class CSVTaskRepository : public TaskRepository {
private:
    std::vector<Task> tasks;
    QString filePath;

public:
    CSVTaskRepository(const QString filePath);

    void addTask(const Task& task) override;
    void removeTask(int index) override;
    void updateTask(int index, const Task &task) override;
    const std::vector<Task>& getAllTasks() const override;
    void insertTaskAt(int index, const Task &task) override;
    void toggleCompletion(int index) override;

    void save() const override;
    void load() override;
};



#endif //CSVTASKREPOSITORY_H
