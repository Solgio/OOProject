######################################################################
# Automatically generated by qmake (3.1) Thu Mar 27 13:36:13 2025
######################################################################

TEMPLATE = app
TARGET = OOProject
INCLUDEPATH += .
QT+= widgets core xml

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x060000 # disables all APIs deprecated in Qt 6.0.0 and earlier

# Input
HEADERS += src/data_persistency/IReader.h \
           src/View/Visitor.h \
           src/View/LibraryWIndow.h \
           src/View/PreviewWidget.h \
           src/data_persistency/json/visitorJson.h \
           src/data_persistency/json/jsonReader.h \
           src/data_persistency/xml/xmlReader.h \
           src/data_persistency/xml/xmlVisitor.h \
           src/Model/lib/Book.h \
           src/Model/lib/Comic.h \
           src/Model/lib/Content.h \
           src/Model/lib/Film.h \
           src/Model/lib/lib.h \
           src/Model/lib/Multimedia.h \
           src/Model/lib/Paper.h \
           src/Model/lib/ScienceFictionLibrary.h \
           src/Model/lib/Serie.h \
           src/Model/lib/Video.h \
           src/Model/lib/VideoGame.h
SOURCES += src/Model/Book.cpp \
           src/Model/Comic.cpp \
           src/Model/Content.cpp \
           src/Model/Film.cpp \
           src/Model/main.cpp \
           src/Model/Multimedia.cpp \
           src/Model/Paper.cpp \
           src/Model/ScienceFictionLibrary.cpp \
           src/Model/Serie.cpp \
           src/Model/Video.cpp \
           src/Model/VideoGame.cpp \
           src/View/Visitor.cpp \
           src/View/LibraryWindow.cpp \
           src/View/PreviewWidget.cpp \
           src/data_persistency/json/visitorJson.cpp \
           src/data_persistency/json/jsonReader.cpp \
           src/data_persistency/xml/xmlReader.cpp \
           src/data_persistency/xml/xmlVisitor.cpp

RESOURCES += \
    resources.qrc
