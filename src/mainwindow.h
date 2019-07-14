#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    static const int font_size_title = 25;
    static const int font_size = 15;
    static const int font_size_2 = 8;
    const QString font_family = "Joystix";
    void loadUI();
};

#endif // MAINWINDOW_H
