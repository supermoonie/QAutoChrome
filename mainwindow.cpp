#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    autoChrome(0)
{
    ui->setupUi(this);
    ui->lineEdit->installEventFilter(this);
    connect(this, &MainWindow::lineEditClicked, [=](){
        //定义文件对话框类
        QFileDialog *fileDialog = new QFileDialog(this);
        //定义文件对话框标题
        fileDialog->setWindowTitle(tr("请选择chrome.exe"));
        //设置默认文件路径
        fileDialog->setDirectory("C://");
        //设置文件过滤器
        fileDialog->setNameFilter(tr("*.exe"));
        //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
        fileDialog->setFileMode(QFileDialog::ExistingFile);
        //设置视图模式
        fileDialog->setViewMode(QFileDialog::Detail);
        //打印所有选择的文件的路径
        QStringList fileNames;
        if(fileDialog->exec())
        {
            fileNames = fileDialog->selectedFiles();
        }
        for(auto tmp:fileNames) {
            ui->lineEdit->setText(tmp);
            qDebug()<<tmp<<endl;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == ui->lineEdit && e->type() == QEvent::MouseButtonPress){
        QMouseEvent *me = (QMouseEvent*)e;
        if(me->button() == Qt::LeftButton){
            emit lineEditClicked();
        }
    }
    return QMainWindow::eventFilter(obj,e);
}

void MainWindow::on_pushButton_clicked()
{
    QString path = ui->lineEdit->text();
    if(path.isEmpty()) {
        return;
    }
    autoChrome = new QAutoChrome(this);
    autoChrome->setChromePath(path);
    autoChrome->start();
}
