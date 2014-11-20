#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMainWindow>
#include "fileloader.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QMessageBox daMessageBox;
    void drawMyLawn();
    ~MainWindow();

private slots:
    void on_QuitButon_clicked();

    void on_RestartLevelButton_clicked();

    void on_UserChoose_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    fileloader loader;

};

#endif // MAINWINDOW_H
