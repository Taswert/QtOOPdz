#ifndef REGISTERWINDOWNEW_H
#define REGISTERWINDOWNEW_H

#include <QMainWindow>

namespace Ui {
class RegisterWindowNew;
}

class RegisterWindowNew : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindowNew(QWidget *parent = nullptr);
    ~RegisterWindowNew();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RegisterWindowNew *ui;
};

#endif // REGISTERWINDOWNEW_H
