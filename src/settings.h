#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QFontDatabase>
#include "mainwindow.h"

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Settings *ui;
    static const int font_size_title = 25;
    static const int font_size = 15;
    static const int font_size_2 = 8;
    const QString font_family = "Joystix";
    void loadUI();
};

#endif // SETTINGS_H
