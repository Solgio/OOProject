#include "LibraryWindow.h"
#include "PreviewWidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>
#include <QSplitter>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

LibraryWindow::LibraryWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
    connectSignals();
    updateContentDisplay();
}

void LibraryWindow::setupUI() {
    // Configurazione finestra principale
    setWindowTitle("Science Fiction Library Manager");
    resize(1024, 768);

    // Barra strumenti
    m_toolBar = addToolBar("Main Toolbar");
    m_toolBar->addAction("Import", this, &LibraryWindow::importContent);
    m_toolBar->addAction("Save XML", [this]() { saveToFile("xml"); });
    m_toolBar->addAction("Save JSON", [this]() { saveToFile("json"); });

    // Lista contenuti
    m_contentList = new QListWidget();
    m_contentList->setViewMode(QListView::IconMode);
    m_contentList->setIconSize(m_previewSize);
    m_contentList->setResizeMode(QListView::Adjust);
    m_contentList->setSpacing(15);

    // Dettagli contenuto
    m_contentDetails = new QLabel("Select an item to view details");
    m_contentDetails->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_contentDetails->setWordWrap(true);
    m_contentDetails->setTextFormat(Qt::RichText);

    // Ricerca e filtri
    m_searchBar = new QLineEdit();
    m_searchBar->setPlaceholderText("Search content...");
    m_filterCombo = new QComboBox();
    m_filterCombo->addItems({"All", "Movies", "Books", "Watched", "Starred"});

    // Layout principale
    QWidget *leftPanel = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->addWidget(m_searchBar);
    leftLayout->addWidget(m_filterCombo);
    leftLayout->addWidget(m_contentList);

    m_splitter = new QSplitter(Qt::Horizontal);
    m_splitter->addWidget(leftPanel);
    m_splitter->addWidget(m_contentDetails);
    m_splitter->setStretchFactor(1, 2);

    setCentralWidget(m_splitter);

    m_contentList->setViewMode(QListView::IconMode);
    m_contentList->setIconSize(QSize(120, 180));
    m_contentList->setGridSize(QSize(150, 220));
    m_contentList->setWordWrap(true);
    m_contentList->setStyleSheet(
        "QListView::item { padding: 10px; margin: 5px; border: 1px solid #ddd; }"
        "QListView::item:hover { background: #f0f0f0; }"
    );
    
    // DEBUG: Aggiungi un pulsante di test
    QPushButton* testBtn = new QPushButton("Test Connection");
    connect(testBtn, &QPushButton::clicked, this, &LibraryWindow::verifyResources);
    m_toolBar->addWidget(testBtn);
}

void LibraryWindow::connectSignals() {
    connect(m_contentList, &QListWidget::itemClicked, 
            this, &LibraryWindow::showContentDetails);
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

void LibraryWindow::updateContentDisplay() {qDebug() << "Updating content display...";
    m_contentList->clear();

    auto& library = ScienceFiction_Library::getInstance();
    const auto& contents = library.getContentList();
    
    qDebug() << "Library contains" << contents.size() << "items";
    
    for (const auto& content : contents) 
    {
        qDebug() << "Processing item:" << content->getId() << content->getTitle().c_str();
        
        QListWidgetItem* item = new QListWidgetItem(m_contentList);
        item->setText(QString::fromStdString(content->getTitle()));
        
        QString imagePath = QString::fromStdString(content->getImage());
        qDebug() << "Image path:" << imagePath;
        
        if(QFile::exists(imagePath)) {
            qDebug() << "Image found, loading...";
            QPixmap pixmap(imagePath);
            item->setIcon(QIcon(pixmap.scaled(100, 150, Qt::KeepAspectRatio)));
        } else {
            qWarning() << "Image not found, using default";
            item->setIcon(QIcon(":assets/icons/default.png"));
        }
        
        item->setData(Qt::UserRole, QVariant(content->getId()));
    }
}

void LibraryWindow::showContentDetails(QListWidgetItem *item) {
    unsigned int id = item->data(Qt::UserRole).toUInt();
    Content* content = ScienceFiction_Library::getInstance().searchId(id);
    
    if (content) {
        QString html = QString(
            "<div style='margin:10px;'>"
            "<h2>%1</h2>"
            "<div style='float:right; margin-left:20px;'>"
            "<img src='%2' width='200' onerror=\":assets/icons/default.png'\">"
            "</div>"
            "<p><b>Year:</b> %3</p>"
            "<p><b>Genre:</b> %4</p>"
            "<p><b>Watched:</b> %5</p>"
            "<p><b>Starred:</b> %6</p>"
            "<p><b>Description:</b><br>%7</p>"
            "</div>"
        ).arg(
            QString::fromStdString(content->getTitle()),
            QString::fromStdString(content->getImage()),
            QString::number(content->getYear()),
            QString::fromStdString(content->getSubgenreString()),
            content->getWatched() ? "Yes" : "No",
            content->getStarred() ? "Yes" : "No",
            QString::fromStdString(content->getDescription())
        );
        
        m_contentDetails->setText(html);
    }
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
void LibraryWindow::verifyResources()
{
    qDebug() << "Working directory:" << QDir::currentPath();
    
    // Verifica immagini di default
    qDebug() << "Default icon exists:" << QFile::exists("/home/solgio/Desktop/OOProject/assets/icons/default.png");
    
    // Verifica percorsi dei contenuti
    auto& library = ScienceFiction_Library::getInstance();
    for (const auto& content : library.getContentList()) 
    {
        QString path = QString::fromStdString(content->getImage());
        qDebug() << "Content" << content->getId() 
                 << "| Title:" << QString::fromStdString(content->getTitle())
                 << "| Path:" << path 
                 << "| Exists Image:" << QFile::exists(path);
    }
}