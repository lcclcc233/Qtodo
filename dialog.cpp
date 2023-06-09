#include "dialog.h"
#include "ui_dialog.h"
#include "qtodo.h"
Dialog::Dialog(CItem &_i, QWidget *parent, const CItem* fa, const QDateTime qdt) :
    QDialog(parent),
    input(_i),
    ui(new Ui::Dialog)
{
    setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
    ui->dateTimeEdit->setCalendarPopup(true);
    if(fa==NULL)
        ui->dateTimeEdit->setDateTime(qdt);
    else
        ui->dateTimeEdit->setDateTime(fa->ddl);
    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm");
    ui->dateTimeEdit_2->setCalendarPopup(true);
    if(fa==NULL)
        ui->dateTimeEdit_2->setDateTime(qdt);
    else
        ui->dateTimeEdit_2->setDateTime(fa->reminder_time);
    ui->dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd hh:mm");
    for(int i=0;i<((Qtodo*)parent)->categorycnt;i++){
        ui->comboBox->addItem(((Qtodo*)parent)->categoryname[i]);
    }
    if(fa!=NULL){
        ui->vital_checkBox->setEnabled(false);
        ui->comboBox->setEnabled(false);
        ui->week_checkBox->setEnabled(false);
        input.is_vital = fa->is_vital;
        if(input.is_vital)
            ui->vital_checkBox->setCheckState(Qt::Checked);
        input.category = fa->category;
        ui->comboBox->setCurrentText(input.category);
        input.is_weekly=fa->is_weekly;
        if(input.is_weekly)
            ui->week_checkBox->setCheckState(Qt::Checked);
    }
    ui->comboBox->setEditable(true);
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
    input.category = ui->comboBox->currentText();
    input.is_weekly = ui->week_checkBox->checkState();
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

