#include <stdexcept>

#include "queue.h"

Queue::Queue(std::string strName, int nPriority) : 
  m_nPriority(nPriority),
  m_bActive(true),
  m_bSystem(false),
  m_strName(strName) {}

std::string Queue::GetName() const {
    return m_strName;
}

int Queue::GetPriority() const {
    return m_nPriority;
}

void Queue::SetPriority(int nPriority)  {
    if (m_bSystem)
	throw std::runtime_error("Cannot alter system queues");
    m_nPriority = nPriority;
}

void Queue::SetSystemFlag(bool bSystem) {
    m_bSystem = bSystem;
}
