#include "LibraryWindow.h"
#include "ContentDetailWindow.h"
#include "TypeChoiceDialog.h"
#include "ContentEditWindow.h"
#include "ContentModel.h"
#include "ContentProxyModel.h"

#include "../Model/lib/ScienceFictionLibrary.h"
#include "../Model/lib/Content.h"
#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Serie.h"
#include "../Model/lib/VideoGame.h"

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
#include <QHeaderView>
#include <QListWidget>
#include <QEvent>

LibraryWindow::LibraryWindow(QWidget *parent) : QMainWindow(parent) {
    // Initialize search timer
    m_searchTimer = new QTimer(this);
    m_searchTimer->setSingleShot(true);
    m_searchTimer->setInterval(SEARCH_DELAY_MS);
    
    // Initialize filter toggle button
    m_filtersToggleBtn = new QToolButton();
    m_filtersToggleBtn->setText("Filters");
    m_filtersToggleBtn->setCheckable(true);
    m_filtersToggleBtn->setToolTip("Show/Hide filters");
    
    setupUI();
    connectSignals();
    updateContentDisplay();
}

LibraryWindow::~LibraryWindow() {
    delete m_detailWindow;
    delete m_searchTimer;
}

bool LibraryWindow::eventFilter(QObject* obj, QEvent* event) {
    // Event filter for custom widgets if needed
    return QMainWindow::eventFilter(obj, event);
}

void LibraryWindow::setupUI() {
    setWindowTitle("Science Fiction Library Manager");
    resize(1920, 1080);

    // Main structure
    m_splitter = new QSplitter(Qt::Horizontal);
    m_toolBar = addToolBar("Main Toolbar");
    m_toolBar->setIconSize(QSize(28, 28));
    

    // Left panel (filters and sorting)
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
    
    // Setup filter section
    setupFilterSection();
    
    // Setup sorting controls 
    setupSortingControls();
    
    leftLayout->addWidget(searchContainer);
    leftLayout->addWidget(m_filtersToggleBtn);
    leftLayout->addWidget(m_filtersSection);

    auto *sortingContainer = new QWidget();
    m_sortingLayout = new QHBoxLayout(sortingContainer);
    leftLayout->addWidget(new QLabel("Sort by:"));
    leftLayout->addWidget(m_sortingComboBox);
    
    auto *sortDirectionLayout = new QHBoxLayout();
    sortDirectionLayout->addWidget(new QLabel("Direction:"));
    sortDirectionLayout->addWidget(m_sortDirectionButton);
    sortDirectionLayout->addStretch();

    m_sortingLayout->addWidget(m_sortingComboBox);
    
    auto *sortDirectionContainer = new QWidget();
    sortDirectionContainer->setLayout(sortDirectionLayout);
    m_sortingLayout->addWidget(sortDirectionContainer);
    leftLayout->addWidget(sortingContainer);
    leftLayout->addStretch();

    // Setup content table
    setupContentTable();

    // Right panel - Main stack
    m_rightPanel = new QStackedWidget();
    m_mainView = new QWidget();
    auto *rightLayout = new QVBoxLayout(m_mainView);
    
    // Setup content preview widget
    setupPreviewWidget();
    rightLayout->addWidget(new QLabel("Content Library:"));
    rightLayout->addWidget(m_previewScrollArea);
    
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
    m_splitter->setStretchFactor(0, 1);  // Left panel gets minimal space
    m_splitter->setStretchFactor(1, 4);  // Right panel gets 4x more space
    setCentralWidget(m_splitter);
    
    // Toolbar
    setupToolbar();
}

void LibraryWindow::setupPreviewWidget() {
    // Create the model and proxy model if not already created
    if (!m_contentModel) {
        m_contentModel = new ContentModel(this);
    }
    
    if (!m_proxyModel) {
        m_proxyModel = new ContentProxyModel(this);
        m_proxyModel->setSourceModel(m_contentModel);
    }
    
    // Create scroll area
    m_previewScrollArea = new QScrollArea();
    m_previewScrollArea->setWidgetResizable(true);
    m_previewScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_previewScrollArea->setFrameShape(QFrame::NoFrame);
    
    // Create the preview widget with a grid layout
    m_previewWidget = new QWidget();
    m_previewLayout = new QGridLayout(m_previewWidget);
    m_previewLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_previewLayout->setSpacing(10); // Reduced spacing
    m_previewLayout->setContentsMargins(5, 5, 5, 5);
    
    // Add no results label
    m_noResultsLabel = new QLabel();
    m_noResultsLabel->setPixmap(QPixmap(":assets/icons/no-results.png"));
    m_noResultsLabel->setAlignment(Qt::AlignCenter);
    m_noResultsLabel->setText("<center><h2 style='color:gray;'>No results found</h2></center>");
    m_noResultsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_noResultsLabel->hide();
    
    m_previewLayout->addWidget(m_noResultsLabel, 0, 0, 1, 6); // Span all columns
    m_previewScrollArea->setWidget(m_previewWidget);
}

