//
// Created by David Druja on 28.05.2025.
//

#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(TaskController& controller, QWidget *parent)
    : QMainWindow(parent), controller(controller) {
    setupUI();
    connectSignals();
    refreshUI();
}

void MainWindow::setupUI() {
    QWidget* central = new QWidget(this);
    this->setCentralWidget(central);

    // Layouts
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* inputLayout = new QHBoxLayout();

    // Widgets
    taskInput = new QLineEdit(this);
    addButton = new QPushButton("Add task", this);
    taskList = new QListWidget(this);

    // Input Layout
    inputLayout->addWidget(taskInput);
    inputLayout->addWidget(addButton);

    // Main Layout
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(taskList);

    central->setLayout(mainLayout);
}

void MainWindow::connectSignals() {
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddTask);
    connect(taskList, &QListWidget::itemDoubleClicked, this, &MainWindow::onTaskDoubleClicked);
}

void MainWindow::refreshUI() {
    taskList->clear();
    const auto& tasks = controller.getAllTasks();

    for (size_t i = 0; i < tasks.size(); ++i) {
        const auto& task = tasks[i];
        QListWidgetItem* item = new QListWidgetItem(task.getDescription());
        if (task.getCompleted()) {
            item->setCheckState(Qt::Checked);
            item->setForeground(Qt::gray);
        }
        else {
            item->setCheckState(Qt::Unchecked);
        }
        item->setData(Qt::UserRole, static_cast<int>(i));
        taskList->addItem(item);
    }
    qDebug() << "Total tasks:" << tasks.size();
}

void MainWindow::onAddTask() {
    QString text = taskInput->text();
    if (!text.isEmpty()) {
        qDebug() << "Adding task: " << text;
        controller.addTask(text);
        taskInput->clear();
        refreshUI();
    }
}

void MainWindow::onTaskDoubleClicked(QListWidgetItem* item) {
    int index = item->data(Qt::UserRole).toInt();

    controller.toggleCompletion(index);
    refreshUI();
}