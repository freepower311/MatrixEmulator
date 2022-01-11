#ifndef LIMITEDQUEUE_H
#define LIMITEDQUEUE_H
#include <cstdint>
#define MAX_LENGTH 80

class LimitedQueue
{
public:
  LimitedQueue();
  void push(int8_t b);
  int8_t pop();
private:
  int8_t m_array[MAX_LENGTH];
  int m_front = 0;
  int m_back = 0;
};

#endif // LIMITEDQUEUE_H
