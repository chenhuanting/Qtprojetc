#include <QCoreApplication>
#include <QObject>
#include <QThread>
#include <iostream>
#include <chrono>
#include <thread>
#include <QDebug>
#include "Enginner.h"
#include "commanager.h"
#include "motor.h"

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    Enginner en;
    en.process();

    return 0;
}
