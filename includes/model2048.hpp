/* model2048.hpp */

#ifndef MODEL_2048_HPP
#define MODEL_2048_HPP

#include <QObject>

#include "game2048model.hpp"
#include <QAbstractListModel>

class Model2048 : public Game::Game2048Model
{
  Q_OBJECT
public:
  Model2048(int deep_ = 4, QObject* parent = nullptr);
  virtual ~Model2048();

  // QAbstractItemModel interface
public:
protected:
private:
};
#endif // MODEL_2048_HPP
