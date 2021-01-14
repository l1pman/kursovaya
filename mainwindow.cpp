#include <iostream>
#include <string>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personal_cab.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //! Устанавливаем заголовок и размер окна
    this->setWindowTitle("Главное меню");
    this->setFixedSize(454, 335);

    //! Присваиваем указетлям окна их типа данных
    //! и создаем их, для того чтобы вызывать в нужный момент
    aw = new admin_window(&mUsers, this);

    pw = new product_window(this);

    int res, idx;

    auth_w = new auth_window(&mUsers, idx, this);

    res = auth_w->exec();

    if (res != QDialog::Accepted)
    {
        exit(res);
    }
    else
        show();

    //! Значение текущего пользователя
    current_user = mUsers[idx];

    //! Указатель на личный кабинет
    pc = new personal_cab(current_user, &mUsers, this);

    //! Подключение прав администратора
    if (current_user.role() != "Администратор")
    {
        ui->admin_cab->hide();
    }
}

//! В деструкторе удаляются все указатели на окна
//! созданные в конструкторе (инициализированные)
MainWindow::~MainWindow()
{
    delete aw;
    delete pw;
    delete ui;
}

//! Открытие окна товаров
void MainWindow::on_products_clicked()
{
    hide();
    pw->show();
}

//! Открытие окна администратора
void MainWindow::on_admin_cab_clicked()
{
    hide();
    aw->show();
}

//! Открытие личного кабинета
void MainWindow::on_personal_cab_clicked()
{
    hide();
    pc->show();
}
