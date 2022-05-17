#include "patient_data.h"
#include "ui_patient_data.h"
#include <his.hpp>

//using namespace his;
patient_data::patient_data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::patient_data)
{
    ui->setupUi(this);
}

patient_data::~patient_data()
{
    delete ui;
}

void patient_data::on_save_clicked()
{
    QString id = ui->patient_id->text();
    QString name = ui->name->text();
    QString bdate = ui->birth_date->text();
    QString phone = ui->phone_number->text();
    QString address = ui->address->text();
    QString med_history = ui->med_history->text();
    QString allergy = ui->allergy->text();
    QString gender = ui->gender->currentText();
    QString syst = ui->systolic->text();
    QString diast = ui->diastolic->text();
    QString temp = ui->temp->text();
    QString heart_rate = ui->heart_rate->text();

//incomplete save button
// having difficulties passing data from here to mainwindow.cpp

}
