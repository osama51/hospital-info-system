#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patient_data.h"
#include "his.hpp"
#include <QMessageBox>
#include <QListWidget>
#include <QDate>


#define SIZE 10


//int icu_count = 3;
his::icu ICU [3];
his::queue q;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


bool isEmpty(his::icu *ICU,int icu_number)
{
    //circular queue
    if(ICU[icu_number].q.fronte == -1){ return true;}
    else { return false;}


//    if (ICU[icu_number].q.fronte == ICU[icu_number].q.rear){
//        ICU[icu_number].q.fronte = ICU[icu_number].q.rear = -1;
//        return 1;
//    }
//    else
//        return 0;
}

bool isFull(his::icu *ICU,int icu_number)
{
    //circular queue
    int sub = ICU[icu_number].q.rear - ICU[icu_number].q.fronte + 1;
    if( sub == SIZE || sub == 0)
        return true;
    else{
        return false;
    }

//    if (ICU[icu_number].q.rear - ICU[icu_number].q.fronte == 10 ){
//        return 1;
//    }
//    else
//        return 0;

}



void enqueue(
    his::icu *ICU,
    int icu_number,
    QString patient_ID,
    QString name ,
    QString sex ,
    QString patient_phone,
    QString address,
    QString birth_date,
    QString medical_histroy,
    QString allergy ,
    QString systolic_blood_pressure,
    QString diastolic_blood_pressure,
    QString heart_rate,
    QString temperature)
{

    if (isFull(&ICU[0], icu_number))
    {
         std::cout<<"ICU is full!"<<std::endl;}
    else {
        if(isEmpty(&ICU[0], icu_number)){ ICU[icu_number].q.fronte = 0;}
        ICU[icu_number].q.rear = (ICU[icu_number].q.rear + 1) % SIZE;
        int n = ICU[icu_number].q.rear;

        ICU[icu_number].q.item[n].patient_ID = patient_ID;
        ICU[icu_number].q.item[n].name = name;
        ICU[icu_number].q.item[n].address = address;
        ICU[icu_number].q.item[n].allergy = allergy;
        ICU[icu_number].q.item[n].birth_date = birth_date;
        ICU[icu_number].q.item[n].diastolic_blood_pressure = diastolic_blood_pressure;
        ICU[icu_number].q.item[n].heart_rate = heart_rate;
        ICU[icu_number].q.item[n].medical_histroy = medical_histroy;
        ICU[icu_number].q.item[n].patient_phone = patient_phone;
        ICU[icu_number].q.item[n].sex = sex;
        ICU[icu_number].q.item[n].systolic_blood_pressure = systolic_blood_pressure;
        ICU[icu_number].q.item[n].temperature = temperature;
        ICU[icu_number].q.item[n].date = QDate::currentDate().toString();
    }

}

void dequeue(his::icu *ICU,int icu_number){
if(!isEmpty(&ICU[0], icu_number))
    {
        if(ICU[icu_number].q.fronte == ICU[icu_number].q.rear)
        {
            ICU[icu_number].q.rear = -1; ICU[icu_number].q.fronte = -1;
        }else
        {
            ICU[icu_number].q.fronte = (ICU[icu_number].q.fronte + 1) % SIZE;
        }
    }
}

//this part was for a new window but I'm having issues declaring arrays globally
/*
void MainWindow::on_pushButton_clicked()
{
    patient_data patient_data;
    patient_data.setModal(true);
    patient_data.exec();
    if(ui->radioButton->isChecked())
    {
    }
}
*/

