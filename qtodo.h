#ifndef QTODO_H
#define QTODO_H

#include <QMainWindow>
#include <QListWidget>
#include <QSystemTrayIcon>
#include <QTreeWidget>
#include "citem.h"
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

private:
    Ui::Qtodo *ui;
    QTimer *timer;
    QSystemTrayIcon* pTrayIcon;
};
#endif // QTODO_H
