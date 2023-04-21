// #include <iostream>
// #include <vector>
// #include <queue>
// #include <unordered_map>
// #include <functional>

// using namespace std;

// struct Node
// {
//   int x, y;
//   int g_score, f_score;
//   Node *parent;
//   Node(int x, int y) : x(x), y(y), g_score(0), f_score(0), parent(nullptr) {}
// };

// struct CompareFScore
// {
//   bool operator()(Node *const &a, Node *const &b)
//   {
//     return a->f_score > b->f_score;
//   }
// };

// vector<Node *> AStarSearch(Node *start, Node *goal, unordered_map<Node *, vector<Node *>> &graph, function<int(Node *, Node *)> heuristic)
// {
//   vector<Node *> path;

//   priority_queue<Node *, vector<Node *>, CompareFScore> pq;
//   unordered_map<Node *, int> g_scores;
//   unordered_map<Node *, int> f_scores;
//   unordered_map<Node *, Node *> parents;

//   pq.push(start);
//   g_scores[start] = 0;
//   f_scores[start] = heuristic(start, goal);

//   while (!pq.empty())
//   {
//     Node *current = pq.top();
//     pq.pop();

//     if (current == goal)
//     {
//       while (current != nullptr)
//       {
//         path.push_back(current);
//         current = parents[current];
//       }
//       reverse(path.begin(), path.end());
//       break;
//     }

//     for (Node *neighbor : graph[current])
//     {
//       int tentative_g_score = g_scores[current] + 1;
//       if (!g_scores.count(neighbor) || tentative_g_score < g_scores[neighbor])
//       {
//         g_scores[neighbor] = tentative_g_score;
//         f_scores[neighbor] = tentative_g_score + heuristic(neighbor, goal);
//         parents[neighbor] = current;
//         neighbor->g_score = tentative_g_score;
//         neighbor->f_score = f_scores[neighbor];
//         pq.push(neighbor);
//       }
//     }
//   }

//   return path;
// }

// int main()
// {
//   Node *start = new Node(0, 0);
//   Node *goal = new Node(4, 4);

//   unordered_map<Node *, vector<Node *>> graph;
//   for (int i = 0; i < 5; i++)
//   {
//     for (int j = 0; j < 5; j++)
//     {
//       Node *node = new Node(i, j);
//       if (i > 0)
//         graph[node].push_back(new Node(i - 1, j));
//       if (i < 4)
//         graph[node].push_back(new Node(i + 1, j));
//       if (j > 0)
//         graph[node].push_back(new Node(i, j - 1));
//       if (j < 4)
//         graph[node].push_back(new Node(i, j + 1));
//     }
//   }

//   auto heuristic = [](Node *a, Node *b)
//   {
//     return abs(a->x - b->x) + abs(a->y - b->y);
//   };

//   vector<Node *> path = AStarSearch(start, goal, graph, heuristic);

//   if (!path.empty())
//   {
//     for (Node *node : path)
//     {
//       cout << "(" << node->x << ", " << node->y << ") -> ";
//     }
//     cout << "GOAL" << endl;
//   }
//   else
//   {
//     cout << "No path found." << endl;
//   }

//   return 0;
// }

#include <iostream>
#include <queue>
using namespace std;

// Define a class
class MyClass
{
public:
  MyClass(int value) : m_value(value) {}
  int getValue() const { return m_value; }

private:
  int m_value;
};
struct compare
{
  bool operator()(const MyClass *const &a, const MyClass *const &other) const
  {
    // Define the less-than operator
    return a->getValue() > other->getValue();
  }
};
// struct CompareFScore
// {
//   bool operator()(Node *const &a, Node *const &b)
//   {
//     return a->f_score > b->f_score;
//   }
// };
int
main()
{
  // Create a priority queue of MyClass pointers
  priority_queue<MyClass *, vector<MyClass *>, compare> pq;

  // Create some MyClass objects
  MyClass *obj1 = new MyClass(3);
  MyClass *obj2 = new MyClass(1);
  MyClass *obj3 = new MyClass(2);

  // Add the objects to the priority queue
  pq.push(obj1);
  pq.push(obj2);
  pq.push(obj3);

  // Pop the elements from the priority queue and print their values
  while (!pq.empty())
  {
    MyClass *obj = pq.top();
    pq.pop();
    cout << obj->getValue() << endl;
  }

  // Clean up memory
  delete obj1;
  delete obj2;
  delete obj3;

  return 0;
}
