#ifndef Sector_h__
#define Sector_h__

#include <QGraphicsItem>
#include <QPainter>
#include "AllInclude.h"



class Sector : public QGraphicsItem
{
public:
    void updateData(float minRadius_px, float maxRadius_px, float minAngle_deg, float maxAngle_deg)
    {
        m_minRadius_px = minRadius_px;
        m_maxRadius_px = maxRadius_px;
        m_minAngle_deg = minAngle_deg;
        m_maxAngle_deg = maxAngle_deg;
    }

    virtual QRectF boundingRect() const override
    {
        return qtplus::radiusRect(m_maxRadius_px);
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override
    {
        painter->drawText(QPointF(0, 0), qtplus::to_qstring(pos()));
        painter->drawRect(boundingRect());                
        qtplus::drawArc(painter, boundingRect(), m_minAngle_deg, m_maxAngle_deg);
        qtplus::drawArc(painter, qtplus::radiusRect(m_minRadius_px), m_minAngle_deg, m_maxAngle_deg);

        QLineF lineLeftMin = qtplus::fromPolar(m_minRadius_px, m_minAngle_deg);
        QLineF lineLeftMax = qtplus::fromPolar(m_maxRadius_px, m_minAngle_deg);

        QLineF lineRightMin = qtplus::fromPolar(m_minRadius_px, m_maxAngle_deg);
        QLineF lineRightMax = qtplus::fromPolar(m_maxRadius_px, m_maxAngle_deg);

        QLineF leftLine(lineLeftMin.p2(), lineLeftMax.p2());
        QLineF rightLine(lineRightMin.p2(), lineRightMax.p2());

        painter->drawLine(leftLine);
        painter->drawLine(rightLine);
    }

private:
    float m_minRadius_px = 0;
    float m_maxRadius_px = 0;
    float m_minAngle_deg = 0;
    float m_maxAngle_deg = 0;

};


#endif // Sector_h__
