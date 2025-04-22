#include "TypeChoiceDialog.h"
#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Serie.h"
#include "../Model/lib/VideoGame.h"
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>

TypeChoiceDialog::TypeChoiceDialog(QWidget *parent)
    : QDialog(parent), m_selectedFactory(nullptr) {
    setWindowTitle("Select Content Type");
    setFixedSize(500, 400);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(20, 20, 20, 20);

    // Aggiungi i tipi di contenuto disponibili
    addContentType(gridLayout, "Book", ":/assets/icons/book.png", 
                  []() { return new Book(); }, 0, 0);
    addContentType(gridLayout, "Comic", ":/assets/icons/comic.png", 
                  []() { return new Comic(); }, 0, 1);
    addContentType(gridLayout, "Film", ":/assets/icons/film.png", 
                  []() { return new Film(); }, 1, 0);
    addContentType(gridLayout, "TV Series", ":/assets/icons/serie.png", 
                  []() { return new Serie(); }, 1, 1);
    addContentType(gridLayout, "Video Game", ":/assets/icons/videogame.png", 
                  []() { return new VideoGame(); }, 2, 0);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(gridLayout);
    mainLayout->addStretch();

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
}

void TypeChoiceDialog::addContentType(QGridLayout *layout, const QString &label,
                                     const QString &iconPath, ContentFactory factory, int row, int col) {
    QPushButton *button = new QPushButton(this);
    button->setIcon(QIcon(iconPath));
    button->setIconSize(QSize(80, 80));
    button->setText(label);
    button->setToolTip("Create new " + label);
    button->setCheckable(true);
    button->setStyleSheet(
        "QPushButton {"
        "   padding: 15px;"
        "   border: 2px solid transparent;"
        "   border-radius: 8px;"
        "}"
        "QPushButton:hover {"
        "   border-color: #3498db;"
        "   background-color: #eaf2f8;"
        "}"
        "QPushButton:checked {"
        "   border-color: #2980b9;"
        "   background-color: #d4e6f1;"
        "}"
    );

    connect(button, &QPushButton::clicked, [this, factory]() {
        m_selectedFactory = factory;
    });

    layout->addWidget(button, row, col, Qt::AlignCenter);
}

Content* TypeChoiceDialog::createSelectedContent() const {
    return m_selectedFactory ? m_selectedFactory() : nullptr;
}