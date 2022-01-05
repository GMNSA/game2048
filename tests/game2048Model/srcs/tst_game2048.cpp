#include "tst_game2048.hpp"

#include <QDebug>

TestGame2048::TestGame2048()
  : m_app(new Game::Game2048Model(4, this))
{}

TestGame2048::~TestGame2048() {}

// 0  1  2  3
// 4  5  6  7
// 8  9 10 11
// 12 13 14 15

void
TestGame2048::test_rowAndColumn()
{
  int num{ 6 };
  QVERIFY(1 == m_app->row(num));
  QVERIFY(2 == m_app->column(num));

  num = 7;

  QVERIFY(1 == m_app->row(num));
  QVERIFY(3 == m_app->column(num));

  num = 9;

  QVERIFY(2 == m_app->row(num));
  QVERIFY(1 == m_app->column(num));

  num = 12;

  QVERIFY(3 == m_app->row(num));
  QVERIFY(0 == m_app->column(num));

  num = 3;

  QVERIFY(0 == m_app->row(num));
  QVERIFY(3 == m_app->column(num));

  QVERIFY(true);
}

void
TestGame2048::test_randomNumber()
{
  int n{ 0 };
  for (int i{ 0 }; i < 10; ++i) {
    n = m_app->randomNumber(1, 10);
    QVERIFY(n >= 0 && n <= 10);
  }

  for (int i{ 0 }; i < 10; ++i) {
    n = m_app->randomNumber(10, 15);
    QVERIFY(n >= 10 && n <= 15);
  }

  for (int i{ 0 }; i < 30; ++i) {
    n = m_app->randomNumber(20, 38);
    QVERIFY(n >= 20 && n <= 38);
  }
}

void
TestGame2048::test_freeRandomPlace()
{
  auto randomPlace{ m_app->freeRandomPlace() };

  QVERIFY(randomPlace >= 0 && randomPlace < m_app->size());
}

void
TestGame2048::test_occupiedCells()
{
  m_app->addRandomTile();
  m_app->addRandomTile();

  auto nOccupied{ m_app->occupiedCells() };
  QVERIFY(nOccupied == 2);

  m_app->addRandomTile();
  m_app->addRandomTile();
  m_app->addRandomTile();

  nOccupied = m_app->occupiedCells();
  QVERIFY(nOccupied == 5);
}

void
TestGame2048::test_freeCells()
{
  m_app->clearBoard();

  auto nFreeCells{ m_app->freeCells() };
  QVERIFY(nFreeCells == m_app->size());

  m_app->addRandomTile();
  m_app->addRandomTile();

  nFreeCells = m_app->freeCells();
  QVERIFY(nFreeCells == m_app->size() - 2);

  m_app->addRandomTile();
  m_app->addRandomTile();

  nFreeCells = m_app->freeCells();
  QVERIFY(nFreeCells == m_app->size() - 4);
}

void
TestGame2048::test_prepareGame()
{
  m_app->clearBoard();

  auto nOccupied = m_app->occupiedCells();
  QVERIFY(nOccupied == 0);

  m_app->prepareGame();

  nOccupied = m_app->occupiedCells();
  QVERIFY(nOccupied == 2);
}

void
TestGame2048::test_printData()
{
  m_app->clearBoard();

  m_app->addRandomTile();
  // m_app->printData();
}

void
TestGame2048::test_addTile()
{
  m_app->clearBoard();

  m_app->addTile(3, 2);
  auto occupied = m_app->occupiedCells();
  QVERIFY(occupied == 1);
}

void
TestGame2048::test_moveLeft()
{
  m_app->clearBoard();

  m_app->addTile(3, 2);
  m_app->addTile(4, 2);
  m_app->addTile(10, 4);

  QVERIFY(m_app->value(3) == 2);
  QVERIFY(m_app->value(4) == 2);
  QVERIFY(m_app->value(10) == 4);
  // 0  1  2  3
  // 4  5  6  7
  // 8  9 10 11
  // 12 13 14 15

  m_app->moveLeft();

  QVERIFY(m_app->value(0) == 2);
  QVERIFY(m_app->value(4) == 2);
  QVERIFY(m_app->value(8) == 4);
}

void
TestGame2048::test_moveLeftAdd()
{
  m_app->clearBoard();

  m_app->addTile(3, 2);
  m_app->addTile(0, 4);
  m_app->addTile(4, 2);
  m_app->addTile(6, 2);
  m_app->addTile(7, 4);

  QVERIFY(m_app->value(3) == 2);
  QVERIFY(m_app->value(0) == 4);
  QVERIFY(m_app->value(4) == 2);
  QVERIFY(m_app->value(6) == 2);
  QVERIFY(m_app->value(7) == 4);

  m_app->moveLeft();

  QVERIFY(m_app->value(1) == 2);
  QVERIFY(m_app->value(0) == 4);
  QVERIFY(m_app->value(4) == 8);
  QVERIFY(m_app->value(5) == 0);
}

