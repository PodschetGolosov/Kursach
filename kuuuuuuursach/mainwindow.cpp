#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//кнопка Enter
void MainWindow::on_pushButton_7_clicked()
{

}

//кнопка Добавить опрос
void MainWindow::on_pushButton_clicked()
{

}

//проголосовать
void MainWindow::on_pushButton_2_clicked()
{

}

//подсчет всех нет
void MainWindow::on_pushButton_5_clicked()
{

}

//подсчет голосов
void MainWindow::on_pushButton_3_clicked()
{

}

//подсчет всех да
void MainWindow::on_pushButton_4_clicked()
{

}

//подсчет вопросов на которые ответили да
void MainWindow::on_pushButton_6_clicked()
{

}
