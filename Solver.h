#ifndef SOLVER_H_
#define SOLVER_H_
#include "State.h"
#include "Goal.h"
#include "Action.h"
class Solver
{
private:
  State currentState;
  vector<Goal> goals;
  priority_queue<Action> actionsWithHeuristic;
  bool flagh = false;
  unordered_set<State, StateHasher> visitedStates = {};
  vector<State> recordedStates = {};   // actual result for printing
  vector<Action> recordedActions = {}; // actual result for printing
  vector<int> recordedH = {};          // actual result for printing
  priority_queue<Action> actions;
  bool flag = true; // assumed disjunctive = true; conjunctive = false;
public:
  Solver(State s, vector<Goal> g, bool f) : currentState(s)
  {
    goals = g;
    flag = f;
  };
  void availableActions(State s, vector<Action> &actions);
  void availableActionsWithHeuristic(State s, priority_queue<Action> &actions, vector<Goal> g);
  bool catchError() const;
  bool checkGoals(State s, vector<Goal> gs);
  void singleGoalWithoutHeuristic(State s, vector<Goal> g);
  void singleGoalWithHeuristic(State s, priority_queue<Action> actions, vector<Goal> g);
  void print()
  {
    for (int i = 0; i < recordedStates.size(); i++)
    {
      cout << endl
           << recordedActions[i].source << " -> " << recordedActions[i].destination
           << " with h= " << recordedH[i];
      recordedStates.at(i).printBoard();
    }
    cout << "Found in " << recordedStates.size() << " steps";
  }
};

void Solver::availableActions(State s, vector<Action> &actions)
{
  vector<Action> acts;
  for (int i = 0; i < s.returnGridSize(); i++)
  {
    for (int j = 0; j < s.returnGridSize(); j++)
    {
      State a(s);
      if (i != j)
      {
        if (a.moveBlock(i, j))
        {
          Action act(i, j);
          acts.push_back(act);
        }
      }
    }
  }
  actions = acts;
};

void Solver::availableActionsWithHeuristic(State s, priority_queue<Action> &actions, vector<Goal> g)
{
  while (!actions.empty())
  {
    actions.pop();
  };
  for (int i = 0; i < s.returnGridSize(); i++)
  {
    for (int j = 0; j < s.returnGridSize(); j++)
    {
      State a(s);
      if (i != j)
      {
        if (a.moveBlock(i, j))
        {
          Action act(i, j);
          act.calculateHeuristic(a, g.at(0));
          actions.push(act);
        }
      }
    }
  }
};

bool Solver::checkGoals(State s1, vector<Goal> gs)
{
  State s(s1);
  // disjunctive
  if (flag)
  {
    for (int i = 0; i < gs.size(); i++)
    {
      if (s.returnBlockAtLocation(gs.at(i).row, gs.at(i).col) == gs.at(i).block)
        return true;
    }
    return false;
  }
  else
  { // conjunctive
    for (int i = 0; i < gs.size(); i++)
    {
      if (s.returnBlockAtLocation(gs.at(i).row, gs.at(i).col) != gs.at(i).block)
        return false;
    }
    return true;
  }
}

bool Solver::catchError() const
{
  for (int i = 0; i < goals.size(); i++)
  {
    // if block does not exist
    if (goals.at(i).block > currentState.returnNumberOfBlock() || goals.at(i).block < 1)
    {
      cout << "Block is out of designed game!" << endl;
      return false;
    }
    // check if destination is out of range
    if (goals.at(i).col < 0 || goals.at(i).row < 0 || goals.at(i).col > currentState.returnGridSize() || goals.at(i).col > currentState.returnGridSize())
    {
      cout << "Destination is out of board size!" << endl;
      return false;
    }
    // check duplicate conjuctive goal
    if (!flag)
    {
      for (int i = 0; i < goals.size(); i++)
      {
        int totalSameGoal = 0;
        int totalSameBlock = 0;
        for (int j = 0; j < goals.size(); j++)
        {
          if (goals.at(j) == goals.at(i))
            totalSameGoal++;
          if (goals.at(i).block == goals.at(j).block)
            totalSameBlock++;
        }
        if (totalSameGoal > 1)
        {
          cout << "Duplicate destinations for different blocks!" << endl;
          return false;
        }
        if (totalSameBlock > 1)
        {
          cout << "Duplicate blocks for different destinations!" << endl;
          return false;
        }
      }
    }
  }
  return true;
};

void Solver::singleGoalWithoutHeuristic(State s, vector<Goal> g)
{
  bool flag = false;
  bool breakLoop = false;
  unordered_set<State, StateHasher> visitedStates = {s};
  vector<Action> actions;
  State a(s);
  int step = 0;
  int time = 0;
  while (time < 100 && !flag)
  {
    breakLoop = false;
    availableActions(a, actions);
    int randomAction = rand() % actions.size();
    State b(a);
    b.moveBlock(actions[randomAction].source, actions[randomAction].destination);
    if (!visitedStates.count(b))
    {
      visitedStates.insert(b);
      cout << endl
           << actions[randomAction].source << " -> " << actions[randomAction].destination;
      b.printBoard();
      if (checkGoals(b, g))
      {
        cout << "Found with " << step << " steps!!!";
        flag = true;
      }
      step++;
      a.moveBlock(actions[randomAction].source, actions[randomAction].destination);
    };
    time++;
  }
  if (!flag)
    cout << "Not Found!!!";
}

void Solver::singleGoalWithHeuristic(State s, priority_queue<Action> actions, vector<Goal> g)
{
  if (checkGoals(s, g))
    flagh = true;
  if (flagh)
    return;

  if (visitedStates.count(s))
  {
    return;
  }
  else
  {
    availableActionsWithHeuristic(s, actions, g);
  }
  visitedStates.insert(s);
  while (!actions.empty())
  {
    State a(s);
    if (a.moveBlock(actions.top().source, actions.top().destination))
    {
      Action act(actions.top().source, actions.top().destination);
      recordedActions.push_back(act);
      recordedStates.push_back(a);
      recordedH.push_back(actions.top().heuristic);
      singleGoalWithHeuristic(a, actions, g);
      if (flagh)
        return;
      recordedStates.pop_back();
      recordedActions.pop_back();
      recordedH.pop_back();
    };
    actions.pop();
  };
}
#endif