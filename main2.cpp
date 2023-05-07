#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"

int main()
{
  const int T = 4;
  const int infinity = 1000000;

  std::vector<std::vector<std::pair<int, int>>> adj = {
      {{0, 0}, {1, 2}, {1, 2}, {0, 0}},
      {{0, 0}, {0, 0}, {1, 2}, {2, 3}},
      {{0, 0}, {0, 0}, {0, 0}, {1, 2}},
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
  };

  std::vector<std::pair<int, int>> nodes = {
    {{3, 5}, {4, 8}, {3, 20}, {0, infinity}}
  };
    
  const int dynamic_net_size = nodes.size() * (T + 1) + 2;

  std::vector<std::vector<int>> capacity(dynamic_net_size, std::vector<int>(std::vector<int>(dynamic_net_size)));
  std::vector<int> node_id(dynamic_net_size);

  node_id[0] = 0;
  for (int i = 0; i < 3; ++i)
  {
    capacity[0][i + 1] = nodes[i].first;
  }

  int initial_node_nr = 1;
  int t = 0;
  for (int i = 1; i < dynamic_net_size; ++i)
  {
    if (i % adj.size() == 0)
    {
      ++t;
      initial_node_nr = 1;
    }
    else 
    {
      node_id[i] = initial_node_nr*10 + t;
      if (t < T)
      {
        const auto& initial_node_nr_id = initial_node_nr - 1;
        capacity[i][i + T] = nodes[initial_node_nr_id].second;

        for (int j = 0; j < adj.size(); ++j)
        {
          if (adj[initial_node_nr_id][j].first != 0)
          {
            const auto& time = adj[initial_node_nr_id][j].first;
            if (t + time <= T)
            {
              const auto& cap = adj[initial_node_nr_id][j].second;
              capacity[i][i + time * T + (j - initial_node_nr_id)] = cap;
            }
          }
          
        }
      }
      ++initial_node_nr;
    }
  }

  //nodes and arcs to sink
  t = 1;
  node_id[T] = adj.size() * 10;
  const auto& sink_id = dynamic_net_size - 1;
  for (int i = 2 * T; i <= (T + 1) * T; i += T)
  {
    node_id[i] = adj.size() * 10 + t;
    capacity[i][sink_id] = infinity;
    ++t;
  }
  node_id[sink_id] = adj.size() + 1;

//   for (int i = 0; i < capacity.size(); ++i)
//   {
//     std::cout << "id: " << node_id[i] << std::endl;
//     for (int j = 0; j < capacity.size(); ++j)
//     {
//         if (capacity[i][j] != 0)
//         {
//             std::cout << "adj: " << j << ", id:" << node_id[j] << std::endl;
//             std::cout << "capacity: " << capacity[i][j] << std::endl;
//         }

//     }
//     std::cout << std::endl;
//   }

  Graph graph(capacity, 0, sink_id);
  graph.saveToFile();
  FordFulkerson fordFulkerson;
  std::cout << fordFulkerson.computeMaxFlow(graph) << std::endl;
  graph.saveFlowToFile();

//   graph.printVec(graph.capacity);  
//   graph.printVec(graph.flow);

  t = 1;
  for (int i = 2 * T; i <= (T + 1) * T; i += T)
  {
    if (graph.flow[i][sink_id] != 0)
    {
        std::cout << "id: " << node_id[i] 
            << " - " << graph.flow[i][sink_id] << " people " 
            << "evacuated in " << t * 5 << "s" << std::endl;
        std::cout << std::endl;
    }
    ++t;
  }
}