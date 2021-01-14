#ifndef PRODUCT_H
#define PRODUCT_H

//! Подключение стандартных библиотек для работы со строками,
//! обработки потоков и времени
#include <QVariant>
#include <QString>
#include <QDateTime>
#include <QFile>

class Product
{
public:
    //! стандартный конустркутор нашего класса
    Product();

    //! конструктор, определяющий параметры товара, которые будут отображаться в таблице
    Product(QString name, QString place, QString placefrom, QString timefrom, QString price);

    //! возвращает название товара
    const QString &name() const; // getter

    //! устанавливаем название товара, равное name
    void setName(const QString &name); // setter

    //! возвращает место товара на складе
    const QString &place() const;

    //! устанавливаем место товара на складе
    void setPlace(const QString &place);

    //! возвращает место, откуда товар прибыл
    const QString &placefrom() const;

    //! устанавливаем место прибытия товара
    void setPlacefrom(const QString &placefrom);

    //! получаем время прибытия товара
    const QString &timefrom() const;

    //! устанавливаем время прибытия товара
    void setTimefrom(const QString &timefrom);

    //! возвращает цену товара
    const QString &price() const;

    //! устанавливаем цену товара
    void setPrice(const QString &price);

    //! Перегрузка оператора считывания из бинарного файла
    friend QDataStream &operator >>(QDataStream &ist, Product &product);

    //! Перегрузка оператора запись в бинарный файл
    friend QDataStream &operator <<(QDataStream &ost, const Product &product);

private:
    //! Приватные параметры класса User
    QString mName, mPlace, mPlacefrom, mPrice, mTimefrom;
};

#endif // PRODUCT_H
