#include "game2048model.hpp"
#include <QDebug>
#include <QTimer>
#include <random>

namespace Game {

Game2048Model::Game2048Model(int deep_, QObject* parent)
  : QAbstractListModel(parent)
  , m_deep(deep_)
  , m_size(deep_ * deep_)
  , m_timer(new QTimer(this))
  , m_isAnimationEnable(true)
{
  m_data.resize(m_size);
}

Game2048Model::~Game2048Model()
{
  // dtor
}

int
Game2048Model::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return m_size;
}

QVariant
Game2048Model::data(const QModelIndex& index, int role) const
{
  Q_UNUSED(index);
  Q_UNUSED(role);

  if (!index.isValid() or role != Qt::DisplayRole or
      (index.row() > m_size or index.row() < 0))
    return {};

  return QVariant::fromValue(m_data[index.row()]);
}

void
Game2048Model::init()
{
  prepareGame();
}

int
Game2048Model::randomNumber(int begin_, int end_)
{
  std::uniform_int_distribution<int> distribution(begin_, end_);
  std::random_device rd;
  std::default_random_engine random(rd());

  return (distribution(random));
}

int
Game2048Model::prepareGame()
{
  addRandomTile();
  addRandomTile();

  return (0);
}

int
Game2048Model::freeRandomPlace()
{
  int tmp{ 0 };
  bool isStart{ true };
  while (isStart) {
    tmp = randomNumber(0, m_size - 1);

    if (m_data[tmp] == 0)
      isStart = false;
  }
  return (tmp);
}

int
Game2048Model::beginRandomNumber()
{
  int t = randomNumber(0, 1);

  if (t == 0)
    return (2);
  else
    return (4);
}

bool
Game2048Model::reset()
{
  if (m_isAnimationEnable) {
    beginResetModel();
    clearBoard();
    prepareGame();
    endResetModel();
    timerAnimation();

    return (true);
  } else
    return (false);
}

// 0  1  2  3
// 4  5  6  7
// 8  9 10 11
// 12 13 14 15

// 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15

bool
Game2048Model::moveLeft()
{
  if (!m_isAnimationEnable)
    return false;

#ifdef FOR_TEST
  timerAnimation();
#endif

  for (int i{ 0 }; i < m_size; ++i) {
    if (m_data[i] != 0) {
      for (int j{ i }; j > 0; --j) {
        if (column(j) > 0 && column(j) < m_deep) {
          if (m_data[j - 1] == 0) {
            beginMoveColumns(QModelIndex(), j, j, QModelIndex(), j - 1);
            std::swap(m_data[j], m_data[j - 1]);
            endMoveRows();
          }

          if (m_data[j - 1] != 0 && m_data[j - 1] == m_data[j]) {
            beginResetModel();
            m_data[j - 1] = 0;
            m_data[j] *= 2;
            endResetModel();
            beginMoveColumns(QModelIndex(), j, j, QModelIndex(), j - 1);
            std::swap(m_data[j], m_data[j - 1]);
            endMoveRows();
          }
        }
      }
    }
  }

  printData();
  return (true);
}

bool
Game2048Model::moveRight()
{
  if (!m_isAnimationEnable)
    return (false);

#ifdef FOR_TEST
  timerAnimation();
#endif

  for (int i{ m_size - 1 }; i >= 0; --i) {
    if (m_data[i] != 0) {
      for (int j{ i }; j < m_size - 1; ++j) {
        int col = column(j);
        if (col >= 0 && col < m_deep - 1) {
          if (m_data[j + 1] == 0) {
            beginMoveRows(QModelIndex(), j, j, QModelIndex(), j + 2);
            std::swap(m_data[j], m_data[j + 1]);
            endMoveRows();
          }

          if (m_data[j + 1] == m_data[j] && m_data[j] != 0) {
            beginResetModel();
            m_data[j + 1] = 0;
            m_data[j] *= 2;
            endResetModel();

            beginMoveRows(QModelIndex(), j, j, QModelIndex(), j + 2);
            std::swap(m_data[j], m_data[j + 1]);
            endMoveRows();
          }
        }
      }
    }
  }

  printData();
  return (true);
}

