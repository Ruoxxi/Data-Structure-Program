#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include "func.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString mode = ui->mode_buttonGroup->checkedButton()->text();
    int way = (mode == "walk" ? 1 : 2);

    QString src = ui->lineEdit_src->text();
    QString dest = ui->lineEdit_dest->text();

    func(src.toInt(), dest.toInt(), way);
//    QMessageBox::information(NULL, "Title", src,QMessageBox::Yes|QMessageBox::No);
}

void MainWindow::on_radioButton_drive_clicked()
{

}

void MainWindow::on_radioButton_walk_clicked()
{

}
