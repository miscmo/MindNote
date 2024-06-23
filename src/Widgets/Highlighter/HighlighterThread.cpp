#include "HighlighterThread.h"

#include <Widgets/Highlighter/peg-markdown-highlight/pmh_parser.h>

using namespace MyNote;

HighlighterThread::HighlighterThread(QObject *parent) :
    QThread(parent)
{
}


void HighlighterThread::enqueue(const QString &text, unsigned long offset)
{
    QMutexLocker locker(&tasksMutex);
    tasks.enqueue(Task {text, offset});
    bufferNotEmpty.wakeOne();
}


void HighlighterThread::run()
{
    forever {
        Task task;

        {
            // wait for new task
            QMutexLocker locker(&tasksMutex);
            while (tasks.count() == 0) {
                bufferNotEmpty.wait(&tasksMutex);
            }

            // get last task from queue and skip all previous tasks
            while (!tasks.isEmpty())
                task = tasks.dequeue();
        }

        // end processing?
        if (task.text.isNull()) {
            return;
        }

        // delay processing by 500 ms to see if more tasks are coming
        // (e.g. because the user is typing fast)
        this->msleep(500);

        // no more new tasks?
        if (tasks.isEmpty()) {
            // parse markdown and generate syntax elements
            pmh_element **elements;
            pmh_markdown_to_elements(task.text.toUtf8().data(), pmh_EXT_NONE, &elements);

            emit signalResultReady(elements, task.offset);
        }
    }
}
