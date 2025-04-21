#include "LibraryWindow.h"
#include "ContentDetailWindow.h"
#include "PreviewWidget.h"
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

void LibraryWindow::createSaveMenu() {
    m_saveMenu = new QMenu("Save Options", this);
    
    QAction *saveXmlAction = m_saveMenu->addAction(QIcon(":assets/icons/w_xml.png"), "Save as XML");
    saveXmlAction->setToolTip("Export library as XML file");
    connect(saveXmlAction, &QAction::triggered, [this]() { saveToFile("xml"); });
    
    QAction *saveJsonAction = m_saveMenu->addAction(QIcon(":assets/icons/w_json.png"), "Save as JSON");
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

void LibraryWindow::setupUI() {
    // Configurazione finestra principale
    setWindowTitle("Science Fiction Library Manager");
    resize(1024, 768);

    // Barra strumenti
    m_toolBar = addToolBar("Main Toolbar");

    createImportButton();
    m_toolBar->addWidget(m_importButton);
    createSaveMenu();
    m_toolBar->addWidget(m_saveButton);

    // DEBUG: Aggiungi un pulsante di test
    QPushButton* testBtn = new QPushButton("Test Connection");
    connect(testBtn, &QPushButton::clicked, this, &LibraryWindow::verifyResources);
    m_toolBar->addWidget(testBtn);

    m_contentList = new QListWidget();
    m_contentList->setViewMode(QListWidget::IconMode);
    m_contentList->setIconSize(m_previewSize);
    m_contentList->setResizeMode(QListWidget::Adjust);
    m_contentList->setMovement(QListWidget::Static);

    // Filtri e ricerca (pannello sinistro)
    m_searchBar = new QLineEdit();
    m_searchBar->setPlaceholderText("Search content...");
    m_filterCombo = new QComboBox();
    m_filterCombo->addItems({"All", "Movies", "Books", "Watched", "Starred"});


    // Pannello sinistro (solo filtri)
    QWidget *leftPanel = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->addWidget(m_searchBar);
    leftLayout->addWidget(m_filterCombo);
    leftLayout->addStretch(); // Spazio vuoto sotto i filtri
    

    // Lista dei contenuti (pannello destro)
    m_rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(m_rightPanel);
    rightLayout->addWidget(new QLabel("Content Preview:"));
    rightLayout->addWidget(m_contentList);

    // Create overlay container
    m_detailWindow = new ContentDetailWindow();
    m_detailWindow->hide();
    rightLayout->addWidget(m_detailWindow);

    // Configurazione splitter
    m_splitter = new QSplitter(Qt::Horizontal);
    m_splitter->addWidget(leftPanel);
    m_splitter->addWidget(m_rightPanel);
    m_splitter->setStretchFactor(0, 1);
    m_splitter->setStretchFactor(1, 3);

    setCentralWidget(m_splitter);
}

void LibraryWindow::connectSignals() {
    connect(m_contentList, &QListWidget::itemClicked, 
            this, &LibraryWindow::showContentDetails);
    connect(m_detailWindow, &ContentDetailWindow::editRequested,
            this, &LibraryWindow::editContent);
    connect(m_detailWindow, &ContentDetailWindow::closeRequested,
            this, &LibraryWindow::hideDetailView);
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

void LibraryWindow::loadContentPreview(Content* content, QListWidgetItem* item) {
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
    const auto& contents = library.getContentList();
    
    qDebug() << "Library contains" << contents.size() << "items";
    
    for (const auto& content : contents) {
        qDebug() << "Processing item:" << content->getId() << content->getTitle().c_str();
        
        QListWidgetItem* item = new QListWidgetItem(m_contentList);
        loadContentPreview(content.get(), item);
    }
}

void LibraryWindow::hideDetailView() {
    m_detailWindow->hide();
    m_contentList->show();
}

void LibraryWindow::editContent(Content* content) 
{
    if (!content) {
        qCritical() << "Attempted to edit null content!";
        return;
    }

    ContentEditWindow *editWindow = new ContentEditWindow(content, this);
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

void LibraryWindow::verifyResources() {
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