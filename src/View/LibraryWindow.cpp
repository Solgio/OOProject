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
using std::underlying_type_t;
using SortRole = ContentModel::SortRole;

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
    if (event->type() == QEvent::MouseButtonDblClick) {
        if (obj->property("content_ptr").isValid()) {
            Content* content = obj->property("content_ptr").value<Content*>();
            if (content) {
                m_detailWindow->setContent(content);
                m_rightPanel->setCurrentIndex(1); // Show detail view
                return true;
            }
        }
    } 
    else if (event->type() == QEvent::MouseButtonPress) {
        // Handle single click for selection
        QWidget* widget = qobject_cast<QWidget*>(obj);
        if (widget && widget->objectName() == "ContentCard") {
            Content* content = obj->property("content_ptr").value<Content*>();
            if (content) {
                // If this card is already selected, deselect it
                if (m_selectedCard == widget) {
                    // Deselect - reset to original style
                    if (content->getStarred()) {
                        widget->setStyleSheet("QWidget#ContentCard { border: 2px solid #FFD700; border-radius: 5px; background-color: transparent; }");
                    } else {
                        widget->setStyleSheet("QWidget#ContentCard { border: 1px solid #ccc; border-radius: 5px; background-color: transparent; }");
                    }
                    m_selectedCard = nullptr;
                } else {
                    // Deselect previous card if any
                    if (m_selectedCard) {
                        // Find the content of the previously selected card
                        Content* prevContent = m_selectedCard->property("content_ptr").value<Content*>();
                        if (prevContent) {
                            if (prevContent->getStarred()) {
                                m_selectedCard->setStyleSheet("QWidget#ContentCard { border: 2px solid #FFD700; border-radius: 5px; background-color: transparent; }");
                            } else {
                                m_selectedCard->setStyleSheet("QWidget#ContentCard { border: 1px solid #ccc; border-radius: 5px; background-color: transparent; }");
                            }
                        }
                    }
                    
                    // Select this card
                    widget->setStyleSheet("QWidget#ContentCard { border: 2px solid #00FF00; border-radius: 5px; background-color: transparent; }");
                    m_selectedCard = widget;
                }
                return true;
            }
        }
    }
    
    return QMainWindow::eventFilter(obj, event);
}

