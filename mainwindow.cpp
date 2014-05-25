#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QProcess>
#include <QtCore>
#include <QString>
#include <QMessageBox>
#include <QDirModel>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QTreeView>
#include <QModelIndex>

#define MAIN_FILE 1
#define INO_HEADER 2

QString fname;
bool ef=false;
QString root="";
bool arduino=false;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setVisible(false);
    ui->label->setText("");
    ui->textEdit->setPlainText("task main()\n{\n\n}");
    highlighter = new Highlighter(ui->textEdit->document());

    QFile file("mainwindow.h");
    if (file.open(QFile::ReadOnly | QFile::Text))
        ui->textEdit->setPlainText(file.readAll());

    #ifdef __unix__

    #else
    ui->actionUse_root_You_have_to_start_the_application_with_root_rights_2->setVisible(false);

    #endif

    update_treeview();
}

void MainWindow::update_treeview()
{
    model = new QDirModel(this);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    QModelIndex homeIndex;
    /*if(fname.isEmpty())
        homeIndex = model->index(QDesktopServices::storageLocation(QDesktopServices::HomeLocation));
    else*/
        homeIndex = model->index(fname);
    ui->treeView->setModel(model);
    //ui->treeView->setRootIndex(homeIndex);
    ui->treeView->expand(homeIndex);
    ui->treeView->scrollTo(homeIndex);
    ui->treeView->setCurrentIndex(homeIndex);
    ui->treeView->resizeColumnToContents(0);
    ui->treeView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


QString file_name(int file)
{
    if(arduino&&file==MAIN_FILE)
        return "Tools/arduino/main.nxc";
    else
        return fname;

}

void MainWindow::on_actionSave_File_triggered()                     //Speichern
{
    if(fname.isEmpty())
    {
        if(arduino)
            fname= QFileDialog::getSaveFileName(this, tr("Save File"),"~/Sketch.ino",tr("Sketches (*.ino)"));
        else
            fname= QFileDialog::getSaveFileName(this, tr("Save File"),"~/Program.nxc",tr("Programms (*.nxc)"));
    }
    QFile outfile;
    outfile.setFileName(fname);
    outfile.open(QIODevice::Truncate | QIODevice::Text|QFile::ReadWrite);
    QTextStream out(&outfile);
    out << ui->textEdit->toPlainText() << endl;
    update_treeview();
}

void MainWindow::on_actionChose_File_triggered()                    //Öffnen
{
    if(arduino)
        fname= QFileDialog::getOpenFileName(this, tr("Save File"),"~/Sketch.ino",tr("Sketches (*.ino)"));
    else
        fname= QFileDialog::getOpenFileName(this, tr("Save File"),"~/Program.nxc",tr("Programms (*.nxc)"));
    QFile file(fname);

    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream ReadFile(&file);
    ui->textEdit->setText(ReadFile.readAll());

    update_treeview();
}

void MainWindow::on_actionCreate_new_File_triggered()               //Neue Datei
{
    ui->textEdit->clear();
}

void MainWindow::on_actionFinish_triggered()                        //Beenden
{
     qApp->quit();
}

void MainWindow::on_actionInstall_Compiler_triggered()              //Compiler Installieren
{
   /* QProcess process;
    process.start("svn co https://svn.code.sf.net/p/bricxcc/code/");
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();*/

    ui->textBrowser->append("Test");
}

void MainWindow::on_actionCompile_Program_triggered()
{
    if(fname.isEmpty())
        on_actionSave_File_triggered() ;
    QString befehl;
    befehl =root +"nbc -S=USB0 "+file_name(MAIN_FILE);
    if(ef)
        befehl+=" -EF";
    QProcess process;
    process.start(befehl);
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    ui->textBrowser->setText(befehl);
   // ui->textBrowser->append(stdout);
    ui->textBrowser->append(stderr);
    if(stderr.isEmpty())
        ui->textBrowser->append("Finished");
    else
    {
        QTextCursor cursor = ui->textEdit->textCursor();
        if(stderr.indexOf("line")!=-1)
        {
            int pos = 0;
            for(int zaehler=5 ; stderr.at(stderr.indexOf("line")+zaehler).digitValue()!=-1 ; zaehler++ )
                    pos = pos*10 + stderr.at(stderr.indexOf("line")+zaehler).digitValue();

            ui->label->setText(QString::number(pos));
            if(pos>0)
            {
                cursor.setPosition(0, QTextCursor::MoveAnchor);
                cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, pos-1);
                ui->textEdit->setTextCursor(cursor);
                QColor lineColor = QColor(Qt::red).lighter(160);
                QTextEdit::ExtraSelection selection;
                QList<QTextEdit::ExtraSelection> extraSelections;

                selection.format.setBackground(lineColor);
                selection.format.setProperty(QTextFormat::FullWidthSelection, true);
                selection.cursor = cursor;
                selection.cursor.clearSelection();
                extraSelections.append(selection);

                ui->textEdit->setExtraSelections(extraSelections);
            }
        }
    }
    ui->textEdit->setFocus();
}

