#include "product.h"

//! Стандартный конструктор класса User
Product::Product()
{

}

//! Конструктор, принимающий параметры для создания объекта
//! класса Product
Product::Product(QString name, QString place, QString placefrom, QString timefrom, QString price)
    : mName(name)
    , mPlace(place)
    , mPlacefrom(placefrom)
    , mPrice(price)
    , mTimefrom(timefrom)
{
}

//! Функция для получения названия товара
const QString &Product::name() const {
    return mName;
}

//! Функция для присваивания названия товара
void Product::setName(const QString &name) {
    mName = name;
}

//! Функция для получения места расположения товара
const QString &Product::place() const {
    return mPlace;
}

//! Функция для присваивания места расположения товара
void Product::setPlace(const QString &place) {
    mPlace = place;
}

//! Функция для получения места ценника товара
const QString &Product::price() const {
    return mPrice;
}

//! Функция для присваивания места ценника товара
void Product::setPrice(const QString &price) {
    mPrice = price;
}

//! Функция для получения места прибытия товара
const QString &Product::placefrom() const {
    return mPlacefrom;
}

//! Функция для присваивания места прибытия товара
void Product::setPlacefrom(const QString &placefrom) {
    mPlacefrom = placefrom;
}

//! Функция для получения время прибытия товара
const QString &Product::timefrom() const {
    return mTimefrom;
}

//! Функция для присваивания время прибытия товара
void Product::setTimefrom(const QString &timefrom) {
    mTimefrom = timefrom;
}

//! Перегрузка опреатора считывания из файла
QDataStream &operator >>(QDataStream &ist, Product &product)
{
    ist >> product.mName
        >> product.mPlace
        >> product.mPlacefrom
        >> product.mTimefrom
        >> product.mPrice;

    //! возвращает поток данных
    return ist;
}

//! Перегрузка опреатора записи в файл
QDataStream &operator <<(QDataStream &ost, const Product &product)
{
    ost << product.mName
        << product.mPlace
        << product.mPlacefrom
        << product.mTimefrom
        << product.mPrice;

    //! возвращает поток данных
    return ost;
}
