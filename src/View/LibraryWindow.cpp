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
#include <QTimer>
#include <QHBoxLayout>
#include <QStyle>

LibraryWindow::LibraryWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    connectSignals();
    updateContentDisplay();
}

LibraryWindow::~LibraryWindow() {
    delete m_detailWindow;
    delete m_searchTimer;
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
    
    // Search bar with clear button
    auto *searchContainer = new QWidget();
    auto *searchLayout = new QHBoxLayout(searchContainer);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    
    m_searchBar = new QLineEdit();
    m_searchBar->setPlaceholderText("Search content...");
    m_clearSearchButton = new QToolButton();
    m_clearSearchButton->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
    m_clearSearchButton->setCursor(Qt::PointingHandCursor);
    m_clearSearchButton->setToolTip("Clear search");
    m_clearSearchButton->hide();
    
    searchLayout->addWidget(m_searchBar);
    searchLayout->addWidget(m_clearSearchButton);
    
    setupFilterSection();
      
    leftLayout->addWidget(searchContainer);
    leftLayout->addWidget(m_filtersToggleBtn);
    leftLayout->addWidget(m_filtersSection);
    leftLayout->addStretch();

    // Right panel - Main stack
    m_rightPanel = new QStackedWidget();
    m_mainView = new QWidget();
    auto *rightLayout = new QVBoxLayout(m_mainView);
    
    setupContentListView();
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
    setupToolbar();
}

void LibraryWindow::setupContentListView() {
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
}

void LibraryWindow::setupFilterSection() {
    // Create the filters dropdown section
    m_filtersSection = new QWidget();
    auto* filtersLayout = new QVBoxLayout(m_filtersSection);
    filtersLayout->setContentsMargins(0, 10, 0, 10);
    
    // Genre filter group
    auto* genreGroupBox = new QGroupBox("Genre Filters");
    auto* genreLayout = new QVBoxLayout(genreGroupBox);
    m_genreFilterList = createFilterList({
        "Action",
        "Comedy",
        "Drama",
        "Horror",
        "Romance",
        "Thriller",
        "Mystery",
        "Adventure",
        "Western",
        "War",
        "Musical",
        "Family",
        "Sports",
        "Superhero"    
    });
    genreLayout->addWidget(m_genreFilterList);
    
    // Type filter group
    auto* typeGroupBox = new QGroupBox("Type Filters");
    auto* typeLayout = new QVBoxLayout(typeGroupBox);
    m_typeFilterList = createFilterList({"Book", "Comic", "Film", "Serie", "VideoGame"});
    typeLayout->addWidget(m_typeFilterList);
    

    // Status filter group
    auto* statusGroupBox = new QGroupBox("Status Filters");
    auto* statusLayout = new QVBoxLayout(statusGroupBox);
    m_statusFilterList = createFilterList({"Watched", "Starred"});
    statusLayout->addWidget(m_statusFilterList);
    
    // Clear button and counter
    auto* filterFooter = new QWidget();
    auto* footerLayout = new QHBoxLayout(filterFooter);
    m_clearFiltersBtn = new QPushButton("Clear All Filters");
    m_filterCounter = new QLabel("0 items");
    footerLayout->addWidget(m_clearFiltersBtn);
    footerLayout->addWidget(m_filterCounter);
    
    // Add groups to main filter layout
    filtersLayout->addWidget(typeGroupBox);
    filtersLayout->addWidget(genreGroupBox);
    filtersLayout->addWidget(statusGroupBox);
    filtersLayout->addWidget(filterFooter);
    
    // Initially hide the filters section
    m_filtersSection->setVisible(false);
    
    // Create toggle button for filters
    m_filtersToggleBtn = new QToolButton();
    m_filtersToggleBtn->setText("Filters ▼");
    m_filtersToggleBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_filtersToggleBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_filtersToggleBtn->setCheckable(true);
}

void LibraryWindow::setupToolbar() {
    createImportButton();
    m_toolBar->addWidget(m_importButton);
    
    createSaveMenu();
    m_toolBar->addWidget(m_saveButton);
}

