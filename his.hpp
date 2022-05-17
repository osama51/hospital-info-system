#ifndef HIS_HPP
#define HIS_HPP


#include <iostream>
#include<string>
#include <QApplication>

namespace his {

using namespace std;

struct drugs_data
{
QString drug_name[3]; //assume every patient is only allowed to 3 drugs!!
QString time[3];
QString date;
QString every[3];
};

struct  patient {
QString patient_ID;
QString name ;
QString sex ;
QString patient_phone;
QString address;
QString birth_date;
QString medical_histroy;
QString allergy ;
QString systolic_blood_pressure;
QString diastolic_blood_pressure;
QString heart_rate;
QString temperature;
QString date;
QString prescription;
drugs_data drugs[10];
int last = -1; //holds last element_drug edited

};
struct queue{
int rear = -1, fronte = -1; //intentional e
patient item[10];

};
extern queue q;

struct icu {
QString icu_name ;
QString  icu_code;
QString icu_manager_name;
QString icu_beds_number;
queue q;
};


extern icu ICU;
//extern int icu_count; // was trying to use a variable as an argument
                        //to the array.. but alas


//void enqueue(icu *,qint32 ,QString,QString,QString,QString,QString,QString,QString,QString,QString,QString,QString,QString);
//void dequeue(icu *,QString);
//bool isFull(icu *,QString);
//bool isEmpty(icu *,QString );
//void display(icu *,QString);
//int check_id(icu *,QString,QString);
//void display_ICU_information(icu *,QString);

}
#endif // HIS_HPP












