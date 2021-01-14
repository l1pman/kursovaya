#include "users.h"

//! Считываем данные из файла
Users::Users()
{
    beginInsertRows(QModelIndex(), //! Индекс родителя, в список потомков которого добавляются строки
                           0, //! Номер первой добавляемой строки
                           size()); //! Номер последней добавляемой строки
    load();

    endInsertRows();
}

//! Записываем данные в файл
Users::~Users()
{
    save();
}

//! Метод для получения количества строк
int Users::rowCount(const QModelIndex &parent) const
{
    return mUsers.size();
}

//! Метод для получения количества столбцов
int Users::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant Users::data(const QModelIndex &index, int role) const
{
    //! Если требуется текст для отображения...
    if (role == Qt::DisplayRole)
    {
        //! Если столбец первый, возвращаем заголовок заметки, находящейся
        //! в соответствующей строке таблицы
        if (index.column() == 0)
            return mUsers[index.row()].login();
        if (index.column() == 1)
            return mUsers[index.row()].password();
        if (index.column() == 2)
            return mUsers[index.row()].role();
    }
    //! Игнорируем все остальные запросы, возвращая пустой QVariant
    return QVariant();
}

QVariant Users::headerData(int section, Qt::Orientation orientation, int role) const
{
    //! Если требуется текст для отображения...
    if (role == Qt::DisplayRole)
    {
        //! Если речь о заголовках столбцов...
        if (orientation == Qt::Horizontal)
        {
            //! Если столбец первый, возвращаем заголовок
            if (section == 0)
                return "  Логин   ";
            if (section == 1)
                return "  Пароль  ";
            if (section == 2)
                return "  Должность  ";
        }
        //! Если речь о заголовках строк...
        else if (orientation == Qt::Vertical)
        {
            //! Возвращаем номер строки
            return QString::number(section);
        }
    }
    //! Игнорируем все остальные запросы, возвращая пустой QVariant
    return QVariant();
}

//! Метод, для получения размера вектора
size_t Users::size()
{
    return mUsers.size();
}

//! Перегрузка оператора квадратных скобок для обращения
//! по индексу к вектору
const User &Users::operator[](size_t idx) const
{
    return mUsers[idx];
}

void Users::add(User user)
{
    //! В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    //! что мы начинаем вставлять строки в модель.
    //! Вставку производим в конец, поэтому номер новой строки будет равен size()
    beginInsertRows(QModelIndex(), //! Индекс родителя, в список потомков которого добавляются строки
                           size(), //! Номер первой добавляемой строки
                           size()); //! Номер последней добавляемой строки

    //! Вставляем заметку в конец вектора mUsers
    mUsers.push_back(user);

    //! В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    //! что мы закончили вставлять строки в модель.
    endInsertRows();
}

void Users::load()
{
    //! Путь к базе данных пользователей
    QString path = "UserStream.bin";

    //! Создаем объект класса QFille, которым
    //! является наш файл по прописанному выше пути
    QFile file(path);

    //! Открываем файл с параметром только для считывания
    file.open(QIODevice::ReadOnly);

    //! Создаем входной поток даных из нашего файла
    QDataStream ist(&file);

    //! Создаем буферную переменную, которая будет
    //! считывать в себя информацию о пользователе из
    //! файла, а затем добавляться в вектор
    User tmp_user;

    //! Считываем поток, пока не закончится файл
    while (!file.atEnd())
    {
        //! Считывание из файла
        ist >> tmp_user;

        //! Добавляем пользователя в поток
        add(tmp_user);
    }

    //! Закрываем файл, чтобы не повредился
    file.close();
}

void Users::save()
{
    //! Путь к базе данных пользователей
    QString path = "UserStream.bin";

    //! Создаем объект класса QFille, которым
    //! является наш файл по прописанному выше пути
    QFile file(path);

    //! Открываем файл с параметром записи в файл
    file.open(QIODevice::WriteOnly);

    //! Создаем выходной поток данных в файл
    QDataStream ost(&file);

    //! Запись вектора в поток
    for (size_t i = 0; i < size(); ++i)
    {
        ost << mUsers[i];
    }

    //! Закрываем файл, чтобы не повредился
    file.close();
}

void Users::erase(size_t idx)
{
    //! В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    //! что мы начинаем удалять строки из модели
    beginRemoveRows(QModelIndex(), // Индекс родителя, из списка потомков которого удаляются строки
                    idx, //! Номер первой удаляемой строки
                    idx //! Номер последней удаляемой строки
                    );
    //! Удаляем из вектора элемент с индексом idx
    mUsers.erase(std::next(mUsers.begin(), idx));
    //! В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    //! что мы закончили удалять строки из модели
    endRemoveRows();
}

//! Метод класса для получения пользователя по индексу
const User &Users::get_user(size_t idx) const
{
    return mUsers[idx];
}

//! Метод класса для замены пользователя по индексу
//! на передаваемый параметр (User user)
void Users::replace(size_t idx, User user)
{
    mUsers.replace(idx, user);
}
