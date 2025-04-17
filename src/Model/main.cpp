#include <QApplication>
#include "../View/LibraryWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    LibraryWindow window;
    window.show();
    
    return a.exec();
}