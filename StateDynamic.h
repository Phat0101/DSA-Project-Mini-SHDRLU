#ifndef STATEDYNAMIC_H_
#define STATEDYNAMIC_H_
using namespace std;

class DynamicState
{
protected:
  int GRID_SIZE;
  int NUMBER_OF_BLOCKS;
  int **grid;

public:
  DynamicState(int size, int n)
  {
    GRID_SIZE = size;
    NUMBER_OF_BLOCKS = n;
    grid = new int *[size];
    for (int i = 0; i < size; i++)
    {
      grid[i] = new int[size];
    }
    int array_size = GRID_SIZE * GRID_SIZE;
    int array[array_size] = {0};
    vector<int> arrayOfPosition = {};
    for (int i = 0; i < array_size; i++)
    {
      arrayOfPosition.push_back(i);
    }
    for (int i = 1; i < NUMBER_OF_BLOCKS + 1; i++)
    {
      int x = rand() % arrayOfPosition.size();
      int ri = arrayOfPosition.at(x);
      arrayOfPosition.erase(arrayOfPosition.begin() + x);
      array[ri] = i;
    }
    for (int i = 0; i < GRID_SIZE; i++)
    {
      for (int j = 0; j < GRID_SIZE; j++)
      {
        grid[i][j] = array[i * GRID_SIZE + j];
      }
    }
  }

  ~DynamicState()
  {
    for (int i = 0; i < GRID_SIZE; i++)
    {
      delete[] grid[i];
    }
    delete[] grid;
  }
};
#endif