void enqueueDrug(
        his::icu *ICU,
        int icu_number,
        QString patient_ID,
        QString drug_1 ,
        QString drug_2 ,
        QString drug_3,
        QString time_1,
        QString time_2,
        QString time_3,
        QString every_1,
        QString every_2,
        QString every_3)
{
    for(int i = 0; i <= SIZE - 1; ++i)
    {
        if(ICU[icu_number].q.item[i].patient_ID == patient_ID)
        {
            QString today = QDate::currentDate().toString();
            int last = ICU[icu_number].q.item[i].last;
            if(ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].date != today)
            {
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].drug_name[0] = drug_1;
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].time[0] = time_1;
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].every[0] = every_1;
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].drug_name[1] = drug_2;
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].time[1] = time_2;
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].every[1] = every_2;
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].drug_name[2] = drug_3;
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].time[2] = time_3;
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].every[2] = every_3;
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].date = today;
                ++ICU[icu_number].q.item[i].last;
            }
        }
    }
}

void editDrug(
        his::icu *ICU,
        int icu_number,
        QString patient_ID,
        QString drug_1 ,
        QString drug_2 ,
        QString drug_3,
        QString time_1,
        QString time_2,
        QString time_3,
        QString every_1,
        QString every_2,
        QString every_3)
{
    for(int i = 0; i <= SIZE - 1; ++i)
    {
        if(ICU[icu_number].q.item[i].patient_ID == patient_ID)
        {
            int last = ICU[icu_number].q.item[i].last - 1;
            if(ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].date == QDate::currentDate().toString())
            {
                if(!drug_1.isEmpty()){ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].drug_name[0] = drug_1;
                                      ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].time[0] = time_1;
                                      ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].every[0] = every_1;}
                if(!drug_2.isEmpty()){ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].drug_name[1] = drug_2;
                                      ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].time[1] = time_2;
                                      ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].every[1] = every_2;}
                if(!drug_3.isEmpty()){ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].drug_name[2] = drug_3;
                                      ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].time[2] = time_3;
                                      ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].every[2] = every_3;}
                ICU[icu_number].q.item[i].drugs[(last+1)%SIZE].date = QDate::currentDate().toString();
            }
        }
    }

}

//__________________________________________________
//Page 1 in "Patients" tab starts here: Add / Remove
//__________________________________________________

void MainWindow::on_radioButton_clicked() // ICU 1

{
    ui->listWidget->clear();
    if(!isEmpty(&ICU[0], 0)){


        if(ICU[0].q.fronte == ICU[0].q.rear)
        {
            ui->listWidget->addItem(ICU[0].q.item[ICU[0].q.fronte].patient_ID);
            //++iterate;
        }else{
            for(int iterate = ICU[0].q.fronte; iterate%SIZE != ICU[0].q.rear; ++iterate)
            {
                QString qstr = ICU[0].q.item[iterate%SIZE].patient_ID;
                ui->listWidget->addItem(qstr);
            }
            ui->listWidget->addItem(ICU[0].q.item[ICU[0].q.rear].patient_ID);
        }
    }
}

void MainWindow::on_radioButton_2_clicked() // ICU 2
{
    ui->listWidget->clear();
    if(!isEmpty(&ICU[0], 1)){

        if(ICU[1].q.fronte == ICU[1].q.rear)
        {
            ui->listWidget->addItem(ICU[1].q.item[ICU[1].q.fronte].patient_ID);
            //++iterate;
        }else{
            for(int iterate = ICU[1].q.fronte; iterate%SIZE != ICU[1].q.rear; ++iterate)
            {
                QString qstr = ICU[1].q.item[iterate%SIZE].patient_ID;
                ui->listWidget->addItem(qstr);
            }
            ui->listWidget->addItem(ICU[1].q.item[ICU[1].q.rear].patient_ID);
        }
    }
}

void MainWindow::on_radioButton_3_clicked() //ICU 3
{
    ui->listWidget->clear();
    if(!isEmpty(&ICU[0], 2)){

        if(ICU[2].q.fronte == ICU[2].q.rear)
        {
            ui->listWidget->addItem(ICU[2].q.item[ICU[2].q.fronte].patient_ID);
            //++iterate;
        }else{
            for(int iterate = ICU[2].q.fronte; iterate%SIZE != ICU[2].q.rear; ++iterate)
            {
                QString qstr = ICU[2].q.item[iterate%SIZE].patient_ID;
                ui->listWidget->addItem(qstr);
            }
            ui->listWidget->addItem(ICU[2].q.item[ICU[2].q.rear].patient_ID);
        }
    }
}



