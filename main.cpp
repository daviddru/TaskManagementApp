#include <QApplication>
#include "repository/CSVTaskRepository.h"
#include "repository/JSONTaskRepository.h"
#include "controller/TaskController.h"
#include "ui/MainWindow.h"
#include "tests/test.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icons/resources/icon.png"));

    // CSVTaskRepository csvRepo("save.csv");
    // TaskController controller(csvRepo);

    QString savePath = QCoreApplication::applicationDirPath() + "/save.json";
    JSONTaskRepository jsonRepo(savePath);
    TaskController controller(jsonRepo);

    MainWindow window(controller);

    window.setWindowTitle("Task Management App");
    window.resize(550,450);
    window.show();

    // UNCOMMENT FOR TESTS AT LAUNCH
    // testAll();

    return app.exec();
}