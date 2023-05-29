#include "citem.h"

CItem::CItem()
{

}
CItem::CItem(QString _s, QDateTime _d, QDateTime _r, bool _iw, bool _if){
    name=_s;
    ddl=_d;
    reminder_time=_r;
    is_whole_day=_iw;
    is_finish=_if;
}
