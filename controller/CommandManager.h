//
// Created by David Druja on 03.06.2025.
//

#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <stack>
#include <memory>
#include "../domain/Command.h"

class CommandManager {
private:
    std::stack<std::shared_ptr<Command>> undoStack;
    std::stack<std::shared_ptr<Command>> redoStack;

public:
    void executeCommand(std::shared_ptr<Command> cmd) {
        cmd->execute();
        undoStack.push(cmd);
        while (!redoStack.empty()) redoStack.pop();
    }

    void undo() {
        if (!undoStack.empty()) {
            auto cmd = undoStack.top();
            undoStack.pop();
            cmd->undo();
            redoStack.push(cmd);
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            auto cmd = redoStack.top();
            redoStack.pop();
            cmd->execute();
            undoStack.push(cmd);
        }
    }

    bool canUndo() const { return !undoStack.empty(); }
    bool canRedo() const { return !redoStack.empty(); }
};

#endif //COMMANDMANAGER_H
