/* game2048logic.cpp */

#include "game2048logic.hpp"
#include <QDebug>
#include <QQmlComponent>
#include <QQuickItem>

Game2048Logic::Game2048Logic(int deep_, QObject* parent)
  : QObject(parent)
  , m_deep(deep_)
{
  auto t = QObject::metaObject();
  qDebug() << "1: " << t->classInfo(1).name();
  qDebug() << "className: " << t->className();
}

Game2048Logic::~Game2048Logic()
{
  // dtor
}

int
Game2048Logic::deep() const
{
  return m_deep;
}

void
Game2048Logic::setDeep(int deep)
{
  m_deep = deep;
}

void
Game2048Logic::init(QObject* item_)
{
  Q_UNUSED(item_);

  // QQuickItem* obj = qobject_cast<QQuickItem*>(item_);
  // auto lst = item_->children();

  // for (auto& l : lst)
  //   qDebug() << "lst: " << l;

  // if (obj)
  //   qDebug("OK");
  // else
  //   qDebug("False");
}
