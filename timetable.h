#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QDialog>

namespace Ui {
class timetable;
}

class timetable : public QDialog
{
    Q_OBJECT

public:
    explicit timetable(QWidget *parent = nullptr);
    ~timetable();
    void gettext(int r,int c,QString& text,int& R,int& G,int& B);
    void additem(int r,int c,QString text,int R,int G,int B);
    void clear();
private slots:
    void on_addButton_clicked();

    void on_delButton_clicked();

    void on_itemButton_clicked();

private:
    Ui::timetable *ui;
    QWidget *pa;
};

#endif // TIMETABLE_H
