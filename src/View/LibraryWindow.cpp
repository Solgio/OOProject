#include "LibraryWindow.h"
#include "ContentDetailWindow.h"
#include "TypeChoiceDialog.h"
#include "ContentEditWindow.h"
#include "../Model/lib/ScienceFictionLibrary.h"
#include "../Model/lib/Content.h"

#include <QLabel>
#include <QToolButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QToolBar>
#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QCheckBox>
#include <QGroupBox>


LibraryWindow::LibraryWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    connectSignals();
    updateContentDisplay();
}

LibraryWindow::~LibraryWindow() {
    delete m_detailWindow;
}

void LibraryWindow::setupUI() {
    setWindowTitle("Science Fiction Library Manager");
    resize(1920, 1080);

    // Main structure
    m_splitter = new QSplitter(Qt::Horizontal);
    m_toolBar = addToolBar("Main Toolbar");

    // Left panel (filters)
    auto *leftPanel = new QWidget();
    auto *leftLayout = new QVBoxLayout(leftPanel);
    
    m_searchBar = new QLineEdit();
    m_searchBar->setPlaceholderText("Search content...");
    setupFiltersSection();
   
    m_clearFiltersBtn = new QPushButton("Clear Filters");
      
    leftLayout->addWidget(m_searchBar);
    leftLayout->addWidget(m_filtersToggleBtn);
    leftLayout->addWidget(m_filtersSection);

    leftLayout->addStretch();

    // Right panel - Main stack
    m_rightPanel = new QStackedWidget();
    m_mainView = new QWidget();
    auto *rightLayout = new QVBoxLayout(m_mainView);
    
    // Content container (list/no results)
    m_contentContainer = new QStackedWidget();
    m_contentList = new QListWidget();
    m_contentList->setViewMode(QListWidget::IconMode);
    m_contentList->setIconSize(m_previewSize);
    m_contentList->setResizeMode(QListWidget::Adjust);
    m_contentList->setMovement(QListWidget::Static);
    
    m_noResultsLabel = new QLabel();
    m_noResultsLabel->setAlignment(Qt::AlignCenter);
    m_noResultsLabel->setText("<center><h2 style='color:gray;'>No results found</h2>"
                            "<p style='color:gray;'>Try different search terms</p></center>");
    m_noResultsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    m_contentContainer->addWidget(m_contentList);
    m_contentContainer->addWidget(m_noResultsLabel);
    
    rightLayout->addWidget(new QLabel("Content Preview:"));
    rightLayout->addWidget(m_contentContainer);
    
    // Add button
    auto *addButtonContainer = new QWidget();
    auto *addButtonLayout = new QHBoxLayout(addButtonContainer);
    addButtonLayout->addStretch();
    
    m_add = new QToolButton();
    m_add->setText("Add Content");
    m_add->setIcon(QIcon(":assets/icons/add.png"));
    m_add->setToolTip("Add new content to the library");
    m_add->setIconSize(QSize(32, 32));
    addButtonLayout->addWidget(m_add);
    
    rightLayout->addWidget(addButtonContainer);
    
    // Detail window
    m_detailWindow = new ContentDetailWindow();
    
    // Add views to main stack
    m_rightPanel->addWidget(m_mainView);      // Index 0
    m_rightPanel->addWidget(m_detailWindow);  // Index 1
    
    // Final setup
    m_splitter->addWidget(leftPanel);
    m_splitter->addWidget(m_rightPanel);
    setCentralWidget(m_splitter);
    
    // Toolbar
    createToolbar();
}

void LibraryWindow::toggleFiltersSection() {
    bool isVisible = !m_filtersSection->isVisible();
    m_filtersSection->setVisible(isVisible);
    m_filtersToggleBtn->setText(isVisible ? "Filters ▲" : "Filters ▼");
}


void LibraryWindow::updateContentDisplay() {
    auto& library = ScienceFiction_Library::getInstance();
    
    m_contentList->clear();
    
    if (!library.getShownContentList().empty()) {
        for (Content* content : library.getShownContentList()) {
            auto* item = new QListWidgetItem();
            loadContentPreview(content, item);
            m_contentList->addItem(item);
        }
        m_contentContainer->setCurrentIndex(0);
    } 
    else if (m_searchBar->text().isEmpty()) {
        for (const auto& contentPtr : library.getContentList()) {
            auto* item = new QListWidgetItem();
            loadContentPreview(contentPtr.get(), item);
            m_contentList->addItem(item);
        }
        m_contentContainer->setCurrentIndex(0);
    }
    else {
        m_contentContainer->setCurrentIndex(1);
    }
}

