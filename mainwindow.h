#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mybluetooth.h"
#include<QValidator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void addItem(QString text);

private slots:
    void on_devices_doubleClicked(const QModelIndex &index);

    void on_input_editingFinished();

    //void on_send_clicked();
    void openInput();
    void closeInput();
    void on_Scan_clicked();
    void SetScanEnable();


   // void on_input_textEdited(const QString &arg1);

signals:
    void OutText(QString text);
    void SendIndex(int index);
    void SendInput(QString text);
};

#endif // MAINWINDOW_H
