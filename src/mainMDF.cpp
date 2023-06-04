#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"
#include "MinimumCost.hpp"

std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>> addNode0(std::vector<std::vector<std::pair<int, int>>> adj, int nrSourceNodes)
{
  int newSize = adj.size() + 1;
  std::vector<std::vector<int>> cap(newSize, std::vector<int>(newSize));
  std::vector<std::vector<int>> time(newSize, std::vector<int>(newSize));

  for (int i = 0; i < newSize; ++i)
  {
    for (int j = 0; j < newSize; ++j)
    {
        if (i == 0 and j > 0 and j <= nrSourceNodes)
        {
            for (int k = 0; k < (newSize - 1); ++k)
            {
                if (adj[j - 1][k].second != 0)
                {
                    cap[i][j] = adj[j - 1][k].second;
                }
            }
        }
        else if (i > 0 and j > 0)
        {
            cap[i][j] = adj[i - 1][j - 1].second;
            time[i][j] = adj[i - 1][j - 1].first;
        }
    }
  }

  return {cap, time};
}

int main()
{

  const int infinity = 1000000;

    std::vector<std::vector<int>> cap0 {
    {0, 6, 1, 0, 0, 0},
    {0, 0, 0, 5, 0, 1},
    {0, 0, 0, 0, 5, 6},
    {0, 0, 5, 0, 0, 0},
    {0, 5, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
  };
  std::vector<std::vector<int>> time0 {
    {0, 3, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 1, 3},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
  };
  int T0 = 7;
  Graph graph0(cap0, 0, 5, time0, T0);

////////////////////////////////////

 std::vector<std::vector<std::pair<int, int>>> adj2 = {
        {{0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {2, 3}, {2, 6}},
        {{0, 0}, {0, 0}, {0, 0}, {2, 3}, {0, 0}, {1, 2}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
    };

  int nrSourceNodes = 3;
  auto [cap2, time2] = addNode0(adj2, nrSourceNodes);
  int T2 = 7;
  Graph graph2(cap2, 0, 6, time2, T2);
//   graph2.printVec(cap2);


///////////////////////////////////

const int T3 = 30;

const int nrPeopleInEachRoom3 = 8;

std::vector<std::vector<std::pair<int, int>>> adj3(29, std::vector<std::pair<int, int>>(29));
std::vector<std::pair<int, int>> nodes3(29);
for (int i = 0; i < 18; ++i)
{
  nodes3[i] = {nrPeopleInEachRoom3, 10};
  if (i < 4)
    adj3[i][i + 18] = {1, 5};
  else if (i < 13)
    adj3[i][i + 14] = {1, 5};
  else if (i < 18)
    adj3[i][i + 10] = {1, 5};
}
for (int i = 18; i < 27; ++i)
{
  nodes3[i] = {0, 1};
  if (i != 22)
  {
    adj3[i][i + 1] = {1, 3};
    if (i < 22)
      adj3[i + 1][i] = {1, 3};
  }
}
nodes3[27] = {0, 1};
nodes3[28] = {0, infinity};
adj3[27][22] = {3, 3};
adj3[22][28] = {1, 5};
adj3[18][28] = {1, 5};

nrSourceNodes = 18;
auto [cap3, time3] = addNode0(adj3, nrSourceNodes);
Graph graph3(cap3, 0, 29, time3, T3);
// graph3.printVec(cap3);

/////////////////////////////////////////////////////   

const int T4 = 30;

const int nrPeopleInEachRoom4 = 8;

std::vector<std::vector<std::pair<int, int>>> adj4(29, std::vector<std::pair<int, int>>(29));
std::vector<std::pair<int, int>> nodes4(29);
for (int i = 0; i < 18; ++i)
{
  nodes4[i] = {nrPeopleInEachRoom4, 10};
  if (i < 2)
    adj4[i][i + 18] = {1, 5};
  else if (i < 4)
    adj4[i][i + 19] = {1, 5};
  else if (i < 11)
    adj4[i][i + 14] = {1, 5};
  else if (i < 13)
    adj4[i][i + 15] = {1, 5};
  else if (i < 18)
    adj4[i][i + 10] = {1, 5};
}
for (int i = 18; i < 25; ++i)
{
  nodes4[i] = {0, 1};
  if (i != 22)
  {
    adj4[i][i + 1] = {1, 3};
    if (i < 22)
      adj4[i + 1][i] = {1, 3};
  }
}

for (int i = 25; i <= 27; ++i)
{
    nodes4[i] = {0, 1};
}
nodes4[28] = {0, infinity};

adj4[26][25] = {1, 3};
adj4[27][26] = {1, 3};
adj4[25][20] = {3, 3};
adj4[22][28] = {1, 5};
adj4[18][28] = {1, 5};

nrSourceNodes = 18;
auto [cap4, time4] = addNode0(adj4, nrSourceNodes);
Graph graph4(cap4, 0, 29, time4, T4);
// graph4.printVec(cap4);

////////////////////////////////////////////

const int T5 = 31;

    const int nrPeopleInEachRoom5 = 10;

    std::vector<std::vector<std::pair<int, int>>> adj5(27, std::vector<std::pair<int, int>>(27));
    std::vector<std::pair<int, int>> nodes5(27);
    for (int i = 0; i < 16; ++i)
    {
      nodes5[i] = {nrPeopleInEachRoom5, 15};
      if (i < 4)
        adj5[i][i + 16] = {1, 5};
      else if (i < 12)
        adj5[i][i + 13] = {1, 5};
      else if (i < 16)
        adj5[i][i + 10] = {1, 5};
    }
    for (int i = 16; i < 26; ++i)
    {
      nodes5[i] = {0, 1};
      if (i != 20 and i != 25)
      {
        adj5[i][i + 1] = {1, 3};
      }
      if (i != 15 and i != 20)
      {
          adj5[i + 1][i] = {1, 3};
      }
    }
    nodes5[26] = {0, infinity};
    // adj5[25][20] = {3, 3};
    adj5[21][16] = {3, 3};
    adj5[20][26] = {1, 5};
    adj5[16][26] = {1, 5};

    nrSourceNodes = 16;
    auto [cap5, time5] = addNode0(adj5, nrSourceNodes);
    Graph graph5(cap5, 0, 27, time5, T5);
    // graph5.printVec(cap5);

//////////////////////////////////////////////    

const int T6 = 18;

const int nrPeopleInEachRoom6 = 10;

std::vector<std::vector<std::pair<int, int>>> adj6(27, std::vector<std::pair<int, int>>(27));
std::vector<std::pair<int, int>> nodes6(27);
for (int i = 0; i < 16; ++i)
{
  nodes6[i] = {nrPeopleInEachRoom6, 15};
  if (i < 2)
    adj6[i][i + 16] = {1, 5};
  else if (i < 4)
    adj6[i][i + 17] = {1, 5};
  else if (i < 10)
    adj6[i][i + 13] = {1, 5};
  else if (i < 12)
    adj6[i][i + 14] = {1, 5};
  else if (i < 16)
    adj6[i][i + 10] = {1, 5};
}

for (int i = 16; i < 26; ++i)
{
  nodes6[i] = {0, 1};
  if (i != 20 and i != 25)
  {
    adj6[i][i + 1] = {1, 3};
  }
  if (i != 15 and i != 20)
  {
    adj6[i + 1][i] = {1, 3};
  }
}
nodes6[26] = {0, infinity};

adj6[23][18] = {3, 3};
adj6[21][16] = {3, 3};
adj6[20][26] = {1, 5};
adj6[16][26] = {1, 5};

nrSourceNodes = 16;
auto [cap6, time6] = addNode0(adj6, nrSourceNodes);
Graph graph6(cap6, 0, 27, time6, T6);
// graph6.printVec(cap6);

/////////////////////////////////////////////////////

  Graph& graph = graph5;
  MinimumCost minimumCost;
  
  std::cout << "Min cost static flow = " << minimumCost.computeMaxFlow(graph) << std::endl << std::endl;
  graph.saveFlowToFile();
  std::cout << "Max dynamic flow = " << minimumCost.maxDynamicFlow << std::endl << std::endl;
}