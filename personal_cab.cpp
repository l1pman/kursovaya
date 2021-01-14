#include "personal_cab.h"
#include "ui_personal_cab.h"

personal_cab::personal_cab(User &current_user, Users *mUsers, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::personal_cab)
{
    ui->setupUi(this);

    this->mUsers = mUsers;

    //! Создаем указатель на окно смены пароля
    pass_change = new password_change(current_user, mUsers, this);

    //! Делаем поля данных о пользователе неизменнымии
    ui->current_login_edit->setReadOnly(true);
    ui->current_password_edit->setReadOnly(true);

    //! Показываем данные о пользователе
    ui->current_login_edit->setText(current_user.login());
    ui->current_password_edit->setText(current_user.role());
}

personal_cab::~personal_cab()
{
    delete ui;
}

//! Метод класса для возвращения
//! в главное окно
void personal_cab::on_back_clicked()
{
    QMainWindow *parent_window = dynamic_cast<QMainWindow*>(parent());
    parent_window->show();
    close();
}

//! Метод класса для изменения пароля
//! в личном кабинете
void personal_cab::on_change_password_clicked()
{
    int res;

    res = pass_change->exec();

    if (res != QDialog::Accepted)
        pass_change->close();

}
