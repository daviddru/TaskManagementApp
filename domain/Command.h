//
// Created by David Druja on 03.06.2025.
//

#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

#endif //COMMAND_H
