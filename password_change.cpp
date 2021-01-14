#include "password_change.h"
#include "ui_password_change.h"

password_change::password_change(User &current_user, Users *mUsers, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::password_change)
{
    ui->setupUi(this);

    this->current_user = &current_user;
    this->mUsers = mUsers;
}

password_change::~password_change()
{
    delete ui;
}

//! Функция формирования окна предупрждения
//! при неправильном вводе пользователя
void password_change::create_warning_box_user(QString &warning_message, QWidget *parent)
{
    QMessageBox fillRows(parent);
    fillRows.setIcon(QMessageBox::Warning);
    fillRows.setWindowTitle("Ошибка");
    fillRows.setText(warning_message);
    fillRows.setStandardButtons(QMessageBox::Discard);
    fillRows.exec();
}

//! Метод класса для изменения пароля пользователя
void password_change::on_acc_clicked()
{

    //! Проверка на корректность введения текущего пароля
    if (current_user->password() != ui->old_pas_edit->text())
    {
        QString warning_message = "Старый пароль введён неверно!";
        create_warning_box_user(warning_message, this);

        ui->old_pas_edit->clear();
        ui->new_pas_edit->clear();
        ui->accept_pas_edit->clear();
    }

    //! Проверка на совпадение и подтверждение
    //! нового пароля введенного пользователем
    else if (ui->new_pas_edit->text() != ui->new_pas_edit->text())
    {
        QString warning_message = "Новый пароль не совпадает!";
        create_warning_box_user(warning_message, this);

        ui->old_pas_edit->clear();
        ui->new_pas_edit->clear();
        ui->accept_pas_edit->clear();
    }
    else
    {
        //! Установка нового пароля для пользователя
        //! и замена его в базе данных
        current_user->setPassword(ui->new_pas_edit->text());
        for (size_t i = 0; i < mUsers->size(); ++i)
        {
            if (current_user->login() == (*mUsers)[i].login())
            {
                (*mUsers).replace(i, *current_user);
                (*mUsers).save();
            }
        }

        //! Сигнал о подтверждении
        accept();
    }
}

//! Метод отклонения QDialog
void password_change::on_rej_clicked()
{
    reject();
}
