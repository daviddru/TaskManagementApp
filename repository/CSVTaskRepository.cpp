//
// Created by David Druja on 01.06.2025.
//

#include "CSVTaskRepository.h"
#include <QFile>
#include <QTextStream>
#include <exception>

CSVTaskRepository::CSVTaskRepository(const QString filePath) {
    this->filePath = filePath;
    load();
}

void CSVTaskRepository::addTask(const Task& task) {
    tasks.push_back(task);
    save();
}

void CSVTaskRepository::removeTask(int index) {
    if (index < tasks.size() && index >= 0) {
        tasks.erase(tasks.begin() + index);
        save();
    }
    else throw std::exception();
}

void CSVTaskRepository::updateTask(int index, const Task &task) {
    if (index < tasks.size() && index >= 0) {
        tasks[index] = task;
        save();
    }
    else throw std::exception();
}

const std::vector<Task>& CSVTaskRepository::getAllTasks() const {
    return tasks;
}

void CSVTaskRepository::toggleCompletion(int index) {
    if (index < tasks.size() && index >= 0) {
        if (tasks[index].getCompleted()) {
            tasks[index].setCompleted(false);
        }
        else {
            tasks[index].setCompleted(true);
        }
    }
    else throw std::exception();
    save();
}

void CSVTaskRepository::save() const {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);

    for (const Task& task : tasks) {
        out << task.getDescription() << ";" << (task.getCompleted() ? "1" : "0") << "\n";
    }
}

void CSVTaskRepository::load() {
    tasks.clear();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(";");
        if (parts.size() >= 2) {
            QString description = parts[0];
            bool completed = parts[1] == "1";

            Task temp = Task(description, completed);
            tasks.push_back(temp);
        }
    }
}

void CSVTaskRepository::insertTaskAt(int index, const Task& task) {
    if (index >= 0 && index <= static_cast<int>(tasks.size())) {
        tasks.insert(tasks.begin() + index, task);
        save();
    }
    else throw std::exception();
}