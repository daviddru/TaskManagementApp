//
// Created by David Druja on 02.06.2025.
//

#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>

class FilterDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* keywordEdit;
    QCheckBox* completionCheck;
    QComboBox* logicCombo;

public:
    explicit FilterDialog(QWidget* parent = nullptr);

    QString getKeyword() const;
    bool getCompletionStatus() const;
    bool isCompletionChecked() const;
    bool isAndCondition() const;
};

#endif // FILTERDIALOG_H
