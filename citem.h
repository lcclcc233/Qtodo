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
    bool is_finish;
    CItem();
    CItem(QString _s, QDateTime _d, bool _i=false);
};

#endif // CITEM_H
