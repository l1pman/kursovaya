#ifndef PERSONAL_CAB_H
#define PERSONAL_CAB_H

#include "mainwindow.h"
#include "user.h"
#include "password_change.h"
#include "users.h"

#include <QMainWindow>

namespace Ui {
class personal_cab;
}

class personal_cab : public QMainWindow
{
    Q_OBJECT

public:
    explicit personal_cab(User &current_user, Users *mUsers, QWidget *parent = nullptr);
    ~personal_cab();

private slots:
    void on_back_clicked();

    void on_change_password_clicked();

private:
    Ui::personal_cab *ui;

    password_change *pass_change;

    User *current_user;

    Users *mUsers;
};

#endif // PERSONAL_CAB_H
