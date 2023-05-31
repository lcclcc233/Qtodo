QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    citem.cpp \
    dialog.cpp \
    item_display.cpp \
    main.cpp \
    qtodo.cpp \
    reminder.cpp \
    timetable.cpp


HEADERS += \
    citem.h \
    dialog.h \
    item_display.h \
    qtodo.h \
    reminder.h \
    timetable.h


FORMS += \
    dialog.ui \
    item_display.ui \
    qtodo.ui \
    reminder.ui \
    timetable.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
    