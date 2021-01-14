#include "admin_window.h"
#include "mainwindow.h"
#include "ui_admin_window.h"
#include "add_user.h"
#include "users.h"

admin_window::admin_window(Users *mUsers, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin_window)
{
    ui->setupUi(this);

    //! Устанавливаем заголовок окна и его
    //! фиксированный размер
    this->setWindowTitle("Окно администратора");
    this->setFixedSize(859, 399);

    //! Синхронизируем наш объект класса Users и таблицу,
    //! которая отображает данные о нашем векторе
    ui->users_table->setModel(mUsers);

    //! Присваиваем нашему указателю адрес объекта
    this->mUsers = mUsers;
}

//! Деструктор данного окна
admin_window::~admin_window()
{
    delete ui;
}

//! Функция, сохраняющая объекты в поток из вектора
void admin_window::save_data()
{
    mUsers->save();
}

//! Функция, выгружающая объекты в в вектор из потока
void admin_window::load_data()
{
    mUsers->load();
}

//! Кнопка переключения между окнами
void admin_window::on_back_clicked()
{
    MainWindow *parent_window = dynamic_cast<MainWindow*>(parent());
    parent_window->show();
    close();
}

//! Кнопка добавления пользователя
void admin_window::on_add_user_clicked()
{
    //! Отслеживаем результат выполнения диалогового окна
    int res;

    //! Создаем буферного пользователя
    User newUser;

    //! Создаем наше окно
    add_user adduserWindow(this);

    //! Устанавливаем значение пользователя
    adduserWindow.set_user(&newUser);

    res = adduserWindow.exec();

    //! Привязываем сигнал принятия
    if (res == QDialog::Accepted)
        mUsers->add(newUser);
}

void admin_window::on_delete_usr_clicked()
{
    int ask = QMessageBox::question(this,
                                      QString("Предупреждение"),
                                      QString("Вы уверены, что хотите удалить этого пользователя?"),
                                      QMessageBox::Yes | QMessageBox::No);
    if (ask == QMessageBox::Yes)
    {
        // Для хранения номеров строк создаём STL-контейнер "множество", элементы
        // которого автоматически упорядочиваются по возрастанию
        std::set<int> rows;{
            // Получаем от таблицы заметок список индексов выбранных в настоящий момент
            // элементов
            QModelIndexList idc = ui->users_table->selectionModel()->selectedRows();
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
            mUsers->erase(*it);
        }
    }
}