void LibraryWindow::setupSortingControls() {
    // Create sorting combo box


    m_sortingComboBox = new QComboBox();
    m_sortingComboBox->setToolTip("Sort by");
    m_sortingComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_sortingComboBox->setMinimumWidth(120);
    m_sortingComboBox->addItem("Title", static_cast<int>(ContentModel::SortRole::Title));
    m_sortingComboBox->addItem("Release Date", static_cast<int>(ContentModel::SortRole::ReleaseDate));
    m_sortingComboBox->addItem("Rating", static_cast<int>(ContentModel::SortRole::Rating));
    m_sortingComboBox->addItem("Creator", static_cast<int>(ContentModel::SortRole::Creator));
    m_sortingComboBox->addItem("Type", static_cast<int>(ContentModel::SortRole::Type));
    
    // Create sort direction button
    m_sortDirectionButton = new QToolButton();
    m_sortDirectionButton->setIcon(QIcon(":assets/icons/ord-cresc.png"));
    m_sortDirectionButton->setIconSize(QSize(28, 28));
    m_sortDirectionButton->setCheckable(true);
    m_sortDirectionButton->setToolTip("Sort Ascending/Descending");

    // Connect signals
    connect(m_sortingComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
        [this](int index) {
            int role = m_sortingComboBox->itemData(index).toInt();
            m_proxyModel->setSortRole(static_cast<ContentModel::SortRole>(role));
            updateContentPreviews();
        });
    
    connect(m_sortDirectionButton, &QToolButton::clicked, this, &LibraryWindow::changeSortDirection);
}

void LibraryWindow::changeSortDirection() {
    bool isAscending = !m_sortDirectionButton->isChecked();
    
    // Update the button icon
    m_sortDirectionButton->setIcon(QIcon(isAscending ? 
        ":assets/icons/ord-cresc.png" : 
        ":assets/icons/ord-decresc.png"));
    
    
    // Update the sort order in the proxy model
    m_proxyModel->sort(0, isAscending ? Qt::AscendingOrder : Qt::DescendingOrder);
    
    // Refresh the content previews
    updateContentPreviews();
}

