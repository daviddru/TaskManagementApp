//
// Created by David Druja on 03.06.2025.
//

#ifndef REMOVETASKCOMMAND_H
#define REMOVETASKCOMMAND_H

#include "../domain/Command.h"
#include "../controller/TaskController.h"
#include "../domain/Task.h"

class RemoveTaskCommand : public Command {
private:
    TaskController& controller;
    int taskIndex;
    Task removedTask;

public:
    RemoveTaskCommand(TaskController& controller, int index)
        : controller(controller), taskIndex(index), removedTask(controller.getAllTasks().at(index)) {}

    void execute() override {
        const auto& allTasks = controller.getAllTasks();
        if (taskIndex >= 0 && static_cast<size_t>(taskIndex) < allTasks.size()) {
            removedTask = allTasks[taskIndex];
            controller.removeTask(taskIndex);
        }
    }

    void undo() override {
        controller.insertTaskAt(taskIndex, removedTask); // assumes insertTaskAt exists
    }
};


#endif //REMOVETASKCOMMAND_H
