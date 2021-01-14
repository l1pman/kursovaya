#include "auth_window.h"
#include "ui_auth_window.h"

#include <iostream>

auth_window::auth_window(Users *mUsers, int &idx, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auth_window),
    idx(idx)
{
    ui->setupUi(this);

    //! Установка заголовка и размера окна
    this->setWindowTitle("Авторизация");
    this->setFixedSize(315, 270);

    //! Инициализурем указатель на нашу базу данных
    this->mUsers = mUsers;

    setModal(true);

    //! Задаем наши параметры для администратора
    //! чтобы наличие его в программе было всегда
    Admin.setRole("Администратор");
    Admin.setLogin("Nikolay");
    Admin.setPassword("11111");

    //! Поиск админисратора в базе данных
    for (size_t i = 0; i < mUsers->size(); ++i)
    {
        if (mUsers->get_user(i).login() == Admin.login())
        {
            check_admin = true;
        }
    }

    //! Если администратор найден, он не будет содаваться,
    //! иначе добавляется в вектор
    if (!check_admin)
        mUsers->add(Admin);
}

//! Деструктор данного класса
auth_window::~auth_window()
{
    delete ui;
}

//! Установка значения пользователя по указателю
void auth_window::set_user(User *check_user)
{
    this->check_user = check_user;
}


void auth_window::on_auth_button_clicked()
{
    //! Переменная для отслеживания, найден ли пользователь
    bool user_find = false;

    //! Проходим по вектору, для нахождения пользователя в
    //! базе данных
    for (size_t i = 0; i < mUsers->size(); ++i)
    {
        if (mUsers->get_user(i).login() == ui->usr_login->text() && mUsers->get_user(i).password() == ui->usr_password->text())
        {
            //! Если пользователь найден, то переменная становиться true
            user_find = true;

            //! Фиксируем индекс этого пользователя
            idx = i;
            accept();
        }
    }

    //! Если пользователь не найден, то выдается сообщение об
    //! этом пользователю
    if (!user_find){
         QMessageBox::warning(this, QString(tr("Ошибка")),
                              QString(tr("Логин или пароль не найден")),
                              QMessageBox::Ok);

         //! обнуляем поля, заполненные пользователем
         ui->usr_login->clear();
         ui->usr_password->clear();
    }
}
