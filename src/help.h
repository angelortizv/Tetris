#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QFontDatabase>
#include "mainwindow.h"

namespace Ui {
class Help;
}

class Help : public QWidget
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = 0);
    ~Help();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Help *ui;
    static const int font_size_title = 25;
    static const int font_size = 15;
    static const int font_size_2 = 8;
    const QString font_family = "Joystix";
    void loadUI();
};

#endif // HELP_H
