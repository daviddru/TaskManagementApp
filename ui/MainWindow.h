//
// Created by David Druja on 28.05.2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    QLineEdit* taskInput;
    QPushButton* addButton;
    QListWidget* taskList;
    QPushButton* removeButton;
    QPushButton* updateButton;

    void setupUI();
    void connectSignals();
    void refreshUI();

private slots:
    void onAddTask();
    void onTaskDoubleClicked(QListWidgetItem* item);
    void onRemoveTask();
    void onUpdateTask();

public:
    MainWindow(TaskController& controller, QWidget* parent = nullptr);
};



#endif //MAINWINDOW_H
