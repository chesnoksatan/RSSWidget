#include "Core.h"

Core::Core(QObject *parent) : QObject(parent)
{
    _form = new FormController();
}

Core::~Core()
{
    delete _form;
}