void LibraryWindow::connectSignals() {
    // Content list interactions
    connect(m_contentList, &QListWidget::itemDoubleClicked, this, &LibraryWindow::showContentDetails);

    // Detail window signals
    connect(m_detailWindow, &ContentDetailWindow::editRequested, this, &LibraryWindow::editContent);
    connect(this, &LibraryWindow::contentDataChanged, m_detailWindow, &ContentDetailWindow::refreshContent);
    connect(m_detailWindow, &ContentDetailWindow::closeRequested, this, &LibraryWindow::hideDetailView);
    connect(m_detailWindow, &ContentDetailWindow::contentDeleted, this, &LibraryWindow::updateContentDisplay);

    // Filter signals
    connect(m_filtersToggleBtn, &QToolButton::clicked, this, &LibraryWindow::toggleFiltersSection);
    connect(m_genreFilterList, &QListWidget::itemChanged, this, &LibraryWindow::applyFilters);
    connect(m_typeFilterList, &QListWidget::itemChanged, this, &LibraryWindow::applyFilters);
    connect(m_statusFilterList, &QListWidget::itemChanged, this, &LibraryWindow::applyFilters);
    connect(m_clearFiltersBtn, &QPushButton::clicked, this, &LibraryWindow::clearFilters);

    // Search signals
    m_searchTimer = new QTimer(this);
    m_searchTimer->setSingleShot(true);
    connect(m_searchTimer, &QTimer::timeout, this, &LibraryWindow::delayedSearch);

    connect(m_searchBar, &QLineEdit::textChanged, [this]() {
        m_clearSearchButton->setVisible(!m_searchBar->text().isEmpty());
        m_searchTimer->start(SEARCH_DELAY_MS);
    });
    connect(m_clearSearchButton, &QToolButton::clicked, this, &LibraryWindow::clearSearch);

    // Add content
    connect(m_add, &QToolButton::clicked, this, &LibraryWindow::showAddContentDialog);
}

void LibraryWindow::delayedSearch() {
    applyFilters();
}

void LibraryWindow::clearSearch() {
    m_searchBar->clear();
    applyFilters();
}

