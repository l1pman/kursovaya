#ifndef USER_H
#define USER_H


#include <QString>
#include <QDataStream>
#include <QFile>


class User
{
public:
    //! стандартный конустркутор нашего класса
    User();

    //! конструктор определения пользователя
    User(QString login, QString password, QString role);

    //! возвращает логин пользователя
    const QString &login() const;

    //! устанавливаем название товара, равное name
    void setLogin(const QString &login);

    //! возвращает пароль пользователя
    const QString &password() const;

    //! устанавливаем название товара, равное name
    void setPassword(const QString &password);

    //! устанавливаем роль пользователя в нашей программе
    const QString &role() const;

    //! метод для загрузки информации в файла
    void setRole(const QString &role);

    //! Метод для возвращения пользователя
    const User &user() const;

    //! Метод для установления определенного значения для объекта
    //! класса User
    void setUser(const User user);

    //! Перегрузка оператора считывания данных из потока
    friend QDataStream &operator >>(QDataStream &ist, User &user);

    //! Перегрузка оператора загрузки данных в поток
    friend QDataStream &operator <<(QDataStream &ost, const User &user);

private:
    //! Приватные параметры пользователя
    QString mLogin, mPassword, mRole;
};

#endif // USER_H
