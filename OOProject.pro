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
           src/View/EditWindows/BookEditWindow.h \
           src/View/EditWindows/ComicEditWindow.h \
           src/View/EditWindows/CommonEditWindow.h \
           src/View/EditWindows/FilmEditWindow.h \
           src/View/EditWindows/MultimediaEditWindow.h \
           src/View/EditWindows/VideoEditWindow.h \
           src/View/EditWindows/VideoGameEditWindow.h \
           src/View/Visitor.h \
           src/View/LibraryWindow.h \
           src/View/PreviewWidget.h \
           src/View/ContentDetailWindow.h \
           src/View/ContentEditWindow.h \
           src/View/TypeChoiceDialog.h \
           src/View/ContentModel.h \
           src/View/ContentProxyModel.h \
           src/View/DisplayWindows/AttributeDisplayWindow.h \
           src/View/DisplayWindows/BookDisplayWindow.h \
           src/View/DisplayWindows/ComicDisplayWindow.h \
           src/View/DisplayWindows/FilmDisplayWindow.h \
           src/View/EditWindows/MultimediaEditWindow.h \
           src/View/EditWindows/SerieEditWindow.h \
           src/View/DisplayWindows/MultimediaDisplayWindow.h \
           src/View/DisplayWindows/SerieDisplayWindow.h \
           src/View/DisplayWindows/VideoDisplayWindow.h \
           src/View/DisplayWindows/VideogameDisplayWindow.h \
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
           src/Model/lib/VideoGame.h \
           src/View/LibraryActionsManager.h \
           src/View/LibraryToolbar.h \
           src/View/ContentPreviewGrid.h \
           src/View/ContentCardWidget.h \
           src/View/ShortcutManager.h \
           src/View/SortingSectionWidget.h \
           src/View/FilterSectionWidget.h 
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
           src/View/EditWindows/BookEditWindow.cpp \
           src/View/EditWindows/ComicEditWindow.cpp \
           src/View/EditWindows/CommonEditWindow.cpp \
           src/View/EditWindows/FilmEditWindow.cpp \
           src/View/EditWindows/MultimediaEditWindow.cpp \
           src/View/EditWindows/SerieEditWindow.cpp \
           src/View/EditWindows/VideoEditWindow.cpp \
           src/View/EditWindows/VideoGameEditWindow.cpp \
           src/View/Visitor.cpp \
           src/View/LibraryWindow.cpp \
           src/View/PreviewWidget.cpp \
           src/View/ContentDetailWindow.cpp \
           src/View/ContentEditWindow.cpp \
           src/View/TypeChoiceDialog.cpp \
           src/View/ContentModel.cpp \
           src/View/ContentProxyModel.cpp \
           src/View/DisplayWindows/AttributeDisplayWindow.cpp \
           src/View/DisplayWindows/BookDisplayWindow.cpp \
           src/View/DisplayWindows/ComicDisplayWindow.cpp \
           src/View/DisplayWindows/FilmDisplayWindow.cpp \
           src/View/DisplayWindows/MultimediaDisplayWindow.cpp \
           src/View/DisplayWindows/SerieDisplayWindow.cpp \
           src/View/DisplayWindows/VideoDisplayWindow.cpp \
           src/View/DisplayWindows/VideogameDisplayWindow.cpp \
           src/data_persistency/json/visitorJson.cpp \
           src/data_persistency/json/jsonReader.cpp \
           src/data_persistency/xml/xmlReader.cpp \
           src/data_persistency/xml/xmlVisitor.cpp \
           src/View/LibraryActionsManager.cpp \
           src/View/LibraryToolbar.cpp \
           src/View/ContentPreviewGrid.cpp \
           src/View/ContentCardWidget.cpp \
           src/View/ShortcutManager.cpp \
           src/View/SortingSectionWidget.cpp \
           src/View/FilterSectionWidget.cpp \

RESOURCES += \
    resources.qrc
