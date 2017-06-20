#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyBluetooth * dev = new MyBluetooth();
    connect(ui->local, SIGNAL(clicked(bool)), dev, SLOT(startLocalDiscovery()));
    connect(dev,SIGNAL(SendText(QString )),ui->commun,SLOT(append(QString )));
    ui->Scan->setEnabled(false);
    connect(ui->Scan, SIGNAL(clicked(bool)), dev, SLOT(startDeviceDiscovery()));
    connect(dev, SIGNAL(SetScanEnable()), this, SLOT(SetScanEnable()));
    connect(dev, SIGNAL(SendItem(QString)), this, SLOT(addItem(QString)));
    connect(this, SIGNAL(SendIndex(int)), dev, SLOT(SelectDevice(int)));
    ui->connect->setEnabled(false);
    ui->disconnect->setEnabled(false);
    connect(ui->connect, SIGNAL(clicked(bool)), dev, SLOT(ConnectDevice()));
    //connect(ui->input, SIGNAL(textChanged(QString)), dev, SLOT(WriteData(QString)));
    connect(ui->close, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(this, SIGNAL(SendInput(QString)), dev, SLOT(WriteData(QString)));
    connect(this, SIGNAL(OutText(QString)), ui->out, SLOT(append(QString)));
    connect(dev, SIGNAL(OpenInput()) , this, SLOT(openInput()));
    ui->input->setEnabled(false);
    QRegExp exp ("[a-zA-Z]{0,10}[0-9]{0,10}[a-zA-Z]{0,10}[0-9]{0,10}[a-zA-Z]{0,10}");
    ui->input->setValidator(new QRegExpValidator(exp, this) );
    ui->out->setEnabled(false);
    connect(ui->disconnect, SIGNAL(clicked(bool)), dev, SLOT(DisconnectDevice()));
    connect(dev, SIGNAL(CloseInput()),this, SLOT(closeInput()));


}

void MainWindow::addItem(QString text)
{
    ui->devices->addItem(text);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_devices_doubleClicked(const QModelIndex &index)
{
    ui->connect->setEnabled(true);
    ui->devices->setEnabled(false);
     emit SendIndex(index.row());
}



void MainWindow::on_input_editingFinished()
{   
    if(ui->input->isActiveWindow())
    {
        emit SendInput(ui->input->text());
        emit OutText("You enter :");
        emit OutText(ui->input->text());
    }
    ui->input->clear();
}



//void MainWindow::on_send_clicked()
//{
//    ui->send->setEnabled(false);
//    emit SendInput(ui->send->text());
//    ui->input->clear();
//}

void MainWindow::openInput()
{
    ui->disconnect->setEnabled(true);
    ui->input->setEnabled(true);
    ui->out->setEnabled(true);
}

void MainWindow::closeInput()
{
    ui->input->setEnabled(false);
    ui->disconnect->setEnabled(false);
    ui->out->clear();
    ui->out->setEnabled(false);
}

void MainWindow::on_Scan_clicked()
{
    ui->devices->setEnabled(true);
    ui->devices->clear();
}

void MainWindow::SetScanEnable()
{
    ui->Scan->setEnabled(true);

}

//void MainWindow::on_input_textEdited(const QString &arg1)
//{
//    emit SendInput(arg1);
//    emit OutText("You enter :");
//    emit OutText(arg1);
//}
