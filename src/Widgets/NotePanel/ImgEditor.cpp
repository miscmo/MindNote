#include "ImgEditor.h"

#include <QVBoxLayout>
#include <QPixmap>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QDebug>

using namespace MyNote;

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
    event->accept();

    if (isResizingArea(event->pos())) {
        m_bResizing = true;
        m_bResizeStartPos = event->pos();
    }
    QGraphicsPixmapItem::mousePressEvent(event);
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

    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void ResizeablePixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_bResizing) {
        m_bResizing = false;
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsPixmapItem::mouseReleaseEvent(event);
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

ImgEditor::ImgEditor(QWidget *parent, Block *block)
    : QGraphicsView(parent)
    , m_pPixmapItem(nullptr)
    , m_pRoundRectItem(nullptr)
    , m_pRDResizeRect(nullptr)
    , m_bIsResizing(false)
    , m_pSelectedItem(nullptr)
    , m_pToolMenu(nullptr)
    , m_bScaleFactor(1.0)
    , m_bIsDragging(false)
    , m_pBlock(block) {
    //setAttribute(Qt::WA_StyledBackground);
    //setStyleSheet("background-color: blue;");
    setMouseTracking(true);
}

ImgEditor::~ImgEditor() {
}

void ImgEditor::init() {
    initUi();
    setupSignal();
}

void ImgEditor::initUi() {

    if ( m_pBlock == nullptr
        || m_pBlock->getType() != BLOCK_TYPE_IMG
        || m_pBlock->getLocalFilePath().isEmpty() ) {
        return ;
    }

    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 设置无边框
    setContentsMargins(0, 0, 0, 0);
    setFrameStyle(QFrame::NoFrame);
    setAlignment(Qt::AlignTop);

//    setStyleSheet("QGraphicsView { border: none; }");

    setScene(new QGraphicsScene(this));
    //setDragMode(QGraphicsView::ScrollHandDrag);

    m_bOriginalPixmap = QPixmap(m_pBlock->getLocalFilePath());
    m_pPixmapItem = new QGraphicsPixmapItem();

    // 设置图片图层在最底层
    m_pPixmapItem->setZValue(0);

    // todo 设置图片的初始尺寸，从Block中读取
    // 图片的尺寸优先级：窗口大小 -> 本地临时调整 -> Block配置 -> 原图
    m_pPixmapItem->setPixmap(m_bOriginalPixmap);
    m_pPixmapItem->setFlag(QGraphicsItem::ItemIsSelectable);
    m_pPixmapItem->setTransformOriginPoint(m_bOriginalPixmap.rect().center());

    scene()->addItem(m_pPixmapItem);
    scene()->setSceneRect(m_bOriginalPixmap.rect());

    setFixedHeight(m_bOriginalPixmap.height()+20);

    // 大小调节框
    m_pRoundRectItem = new QGraphicsRectItem(m_pPixmapItem->boundingRect());
    m_pRoundRectItem->setPen(QPen(Qt::red, 2, Qt::DashLine));
    m_pRoundRectItem->setBrush(Qt::NoBrush);
    scene()->addItem(m_pRoundRectItem);
    m_pRoundRectItem->setZValue(1);
    m_pRoundRectItem->hide();

    QRectF rect = m_pRoundRectItem->boundingRect();
    QPointF bottomRight = m_pRoundRectItem->mapToScene(rect.bottomRight());

    // 右下角
    m_pRDResizeRect = new QGraphicsRectItem(0, 0, 10, 10);
    m_pRDResizeRect->setBrush(Qt::red);
    scene()->addItem(m_pRDResizeRect);
    m_pRDResizeRect->setZValue(1);
    //m_pLUResizeRect->setPos(topLeft.x() + 10, bottomRight.y() + 10);
    m_pRDResizeRect->setPos(bottomRight.x() - 10, bottomRight.y() - 10);
    m_pRDResizeRect->hide();

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
    m_pRoundRectItem->show();
    m_pRDResizeRect->show();

    if (m_pRDResizeRect->isVisible() && m_pRDResizeRect->isUnderMouse()) {
        m_bIsResizing = true;
        m_bStartPos = event->pos();
    }

    QGraphicsView::mousePressEvent(event);
    // QGraphicsItem *item = itemAt(event->pos());
    // if (item && item->type() == ResizeablePixmapItem::Type) {
    //     m_pSelectedItem = qgraphicsitem_cast<ResizeablePixmapItem *>(item);
    //     m_pResizableRectItem = new QGraphicsRectItem(0, 0, 10, 10);
    //     m_pResizableRectItem->setZValue(1);
    //     m_pResizableRectItem->setBrush(Qt::red);
    //     scene()->addItem(m_pResizableRectItem);
    //     QRectF rect = m_pSelectedItem->boundingRect();
    //     QPointF bottomRight = m_pSelectedItem->mapToScene(rect.bottomRight());
    //     m_pResizableRectItem->setPos(bottomRight.x() - 10, bottomRight.y() - 10);
    // } else {
    //     m_pSelectedItem = nullptr;
    //     if (m_pResizableRectItem) {
    //         scene()->removeItem(m_pResizableRectItem);
    //         delete m_pResizableRectItem;
    //         m_pResizableRectItem = nullptr;
    //     }
    // }

    // if (m_pResizableRectItem && m_pResizableRectItem->isUnderMouse()) {
    //     m_bIsResizing = true;
    //     m_bResizeStartPos = event->pos();
    //     m_bOriginalPixmap = m_pSelectedItem->pixmap();
    // } else {
    //     QGraphicsView::mousePressEvent(event);
    // }

}

void ImgEditor::mouseMoveEvent(QMouseEvent *event) {
    // if (m_bIsResizing && m_pSelectedItem) {
    //     QPointF delta = mapToScene(event->pos()) - mapToScene(m_bResizeStartPos.toPoint());
    //     int newWidth = m_bOriginalPixmap.width() + delta.x();
    //     int newHeight = m_bOriginalPixmap.height() + delta.y();

    //     if (newWidth > 1 && newHeight > 1) {
    //         QPixmap newPixmap = m_bOriginalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //         m_pSelectedItem->setPixmap(newPixmap);
    //         m_pSelectedItem->setOffset(-newPixmap.width()/2, -newPixmap.height()/2);  // 保持图片居中
    //         updateSceneSize();
    //         updateResizeHandle();
    //     }
    // } else {
    //     QGraphicsView::mouseMoveEvent(event);
    // }
    if (m_pRDResizeRect->isVisible() && m_pRDResizeRect->isUnderMouse()) {
        // 修改鼠标图标
        viewport()->setCursor(Qt::SizeFDiagCursor);

    } else {
        viewport()->setCursor(Qt::ArrowCursor);
    }

    if (m_bIsResizing) {
        qDebug() << "resizing" << Qt::endl;

        // 更改调节框大小和位置
        QRectF rect = m_pRoundRectItem->boundingRect();

        QPointF mousePos = event->pos();

        QPointF delta = m_bStartPos - mousePos;

        // 将鼠标位置转换为相对于图片的坐标
        //QPointF relativePos = m_pRoundRectItem->mapFromScene(mousePos);
        //QPointF originPos = m_pRoundRectItem->mapFromScene(m_bStartPos);

        //QPointF delta = mousePos - m_bStartPos;

        QPointF bottomRightPoint = rect.bottomRight();

        //rect.setBottomRight(bottomRightPoint + delta);
        //rect.setBottomRight(mousePos);
        rect.adjust(0, 0, delta.x(), delta.y());

        m_pRoundRectItem->setRect(rect);
        m_pRoundRectItem->setPos(m_pPixmapItem->pos());
        m_pRDResizeRect->setPos(rect.bottomRight() - QPointF(10, 10));
        adjustPixmapSize(rect.size().toSize());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void ImgEditor::mouseReleaseEvent(QMouseEvent *event) {
    if (m_bIsResizing) {
        m_bIsResizing = false;
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void ImgEditor::focusOutEvent(QFocusEvent *event) {
    m_pRoundRectItem->hide();
    m_pRDResizeRect->hide();

    // if (m_pResizableRectItem) {
    //     scene()->removeItem(m_pResizableRectItem);
    //     delete m_pResizableRectItem;
    //     m_pResizableRectItem = nullptr;
    // }
    QGraphicsView::focusOutEvent(event);
}

void ImgEditor::contextMenuEvent(QContextMenuEvent *event) {

    QMenu menu(this);

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

    menu.addAction(zoomInAction);
    menu.addAction(zoomOutAction);
    menu.addAction(alignCenterAction);
    menu.addAction(alignLeftAction);
    menu.addAction(alignRightAction);

    menu.exec(event->globalPos());
}

void ImgEditor::updateImage() {
    // QPixmap scaledPixmap = m_bOriginalPixmap.scaled(m_bOriginalPixmap.size() * m_bScaleFactor, Qt::KeepAspectRatio);
    // m_pImgLabel->setPixmap(scaledPixmap);
    // m_pImgLabel->adjustSize();
    // adjustSize();
    // //imageRect = imageLabel->geometry();
}

void ImgEditor::adjustPixmapSize(QSize size) {
    // 最大size 窗口大小，原图
    // 最小size 限制最小尺寸
    // todo 图片的尺寸优先级：窗口大小 -> 本地临时调整 -> Block配置 -> 原图

    QSize pixmapSize = m_bOriginalPixmap.size();
    pixmapSize.scale(size, Qt::KeepAspectRatio);

    QImage image = m_bOriginalPixmap.toImage();
    QImage scaledImage = image.scaled(pixmapSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pPixmapItem->setPixmap(QPixmap::fromImage(scaledImage));
    scene()->setSceneRect(m_pPixmapItem->boundingRect());
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
            scene()->setSceneRect(m_pPixmapItem->boundingRect());
        }
    }
}

void ImgEditor::createResizeHandle() {
    if (m_pSelectedItem) {
        m_pResizableRectItem = new QGraphicsRectItem(0, 0, 10, 10);
        m_pResizableRectItem->setZValue(1);
        m_pResizableRectItem->setBrush(Qt::red);
        scene()->addItem(m_pResizableRectItem);
        updateResizeHandle();
    }
}

void ImgEditor::updateResizeHandle() {
    if (m_pResizableRectItem && m_pSelectedItem) {
        QRectF rect = m_pSelectedItem->boundingRect();
        QPointF bottomRight = m_pSelectedItem->mapToScene(rect.bottomRight());
        m_pResizableRectItem->setPos(bottomRight.x() - 10, bottomRight.y() - 10);
    }
}

void ImgEditor::updateSceneSize() {
    if (scene()) {
        QRectF newRect = m_pSelectedItem->boundingRect();
        scene()->setSceneRect(newRect.adjusted(-20, -20, 20, 20));
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
