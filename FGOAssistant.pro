#-------------------------------------------------
#
# Project created by QtCreator 2018-11-20T16:52:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FGOAssistant
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    res.qrc

#RC_FILE = fgoass.rc

# 配置图标（仅Windows有效）
RC_ICONS += myapp.ico
# 版本号
VERSION = 1.2
# 语言
# 0x0004 表示 简体中文
RC_LANG = 0x0004
# 公司名
#QMAKE_TARGET_COMPANY =
# 产品名称
QMAKE_TARGET_PRODUCT = FGOAssistant
# 详细描述
#QMAKE_TARGET_DESCRIPTION = XXXXXX
# 版权
#QMAKE_TARGET_COPYRIGHT = Copyright(C) 2018 XXXXX
