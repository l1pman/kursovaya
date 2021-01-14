
//! подключение нужных библиотек для работы с методами классов
#include "user.h"
#include "ui_add_product.h"
#include "add_product.h"
#include "product_window.h"

//! Конструктор данного класс
add_product::add_product(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_product)
{
    ui->setupUi(this);

    //! Устанавливается заголовок окна и фиксированное значение
    this->setWindowTitle("Добавление товара");
    this->setFixedSize(400, 300);
}

//! Деструктор данного класса
add_product::~add_product()
{
    delete ui;
}

//! Метод, устанавливающий значение товара
void add_product::set_product(Product* new_product)
{
    this->new_product = new_product;
}

//! Метод класса, устанавливающий значение объекта
//! класса по указателю, также внутри данного метода проводить
//! проверка параметров введённых пользователем, если данные пусты -
//! выведеться сообщение об ошибке, если введена отрицательная
//! цена - выведеться собщеие об ошибке, также оно выведется,
//! если какой-то из параметров задан некорректно
void add_product::on_addProduct_clicked()
{
    QDateTime current_time = QDateTime::currentDateTime();

    new_product->setName(ui->name->text());
    new_product->setPlace(ui->place->text());
    new_product->setPlacefrom(ui->placefrom->text());
    new_product->setPrice(ui->price->text());
    new_product->setTimefrom(current_time.toString());

    if (new_product->name() == "" ||
        new_product->place() == "" ||
        new_product->placefrom() == "" ||
        new_product->price() == "" ||
        new_product->timefrom() == "")
    {
        //! Создание сообщения об ошибке, а также функция,
        //! создающее само окно, предупреждающее пользо-
        //! вателя об ошибке
        QString warning_message = "Какое-либо поле не заполнено!";
        create_warning_box(warning_message, this);

        //! Обнуление полей вводимых пользователем
        ui->name->clear();
        ui->place->clear();
        ui->placefrom->clear();
        ui->price->clear();
    }
    else if (new_product->price().toInt() <= 0)
    {
        //! Создание сообщения об ошибке, а также функция,
        //! создающее само окно, предупреждающее пользо-
        //! вателя об ошибке
        QString warning_message = "Цена товара не может быть отрицательной\nили бесплатна!";
        create_warning_box(warning_message, this);

        //! Обнуление полей вводимых пользователем
        ui->name->clear();
        ui->place->clear();
        ui->placefrom->clear();
        ui->price->clear();
    }
    else if (new_product->name().size() > 15 || new_product->name().size() < 4)
    {
        //! Создание сообщения об ошибке, а также функция,
        //! создающее само окно, предупреждающее пользо-
        //! вателя об ошибке
        QString warning_message = "Некорректное название товара!";
        create_warning_box(warning_message, this);

        //! Обнуление полей вводимых пользователем
        ui->name->clear();
        ui->place->clear();
        ui->placefrom->clear();
        ui->price->clear();
    }
    else if (new_product->place().size() != 2)
    {
        //! Создание сообщения об ошибке, а также функция,
        //! создающее само окно, предупреждающее пользо-
        //! вателя об ошибке
        QString warning_message = "Некорректное положение на складе!";
        create_warning_box(warning_message, this);

        //! Обнуление полей вводимых пользователем
        ui->name->clear();
        ui->place->clear();
        ui->placefrom->clear();
        ui->price->clear();
    }
    else if (new_product->placefrom().size() > 13 || new_product->placefrom().size() < 3)
    {
        //! Создание сообщения об ошибке, а также функция,
        //! создающее само окно, предупреждающее пользо-
        //! вателя об ошибке
        QString warning_message = "Некорректное название города!";
        create_warning_box(warning_message, this);

        //! Обнуление полей вводимых пользователем
        ui->name->clear();
        ui->place->clear();
        ui->placefrom->clear();
        ui->price->clear();
    }
    else
        accept();
}

void add_product::on_back_clicked()
{
    reject();
}

//! Данный метод создает сообщение об ошибке, и на вход принимает
//! параметры: само сообщение, выводимое пользователю, а также указатель
//! на объект родителя
void add_product::create_warning_box(QString &warning_message, QWidget *parent)
{
    QMessageBox fillRows(parent);
    fillRows.setIcon(QMessageBox::Warning);
    fillRows.setWindowTitle("Ошибка");
    fillRows.setText(warning_message);
    fillRows.setStandardButtons(QMessageBox::Discard);
    fillRows.exec();
}
