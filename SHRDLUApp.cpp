#include <iostream>
#include <queue>
#include <stack>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

#include "State.h"
#include "StateDynamic.h"
#include "Goal.h"
#include "Solver.h"
#include "Action.h"

int main()
{
  srand(time(0));
  // for (int i = 0; i < 5; i++)
  // {
  //   State s(5,20);
  //   s.printBoard();
  //   s.pushDown();
  //   s.printBoard();
  //   bool f = s.moveBlock(3, 1);
  //   cout << f << endl;
  //   s.printBoard();
  // }
  State s(3, 6);
  s.pushDown();
  s.printBoard();
  vector<Goal> goals;
  for (int i = 0; i < 1; i++)
  {
    int block, row, col;
    cout << "Input a goal in the format (block, row, col): " << endl;
    cout << "Block: ";
    cin >> block;
    cout << "Row (bottom-up): ";
    cin >> row;
    cout << "Col (left-right):";
    cin >> col;
    Goal g(block, row, col);
    goals.push_back(g);
  }
  Solver so(s, goals, true);
  // so.singleGoalWithoutHeuristic(s,goals);
  priority_queue<Action> actions;
  so.availableActionsWithHeuristic(s, actions, goals);
  so.singleGoalWithHeuristic(s, actions, goals);
  so.print();
  cout << endl;

  // priority_queue<Action> as;
  // for (int i = 0; i < 4; i++)
  // {
  //   Action a;
  //   a.calculateHeuristic(s, goals);
  //   cout << a.heuristic << endl;
  //   as.push(a);
  // }
  // while (!as.empty()) {
  //   cout << as.top().heuristic << endl;
  //   as.pop();
  // }

  // Action a;
  // cout << a.blocksAboveCurrent(s, goals.at(0).block) << endl;
  // cout << a.blocksAboveGoal(s, goals.at(0)) << endl;
  // cout << a.EmptyBlocksBelowGoal(s, goals.at(0));
  // a.calculateHeuristic(s, goals.at(0));
  // cout << a.heuristic;
  return 0;
}