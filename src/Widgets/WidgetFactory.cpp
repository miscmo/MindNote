#include "WidgetFactory.h"

#include <QFormLayout>

using namespace MyNote;

QFormLayout *WidgetFactory::createFormLayout(QWidget *parent) {
    QFormLayout *layout = new QFormLayout(parent);

    return layout;
}
