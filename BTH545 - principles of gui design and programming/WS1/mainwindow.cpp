#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

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
        QMessageBox::information(this, "Greeting", "Hello BTH545");
        //Avoid unnecessary string assignment if the text is fine becuase 'new' is expensive
        if(ui->label->text() != "Hello BTH545")
            ui->label->setText("Hello BTH545");
    }