void MainWindow::on_actionDownload_Program_to_the_NXT_triggered()
{
    if(fname.isEmpty())
        on_actionSave_File_triggered() ;
    QString befehl;
    befehl =root+"nbc -S=USB0 "+file_name(MAIN_FILE)+" -d ";
    if(ef)
        befehl+=" -EF";
    QProcess process;
    process.start(befehl);
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    ui->textBrowser->setText(befehl);
    //ui->textBrowser->append(stdout);
    ui->textBrowser->append(stderr);
    if(stderr.isEmpty())
        ui->textBrowser->append("Finished");
    else
    {
        QTextCursor cursor = ui->textEdit->textCursor();
        if(stderr.indexOf("line")!=-1)
        {
            int pos = 0;
            for(int zaehler=5 ; stderr.at(stderr.indexOf("line")+zaehler).digitValue()!=-1 ; zaehler++ )
                    pos = pos*10 + stderr.at(stderr.indexOf("line")+zaehler).digitValue();

            ui->label->setText(QString::number(pos));
            if(pos>0)
            {
                cursor.setPosition(0, QTextCursor::MoveAnchor);
                cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, pos-1);
                ui->textEdit->setTextCursor(cursor);
                QColor lineColor = QColor(Qt::red).lighter(160);
                QTextEdit::ExtraSelection selection;
                QList<QTextEdit::ExtraSelection> extraSelections;

                selection.format.setBackground(lineColor);
                selection.format.setProperty(QTextFormat::FullWidthSelection, true);
                selection.cursor = cursor;
                selection.cursor.clearSelection();
                extraSelections.append(selection);

                ui->textEdit->setExtraSelections(extraSelections);
            }
        }
    }
    ui->textEdit->setFocus();
}

void MainWindow::on_actionDownload_Program_and_run_it_triggered()
{
    if(fname.isEmpty())
        on_actionSave_File_triggered() ;
    QString befehl;
    befehl =root+"nbc -S=USB0 "+file_name(MAIN_FILE)+" -r ";
    if(ef)
        befehl+=" -EF";
    QProcess process;
    process.start(befehl);
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    ui->textBrowser->setText(befehl);
    //ui->textBrowser->append(stdout);
    ui->textBrowser->append(stderr);
    if(stderr.isEmpty())
        ui->textBrowser->append("Finished");
    else
    {
        QTextCursor cursor = ui->textEdit->textCursor();
        if(stderr.indexOf("line")!=-1)
        {
            int pos = 0;
            for(int zaehler=5 ; stderr.at(stderr.indexOf("line")+zaehler).digitValue()!=-1 ; zaehler++ )
                    pos = pos*10 + stderr.at(stderr.indexOf("line")+zaehler).digitValue();

            ui->label->setText(QString::number(pos));
            if(pos>0)
            {
                cursor.setPosition(0, QTextCursor::MoveAnchor);
                cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, pos-1);
                ui->textEdit->setTextCursor(cursor);
                QColor lineColor = QColor(Qt::red).lighter(160);
                QTextEdit::ExtraSelection selection;
                QList<QTextEdit::ExtraSelection> extraSelections;

                selection.format.setBackground(lineColor);
                selection.format.setProperty(QTextFormat::FullWidthSelection, true);
                selection.cursor = cursor;
                selection.cursor.clearSelection();
                extraSelections.append(selection);

                ui->textEdit->setExtraSelections(extraSelections);
            }
        }
    }
    ui->textEdit->setFocus();
}

