#ifndef HIGHLIGHTERTHREAD_H
#define HIGHLIGHTERTHREAD_H

#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>

#include <Widgets/Highlighter/peg-markdown-highlight/pmh_definitions.h>

namespace MyNote {

struct Task {
    QString text;
    unsigned long offset;
};

class HighlighterThread : public QThread {
    Q_OBJECT

public:
    explicit HighlighterThread(QObject *parent = nullptr);


    void enqueue(const QString &text, unsigned long offset = 0);

signals:
    void signalResultReady(pmh_element **elements, unsigned long offset);

protected:
    virtual void run();

private:
    QQueue<Task> tasks;
    QMutex tasksMutex;
    QWaitCondition bufferNotEmpty;
};

}

#endif // HIGHLIGHTERTHREAD_H
