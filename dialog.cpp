#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(CItem &_i, QWidget *parent, const CItem* fa) :
    QDialog(parent),
    input(_i),
    ui(new Ui::Dialog)
{
    setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
    ui->dateTimeEdit->setCalendarPopup(true);
    if(fa==NULL)
        ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    else
        ui->dateTimeEdit->setDateTime(fa->ddl);
    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm");
    ui->dateTimeEdit_2->setCalendarPopup(true);
    if(fa==NULL)
        ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    else
        ui->dateTimeEdit_2->setDateTime(fa->reminder_time);
    ui->dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd hh:mm");
    if(fa!=NULL){
        ui->vital_checkBox->setEnabled(false);
        input.is_vital = fa->is_vital;
        if(input.is_vital)
            ui->vital_checkBox->setCheckState(Qt::Checked);
    }
}
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    input.name = ui->textEdit->toPlainText();
    input.ddl = ui->dateTimeEdit->dateTime();
    input.is_finish = false;
    input.reminder_time = ui->dateTimeEdit_2->dateTime();
}


void Dialog::on_wholeday_checkBox_stateChanged(int state)
{
    if(state==Qt::Checked){
        input.is_whole_day=true;
        ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd");
    }
    else{
        input.is_whole_day=false;
        ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm");
    }
}


void Dialog::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    ui->dateTimeEdit_2->setDateTime(dateTime);
}


void Dialog::on_vital_checkBox_stateChanged(int state)
{
    if(state==Qt::Checked){
        input.is_vital=true;
    }
    else{
        input.is_vital=false;
    }
}

