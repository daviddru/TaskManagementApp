//
// Created by David Druja on 02.06.2025.
//

#include "FilterDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>

FilterDialog::FilterDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Filter Tasks");
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Keyword:"));
    keywordEdit = new QLineEdit(this);
    layout->addWidget(keywordEdit);

    completionCheck = new QCheckBox("Completed?", this);
    layout->addWidget(completionCheck);

    layout->addWidget(new QLabel("Condition logic:"));
    logicCombo = new QComboBox(this);
    logicCombo->addItem("AND");
    logicCombo->addItem("OR");
    layout->addWidget(logicCombo);

    auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &FilterDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &FilterDialog::reject);
    layout->addWidget(buttonBox);
}

QString FilterDialog::getKeyword() const {
    return keywordEdit->text();
}

bool FilterDialog::getCompletionStatus() const {
    return completionCheck->isChecked();
}

bool FilterDialog::isCompletionChecked() const {
    return completionCheck->isChecked();
}

bool FilterDialog::isAndCondition() const {
    return logicCombo->currentText() == "AND";
}