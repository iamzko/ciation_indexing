QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./src/main.cpp \
    ./src/indexmainwindow.cpp \
    src/mydatabasemodule.cpp \
    src/mydatamodel.cpp \
    src/mydatatable.cpp \
    src/myeditor.cpp \
    src/mygraphicseditor.cpp \
    src/mytaskmodule.cpp \
    src/mytexteditor.cpp

HEADERS += \
    ./src/indexmainwindow.h \
    src/mydatabasemodule.h \
    src/mydatamodel.h \
    src/mydatatable.h \
    src/myeditor.h \
    src/mygraphicseditor.h \
    src/mytaskmodule.h \
    src/mytexteditor.h\
    src/TaskAidWrap.h


FORMS += \
    ./ui/indexmainwindow.ui

TRANSLATIONS += \
    ./translations/citation_indexing_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations
win32{
#QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator'"
}
CONFIG(release,debug|release){
LIBS += -L$$PWD/lib/release/  -lTaskAidWrap
}else{
LIBS += -L$$PWD/lib/debug/  -lTaskAidWrap
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/main_res.qrc
