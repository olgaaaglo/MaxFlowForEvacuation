#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"

int main()
{
    std::vector<std::vector<std::vector<int>>> adjs = {
        {{ 0, 5, 4, 0 },
        { 0, 0, 6, 1 },
        { 0, 0, 0, 3 },
        { 0, 0, 0, 0 }},
        {{ 0, 5, 6, 8, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 2, 0, 0, 0 },
        { 0, 5, 0, 0, 0, 4, 0, 0 },
        { 0, 0, 0, 0, 0, 3, 10, 0 },
        { 0, 0, 3, 0, 0, 0, 0, 6 },
        { 0, 0, 0, 0, 0, 0, 0, 7 },
        { 0, 0, 0, 0, 0, 2, 0, 8 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },},
        {{ 0, 4, 5, 3, 0 },
        { 0, 0, 0, 0, 6 },
        { 0, 3, 0, 2, 0 },
        { 0, 0, 0, 0, 6 },
        { 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 15, 0, 0 },
        { 0, 0, 0, 0, 0, 10, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 10, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 9 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 8 },
        { 0, 0, 0, 0, 8, 0, 6, 0, 0 },
        { 0, 0, 0, 9, 0, 6, 0, 0, 0 },
        { 15, 10, 10, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 6, 0, 0 },
        { 0, 0, 0, 0, 0, 2, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 10, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 9 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 8 },
        { 0, 0, 0, 0, 8, 0, 6, 0, 0 },
        { 0, 0, 0, 9, 0, 6, 0, 0, 0 },
        { 6, 2, 10, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 15, 10, 10, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 15, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 10, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 10, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 6, 9, 0, 0 },
        { 0, 0, 0, 0, 6, 0, 0, 8, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 9 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 8 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }}
    };

    std::vector<std::vector<int>> source_sink = {
      {0, 3},
      {0, 7},
      {0, 4},
      {7, 8},
      {7, 8},
      {0, 8}
    };

    std::vector<std::vector<int>> distance = {
      {0, 0, 0, 0, 0, 0, 2, 0, 0},
      {0, 0, 0, 0, 0, 2, 0, 0, 0},
      {0, 0, 0, 0, 0, 2, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 5, 0, 10, 0, 0},
      {0, 0, 0, 4, 0, 10, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    // for (int i = 0; i < adjs.size(); ++i)
    // {
    //     Graph graph(adjs[i], source_sink[i][0], source_sink[i][1]);
    //     graph.saveToFile();
    //     FordFulkerson fordFulkerson;
    //     std::cout << fordFulkerson.computeMaxFlow(graph, source_sink[i][0], source_sink[i][1]) << std::endl;
    // }

    // int i = 3;
    // Graph graph(adjs[i], source_sink[i][0], source_sink[i][1], distance);
    // graph.saveToFile();
    // FordFulkerson fordFulkerson;
    // std::cout << fordFulkerson.computeMaxFlow(graph) << std::endl;
    // graph.saveFlowToFile();

    // std::vector<std::vector<int>> adj(30, std::vector<int>(30, 0));
    // for (int i = 1; i <= 18; ++i)
    // {
    //   adj[0][i] = 2;
    //   if (i <= 4)
    //     adj[i][i + 18] = 60;
    //   else if (i <= 13)
    //     adj[i][i + 14] = 60;
    //   else if (i <= 18)
    //     adj[i][i + 10] = 60;
    // }
    // for (int i = 19; i <= 27; ++i)
    // {
    //   if (i != 23)
    //   {
    //     adj[i][i + 1] = 59;
    //     if (i <= 22)
    //       adj[i + 1][i] = 59;
    //   }
    // }
    // adj[28][23] = 53;
    // adj[23][29] = 57;
    // adj[19][29] = 60;

    // Graph graph(adj, 0, 29);
    // graph.saveToFile();
    // FordFulkerson fordFulkerson;
    // std::cout << fordFulkerson.computeMaxFlow(graph) << std::endl;
    // graph.saveFlowToFile();
    // //36


    std::vector<std::vector<int>> adj2(30, std::vector<int>(30, 0));
    for (int i = 1; i <= 18; ++i)
    {
      adj2[0][i] = 10;
      if (i <= 4)
        adj2[i][i + 18] = 60;
      else if (i <= 13)
        adj2[i][i + 14] = 60;
      else if (i <= 18)
        adj2[i][i + 10] = 60;
    }
    for (int i = 19; i <= 25; ++i)
    {
      if (i != 23)
      {
        adj2[i][i + 1] = 59;
        if (i <= 22)
          adj2[i + 1][i] = 59;
      }
    }
    adj2[27][26] = 59;
    adj2[28][27] = 59;
    adj2[26][21] = 53;
    adj2[23][29] = 60;
    adj2[19][29] = 60;

    Graph graph2(adj2, 0, 29);
    graph2.saveToFile();
    FordFulkerson fordFulkerson;
    std::cout << fordFulkerson.computeMaxFlow(graph2) << std::endl;
    graph2.saveFlowToFile();
    //36
}