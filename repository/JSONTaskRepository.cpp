//
// Created by David Druja on 01.06.2025.
//

#include "JSONTaskRepository.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>

JSONTaskRepository::JSONTaskRepository(const QString& filePath)
    : filePath(filePath) {
    load();
}

void JSONTaskRepository::addTask(const Task& task) {
    tasks.push_back(task);
    save();
}

void JSONTaskRepository::removeTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
        save();
    }
}

void JSONTaskRepository::updateTask(int index, const Task& task) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index] = task;
        save();
    }
}

void JSONTaskRepository::toggleCompletion(int index) {
    if (index < tasks.size() && index >= 0) {
        if (tasks[index].getCompleted()) {
            tasks[index].setCompleted(false);
        }
        else {
            tasks[index].setCompleted(true);
        }
    }
    save();
}

const std::vector<Task>& JSONTaskRepository::getAllTasks() const {
    return tasks;
}

void JSONTaskRepository::save() const {
    QJsonArray taskArray;
    for (const Task& task : tasks) {
        QJsonObject taskObject;
        taskObject["description"] = task.getDescription();
        taskObject["completed"] = task.getCompleted();
        taskArray.append(taskObject);
    }

    QJsonDocument taskDocument(taskArray);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly) | QIODevice::Truncate) {
        file.write(taskDocument.toJson());
        file.close();
    }
}

void JSONTaskRepository::load() {
    tasks.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument taskDocument = QJsonDocument::fromJson(data);
    if (taskDocument.isArray()) {
        QJsonArray taskArray = taskDocument.array();
        for (const QJsonValue& value : taskArray) {
            if (value.isObject()) {
                QJsonObject taskObject = value.toObject();
                Task task(taskObject["description"].toString(), taskObject["completed"].toBool());
                tasks.push_back(task);
            }
        }
    }
}

void JSONTaskRepository::insertTaskAt(int index, const Task& task) {
    if (index >= 0 && index <= static_cast<int>(tasks.size())) {
        tasks.insert(tasks.begin() + index, task);
        save();
    }
}