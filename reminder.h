#ifndef REMINDER_H
#define REMINDER_H

#include <QDialog>
#include <QTimer>
#include "citem.h"
namespace Ui {
class reminder;
}

class reminder : public QDialog
{
    Q_OBJECT

public:
    explicit reminder(QWidget *parent, CItem& _i);
    ~reminder();
    void work();

private slots:
    void on_CloseButton_clicked();

    void on_DelayButton_clicked();

    void on_timeout();

private:
    Ui::reminder *ui;
    CItem& item;
    QPoint point;
    int now_y;
    QTimer* timer;
};

#endif // REMINDER_H
