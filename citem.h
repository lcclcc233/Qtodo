#ifndef CITEM_H
#define CITEM_H
#include <string>
#include <QDateTimeEdit>
class CItem
{
private:

public:
    QString name;//成员变量应该放private更好，暂时放外面方便写
    QDateTime ddl;
    QDateTime reminder_time;
    bool is_finish;
    bool is_whole_day;
    bool is_vital;
    QString category;
    bool is_weekly;
    CItem();
    CItem(QString _s, QDateTime _d, QDateTime _r, bool _iw=false, bool _if=false, bool _iv=false,QString _c="无",bool _ik=false);
};

#endif // CITEM_H
