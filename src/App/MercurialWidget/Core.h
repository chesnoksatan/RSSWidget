#ifndef CORE_H
#define CORE_H

#include <QObject>

#include "FormController/FormController.h"

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

private:
    FormController* _form;
};

#endif // CORE_H
