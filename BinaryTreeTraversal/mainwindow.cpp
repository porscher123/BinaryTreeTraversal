#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowBase();
    this->setInputText();
    this->setLeftLayout();
    this->setRightLayout();
    this->setMainLayout();






}
void MainWindow::setWindowBase() {
    this->setFixedSize(1000, 650);
}
void MainWindow::setInputText() {
    this->inputText = new QTextEdit();

}


void MainWindow::setLeftLayout() {
    this->leftLayout = new QVBoxLayout();
//    this->leftLayout->
}
void MainWindow::setRightLayout() {
    this->rightLayout = new QVBoxLayout();
}
void MainWindow::setMainLayout() {
    this->mainLayout = new QGridLayout(this);
    this->mainLayout->setSpacing(10);
    this->mainLayout->addLayout(this->leftLayout, 0, 0);
    this->mainLayout->addLayout(this->rightLayout, 0, 1);
}
MainWindow::~MainWindow()
{
}

