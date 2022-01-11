#include "LimitedQueue.h"

LimitedQueue::LimitedQueue()
{

}
void LimitedQueue::push(int8_t b)
{
  m_array[m_front] = b;
  m_front++;
  if(m_front >= MAX_LENGTH)
    m_front = 0;
}

int8_t LimitedQueue::pop()
{
  if(m_front == m_back)
    return 0;
  const auto result = m_array[m_back];
  m_back++;
  if(m_back >= MAX_LENGTH)
    m_back = 0;
  return result;
}
