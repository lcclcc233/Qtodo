#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDateTime>
#include "citem.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    ~Dialog();
    CItem &input;
    explicit Dialog(CItem &_i, QWidget *parent = nullptr,const CItem* fa=NULL, const QDateTime qdt=QDateTime::currentDateTime());
private slots:
    void on_buttonBox_accepted();

    void on_wholeday_checkBox_stateChanged(int arg1);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_vital_checkBox_stateChanged(int arg1);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
