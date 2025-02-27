/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *Title;
    QFrame *InfoFrame;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLineEdit *nameInput;
    QLabel *addressLabel;
    QLineEdit *addressInput;
    QLabel *aptLabel;
    QLineEdit *aptInput;
    QLabel *cityLabel;
    QLineEdit *cityInput;
    QLabel *postalCodeLabel;
    QLineEdit *postalCodeInput;
    QFrame *PizzaInfoFrame;
    QHBoxLayout *horizontalLayout;
    QFrame *SizeFrame;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton;
    QLabel *nameLabel_2;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QFrame *ToppingsFrame;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_6;
    QLabel *nameLabel_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_3;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *orderButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(564, 686);
        MainWindow->setMaximumSize(QSize(16777215, 16777161));
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/Desktop/background (1).png) 0 0 0 0 stretch stretch;\n"
"background-repeat: no-repeat;\n"
"background-position: center;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        Title = new QLabel(centralwidget);
        Title->setObjectName("Title");
        QFont font;
        font.setPointSize(40);
        Title->setFont(font);
        Title->setStyleSheet(QString::fromUtf8("color: rgb(235, 255, 0);\n"
"background-color: rgb(135, 39, 39);"));
        Title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(Title);

        InfoFrame = new QFrame(centralwidget);
        InfoFrame->setObjectName("InfoFrame");
        InfoFrame->setStyleSheet(QString::fromUtf8("background-color: #444444;\n"
"opacity: 0.3;"));
        InfoFrame->setFrameShape(QFrame::Shape::StyledPanel);
        InfoFrame->setFrameShadow(QFrame::Shadow::Raised);
        formLayout = new QFormLayout(InfoFrame);
        formLayout->setObjectName("formLayout");
        nameLabel = new QLabel(InfoFrame);
        nameLabel->setObjectName("nameLabel");
        QFont font1;
        font1.setPointSize(17);
        nameLabel->setFont(font1);
        nameLabel->setStyleSheet(QString::fromUtf8("margin-bottom: 3px;\n"
"color:  #FFF;"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameInput = new QLineEdit(InfoFrame);
        nameInput->setObjectName("nameInput");
        QFont font2;
        font2.setPointSize(12);
        nameInput->setFont(font2);
        nameInput->setStyleSheet(QString::fromUtf8("background-color: #8F8F8F;\n"
""));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameInput);

        addressLabel = new QLabel(InfoFrame);
        addressLabel->setObjectName("addressLabel");
        addressLabel->setFont(font1);
        addressLabel->setStyleSheet(QString::fromUtf8("margin-bottom: 3px;\n"
"color:  #FFF;"));

        formLayout->setWidget(1, QFormLayout::LabelRole, addressLabel);

        addressInput = new QLineEdit(InfoFrame);
        addressInput->setObjectName("addressInput");
        addressInput->setFont(font2);
        addressInput->setStyleSheet(QString::fromUtf8("background-color: #8F8F8F;\n"
""));

        formLayout->setWidget(1, QFormLayout::FieldRole, addressInput);

        aptLabel = new QLabel(InfoFrame);
        aptLabel->setObjectName("aptLabel");
        aptLabel->setFont(font1);
        aptLabel->setStyleSheet(QString::fromUtf8("margin-bottom: 3px;\n"
"color:  #FFF;"));

        formLayout->setWidget(2, QFormLayout::LabelRole, aptLabel);

        aptInput = new QLineEdit(InfoFrame);
        aptInput->setObjectName("aptInput");
        aptInput->setFont(font2);
        aptInput->setStyleSheet(QString::fromUtf8("background-color: #8F8F8F;\n"
""));

        formLayout->setWidget(2, QFormLayout::FieldRole, aptInput);

        cityLabel = new QLabel(InfoFrame);
        cityLabel->setObjectName("cityLabel");
        cityLabel->setFont(font1);
        cityLabel->setStyleSheet(QString::fromUtf8("margin-bottom: 3px;\n"
"color:  #FFF;"));

        formLayout->setWidget(3, QFormLayout::LabelRole, cityLabel);

        cityInput = new QLineEdit(InfoFrame);
        cityInput->setObjectName("cityInput");
        cityInput->setFont(font2);
        cityInput->setStyleSheet(QString::fromUtf8("background-color: #8F8F8F;\n"
""));

        formLayout->setWidget(3, QFormLayout::FieldRole, cityInput);

        postalCodeLabel = new QLabel(InfoFrame);
        postalCodeLabel->setObjectName("postalCodeLabel");
        postalCodeLabel->setFont(font1);
        postalCodeLabel->setStyleSheet(QString::fromUtf8("color:  #FFF;"));

        formLayout->setWidget(4, QFormLayout::LabelRole, postalCodeLabel);

        postalCodeInput = new QLineEdit(InfoFrame);
        postalCodeInput->setObjectName("postalCodeInput");
        postalCodeInput->setFont(font2);
        postalCodeInput->setStyleSheet(QString::fromUtf8("background-color: #8F8F8F;\n"
""));

        formLayout->setWidget(4, QFormLayout::FieldRole, postalCodeInput);


        verticalLayout_2->addWidget(InfoFrame);

        PizzaInfoFrame = new QFrame(centralwidget);
        PizzaInfoFrame->setObjectName("PizzaInfoFrame");
        PizzaInfoFrame->setStyleSheet(QString::fromUtf8("background-color: #444444;\n"
"opacity: 0.3;"));
        PizzaInfoFrame->setFrameShape(QFrame::Shape::StyledPanel);
        PizzaInfoFrame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(PizzaInfoFrame);
        horizontalLayout->setObjectName("horizontalLayout");
        SizeFrame = new QFrame(PizzaInfoFrame);
        SizeFrame->setObjectName("SizeFrame");
        SizeFrame->setFrameShape(QFrame::Shape::StyledPanel);
        SizeFrame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(SizeFrame);
        gridLayout_2->setObjectName("gridLayout_2");
        radioButton = new QRadioButton(SizeFrame);
        radioButton->setObjectName("radioButton");
        radioButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        radioButton->setChecked(false);
        radioButton->setAutoExclusive(true);

        gridLayout_2->addWidget(radioButton, 1, 0, 1, 1);

        nameLabel_2 = new QLabel(SizeFrame);
        nameLabel_2->setObjectName("nameLabel_2");
        nameLabel_2->setMaximumSize(QSize(90, 16777215));
        QFont font3;
        font3.setPointSize(20);
        nameLabel_2->setFont(font3);
        nameLabel_2->setStyleSheet(QString::fromUtf8("margin-bottom: 15px;\n"
"color:  #FFF;\n"
"background: #FCF77D;"));

        gridLayout_2->addWidget(nameLabel_2, 0, 0, 1, 1);

        radioButton_2 = new QRadioButton(SizeFrame);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        radioButton_2->setAutoExclusive(true);

        gridLayout_2->addWidget(radioButton_2, 2, 0, 1, 1);

        radioButton_3 = new QRadioButton(SizeFrame);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        radioButton_3->setChecked(true);
        radioButton_3->setAutoExclusive(true);

        gridLayout_2->addWidget(radioButton_3, 3, 0, 1, 1);


        horizontalLayout->addWidget(SizeFrame);

        ToppingsFrame = new QFrame(PizzaInfoFrame);
        ToppingsFrame->setObjectName("ToppingsFrame");
        ToppingsFrame->setFrameShape(QFrame::Shape::StyledPanel);
        ToppingsFrame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout = new QGridLayout(ToppingsFrame);
        gridLayout->setObjectName("gridLayout");
        checkBox_7 = new QCheckBox(ToppingsFrame);
        checkBox_7->setObjectName("checkBox_7");
        checkBox_7->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(checkBox_7, 2, 2, 1, 1);

        checkBox_2 = new QCheckBox(ToppingsFrame);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(checkBox_2, 3, 0, 1, 1);

        checkBox = new QCheckBox(ToppingsFrame);
        checkBox->setObjectName("checkBox");
        checkBox->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(checkBox, 1, 0, 1, 1);

        checkBox_9 = new QCheckBox(ToppingsFrame);
        checkBox_9->setObjectName("checkBox_9");
        checkBox_9->setCursor(QCursor(Qt::CursorShape::ForbiddenCursor));
        checkBox_9->setAcceptDrops(false);
        checkBox_9->setCheckable(false);
        checkBox_9->setChecked(false);

        gridLayout->addWidget(checkBox_9, 1, 2, 1, 1);

        checkBox_6 = new QCheckBox(ToppingsFrame);
        checkBox_6->setObjectName("checkBox_6");
        checkBox_6->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(checkBox_6, 3, 1, 1, 1);

        nameLabel_3 = new QLabel(ToppingsFrame);
        nameLabel_3->setObjectName("nameLabel_3");
        nameLabel_3->setMaximumSize(QSize(150, 16777215));
        nameLabel_3->setFont(font3);
        nameLabel_3->setStyleSheet(QString::fromUtf8("margin-bottom: 15px;\n"
"color:  #000;\n"
"background: #2CC24D;"));

        gridLayout->addWidget(nameLabel_3, 0, 1, 1, 1);

        checkBox_4 = new QCheckBox(ToppingsFrame);
        checkBox_4->setObjectName("checkBox_4");
        checkBox_4->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(checkBox_4, 2, 0, 1, 1);

        checkBox_5 = new QCheckBox(ToppingsFrame);
        checkBox_5->setObjectName("checkBox_5");
        checkBox_5->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(checkBox_5, 2, 1, 1, 1);

        checkBox_8 = new QCheckBox(ToppingsFrame);
        checkBox_8->setObjectName("checkBox_8");
        checkBox_8->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(checkBox_8, 3, 2, 1, 1);

        checkBox_3 = new QCheckBox(ToppingsFrame);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(checkBox_3, 1, 1, 1, 1);


        horizontalLayout->addWidget(ToppingsFrame);


        verticalLayout_2->addWidget(PizzaInfoFrame);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName("gridLayout_3");
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(0, 50));
        pushButton->setMaximumSize(QSize(150, 80));
        pushButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(214, 44, 33);\n"
