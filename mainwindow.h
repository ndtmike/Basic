#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGlobal>
#include <QMessageBox>
#include <QtWidgets>
#include <QTextEdit>

#include "splash.h"
#include "currentserialport.h"

#ifdef QT_DEBUG
//    #define MENU_TEST
    #define TEST_SPLASH
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void FileOpen();
    void FileSave();
    bool FileSaveAs();
    void FileQuit();
    void EditCopy();
    void ToolConnect();
    void HelpContents();
    void HelpAbout();

    void ShowSplash();
    void serialport(); //change this after getting splash to work

private:
    Ui::MainWindow *ui;
    CurrentSerialPort* SerialPort;

    void ConnectMenu();
    void LoadDisplay();
    void ConnectSplash();
    bool SaveFile(const QString& fileName);
    QTextEdit* Display;

    QString saveFileName;
};

#endif // MAINWINDOW_H
