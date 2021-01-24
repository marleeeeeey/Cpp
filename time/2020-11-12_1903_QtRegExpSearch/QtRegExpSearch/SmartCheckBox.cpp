#include "SmartCheckBox.h"

void SmartCheckBox::checkStateSet()
{
    QCheckBox::checkStateSet();
    if( m_oldState == checkState() )
    {
        // emit the signal here, as QCheckBox::checkStateSet() didn't do it.
        emit stateChanged( m_oldState );
    }
    else
    {
        // don't emit the signal as it has been emitted already,
        // but save the old state
        m_oldState = checkState();
    }
}
