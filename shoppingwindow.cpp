#include "shoppingwindow.h"
#include "ui_shoppingwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSpinBox>
#include <QTextCodec>
#include <QString>

ShoppingWindow::ShoppingWindow(QWidget *parent, QString nickname) :
    QMainWindow(parent),
    ui(new Ui::ShoppingWindow)
{
    ui->setupUi(this);
    this->nickname = nickname;
    ui->label_2->setText(nickname);
    auto table = ui->tableWidget;
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels(QStringList() << "Товар" << "Количество" << "Цена" << "Выбрано");
    updateProductList(table);
}

void ShoppingWindow::updateProductList(QTableWidget* table) {
    table->clearContents();
    table->setRowCount(0);
    qDeleteAll(spinBoxes);
    spinBoxes.clear();

    QFile file("C:/Users/Romah/Documents/untitled/products.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл товаров для чтения.");
            return;
        }
        QTextStream ifile(&file);
        table->setRowCount(0);
        int row = 0;
        while (!ifile.atEnd()) {
            QString line = ifile.readLine();
            QStringList parts = line.split(" - ");
            if (parts.size() == 2) {
                QStringList secondPart = parts[1].split(" | ");
                if (secondPart.size() == 2) {
                    table->insertRow(row);
                    table->setItem(row, 0, new QTableWidgetItem(parts[0].trimmed()));
                    int count = secondPart[0].toInt();
                    table->setItem(row, 1, new QTableWidgetItem(QString::number(count)));
                    table->setItem(row, 2, new QTableWidgetItem(secondPart[1].trimmed()));
                    QSpinBox *spinBox = new QSpinBox(this);
                    spinBox->setMinimum(0);
                    spinBox->setMaximum(count);
                    spinBoxes.append(spinBox);
                    table->setCellWidget(row, 3, spinBox);

                    row++;
                }
            }
        }
    file.close();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ShoppingWindow::~ShoppingWindow()
{
    delete ui;
}

void ShoppingWindow::on_pushButton_clicked()
{
    QFile productsFile("C:/Users/Romah/Documents/untitled/products.txt");
    QFile chequeFile("C:/Users/Romah/Documents/untitled/cheque.txt");
    struct Order {
            QString name;
            int count;
            int price;
        };
    QList<Order> ordersList;
    auto table = ui->tableWidget;


    for (int row = 0; row < table->rowCount(); ++row) {
        if (spinBoxes[row]->value() > 0) {
            QString name = table->item(row, 0)->text();
            int quantityAvailable = table->item(row, 1)->text().toInt();
            int price = table->item(row, 2)->text().toInt();
            int quantityOrdered = spinBoxes[row]->value();

            if (quantityOrdered > 0 && quantityOrdered <= quantityAvailable) {
                quantityAvailable -= quantityOrdered;
                table->item(row, 1)->setText(QString::number(quantityAvailable));
                ordersList.append({name, quantityOrdered, price});
            }
        }
    }


    if (!productsFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл товаров для записи.");
        return;
    }
    QTextStream out(&productsFile);
    for (int row = 0; row < table->rowCount(); ++row) {
        QString name = table->item(row, 0)->text();
        QString count = table->item(row, 1)->text();
        QString price = table->item(row, 2)->text();
        out << name << " - " << count << " | " << price << endl;
    }
    productsFile.close();

    if (!chequeFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл чеков для записи.");
        return;
    }
    QTextStream chequeOut(&chequeFile);
    chequeOut << "-------------------------" << endl;
    chequeOut << "Nickname: " << nickname << endl;
    int totalSum = 0;
    for (const Order &order : ordersList) {
        int sum = order.count * order.price;
        totalSum += sum;
        chequeOut << order.name << " - " << order.count << " | " << sum << " RUB" << endl;
    }
    chequeOut << "Total: " << totalSum << " RUB" << endl;
    chequeOut << "-------------------------" << endl;
    chequeFile.close();

    QMessageBox::information(this, "Готово!", "Ваш заказ успешно составлен и сохранён в чековом файле!");
    updateProductList(table);
}
