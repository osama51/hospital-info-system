#ifndef PATIENT_DATA_H
#define PATIENT_DATA_H

#include <QDialog>

namespace Ui {
class patient_data;
}

class patient_data : public QDialog
{
    Q_OBJECT

public:
    explicit patient_data(QWidget *parent = nullptr);
    ~patient_data();

private slots:
    void on_save_clicked();

private:
    Ui::patient_data *ui;
};

#endif // PATIENT_DATA_H
