#include <QApplication>
#include "repository/CSVTaskRepository.h"
#include "repository/JSONTaskRepository.h"
#include "controller/TaskController.h"
#include "ui/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // CSVTaskRepository csvRepo("save.csv");
    // TaskController controller(csvRepo);

    JSONTaskRepository jsonRepo("save.json");
    TaskController controller(jsonRepo);

    MainWindow window(controller);

    window.setWindowTitle("Task Management App");
    window.resize(400,300);
    window.show();

    return app.exec();
}