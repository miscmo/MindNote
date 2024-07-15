#ifndef IMGEDITOR_H
#define IMGEDITOR_H

#include <QLabel>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>

#include <Widgets/NotePanel/NoteEditor.h>
#include <Notebook/Block.h>

namespace MyNote {

class ResizableRectItem;

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

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void updateImage();
    void fitImage();

private:
    QGraphicsScene *m_pScene;
    QGraphicsPixmapItem *m_pPixmapItem;
    QMenu *m_pToolMenu;
    QPixmap m_bOriginalPixmap;
    double m_bScaleFactor;
    bool m_bIsDragging;
    Block *m_pBlock;
    ResizableRectItem *m_pResizableRectItem;
};

class ResizableRectItem : public QGraphicsRectItem {
public:
    ResizableRectItem(QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool isResizingArea(const QPointF &pos) const;

    bool resizing;
    QRectF originalRect;
    QPointF originalPos;
};

}

#endif // IMGEDITOR_H