void LibraryWindow::setupUI() {
    setWindowTitle("Science Fiction Library Manager");
    resize(1920, 1080);

    // Main structure
    m_splitter = new QSplitter(Qt::Horizontal);
    m_toolBar = addToolBar("Main Toolbar");
    m_toolBar->setIconSize(QSize(28, 28));

    // Left panel (now contains search, sorting, and filters)
    auto *leftPanel = new QWidget();
    auto *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(5, 5, 5, 5);
    leftLayout->setSpacing(10);
    
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
    
    // Create scroll area for filters
    auto* filtersScrollArea = new QScrollArea();
    filtersScrollArea->setWidgetResizable(true);
    filtersScrollArea->setWidget(m_filtersSection);
    filtersScrollArea->setFrameShape(QFrame::NoFrame);
    filtersScrollArea->setMinimumHeight(750); // Ensure reasonable minimum height
    filtersScrollArea->setMaximumHeight(900); // Prevent it from taking too much space
    
    // Setup sorting controls
    setupSortingControls();
    
    leftLayout->addWidget(searchContainer);
    leftLayout->addWidget(m_filtersToggleBtn);
    leftLayout->addWidget(filtersScrollArea); // Add scroll area instead of direct widget
    
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
    
    // Initially hide the filters scroll area
    filtersScrollArea->setVisible(false);
    // Update the toggle button to control the scroll area visibility
    connect(m_filtersToggleBtn, &QToolButton::clicked, [filtersScrollArea, this](bool checked) {
        filtersScrollArea->setVisible(checked);
        this->toggleFiltersSection();
    });
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
    m_sortingComboBox->addItem("Title", static_cast<underlying_type_t<SortRole>>(SortRole::Title));
    m_sortingComboBox->addItem("Release Date", static_cast<underlying_type_t<SortRole>>(SortRole::ReleaseDate));
    m_sortingComboBox->addItem("Rating", static_cast<underlying_type_t<SortRole>>(SortRole::Rating));
    m_sortingComboBox->addItem("Creator", static_cast<underlying_type_t<SortRole>>(SortRole::Creator));
    m_sortingComboBox->addItem("Type", static_cast<underlying_type_t<SortRole>>(SortRole::Type));
    
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
    m_filtersSection = new QWidget();
    auto* filtersLayout = new QVBoxLayout(m_filtersSection);
    filtersLayout->setContentsMargins(5, 5, 5, 5);
    filtersLayout->setSpacing(8);

    // Define checkbox style for highlighting
    QString checkboxStyle = 
        "QCheckBox:checked {"
        "   border: 2px solid rgb(15, 228, 61);"
        "   border-radius: 3px;"
        "   padding: 2px;"
        "}"
        "QCheckBox:hover {"
        "   background-color:rgb(85, 87, 86);"
        "}"
        "QCheckBox:checked:hover {"
        "   background-color:rgb(0, 110, 59);"
        "}";

    // Create dropdown buttons for each filter type
    auto createDropdownSection = [this, checkboxStyle](const QString& title, const QStringList& items, const QString& filterType) {
        auto* dropdownBtn = new QToolButton();
        dropdownBtn->setText(title);
        dropdownBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        dropdownBtn->setArrowType(Qt::RightArrow);
        dropdownBtn->setCheckable(true);
        dropdownBtn->setChecked(false);
        dropdownBtn->setStyleSheet("QToolButton {"
        "   border: none;"
        "   background: transparent;"
        "   text-align: left;"
        "   padding: 5px;"
        "   color: palette(window-text);"
        "}"
        "QToolButton:hover {"
        "   background: rgba(128, 128, 128, 30);"  // Slight hover effect
        "}");

        auto* contentWidget = new QWidget();
        contentWidget->setVisible(false);
        auto* contentLayout = new QVBoxLayout(contentWidget);
        contentLayout->setContentsMargins(15, 5, 5, 5);
        contentLayout->setSpacing(5);

        for (const auto& item : items) {
            QCheckBox* cb = new QCheckBox(item);
            cb->setProperty("filterType", filterType);
            cb->setProperty("filterValue", item);
            cb->setStyleSheet(checkboxStyle);
            connect(cb, &QCheckBox::checkStateChanged, this, &LibraryWindow::applyFilters);
            contentLayout->addWidget(cb);
        }

        connect(dropdownBtn, &QToolButton::toggled, [dropdownBtn, contentWidget](bool checked) {
            contentWidget->setVisible(checked);
            dropdownBtn->setArrowType(checked ? Qt::DownArrow : Qt::RightArrow);
        });

        return std::make_pair(dropdownBtn, contentWidget);
    };

    // Type filter section
    auto [typeBtn, typeContent] = createDropdownSection("Content Types", 
        {"Book", "Comic", "Film", "Serie", "VideoGame"}, "type");
    filtersLayout->addWidget(typeBtn);
    filtersLayout->addWidget(typeContent);

    // Genre filter section
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
    QStringList genres;
    for (auto it = genreMap.begin(); it != genreMap.end(); ++it) {
        genres << it.value();
    }

    auto [genreBtn, genreContent] = createDropdownSection("Genres", genres, "genre");
    filtersLayout->addWidget(genreBtn);
    filtersLayout->addWidget(genreContent);

    // Status filters
    auto* statusBtn = new QToolButton();
    statusBtn->setText("Status");
    statusBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    statusBtn->setArrowType(Qt::RightArrow);
    statusBtn->setCheckable(true);
    statusBtn->setChecked(false);
    statusBtn->setStyleSheet(        "QToolButton {"
        "   border: none;"
        "   background: transparent;"
        "   text-align: left;"
        "   padding: 5px;"
        "   color: palette(window-text);"
        "}"
        "QToolButton:hover {"
        "   background: rgba(128, 128, 128, 30);"  // Slight hover effect
        "}");

    auto* statusContent = new QWidget();
    statusContent->setVisible(false);
    auto* statusLayout = new QVBoxLayout(statusContent);
    statusLayout->setContentsMargins(15, 5, 5, 5);
    statusLayout->setSpacing(5);

    QCheckBox* watchedCb = new QCheckBox("Watched Only");
    watchedCb->setProperty("filterType", "watched");
    watchedCb->setStyleSheet(checkboxStyle);
    connect(watchedCb, &QCheckBox::checkStateChanged, 
        [this](int state) {
            m_proxyModel->setWatchedFilter(state == Qt::Checked);
            updateFilterCounter();
            updateContentPreviews();
            updateFilterToggleButtonState();
        });
    statusLayout->addWidget(watchedCb);

    QCheckBox* starredCb = new QCheckBox("Starred Only");
    starredCb->setProperty("filterType", "starred");
    starredCb->setStyleSheet(checkboxStyle);
    connect(starredCb, &QCheckBox::checkStateChanged, 
        [this](int state) {
            m_proxyModel->setStarredFilter(state == Qt::Checked);
            updateFilterCounter();
            updateContentPreviews();
            updateFilterToggleButtonState();
        });
    statusLayout->addWidget(starredCb);

    connect(statusBtn, &QToolButton::toggled, [statusBtn, statusContent](bool checked) {
        statusContent->setVisible(checked);
        statusBtn->setArrowType(checked ? Qt::DownArrow : Qt::RightArrow);
    });

    filtersLayout->addWidget(statusBtn);
    filtersLayout->addWidget(statusContent);

    // Clear button and counter
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
    filtersLayout->addStretch();
}

