#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QtCore>
#include <QFile>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   // QLabel *mouseCord = new QLabel();
    QString currentfile;


private slots:
    void on_action_New_Map_triggered();

    void on_actionLoad_Tileset_triggered();

    void on_actionSave_Map_triggered();

    void on_actionLoad_Map_triggered();

    void on_actionAbout_triggered();

    void on_actionSave_triggered();

    void on_actionEraser_triggered();

    void on_actionExport_to_JSON_triggered();

private:
    Ui::MainWindow *ui;
    void SaveMap(QString filename);
    void EnableTool();
    void DisableTool();
};

#endif // MAINWINDOW_H