void MainWindow::on_pushButton_2_clicked() //Insert button
{

if(!ui->id->text().isEmpty())
    {
    int  num;
    QString id = ui->id->text();
    QString name = ui->name->text();
    QString gender = ui->gender->currentText();
    QString phone = ui->phone->text();
    QString address = ui->address->text();
    QString bdate = ui->dob->text();
    QString med_history = ui->history->text();
    QString allergy = ui->allergy->text();
    QString syst = ui->syst->text();
    QString diast = ui->diast->text();
    QString heart_rate = ui->heart->text();
    QString temp = ui->temp->text();

    if(ui->radioButton->isChecked()){ num = 0;}
    else if(ui->radioButton_2->isChecked()){ num = 1;}
    else if (ui->radioButton_3->isChecked()){ num = 2;}
    else{ return;}

    enqueue(&ICU[0], num, id, name, gender, phone, address, bdate,
            med_history, allergy, syst, diast, heart_rate, temp);

    switch(num){
        case 0: ui->radioButton->click();
        break;
        case 1: ui->radioButton_2->click();
        break;
        case 2: ui->radioButton_3->click();
        break;

    }

    //tracking rear and front counting
    //could be changed to the status of ICU later
    int rear = ICU[num].q.rear;
    ui->lcdNumber_rear->display(rear);
    int front = ICU[num].q.fronte;
    ui->lcdNumber_front->display(front);

    if(isFull(&ICU[0], num))
    {
        ui->msgLabel->setText("ICU is Full!");
    }else{ui->msgLabel->setText(" ");}
    }
}

void MainWindow::on_pushButton_4_clicked() //Remove button
{
    int i;
    if(ui->radioButton->isChecked()){i = 0; }
    else if(ui->radioButton_2->isChecked()){i = 1;}
    else if (ui->radioButton_3->isChecked()){i = 2;}
    else{ return;}


    dequeue(&ICU[0], i);
    switch(i){
        case 0: ui->radioButton->click();
        break;
        case 1: ui->radioButton_2->click();
        break;
        case 2: ui->radioButton_3->click();
        break;

    }

    if(isFull(&ICU[0], i))
    {
        ui->msgLabel->setText("ICU is Full!");
    }else{ui->msgLabel->setText(" ");}

    //tracking rear and front counting
    //could be changed to the status of ICU later
    int front = ICU[i].q.fronte;
    ui->lcdNumber_front->display(front);
    int rear = ICU[i].q.rear;
    ui->lcdNumber_rear->display(rear);

}



//You can double click an item to view its information.
//it's awful and the way I search for the patient makes the msg reopens for every
//duplicate id in the ICU from the past if not overwritten, that's the hospital's issue though
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //showing patient info via info message
    //not sufficient, but will do for now
    QString id = item->text();

    int num;
    if(ui->radioButton->isChecked()){num = 0; }
    else if(ui->radioButton_2->isChecked()){num = 1;}
    else if (ui->radioButton_3->isChecked()){num = 2;}
    else{ return;}

    for(int i = 0; i <= SIZE - 1; ++i)
    {
        if(ICU[num].q.item[i].patient_ID == id)
        {

            QMessageBox::information(this, QString("Patient %1").arg(id),
                                           QString(" ID: %1\n Name: %2\n Gender: %3\n Phone: %4\n "
                                                      "Address: %5\n Birth Date: %6\n Med History: %7\n "
                                                      "Allergy: %8\n Admittance Date: %9")
                                     .arg(ICU[num].q.item[i].patient_ID).arg(ICU[num].q.item[i].name)
                                     .arg(ICU[num].q.item[i].sex).arg(ICU[num].q.item[i].patient_phone)
                                     .arg(ICU[num].q.item[i].address).arg(ICU[num].q.item[i].birth_date)
                                     .arg(ICU[num].q.item[i].medical_histroy).arg(ICU[num].q.item[i].allergy)
                                     .arg(ICU[num].q.item[i].date));
        }
    }
