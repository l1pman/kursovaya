#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

//! Стандартные библиотеки QT для оперирования с диалоговым окном,
//! а также создания предупреждающих сообщений при авторизации
#include <QDialog>
#include <QWidget>
#include <QMessageBox>

//! Работа с классами пользователя для авторизации
#include "user.h"
#include "users.h"

//! Стандартный конструктор для класса ui формы
namespace Ui {
class auth_window;
}
//! Рабочий конструктор с созданием и уничтожением
//! окна авторизации
class auth_window : public QDialog
{

    Q_OBJECT

public:
    //! конструктор создания данного окна
    explicit auth_window(Users *mUsers, int &idx, QWidget *parent = nullptr);

    //! деструктор данного окна
    ~auth_window();

    //! Метод для установки пользователь и его добавления в базу данных
    void set_user(User* check_user);

private slots:
    //! Слот о подтверждении введенных пользователем данных
    void on_auth_button_clicked();

private:
    //! Указатель на данное окно
    Ui::auth_window *ui;

    //! Создание администратора для его постоянного существования в программе
    User Admin;

    //! Указатель для установки пользователь (буфер)
    User *check_user;

    //! Указатель на базу данных, которая содержит в себе пользователей
    Users *mUsers;

    //! Адрес переменной, которая будет хранить в себе индекс
    //! текущего пользователя для дальнейшей работы с главным окном
    int &idx;

    //! Проверка на администратора в программе
    bool check_admin = false;
};

#endif // AUTH_WINDOW_H
