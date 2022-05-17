#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qlistwidget.h"
#include <QTreeWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void addRoot(QString patientid, QString drug, QString time, QString every, QString date);
    void addChild(QString space, QString drug, QString time, QString every);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();


    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);


    void on_radioButton_icu1_drugs_clicked();
    void on_radioButton_icu2_drugs_clicked();
    void on_radioButton_icu3_drugs_clicked();

    void on_add_drugs_clicked();

    void on_listWidget_drugs_itemClicked(QListWidgetItem *item);

    void on_edit_drugs_clicked();

private:
    Ui::MainWindow *ui;
    //patient_info *patient_info(QString& id);

};
#endif // MAINWINDOW_H
