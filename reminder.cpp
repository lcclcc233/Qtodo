#include "reminder.h"
#include "ui_reminder.h"
#include "citem.h"
#include <QScreen>
reminder::reminder(QWidget *parent, CItem& _i) :
    QDialog(parent),
    ui(new Ui::reminder),
    item(_i)
{
    ui->setupUi(this);
    setWindowModality(Qt::NonModal);
    QString out;
    if(!item.is_whole_day)
        out =item.name+" due on "+item.ddl.toString("yyyy-MM-dd hh:mm:ss")+" is coming";
    else
        out =item.name+" due on "+item.ddl.toString("yyyy-MM-dd")+" is coming";
    ui->textBrowser->setText(out);
    timer = new QTimer;
}

reminder::~reminder()
{
    delete ui;
    timer->stop();
}

void reminder::on_CloseButton_clicked()
{
    this->close();
}


void reminder::on_DelayButton_clicked()
{
    item.reminder_time=item.reminder_time.addSecs(300);
    this->close();
}

void reminder::work(){
    this->show();
    QRect desk_rect=QGuiApplication::primaryScreen()->availableGeometry();
    point.setX(desk_rect.width()-rect().width());
    point.setY(desk_rect.height()-rect().height());
    now_y=desk_rect.height();
    move(point.x(),now_y);
    timer->start(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
}

void reminder::on_timeout(){
    now_y--;
    move(point.x(),now_y);
    if(now_y==point.y())
        timer->stop();
}
