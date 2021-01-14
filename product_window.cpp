#include "product_window.h"
#include "mainwindow.h"
#include "ui_product_window.h"
#include "product.h"
#include "add_product.h"

product_window::product_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::product_window)
{
    ui->setupUi(this);

    //! Устанавливаем значение размера окна и заголовок его
    this->setWindowTitle("Окно товаров");
    this->setFixedSize(809,403);
    // Настраиваем таблицу заметок, чтобы её последняя колонка занимала всё доступное место

    ui->product_table->setModel(&mProducts);
}

product_window::~product_window()
{
    delete ui;
}

//! Кнопка возварата назад
void product_window::on_back_button_clicked()
{
    MainWindow *parent_window = dynamic_cast<MainWindow*>(parent());
    parent_window->show();
    close();
}

void product_window::save_data()
{
    mProducts.save();
}

void product_window::load_data()
{
    mProducts.load();
}

//! Добавление товара в вектор товаров
void product_window::on_add_product_clicked()
{
    int res;
    Product newProduct;

    add_product addproductWindow(this);
    addproductWindow.set_product(&newProduct);

    res = addproductWindow.exec();

    if (res == QDialog::Accepted)
        mProducts.add(newProduct);

}

void product_window::on_delete_product_clicked()
{
    int ask = QMessageBox::question(this,
                                      QString("Warning"),
                                      QString("Вы действительно хотите удалить товар со склада?"),
                                      QMessageBox::Yes | QMessageBox::No);
    if (ask == QMessageBox::Yes){
        // Для хранения номеров строк создаём STL-контейнер "множество", элементы
        // которого автоматически упорядочиваются по возрастанию
        std::set<int> rows;{
            // Получаем от таблицы заметок список индексов выбранных в настоящий момент
            // элементов
            QModelIndexList idc = ui->product_table->selectionModel()->selectedRows();
            // Вставляем номера выбранных строк в rows
            for (const auto &i : idc)
            {
                rows.insert(i.row());
            }
        }
        // Обходим множество номеров выбранных строк *по убыванию*, чтобы удаление предыдущих
        // не сбивало нумерацию следующих
        for (auto it = rows.rbegin(); it != rows.rend(); ++it){
            // Удаляем строку
            mProducts.erase(*it);
        }
    }
}

//! Функция поиска нашего товара в базе данных
void product_window::on_search_edit_textEdited(const QString &product_name)
{
    //! Разбиваем нашу строку на элементы и заполняем
    //! ей QStringList для посимвольного сравнения
    QStringList listStr = product_name.split(" ");
    listStr.removeAll(QString());

    //! Если товар не соответствует - скрывает строку
    for (size_t i = 0; i < mProducts.size(); ++i) {
        ui->product_table->showRow(i);
    }

    //! Подсчитываем количество строк
    int row = 0;

    //! Двойной цикл поиска товаров
    for (size_t i = 0; i < mProducts.size(); ++i) {
        int count = 0;
        foreach (const QString &str, listStr)
        {
            if (mProducts[i].name().contains(str) ||
                mProducts[i].place().contains(str) ||
                mProducts[i].placefrom().contains(str) ||
                mProducts[i].timefrom().contains(str) ||
                mProducts[i].price().contains(str))
            {
                count++;
            }
        }

        //! Скрываем товары, если не подходят вводу пользователя
        if (count != listStr.size()) {
            ui->product_table->hideRow(row);
        }
        row++;
    }
}
