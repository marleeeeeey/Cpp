#include "Application.h"

class TimerScene : public QGraphicsScene
{

protected:
    virtual void timerEvent(QTimerEvent *) override
    {
        update();
    }

};

Applicaion::Applicaion()
{
    initViewScene();
    
    m_sector = new Sector();
    m_sector->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_scene->addItem(m_sector);

    startTimer(10);
}

void Applicaion::update()
{
    float minRadius_px = 0;
    float maxRadius_px = 0;
    float minAngle_deg = 0;
    float maxAngle_deg = 0;

    ABIND_DBL(minRadius_px, 40);
    ABIND_DBL(maxRadius_px, 80);
    ABIND_DBL(minAngle_deg, -30);
    ABIND_DBL(maxAngle_deg, 30);

    m_sector->updateData(minRadius_px, 
        maxRadius_px, minAngle_deg, maxAngle_deg);
}

void Applicaion::timerEvent(QTimerEvent *)
{
    update();
}

void Applicaion::myCallback(void * data)
{
    Applicaion * pApp = static_cast<Applicaion *>(data);
    pApp->update();
}

void Applicaion::initViewScene()
{
    m_view = new QGraphicsView();
    m_view->show();

    m_scene = new TimerScene();
    m_scene->startTimer(100);
    m_view->setScene(m_scene);

}

