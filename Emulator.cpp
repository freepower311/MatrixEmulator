#include "Emulator.h"
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>

Emulator::Emulator(QWidget* parent):
  QWidget(parent)
{
  setMatrixSize(10,10);
  setColor(4,9,QColor(0,255,0));
}

void Emulator::paintEvent(QPaintEvent *event)
{
  if(m_array.empty()||m_array[0].empty())
    return;

/*  size().width();
  size().height();
  m_array.size();
  m_array[0].size();*/
  double xResolution = 1.0 * size().width() / m_array.size();
  double yResolution = 1.0 * size().height() / m_array[0].size();
  double finalResolution = std::min(xResolution,yResolution);
  double xShift = (size().width() - finalResolution * m_array.size())/2;
  double yShift = (size().height() - finalResolution * m_array[0].size())/2;
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 0));
  painter.setBrush(QColor(0,0,0));
  for(qint32 x = 0; x < m_array.size(); x++)
  {
    for(qint32 y = 0; y < m_array[0].size(); y++)
    {
      painter.setBrush(m_array[x][y]);
      painter.drawRect(QRectF{xShift + x * finalResolution,
                              yShift + y * finalResolution,
                              finalResolution ,
                              finalResolution });
    }
  }

  painter.end();
}

void Emulator::setMatrixSize(qint32 width, qint32 height)
{
  m_array.clear();
  for(qint32 i = 0; i < width; i++)
  {
    m_array.push_back(std::vector<QColor>());
    for(qint32 j = 0; j < height; j++)
    {
      m_array.back().push_back(QColor(0,0,0));
    }
  }
  update();
}

void Emulator::setColor(qint32 x, qint32 y, const QColor& color)
{
  if(x<0||x>=m_array.size())
    return;
  if(y<0||y>=m_array[x].size())
    return;
  m_array[x][y] = color;
  update();
}