//    patient_info  patient_info(id);
//    patient_info.show();
}

//_________________________________________________
//From here starts Page 2 in "Patients" tab: Drugs
//_________________________________________________


void MainWindow::on_radioButton_icu1_drugs_clicked() // ICU 1 - Drugs
{
    ui->listWidget_drugs->clear();
    if(!isEmpty(&ICU[0], 0)){

        if(ICU[0].q.fronte == ICU[0].q.rear)
        {
            ui->listWidget_drugs->addItem(ICU[0].q.item[ICU[0].q.fronte].patient_ID);
        }else{
            for(int iterate = ICU[0].q.fronte; iterate%SIZE != ICU[0].q.rear; ++iterate)
            {
                QString qstr = ICU[0].q.item[iterate%SIZE].patient_ID;
                ui->listWidget_drugs->addItem(qstr);
            }
            ui->listWidget_drugs->addItem(ICU[0].q.item[ICU[0].q.rear].patient_ID);
        }
    }
}

void MainWindow::on_radioButton_icu2_drugs_clicked() // ICU 2 - Drugs
{
    ui->listWidget_drugs->clear();
    if(!isEmpty(&ICU[0], 0)){

        if(ICU[1].q.fronte == ICU[1].q.rear)
        {
            ui->listWidget_drugs->addItem(ICU[1].q.item[ICU[1].q.fronte].patient_ID);
        }else{
            for(int iterate = ICU[1].q.fronte; iterate%SIZE != ICU[1].q.rear; ++iterate)
            {
                QString qstr = ICU[1].q.item[iterate%SIZE].patient_ID;
                ui->listWidget_drugs->addItem(qstr);
            }
            ui->listWidget_drugs->addItem(ICU[1].q.item[ICU[1].q.rear].patient_ID);
        }
    }
}

void MainWindow::on_radioButton_icu3_drugs_clicked() // ICU 3 - Drugs
{
    ui->listWidget_drugs->clear();
    if(!isEmpty(&ICU[0], 0)){

        if(ICU[2].q.fronte == ICU[2].q.rear)
        {
            ui->listWidget_drugs->addItem(ICU[2].q.item[ICU[2].q.fronte].patient_ID);
        }else{
            for(int iterate = ICU[2].q.fronte; iterate%SIZE != ICU[2].q.rear; ++iterate)
            {
                QString qstr = ICU[2].q.item[iterate%SIZE].patient_ID;
                ui->listWidget_drugs->addItem(qstr);
            }
            ui->listWidget_drugs->addItem(ICU[2].q.item[ICU[2].q.rear].patient_ID);
        }
    }
}


void MainWindow::on_add_drugs_clicked()
{

    if(!ui->id_drugs->text().isEmpty())
    {
        int  num;
        QString id = ui->id_drugs->text();
        QString drug_1 = ui->drug_1->text(); QString time_1 = ui->time1_drugs->text(); QString every_1 = ui->spinBox_every1->text();
        QString drug_2 = ui->drug_2->text(); QString time_2 = ui->time2_drugs->text(); QString every_2 = ui->spinBox_every2->text();
        QString drug_3 = ui->drug_3->text(); QString time_3 = ui->time3_drugs->text(); QString every_3 = ui->spinBox_every3->text();

        if(ui->radioButton_icu1_drugs->isChecked()){ num = 0;}
        else if(ui->radioButton_icu2_drugs->isChecked()){ num = 1;}
        else if (ui->radioButton_icu3_drugs->isChecked()){ num = 2;}
        else{ return;}

        if(!isEmpty(&ICU[0], num))
        {
            enqueueDrug(&ICU[0], num, id, drug_1, drug_2, drug_3, time_1, time_2,
            time_3, every_1, every_2, every_3);
        }
    switch(num){
        case 0: ui->radioButton_icu1_drugs->click();
        break;
        case 1: ui->radioButton_icu2_drugs->click();
        break;
        case 2: ui->radioButton_icu3_drugs->click();
        break;

        }
    }
}


