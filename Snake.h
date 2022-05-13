#ifndef SNAKE_H
#define SNAKE_H
#include <QtCore/QObject>
class Snake: public QObject
{
  Q_OBJECT
public:
  enum class GameObject: quint8
  {
    APPLE,
    SNAKE,
    EMPTY
  };
  enum class Direction: quint8
  {
    LEFT,
    RIGHT,
    FORVARD
  };
  Snake(QObject* parent = nullptr);
  void timerEvent(QTimerEvent*);
  void init();

signals:
  void signalSetColor(qint32 x, qint32 y, const QColor& color);
  void signalSetMatrixSize(qint32 width, qint32 height);
private:
  bool checkWall(quint32 x, quint32 y);
  Snake::Direction chooseDirection(qint32 previousPosX, qint32 previousPosY, qint32 currentPosX, qint32 currentPosY, qint32 applePosX, qint32 applePosY);
  using ObjectsVector = std::vector<GameObject>;
  std::vector<ObjectsVector> m_array;

};


#endif // SNAKE_H
