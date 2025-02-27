#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    QString text = QString::number(position);
    this->ui->label->setText(text);

    QString numberWord = QString::fromStdString(this->GetWordFromNumber(position));
    this->ui->label_2->setText(numberWord);
}

std::string MainWindow::GetWordFromNumber(int value)
{
    switch(value)
    {
    case 1: return "One";
    case 2: return "Two";
    case 3: return "Three";
    case 4: return "Four";
    case 5: return "Five";
    case 6: return "Six";
    case 7: return "Seven";
    case 8: return "Eight";
    case 9: return "Nine";
    case 0: return "Zero";
    default:
        return "Ten";
    };
}


void MainWindow::on_pushButton_2_clicked()
{
    int newPosition = ui->horizontalSlider->sliderPosition() +  1;
    newPosition = newPosition > 10 ? 0 : newPosition;

    this->ui->horizontalSlider->setSliderPosition(newPosition);
    this->on_horizontalSlider_sliderMoved(newPosition);
}


void MainWindow::on_horizontalSlider_sliderPressed()
{
    int newPosition = this->ui->horizontalSlider->sliderPosition();
    this->on_horizontalSlider_sliderMoved(newPosition);
}


void MainWindow::on_pushButton_3_clicked()
{
    int newPosition = this->ui->horizontalSlider->sliderPosition() - 1;
    newPosition = newPosition < 0 ? 10 : newPosition;

    this->ui->horizontalSlider->setSliderPosition(newPosition);
    this->on_horizontalSlider_sliderMoved(newPosition);
}

