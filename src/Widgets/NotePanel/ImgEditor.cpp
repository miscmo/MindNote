#include "ImgEditor.h"

#include <QVBoxLayout>
#include <QPixmap>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>

using namespace MyNote;

ImgEditor::ImgEditor(QWidget *parent, Block *block)
    : QGraphicsView(parent)
    , m_pScene(nullptr)
    , m_pPixmapItem(nullptr)
    , m_pToolMenu(nullptr)
    , m_bScaleFactor(1.0)
    , m_bIsDragging(false)
    , m_pBlock(block) {
    //setAttribute(Qt::WA_StyledBackground);
    //setStyleSheet("background-color: blue;");
}

ImgEditor::~ImgEditor() {
}

void ImgEditor::init() {
    initUi();
    setupSignal();
}

void ImgEditor::initUi() {

    if (m_pBlock == nullptr) {
        return ;
    }

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setContentsMargins(0, 0, 0, 0);
    setFrameStyle(QFrame::NoFrame);
    setAlignment(Qt::AlignTop);

//    setStyleSheet("QGraphicsView { border: none; }");

    m_pScene = new QGraphicsScene(this);
    setScene(m_pScene);
    setDragMode(QGraphicsView::ScrollHandDrag);


    QPixmap pixmap(m_pBlock->getLocalFilePath());
    m_pPixmapItem = new ResizeablePixmapItem(pixmap);

    m_pScene->addItem(m_pPixmapItem);
    m_pPixmapItem->setTransformOriginPoint(pixmap.rect().center());
    m_pScene->setSceneRect(pixmap.rect());

    setFixedHeight(pixmap.height()+20);

    // m_pResizableRectItem = new ResizableRectItem();
    // m_pResizableRectItem->setRect(m_pPixmapItem->boundingRect());
    // m_pResizableRectItem->setPen(QPen(Qt::white, 2, Qt::DashLine));
    // m_pResizableRectItem->setBrush(Qt::NoBrush);
    // m_pResizableRectItem->setVisible(false);
    // m_pScene->addItem(m_pResizableRectItem);

    //fitInView(m_pPixmapItem, Qt::KeepAspectRatio);

    // m_pImgLabel = new QLabel(this);
    // m_bOriginalPixmap.load(m_pBlock->getContent());
    // m_pImgLabel->setPixmap(m_bOriginalPixmap);
    // m_pImgLabel->setScaledContents(true);
    // m_pImgLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // m_pImgLabel->setAlignment(Qt::AlignCenter);
    // m_pImgLabel->resize(m_bOriginalPixmap.size());

    // QVBoxLayout *layout = new QVBoxLayout(this);
    // layout->addWidget(m_pImgLabel);
    // layout->setAlignment(Qt::AlignCenter);
    // setLayout(layout);

    m_pToolMenu = new QMenu(this);

    QAction *zoomInAction = new QAction(tr("Zoom In"), this);
    QAction *zoomOutAction = new QAction(tr("Zoom Out"), this);
    QAction *alignCenterAction = new QAction(tr("Align Center"), this);
    QAction *alignLeftAction = new QAction(tr("Align Left"), this);
    QAction *alignRightAction = new QAction(tr("Align Right"), this);

    connect(zoomInAction, &QAction::triggered, this, &ImgEditor::onZoomIn);
    connect(zoomOutAction, &QAction::triggered, this, &ImgEditor::onZoomOut);
    connect(alignCenterAction, &QAction::triggered, this, &ImgEditor::onAlignCenter);
    connect(alignLeftAction, &QAction::triggered, this, &ImgEditor::onAlignLeft);
    connect(alignRightAction, &QAction::triggered, this, &ImgEditor::onAlignRight);

    m_pToolMenu->addAction(zoomInAction);
    m_pToolMenu->addAction(zoomOutAction);
    m_pToolMenu->addAction(alignCenterAction);
    m_pToolMenu->addAction(alignLeftAction);
    m_pToolMenu->addAction(alignRightAction);

    adjustHeight();
}

void ImgEditor::setupSignal() {

}

