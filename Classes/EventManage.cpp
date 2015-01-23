#include "EventManage.h"

static EventManage * pEv = NULL;

EventManage * EventManage::getInstance()
{
	if(pEv == NULL)
	{
		pEv = new EventManage();
	}
	return pEv;
}

bool EventManage::isEmpty()
{
	return m_ManageEvent.empty();
}

void EventManage::addEvent(nEvent * ev)
{
	m_ManageEvent.push(ev);
}

nEvent *  EventManage::getEvent()
{	
	if(m_ManageEvent.empty())
	{
		return NULL;
	}

	nEvent *  pEvent = m_ManageEvent.front();
	m_ManageEvent.pop();
	return pEvent;
}

