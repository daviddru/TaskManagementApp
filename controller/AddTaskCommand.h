//
// Created by David Druja on 03.06.2025.
//

#ifndef ADDTASKCOMMAND_H
#define ADDTASKCOMMAND_H

#include "../domain/Command.h"
#include "TaskController.h"

class AddTaskCommand : public Command {
private:
    TaskController& controller;
    QString description;
    int addedIndex = -1;

public:
    AddTaskCommand(TaskController& ctrl, const QString& desc)
        : controller(ctrl), description(desc) {}

    void execute() override {
        controller.addTask(description);
        addedIndex = controller.getAllTasks().size() - 1;
    }

    void undo() override {
        if (addedIndex != -1)
            controller.removeTask(addedIndex);
    }
};

#endif //ADDTASKCOMMAND_H