int ImgEditor::adjustHeight() {
    // QPixmap scaledPixmap = m_bOriginalPixmap.scaled(m_bOriginalPixmap.size() * m_bScaleFactor, Qt::KeepAspectRatio);
    // m_pImgLabel->setPixmap(scaledPixmap);
    // m_pImgLabel->adjustSize();

    // int newHeight = scaledPixmap.height();

    // int currentHeight = height();

    // if (currentHeight != newHeight) {
    //     setFixedHeight(newHeight);
    //     emit signalHeightChanged(newHeight);
    // }

    // return newHeight;
}

int ImgEditor::getHeight() {
    return height();
}

void ImgEditor::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    //fitImage();
    fitInView(m_pPixmapItem, Qt::KeepAspectRatio);
}

void ImgEditor::mousePressEvent(QMouseEvent *event) {
    QGraphicsView::mousePressEvent(event);
    // if (itemAt(event->pos())) {
    //     m_pResizableRectItem->setVisible(true);
    //     //m_pToolMenu->exec(mapToGlobal(event->pos()));
    // } else {
    //     m_pResizableRectItem->setVisible(false);
    // }
}

void ImgEditor::updateImage() {
    // QPixmap scaledPixmap = m_bOriginalPixmap.scaled(m_bOriginalPixmap.size() * m_bScaleFactor, Qt::KeepAspectRatio);
    // m_pImgLabel->setPixmap(scaledPixmap);
    // m_pImgLabel->adjustSize();
    // adjustSize();
    // //imageRect = imageLabel->geometry();
}

void ImgEditor::fitImage() {
    if (m_pPixmapItem) {
        QPixmap pixmap = m_pPixmapItem->pixmap();
        if (!pixmap.isNull()) {
            QSize viewSize = size();
            QSize pixmapSize = pixmap.size();
            pixmapSize.scale(viewSize, Qt::KeepAspectRatio);
            // High-quality scaling
            QImage image = pixmap.toImage();
            QImage scaledImage = image.scaled(pixmapSize, Qt::KeepAspectRatio, Qt::FastTransformation);
            m_pPixmapItem->setPixmap(QPixmap::fromImage(scaledImage));
            m_pScene->setSceneRect(m_pPixmapItem->boundingRect());
        }
    }
}

Error ImgEditor::save() {
    return Error::success();
}

void ImgEditor::onZoomIn() {
    scale(1.2, 1.2);
}

void ImgEditor::onZoomOut() {
    scale(0.8, 0.8);

}


void ImgEditor::onAlignLeft() {

}

void ImgEditor::onAlignCenter() {

}

void ImgEditor::onAlignRight() {

}

ResizableRectItem::ResizableRectItem(QGraphicsItem *parent)
    : QGraphicsRectItem(parent), resizing(false) {
    setFlags(ItemIsSelectable | ItemIsMovable);
}

void ResizableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (isResizingArea(event->pos())) {
        resizing = true;
        originalRect = rect();
        originalPos = event->pos();
    } else {
        QGraphicsRectItem::mousePressEvent(event);
    }
}

void ResizableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (resizing) {
        QPointF delta = event->pos() - originalPos;
        QRectF newRect = originalRect;
        newRect.setBottomRight(newRect.bottomRight() + delta);
        setRect(newRect);
    } else {
        QGraphicsRectItem::mouseMoveEvent(event);
    }
}

void ResizableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (resizing) {
        resizing = false;
    } else {
        QGraphicsRectItem::mouseReleaseEvent(event);
    }
}

bool ResizableRectItem::isResizingArea(const QPointF &pos) const {
    QRectF resizeArea = rect().adjusted(rect().width() - 10, rect().height() - 10, 0, 0);
    return resizeArea.contains(pos);
}

