#include "VideoGameEditWindow.h"


VideoGameEditWindow::VideoGameEditWindow():
    MultimediaEditWindow(),
    gameEngEdit(new QTextEdit()),
    ExpHoursEdit(new MySpinBox()),
    gameTypeEdit(new MyComboBox())
{
    ExpHoursEdit->setMaximum(9999);
    setUp();
}

VideoGameEditWindow::VideoGameEditWindow(Content *content):
    MultimediaEditWindow(content),
    gameEngEdit(new QTextEdit()),
    ExpHoursEdit(new MySpinBox()),
    gameTypeEdit(new MyComboBox())
{
    ExpHoursEdit->setMaximum(9999);
    setUpGameEditBox();
    setUp();
}

VideoGameEditWindow::VideoGameEditWindow(VideoGame *videogame):
    MultimediaEditWindow(videogame),
    gameEngEdit(new QTextEdit(QString::fromStdString(videogame->getGameEngine()))),
    ExpHoursEdit(new MySpinBox()),
    gameTypeEdit(new MyComboBox()),
    vgPtr(videogame)
{
    ExpHoursEdit->setMaximum(9999);
    setUpGameEditBox();
    gameTypeEdit->setCurrentText(QString::fromStdString(videogame->getGameType()));

    ExpHoursEdit->setValue(videogame->getExpectedHours());
    setUp();
}

void VideoGameEditWindow::setUpGameEditBox(){
    const QStringList gameGenres = {
        "FPS", "RPG", "ARPG", "RTS", "MOBA", "MMORPG", "SIMULATION", "SPORTS", "PUZZLE", "PLATFORMER", "RACING", "FIGHTING", "SURVIVAL", "ADVENTURE", "ACTION", "STRATEGY",
        "SANDBOX", "TOWERDEFENSE", "CARDGAME", "PARTYGAME", "CASUAL", "ARCADE", "VIRTUALREALITY"
    };
    gameTypeEdit->addItems(gameGenres);
    gameTypeEdit->setEditable(false);
    gameTypeEdit->setInsertPolicy(QComboBox::NoInsert);
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
}

void VideoGameEditWindow::saveEdit(){
    MultimediaEditWindow::saveEdit();
    if(vgPtr){
        vgPtr->setGameEngine(gameEngEdit->toPlainText().QString::toStdString());
        vgPtr->setExpectedHours(ExpHoursEdit->value());
        vgPtr->setGameType(vgPtr->stringToGametype(gameTypeEdit->currentText().QString::toStdString()));
    }
}
