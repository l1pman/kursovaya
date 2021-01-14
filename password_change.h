#ifndef PASSWORD_CHANGE_H
#define PASSWORD_CHANGE_H

#include "user.h"
#include "users.h"

#include <QDialog>
#include <QString>
#include <QMessageBox>

namespace Ui {
class password_change;
}

class password_change : public QDialog
{
    Q_OBJECT

public:
    explicit password_change(User &current_user, Users *mUsers, QWidget *parent = nullptr);
    ~password_change();

private slots:

    void create_warning_box_user(QString &warning_message, QWidget *parent);

    void on_acc_clicked();

    void on_rej_clicked();

private:
    Ui::password_change *ui;

    User *current_user;

    Users *mUsers;
};

#endif // PASSWORD_CHANGE_H
