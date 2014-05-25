#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QDirModel>

#include "highlighter.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void update_treeview();
    ~MainWindow();

private slots:
    void on_actionSave_File_triggered();

    void on_actionChose_File_triggered();

    void on_actionCreate_new_File_triggered();

    void on_actionFinish_triggered();

    void on_actionInstall_Compiler_triggered();

    void on_actionCompile_Program_triggered();

    void on_actionDownload_Program_to_the_NXT_triggered();

    void on_actionDownload_Program_and_run_it_triggered();

    void on_actionEnhanced_Firmware_toggled(bool arg1);


    void on_actionUse_root_You_have_to_start_the_application_with_root_rights_2_toggled(bool arg1);

    void on_actionFind_triggered();

    void on_lineEdit_returnPressed();


    void on_textEdit_textChanged();

    void on_actionUse_the_Arduino_Language_to_Program_your_NXT_toggled(bool arg1);

    void on_textEdit_cursorPositionChanged();


    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Highlighter *highlighter;
    QDirModel *model;
};

#endif // MAINWINDOW_H
