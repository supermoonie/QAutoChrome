#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QFileDialog>
#include "qautochrome.h"

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
    QAutoChrome* autoChrome;

protected:
    bool eventFilter(QObject *obj, QEvent *e);

signals:
    void lineEditClicked();

private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
