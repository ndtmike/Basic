#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConnectMenu();
    LoadDisplay();
    ConnectSplash();
    saveFileName = "";
}

MainWindow::~MainWindow()
{
    delete SerialPort;
    delete Display;
    delete ui;
}
void MainWindow::LoadDisplay()
{
    Display = new QTextEdit;
    setCentralWidget(Display);

}

void MainWindow::ConnectSplash()
{
#ifndef QT_DEBUG
    QTimer* init_timer = new QTimer(this);
    init_timer->singleShot(100, this, SLOT(showSplash()));
#endif

#ifdef TEST_SPLASH
    QTimer* init_timer = new QTimer(this);
    init_timer->singleShot(100, this, SLOT(ShowSplash()));
#endif

}

void MainWindow::ShowSplash()
{
    const int five_sec = 5000;
    SplashDialog* splash = new SplashDialog();
    splash->setModal( true );
    splash->show();

    QTimer* splash_timer = new QTimer(this);
    splash_timer->singleShot(five_sec, this, SLOT(serialport()));
}

void MainWindow::serialport() //change name!!
{
    SerialPort = new CurrentSerialPort(this);
    if(!SerialPort->CheckSerialPort()) delete SerialPort;
}

void MainWindow::ConnectMenu()
{
    connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(FileOpen()));
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(FileSave()));
    connect(ui->action_Save_As, SIGNAL(triggered()), this, SLOT(FileSaveAs()));
    connect(ui->action_Quit, SIGNAL(triggered()), this, SLOT(FileQuit()));
    connect(ui->action_Copy, SIGNAL(triggered()), this, SLOT(EditCopy()));
    connect(ui->action_Connect, SIGNAL(triggered()), this, SLOT(ToolConnect()));
    connect(ui->action_Help, SIGNAL(triggered()), this, SLOT(HelpContents()));
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(HelpAbout()));
}

void MainWindow::FileOpen()
{
#ifdef MENU_TEST
    QMessageBox::information( this,"FileOpen", "File Open OK!");
#endif

    QString fileName = "";
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Text File"), "", tr("Text FIles (*.txt)"));
    saveFileName = fileName;
    QFile file(fileName);
    QTextStream load(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    file.open(QFile::ReadOnly | QFile::Text);
    Display->setPlainText(load.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    file.close();
}

void MainWindow::FileSave()
{
#ifdef MENU_TEST
    QMessageBox::information( this,"FileSave", "File Save OK!");
#endif
    if(saveFileName != ""){
        SaveFile(saveFileName);
    }else{
        FileSaveAs(); //might need to put a test here for a cancel
    }
}

bool MainWindow::FileSaveAs()
{
#ifdef MENU_TEST
    QMessageBox::information( this,"FileSaveAs", "File Save As OK!");
#endif
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("Text FIles (*.txt)"));
    QStringList files;
    if (dialog.exec())
        files = dialog.selectedFiles();
    else
        return false;

    return SaveFile(files.at(0));
}

void MainWindow::FileQuit()
{
#ifdef MENU_TEST
    QMessageBox::information( this,"FileQuit", "File Quit OK!");
#endif
    close();
}

void MainWindow::EditCopy()
{
#ifdef MENU_TEST
    QMessageBox::information( this,"EditCopy", "Edit Copy OK!");
#endif
}

void MainWindow::ToolConnect()
{
#ifdef MENU_TEST
    QMessageBox::information( this,"ToolConnect", "Tool Connect OK!");
#endif
    serialport();
}

void MainWindow::HelpContents()
{
#ifdef MENU_TEST
    QMessageBox::information( this,"HelpContents", "Help Contents OK!");
#endif
}

void MainWindow::HelpAbout()//don't forget to change this for new software
{
#ifdef MENU_TEST
    QMessageBox::information( this,"Help About", "Help About OK!");
#endif
    QString s;
    QTextStream toabout(&s);

    toabout << tr("The <b>Basic Software</b> is used with the <br>") <<
               tr("<b><i>James Instruments Inc.</i></b> Basic.<br><br>")<<
               tr("USA: +1773.4636565<br>")<<
               tr("Europe: +31.548.659032<br>")<<
               tr("Email: <a href=\"mailto:info@ndtjames.com?Subject=Reboundlinx\" target=\"_top\">info@ndtjames.com</a><br>")<<
               tr("Web: <a href=\"http://www.ndtjames.com\">http://www.ndtjames.com</a><br>")<<
               tr("Copyright 2016");

    QMessageBox::information(this, tr("About Basic"), s);
}

bool MainWindow::SaveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << Display->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    saveFileName = fileName;
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}