void MainWindow::on_actionEnhanced_Firmware_toggled(bool arg1)
{
    ef=arg1;
}

void MainWindow::on_actionUse_root_You_have_to_start_the_application_with_root_rights_2_toggled(bool arg1)
{
    if(arg1)
    {
        #ifdef __unix__
        root="sudo ";
        #else
        root="";
        #endif
    }
    else
        root="";
}

void MainWindow::on_actionFind_triggered()
{
    ui->lineEdit->setVisible(true);
    ui->lineEdit->setFocus();
    ui->lineEdit->setCursorPosition(0);
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString text = ui->textEdit->toPlainText();
    QTextCursor cursor = ui->textEdit->textCursor();
    if(text.indexOf(ui->lineEdit->text())!=-1)
    {
        ui->lineEdit->setVisible(false);
        cursor.setPosition(text.indexOf(ui->lineEdit->text()),QTextCursor::MoveAnchor);
        ui->textEdit->setFocus();
        ui->lineEdit->clear();
        ui->textEdit->setTextCursor(cursor);
    }
    else
    {
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::red);
        ui->lineEdit->setPalette(*palette);
    }
}


void MainWindow::on_textEdit_textChanged()
{
    QString text = ui->textEdit->toPlainText();
    if(!text.isEmpty())
    {
        QTextCursor cursor = ui->textEdit->textCursor();
        long pos = cursor.position()-1;
        if(pos<0)
            pos=0;
        QByteArray c_text = text.toAscii();
        bool apply=false;
        if(c_text.at(pos)=='('&&c_text.at(pos+1)!=')'&&c_text.at(pos-1)!='(')
        {
            text.insert(pos+1, ")");
            apply=true;
        }
        /*else if(c_text.at(pos)=='"')
        {
            text.insert(pos+1, "\"");
            apply=true;
        }*/
        else if(c_text.at(pos)=='{'&&c_text.at(pos+1)!='}'&&c_text.at(pos-1)!='{')
        {
            text.insert(pos+1, "}");
            apply=true;
        }
        else if(c_text.at(pos)=='['&&c_text.at(pos+1)!=']'&&c_text.at(pos-1)!='[')
        {
            text.insert(pos+1, "]");
            apply=true;
        }

        if(apply)
        {
            ui->textEdit->setPlainText(text);
            cursor.setPosition(pos+1,QTextCursor::MoveAnchor);
            ui->textEdit->setTextCursor(cursor);
        }
    }


}

void MainWindow::on_actionUse_the_Arduino_Language_to_Program_your_NXT_toggled(bool arg1)
{
    arduino=arg1;
    if(arg1)
    {
        QFile file_main("Tools/arduino/main.nxc");

        file_main.open(QFile::ReadOnly | QFile::Text);

        QTextStream ReadFile(&file_main);
        QString inhalt = ReadFile.readAll();

        file_main.close();


        QFile file(file_name(MAIN_FILE));

        file.open(QIODevice::Truncate |QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << "#include \""+file_name(INO_HEADER)+"\" \n";
        out << inhalt;

        // optional, as QFile destructor will already do it:
        file.close();

        ui->textEdit->setPlainText("void setup()\n{\n\n}\n\nvoid loop()\n{\n\n}");
    }

}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    long pos = cursor.blockNumber()+1;
    ui->label->setText(QString::number(pos));
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selection;

    QColor lineColor = QColor(Qt::yellow).lighter(160);

    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = cursor;
    selection.cursor.clearSelection();
    extraSelections.append(selection);

    ui->textEdit->setExtraSelections(extraSelections);

}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if(model->fileInfo(index).isDir())
        return;
    fname=model->fileName(index);
    QFile file(fname);

    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream ReadFile(&file);
    ui->textEdit->setText(ReadFile.readAll());
}
