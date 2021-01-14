#include "products.h"

//! Считываем данные из файла
Products::Products()
{
    beginInsertRows(QModelIndex(), // Индекс родителя, в список потомков которого добавляются строки
                           0, // Номер первой добавляемой строки
                           size()); // Номер последней добавляемой строки

    load();

    endInsertRows();
}

//! Записываем данные в файл
Products::~Products()
{
    save();
}

//! Метод, для получения размера вектора
size_t Products::size()
{
    return mProducts.size();
}

//! Метод для получения количества строк
int Products::rowCount(const QModelIndex &parent) const
{
    return mProducts.size();
}

//! Метод для получения количества столбцов
int Products::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant Products::data(const QModelIndex &index, int role) const
{
    // Если требуется текст для отображения...
    if (role == Qt::DisplayRole)
    {
        // Если столбец первый, возвращаем заголовок заметки, находящейся
        // в соответствующей строке таблицы
        if (index.column() == 0)
            return mProducts[index.row()].name();
        if (index.column() == 1)
            return mProducts[index.row()].place();
        if (index.column() == 2)
            return mProducts[index.row()].placefrom();
        if (index.column() == 3)
            return mProducts[index.row()].timefrom();
        if (index.column() == 4)
            return mProducts[index.row()].price();
    }
    // Игнорируем все остальные запросы, возвращая пустой QVariant
    return QVariant();
}

QVariant Products::headerData(int section, Qt::Orientation orientation, int role) const
{
    // Если требуется текст для отображения...
    if (role == Qt::DisplayRole)
    {
        // Если речь о заголовках столбцов...
        if (orientation == Qt::Horizontal)
        {
            // Если столбец первый, возвращаем заголовок
            if (section == 0)
                return "  Название товара  ";
            if (section == 1)
                return "  Расположение  ";
            if (section == 2)
                return "  Место прибытия  ";
            if (section == 3)
                return "  Время прибытия  ";
            if (section == 4)
                return "  Цена  ";
        }
        // Если речь о заголовках строк...
        else if (orientation == Qt::Vertical)
        {
            // Возвращаем номер строки
            return QString::number(section);
        }
    }
    // Игнорируем все остальные запросы, возвращая пустой QVariant
    return QVariant();
}

//! Перегрузка оператора квадратных скобок для обращения
//! по индексу к вектору
const Product &Products::operator[](size_t idx) const
{
    return mProducts[idx];
}

void Products::add(Product product)
{
    // В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    // что мы начинаем вставлять строки в модель.
    // Вставку производим в конец, поэтому номер новой строки будет равен size()
    beginInsertRows(QModelIndex(), // Индекс родителя, в список потомков которого добавляются строки
                           size(), // Номер первой добавляемой строки
                           size()); // Номер последней добавляемой строки
    // Вставляем заметку в конец вектора mProducts
    mProducts.push_back(product);
    // В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    // что мы закончили вставлять строки в модель.
    endInsertRows();
}

void Products::load()
{
    //! Путь к базе данных пользователей
    QString path = "ProductStream.bin";

    //! Создаем объект класса QFille, которым
    //! является наш файл по прописанному выше пути
    QFile file(path);

    //! Открываем файл с параметром только для считывания
    file.open(QIODevice::ReadOnly);

    //! Создаем входной поток даных из нашего файла
    QDataStream ist(&file);

    //! Создаем буферную переменную, которая будет
    //! считывать в себя информацию о товаре из
    //! файла, а затем добавляться в вектор
    Product tmp_product;

    //! Считываем поток, пока не закончится файл
    while (!file.atEnd())
    {
        //! Считывание из файла
        ist >> tmp_product;

        //! Добавляем пользователя в поток
        add(tmp_product);
    }

    //! Закрываем файл, чтобы не повредился
    file.close();
}

void Products::save()
{
    //! Путь к базе данных пользователей
    QString path = "ProductStream.bin";

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
        ost << mProducts[i];
    }

    //! Закрываем файл, чтобы не повредился
    file.close();
}

void Products::erase(size_t idx)
{
    // В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    // что мы начинаем удалять строки из модели
    beginRemoveRows(QModelIndex(), // Индекс родителя, из списка потомков которого удаляются строки
                    idx, // Номер первой удаляемой строки
                    idx // Номер последней удаляемой строки
                    );
    // Удаляем из вектора элемент с индексом idx
    mProducts.erase(std::next(mProducts.begin(), idx));
    // В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    // что мы закончили удалять строки из модели
    endRemoveRows();
}
