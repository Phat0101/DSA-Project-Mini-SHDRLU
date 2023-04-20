#ifndef GOAL_H_
#define GOAL_H_
class Goal
{
public:
  int block, row, col;
  Goal(int b, int r, int c)
  {
    block = b;
    row = r;
    col = c;
  };
  bool operator<(const Goal &c) const
  {
    return row > c.row;
  }
  bool operator==(const Goal &c) const
  {
    return (row == c.row && col == c.col);
  }
};
#endif