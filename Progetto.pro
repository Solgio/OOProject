QT += core widgets

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
        src/Model/lib/CreateJSon.h \
        src/Model/lib/MainWidget.h \
        src/Model/lib/Content.h \
        src/Model/lib/Paper.h \
        src/Model/lib/Multimedia.h \
        src/Model/lib/Video.h \
        src/Model/lib/VideoGame.h \
        src/Model/lib/Series.h \
        src/Model/lib/Film.h \
        src/Model/lib/ScienceFictionLibrary.h \
        src/Model/lib/Book.h \
        src/Model/lib/Comic.h \
        src/Model/lib/Visitor.h \
        src/json/visitorJson.h \
        src/View/Visitor.h \
        src/xml/xmlVisitor.h

SOURCES += \
        src/Model/CreateJSon.cpp \
        src/Model/main.cpp \
        src/Model/MainWidget.cpp \
        src/Model/Content.cpp \
        src/Model/Paper.cpp \
        src/Model/Multimedia.cpp \
        src/Model/Video.cpp \
        src/Model/VideoGame.cpp \
        src/Model/Series.cpp \
        src/Model/Film.cpp \
        src/Model/ScienceFictionLibrary.cpp \
        src/Model/Book.cpp \
        src/Model/Comic.cpp \
        src/Model/Visitor.cpp \
        src/json/visitorJson.cpp \
        src/View/Visitor.cpp \
        src/xml/xmlVisitor.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=
