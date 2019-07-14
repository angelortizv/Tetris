#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadUI(){
    QFontDatabase::addApplicationFont(":/src/font/pixel.ttf");
    ui->title_label->setFont(QFont(font_family, font_size_title));
    ui->developer->setFont(QFont(font_family, font_size_2));
    ui->play_button->setFont(QFont(font_family, font_size_2));
}

void MainWindow::on_play_button_clicked()
{
    this->close();
    Game *game = new Game();
    game->show();
}
