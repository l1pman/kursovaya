QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_product.cpp \
    add_user.cpp \
    admin_window.cpp \
    auth_window.cpp \
    main.cpp \
    mainwindow.cpp \
    password_change.cpp \
    personal_cab.cpp \
    product.cpp \
    product_window.cpp \
    products.cpp \
    user.cpp \
    users.cpp

HEADERS += \
    add_product.h \
    add_user.h \
    admin_window.h \
    auth_window.h \
    mainwindow.h \
    password_change.h \
    personal_cab.h \
    product.h \
    product_window.h \
    products.h \
    user.h \
    users.h

FORMS += \
    add_product.ui \
    add_user.ui \
    admin_window.ui \
    auth_window.ui \
    mainwindow.ui \
    password_change.ui \
    personal_cab.ui \
    product_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CurrentUser.bin \
    ProductStream.bin \
    UserStream.bin
