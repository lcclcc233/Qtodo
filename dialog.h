#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
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
    explicit Dialog(CItem &_i, QWidget *parent = nullptr);
private slots:
    void on_buttonBox_accepted();

    void on_wholeday_checkBox_stateChanged(int arg1);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