void MainWindow::addRoot(QString patientid, QString drug, QString time, QString every, QString date)
{
    QTreeWidgetItem *patient = new QTreeWidgetItem(ui->treeWidget_drugs);
    patient->setText(0, patientid);
    patient->setText(1, drug);
    patient->setText(2, time);
    patient->setText(3, every);
    patient->setText(4, date);
}
void MainWindow::addChild(QString space, QString drug, QString time, QString every)
{
    QTreeWidgetItem *patient = new QTreeWidgetItem(ui->treeWidget_drugs);
    patient->setText(0, space);
    patient->setText(1, drug);
    patient->setText(2, time);
    patient->setText(3, every);


}


void MainWindow::on_listWidget_drugs_itemClicked(QListWidgetItem *item)
{
    ui->treeWidget_drugs->clear();
    int num ;
    if(ui->radioButton_icu1_drugs->isChecked()){ num = 0;}
    else if(ui->radioButton_icu2_drugs->isChecked()){ num = 1;}
    else if (ui->radioButton_icu3_drugs->isChecked()){ num = 2;}
    else{ return;}


    for(int i = 0; i <= SIZE - 1; ++i)
    {
        if(ICU[num].q.item[i].patient_ID == item->text())
        {
            QString space = QString();
            int last = ICU[num].q.item[i].last;
            for(int d = 0; d <= (last+1)%SIZE; ++d)
            {
                addRoot(item->text(),ICU[num].q.item[i].drugs[d].drug_name[0],
                        ICU[num].q.item[i].drugs[d].time[0],
                        ICU[num].q.item[i].drugs[d].every[0],
                        ICU[num].q.item[i].drugs[d].date);
                addChild( "", ICU[num].q.item[i].drugs[d].drug_name[1],
                        ICU[num].q.item[i].drugs[d].time[1],
                        ICU[num].q.item[i].drugs[d].every[1]);
                addChild( "", ICU[num].q.item[i].drugs[d].drug_name[2],
                        ICU[num].q.item[i].drugs[d].time[2],
                        ICU[num].q.item[i].drugs[d].every[2]);
            }
        }

}
}

void MainWindow::on_edit_drugs_clicked()
{
    if(!ui->id_drugs->text().isEmpty())
    {
        int  num;
        QString id = ui->id_drugs->text();
        QString drug_1 = ui->drug_1->text(); QString time_1 = ui->time1_drugs->text(); QString every_1 = ui->spinBox_every1->text();
        QString drug_2 = ui->drug_2->text(); QString time_2 = ui->time2_drugs->text(); QString every_2 = ui->spinBox_every2->text();
        QString drug_3 = ui->drug_3->text(); QString time_3 = ui->time3_drugs->text(); QString every_3 = ui->spinBox_every3->text();

        if(ui->radioButton_icu1_drugs->isChecked()){ num = 0;}
        else if(ui->radioButton_icu2_drugs->isChecked()){ num = 1;}
        else if (ui->radioButton_icu3_drugs->isChecked()){ num = 2;}
        else{ return;}

        if(!isEmpty(&ICU[0], num))
        {
            editDrug(&ICU[0], num, id, drug_1, drug_2, drug_3, time_1, time_2,
            time_3, every_1, every_2, every_3);
        }
    switch(num){
        case 0: ui->radioButton_icu1_drugs->click();
        break;
        case 1: ui->radioButton_icu2_drugs->click();
        break;
        case 2: ui->radioButton_icu3_drugs->click();
        break;

        }
    }
}
