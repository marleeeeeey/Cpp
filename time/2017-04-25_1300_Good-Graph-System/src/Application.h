#ifndef Application_h__
#define Application_h__

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "AllInclude.h"
#include "Sector.h"

class Applicaion : public QObject
{
public:
    Applicaion();
    void update();


protected:
    virtual void timerEvent(QTimerEvent *) override;

private:
    
    static void myCallback(void * data);

    void initViewScene();

    QGraphicsView *  m_view   = nullptr;
    QGraphicsScene * m_scene  = nullptr;
    Sector *         m_sector = nullptr;
};


#endif // Application_h__
