#ifndef PRODUCT_WINDOW_H
#define PRODUCT_WINDOW_H

//! Подключение классов товара и самой базы данных
#include "product.h"
#include "products.h"

//! Подключение стандартных библиотек C++
#include <set>
#include <stdexcept>
#include <istream>

//! Подключение QT библиотек, позволяющих работать
//! со временем, обработкой сообщений пользователю,
//! считыванию из потока, а также с виджетами типа таблицы
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTime>
#include <QFile>
#include <QMessageBox>
#include <QMainWindow>

//! Стандартный конструктор класса ui формы
namespace Ui {
class product_window;
};

//! Рабочий конструктор окна товаров
class product_window : public QMainWindow
{
    Q_OBJECT

public:
    //! Конструктор для создания ui формы
    explicit product_window(QWidget *parent = nullptr);

    //! Деструктор данного окна
    ~product_window();

    //! Методы для разметки таблицы - кол-во столбцов и строк
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    //! Абстрактные методы для сохранения и загрузки данных
    //! в файлы и из них
    void save_data();
    void load_data();

private slots:
    //! Приватные слоты - кнопки данного ui объекта
    void on_back_button_clicked();

    void on_add_product_clicked();

    void on_delete_product_clicked();

    void on_search_edit_textEdited(const QString &arg1);

private:
    //! Указатель на данное окно
    Ui::product_window *ui;

    //! Создание объекта класса Products,
    //! который является абстрактным классом
    //! и некой базой данных для хранения информации
    //! о товарах
    Products mProducts;
};

#endif // PRODUCT_WINDOW_H
