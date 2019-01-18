

#include "JveEngine.h"


#include <QtMath>
#include <QThread>
#include <QDebug>


JveEngine::JveEngine(QObject *parent)
    : QObject(parent)
{
}

JveEngine::~JveEngine(void)
{
}

void
JveEngine::process(void)
{
    while (true) {
        // TODO lock project mutex
        // caching
        if (2 > 3) {
            // TODO render and cache next frames
            qDebug() << "caching";
        // playing or render
        } else if (2 == 2) {
            //JveState::projectState->playheadPosition++;
            /*if (JveState::mode == JveState::MODE_GUI) {
                emit wantUpdateUi();
            }*/
            //qDebug() << "playing";
        }
        // TODO unlock project mutex
        QThread::usleep(qCeil(1.0 / 23.976023976 * 1000000));
    }
}


