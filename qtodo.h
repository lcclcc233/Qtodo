#ifndef QTODO_H
#define QTODO_H

#include <QMainWindow>
#include <QListWidget>
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
private:
    Ui::Qtodo *ui;
};
#endif // QTODO_H
