#include <QApplication>

#include "Core.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Core core;

    return app.exec();
}

