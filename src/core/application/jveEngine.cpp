

#include "jveEngine.h"


#include <QtMath>
#include <QThread>
#include <QDebug>


jveEngine::jveEngine(QObject *parent)
    : QObject(parent)
{
}

jveEngine::~jveEngine(void)
{
}

void
jveEngine::process(void)
{
    while (true) {
        // TODO lock project mutex
        // caching
        if (2 > 3) {
            // TODO render and cache next frames
            qDebug() << "caching";
        // playing or render
        } else if (2 == 2) {
            //jveState::projectState->playheadPosition += 1;
            /*if (jveState::mode == jveState::MODE_GUI) {
                emit wantUpdateUi();
            }*/
            //qDebug() << "playing";
        }
        // TODO unlock project mutex
        QThread::usleep(qCeil(1.0 / 23.976023976 * 1000000));
    }
}


