#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(auto child : this->ui->centralwidget->children())
    {
        if(QFrame* currentFrame = qobject_cast<QFrame*>(child))
        {
            for(auto widget : currentFrame->children())
            {
                if(QFrame* innerWidget = qobject_cast<QFrame*>(widget))
                {
                    for(auto item : innerWidget->children())
                    {
                        if(QRadioButton* currentRadio = qobject_cast<QRadioButton*>(item))
                            this->radioButtons.push_back(currentRadio);
                        else if(QCheckBox* currentCheckBox = qobject_cast<QCheckBox*>(item))
                        {
                            this->checkBoxes.push_back(currentCheckBox);
                            connect(currentCheckBox, &QCheckBox::toggled, this, &MainWindow::onCheckBoxesToggled);
                        }
                    }
                }
                else if(QLineEdit* currentLine = qobject_cast<QLineEdit*>(widget))
                    this->LineEdit.push_back(currentLine);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Exit Button
void MainWindow::on_pushButton_clicked()
{
    this->close();
}

//Reset Button
void MainWindow::on_pushButton_2_clicked()
{
    for(auto radio : this->radioButtons)
    {
        radio->setChecked(false);
    }

    for(auto checkBox : this->checkBoxes)
    {
        checkBox->setChecked(false);
    }

    for(auto currentLine : this->LineEdit)
    {
        if(currentLine->objectName() == "addressInput") continue;
        currentLine->setText("");
    }
}

//Order Button
void MainWindow::on_orderButton_clicked()
{
    if(!this->isValidOrder())
    {
        QMessageBox::information(this, "Invalid Infromation", "Some key information is incomplete/invalid...\nplease fix it to order, all key information has a red * next it");
        return;
    }


    const QString text
        = "Summary: \nName\t\t: " + this->ui->nameInput->text()
        + "\nAddress\t\t: " + this->ui->addressInput->text()
          + "\nApt/Unit\t: " + this->ui->aptInput->text()
          + "\nCity\t\t: " + this->ui->cityInput->text()
          + "\nPostal-Code\t: " + this->ui->postalCodeInput->text()
          + "\n\nSize: " + (this->ui->radioButton->isChecked() ? this->ui->radioButton->text()
                                                               : this->ui->radioButton_2->isChecked()
                                                               ? this->ui->radioButton_2->text()
                                                               : this->ui->radioButton_3->text())
        + "\nToppings: " + this->GetSelectedToppings();

    QMessageBox msgBox{};
    msgBox.setWindowTitle("Confirmation");
    msgBox.setText(text);

    QPushButton* rejectButton = msgBox.addButton(tr("Reject"), QMessageBox::RejectRole);
    QPushButton* confirmButton = msgBox.addButton(tr("Confirm"), QMessageBox::AcceptRole);

    msgBox.exec();

    if(msgBox.clickedButton() == confirmButton)
        this->close();
    else if(msgBox.clickedButton() == rejectButton)
        msgBox.close();
}

QString MainWindow::GetSelectedToppings()
{
    QString toppings{};

    for(auto topping: this->checkBoxes)
    {
        if(topping->isChecked()) toppings += topping->text() + ",  ";
    }

    return toppings;
}

bool MainWindow::isValidOrder()
{
    for(auto input : this->LineEdit)
    {
        if(input->text() == "" && input->objectName() != "aptInput") return false;

        //if postal code
        if(input->objectName() == "postalCodeInput")
        {
            if(input->text().length() != POSTAL_CODE_LENGTH) return false;
            for(int i = 0; i < POSTAL_CODE_LENGTH; ++i)
            {
                if(i % 2 != 0 && !input->text().at(i).isDigit())
                    return false;
                else if(i % 2 == 0 && !input->text().at(i).isLetter())
                    return false;
            }
        }
    }

    return true;
}

//Small size pizza
void MainWindow::on_radioButton_clicked()
{
    this->ui->checkBox_9->setCursor(Qt::PointingHandCursor);
    this->ui->checkBox_9->setCheckable(true);
}


void MainWindow::on_radioButton_3_clicked()
{
    this->ui->checkBox_9->setCursor(Qt::ForbiddenCursor);
    this->ui->checkBox_9->setCheckable(false);
    this->ui->checkBox_9->setChecked(false);
}


void MainWindow::on_radioButton_2_clicked()
{
    this->ui->checkBox_9->setCursor(Qt::PointingHandCursor);
    this->ui->checkBox_9->setCheckable(true);
}

void MainWindow::onCheckBoxesToggled(bool checked)
{
    if(!checked) return;

    int count{0};
    for(const auto& checkBox : this->checkBoxes)
        if(checkBox->isChecked()) ++count;

    if(count > 3)
    {
        QCheckBox* senderButton = qobject_cast<QCheckBox*>(sender());
        if(senderButton)
            senderButton->setChecked(false);
    }
}


void MainWindow::on_postalCodeInput_textChanged(const QString &arg1)
{

    if (arg1.length() > POSTAL_CODE_LENGTH)
    {
        this->ui->postalCodeInput->setText(arg1.left(POSTAL_CODE_LENGTH));
        this->ui->postalCodeInput->setCursorPosition(POSTAL_CODE_LENGTH);
    }
    else if(arg1.length() > 0)
    {
        //if even -> it needs to be a number
        if(arg1.length() % 2 == 0 && !arg1.at(arg1.length() - 1).isNumber())
        {
            this->ui->postalCodeInput->setText(arg1.left(arg1.length() - 1));
            this->ui->postalCodeInput->setCursorPosition(arg1.length() - 1);

        }
        else if(arg1.length() % 2 != 0 && !arg1.at(arg1.length() - 1).isLetter())
        {
            this->ui->postalCodeInput->setText(arg1.left(arg1.length() - 1));
            this->ui->postalCodeInput->setCursorPosition(arg1.length() - 1);
        }
    }
}

