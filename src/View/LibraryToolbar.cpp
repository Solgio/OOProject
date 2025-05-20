#include "LibraryToolbar.h"

LibraryToolbar::LibraryToolbar(QWidget *parent) : QToolBar(parent) {
    setIconSize(QSize(28, 28));
    setupToolbar();
}

void LibraryToolbar::setupToolbar() {
    createImportButton();
    addWidget(m_importButton);

    createSaveMenu();
    addWidget(m_saveButton);

    createAddButton();
    addWidget(m_addContentButton);
}

void LibraryToolbar::createImportButton() {
    m_importButton = new QToolButton();
    m_importButton->setText("Import");
    m_importButton->setIcon(QIcon(":assets/icons/import.png"));
    m_importButton->setToolTip("Import content from file");
    connect(m_importButton, &QToolButton::clicked, this, &LibraryToolbar::importRequested);
}

void LibraryToolbar::createSaveMenu() {
    m_saveMenu = new QMenu(this);
    m_saveMenu->setStyleSheet("QMenu::item { padding: 5px 10px; }");

    auto *saveJson = new QAction(QIcon(":assets/icons/w_json.png"), "Save as JSON", this);
    saveJson->setIconText("Save as JSON");
    saveJson->setToolTip("Export library as JSON file");
    connect(saveJson, &QAction::triggered, this, [this]() { emit saveRequested("json"); });

    auto *saveXml = new QAction(QIcon(":assets/icons/w_xml.png"), "Save as XML", this);
    saveXml->setIconText("Save as XML");
    saveXml->setToolTip("Export library as XML file");
    connect(saveXml, &QAction::triggered, this, [this]() { emit saveRequested("xml"); });

    m_saveMenu->addAction(saveJson);
    m_saveMenu->addAction(saveXml);

    m_saveButton = new QToolButton();
    m_saveButton->setText("Save");
    m_saveButton->setIcon(QIcon(":assets/icons/save.png"));
    m_saveButton->setToolTip("Save library to file. Supported formats: JSON, XML");
    m_saveButton->setMenu(m_saveMenu);
    m_saveButton->setPopupMode(QToolButton::InstantPopup);
    m_saveButton->setIconSize(QSize(28, 28));
}

void LibraryToolbar::createAddButton() {
    m_addContentButton = new QToolButton();
    m_addContentButton->setText("Add Content");
    m_addContentButton->setIcon(QIcon(":assets/icons/add.png"));
    m_addContentButton->setToolTip("Add new content to the library");
    m_addContentButton->setIconSize(QSize(32, 32));
    connect(m_addContentButton, &QToolButton::clicked, this, &LibraryToolbar::addContentRequested);
}