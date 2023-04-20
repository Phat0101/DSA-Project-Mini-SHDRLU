
#ifndef STATE_H_
#define STATE_H_
#include "StateDynamic.h"

class State : public DynamicState
{
public:
  State(int s, int b) : DynamicState(s, b){};
  State(const State &other) : DynamicState(other.GRID_SIZE, other.NUMBER_OF_BLOCKS)
  {
    // Copy grid data members
    for (int i = 0; i < GRID_SIZE; i++)
    {
      for (int j = 0; j < GRID_SIZE; j++)
      {
        grid[i][j] = other.grid[i][j];
      }
    }
  }
  void printBoard();
  void pushDown();
  int removeBlockFrom(int column);
  bool insertBlockTo(int column, int value);
  bool moveBlock(int source, int destination);
  bool operator==(const State &s) const;
  bool operator!=(const State &s) const;
  int returnNumberOfBlock() const;
  int returnGridSize() const;
  int returnBlockAtLocation(int row, int col) const;
};

int State::returnNumberOfBlock() const
{
  return NUMBER_OF_BLOCKS;
}
int State::returnGridSize() const
{
  return GRID_SIZE;
}

int State::returnBlockAtLocation(int row, int col) const
{
  return grid[row][col];
};

bool State::operator==(const State &s) const
{
  for (int i = 0; i < GRID_SIZE; i++)
    for (int j = 0; j < GRID_SIZE; j++)
      if (s.grid[i][j] != grid[i][j])
        return false;
  return true;
}

bool State::operator!=(const State &s) const
{
  for (int i = 0; i < GRID_SIZE; i++)
    for (int j = 0; j < GRID_SIZE; j++)
      if (s.grid[i][j] != grid[i][j])
        return true;
  return false;
}

void State::printBoard()
{
  cout << endl;

  for (int i = 0; i < GRID_SIZE; i++)
  {
    cout << "|";
    for (int j = 0; j < GRID_SIZE; j++)
    {
      if (grid[i][j] > 9)
      {
        cout << " " << grid[i][j] << " |";
      }
      else
      {
        cout << "  " << grid[i][j] << " |";
      }
    }
    cout << endl;
  }
}

void State::pushDown()
{
  for (int i = 0; i < GRID_SIZE; i++)
  {
    stack<int> s;
    for (int j = 0; j < GRID_SIZE; j++)
    {
      if (grid[j][i] != 0)
        s.push(grid[j][i]);
    }
    for (int j = GRID_SIZE - 1; j >= 0; j--)
    {
      if (!s.empty())
      {
        grid[j][i] = s.top();
        s.pop();
      }
      else
      {
        grid[j][i] = 0;
      }
    }
  }
}

int State::removeBlockFrom(int column)
{
  for (int i = 0; i < GRID_SIZE; i++)
  {
    if (grid[i][column] != 0)
      return grid[i][column];
  }
  return -1;
}

bool State::insertBlockTo(int column, int value)
{
  int x = GRID_SIZE;
  for (int i = 0; i < GRID_SIZE; i++)
  {
    if (grid[i][column] != 0)
    {
      x = i;
      break;
    }
  }
  if (x == 0)
    return false;
  else
  {
    grid[x-1][column] = value;
    return true;
  }
}

bool State::moveBlock(int source, int destination)
{
  int value = removeBlockFrom(source);
  if (value == -1)
    return false;
  if (insertBlockTo(destination, value))
  {
    int i = 0;
    while (grid[i][source] != value)
    {
      i++;
    }
    grid[i][source] = 0;
    return true;
  };
  return false;
}

struct StateHasher
{
  std::size_t operator()(const State &obj) const
  {
    std::size_t hash = 0;
    for (int i = 0; i < obj.returnGridSize(); i++)
    {
      for (int j = 0; j < obj.returnGridSize(); j++)
      {
        hash ^= std::hash<int>{}(obj.returnBlockAtLocation(i, j)) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
      }
    }
    return hash;
  }
};

#endif