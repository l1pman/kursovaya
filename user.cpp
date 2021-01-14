#include "user.h"

//! Стандартный конструктор класса User
User::User()
{

}

//! Конструктор, принимающий параметры для создания объекта
//! класса User
User::User(QString login, QString password, QString role)
    : mLogin(login)
    , mPassword(password)
    , mRole(role)
{
}

//! Функция для получения логина пользователя
const QString &User::login() const {
    return mLogin;
}

//! Функция для присваивания логина пользователю
void User::setLogin(const QString &login) {
    mLogin = login;
}

//! Функция для получения пароля пользователя
const QString &User::password() const {
    return mPassword;
}

//! Функция для присваивания пароля пользователю
void User::setPassword(const QString &password) {
    mPassword = password;
}

//! Функция для получения должности пользователя
const QString &User::role() const {
    return mRole;
}

//! Функция для присваивания должности пользователю
void User::setRole(const QString &role) {
    mRole = role;
}

//! Перегрузка оператора считвания из файла
QDataStream &operator >>(QDataStream &ist, User &user)
{
    ist >> user.mLogin
        >> user.mPassword
        >> user.mRole;
    return ist;
}

//! Перегрузка оператора записи в файл
QDataStream &operator <<(QDataStream &ost, const User &user)
{
    ost << user.mLogin
        << user.mPassword
        << user.mRole;
    return ost;
}
