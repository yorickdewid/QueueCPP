#ifndef QUEUE_H
#define QUEUE_H
#include <string>
#include <stdint.h>

class Queue
{
  std::string m_strName;
  bool m_bActive;
  bool m_bSystem;
  int m_nPriority;
public:
  Queue(std::string strName, int nPriority = -10);
  std::string GetName() const;
  int GetPriority() const;
  void SetPriority(int nPriority);
  void SetSystemFlag(bool bSystem);
};

#endif // QUEUE_H
