#include "registerwindownew.h"
#include "ui_registerwindownew.h"
#include <QtWidgets>
#include "shoppingwindow.h"
QString name;
RegisterWindowNew::RegisterWindowNew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterWindowNew)
{
    ui->setupUi(this);
}

RegisterWindowNew::~RegisterWindowNew()
{
    delete ui;
}

void RegisterWindowNew::on_pushButton_clicked()
{
    name = ui->nicknameLineEdit->text();
    if (name == "") {
        QMessageBox::warning(
            this,
            tr("Enter Nickname"),
            tr("You should enter your nickname before shopping.") );
        //error
    }
    else {
        ShoppingWindow* myShopWindow = new ShoppingWindow(nullptr, name);
        myShopWindow->show();
        this->close();
        //this->hide();
    }
}
