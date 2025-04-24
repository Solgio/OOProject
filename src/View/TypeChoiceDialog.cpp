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

    auto *gridLayout = new QGridLayout();
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(20, 20, 20, 20);

    // Crea un gruppo di pulsanti per la selezione esclusiva
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setExclusive(true);  // Imposta la selezione esclusiva

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

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(gridLayout);
    mainLayout->addStretch();

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
}

void TypeChoiceDialog::addContentType(QGridLayout *layout, const QString &label,
    const QString &iconPath, ContentFactory factory, int row, int col) {
auto *button = new QPushButton(this);
button->setIcon(QIcon(iconPath));

// Dimensioni delle icone
QSize normalSize(80, 80);
QSize selectedSize(90, 90); // Leggermente più grande quando selezionato

button->setIconSize(normalSize);
button->setText(label);
button->setToolTip("Create new " + label);
button->setCheckable(true);

// Aggiungi al gruppo di pulsanti
m_buttonGroup->addButton(button);

// Animazione per il cambio dimensione
auto *sizeAnimation = new QPropertyAnimation(button, "iconSize", this);
sizeAnimation->setDuration(150);
sizeAnimation->setEasingCurve(QEasingCurve::OutCubic);

connect(button, &QPushButton::toggled, [sizeAnimation, normalSize, selectedSize](bool checked) {
sizeAnimation->stop();
sizeAnimation->setStartValue(sizeAnimation->targetObject()->property("iconSize").toSize());
sizeAnimation->setEndValue(checked ? selectedSize : normalSize);
sizeAnimation->start();
});

// Stile CSS con solo contorno verde per la selezione
button->setStyleSheet(
"QPushButton {"
"   padding: 15px;"
"   border: 2px solid transparent;"
"   border-radius: 8px;"
"   spacing: 5px;"
"   background: none;" // Rimuove qualsiasi sfondo
"}"
"QPushButton:hover {"
"   border-color: #3498db;" // Blu al passaggio del mouse
"}"
"QPushButton:checked {"
"   border-color: #2ecc71;" // Verde brillante quando selezionato
"   border-width: 3px;"     // Contorno più spesso
"}"
"QPushButton:pressed {"
"   border-color: #27ae60;" // Verde più scuro quando cliccato
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