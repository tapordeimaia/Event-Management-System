#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtLifeAfterSchool.h"

class QtLifeAfterSchool : public QMainWindow
{
    Q_OBJECT

public:
    QtLifeAfterSchool(QWidget* parent = nullptr);
    ~QtLifeAfterSchool();

private:
    Ui::QtLifeAfterSchoolClass ui;
};