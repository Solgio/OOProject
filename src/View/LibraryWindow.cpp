// LibraryWindow.cpp
#include "LibraryWindow.h"
#include <QDebug>
#include <QLabel>

LibraryWindow::LibraryWindow(QWidget *parent) 
    : QMainWindow(parent) {
    // Configurazione della finestra principale
    setWindowTitle("Libreria di Contenuti");
    resize(800, 600);

    // Inizializzazione della libreria
    // (eventualmente caricare dati qui)

    // Creazione degli elementi dell'interfaccia
    createToolBar();
    createSidePanel();
    createContentArea();
    setupMainLayout();

    // Connessioni dei segnali
    connectActions();

    // Aggiorna la visualizzazione iniziale
    refreshContentDisplay();
}

LibraryWindow::~LibraryWindow() {
    // Pulizia se necessaria
}

void LibraryWindow::createToolBar() {
    // Barra degli strumenti in alto
    QToolBar *toolBar = addToolBar("Strumenti");

    // Pulsanti per importare file
    m_importAction = new QAction(QIcon(":/icons/import.png"), "Importa", this);
    toolBar->addAction(m_importAction);

    // Pulsanti per salvare
    m_saveXmlAction = new QAction(QIcon(":/icons/xml.png"), "Salva come XML", this);
    m_saveJsonAction = new QAction(QIcon(":/icons/json.png"), "Salva come JSON", this);
    
    toolBar->addSeparator();
    toolBar->addAction(m_saveXmlAction);
    toolBar->addAction(m_saveJsonAction);
}

void LibraryWindow::createSidePanel() {
    // Pannello laterale sinistro
    m_sidePanel = new QWidget();
    QVBoxLayout *sideLayout = new QVBoxLayout(m_sidePanel);

    // Barra di ricerca
    m_searchBar = new QLineEdit();
    m_searchBar->setPlaceholderText("Cerca contenuti...");
    m_searchBar->setClearButtonEnabled(true);
    sideLayout->addWidget(m_searchBar);

    // Filtri
    m_filterCombo = new QComboBox();
    m_filterCombo->addItem("Tutti i contenuti");
    m_filterCombo->addItem("Visti");
    m_filterCombo->addItem("Non visti");
    m_filterCombo->addItem("Preferiti");
    m_filterCombo->addItem("Film");
    m_filterCombo->addItem("Serie TV");
    m_filterCombo->addItem("Libri");
    sideLayout->addWidget(m_filterCombo);

    // Lista dei contenuti
    m_contentList = new QListWidget();
    m_contentList->setSelectionMode(QAbstractItemView::SingleSelection);
    sideLayout->addWidget(m_contentList);

    m_sidePanel->setLayout(sideLayout);
    m_sidePanel->setMinimumWidth(200);
}

void LibraryWindow::createContentArea() {
    // Area principale del contenuto
    m_contentWidget = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(m_contentWidget);

    // Etichetta per i dettagli del contenuto
    m_contentDetails = new QLabel("Nessun contenuto selezionato");
    m_contentDetails->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_contentDetails->setWordWrap(true);
    contentLayout->addWidget(m_contentDetails);

    m_contentWidget->setLayout(contentLayout);
}

void LibraryWindow::setupMainLayout() {
    // Layout principale con splitter
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(m_sidePanel);
    splitter->addWidget(m_contentWidget);

    // Imposta le proporzioni iniziali
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);

    setCentralWidget(splitter);
}

void LibraryWindow::connectActions() {
    // Connessioni dei pulsanti
    connect(m_importAction, &QAction::triggered, this, &LibraryWindow::importContent);
    connect(m_saveXmlAction, &QAction::triggered, this, &LibraryWindow::saveAsXml);
    connect(m_saveJsonAction, &QAction::triggered, this, &LibraryWindow::saveAsJson);
    
    // Connessioni per la ricerca e filtri
    connect(m_searchBar, &QLineEdit::textChanged, this, &LibraryWindow::searchContent);
    connect(m_filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &LibraryWindow::filterContent);
    
    // Connessione per la selezione del contenuto
    connect(m_contentList, &QListWidget::itemSelectionChanged, 
            this, &LibraryWindow::updateContentList);
}

