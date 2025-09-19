#pragma once
#include "Command.h"
#include <stack>
#include <memory>
#include <QDebug>

class UndoRedoManager {
    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;

public:
    void execute(std::unique_ptr<Command> command) {
        command->execute();
        undoStack.push(std::move(command));
        qDebug() << "Undo stack size:" << undoStack.size();
        // Clear redo stack when new command is executed
        while (!redoStack.empty()) redoStack.pop();
    }

    void undo() {
        if (undoStack.empty()) return;
        auto command = std::move(undoStack.top());
        undoStack.pop();
        command->undo();
        redoStack.push(std::move(command));
    }

    void redo() {
        if (redoStack.empty()) return;
        auto command = std::move(redoStack.top());
        redoStack.pop();
        command->execute();  // Note: We call execute() for redo
        undoStack.push(std::move(command));
    }

    bool canUndo() const { return !undoStack.empty(); }
    bool canRedo() const { return !redoStack.empty(); }

    void clear() {
        while (!undoStack.empty()) undoStack.pop();
        while (!redoStack.empty()) redoStack.pop();
    }
};