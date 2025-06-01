//
// Created by David Druja on 28.05.2025.
//

#include "MainWindow.h"
#include <QDebug>
#include <QMessageBox>

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
    QHBoxLayout* actionsLayout = new QHBoxLayout();

    // Widgets
    taskInput = new QLineEdit(this);
    addButton = new QPushButton("Add task", this);
    taskList = new QListWidget(this);
    removeButton = new QPushButton("Remove task", this);
    updateButton = new QPushButton("Update task", this);

    // Input Layout
    inputLayout->addWidget(taskInput);
    inputLayout->addWidget(addButton);

    // Actions Layout
    actionsLayout->addWidget(removeButton);
    actionsLayout->addWidget(updateButton);

    // Main Layout
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(actionsLayout);
    mainLayout->addWidget(taskList);

    central->setLayout(mainLayout);
}

void MainWindow::connectSignals() {
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddTask);
    connect(taskList, &QListWidget::itemChanged, this, &MainWindow::onItemChanged);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveTask);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateTask);
}

void MainWindow::refreshUI() {
    taskList->clear();
    const auto& tasks = controller.getAllTasks();

    for (size_t i = 0; i < tasks.size(); ++i) {
        const auto& task = tasks[i];
        QListWidgetItem* item = new QListWidgetItem(task.getDescription());
        if (task.getCompleted()) {
            item->setCheckState(Qt::Checked);
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

void MainWindow::onItemChanged(QListWidgetItem* item) {
    int index = item->data(Qt::UserRole).toInt();
    bool isChecked = item->checkState() == Qt::Checked;

    const auto& tasks = controller.getAllTasks();
    if (index >= 0 && static_cast<size_t>(index) < tasks.size()) {
        if (tasks[index].getCompleted() != isChecked) {
            controller.toggleCompletion(index);
        }
    }
}

void MainWindow::onRemoveTask() {
    QListWidgetItem* item = taskList->currentItem();

    if (!item) {
        QMessageBox::warning(this, "Removing task", "Task not found!");
        return;
    }

    controller.removeTask(item->data(Qt::UserRole).toInt());
    refreshUI();
}

void MainWindow::onUpdateTask() {
    QListWidgetItem* item = taskList->currentItem();

    if (!item) {
        QMessageBox::warning(this, "Update task", "Task not found!");
        return;
    }

    QString text = taskInput->text();
    if (!text.isEmpty()) {
        controller.updateTask(item->data(Qt::UserRole).toInt(), text);
        taskInput->clear();
        refreshUI();
    }
}