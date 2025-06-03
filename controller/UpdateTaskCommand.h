//
// Created by David Druja on 03.06.2025.
//

#ifndef UPDATETASKCOMMAND_H
#define UPDATETASKCOMMAND_H

#include "../domain/Command.h"
#include "../domain/Task.h"
#include "TaskController.h"


class UpdateTaskCommand : public Command {
private:
    TaskController& controller;
    int index;
    Task newTask;
    Task oldTask;

public:
    UpdateTaskCommand(TaskController& controller, int index, const QString& newDescription)
        : controller(controller), index(index), oldTask(controller.getAllTasks().at(index)),
            newTask(newDescription, oldTask.getCompleted()) {}

    void execute() override {
        controller.updateTask(index, newTask.getDescription());
    }

    void undo() override {
        controller.updateTask(index, oldTask.getDescription());
    }
};

#endif //UPDATETASKCOMMAND_H
