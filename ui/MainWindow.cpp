//
// Created by David Druja on 28.05.2025.
//

#include "MainWindow.h"
#include <QDebug>
#include <QMessageBox>
#include "FilterDialog.h"
#include "../controller/AddTaskCommand.h"

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
    QHBoxLayout* filterLayout = new QHBoxLayout();

    // Widgets
    taskInput = new QLineEdit(this);
    addButton = new QPushButton("Add task", this);
    taskList = new QListWidget(this);
    removeButton = new QPushButton("Remove task", this);
    updateButton = new QPushButton("Update task", this);
    filterButton = new QPushButton("Advanced Filter", this);
    resetFilterButton = new QPushButton("Reset filter", this);
    showUncompletedButton = new QPushButton("Show uncompleted", this);

    // Input Layout
    inputLayout->addWidget(taskInput);
    inputLayout->addWidget(addButton);

    // Actions Layout
    actionsLayout->addWidget(removeButton);
    actionsLayout->addWidget(updateButton);

    // Filter Layout
    filterLayout->addWidget(showUncompletedButton);
    filterLayout->addWidget(filterButton);
    filterLayout->addWidget(resetFilterButton);

    // Main Layout
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(actionsLayout);
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(taskList);

    central->setLayout(mainLayout);
}

void MainWindow::connectSignals() {
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddTask);
    connect(taskList, &QListWidget::itemChanged, this, &MainWindow::onItemChanged);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveTask);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateTask);
    connect(filterButton, &QPushButton::clicked, this, &MainWindow::onFilterTasks);
    connect(resetFilterButton, &QPushButton::clicked, this, &MainWindow::onResetFilter);
    connect(showUncompletedButton, &QPushButton::clicked, this, &MainWindow::onShowUncompleted);
}

void MainWindow::refreshUI() {
    taskList->clear();
    const auto& tasks = isFiltered ? filteredTasks : controller.getAllTasks();

    for (size_t i = 0; i < tasks.size(); ++i) {
        const auto& task = tasks[i];
        QListWidgetItem* item = new QListWidgetItem(task.getDescription());
        item->setCheckState(task.getCompleted() ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole, static_cast<int>(i));
        taskList->addItem(item);
    }

    qDebug() << "Displayed tasks:" << tasks.size();
}

void MainWindow::onAddTask() {
    QString text = taskInput->text();
    if (!text.isEmpty()) {
        qDebug() << "Adding task: " << text;
        auto cmd = std::make_shared<AddTaskCommand>(controller, text);
        commandManager.executeCommand(cmd);
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

void MainWindow::onFilterTasks() {
    FilterDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        auto keyword = dialog.getKeyword();
        bool useCompletion = dialog.isCompletionChecked();
        bool isAnd = dialog.isAndCondition();

        Specification* keywordSpec = nullptr;
        Specification* completionSpec = nullptr;

        if (!keyword.isEmpty())
            keywordSpec = new DescriptionContainsSpecification(keyword);

        if (useCompletion)
            completionSpec = new CompletionSpecification(true);

        Specification* finalSpec = nullptr;
        if (keywordSpec && completionSpec) {
            if (isAnd)
                finalSpec = new AndSpecification(*keywordSpec, *completionSpec);
            else
                finalSpec = new OrSpecification(*keywordSpec, *completionSpec);
        } else if (keywordSpec) {
            finalSpec = keywordSpec;
        } else if (completionSpec) {
            finalSpec = completionSpec;
        }

        if (finalSpec) {
            filteredTasks = controller.filterTasks(*finalSpec);
            isFiltered = true;
            refreshUI();
        }

        delete keywordSpec;
        delete completionSpec;
        if (finalSpec != keywordSpec && finalSpec != completionSpec) {
            delete finalSpec;
        }
    }
}

void MainWindow::onResetFilter() {
    isFiltered = false;
    refreshUI();
}

void MainWindow::onShowUncompleted() {
    Specification* spec = new CompletionSpecification(false);  // false = not completed
    filteredTasks = controller.filterTasks(*spec);
    isFiltered = true;
    refreshUI();
    delete spec;
}