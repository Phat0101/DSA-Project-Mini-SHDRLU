#ifndef SOLVER_H_
#define SOLVER_H_
#include "State.h"
#include "Goal.h"
#include "Action.h"

class SearchNode
{
public:
  State state;
  int gn = 0;
  int fn;
  SearchNode *parent = nullptr;
  SearchNode(State s) : state(s){};
};

struct compare
{
  bool operator()(const SearchNode *const &a, const SearchNode *const &b) const
  {
    return (a->fn > b->fn);
  }
};

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
  void disjunctiveGoalWithHeuristic(State s, priority_queue<Action> actions, vector<Goal> g);
  void conjunctiveGoalWithHeuristic(State s, priority_queue<Action> actions, vector<Goal> g);
  void aStarAlgo(State s, vector<Goal> g);
  void print(Goal recordedGoal)
  {
    for (int i = 0; i < recordedStates.size(); i++)
    {
      cout << endl
           << recordedActions[i].source << " -> " << recordedActions[i].destination
           << " with h= " << recordedH[i];
      recordedStates.at(i).printBoard();
    }
    cout << "Goal (" << recordedGoal.block << ", "
         << currentState.returnGridSize() - 1 - recordedGoal.row << ", "
         << recordedGoal.col
         << ") was found in " << recordedStates.size() << " steps";
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

void Solver::disjunctiveGoalWithHeuristic(State s, priority_queue<Action> actions, vector<Goal> g)
{
  for (int i = 0; i < g.size(); i++)
  {
    vector<Goal> go = {};
    go.push_back(g.at(i));
    availableActionsWithHeuristic(s, actions, go);
    singleGoalWithHeuristic(s, actions, go);
    if (recordedStates.size() < 100)
    {
      print(go[0]);
      break;
    }
    else
    {
      recordedStates.clear();
      recordedActions.clear();
      recordedH.clear();
    }
  }
}

void Solver::conjunctiveGoalWithHeuristic(State s, priority_queue<Action> actions, vector<Goal> g)
{
  vector<Goal> go = {};
  for (int i = 0; i < g.size(); i++)
  {
    go.insert(go.begin(), g.at(i));
    if (i == 0)
    {
      singleGoalWithHeuristic(s, actions, go);
    }
    else
    {
      State a(recordedStates.back());
      recordedStates.clear();
      recordedH.clear();
      recordedActions.clear();
      singleGoalWithHeuristic(a, actions, go);
    }
    flagh = false;
    print(go[0]);
    cout << endl;
  }
};

void Solver::aStarAlgo(State s, vector<Goal> g)
{
  priority_queue<SearchNode *, vector<SearchNode *>, compare> searchNodes;
  stack<State> path;
  int steps;
  Action act(1, 1); // arbitrary
  act.calculateHeuristic(s, g[0]);
  SearchNode *se = new SearchNode(s);
  se->fn = act.heuristic;
  searchNodes.push(se);
  while (!searchNodes.empty())
  {
    SearchNode *current = searchNodes.top();
    searchNodes.pop();
    if (checkGoals(current->state, g))
    {
      steps = current->fn;
      while (current != nullptr)
      {
        path.push(current->state);
        current = current->parent;
      }
      break;
    }
    priority_queue<Action> actions;
    availableActionsWithHeuristic(current->state, actions, g);
    while (!actions.empty())
    {
      State a(current->state);
      if (a.moveBlock(actions.top().source, actions.top().destination))
      {
        if (!visitedStates.count(a))
        {
          visitedStates.insert(a);
          act.calculateHeuristic(a, g[0]);
          SearchNode *temp = new SearchNode(a);
          temp->parent = current;
          temp->gn = current->gn + 1;
          temp->fn = act.heuristic + temp->gn;
          searchNodes.push(temp);
        }
      }
      actions.pop();
    }
  }

  while (!path.empty())
  {
    path.top().printBoard();
    path.pop();
  }
  cout << "Found in " << steps << " steps!\n";
}
#endif