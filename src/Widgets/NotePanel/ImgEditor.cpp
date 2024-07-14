#include "ImgEditor.h"

#include <QVBoxLayout>
#include <QPixmap>
#include <QMenu>
#include <QAction>

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

    m_pPixmapItem = new QGraphicsPixmapItem();
    m_pScene->addItem(m_pPixmapItem);

    QPixmap pixmap(m_pBlock->getContent());
    m_pPixmapItem->setPixmap(pixmap);
    m_pPixmapItem->setTransformOriginPoint(pixmap.rect().center());
    m_pScene->setSceneRect(pixmap.rect());

    setFixedHeight(pixmap.height()+20);

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

void ImgEditor::updateImage() {
    // QPixmap scaledPixmap = m_bOriginalPixmap.scaled(m_bOriginalPixmap.size() * m_bScaleFactor, Qt::KeepAspectRatio);
    // m_pImgLabel->setPixmap(scaledPixmap);
    // m_pImgLabel->adjustSize();
    // adjustSize();
    // //imageRect = imageLabel->geometry();
}

Error ImgEditor::save() {
    return Error::success();
}

void ImgEditor::onZoomIn() {

}

void ImgEditor::onZoomOut() {

}


void ImgEditor::onAlignLeft() {

}

void ImgEditor::onAlignCenter() {

}

void ImgEditor::onAlignRight() {

}
