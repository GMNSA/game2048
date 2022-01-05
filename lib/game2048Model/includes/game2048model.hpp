#ifndef GAME_2048_MODEL_HPP
#define GAME_2048_MODEL_HPP

#include <QObject>

#include <QAbstractListModel>

class QTimer;

namespace Game {

class Game2048Model : public QAbstractListModel
{
  Q_OBJECT
public:
  Game2048Model(int deep_ = 4, QObject* parent = nullptr);
  virtual ~Game2048Model();

  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex& parent) const override;
  virtual QVariant data(const QModelIndex& index, int role) const override;

  Q_INVOKABLE void init();
  Q_INVOKABLE bool reset();
  Q_INVOKABLE bool moveLeft();
  Q_INVOKABLE bool moveRight();
  Q_INVOKABLE bool moveUp();
  Q_INVOKABLE bool moveDown();
  Q_INVOKABLE void add()
  {
    beginResetModel();
    addRandomTile();
    endResetModel();
  }

protected:
private:
  int m_deep;
  int m_size;
  QVector<int> m_data;

  QTimer* m_timer;
  bool m_isAnimationEnable;

#ifndef FOR_TEST
private:
#else
public:
#endif // FOR_TEST
  int randomNumber(int begin_, int end_);
  int prepareGame();

  int freeRandomPlace();
  int beginRandomNumber();
  void clearBoard();

  int row(int number_);
  int column(int number_);

  bool timerAnimation();
  int size() const;
  int occupiedCells();
  int freeCells();

  bool addRandomTile();
  bool addTile(int place_, int value_);
  void printData();
  int value(int value_);
};
}

#endif // GAME_2048_MODEL_HPP