ResizeablePixmapItem::ResizeablePixmapItem(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , m_bResizing(false)
    , m_pLeftUpResizeRect(nullptr)
    , m_pRightDownResizeRect(nullptr)
    , m_pLeftDownResizeRect(nullptr)
    , m_pRightUpResizeRect(nullptr) {

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setZValue(1);
}

ResizeablePixmapItem::ResizeablePixmapItem(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , m_bResizing(false)
    , m_bOriginalPixmap(pixmap)
    , m_pLeftUpResizeRect(nullptr)
    , m_pRightDownResizeRect(nullptr)
    , m_pLeftDownResizeRect(nullptr)
    , m_pRightUpResizeRect(nullptr) {

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setZValue(1);
    setPixmap(m_bOriginalPixmap);

}

ResizeablePixmapItem::~ResizeablePixmapItem() {

}

void ResizeablePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (isResizingArea(event->pos())) {
        m_bResizing = true;
        m_bResizeStartPos = event->pos();
    } else {
        QGraphicsPixmapItem::mousePressEvent(event);
    }
}

void ResizeablePixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_bResizing) {
        QPointF delta = event->pos() - m_bResizeStartPos;
        int newWidth = m_bOriginalPixmap.width() + delta.x();
        int newHeight = m_bOriginalPixmap.height() + delta.y();

        if (newWidth > 1 && newHeight > 1) {
            QPixmap newPixmap = m_bOriginalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            setPixmap(newPixmap);
            setOffset(-newPixmap.width()/2, -newPixmap.height()/2);  // 保持图片居中
            updateSceneSize();
            update();
        }
    } else if (isResizingArea(event->pos())) {
        setCursor(Qt::SizeFDiagCursor);
    }
    else {
        QGraphicsPixmapItem::mouseMoveEvent(event);
    }
}

void ResizeablePixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_bResizing) {
        m_bResizing = false;
        setCursor(Qt::ArrowCursor);
    } else {
        QGraphicsPixmapItem::mouseReleaseEvent(event);
    }
}

void ResizeablePixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);
    if (isSelected()) {
        QPen pen(Qt::DashLine);
        pen.setColor(Qt::red);
        painter->setPen(pen);
        //painter->drawRect(boundingRect());

        // Draw resize handle
        m_pLeftUpResizeRect = new QRectF(boundingRect().left(),
                          boundingRect().top(),
                          m_nResizeAreaWidth, m_nResizeAreaWidth);

        m_pLeftDownResizeRect = new QRectF(boundingRect().left(),
                          boundingRect().bottom() - m_nResizeAreaWidth,
                          m_nResizeAreaWidth, m_nResizeAreaWidth);

        m_pRightUpResizeRect = new QRectF(boundingRect().right() - m_nResizeAreaWidth,
                          boundingRect().top(),
                          m_nResizeAreaWidth, m_nResizeAreaWidth);

        m_pRightDownResizeRect = new QRectF(boundingRect().right() - m_nResizeAreaWidth,
                          boundingRect().bottom() - m_nResizeAreaWidth,
                          m_nResizeAreaWidth, m_nResizeAreaWidth);

        painter->fillRect(*m_pLeftDownResizeRect, Qt::blue);
        painter->fillRect(*m_pRightUpResizeRect, Qt::blue);
        painter->fillRect(*m_pLeftUpResizeRect, Qt::blue);
        painter->fillRect(*m_pRightDownResizeRect, Qt::blue);
    }
}

bool ResizeablePixmapItem::isResizingArea(const QPointF &pos) const {
    if (m_pLeftDownResizeRect != nullptr) {
        if (m_pLeftDownResizeRect->contains(pos)) {
            return true;
        }
    }

    if (m_pRightUpResizeRect != nullptr) {
        if (m_pRightUpResizeRect->contains(pos)) {
            return true;
        }
    }

    if (m_pLeftUpResizeRect != nullptr) {
        if (m_pLeftUpResizeRect->contains(pos)) {
            return true;
        }
    }

    if (m_pRightDownResizeRect != nullptr) {
        if (m_pRightDownResizeRect->contains(pos)) {
            return true;
        }
    }

    return false;
}

void ResizeablePixmapItem::updateSceneSize() {
    if (scene()) {
        QRectF newRect = boundingRect();
        scene()->setSceneRect(newRect.adjusted(-20, -20, 20, 20));
    }
}
