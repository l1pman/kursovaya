#ifndef ADD_USER_H
#define ADD_USER_H

//! Подключение класса User для дальнейших оппераций
//! с пользователями - их добавление и удаление
#include "user.h"
#include "add_product.h"

//! Стандартная библиотека от которой наследуется данный
//! вижджет QDialog - одна из стандартных форма окна
#include <QDialog>

//! Стандартный конструктор для класса ui формы
namespace Ui {
class add_user;
}

//! Рабочий конструктор с созданием и уничтожением
//! Окна добавления пользователя
class add_user : public QDialog
{
    Q_OBJECT

public:
    //! конструктор создания данного окна
    explicit add_user(QWidget *parent = nullptr);
    ~add_user();

    //! Функция для установления значения пользователя в буфере
    void set_user(User* new_user);

    //! Функция создания сообщения для пользователя о предупреждении
    void create_warning_box_user(QString &warning_message, QWidget *parent);

private slots:
    //! Приватные слоты - кнопки данного ui объекта
    void on_addUser_clicked();

    void on_back_clicked();

private:
    //! Переменная-указатель для работы с буферным пользователем
    User *new_user;

    //! Указатель на данную ui форму
    Ui::add_user *ui;
};

#endif // ADD_USER_H
