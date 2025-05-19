#include <QApplication>
#include <QStyleFactory>
#include "../View/LibraryWindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    // Personalizza la palette (opzionale ma consigliato)
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(46, 45, 45));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Button, QColor(46, 45, 45));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::Base, Qt::black);
    palette.setColor(QPalette::Text, Qt::white);
    a.setPalette(palette);
    
    LibraryWindow window;
    window.show();
    
    return a.exec();
}