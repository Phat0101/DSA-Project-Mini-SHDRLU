#include <iostream>
#include <queue>
#include <stack>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

#include "State.h"
#include "StateDynamic.h"
#include "Goal.h"
#include "Solver.h"
#include "Action.h"

void inputGoals(State s, vector<Goal> &goals, bool flag)
{ // flag = true: disjunctive
  string next;
  while (next != "s")
  {
    int block, row, col;
    cout << "Input a goal in the format (block, row, col): " << endl;
    cout << "Block: ";
    cin >> block;
    cout << "Row (bottom-up): ";
    cin >> row;
    row = s.returnGridSize() - 1 - row;
    cout << "Col (left-right):";
    cin >> col;
    Goal g(block, row, col);
    goals.push_back(g);
    Solver so(s, goals, flag);
    if (so.catchError())
    {
      cout << "Type 'g' to continue, s to stop\n";
      cin >> next;
    }
    else
    {
      goals.pop_back();
      cout << "Please reenter your goal!" << endl;
      next = "g";
    }
  }
  cout << "Your goals are: \n";
  for (int i = 0; i < goals.size(); i++)
  {
    cout << "(" << goals[i].block << ", " << s.returnGridSize() - goals[i].row - 1 << ", " << goals[i].col << ")\n";
  };
}

void reorderGoals(vector<Goal> &goals)
{
  for (int i = 0; i < goals.size() - 1; i++)
  {
    for (int j = i + 1; j < goals.size(); j++)
    {
      if (goals[j] < goals[i])
      {
        Goal temp(goals[i].block, goals[i].row, goals[i].col);
        goals[i] = goals[j];
        goals[j] = temp;
      }
    }
  }
}

int main()
{
  srand(time(0));
  int choice = 0;
  int size, numberOfBlocks;
  cout << "1. Single goal solver without Heuristic\n"
       << "2. Single goal solver with Heuristic\n"
       << "3. Disjunctive goal solver\n"
       << "4. Conjunctive goal solver\n"
       << "5. A star algorithm\n";
  cin >> choice;
  cout << "Input board size: ";
  cin >> size;
  cout << "Input number of blocks: ";
  cin >> numberOfBlocks;
  State s(size, numberOfBlocks);
  s.pushDown();
  s.printBoard();
  vector<Goal> goals;
  if (choice == 4)
  {
    inputGoals(s, goals, false);
  }
  else
  {
    inputGoals(s, goals, true);
  }
  reorderGoals(goals);
  priority_queue<Action> actions;
  if (choice == 4)
  {
    Solver so(s, goals, false);
    so.conjunctiveGoalWithHeuristic(s, actions, goals);
  }
  else
  {
    Solver so(s, goals, true);
    if (choice == 1)
      so.singleGoalWithoutHeuristic(s, goals);
    if (choice == 2) {
      so.singleGoalWithHeuristic(s, actions, goals);
      so.print(goals[0]);
    }
    if (choice == 3)
      so.disjunctiveGoalWithHeuristic(s, actions, goals);
    if (choice == 5)
      so.aStarAlgo(s, goals);
  }
  char any;
  cout << "\nEnter anything to stop: ";
  cin >> any;
  return 0;
}