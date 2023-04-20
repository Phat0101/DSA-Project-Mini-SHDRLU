#ifndef ACTION_H_
#define ACTION_H_
#include "State.h"
#include "Goal.h"
class Action
{
public:
  int source;
  int destination;
  int heuristic;
  Action(int s, int d) : source(s), destination(d){};
  bool operator<(const Action a) const;
  void calculateHeuristic(State s, Goal g);
  int blocksAboveCurrent(State s, int block); // add to heuristic
  int blocksAboveGoal(State s, Goal g);       // add to heuristic
  int EmptyBlocksBelowGoal(State s, Goal g);  // add to heuristic
  int currentBelowGoal(State s, Goal g);
};

int Action::blocksAboveCurrent(State s, int block)
{
  int r, c, counter;
  for (int i = 0; i < s.returnGridSize(); i++)
  {
    for (int j = 0; j < s.returnGridSize(); j++)
    {
      if (s.returnBlockAtLocation(i, j) == block)
      {
        r = i;
        c = j;
        break;
      }
    }
  }
  if (r == 0)
    return 0;
  counter = 0;
  int i = 0;
  while (i < r)
  {
    if (s.returnBlockAtLocation(i, c) != 0)
      counter++;
    i++;
  }
  return counter;
}

int Action::blocksAboveGoal(State s, Goal g)
{
  int counter = 0;
  int i = 0;
  while (i <= g.row)
  {
    if (s.returnBlockAtLocation(i, g.col) != 0)
      counter++;
    i++;
  }
  return counter;
};

int Action::EmptyBlocksBelowGoal(State s, Goal g)
{
  int counter = 0;
  int i = s.returnGridSize() - 1;
  while (i > g.row)
  {
    if (s.returnBlockAtLocation(i, g.col) == 0)
      counter++;
    i--;
  }
  return counter;
}

int Action::currentBelowGoal(State s, Goal g)
{
  int counter = 0;
  for (int i = g.row; i < s.returnGridSize(); i++)
  {
    if (s.returnBlockAtLocation(i, g.col) == g.block)
    {
      return counter;
    }
    counter++;
  }
  return 0;
}

bool Action::operator<(const Action a) const
{
  return (heuristic > a.heuristic);
};

void Action::calculateHeuristic(State s, Goal g)
{
  if (s.returnBlockAtLocation(g.row, g.col) == g.block)
  {
    heuristic = 0;
    return;
  }
  int h = 1;
  h += blocksAboveCurrent(s, g.block);
  h += blocksAboveGoal(s, g);
  h += EmptyBlocksBelowGoal(s, g);
  h += currentBelowGoal(s, g);

  heuristic = h;
};
#endif