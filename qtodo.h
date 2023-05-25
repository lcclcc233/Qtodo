#ifndef QTODO_H
#define QTODO_H

#include <QMainWindow>
#include <QListWidget>
#include <QSystemTrayIcon>
QT_BEGIN_NAMESPACE
namespace Ui { class Qtodo; }
QT_END_NAMESPACE

class Qtodo : public QMainWindow
{
    Q_OBJECT

public:
    Qtodo(QWidget *parent = nullptr);
    ~Qtodo();

private slots:

    void on_additemButton_clicked();

    void anyStateChanged();

    void on_checkitem();

    void on_hideButton_clicked();

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
private:
    Ui::Qtodo *ui;
    QTimer *timer;
    QSystemTrayIcon* pTrayIcon;
};
#endif // QTODO_H
