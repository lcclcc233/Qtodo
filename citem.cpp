#include "citem.h"

CItem::CItem()
{

}
CItem::CItem(QString _s, QDateTime _d, bool _i){
    name=_s;
    ddl=_d;
    is_finish=_i;
}
