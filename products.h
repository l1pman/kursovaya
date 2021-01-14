#ifndef PRODUCTS_H
#define PRODUCTS_H

//! Подключение класса Product для работы с товарами
#include "product.h"

//! Подключение основной библиотеки для работы с таблицей
//! и отображением содержимого вектора в ней, а также
//! подключение библиотеки для работы с потоками
#include <QAbstractTableModel>
#include <QDataStream>

//! Для реализации базы данных, данный класс наследует
//! от QAbstractTableModel, что позволяет сделать из нашей
//! таблицы некий аналог QTableWidget, который мы можем корректировать
//! в зависимости от требований к нашей программе, так как сам класс
//! QTableWidget наследует классы QTableView - который и отображает содержимое
//! нашей таблицы, а также QAbstractTableModel, который за счёт абстракции позволяет
//! задать параметры нашей таблицы (количество столбцов и строк, название, а также
//! заголовки нашей таблицы и т.д.
class Products : public QAbstractTableModel
{
    Q_OBJECT;
public:
    //! Стандартные конструктор и деструктор нашего класса
    Products();
    ~Products();

    //! Методы класса, позволяющие отображать нужное количество строк
    //! и столбцов в данной таблице
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    //! Методы, позволяющие отображать строки нашей таблицы, а также функция, которая
    //! устанавливает заголовки наших столбцов
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    //! Метод, позволяющий определить размер нашей базы данных
    size_t size();

    //! Перегрузка оператора квадратных скобок для обращения
    //! к объекту нашего класса по индексу
    const Product &operator[](size_t idx) const;

    //! Методы класса, позволяющие добавлять и удалять товар
    //! соответственно
    void add(Product product);
    void erase(size_t idx);

    //! Методы класса, позволяющие загружать и выгружать информацию
    //! нашего вектора в базу данных(бинарный файл)
    void load();
    void save();

private:
    //! Создания объекта класса QVector для хранения товаров
    //! в программе
    QVector<Product> mProducts;
};

#endif // PRODUCTS_H
