#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    loadUI();
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_clicked()
{
    close();
    MainWindow *w = new MainWindow();
    w->show();
}

void Help::loadUI(){
    QFontDatabase::addApplicationFont(":/src/font/pixel.ttf");
    ui->pushButton->setFont(QFont(font_family, font_size_2));
}