bool
Game2048Model::moveUp()
{
  if (!m_isAnimationEnable)
    return false;

#ifdef FOR_TEST
  timerAnimation();
#endif

  for (int i{ 0 }; i < m_size; ++i) {
    if (m_data[i] != 0) {
      for (int j{ i }; j > 0; j -= m_deep) {
        int r{ row(j) };
        if (r > 0 && r < m_deep) {

          if (m_data[j - m_deep] == 0 && m_data[j] != 0) {
            beginMoveRows(QModelIndex(), j, j, QModelIndex(), j - m_deep);
            std::swap(m_data[j], m_data[j - m_deep]);
            endMoveRows();
          }

          if (m_data[j - m_deep] == m_data[j]) {
            beginResetModel();
            m_data[j - m_deep] = 0;
            m_data[j] *= 2;
            endResetModel();

            beginMoveRows(QModelIndex(), j, j, QModelIndex(), j - m_deep);
            std::swap(m_data[j], m_data[j - m_deep]);
            endMoveRows();
          }
        }
      }
    }
  }

  printData();
  return (true);
}

// 0  1  2  3
// 4  5  6  7
// 8  9 10 11
// 12 13 14 15

// 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15

bool
Game2048Model::moveDown()
{
  if (!m_isAnimationEnable)
    return false;

#ifdef FOR_TEST
  timerAnimation();
#endif

  for (int i{ m_size - 1 }; i >= 0; --i) {
    int r{ 0 };
    if (m_data[i] != 0) {
      for (int j{ i }; j < m_size; ++j) {
        r = row(j);
        if (r >= 0 && r < m_deep - 1) {

          if (m_data[j + m_deep] == 0 && m_data[j] != 0) {
            beginMoveRows(QModelIndex(), j, j, QModelIndex(), j + m_deep);
            std::swap(m_data[j], m_data[j + m_deep]);
            endMoveRows();
          }

          if (m_data[j + m_deep] == m_data[j] && m_data[j] != 0) {
            beginResetModel();
            m_data[j + m_deep] = 0;
            m_data[j] *= 2;
            endResetModel();

            beginMoveRows(QModelIndex(), j, j, QModelIndex(), j + m_deep);
            std::swap(m_data[j], m_data[j + m_deep]);
            endMoveRows();
          }
        }
      }
    }
  }

  printData();
  return (true);
}

int
Game2048Model::size() const
{
  return m_size;
}

int
Game2048Model::occupiedCells()
{
  int nCells{ 0 };

  for (int i{ 0 }; i < m_size; ++i) {
    if (m_data[i] != 0)
      ++nCells;
  }

  return (nCells);
}

int
Game2048Model::freeCells()
{
  int nCells{ 0 };

  for (int i{ 0 }; i < m_size; ++i) {
    if (m_data[i] == 0)
      ++nCells;
  }

  return (nCells);
}

bool
Game2048Model::addRandomTile()
{
  if (freeCells() >= 1) {
    m_data[freeRandomPlace()] = beginRandomNumber();
    return (true);
  }
  return (false);
}

bool
Game2048Model::addTile(int place_, int value_)
{
  if (place_ < 0 or place_ >= m_size)
    return (false);

  if (m_data[place_] == 0) {
    m_data[place_] = value_;
    return (true);
  }
  return (false);
}

void
Game2048Model::printData()
{
  QTextStream stream(stdout);

  for (int i{ 0 }; i < m_size; ++i) {
    if (i % 4 != 0 && i != 0) {
      stream << (m_data[i]);
    } else {
      stream << '\n' << m_data[i];
    }
  }

  stream << '\n';
  stream << '\n';

  stream.readAll();
}

int
Game2048Model::value(int value_)
{
  return (m_data[value_]);
}

void
Game2048Model::clearBoard()
{
  for (int i{ 0 }; i < m_size; ++i)
    m_data[i] = 0;
}

int
Game2048Model::row(int number_)
{
  return (number_ / m_deep);
}

int
Game2048Model::column(int number_)
{
  return (number_ % m_deep);
}

bool
Game2048Model::timerAnimation()
{
  m_isAnimationEnable = false;
  m_timer->singleShot(200, [&]() { m_isAnimationEnable = true; });
  return (true);
}

}