void LibraryWindow::showContentDetails(QListWidgetItem *item) {
    if (!item) return;

    bool ok;
    unsigned int id = item->data(Qt::UserRole).toUInt(&ok);
    Content* content = ScienceFiction_Library::getInstance().searchId(id);
    
    if (ok && content) {
        m_detailWindow->setContent(content);
        m_rightPanel->setCurrentIndex(1);
    }
}

void LibraryWindow::hideDetailView() {
    m_rightPanel->setCurrentIndex(0);
}

void LibraryWindow::createToolbar() {
    createImportButton();
    m_toolBar->addWidget(m_importButton);
    
    createSaveMenu();
    m_toolBar->addWidget(m_saveButton);
    
    auto* testBtn = new QPushButton("Test Connection");
    m_toolBar->addWidget(testBtn);
}

void LibraryWindow::editContent(Content* content) 
{
    if (!content) {
        qCritical() << "Attempted to edit null content!";
        return;
    }

    auto *editWindow = new ContentEditWindow(content, this);
    editWindow->setAttribute(Qt::WA_DeleteOnClose);
    
    // Update both the library view and detail view when content is updated
    connect(editWindow, &ContentEditWindow::contentUpdated, 
            this, &LibraryWindow::updateContentDisplay);
    connect(editWindow, &ContentEditWindow::contentUpdated,
            this, [this]() { emit contentDataChanged(); });
            
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
    
    // Verify default images
    qDebug() << "Default icon exists:" << QFile::exists("/home/solgio/Desktop/OOProject/assets/icons/default.png");
    
    // Verify content paths
    auto& library = ScienceFiction_Library::getInstance();
    for (const auto& content : library.getContentList()) {
        QString path = QString::fromStdString(content->getImage());
        qDebug() << "Content" << content->getId() 
                 << "| Title:" << QString::fromStdString(content->getTitle())
                 << "| Path:" << path 
                 << "| Exists Image:" << QFile::exists(path);
    }
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
            newContent->setId(ScienceFiction_Library::getInstance().getNewId());
            ScienceFiction_Library::getInstance().addContent(newContent);
            editContent(newContent);
        }
    }
}

void LibraryWindow::connectSignals() {
    connect(m_contentList, &QListWidget::itemDoubleClicked, this, &LibraryWindow::showContentDetails);

    connect(m_detailWindow, &ContentDetailWindow::editRequested, this, &LibraryWindow::editContent);
    
    connect(this, &LibraryWindow::contentDataChanged, m_detailWindow, &ContentDetailWindow::refreshContent);

    connect(m_detailWindow, &ContentDetailWindow::closeRequested, this, &LibraryWindow::hideDetailView);

    
        connect(m_filtersToggleBtn, &QToolButton::clicked, this, &LibraryWindow::toggleFiltersSection);
    

        connect(m_searchBar, &QLineEdit::textChanged, this, 
            [this](const QString &text) {
                Q_UNUSED(text); // The text is handled in applyFilters()
                applyFilters();
            });
    
            connect(m_genreFilterList, &QListWidget::itemChanged, this, &LibraryWindow::applyFilters);
            connect(m_statusFilterList, &QListWidget::itemChanged, this, &LibraryWindow::applyFilters);
            connect(m_clearFiltersBtn, &QPushButton::clicked, this, &LibraryWindow::clearFilters);
        
    connect(m_add, &QToolButton::clicked, this, &LibraryWindow::editContentTriggered);

    connect(m_detailWindow, &ContentDetailWindow::contentDeleted, this, &LibraryWindow::updateContentDisplay);
}
void LibraryWindow::applyFilters() {
    auto& library = ScienceFiction_Library::getInstance();
    
    // Always start fresh with all content
    library.clearFilters();
    
    // Apply title filter first if there's text in the search bar
    if (!m_searchBar->text().isEmpty()) {
        library.filterByTitle(m_searchBar->text().toStdString());
    }
    
    // Check selected genre filters
    bool hasGenreFilter = false;
    for (int i = 0; i < m_genreFilterList->count(); i++) {
        QListWidgetItem* item = m_genreFilterList->item(i);
        if (item->checkState() == Qt::Checked) {
            hasGenreFilter = true;
            
            // Map text labels to corresponding Subgenre enum values
            if (item->text() == "Action") {
                library.filterBySubgenreId(static_cast<std::underlying_type_t<Subgenre>>(Subgenre::ACTION));
            } 
            else if (item->text() == "War") {
                library.filterBySubgenreId(static_cast<std::underlying_type_t<Subgenre>>(Subgenre::WAR));
            }
            // Add other genres as needed
        }
    }
    
    // Check selected status filters
    bool hasStatusFilter = false;
    for (int i = 0; i < m_statusFilterList->count(); i++) {
        QListWidgetItem* item = m_statusFilterList->item(i);
        if (item->checkState() == Qt::Checked) {
            hasStatusFilter = true;
            
            if (item->text() == "Watched") {
                library.filterByWatched(true);
            }
            else if (item->text() == "Starred") {
                library.filterByStarred(true);
            }
            // Add other statuses as needed
        }
    }
    
    updateContentDisplay();
}

