#include <functional>
#include <iostream>
using namespace std;

class MyClass
{
public:
  int arr[10][10];
  int n;

  bool operator==(const MyClass &other) const
  {
    // Check if the two arrays are equal
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        if (arr[i][j] != other.arr[i][j])
        {
          return false;
        }
      }
    }
    return true;
  }
};

struct MyClassHasher
{
  std::size_t operator()(const MyClass &obj) const
  {
    std::size_t hash = 0;
    for (int i = 0; i < obj.n; ++i)
    {
      for (int j = 0; j < obj.n; ++j)
      {
        hash ^= std::hash<int>{}(obj.arr[i][j]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
      }
    }
    return hash;
  }
};

int main()
{
  MyClass obj;
  obj.n = 3;
  obj.arr[0][0] = 1;
  obj.arr[0][1] = 2;
  obj.arr[0][2] = 3;
  obj.arr[1][0] = 4;
  obj.arr[1][1] = 5;
  obj.arr[1][2] = 6;
  obj.arr[2][0] = 7;
  obj.arr[2][1] = 8;
  obj.arr[2][2] = 9;

  MyClassHasher hasher;
  std::size_t hashValue = hasher(obj);
  std::cout << "Hash value: " << hashValue << std::endl;

  return 0;
}