void
TestGame2048::test_moveRight()
{
  m_app->clearBoard();

  m_app->addTile(0, 2);
  m_app->addTile(4, 2);
  m_app->addTile(5, 4);
  QVERIFY(m_app->value(0) == 2);
  QVERIFY(m_app->value(3) == 0);

  QVERIFY(m_app->value(4) == 2);
  QVERIFY(m_app->value(5) == 4);

  m_app->moveRight();

  QVERIFY(m_app->value(0) == 0);
  QVERIFY(m_app->value(3) == 2);
  QVERIFY(m_app->value(6) == 2);
  QVERIFY(m_app->value(7) == 4);
}

void
TestGame2048::test_moveRightAdd()
{
  m_app->clearBoard();

  m_app->addTile(0, 2);
  m_app->addTile(2, 2);
  m_app->addTile(7, 4);
  m_app->addTile(4, 2);
  m_app->addTile(5, 2);

  // m_app->printData();
  QVERIFY(m_app->value(0) == 2);
  QVERIFY(m_app->value(2) == 2);
  QVERIFY(m_app->value(7) == 4);
  QVERIFY(m_app->value(4) == 2);
  QVERIFY(m_app->value(5) == 2);

  m_app->moveRight();

  QVERIFY(m_app->value(3) == 4);
  QVERIFY(m_app->value(7) == 8);
  QVERIFY(m_app->value(6) == 0);
  QVERIFY(m_app->value(5) == 0);
}

void
TestGame2048::test_moveUp()
{
  m_app->clearBoard();

  m_app->addTile(12, 2);
  m_app->addTile(9, 4);
  m_app->addTile(10, 2);
  // m_app->addTile(5, 2);
  // m_app->addTile(7, 4);

  QVERIFY(m_app->value(12) == 2);
  QVERIFY(m_app->value(0) == 0);
  QVERIFY(m_app->value(4) == 0);

  QVERIFY(m_app->value(9) == 4);
  QVERIFY(m_app->value(10) == 2);
  // QVERIFY(m_app->value(5) == 2);
  // QVERIFY(m_app->value(7) == 4);

  // m_app->printData();
  m_app->moveUp();
  // m_app->printData();

  QVERIFY(m_app->value(12) == 0);
  QVERIFY(m_app->value(0) == 2);
  QVERIFY(m_app->value(4) == 0);
  QVERIFY(m_app->value(10) == 0);
  QVERIFY(m_app->value(2) == 2);
  QVERIFY(m_app->value(6) == 0);

  // QVERIFY(m_app->value(5) == 4);
  QVERIFY(m_app->value(1) == 4);
  // QVERIFY(m_app->value(3) == 4);
}

void
TestGame2048::test_moveUpAdd()
{
  m_app->clearBoard();

  m_app->addTile(12, 2);
  m_app->addTile(8, 4);

  m_app->addTile(9, 4);
  m_app->addTile(1, 4);

  m_app->addTile(10, 2);
  m_app->addTile(14, 2);

  QVERIFY(m_app->value(12) == 2);
  QVERIFY(m_app->value(0) == 0);
  QVERIFY(m_app->value(4) == 0);

  QVERIFY(m_app->value(9) == 4);
  QVERIFY(m_app->value(1) == 4);

  QVERIFY(m_app->value(10) == 2);
  QVERIFY(m_app->value(14) == 2);

  // m_app->printData();
  m_app->moveUp();
  // m_app->printData();

  QVERIFY(m_app->value(12) == 0);
  QVERIFY(m_app->value(0) == 4);
  QVERIFY(m_app->value(4) == 2);

  QVERIFY(m_app->value(1) == 8);

  QVERIFY(m_app->value(2) == 4);
}

void
TestGame2048::test_moveDown()
{
  m_app->clearBoard();

  m_app->addTile(0, 2);

  m_app->addTile(1, 2);
  m_app->addTile(9, 4);

  QVERIFY(m_app->value(0) == 2);

  QVERIFY(m_app->value(1) == 2);
  QVERIFY(m_app->value(9) == 4);

  m_app->printData();
  m_app->moveDown();
  m_app->printData();

  QVERIFY(m_app->value(0) == 0);
  QVERIFY(m_app->value(12) == 2);

  QVERIFY(m_app->value(1) == 0);
  QVERIFY(m_app->value(9) == 2);
  QVERIFY(m_app->value(13) == 4);
}

// 0  1  2  3
// 4  5  6  7
// 8  9  10 11
// 12 13 14 15

void
TestGame2048::test_moveDownAdd()
{
  m_app->clearBoard();

  m_app->addTile(0, 2);
  m_app->addTile(8, 2);

  m_app->addTile(13, 4);
  m_app->addTile(5, 2);
  m_app->addTile(1, 2);

  QVERIFY(m_app->value(0) == 2);
  QVERIFY(m_app->value(8) == 2);

  QVERIFY(m_app->value(13) == 4);
  QVERIFY(m_app->value(5) == 2);
  QVERIFY(m_app->value(1) == 2);

  m_app->printData();
  m_app->moveDown();
  m_app->printData();

  QVERIFY(m_app->value(0) == 0);
  QVERIFY(m_app->value(8) == 0);
  QVERIFY(m_app->value(12) == 4);

  QVERIFY(m_app->value(13) == 8);
  QVERIFY(m_app->value(5) == 0);
  QVERIFY(m_app->value(1) == 0);
}

QTEST_APPLESS_MAIN(TestGame2048)
