//
// Created by David Druja on 28.05.2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../controller/CommandManager.h"
#include "../controller/TaskController.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    TaskController& controller;
    CommandManager commandManager;

    QLineEdit* taskInput;
    QPushButton* addButton;
    QListWidget* taskList;
    QPushButton* removeButton;
    QPushButton* updateButton;
    QPushButton* filterButton;
    QPushButton* resetFilterButton;
    QPushButton* showUncompletedButton;
    QPushButton* undoButton;
    QPushButton* redoButton;

    std::vector<Task> filteredTasks;
    bool isFiltered;

    void setupUI();
    void connectSignals();
    void refreshUI() const;

private slots:
    void onAddTask();
    void onItemChanged(QListWidgetItem* item);
    void onRemoveTask();
    void onUpdateTask();
    void onFilterTasks();
    void onResetFilter();
    void onShowUncompleted();
    void onUndo();
    void onRedo();

public:
    MainWindow(TaskController& controller, QWidget* parent = nullptr);
};



#endif //MAINWINDOW_H
