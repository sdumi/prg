#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Quit,  SIGNAL(activated()), this, SLOT(on_quitMenu_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()),   this, SLOT(on_quitMenu_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quitMenu_clicked()
{
    ::exit(0);
}
