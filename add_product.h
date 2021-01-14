#ifndef ADD_PRODUCT_H
#define ADD_PRODUCT_H


//! Подключение класса Product для дальнейших оппераций
//! с товарами - их добавление и удаление
#include "product.h"

//! Стандартные библиотеки QT для оперирования с сообщениями
//! об ошибке или предупреждениями, фиксирование времени и
//! подключение потоков для работы с файлами
#include <QDialog>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>

//! Стандартный конструктор для класса ui формы
namespace Ui {
class add_product;
}

//! Рабочий конструктор с созданием и уничтожением
//! Окна добавления товара
class add_product : public QDialog
{
    Q_OBJECT

public:
    explicit add_product(QWidget *parent = nullptr);

    ~add_product();

    //! Функция для установления значения продукта в буфере
    void set_product(Product* new_product);

    void create_warning_box(QString &warning_message, QWidget *parent);

private slots:
    //! Приватные слоты - кнопки данного ui объекта
    void on_addProduct_clicked();

    void on_back_clicked();

private:
    //! Переменная-указатель для работы с буферным пользователем
    Product *new_product;

    //! Указатель на данную ui форму
    Ui::add_product *ui;
};

#endif // ADD_PRODUCT_H
