#include <QApplication>
#include "repository/taskrepository.h"
#include "controller/taskcontroller.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TaskRepository repo;
    TaskController controller(repo);
    MainWindow window(controller);

    window.setWindowTitle("Task Management App");
    window.resize(400,300);
    window.show();

    return app.exec();
}