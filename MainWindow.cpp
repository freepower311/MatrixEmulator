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
    connect(m_snakeTest.get(), &Snake::signalSetColor, ui->emulator, &Emulator::setColor);
    connect(m_snakeTest.get(), &Snake::signalSetMatrixSize, ui->emulator, &Emulator::setMatrixSize);
    m_snakeTest->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

