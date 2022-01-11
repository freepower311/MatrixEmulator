#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QtWidgets/QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Button123, &QPushButton::clicked, this, [this]()
    {
        QMessageBox::information(this, "title", "нажата 123");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

