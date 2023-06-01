#ifndef ITEM_DISPLAY_H
#define ITEM_DISPLAY_H

#include <QDialog>
#include "citem.h"
#include "qtodo.h"
#include <QTreeWidgetItem>
namespace Ui {
class item_display;
}

class item_display : public QDialog
{
    Q_OBJECT

public:
    explicit item_display(QWidget *parent, CItem &i, QTreeWidgetItem* p, bool is_son = false);
    ~item_display();

private slots:
    void on_buttonBox_accepted();

    void on_checkBox_stateChanged(int arg1);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_addsubButton_clicked();

private:
    Ui::item_display *ui;
    Qtodo* qtodo;
    CItem &item;
    QTreeWidgetItem* pitem;
};

#endif // ITEM_DISPLAY_H
