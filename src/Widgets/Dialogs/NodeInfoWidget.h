#ifndef NODEINFOWIDGET_H
#define NODEINFOWIDGET_H

#include <QWidget>

class QComboBox;
class QFormLayout;
class QLineEdit;

namespace MyNote {

class Node;

class NodeInfoWidget : public QWidget {
    Q_OBJECT
public:
    enum Mode {Create, Edit};

    NodeInfoWidget(QWidget *parent = nullptr);
    ~NodeInfoWidget();

    void initUi();
    void initNameLineEdit();

    void initNode(Node *parent, int index);

public slots:
    void onNameEdited(const QString &name);

private:
    QFormLayout *m_pMainLayout = nullptr;
    QComboBox *m_pNodeType = nullptr;

    QLineEdit *m_pNameLineEdit = nullptr;

    Node *m_pParentNode;
    int m_nIndex;


};

}

#endif // NODEINFOWIDGET_H
