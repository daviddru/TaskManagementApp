//
// Created by David Druja on 28.05.2025.
//

#ifndef TASK_H
#define TASK_H

#include <QString>

class Task {
private:
    QString description;
    bool completed;

    public:
    Task(QString name, bool completed = false) : description(name), completed(completed) {}

    QString getDescription() const {
        return description;
    }

    bool getCompleted() const {
        return completed;
    }

    void setCompleted(bool completed) {
        this->completed = completed;
    }

    void setDescription(QString description) {
        this->description = description;
    }
};



#endif //TASK_H