void LibraryWindow::setupContentTable() {
    m_contentContainer = new QStackedWidget();
    
    // Create the model and proxy model if they don't exist yet
    if (!m_contentModel) {
        m_contentModel = new ContentModel(this);
    }
    
    if (!m_proxyModel) {
        m_proxyModel = new ContentProxyModel(this);
        m_proxyModel->setSourceModel(m_contentModel);
    }
    
    // Create the table view
    m_contentTable = new QTableView();
    m_contentTable->setModel(m_proxyModel);
    m_contentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_contentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_contentTable->setSortingEnabled(true);
    m_contentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_contentTable->verticalHeader()->setVisible(false);
    m_contentTable->setAlternatingRowColors(true);
    
    // No results label (using the one already defined)
    if (!m_noResultsLabel) {
        m_noResultsLabel = new QLabel();
        m_noResultsLabel->setAlignment(Qt::AlignCenter);
        m_noResultsLabel->setText("<center><h2 style='color:gray;'>No results found</h2>"
                                 "<p style='color:gray;'>Try different search terms</p></center>");
        m_noResultsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
    
    m_contentContainer->addWidget(m_contentTable);
    m_contentContainer->addWidget(m_noResultsLabel);
}

void LibraryWindow::setupFilterSection() {
    // Create a compact filters section
    m_filtersSection = new QWidget();
    auto* filtersLayout = new QVBoxLayout(m_filtersSection);
    filtersLayout->setContentsMargins(0, 0, 0, 0);
    filtersLayout->setSpacing(5);

    // Type filter section
    auto* typeGroup = new QGroupBox("Content Types");
    typeGroup->setFlat(true);
    typeGroup->setStyleSheet("QGroupBox { border: 1px solid gray; border-radius: 3px; margin-top: 6px; }");
    
    auto* typeLayout = new QVBoxLayout(typeGroup);
    typeLayout->setContentsMargins(5, 15, 5, 5);
    
    QStringList types = {"Book", "Comic", "Film", "Serie", "VideoGame"};
    for (const QString& type : types) {
        QCheckBox* cb = new QCheckBox(type);
        cb->setProperty("filterType", "type");
        cb->setProperty("filterValue", type);
        connect(cb, &QCheckBox::stateChanged, this, &LibraryWindow::applyFilters);
        typeLayout->addWidget(cb);
    }
    filtersLayout->addWidget(typeGroup);

    // Genre filter section
    auto* genreGroup = new QGroupBox("Genres");
    genreGroup->setFlat(true);
    genreGroup->setStyleSheet("QGroupBox { border: 1px solid gray; border-radius: 3px; margin-top: 6px; }");
    
    auto* genreLayout = new QVBoxLayout(genreGroup);
    genreLayout->setContentsMargins(5, 15, 5, 5);
    
    // Get all available subgenres from the Content enum
    QMap<int, QString> genreMap;
    genreMap[static_cast<int>(Subgenre::NONE)] = "None";
    genreMap[static_cast<int>(Subgenre::ACTION)] = "Action";
    genreMap[static_cast<int>(Subgenre::ADVENTURE)] = "Adventure";
    genreMap[static_cast<int>(Subgenre::COMEDY)] = "Comedy";
    genreMap[static_cast<int>(Subgenre::DRAMA)] = "Drama";
    genreMap[static_cast<int>(Subgenre::HORROR)] = "Horror";
    genreMap[static_cast<int>(Subgenre::ROMANCE)] = "Romance";
    genreMap[static_cast<int>(Subgenre::THRILLER)] = "Thriller";
    genreMap[static_cast<int>(Subgenre::MYSTERY)] = "Mystery";
    genreMap[static_cast<int>(Subgenre::WESTERN)] = "Western";
    genreMap[static_cast<int>(Subgenre::WAR)] = "War";
    genreMap[static_cast<int>(Subgenre::MUSICAL)] = "Musical";
    genreMap[static_cast<int>(Subgenre::FAMILY)] = "Family";
    genreMap[static_cast<int>(Subgenre::SPORTS)] = "Sports";
    genreMap[static_cast<int>(Subgenre::SUPERHERO)] = "Superhero";
    
    for (auto it = genreMap.begin(); it != genreMap.end(); ++it) {
        QCheckBox* cb = new QCheckBox(it.value());
        cb->setProperty("filterType", "genre");
        cb->setProperty("filterValue", it.key());
        connect(cb, &QCheckBox::stateChanged, this, &LibraryWindow::applyFilters);
        genreLayout->addWidget(cb);
    }
    filtersLayout->addWidget(genreGroup);

    // Status filters (Watched/Starred)
    auto* statusGroup = new QGroupBox("Status");
    statusGroup->setFlat(true);
    statusGroup->setStyleSheet("QGroupBox { border: 1px solid gray; border-radius: 3px; margin-top: 6px; }");
    
    auto* statusLayout = new QVBoxLayout(statusGroup);
    statusLayout->setContentsMargins(5, 15, 5, 5);
    
    QCheckBox* watchedCb = new QCheckBox("Watched Only");
    watchedCb->setProperty("filterType", "watched");
    connect(watchedCb, &QCheckBox::stateChanged, 
        [this](int state) {
            m_proxyModel->setWatchedFilter(state == Qt::Checked);
            updateFilterCounter();
            updateContentPreviews();
        });
    statusLayout->addWidget(watchedCb);
    
    QCheckBox* starredCb = new QCheckBox("Starred Only");
    starredCb->setProperty("filterType", "starred");
    connect(starredCb, &QCheckBox::stateChanged, 
        [this](int state) {
            m_proxyModel->setStarredFilter(state == Qt::Checked);
            updateFilterCounter();
            updateContentPreviews();
        });
    statusLayout->addWidget(starredCb);
    
    filtersLayout->addWidget(statusGroup);

    // Clear button and counter in one row
    auto* bottomRow = new QWidget();
    auto* bottomLayout = new QHBoxLayout(bottomRow);
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    
    m_clearFiltersBtn = new QPushButton("Clear All");
    m_clearFiltersBtn->setMaximumWidth(80);
    bottomLayout->addWidget(m_clearFiltersBtn);
    
    m_filterCounter = new QLabel("0 items");
    bottomLayout->addWidget(m_filterCounter);
    bottomLayout->addStretch();
    
    filtersLayout->addWidget(bottomRow);

    // Initially hide the filters section
    m_filtersSection->setVisible(false);
}

void LibraryWindow::toggleFiltersSection() {
    m_filtersSection->setVisible(!m_filtersSection->isVisible());
    m_filtersToggleBtn->setChecked(m_filtersSection->isVisible());
}

void LibraryWindow::setupToolbar() {
    createImportButton();
    m_toolBar->addWidget(m_importButton);
    
    createSaveMenu();
    m_toolBar->addWidget(m_saveButton);
}

void LibraryWindow::connectSignals() {
    // Content table interactions
    connect(m_contentTable, &QTableView::doubleClicked, this, &LibraryWindow::showContentDetails);

    // Detail window signals
    connect(m_detailWindow, &ContentDetailWindow::editRequested, this, &LibraryWindow::editContent);
    connect(this, &LibraryWindow::contentDataChanged, m_detailWindow, &ContentDetailWindow::refreshContent);
    connect(m_detailWindow, &ContentDetailWindow::closeRequested, this, &LibraryWindow::hideDetailView);
    connect(m_detailWindow, &ContentDetailWindow::contentDeleted, this, &LibraryWindow::updateContentDisplay);

    // Filter signals
    connect(m_filtersToggleBtn, &QToolButton::clicked, this, &LibraryWindow::toggleFiltersSection);
    connect(m_clearFiltersBtn, &QPushButton::clicked, this, &LibraryWindow::clearFilters);

    // Search signals
    connect(m_searchBar, &QLineEdit::textChanged, this, &LibraryWindow::delayedSearch);
    connect(m_searchTimer, &QTimer::timeout, this, [this]() {
        applySearchFilter(m_searchBar->text());
    });
    connect(m_clearSearchButton, &QToolButton::clicked, this, &LibraryWindow::clearSearch);

    // Visibility of clear search button
    connect(m_searchBar, &QLineEdit::textChanged, this, [this](const QString &text) {
        m_clearSearchButton->setVisible(!text.isEmpty());
    });

    // Add button
    connect(m_add, &QToolButton::clicked, this, &LibraryWindow::showAddContentDialog);

    // Import/Save actions
    connect(m_importButton, &QToolButton::clicked, this, &LibraryWindow::importContent);
}

void LibraryWindow::createSaveMenu() {
    m_saveMenu = new QMenu(this);
    // Remove the existing style sheet and set icon size directly
    m_saveMenu->setStyleSheet("QMenu::item { padding: 5px 10px; }");

    // Create actions with 28px icons
    auto* saveJson = new QAction(QIcon(":assets/icons/w_json.png"), "Save as JSON", this);
    saveJson->setIconText("Save as JSON");  // Ensure text is preserved
    saveJson->setToolTip("Export library as JSON file");
    connect(saveJson, &QAction::triggered, this, [this]() { saveToFile("json"); });
    
    auto* saveXml = new QAction(QIcon(":assets/icons/w_xml.png"), "Save as XML", this);
    saveXml->setIconText("Save as XML");    // Ensure text is preserved
    saveXml->setToolTip("Export library as XML file");
    connect(saveXml, &QAction::triggered, this, [this]() { saveToFile("xml"); });
    
    // Add actions to menu
    m_saveMenu->addAction(saveJson);
    m_saveMenu->addAction(saveXml);
    
    // Create the save button
    m_saveButton = new QToolButton();
    m_saveButton->setText("Save");
    m_saveButton->setIcon(QIcon(":assets/icons/save.png"));
    m_saveButton->setToolTip("Save library to file. Supported formats: JSON, XML");
    m_saveButton->setMenu(m_saveMenu);
    m_saveButton->setPopupMode(QToolButton::InstantPopup);
    
    // Ensure the button's icon is also 28px
    m_saveButton->setIconSize(QSize(28, 28));
}
void LibraryWindow::createImportButton() {
    m_importButton = new QToolButton();
    m_importButton->setText("Import");
    m_importButton->setIcon(QIcon(":assets/icons/import.png"));
    m_importButton->setToolTip("Import content from file");
}

QListWidget* LibraryWindow::createFilterList(const QStringList& options) {
    auto* list = new QListWidget();
    list->setSelectionMode(QAbstractItemView::NoSelection);
    
    for (const QString& option : options) {
        QListWidgetItem* item = new QListWidgetItem(option, list);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }
    
    return list;
}

void LibraryWindow::updateContentDisplay() {
    m_contentModel->refreshData();
    updateContentPreviews();
    updateFilterCounter();
}

void LibraryWindow::showContentDetails(const QModelIndex &index) {
    if (!index.isValid())
        return;
    
    // Get the content using the proxy model
    QModelIndex sourceIndex = m_proxyModel->mapToSource(index);
    Content* content = m_contentModel->getContent(sourceIndex.row());
    
    if (content) {
        m_detailWindow->setContent(content);
        m_rightPanel->setCurrentIndex(1); // Show detail view
    }
}

void LibraryWindow::hideDetailView() {
    m_rightPanel->setCurrentIndex(0); // Show main view
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

void LibraryWindow::editContent(Content* content) {
    if (!content)
        return;
    
    ContentEditWindow editWindow(content, this);
    
    if (editWindow.exec() == QDialog::Accepted) {
        // After editing, update if it's a new content or existing
        auto& library = ScienceFiction_Library::getInstance();
        
        // Check if this is a new content or existing one
        bool isNew = true;
        for (const auto& existingContent : library.getContentList()) {
            if (existingContent.get() == content) {
                isNew = false;
                break;
            }
        }
        
        if (isNew) {
            // This is a new content, add it to the library
            library.addContent(content);
        }
        
        // Update the UI
        updateContentDisplay();
        emit contentDataChanged();
    } else if (content) {
        // If it's a new content that was canceled, we need to delete it
        bool isNew = true;
        auto& library = ScienceFiction_Library::getInstance();
        for (const auto& existingContent : library.getContentList()) {
            if (existingContent.get() == content) {
                isNew = false;
                break;
            }
        }
        
        if (isNew) {
            delete content;
        }
    }
}

void LibraryWindow::applyQuickFilter(int index) {
    // Quick filter from combo box or similar
    // Implement if needed
}

void LibraryWindow::applySearchFilter(const QString &text) {
    if (m_proxyModel) {
        m_proxyModel->setTitleFilter(text);
        updateContentPreviews();
        updateFilterCounter();
    }
}

void LibraryWindow::delayedSearch() {
    // Reset the timer each time text changes
    m_searchTimer->start();
}

void LibraryWindow::updateFilterCounter() {
    int count = m_proxyModel->rowCount();
    m_filterCounter->setText(QString("%1 item%2").arg(count).arg(count == 1 ? "" : "s"));
}

void LibraryWindow::clearSearch() {
    m_searchBar->clear();
    m_clearSearchButton->hide();
    applySearchFilter("");
}

void LibraryWindow::updateContentPreviews() {
    // Clear existing layout first (except for no results label)
    QLayoutItem* item;
    while ((item = m_previewLayout->takeAt(0)) != nullptr) {
        if (item->widget() != m_noResultsLabel) {
            delete item->widget();
        }
        delete item;
    }
    
    // Add the no results label back
    m_previewLayout->addWidget(m_noResultsLabel, 0, 0, 1, 6);
    
    // Get filtered content count
    int count = m_proxyModel->rowCount();
    
    // Show or hide the no results label
    m_noResultsLabel->setVisible(count == 0);
    
    if (count == 0) {
        return; // No need to create cards
    }
    
    // Create cards for visible content
    const int columns = 5; // Number of cards per row
    int row = 0, col = 0;
    
    for (int i = 0; i < count; ++i) {
        QModelIndex proxyIndex = m_proxyModel->index(i, 0);
        if (!proxyIndex.isValid()) continue;
        
        QModelIndex sourceIndex = m_proxyModel->mapToSource(proxyIndex);
        Content* content = m_contentModel->getContent(sourceIndex.row());
        
        if (content) {
            QWidget* card = createContentPreviewCard(content);
            if (card) {
                m_previewLayout->addWidget(card, row, col);
                
                // Update grid position
                col++;
                if (col >= columns) {
                    col = 0;
                    row++;
                }
            }
        }
    }
}

QWidget* LibraryWindow::createContentPreviewCard(Content* content) {
    if (!content) return nullptr;
    
    // Create a card widget with a nice border
    auto* card = new QWidget();
    card->setObjectName("ContentCard");
    card->setStyleSheet("QWidget#ContentCard { border: 1px solid #ccc; border-radius: 5px; background-color: transparent; }");
    card->setCursor(Qt::PointingHandCursor);
    
    // Create layout for the card
    auto* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(8, 8, 8, 8);
    
    // Add cover image (using a label with colored background as placeholder)
    auto* coverLabel = new QLabel();
    coverLabel->setFixedSize(180, 240);
    coverLabel->setAlignment(Qt::AlignCenter);
    coverLabel->setStyleSheet("background-color: transparent");
    
    // Get cover image path
    auto coverPath = QString::fromStdString(content->getImage());
    if (!coverPath.isEmpty() && QFile::exists(coverPath)) {
        coverLabel->setPixmap(QPixmap(coverPath).scaled(180, 240, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        // Display placeholder with title text
        coverLabel->setPixmap(QPixmap(
            ":assets/icons/no-image.png"
        ));
    }
    
    // Content details
    auto* titleLabel = new QLabel(QString::fromStdString(content->getTitle()));
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    
    auto* typeLabel = new QLabel(QString::fromStdString(content->getType()));
    typeLabel->setAlignment(Qt::AlignCenter);
    typeLabel->setStyleSheet("background-color: transparent");
    
    auto* genreLabel = new QLabel(QString::fromStdString(content->getSubgenreString()));
    genreLabel->setAlignment(Qt::AlignCenter);
    genreLabel->setStyleSheet("background-color: transparent");
    
    // Add year label
    auto* yearLabel = new QLabel(QString::number(content->getYear()));
    yearLabel->setAlignment(Qt::AlignCenter);
    
    // Watch/Star indicator
    auto* statusLayout = new QHBoxLayout();
    statusLayout->setAlignment(Qt::AlignCenter);
    
    if (content->getWatched()) {
        auto* watchedLabel = new QLabel("✓ Watched");
        watchedLabel->setStyleSheet("color: green;");
        statusLayout->addWidget(watchedLabel);
    }
    
    if (content->getStarred()) {
        auto* starredLabel = new QLabel("★ Starred");
        starredLabel->setStyleSheet("color: orange;");
        statusLayout->addWidget(starredLabel);
    }
    
    // Add all elements to card
    cardLayout->addWidget(coverLabel);
    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(typeLabel);
    cardLayout->addWidget(genreLabel);
    cardLayout->addWidget(yearLabel);
    cardLayout->addLayout(statusLayout);
    
    // Add click handler to the card
    card->installEventFilter(this);
    card->setProperty("content_ptr", QVariant::fromValue(content));
    
    // Connect to click handler
   /* connect(card, &QWidget::mouseDoubleClickEvent, [this, content](QMouseEvent*) {
        if (content) {
            m_detailWindow->setContent(content);
            m_rightPanel->setCurrentIndex(1); // Show detail view
        }
    });*/
    
    return card;
}

void LibraryWindow::clearFilters() {
    // Clear search bar
    m_searchBar->clear();
    
    // Clear all checkboxes in the filters section
    auto checkboxes = m_filtersSection->findChildren<QCheckBox*>();
    for (QCheckBox* cb : checkboxes) {
        cb->blockSignals(true);
        cb->setChecked(false);
        cb->blockSignals(false);
    }
    
    // Reset proxy model filters
    m_proxyModel->clearFilters();
    
    // Update UI
    updateContentPreviews();
    updateFilterCounter();
}

void LibraryWindow::applyFilters() {
    if (!m_proxyModel) return;
    
    // First clear current filters
    m_proxyModel->clearFilters();
    
    // Apply search filter (keep it)
    if (!m_searchBar->text().isEmpty()) {
        m_proxyModel->setTitleFilter(m_searchBar->text());
    }
    
    // Find all checked filters
    auto checkboxes = m_filtersSection->findChildren<QCheckBox*>();
    for (QCheckBox* cb : checkboxes) {
        if (cb->isChecked()) {
            QString filterType = cb->property("filterType").toString();
            
            if (filterType == "type") {
                m_proxyModel->setTypeFilter(cb->text());
            } 
            else if (filterType == "genre") {
                int genreValue = cb->property("filterValue").toInt();
                m_proxyModel->setSubgenreFilter(static_cast<Subgenre>(genreValue));
            }
            else if (filterType == "watched") {
                m_proxyModel->setWatchedFilter(true);
            }
            else if (filterType == "starred") {
                m_proxyModel->setStarredFilter(true);
            }
        }
    }
    
    // Update display
    updateContentPreviews();
    updateFilterCounter();
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