void LibraryWindow::clearFilters() {
    // Reset search text
    m_searchBar->clear();
    
    // Uncheck all genre filter items
    for (int i = 0; i < m_genreFilterList->count(); i++) {
        m_genreFilterList->item(i)->setCheckState(Qt::Unchecked);
    }
    
    // Uncheck all status filter items
    for (int i = 0; i < m_statusFilterList->count(); i++) {
        m_statusFilterList->item(i)->setCheckState(Qt::Unchecked);
    }
    
    // Clear filters in library
    ScienceFiction_Library::getInstance().clearFilters();
    updateContentDisplay();
}

void LibraryWindow::setupFiltersSection() {
    // Create the filters dropdown section
    m_filtersSection = new QWidget();
    auto* filtersLayout = new QVBoxLayout(m_filtersSection);
    filtersLayout->setContentsMargins(0, 10, 0, 10);
    
    // Genre filter group
    auto* genreGroupBox = new QGroupBox("Genre Filters");
    auto* genreLayout = new QVBoxLayout(genreGroupBox);
    m_genreFilterList = createFilterList({"Action", "War", "Dystopian", "Space Opera", "Cyberpunk"});
    genreLayout->addWidget(m_genreFilterList);
    
    // Status filter group
    auto* statusGroupBox = new QGroupBox("Status Filters");
    auto* statusLayout = new QVBoxLayout(statusGroupBox);
    m_statusFilterList = createFilterList({"Watched", "Starred", "To Watch"});
    statusLayout->addWidget(m_statusFilterList);
    
    // Clear button
    m_clearFiltersBtn = new QPushButton("Clear All Filters");
    
    // Add groups to main filter layout
    filtersLayout->addWidget(genreGroupBox);
    filtersLayout->addWidget(statusGroupBox);
    filtersLayout->addWidget(m_clearFiltersBtn);
    
    // Initially hide the filters section
    m_filtersSection->setVisible(false);
    
    // Create toggle button for filters
    m_filtersToggleBtn = new QToolButton();
    m_filtersToggleBtn->setText("Filters ▼");
    m_filtersToggleBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_filtersToggleBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_filtersToggleBtn->setCheckable(true);
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

QListWidget* LibraryWindow::createFilterList(const QStringList& options) {
    auto* list = new QListWidget();
    list->setMaximumHeight(120);
    
    for (const QString& option : options) {
        QListWidgetItem* item = new QListWidgetItem(option, list);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }
    
    return list;
}

void LibraryWindow::loadContentPreview(Content* content, QListWidgetItem* item) const {
    if (!content) return;

    item->setText(QString::fromStdString(content->getTitle()));
    item->setData(Qt::UserRole, QVariant(content->getId()));
    
    QPixmap pixmap = loadSafePixmap(
        QString::fromStdString(content->getImage()),
        m_previewSize
    );
    item->setIcon(QIcon(pixmap));
}

// Add this method back to LibraryWindow.cpp
void LibraryWindow::onFilterChanged(int index) {
    // Clear all filters first
    clearFilters();
    
    // Set specific filters based on the index
    switch (index) {
        case 0: // "All"
            // Do nothing, already cleared
            break;
        case 1: // "Action"
            for (int i = 0; i < m_genreFilterList->count(); i++) {
                if (m_genreFilterList->item(i)->text() == "Action") {
                    m_genreFilterList->item(i)->setCheckState(Qt::Checked);
                    break;
                }
            }
            break;
        case 2: // "War"
            for (int i = 0; i < m_genreFilterList->count(); i++) {
                if (m_genreFilterList->item(i)->text() == "War") {
                    m_genreFilterList->item(i)->setCheckState(Qt::Checked);
                    break;
                }
            }
            break;
        case 3: // "Watched"
            for (int i = 0; i < m_statusFilterList->count(); i++) {
                if (m_statusFilterList->item(i)->text() == "Watched") {
                    m_statusFilterList->item(i)->setCheckState(Qt::Checked);
                    break;
                }
            }
            break;
        case 4: // "Starred"
            for (int i = 0; i < m_statusFilterList->count(); i++) {
                if (m_statusFilterList->item(i)->text() == "Starred") {
                    m_statusFilterList->item(i)->setCheckState(Qt::Checked);
                    break;
                }
            }
            break;
        default:
            break;
    }
}