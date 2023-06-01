#ifndef QTODO_H
#define QTODO_H

#include <QMainWindow>
#include <QListWidget>
#include <QSystemTrayIcon>
#include <QTreeWidget>
#include "citem.h"
#include "timetable.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Qtodo; }
QT_END_NAMESPACE

class Qtodo : public QMainWindow
{
    Q_OBJECT

public:
    Qtodo(QWidget *parent = nullptr);
    ~Qtodo();
    CItem items[100];
    int childid[100][100];
    int itemcnt = 0;
    void additem(QTreeWidgetItem* pitem, QTreeWidgetItem* fa, const CItem& input) ;
    int find_id(QTreeWidgetItem *item);
private slots:

    void on_additemButton_clicked();

    void anyStateChanged();

    void on_checkitem();

    void on_hideButton_clicked();

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void handlecheck(QTreeWidgetItem* fa, int fid, bool paint=false) ;

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_out_pushButton_clicked();

    void on_open_pushButton_clicked();

private:
    Ui::Qtodo *ui;
    QTimer *timer;
    QSystemTrayIcon* pTrayIcon;
    timetable* ptable;
};
#endif // QTODO_H
