#include "add_user.h"
#include "ui_add_user.h"

//! Конструктор данного класса
add_user::add_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_user)
{
    ui->setupUi(this);

    //! Устанавливаем заголовок окна и его
    //! фиксированный размер
    this->setWindowTitle("Добавление пользователя");
    this->setFixedSize(390, 293);
}

//! Стандартный деструктор данного класса
add_user::~add_user()
{
    delete ui;
}

//! Метод класса, устанавливающией текущего пользователя
//! в буферную переменнуюю
void add_user::set_user(User* new_user)
{
    this->new_user = new_user;
}

void add_user::on_addUser_clicked()
{
    //! Присваивание параметров для буферного пользователя
    new_user->setLogin(ui->login->text());
    new_user->setPassword(ui->password->text());
    new_user->setRole(ui->role->text());

    if (new_user->role() != "Администратор" && new_user->role() != "Кладовщик")
    {
        //! Создание сообщения об ошибке, а также функция,
        //! создающее само окно, предупреждающее пользо-
        //! вателя об ошибке
        QString warning_message = "Недопустимая должность пользователя!";
        create_warning_box_user(warning_message, this);

        //! Обнуление полей вводимых пользователем
        ui->login->clear();
        ui->password->clear();
        ui->role->clear();

    }
    else if (new_user->login().size() > 15 || new_user->password().size() > 15)
    {
        //! Создание сообщения об ошибке, а также функция,
        //! создающее само окно, предупреждающее пользо-
        //! вателя об ошибке
        QString warning_message = "Логин или пароль слишком длинные!";
        create_warning_box_user(warning_message, this);

        //! Обнуление полей вводимых пользователем
        ui->login->clear();
        ui->password->clear();
        ui->role->clear();
    }
    else if (new_user->login().size() < 4 || new_user->password().size() < 5)
    {
        //! Создание сообщения об ошибке, а также функция,
        //! создающее само окно, предупреждающее пользо-
        //! вателя об ошибке
        QString warning_message = "Логин или пароль слишком короткие!";
        create_warning_box_user(warning_message, this);

        //! Обнуление полей вводимых пользователем
        ui->login->clear();
        ui->password->clear();
        ui->role->clear();
    }
    else
    {
        accept();
    }
}

//! Кнопка отмены диалогового окна
void add_user::on_back_clicked()
{
    reject();
}

//! Данный метод создает сообщение об ошибке, и на вход принимает
//! параметры: само сообщение, выводимое пользователю, а также указатель
//! на объект родителя
void add_user::create_warning_box_user(QString &warning_message, QWidget *parent)
{
    QMessageBox fillRows(parent);
    fillRows.setIcon(QMessageBox::Warning);
    fillRows.setWindowTitle("Ошибка");
    fillRows.setText(warning_message);
    fillRows.setStandardButtons(QMessageBox::Discard);
    fillRows.exec();
}
