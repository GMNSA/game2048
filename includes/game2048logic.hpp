/* game2048logic.hpp */

#ifndef GAME2048LOGIC_HPP
#define GAME2048LOGIC_HPP

#include <QQuickItem>

class Game2048Logic : public QObject
{
  Q_OBJECT
  Q_CLASSINFO("Version", "Game2048LogicV1.0")
public:
  Game2048Logic(int deep_ = 4, QObject* parent = nullptr);
  virtual ~Game2048Logic();

  int deep() const;
  void setDeep(int deep);

  Q_INVOKABLE void init(QObject* item_);

signals:
  void clicked();
  void pressed();

protected:
private:
  int m_deep;
};

#endif // GAME2048LOGIC_HPP
