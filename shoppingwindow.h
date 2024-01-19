#ifndef SHOPPINGWINDOW_H
#define SHOPPINGWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QTableWidget>

namespace Ui {
class ShoppingWindow;
}

class ShoppingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShoppingWindow(QWidget *parent = nullptr);
    void updateProductList(QTableWidget* table);
    ShoppingWindow(QWidget *parent, QString nickname);
    ~ShoppingWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ShoppingWindow *ui;
    QVector<QSpinBox*> spinBoxes;
    QString nickname;
};

#endif // SHOPPINGWINDOW_H