"color: #FFF;\n"
"font-weight: 900;"));

        gridLayout_3->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(0, 50));
        pushButton_2->setMaximumSize(QSize(150, 80));
        pushButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_2->setStyleSheet(QString::fromUtf8("font-weight: 900;\n"
"color: #fff;\n"
"background-color: rgb(44, 77, 162);"));

        gridLayout_3->addWidget(pushButton_2, 0, 1, 1, 1);

        orderButton = new QPushButton(frame);
        orderButton->setObjectName("orderButton");
        orderButton->setMinimumSize(QSize(0, 50));
        orderButton->setMaximumSize(QSize(150, 80));
        orderButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        orderButton->setStyleSheet(QString::fromUtf8("font-weight: 900;\n"
"color: #fff;\n"
"background-color: rgb(33, 214, 40);"));

        gridLayout_3->addWidget(orderButton, 0, 2, 1, 1);


        verticalLayout_2->addWidget(frame);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Title->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">PIZZA LA VIVA</span></p></body></html>", nullptr));
        nameLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Name</span><span style=\" font-weight:700; color:#ff0000;\">*</span></p></body></html>", nullptr));
        nameInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your name", nullptr));
        addressLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Address</span><span style=\" font-weight:700; color:#ff0000;\">*</span></p></body></html>", nullptr));
        addressInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your address", nullptr));
        aptLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Apt/Unit</span></p></body></html>", nullptr));
        aptInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your Apartment Number", nullptr));
        cityLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">City</span><span style=\" font-weight:700; color:#ff0000;\">*</span></p></body></html>", nullptr));
        cityInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your City", nullptr));
        postalCodeLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Postal Code</span><span style=\" font-weight:700; color:#ff0000;\">*</span></p></body></html>", nullptr));
        postalCodeInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your Postal Code (A1A1A1)", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Small", nullptr));
        nameLabel_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#000000;\">Size</span></p></body></html>", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Medium", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "Large", nullptr));
        checkBox_7->setText(QCoreApplication::translate("MainWindow", "Artichokes", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "Pepperoni", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Ham", nullptr));
        checkBox_9->setText(QCoreApplication::translate("MainWindow", "Extra-Cheese", nullptr));
        checkBox_6->setText(QCoreApplication::translate("MainWindow", "Onion", nullptr));
        nameLabel_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Toppings</span></p><p align=\"center\"><span style=\" font-size:9pt; font-weight:700;\">Select up-to 3</span></p></body></html>", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "Mushroom", nullptr));
        checkBox_5->setText(QCoreApplication::translate("MainWindow", "Pineapple", nullptr));
        checkBox_8->setText(QCoreApplication::translate("MainWindow", "Black Olives", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "Green Pepper", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        orderButton->setText(QCoreApplication::translate("MainWindow", "Order", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
