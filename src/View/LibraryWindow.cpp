#include "LibraryWindow.h"
#include "ContentDetailWindow.h"
#include "TypeChoiceDialog.h"
#include "ContentEditWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>
#include <QSplitter>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMenu>
#include <QDebug>
#include <QDir>

LibraryWindow::LibraryWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
    connectSignals();
    updateContentDisplay();
}

LibraryWindow::~LibraryWindow() {
    // Pulizia delle risorse
    delete m_detailWindow;
}

void LibraryWindow::createSaveMenu() {
    m_saveMenu = new QMenu("Save Options", this);
    
    auto *saveXmlAction = m_saveMenu->addAction(QIcon(":assets/icons/w_xml.png"), "Save as XML");
    saveXmlAction->setToolTip("Export library as XML file");
    connect(saveXmlAction, &QAction::triggered, [this]() { saveToFile("xml"); });
    
    auto *saveJsonAction = m_saveMenu->addAction(QIcon(":assets/icons/w_json.png"), "Save as JSON");
    saveJsonAction->setToolTip("Export library as JSON file");
    connect(saveJsonAction, &QAction::triggered, [this]() { saveToFile("json"); });
    
    m_saveButton = new QToolButton();
    m_saveButton->setText(" Save ");
    m_saveButton->setIcon(QIcon(":assets/icons/save.png"));
    m_saveButton->setToolTip("Save library to file");
    m_saveButton->setPopupMode(QToolButton::MenuButtonPopup);
    m_saveButton->setMenu(m_saveMenu);
}

void LibraryWindow::createImportButton() {
    m_importButton = new QToolButton();
    m_importButton->setText(" Import ");
    m_importButton->setIcon(QIcon(":assets/icons/import.png"));
    m_importButton->setToolTip("Import content from file. Supported formats: XML, JSON");
    connect(m_importButton, &QToolButton::clicked, this, &LibraryWindow::importContent);
}
void LibraryWindow::editContentTriggered(bool checked) {
    Q_UNUSED(checked);
    
    TypeChoiceDialog typeDialog(this);
    if (typeDialog.exec() == QDialog::Accepted) {
        Content* newContent = typeDialog.createSelectedContent();
        if (newContent) {
            // Assegna un ID e aggiungi alla libreria
            newContent->setId(ScienceFiction_Library::getInstance().getNewId());
            ScienceFiction_Library::getInstance().addContent(newContent);
            editContent(newContent);
        }
    }
}

void LibraryWindow::setupUI() {
    setWindowTitle("Science Fiction Library Manager");
    resize(1024, 768);

    // Inizializzazione componenti UI
    m_toolBar = addToolBar("Main Toolbar");
    m_contentList = new QListWidget();
    m_rightPanel = new QWidget();  // Inizializzazione aggiunta
    m_splitter = new QSplitter(Qt::Horizontal);

    // Configurazione toolbar
    createImportButton();
    m_toolBar->addWidget(m_importButton);
    createSaveMenu();
    m_toolBar->addWidget(m_saveButton);

    // Pulsante di debug
    auto* testBtn = new QPushButton("Test Connection");
    connect(testBtn, &QPushButton::clicked, this, &LibraryWindow::verifyResources);
    m_toolBar->addWidget(testBtn);

    // Configurazione lista contenuti
    m_contentList->setViewMode(QListWidget::IconMode);
    m_contentList->setIconSize(m_previewSize);
    m_contentList->setResizeMode(QListWidget::Adjust);
    m_contentList->setMovement(QListWidget::Static);

    // Pannello sinistro (filtri)
    m_searchBar = new QLineEdit();
    m_searchBar->setPlaceholderText("Search content...");
    m_filterCombo = new QComboBox();
    m_filterCombo->addItems({"All", "Action", "War", "Watched", "Starred"});

    auto *leftPanel = new QWidget();
    auto *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->addWidget(m_searchBar);
    leftLayout->addWidget(m_filterCombo);
    leftLayout->addStretch();

    // Pannello destro (contenuti e pulsante)
    auto *rightLayout = new QVBoxLayout(m_rightPanel);
    rightLayout->addWidget(new QLabel("Content Preview:"));
    rightLayout->addWidget(m_contentList);

    // Pulsante Add in basso a destra
    auto *buttonContainer = new QWidget();
    auto *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(0, 0, 10, 10);
    buttonLayout->addStretch();
    
    m_add = new QToolButton();
    m_add->setText("Add Content");
    m_add->setIcon(QIcon(":assets/icons/add.png"));
    m_add->setToolTip("Add new content to the library");
    m_add->setIconSize(QSize(32, 32));
    connect(m_add, &QToolButton::clicked, this, &LibraryWindow::editContentTriggered);
    
    buttonLayout->addWidget(m_add);
    rightLayout->addWidget(buttonContainer);

    // Finestra dei dettagli
    m_detailWindow = new ContentDetailWindow();
    m_detailWindow->hide();
    rightLayout->addWidget(m_detailWindow);

    // Configurazione splitter
    m_splitter->addWidget(leftPanel);
    m_splitter->addWidget(m_rightPanel);
    m_splitter->setStretchFactor(0, 1);
    m_splitter->setStretchFactor(1, 3);

    setCentralWidget(m_splitter);
}