void LibraryWindow::toggleFiltersSection() {
    // Apply a highlight border when filter section is visible
    if (m_filtersToggleBtn->isChecked()) {
        m_filtersSection->setStyleSheet(" padding: 4px;");
    } else {
        m_filtersSection->setStyleSheet("");
    }
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
        updateFilterToggleButtonState();
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

void LibraryWindow::updateFilterToggleButtonState() {
    // Check if there are any active filters
    bool hasActiveFilters = false;
    
    // Check search filter
    if (!m_searchBar->text().isEmpty()) {
        hasActiveFilters = true;
    }
    
    // Check checkboxes
    if (!hasActiveFilters) {
        auto checkboxes = m_filtersSection->findChildren<QCheckBox*>();
        for (QCheckBox* cb : checkboxes) {
            if (cb->isChecked()) {
                hasActiveFilters = true;
                break;
            }
        }
    }
    
    // Update the filter toggle button appearance
    if (hasActiveFilters) {
        m_filtersToggleBtn->setText("Filters (Active)");
        m_filtersToggleBtn->setStyleSheet("QToolButton { background-color:rgb(119, 6, 34); border: 1px solid rgb(15, 228, 61); }");
    } else {
        m_filtersToggleBtn->setText("Filters");
        m_filtersToggleBtn->setStyleSheet("");
    }
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

void LibraryWindow::updateContentDisplay() {
    m_contentModel->refreshData();
    updateContentPreviews();
    updateFilterCounter();
    updateFilterToggleButtonState();
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
    updateFilterToggleButtonState();
}

void LibraryWindow::updateContentPreviews() {
    // Before clearing the layout, check if we have a selected card and save its content
    Content* selectedContent = nullptr;
    if (m_selectedCard) {
        selectedContent = m_selectedCard->property("content_ptr").value<Content*>();
        m_selectedCard = nullptr; // Clear the reference as we're about to delete it
    }
    
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
    
     // When creating new cards, check if any should be selected
     for (int i = 0; i < count; ++i) {
        QModelIndex proxyIndex = m_proxyModel->index(i, 0);
        if (!proxyIndex.isValid()) continue;
        
        QModelIndex sourceIndex = m_proxyModel->mapToSource(proxyIndex);
        Content* content = m_contentModel->getContent(sourceIndex.row());
        
        if (content) {
            QWidget* card = createContentPreviewCard(content);
            if (card) {
                // Check if this card should be selected
                if (selectedContent && content == selectedContent) {
                    card->setStyleSheet("QWidget#ContentCard { border: 2px solid #00FF00; border-radius: 5px; background-color: transparent; }");
                    m_selectedCard = card;
                }
                
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
    
    // Apply yellow border for starred content, or check if this card should be selected
    if (m_selectedCard && m_selectedCard->property("content_ptr").value<Content*>() == content) {
        // This is the selected card
        card->setStyleSheet("QWidget#ContentCard { border: 2px solid #00FF00; border-radius: 5px; background-color: transparent; }");
    } else if (content->getStarred()) {
        card->setStyleSheet("QWidget#ContentCard { border: 2px solid #FFD700; border-radius: 5px; background-color: transparent; }");
    } else {
        card->setStyleSheet("QWidget#ContentCard { border: 1px solid #ccc; border-radius: 5px; background-color: transparent; }");
    }
    
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
    
    // Reset the filter toggle button
    m_filtersToggleBtn->setText("Filters");
    m_filtersToggleBtn->setStyleSheet("");
    
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
        bool hasActiveFilters = false;
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

    if (hasActiveFilters) {
        m_filtersToggleBtn->setText("Filters (Active)");
        m_filtersToggleBtn->setStyleSheet("QToolButton { background-color: #e0f0ff; border: 1px solid #99ccff; }");
    } else {
        m_filtersToggleBtn->setText("Filters");
        m_filtersToggleBtn->setStyleSheet("");
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
