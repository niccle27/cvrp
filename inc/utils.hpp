/**
* @file utils.hpp
* @author vss2sn
* @brief Contains the structs, classes and functions used for the set up of the problem aand solution as well as some functions that aid in debugging.
*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <climits>
#include <unordered_set>
#include <set>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <map>
#include <queue>
#include <unistd.h>
#include <cstdio>
#include <ctime>

/**
* @brief Class node
* @details Contains the x, y coordinates of the locationof the node, its id, its demand, andwhether it has been added to the routes of any of the vehicles
*/
class Node{
public:
  int x, y, id, demand;
  bool is_routed;

  /**
  * @brief Consructor
  * @param int x x coordinate
  * @param int y y coordinate
  * @param int id node id
  * @param int demand node demand
  * @param bool is_routed
  * @return no return parameter
  * @details Constructor for a node
  */
  Node(int x = 0, int y = 0, int id = 0, int demand = 0, bool is_routed = true):x(x), y(y), id(id), demand(demand), is_routed(is_routed){}

  /**
  * @brief print status of node
  * @details prints the status of the node, ie, each of its elements
  */
  void PrintStatus();
};

class Route{
public:
  double cost = 0;
  std::vector<int> nodes;

  /**
  * @brief print status of route
  * @details prints the status of the route, ie, each of its elements
  */
  void PrintStatus();

  /**
  * @brief prints the route
  * @details prints the route, ie, each of its elements in order
  */
  void PrintRoute();

  /**
  * @brief Calculates cost of the route
  * @param std::vector<std::vector<double>> distanceMatrix Holds the distances between each pair of nodes
  * @return void
  * @details Calculates cost of the route
  */
  void CalculateCost(std::vector<std::vector<double>> distanceMatrix);
};


class Vehicle: public Route{
public:
  int id, load, capacity;

  /**
  * @brief Constructor
  * @param id Vehicle id
  * @param load Current vehicle load
  * @param capacity Maximum vehicle capacity (initial load)
  * @return no return value
  * @details Constructor of vehicle class
  */
  Vehicle(int id = 0, int load = 0, int capacity = 0) : id(id), load(load), capacity(capacity){}

  /**
  * @brief print status of vehicle
  * @details prints the status of the vehicle, ie, each of its elements
  */
  void PrintStatus();
};

class Problem{
public:
  std::vector<Node> nodes;
  std::vector<Vehicle> vehicles;
  std::vector<std::vector<double>> distanceMatrix;
  Node depot;
  int capacity;

  /**
  * @brief Constructor
  * @param int noc number of nodes (dropoff points)
  * @param int demand_range max demand of each node (random value between 0 and this value)
  * @param int mov number of vehicles
  * @param int capacity maximum capacityof each vehicle
  * @param int grid_range maximum x and y coordinates of any node
  * @param string distribution distribution of nodes. Can be either clustered or uniform.
  * @param int n_clusters If clustered, number of clusters the nodes are divided into
  * @param int cluster_range If clustered, maximum distance from center of cluster.
  * @return no return value
  * @details Constructor for problem class
  */
  Problem(int noc = 1000, int demand_range = 40, int nov = 50, int capacity = 800, int grid_range = 1000, std::string distribution = "uniform", int n_clusters = 5, int cluster_range = 10);
};

class Solution{
public:
  std::vector<Node> nodes;
  std::vector<Vehicle> vehicles;
  std::vector<std::vector<double>> distanceMatrix;
  Node depot;
  int capacity;
  /**
  * @brief Constructor
  * @param std::vector<Node> nodes Vector of all nodes
  * @param std::vector<Vehicle> vehicles Vector of vehicles
  * @param std::vector<std::vector<double>> distanceMatrix Matrix containing distance between each pair of nodes
  * @return no return type
  * @details Constructor for solution class
  */
  Solution(std::vector<Node> nodes, std::vector<Vehicle> vehicles, std::vector<std::vector<double>> distanceMatrix);

  /**
  * @brief Constructor
  * @param p Instance of problem class defining the problem parameters
  * @return no return type
  * @details Constructor for solution class
  */
  Solution(Problem p);

  /**
  * @brief Creates initial solution
  * @return void
  * @details Creates initial solution, currently set to greedy.
  */
  void CreateInitialSolution();

  /**
  * @brief Check whether the solution is valid
  * @return bool True is solution is valid
  * @details Check whether the solution is valid by checking whether all the nodes are reached and whether the total edmand of all the nodes on any of the routes exceed the capacity of the respective vehicles
  */
  bool CheckSolutionValid();

  /**
  * @brief Virtual function overloaded by solution classes to solve the given problem.
  * @return void
  * @details Virtual function overloaded by solution classes to solve the given problem.
  */
  virtual void Solve(){};

  /**
  * @brief find closest node
  * @param Vehicle& v vehicle under consideration
  * @param std::vector<std::vector<double>>& distanceMatrix Matrix containing distance between each pair of nodes
  * @param std::vector<Node>& nodes
  * @return Node nearest node
  * @details Finds the node nearest to the last node in the route of the vehicle under constideration that has not been routed already
  */
  Node find_closest(Vehicle& v, std::vector<std::vector<double>>& distanceMatrix, std::vector<Node>& nodes);
};

#endif
