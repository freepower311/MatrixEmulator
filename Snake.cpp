#include "Snake.h"
#include <QtGui/QColor>
#include <QtCore/QPoint>
#define START_LENGTH 4    // начальная длина змейки


Snake::Snake(QObject* parent):
  QObject(parent)
{
  for(qint32 i = 0; i < 10; i++)
  {
    m_array.push_back(ObjectsVector());
    for(qint32 j = 0; j < 10; j++)
    {
      m_array.back().push_back(GameObject::EMPTY);
    }
  }

}
void Snake::init()
{
  startTimer(500);
  emit signalSetMatrixSize(10, 10);
}
bool Snake::checkWall(quint32 x, quint32 y)
{
  if(m_array.empty() || m_array[0].empty())
    return true;
  return x < 0 || x >= m_array.size() || y < 0 || y >= m_array[0].size();
}
void Snake::timerEvent(QTimerEvent*)
{
  emit signalSetColor(5, 5, QColor(0, 255, 0));
}
Snake::Direction Snake::chooseDirection(qint32 previousPosX, qint32 previousPosY, qint32 currentPosX, qint32 currentPosY, qint32 applePosX, qint32 applePosY)
{
  qint32 leftPosX;
  qint32 leftPosY;
  qint32 rightPosX;
  qint32 rightPosY;
  qint32 forvardPosX;
  qint32 forvardPosY;
  qint32 previousVectX;
  qint32 previousVectY;
  qint32 leftVectX;
  qint32 leftVectY;
  qint32 rightVectX;
  qint32 rightVectY;
  qint32 appleVectX;
  qint32 appleVectY;
  Direction favouriteDirection;
  Direction finalDirection;
  qint32 finalPos[2];

  previousVectX = currentPosX - previousPosX;
  previousVectY = currentPosY - previousPosY;
  if(previousVectY == 0)
  {
    leftVectX = previousVectY;
    leftVectY = previousVectX;
  }
  else
  {
    leftVectX = - previousVectY;
    leftVectY = - previousVectX;
  }
  rightVectX = - leftVectX;
  rightVectY = - leftVectY;
  leftPosX = currentPosX + leftVectX;
  leftPosY = currentPosY + leftVectY;
  rightPosX = currentPosX + rightVectX;
  rightPosY = currentPosY + rightVectY;
  forvardPosX = currentPosX + previousVectY;
  forvardPosY = currentPosY + previousVectX;
  appleVectX = applePosX - currentPosX;
  appleVectY = applePosY - currentPosY;

  if(appleVectX == 0)
  {
    if(appleVectY > 0)
    {
      if(leftVectX == 0 && leftVectY == 1)
      {
        favouriteDirection = Direction::LEFT;
      }
      else if(rightVectX == 0 && rightVectY == 1)
      {
        favouriteDirection = Direction::RIGHT;
      }
      else
      {
        favouriteDirection = Direction::FORVARD;
      }
    }
    else
    {
      if(leftVectX == 0 && leftVectY == -1)
      {
        favouriteDirection = Direction::LEFT;
      }
      else if(rightVectX == 0 && rightVectY == -1)
      {
        favouriteDirection = Direction::RIGHT;
      }
      else
      {
        favouriteDirection = Direction::FORVARD;
      }
    }
  }
  else if(appleVectY == 0)
  {
    if(appleVectX > 0)
    {
      if(leftVectX == 1 && leftVectY == 0)
      {
        favouriteDirection = Direction::LEFT;
      }
      else if(rightVectX == 1 && rightVectY == 0)
      {
        favouriteDirection = Direction::RIGHT;
      }
      else
      {
        favouriteDirection = Direction::FORVARD;
      }
    }
    else
    {
      if(leftVectX == -1 && leftVectY == 0)
      {
        favouriteDirection = Direction::LEFT;
      }
      else if(rightVectX == -1 && rightVectY == 0)
      {
        favouriteDirection = Direction::RIGHT;
      }
      else
      {
        favouriteDirection = Direction::FORVARD;
      }
    }
  }

  switch (favouriteDirection)
  {
  case Direction::LEFT:
    if(checkWall(leftPosX, leftPosY) || m_array[leftPosX][leftPosY] == GameObject::SNAKE)
      if(checkWall(forvardPosX, forvardPosY) || m_array[forvardPosX][forvardPosY] == GameObject::SNAKE)
        finalDirection = Direction::RIGHT;
      else
        finalDirection = Direction::FORVARD;
    else
      finalDirection = Direction::LEFT;
    break;
  case Direction::RIGHT:
    if(checkWall(rightPosX, rightPosY) || m_array[rightPosX][rightPosY] == GameObject::SNAKE)
      if(checkWall(forvardPosX, forvardPosY) || m_array[forvardPosX][forvardPosY] == GameObject::SNAKE)
        finalDirection = Direction::LEFT;
      else
        finalDirection = Direction::FORVARD;
    else
      finalDirection = Direction::RIGHT;
    break;
  case Direction::FORVARD:
    if(checkWall(forvardPosX, forvardPosY))
      if(checkWall(rightPosX, rightPosY) || m_array[rightPosX][rightPosY] == GameObject::SNAKE)
        finalDirection = Direction::LEFT;
      else
        finalDirection = Direction::RIGHT;
    else if(m_array[forvardPosX][forvardPosY] == GameObject::SNAKE)
      if(checkWall(leftPosX, leftPosY) || m_array[leftPosX][leftPosY] == GameObject::SNAKE)
        finalDirection = Direction::RIGHT;
      else
        finalDirection = Direction::LEFT;
    else
      finalDirection = Direction::FORVARD;
    break;
  default:
    Q_ASSERT(false);
    break;
  }
  switch(finalDirection)
  {
  case Direction::LEFT:
  {
    finalPos[0] = leftPosX;
    finalPos[1] = leftPosY;
  }
  break;
  case Direction::RIGHT:
  {
    finalPos[0] = leftPosX;
    finalPos[1] = leftPosY;
  }
  break;
  case Direction::FORVARD:
  {
    finalPos[0] = leftPosX;
    finalPos[1] = leftPosY;
  }
  break;



  return finalPos;

}










/*
int8_t vectorX, vectorY;
int8_t headX, headY, buttX, buttY;
int8_t appleX, appleY;
bool apple_flag, missDelete = false;

int8_t buttVector[MAX_LENGTH];
int snakeLength;
bool butt_flag, pizdetc;

void snakeRoutine()
{
  if (loadingFlag)
  {
    FastLED.clear();
    loadingFlag = false;
    newGameSnake();
    gamemodeFlag = true;
    modeCode = 2;
  }

  buttonsTickSnake();

  if (gameTimer.isReady())
  {
    // БЛОК ГЕНЕРАЦИИ ЯБЛОКА
    while (!apple_flag)
    {                         // пока яблоко не создано
      appleX = random(0, WIDTH);                  // взять случайные координаты
      appleY = random(0, HEIGHT);

      // проверить, не совпадает ли координата с телом змеи
      if ((long)getPixColorXY(appleX, appleY) == 0)
      {
        apple_flag = true;                        // если не совпадает, считаем что яблоко создано
        drawPixelXY(appleX, appleY, GLOBAL_COLOR_2);        // и рисуем
        FastLED.show();
      }
    }

    // запоминаем, куда повернули голову
    // 0 - право, 1 - лево, 2 - вверх, 3 - вниз
    if (vectorX > 0) buttVector[snakeLength] = 0;
    else if (vectorX < 0) buttVector[snakeLength] = 1;
    if (vectorY > 0) buttVector[snakeLength] = 2;
    else if (vectorY < 0) buttVector[snakeLength] = 3;

    // смещение головы змеи
    headX += vectorX;
    headY += vectorY;

    if (headX < 0 || headX > WIDTH - 1 || headY < 0 || headY > HEIGHT - 1)
    { // если вышла за границы поля
      pizdetc = true;
    }

    if (!pizdetc) {
      // проверка на pizdetc
      if ((long)(getPixColorXY(headX, headY) != 0 && (long)getPixColorXY(headX, headY) != GLOBAL_COLOR_2))
      {   // если змея врезалась во что то, но не в яблоко
        pizdetc = true;                           // флаг на отработку
      }

      // БЛОК ОТРАБОТКИ ПОЕДАНИЯ ЯБЛОКА
      if (!pizdetc && (long)getPixColorXY(headX, headY) == (long)GLOBAL_COLOR_2)
      { // если попали головой в яблоко
        apple_flag = false;                       // флаг что яблока больше нет
        snakeLength++;                            // увеличить длину змеи
        buttVector[snakeLength] = 4;              // запоминаем, что надо будет не стирать хвост
      }

      // вычисляем координату хвоста (чтобы стереть) по массиву вектора
      switch (buttVector[0])
      {
        case 0: buttX += 1;
          break;
        case 1: buttX -= 1;
          break;
        case 2: buttY += 1;
          break;
        case 3: buttY -= 1;
          break;
        case 4: missDelete = true;  // 4 значит не стирать!
          break;
      }

      // смещаем весь массив векторов хвоста ВЛЕВО
      for (byte i = 0; i < snakeLength; i++)
      {
        buttVector[i] = buttVector[i + 1];
      }

      // если змея не в процессе роста, закрасить бывший хвост чёрным
      if (!missDelete) {
        drawPixelXY(buttX, buttY, 0x000000);
      }
      else missDelete = false;

      // рисуем голову змеи в новом положении
      drawPixelXY(headX, headY, GLOBAL_COLOR_1);
      FastLED.show();
    }
    if (gameDemo) snakeDemo();
  }

  // если он настал
  if (pizdetc)
  {
    pizdetc = false;

    if (!gameDemo)
    {
      // ну в общем плавно моргнуть, типо змейке "больно"
      for (byte bright = 0; bright < 15; bright++)
      {
        FastLED.setBrightness(bright);
        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i] = CRGB::Red;
        }
        FastLED.show();
        delay(10);
      }
      delay(100);
      FastLED.clear();
      FastLED.show();
      FastLED.setBrightness(BRIGHTNESS);
      displayScore(snakeLength - START_LENGTH);
      delay(1000);
    }
    FastLED.clear();
    FastLED.show();
    newGameSnake();                          // миша, всё ху.я, давай по новой
  }
}

void snakeDemo()
{
  // смещение головы змеи
  int8_t nextX = headX + vectorX;
  int8_t nextY = headY + vectorY;

  // ищем яблоко
  if (headX == appleX) {                // яблоко на одной линии по вертикали
    if (headY < appleY) buttons = 0;
    if (headY > appleY) buttons = 2;
  }
  if (headY == appleY) {                // яблоко на одной линии по горизонтали
    if (headX < appleX) buttons = 1;
    if (headX > appleX) buttons = 3;
  }

  if (getPixColorXY(nextX, nextY) == GLOBAL_COLOR_1)
  {   // проверка на столкновение с собой
    // поворачиваем налево
    if (vectorX > 0) buttons = 0;
    if (vectorX < 0) buttons = 2;
    if (vectorY > 0) buttons = 3;
    if (vectorY < 0) buttons = 1;
    return;
  }

  if (nextX < 0 || nextX > WIDTH - 1 || nextY < 0        // проверка на столкновение со стеной
      || nextY > HEIGHT - 1)
  {

    // поворачиваем направо в обычном случае или налево в углу
    if (vectorX > 0) buttons = 2;
    if (vectorX > 0 && headY == 0) buttons = 0;

    if (vectorX < 0 && headY == HEIGHT - 1) buttons = 2;
    if (vectorX < 0) buttons = 0;

    if (vectorY > 0) buttons = 1;
    if (vectorY > 0 && headX == WIDTH - 1) buttons = 3;

    if (vectorY < 0 && headX == 0) buttons = 1;
    if (vectorY < 0) buttons = 3;
  }
}

void buttonsTickSnake()
{
  if (checkButtons())
  {
    if (buttons == 3)
    {   // кнопка нажата
      vectorX = -1;
      vectorY = 0;
      buttons = 4;
    }
    if (buttons == 1)
    {   // кнопка нажата
      vectorX = 1;
      vectorY = 0;
      buttons = 4;
    }
    if (buttons == 0)
    {   // кнопка нажата
      vectorY = 1;
      vectorX = 0;
      buttons = 4;
    }
    if (buttons == 2)
    {   // кнопка нажата
      vectorY = -1;
      vectorX = 0;
      buttons = 4;
    }
  }
}

void newGameSnake()
{
  FastLED.clear();
  // свежее зерно для генератора случайных чисел
  randomSeed(millis());

  // длина из настроек, начинаем в середине экрана, бла-бла-бла
  snakeLength = START_LENGTH;
  headX = WIDTH / 2;
  headY = HEIGHT / 2;
  buttY = headY;

  vectorX = 1;  // начальный вектор движения задаётся вот здесь
  vectorY = 0;
  buttons = 4;

  // первоначальная отрисовка змейки и забивка массива векторов для хвоста
  for (byte i = 0; i < snakeLength; i++)
  {
    drawPixelXY(headX - i, headY, GLOBAL_COLOR_1);
    buttVector[i] = 0;
  }
  FastLED.show();
  buttX = headX - snakeLength;   // координата хвоста как голова - длина
  missDelete = false;
  apple_flag = false;
}

#elif (USE_SNAKE == 0)
void snakeRoutine()
{
  return;
}


//void signalSetColor(qint32 x, qint32 y, const QColor& color);
//void signalSetMatrixSize(qint32 width, qint32 height);
*/