void LibraryWindow::connectSignals() const {
    connect(m_contentList, &QListWidget::itemClicked, 
            this, &LibraryWindow::showContentDetails);
    connect(m_detailWindow, &ContentDetailWindow::editRequested,
            this, &LibraryWindow::editContent);
    connect(m_detailWindow, &ContentDetailWindow::closeRequested,
            this, &LibraryWindow::hideDetailView);
    connect(m_filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &LibraryWindow::onFilterChanged);
}

void LibraryWindow::onFilterChanged(int index) {
    auto& library = ScienceFiction_Library::getInstance();
    
    // Clear any existing filters
    library.clearShown();
    
    // Apply the selected filter
    switch (index) {
        case 0: // "All"
            library.showAllContent();
            break;
        case 1: // "Movies"
            library.filteredListbyGen(static_cast<unsigned int>(Subgenre::ACTION));
            break;
        case 2: // "Books"
            library.filteredListbyGen(static_cast<unsigned int>(Subgenre::WAR));
            break;
        case 3: // "Watched"
            library.watchedOrNot(true);
            break;
        case 4: // "Starred"
            library.starredOrNot(true);
            break;
        default:
            break;
    }
    
    // Update the display
    updateContentDisplay();
}

void LibraryWindow::showContentDetails(QListWidgetItem *item) {
    if (!item) return;

    bool ok;
    unsigned int id = item->data(Qt::UserRole).toUInt(&ok);
    if (!ok) return;

    Content* content = ScienceFiction_Library::getInstance().searchId(id);
    if (!content) return;

    m_detailWindow->setContent(content);
    m_contentList->hide();
    m_add->hide();
    m_detailWindow->show();
}

QPixmap LibraryWindow::loadSafePixmap(const QString &path, const QSize &size) const {
    QPixmap pixmap;
    if (!path.isEmpty() && QFile::exists(path)) {
        pixmap.load(path);
    }
    
    if (pixmap.isNull()) {
        pixmap.load("assets/icons/default.png");
    }
    
    return pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void LibraryWindow::loadContentPreview(Content* content, QListWidgetItem* item) const{
    if (!content) return;

    item->setText(QString::fromStdString(content->getTitle()));
    item->setData(Qt::UserRole, QVariant(content->getId()));
    
    QPixmap pixmap = loadSafePixmap(
        QString::fromStdString(content->getImage()),
        m_previewSize
    );
    item->setIcon(QIcon(pixmap));
}
void LibraryWindow::updateContentDisplay() {
    qDebug() << "Updating content display...";
    m_contentList->clear();

    auto& library = ScienceFiction_Library::getInstance();
    
    // Handle filtered content (shownContentList)
    if (!library.getShownContentList().empty()) {
        for (Content* content : library.getShownContentList()) {
            if (!content) continue;
            auto* item = new QListWidgetItem(m_contentList);
            loadContentPreview(content, item);
        }
    } 
    // Handle full content (contentList)
    else {
        for (const auto& contentPtr : library.getContentList()) {
            auto* item = new QListWidgetItem(m_contentList);
            loadContentPreview(contentPtr.get(), item);
        }
    }
}

void LibraryWindow::hideDetailView() {
    m_detailWindow->hide();
    m_contentList->show();
    m_add->show();
}

void LibraryWindow::editContent(Content* content) 
{
    if (!content) {
        
        qCritical() << "Attempted to edit null content!";
        return;
    }

    auto *editWindow = new ContentEditWindow(content, this);
    editWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(editWindow, &ContentEditWindow::contentUpdated, 
            this, &LibraryWindow::updateContentDisplay);
    editWindow->exec();
}

void LibraryWindow::importContent() {
    QString file = QFileDialog::getOpenFileName(
        this, 
        "Import Content", 
        QDir::homePath(), 
        "Supported Files (*.xml *.json)"
    );
    
    if (!file.isEmpty()) {
        bool success = ScienceFiction_Library::getInstance().loadFromFile(file.toStdString());
        if (success) {
            updateContentDisplay();
            QMessageBox::information(this, "Success", "Content imported successfully");
        } else {
            QMessageBox::warning(this, "Error", "Failed to import content");
        }
    }
}

void LibraryWindow::saveToFile(const QString &extension) {
    QString file = QFileDialog::getSaveFileName(
        this,
        QString("Save As %1").arg(extension.toUpper()),
        QDir::homePath(),
        QString("%1 Files (*.%1)").arg(extension)
    );
    
    if (!file.isEmpty()) {
        bool success = ScienceFiction_Library::getInstance().saveToFile(file.toStdString());
        if (success) {
            QMessageBox::information(this, "Success", "Library saved successfully");
        } else {
            QMessageBox::warning(this, "Error", "Failed to save library");
        }
    }
}

void LibraryWindow::verifyResources() const{
    qDebug() << "Working directory:" << QDir::currentPath();
    
    // Verifica immagini di default
    qDebug() << "Default icon exists:" << QFile::exists("/home/solgio/Desktop/OOProject/assets/icons/default.png");
    
    // Verifica percorsi dei contenuti
    auto& library = ScienceFiction_Library::getInstance();
    for (const auto& content : library.getContentList()) {
        QString path = QString::fromStdString(content->getImage());
        qDebug() << "Content" << content->getId() 
                 << "| Title:" << QString::fromStdString(content->getTitle())
                 << "| Path:" << path 
                 << "| Exists Image:" << QFile::exists(path);
    }
}