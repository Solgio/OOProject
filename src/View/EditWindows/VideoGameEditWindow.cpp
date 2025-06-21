#include "VideoGameEditWindow.h"

VideoGameEditWindow::VideoGameEditWindow():
    MultimediaEditWindow(),
    gameEngEdit(new QTextEdit()),
    ExpHoursEdit(new MySpinBox()),
    gameTypeEdit(new QTextEdit())
{
    setUp();
}

VideoGameEditWindow::VideoGameEditWindow(Content *content):
    MultimediaEditWindow(content),
    gameEngEdit(new QTextEdit()),
    ExpHoursEdit(new MySpinBox()),
    gameTypeEdit(new QTextEdit())
{
    setUp();
}

VideoGameEditWindow::VideoGameEditWindow(VideoGame *videogame):
    MultimediaEditWindow(videogame),
    gameEngEdit(new QTextEdit(QString::fromStdString(videogame->getGameEngine()))),
    ExpHoursEdit(new MySpinBox()),
    gameTypeEdit(new QTextEdit(QString::fromStdString(videogame->getGameType()))),
    vgPtr(videogame)
{
    ExpHoursEdit->setValue(videogame->getExpectedHours());
    setUp();
}

void VideoGameEditWindow::setUp(){
    QVBoxLayout *mainLayout = CommonEditWindow::getLayout();

    //Game Engine
    auto *gameEngLayout = new QFormLayout();
    gameEngLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Game Engine : ")), gameEngEdit);
    mainLayout->addLayout(gameEngLayout);

    //Expected Hours
    auto *ExpHoursLayout = new QFormLayout();
    ExpHoursLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Expected Hours : ")), ExpHoursEdit);
    mainLayout->addLayout(ExpHoursLayout);

    //Game Genre
    auto *gameTypeLayout = new QFormLayout();
    gameTypeLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Game Genre : ")), gameTypeEdit);
    mainLayout->addLayout(gameTypeLayout);

    CommonEditWindow::getTypeEditBox()->setCurrentText("VideoGame");
}

void VideoGameEditWindow::saveEdit(){
    if(vgPtr){
        MultimediaEditWindow::saveEdit();
        vgPtr->setGameEngine(gameEngEdit->toPlainText().QString::toStdString());
        vgPtr->setExpectedHours(ExpHoursEdit->value());
        vgPtr->stringToGametype(gameTypeEdit->toPlainText().QString::toStdString());
    }
}
