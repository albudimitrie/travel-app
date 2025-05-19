QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Socket.cpp \
    accommodation.cpp \
    accommodationrequest.cpp \
    ack.cpp \
    allattractionsrequest.cpp \
    allroutesrequest.cpp \
    attraction.cpp \
    clientwindow.cpp \
    destination.cpp \
    factoryrequest.cpp \
    historyrequest.cpp \
    irequest.cpp \
    loginrequest.cpp \
    logoutrequest.cpp \
    main.cpp \
    mainwindow.cpp \
    numberaccommodationsrequest.cpp \
    photoaccommodationrequest.cpp \
    photoattractionrequest.cpp \
    phototransportationrequest.cpp \
    registerrequest.cpp \
    registerwindow.cpp \
    transportation.cpp \
    transportationroute.cpp \
    trip.cpp \
    tripsrequest.cpp

HEADERS += \
    Socket.h \
    accommodation.h \
    accommodationrequest.h \
    ack.h \
    allattractionsrequest.h \
    allroutesrequest.h \
    attraction.h \
    clientwindow.h \
    destination.h \
    factoryrequest.h \
    historyrequest.h \
    irequest.h \
    loginrequest.h \
    logoutrequest.h \
    mainwindow.h \
    numberaccommodationsrequest.h \
    photoaccommodationrequest.h \
    photoattractionrequest.h \
    phototransportationrequest.h \
    registerrequest.h \
    registerwindow.h \
    transportation.h \
    transportationroute.h \
    trip.h \
    tripsrequest.h

FORMS += \
    clientwindow.ui \
    mainwindow.ui \
    registerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

LIBS += -lWs2_32 -lMswsock -lAdvApi32

