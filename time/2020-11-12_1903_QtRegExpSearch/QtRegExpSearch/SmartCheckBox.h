#pragma once

#include <QCheckBox>


class SmartCheckBox : public QCheckBox
{
    Q_OBJECT

public:
    using QCheckBox::QCheckBox;

protected:
    void checkStateSet();

private:
    Qt::CheckState m_oldState;
};

