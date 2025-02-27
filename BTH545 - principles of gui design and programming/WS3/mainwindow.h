#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QVector>
#define POSTAL_CODE_LENGTH 6

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_orderButton_clicked();

    QString GetSelectedToppings();

    bool isValidOrder();

    void on_radioButton_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_2_clicked();

    void onCheckBoxesToggled(bool checked);

    void on_postalCodeInput_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QVector<QRadioButton*> radioButtons{};
    QVector<QCheckBox*> checkBoxes{};
    QVector<QLineEdit*> LineEdit{};

};
#endif // MAINWINDOW_H
