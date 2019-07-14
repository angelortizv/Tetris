#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    loadUI();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    close();
    MainWindow *w = new MainWindow();
    w->show();
}

void Settings::loadUI(){
    QFontDatabase::addApplicationFont(":/src/font/pixel.ttf");
    ui->pushButton->setFont(QFont(font_family, font_size_2));
}