void LibraryWindow::refreshContentDisplay() {
    m_contentList->clear();
    
    // Mostra tutti i contenuti (o quelli filtrati)
    ScienceFiction_Library::getInstance().showAllContent();
    const auto& contents = ScienceFiction_Library::getInstance().getContentList();
    
    for (const auto& content : contents) {
        QListWidgetItem *item = new QListWidgetItem(
            QString::fromStdString(content->getTitle()), 
            m_contentList
        );
        item->setData(Qt::UserRole, QVariant(content->getId()));
    }
}

void LibraryWindow::importContent() {
    QString fileName = QFileDialog::getOpenFileName(this, "Importa contenuto", 
                                                    "", "Tutti i file (*.*)");
    if (!fileName.isEmpty()) {
        // Qui dovresti creare il contenuto appropriato in base al tipo di file
        // e aggiungerlo alla libreria con ScienceFiction_Library::getInstance().addContent()
        QMessageBox::information(this, "Importazione", "Contenuto importato: " + fileName);
        refreshContentDisplay();
    }
}

void LibraryWindow::saveAsXml() {
    QString fileName = QFileDialog::getSaveFileName(this, "Salva come XML", 
                                                    "", "File XML (*.xml)");
    if (!fileName.isEmpty()) {
        if (ScienceFiction_Library::getInstance().saveToFile(fileName.toStdString())) {
            QMessageBox::information(this, "Salvataggio", "Libreria salvata come XML: " + fileName);
        } else {
            QMessageBox::warning(this, "Errore", "Salvataggio fallito");
        }
    }
}

void LibraryWindow::saveAsJson() {
    QString fileName = QFileDialog::getSaveFileName(this, "Salva come JSON", 
                                                    "", "File JSON (*.json)");
    if (!fileName.isEmpty()) {
        if (ScienceFiction_Library::getInstance().saveToFile(fileName.toStdString())) {
            QMessageBox::information(this, "Salvataggio", "Libreria salvata come JSON: " + fileName);
        } else {
            QMessageBox::warning(this, "Errore", "Salvataggio fallito");
        }
    }
}

void LibraryWindow::searchContent(const QString &text) {
    if (text.isEmpty()) {
        refreshContentDisplay();
    } else {
        ScienceFiction_Library::getInstance().filterContent(text.toStdString());
        refreshContentDisplay();
    }
}

void LibraryWindow::filterContent(int index) {
    switch(index) {
        case 0: // Tutti i contenuti
            ScienceFiction_Library::getInstance().showAllContent();
            break;
        case 1: // Visti
            ScienceFiction_Library::getInstance().watchedOrNot(true);
            break;
        case 2: // Non visti
            ScienceFiction_Library::getInstance().watchedOrNot(false);
            break;
        case 3: // Preferiti
            ScienceFiction_Library::getInstance().starredOrNot(true);
            break;
        /*case 4: 
            ScienceFiction_Library::getInstance().filteredListbyGen(static_cast<unsigned int>(Subgenre::Film));
            break;
        case 5: 
            ScienceFiction_Library::getInstance().filteredListbyGen(static_cast<unsigned int>(Subgenre::SerieTV));
            break;
        case 6: 
            ScienceFiction_Library::getInstance().filteredListbyGen(static_cast<unsigned int>(Subgenre::Libri));
            break;*/
    }
    refreshContentDisplay();
}

void LibraryWindow::updateContentList() {
    QList<QListWidgetItem*> selectedItems = m_contentList->selectedItems();
    if (selectedItems.isEmpty()) {
        m_contentDetails->setText("Nessun contenuto selezionato");
        return;
    }
    
    QListWidgetItem* selectedItem = selectedItems.first();
    unsigned int id = selectedItem->data(Qt::UserRole).toUInt();
    Content* content = ScienceFiction_Library::getInstance().searchId(id);
    
    if (content) {
        QString details = QString("<b>Titolo:</b> %1<br>"
                                "<b>Anno:</b> %2<br>"
                                "<b>Genere:</b> %3<br>"
                                "<b>Visto:</b> %4<br>"
                                "<b>Preferito:</b> %5")
                            .arg(QString::fromStdString(content->getTitle()))
                            .arg(content->getYear())
                            .arg(QString::fromStdString(content->getSubgenreString()))
                            .arg(content->getWatched() ? "Sì" : "No")
                            .arg(content->getStarred() ? "Sì" : "No");
        
        m_contentDetails->setText(details);
    }
}