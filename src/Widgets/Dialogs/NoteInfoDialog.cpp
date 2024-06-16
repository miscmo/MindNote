#include "NoteInfoDialog.h"

#include <Notebook/NotebookManager.h>

#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDir>
#include <Utils/Errors.h>

namespace MyNote {

NoteInfoDialog::NoteInfoDialog(QWidget *parent, int type)
    : ScrollDialog(parent), m_bType(type) {
    setupUI();
}

void NoteInfoDialog::setupUI() {

    m_pNoteInfoWidget = new QWidget(this);

    m_pMainLayout = new QFormLayout(m_pNoteInfoWidget);

    m_pNotePath = new QLineEdit(m_pNoteInfoWidget);
    m_pNotePath->setMinimumWidth(300); // 设置最小宽度
    m_pNotePath->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // 让输入框可以扩展
    connect(m_pNotePath, &QLineEdit::textEdited, this, &NoteInfoDialog::onNoteInfoEdited);

    QPushButton *browerBtn = new QPushButton(tr("brower"), this);
    browerBtn->setFixedWidth(80);
    connect(browerBtn, &QPushButton::clicked, [this](){
        QString dir = QFileDialog::getExistingDirectory(
            this, tr("choose new notebook dir"),
            "",
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );
        if (!dir.isEmpty()) {
            m_pNotePath->setText(dir);
        }
    });

    QHBoxLayout *notePathLayout = new QHBoxLayout();
    notePathLayout->addWidget(m_pNotePath);
    notePathLayout->addWidget(browerBtn);


    m_pMainLayout->addRow(tr("NotePath:"), notePathLayout);

    m_pNoteName = new QLineEdit(m_pNoteInfoWidget);
    m_pNoteName->setMinimumWidth(300); // 设置最小宽度
    connect(m_pNoteName, &QLineEdit::textEdited, this, &NoteInfoDialog::onNoteInfoEdited);
    m_pMainLayout->addRow(tr("NoteName:"), m_pNoteName);

    //m_pPasswd = new QLineEdit(m_pNoteInfoWidget);
    m_pMainLayout->addRow(tr("Passwd:"), new QLabel("todo", m_pNoteInfoWidget));

    //m_pRetryPasswd = new QLineEdit(m_pNoteInfoWidget);
    m_pMainLayout->addRow(tr("RetryPasswd:"), new QLabel("todo", m_pNoteInfoWidget));

    //connect(m_pNameLineEdit, &QLineEdit::textEdited, this, &NewNoteDialog::onNameEdited);

    setCentralWidget(m_pNoteInfoWidget);

    setDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    setButtonEnabled(QDialogButtonBox::Ok, false);

    setWindowTitle(tr("New Note"));

}

void NoteInfoDialog::acceptedButtonClicked() {
    QString notePath = m_pNotePath->text();
    QString noteName = m_pNoteName->text();


    if (notePath.isEmpty() || noteName.isEmpty()) {
        QMessageBox::warning(this, tr("create error"), tr("path and name cannot be empty"));
        return ;
    }

    QFileInfo pathInfo(notePath);

    if (!pathInfo.exists() || !pathInfo.isDir()) {
        QMessageBox::warning(this, tr("create error"), tr("path not exists or not a dir"));
        return ;
    }



    QFileInfo noteFilepathInfo(QDir(notePath).filePath(noteName));
    if (noteFilepathInfo.exists() && noteFilepathInfo.isDir()) {
        QMessageBox::warning(this, tr("create error"), tr("current dir already has dupname note"));
        return ;
    }

    Error err = NoteMgr::GetInstance()->createNewNote(notePath, noteName);

    if (err.isSuccess()) {
        accept();
    } else {
        QMessageBox::warning(this, tr("create error"), tr(err.message.toStdString().c_str()));
    }


}

void NoteInfoDialog::onNoteInfoEdited(const QString &path) {
    qDebug() << path << Qt::endl;
    if (m_pNotePath->text().isEmpty() || m_pNoteName->text().isEmpty()) {
        setButtonEnabled(QDialogButtonBox::Ok, false);
        return ;
    }

    setButtonEnabled(QDialogButtonBox::Ok, true);
}

}


