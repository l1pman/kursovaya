#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H

//! Подключение класса Users для дальнейших оппераци
//! абстрактный класс для оперирования с QVector
#include "users.h"

//! Стандартные библиотеки QT для оперирования с таблицей
//! контроля связи между QVectorov и QTableWidgetItem
//! что позволяет отображать данные вектора в таблице
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

//! Стандартный конструктор для класса ui формы
namespace Ui {
class admin_window;
}

//! Рабочий конструктор с созданием и уничтожением
//! Окна добавления пользователя
class admin_window : public QMainWindow
{
    Q_OBJECT

public:
    //! конструктор создания данного окна
    explicit admin_window(Users *mUsers, QWidget *parent = nullptr);

    //! деструктор данного окна
    ~admin_window();

    //! функция загрузки данных из вектор из потока
    void load_data();

    //! функция сохранения данных в вектор из потока
    void save_data();

private slots:
    //! Приватные слоты - кнопки данного ui объекта
    void on_back_clicked();

    void on_add_user_clicked();

    void on_delete_usr_clicked();

private:
    //! Создание указателя на объект класса Users,
    //! который является абстрактным классом
    //! и некой базой данных для хранения информации
    //! о пользователях и администрирования программы
    Users *mUsers;

    //! Указатель на данную ui форму
    Ui::admin_window *ui;
};

#endif // ADMIN_WINDOW_H
