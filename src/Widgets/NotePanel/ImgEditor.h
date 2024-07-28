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
class ResizeablePixmapItem;

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

    void adjustPixmapSize(QSize size);

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
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void updateImage();
    void fitImage();
    void createResizeHandle();
    void updateResizeHandle();
    void updateSceneSize();

private:
    QGraphicsPixmapItem *m_pPixmapItem;
    QPixmap m_bOriginalPixmap;

    QGraphicsRectItem *m_pRoundRectItem;
    QGraphicsRectItem *m_pRDResizeRect;
    bool m_bIsResizing;

    QGraphicsPixmapItem *m_pSelectedItem;
    QGraphicsRectItem *m_pResizableRectItem;
    QMenu *m_pToolMenu;
    double m_bScaleFactor;
    bool m_bIsDragging;
    Block *m_pBlock;
    QPointF m_bResizeStartPos;
    QPointF m_bStartPos;
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

class ResizeablePixmapItem : public QGraphicsPixmapItem {
public:
    ResizeablePixmapItem(QGraphicsItem *parent = nullptr);
    ResizeablePixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    ~ResizeablePixmapItem();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    bool isResizingArea(const QPointF &pos) const;
    void updateSceneSize();

    bool m_bResizing;
    QPointF m_bResizeStartPos;
    QPixmap m_bOriginalPixmap;
    QRectF *m_pLeftUpResizeRect;
    QRectF *m_pRightDownResizeRect;
    QRectF *m_pLeftDownResizeRect;
    QRectF *m_pRightUpResizeRect;

    const int m_nResizeAreaWidth = 10;

};

}

#endif // IMGEDITOR_H
