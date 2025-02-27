#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_2_clicked();

    void on_horizontalSlider_sliderPressed();

    void on_pushButton_3_clicked();

    std::string GetWordFromNumber(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
