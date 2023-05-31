#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"
#include "MinimumCost.hpp"

int main()
{
    std::vector<std::vector<int>> cap5 {
    {0, 6, 1, 0, 0, 0},
    {0, 0, 0, 5, 0, 1},
    {0, 0, 0, 0, 5, 6},
    {0, 0, 5, 0, 0, 0},
    {0, 5, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
  };
  std::vector<std::vector<int>> time5 {
    {0, 3, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 1, 3},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
  };
  int T5 = 7;
  Graph graph5(cap5, 0, 5, time5, T5);

////////////////////////////////////

 std::vector<std::vector<std::pair<int, int>>> adj2 = {
        {{0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {2, 3}, {2, 6}},
        {{0, 0}, {0, 0}, {0, 0}, {2, 3}, {0, 0}, {1, 2}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
    };

  int newSize = adj2.size() + 1;
  std::vector<std::vector<int>> cap2(newSize, std::vector<int>(newSize));
  std::vector<std::vector<int>> time2(newSize, std::vector<int>(newSize));

  for (int i = 0; i < newSize; ++i)
  {
    for (int j = 0; j < newSize; ++j)
    {
        if (i == 0 and j > 0 and j < 4)
        {
            for (int k = 0; k < newSize; ++k)
            {
                if (adj2[j - 1][k].second != 0)
                {
                    cap2[i][j] = adj2[j - 1][k].second;
                }
            }
        }
        else if (i > 0 and j > 0)
        {
            cap2[i][j] = adj2[i - 1][j - 1].second;
            time2[i][j] = adj2[i - 1][j - 1].first;
        }
    }
  }
  int T2 = 7;
  Graph graph2(cap2, 0, 6, time2, T2);
//   graph2.printVec(cap2);


///////////////////////////////////

  Graph& graph = graph2;
  MinimumCost minimumCost;
  
  std::cout << "Min cost static flow = " << minimumCost.computeMaxFlow(graph) << std::endl << std::endl;
  graph.saveFlowToFile();
  std::cout << "Max dynamic flow = " << minimumCost.maxDynamicFlow << std::endl << std::endl;
}