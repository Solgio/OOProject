#include "EditWindow.h"
#include "../../Model/lib/Content.h"

#include <QFileDialog>
#include <QMessageBox>

//include di tutti i concreti EditWindows
#include "EditVisitor.h"
#include "CommonEditWindow.h"
#include "BookEditWindow.h"
#include "ComicEditWindow.h"
#include "FilmEditWindow.h"
#include "SerieEditWindow.h"
#include "VideoGameEditWindow.h"


EditWindow::EditWindow(Content *content, QWidget *parent): QWidget(parent)
{
    format();
}

void EditWindow::format(){
    auto *mainLayout = new QVBoxLayout(this);
    auto *buttonLayout = new QHBoxLayout();
    saveButton = new QPushButton("Save Changes");
    //connect(saveButton, &QPushButton::clicked, this, &EditWindow::saveChanges);

    discardButton = new QPushButton("Cancel");
    //connect(discardButton, &QPushButton::clicked, this, &QDialog::reject);

    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(discardButton);
    mainLayout->addLayout(buttonLayout);
}
