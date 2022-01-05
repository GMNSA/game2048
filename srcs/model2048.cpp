/* game2048model.cpp */

#include "model2048.hpp"
#include <QDebug>
#include <random>

Model2048::Model2048(int deep_, QObject* parent)
  : Game::Game2048Model(deep_, parent)
{}

Model2048::~Model2048()
{
  // dtor
}
