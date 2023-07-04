#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"
#include "MinimumCost.hpp"
#include "AgentModel.hpp"

int main()
{
  const int infinity = 1000000;
  int t = 5;

//////////////////////////////////////////////

  const int T2 = 7;
  t = 6;

  std::vector<std::vector<std::pair<int, int>>> adj2 = {
      {{0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}, {0, 0}},
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {2, 3}, {2, 6}},
      {{0, 0}, {0, 0}, {0, 0}, {2, 3}, {0, 0}, {1, 2}},
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
  };

  std::vector<std::pair<int, int>> nodes2 = {
      {{15, 15}, {10, 15}, {10, 15}, {0, 1}, {0, 1}, {0, infinity}}
  };

  Graph graph2(adj2, nodes2, T2, t);

////////////////////////////////////////////////////////////

  const int T5 = 50;
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
    nodes5[i] = {0, 1}; //{0, 1}; //infinity
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
  adj5[25][20] = {3, 3}; // gdy zakomentowane - zablokowana klatka
  adj5[21][16] = {3, 3};
  adj5[20][26] = {1, 5};
  adj5[16][26] = {1, 5};

  
  Graph graph5(adj5, nodes5, T5, t);

////////////////////////////////////////////   

const int T6 = 50;

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
  nodes6[i] = {0, 1}; //{0, 1}; //infinity
  if (i != 20 and i != 25 and i != 24 and i != 23)
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

Graph graph6(adj6, nodes6, T6, t);

//////////////////////////////////////////////////    

  Graph& graph = graph5;
  // graph.saveInputToFile(adj2, nodes2);
  // graph.saveAdjAndCapacityForNodesToFile();    
  FordFulkerson fordFulkerson;
  std::cout << "Max flow = " << fordFulkerson.computeMaxFlow(graph) << std::endl << std::endl;
  graph.getTimesForFlows();
  graph.printNrPeopleInEachExit();
  graph.saveNrPeopleInEachExitInEachTimeUnit();
  // graph.saveToFile();

/////////////////////////

  // Graph& graph = graph2;
  // MinimumCost minimumCost;
  // std::cout << "Min cost max flow = " << minimumCost.computeMaxFlow(graph) << std::endl << std::endl;
  // graph.getTimesForFlows();
  // graph.printNrPeopleInEachExit();

  // graph3.saveCostToFile();

///////////////////////////////

const int T7 = 30;
t = 6;

std::vector<std::vector<std::pair<int, int>>> adj7 = {
    {{0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {2, 3}, {2, 6}},
    {{0, 0}, {0, 0}, {0, 0}, {2, 3}, {0, 0}, {1, 2}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
};

std::vector<std::pair<int, int>> nodes7 = {
    {{15, 15}, {10, 15}, {10, 15}, {0, 10}, {0, 10}, {0, infinity}}
};

Graph graph7(adj7, nodes7, T7, t);
///////////////////////////////////////

// srand(time(NULL));
// Graph& graph = graph6;
// AgentModel agentModel;
// std::cout << "Max flow = " << agentModel.computeMaxFlow(graph) << std::endl << std::endl;
// graph.getTimesForFlows();
// graph.printNrPeopleInEachExit();
// graph.saveNrPeopleInEachExitInEachTimeUnit();

///////////////////////////////

// srand(time(NULL));
// double sum = 0;
// int iter = 20;
// int initial = 160;
// bool isNotInitial = false;

// for (int i = 0; i < iter; ++i)
// {
//   // Graph graph5(adj5, nodes5, T5, t);
//   Graph graph6(adj6, nodes6, T6, t);
//   Graph& graph = graph6;
//   AgentModel agentModel;
//   int max_flow = agentModel.computeMaxFlow(graph);
//   std::cout << "Max flow = " << max_flow << std::endl << std::endl;
//   int max_time = graph.getTimesForFlows(false);
//   std::cout << "Max time= " <<  max_time << std::endl << std::endl;
//   sum += max_time;
//   if (max_flow != initial)
//   {
//     isNotInitial = true;
//   }
// }
// std::cout << "Mean from " << iter << " runs = " << sum / iter << std::endl;
// std::cout << "isNotInitial " << isNotInitial << std::endl;

}