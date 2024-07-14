#ifndef IMGEDITOR_H
#define IMGEDITOR_H

#include <QLabel>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <Widgets/NotePanel/NoteEditor.h>
#include <Notebook/Block.h>

namespace MyNote {

class ImgEditor : public QGraphicsView, public EditorInterface {
    Q_OBJECT

public:
    ImgEditor(QWidget *parent, Block *block);
    ~ImgEditor();

    virtual void init() override;

    void initUi();
    void setupSignal();

    virtual int adjustHeight() override;
    virtual int getHeight() override;

    virtual Error save() override;

private slots:
    void onZoomIn();
    void onZoomOut();
    void onAlignLeft();
    void onAlignCenter();
    void onAlignRight();

signals:
    void signalHeightChanged(int height);

private:
    void updateImage();

private:
    QGraphicsScene *m_pScene;
    QGraphicsPixmapItem *m_pPixmapItem;
    QMenu *m_pToolMenu;
    QPixmap m_bOriginalPixmap;
    double m_bScaleFactor;
    bool m_bIsDragging;
    Block *m_pBlock;
};

}

#endif // IMGEDITOR_H