void LibraryWindow::updateContentDisplay() {
    auto& library = ScienceFiction_Library::getInstance();
    m_contentList->clear();
    
    std::vector<Content*> contentList;
    if (library.getShownContentList().empty() && m_searchBar->text().isEmpty()) {
        for (const auto& content : library.getContentList()) {
            contentList.push_back(content.get());
        }
    } else {
        for (const auto& content : library.getShownContentList()) {
            contentList.push_back(content);
        }
    }
    
    if (!contentList.empty()) {
        for (const auto& content : contentList) {
            auto* item = new QListWidgetItem();
            loadContentPreview(content, item);
            m_contentList->addItem(item);
        }
        m_contentContainer->setCurrentIndex(0);
    } else {
        m_contentContainer->setCurrentIndex(1);
    }
    
    // Update filter counter
    m_filterCounter->setText(QString("%1 items").arg(contentList.size()));
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

void LibraryWindow::editContent(Content* content) {
    if (!content) {
        qCritical() << "Attempted to edit null content!";
        return;
    }

    auto *editWindow = new ContentEditWindow(content, this);
    editWindow->setAttribute(Qt::WA_DeleteOnClose);
    
    connect(editWindow, &ContentEditWindow::contentUpdated, 
            this, &LibraryWindow::updateContentDisplay);
    connect(editWindow, &ContentEditWindow::contentUpdated,
            this, [this]() { emit contentDataChanged(); });
            
    editWindow->exec();
}

void LibraryWindow::showAddContentDialog(bool checked) {
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

void LibraryWindow::applyQuickFilter(int index) {
    clearFilters();
    
    static const QMap<int, std::pair<QListWidget*, QString>> filterMap = {
        {1, {m_genreFilterList, "Action"}},
        {2, {m_genreFilterList, "Comedy"}},
        {3, {m_genreFilterList, "Drama"}},
        {4, {m_genreFilterList, "Horror"}},
        {5, {m_genreFilterList, "Romance"}},
        {6, {m_genreFilterList, "Thriller"}},
        {7, {m_genreFilterList, "Mystery"}},
        {8, {m_genreFilterList, "Adventure"}},
        {9, {m_genreFilterList, "Western"}},
        {10, {m_genreFilterList, "War"}},
        {11, {m_genreFilterList, "Musical"}},
        {12, {m_genreFilterList, "Family"}},
        {13, {m_genreFilterList, "Sports"}},
        {14, {m_genreFilterList, "Superhero"}},

        {1, {m_typeFilterList, "Book"}},
        {2, {m_typeFilterList, "Comic"}},
        {3, {m_typeFilterList, "Film"}},
        {4, {m_typeFilterList, "Serie"}},
        {5, {m_typeFilterList, "VideoGame"}},

        {1, {m_statusFilterList, "Watched"}},
        {2, {m_statusFilterList, "Unwatched"}},

     
    };
    
    if (filterMap.contains(index)) {
        auto [list, text] = filterMap[index];
        for (int i = 0; i < list->count(); i++) {
            if (list->item(i)->text() == text) {
                list->item(i)->setCheckState(Qt::Checked);
                break;
            }
        }
    }
    applyFilters();
}

void LibraryWindow::applyFilters() {
    auto& library = ScienceFiction_Library::getInstance();
    library.clearFilters();
    
    // Apply title filter
    if (!m_searchBar->text().isEmpty()) {
        library.filterByTitle(m_searchBar->text().toStdString());
    }
    
    // Apply type filters
    for (int i = 0; i < m_typeFilterList->count(); i++) {
        /*QListWidgetItem* item = m_typeFilterList->item(i);
        if (item->checkState() == Qt::Checked) {
            if (item->text() == "Book") {
                library.filterByType(static_cast<std::underlying_type_t<ContentType>>(ContentType::BOOK));
            } 
            else if (item->text() == "Comic") {
                library.filterByType(static_cast<std::underlying_type_t<ContentType>>(ContentType::COMIC));
            } 
            else if (item->text() == "Film") {
                library.filterByType(static_cast<std::underlying_type_t<ContentType>>(ContentType::FILM));
            } 
            else if (item->text() == "Serie") {
                library.filterByType(static_cast<std::underlying_type_t<ContentType>>(ContentType::SERIE));
            } 
            else if (item->text() == "VideoGame") {
                library.filterByType(static_cast<std::underlying_type_t<ContentType>>(ContentType::VIDEO_GAME));
            }
        }*/
    }

    // Apply genre filters
    for (int i = 0; i < m_genreFilterList->count(); i++) {
        QListWidgetItem* item = m_genreFilterList->item(i);
        if (item->checkState() == Qt::Checked) {
            if (item->text() == "Action") {
                library.filterBySubgenreId(static_cast<std::underlying_type_t<Subgenre>>(Subgenre::ACTION));
            } 
            else if (item->text() == "War") {
                library.filterBySubgenreId(static_cast<std::underlying_type_t<Subgenre>>(Subgenre::WAR));
            }
            // Add other genres as needed
        }
    }
    

    // Apply status filters
    for (int i = 0; i < m_statusFilterList->count(); i++) {
        QListWidgetItem* item = m_statusFilterList->item(i);
        if (item->checkState() == Qt::Checked) {
            if (item->text() == "Watched") {
                library.filterByWatched(true);
            }
            else if (item->text() == "Starred") {
                library.filterByStarred(true);
            }
        }
    }
    
    updateContentDisplay();
}

void LibraryWindow::clearFilters() {
    m_searchBar->clear();

    for (int i = 0; i < m_typeFilterList->count(); i++) {
        m_genreFilterList->item(i)->setCheckState(Qt::Unchecked);
    }
    
    for (int i = 0; i < m_genreFilterList->count(); i++) {
        m_genreFilterList->item(i)->setCheckState(Qt::Unchecked);
    }
    
    for (int i = 0; i < m_statusFilterList->count(); i++) {
        m_statusFilterList->item(i)->setCheckState(Qt::Unchecked);
    }
    
    ScienceFiction_Library::getInstance().clearFilters();
    updateContentDisplay();
}

void LibraryWindow::toggleFiltersSection() {
    bool isVisible = !m_filtersSection->isVisible();
    m_filtersSection->setVisible(isVisible);
    m_filtersToggleBtn->setText(isVisible ? "Filters ▲" : "Filters ▼");
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