#include <iostream>
#include <cassert>
#include <cstdio>

#include "../domain/Task.h"
#include "../repository/JSONTaskRepository.h"
#include "../repository/CSVTaskRepository.h"
#include "../controller/TaskController.h"
#include "../controller/AddTaskCommand.h"
#include "../controller/RemoveTaskCommand.h"
#include "../controller/UpdateTaskCommand.h"
#include "../controller/CommandManager.h"

// Utility to clear a file
void cleanFile(const QString& filePath) {
    std::remove(filePath.toStdString().c_str());
}

// ----------- Repository Basic Tests -----------

void testBasicOperations(TaskRepository& repo) {
    repo.addTask(Task("A", false));
    repo.addTask(Task("B", true));
    assert(repo.getAllTasks().size() == 2);

    repo.updateTask(0, Task("A-updated", true));
    assert(repo.getAllTasks()[0].getDescription() == "A-updated");
    assert(repo.getAllTasks()[0].getCompleted());

    repo.toggleCompletion(1);
    assert(!repo.getAllTasks()[1].getCompleted());

    repo.removeTask(0);
    assert(repo.getAllTasks().size() == 1);
    assert(repo.getAllTasks()[0].getDescription() == "B");

    repo.insertTaskAt(0, Task("Inserted", false));
    assert(repo.getAllTasks()[0].getDescription() == "Inserted");
}

// ----------- Edge Case Tests -----------

void testEdgeCases(TaskRepository& repo) {
    try {
        repo.updateTask(10, Task("Invalid", false));
        assert(false);  // Should not reach here
    } catch (...) {}

    try {
        repo.removeTask(-1);
        assert(false);
    } catch (...) {}

    try {
        repo.toggleCompletion(100);
        assert(false);
    } catch (...) {}

    repo.addTask(Task("", false));  // Empty description
    assert(repo.getAllTasks().back().getDescription().isEmpty());
}

// ----------- Persistence Test -----------

void testPersistence(TaskRepository& repo, const QString& path) {
    repo.addTask(Task("Persistent", true));
    repo.save();

    TaskRepository& newRepo = dynamic_cast<decltype(repo)&>(repo);
    newRepo.load();
    const auto& tasks = newRepo.getAllTasks();
    assert(!tasks.empty());
    assert(tasks.back().getDescription() == "Persistent");
}

// ----------- Controller + CommandManager Tests -----------

void testUndoRedo(TaskController& controller, CommandManager& manager) {
    assert(controller.getAllTasks().empty());

    auto addCmd = std::make_shared<AddTaskCommand>(controller, "UndoTest");
    manager.executeCommand(addCmd);
    assert(controller.getAllTasks().size() == 1);

    manager.undo();
    assert(controller.getAllTasks().empty());

    manager.redo();
    assert(controller.getAllTasks().size() == 1);

    controller.addTask("ToRemove");
    auto remCmd = std::make_shared<RemoveTaskCommand>(controller, 1);
    manager.executeCommand(remCmd);
    assert(controller.getAllTasks().size() == 1);

    manager.undo();
    assert(controller.getAllTasks().size() == 2);

    auto updCmd = std::make_shared<UpdateTaskCommand>(controller, 1, "UpdatedTask");
    manager.executeCommand(updCmd);
    assert(controller.getAllTasks()[1].getDescription() == "UpdatedTask");

    manager.undo();
    assert(controller.getAllTasks()[1].getDescription() == "ToRemove");
}

// ----------- High-level test for both types -----------

void runTestsForRepository(TaskRepository& repo, const QString& path) {
    repo.load();  // Ensure initial state is clean
    testBasicOperations(repo);
    testEdgeCases(repo);
    testPersistence(repo, path);
}

void testJSONRepository() {
    QString path = "json_test.json";
    cleanFile(path);
    JSONTaskRepository repo(path);
    runTestsForRepository(repo, path);
    std::cout << "✅ JSON repository tests passed.\n";
}

void testCSVRepository() {
    QString path = "csv_test.csv";
    cleanFile(path);
    CSVTaskRepository repo(path);
    runTestsForRepository(repo, path);
    std::cout << "✅ CSV repository tests passed.\n";
}

void testCommandFlowWithJSON() {
    QString path = "cmd_json.json";
    cleanFile(path);
    JSONTaskRepository repo(path);
    TaskController controller(repo);
    CommandManager manager;

    testUndoRedo(controller, manager);
    std::cout << "✅ Command pattern test (JSON) passed.\n";
}

void testCommandFlowWithCSV() {
    QString path = "cmd_csv.csv";
    cleanFile(path);
    CSVTaskRepository repo(path);
    TaskController controller(repo);
    CommandManager manager;

    testUndoRedo(controller, manager);
    std::cout << "✅ Command pattern test (CSV) passed.\n";
}

// ----------- Entrypoint -----------

void testAll() {
    testJSONRepository();
    testCSVRepository();
    testCommandFlowWithJSON();
    testCommandFlowWithCSV();
    std::cout << "✅ All tests passed.\n";
}