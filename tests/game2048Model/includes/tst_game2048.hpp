#ifndef TST_GAME2048_HPP
#define TST_GAME2048_HPP

#include <QtTest>

#include "game2048model.hpp"

class TestGame2048 : public QObject
{
  Q_OBJECT

public:
  TestGame2048();
  ~TestGame2048();

private slots:
  void test_rowAndColumn();
  void test_randomNumber();
  void test_freeRandomPlace();
  void test_occupiedCells();
  void test_freeCells();
  void test_prepareGame();
  void test_printData();
  void test_addTile();

  void test_moveLeft();
  void test_moveLeftAdd();

  void test_moveRight();
  void test_moveRightAdd();

  void test_moveUp();
  void test_moveUpAdd();

  void test_moveDown();
  void test_moveDownAdd();

private:
  Game::Game2048Model* m_app;
};

// #include "tst_modelpuzzle.moc"

#endif // TST_GAME2048_HPP
