#include <QStandardItemModel>
#include "VideoEditWindow.h"
#include "../../Model/lib/ScienceFictionLibrary.h"

VideoEditWindow::VideoEditWindow():
    MultimediaEditWindow(),
    durationEdit(new QTextEdit()),
    prequelEdit(new MyComboBox()),
    sequelEdit(new MyComboBox())
{
    setUp();
}

VideoEditWindow::VideoEditWindow(Content *content):
    MultimediaEditWindow(content),
    durationEdit(new QTextEdit()),
    prequelEdit(new MyComboBox()),
    sequelEdit(new MyComboBox())
{
    setUpSequelPrequelBox();
    setUp();
}


VideoEditWindow::VideoEditWindow(Video *video):
    MultimediaEditWindow(video),
    durationEdit(new QTextEdit(QString::number(video->getDuration()))),
    prequelEdit(new MyComboBox()),
    sequelEdit(new MyComboBox()),
    videoPtr(video)
{
    setUpSequelPrequelBox();
    if(const Content* temp = library.searchId(video->getPrequel()); temp){
        prequelEdit->setCurrentText(QString::fromStdString(temp->getTitle()));
    }else{
        prequelEdit->setCurrentIndex(0); // Se non trova il prequel del content mostra "No sequel/prequel"
    }
    if(const Content* temp = library.searchId(video->getSequel()); temp){
        sequelEdit->setCurrentText(QString::fromStdString(temp->getTitle()));
    }else{
        sequelEdit->setCurrentIndex(0); // Se non trova la inspiration del content mostra "No sequel/prequel"
    }

    setUp();
}

void VideoEditWindow::setUpSequelPrequelBox(){

    //stessa procedura di CommonEditWindow
    QStandardItemModel *model = new QStandardItemModel();

    QList<QStandardItem*> listaNomi;
    QList<QStandardItem*> listaId;

    listaNomi.append(new QStandardItem("No sequel/prequel"));
    listaId.append(new QStandardItem()); //"No sequel/prequel" non ha ID
    for(const auto &v_content : CommonEditWindow::library.getContentList()){
        if(dynamic_cast<Video*>(v_content.get())){
            listaNomi.append(new QStandardItem(QString::fromStdString(v_content->getTitle())));
            listaId.append(new QStandardItem(QString::number(v_content->getId())));
        }
    }

    model->appendColumn(listaNomi);
    model->appendColumn(listaId);

    prequelEdit->setModel(model);
    sequelEdit->setModel(model);
    prequelEdit->setEditable(false); //per modifica dell'indice con il testo
    sequelEdit->setEditable(false);
}

void VideoEditWindow::setUp(){

    QVBoxLayout *mainLayout = CommonEditWindow::getLayout();

    //Duration
    auto *durationLayout = new QFormLayout();
    durationLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Duration (in minutes) : ")), durationEdit);
    mainLayout->addLayout(durationLayout);

    //Prequel ID
    auto *preqLayout = new QFormLayout();
    preqLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Prequel ID : ")), prequelEdit);
    mainLayout->addLayout(preqLayout);

    //Sequel ID
    auto *seqLayout = new QFormLayout();
    seqLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Sequel ID : ")), sequelEdit);
    mainLayout->addLayout(seqLayout);
}

void VideoEditWindow::saveEdit(){
    if(videoPtr){
        MultimediaEditWindow::saveEdit();
        videoPtr->setDuration(durationEdit->toPlainText().toUInt());
        videoPtr->setPrequel(prequelEdit->model()->itemData(prequelEdit->model()->index(prequelEdit->currentIndex(), 1)).value(0).toInt());
        videoPtr->controllPrequel();
        videoPtr->setSequel(sequelEdit->model()->itemData(sequelEdit->model()->index(sequelEdit->currentIndex(), 1)).value(0).toInt());
        videoPtr->controllSequel();
    }
}
