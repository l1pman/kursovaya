#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//! Основной класс окна типа главное окно
#include <QMainWindow>

//! Подключение классов программы для работы с ними из главного окна
#include "product_window.h"
#include "admin_window.h"
#include "auth_window.h"
#include "users.h"
#include "personal_cab.h"
#include "user.h"

class personal_cab;

//! Стандартный конструктор для класса ui формы
namespace Ui {
class MainWindow;
}

//! Рабочий конструктор главного окна
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Конструктор создания данного окна
    explicit MainWindow(QWidget *parent = nullptr);

    //! Деструктор данного окна
    ~MainWindow();

private slots:
    //! Приватные слоты - кнопки данного ui объекта
    void on_products_clicked();

    void on_admin_cab_clicked();

    void on_personal_cab_clicked();

private:
    //! Указатель на данное окно
    Ui::MainWindow *ui;

    //! Указатель на окно товаров
    product_window *pw;

    //! Указатель на окно администрирования
    admin_window *aw;

    //! Указатель на личный кабинет
    personal_cab *pc;

    //! Объект класса базы данных для пользователей
    Users mUsers;

    //! Указатель на окно авторизации
    auth_window *auth_w;

    //! Буферный объект класса user для определения текущего пользователя
    User current_user;
};

#endif // MAINWINDOW_H
