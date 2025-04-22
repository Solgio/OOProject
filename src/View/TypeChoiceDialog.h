#ifndef TYPECHOICEDIALOG_H
#define TYPECHOICEDIALOG_H

#include <QDialog>
#include <functional>

class Content;
class QGridLayout;

class TypeChoiceDialog : public QDialog {
    Q_OBJECT

public:
    using ContentFactory = std::function<Content*()>;
    explicit TypeChoiceDialog(QWidget *parent = nullptr);
    
    Content* createSelectedContent() const;

private:
    void addContentType(QGridLayout *layout, const QString &label, 
                       const QString &iconPath, ContentFactory factory, int row, int col);

    ContentFactory m_selectedFactory;
};

#endif