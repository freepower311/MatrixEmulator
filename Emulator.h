#ifndef EMULATOR_H
#define EMULATOR_H

#include <QtWidgets/QWidget>

class QPaintEvent;

class Emulator: public QWidget
{
  Q_OBJECT
public:
  Emulator(QWidget* parent = nullptr);
  void paintEvent(QPaintEvent *event) override;
public slots:
  void setMatrixSize(qint32 width, qint32 height);
  void setColor(qint32 x, qint32 y, const QColor& color);
private:
  std::vector<std::vector<QColor>> m_array;


};


#endif // EMULATOR_H
