#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    //Scale float values
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;
    // Get pointers to the closest nodes availeble on the map model data
    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node* current_node) {
    std::vector<RouteModel::Node> path_found {};
    RouteModel::Node parent;
    distance = 0.0;

    // Iterate untill final node in the path (which has parent node as nullptr)
    while(current_node->parent != nullptr) {
        path_found.push_back(*current_node);
        parent = *(current_node->parent);
        distance += current_node->distance(parent);
        current_node = current_node->parent;
    }
    distance = distance * m_Model.MetricScale();
    path_found.push_back(*current_node);
    return path_found;
}


// A*Search implementation
void RoutePlanner::AStarSearch() {
  // Start search
  start_node->visited = true;
  open_list.emplace_back(start_node);
  RouteModel::Node* current_node = nullptr;
  while(!open_list.empty()) {
      current_node = NextNode();
      // If current node is the goal, finish search
      if(current_node->distance(*end_node) == 0) {
          m_Model.path = ConstructFinalPath(current_node);
          return;
      }
      else { // Keep adding nodes to the opel_list
        if (current_node != nullptr)
            AddNeighbors(current_node);
        else
          return;
      }
  }
}

// distacne from given node to the end_node
float RoutePlanner::CalculateHValue(RouteModel::Node* otherNode) {
    return otherNode->distance(*end_node);
}

// Method that ensure we always move forward and always get the node
// with the lowest f value possible
RouteModel::Node* RoutePlanner::NextNode() {
    // sort the list from lowest f value
    std::sort(open_list.begin(), open_list.end(),[](auto first, auto second) {
        return first->g_value + first->h_value < second->g_value + second->h_value;
    });
    // return reference to the first element and remove it from the list
    auto next_node = open_list.front();
    open_list.erase(open_list.begin());
    return next_node;
}

void RoutePlanner::AddNeighbors(RouteModel::Node* current_node) {
    // Populate current_node neighbors vector;
    current_node->FindNeighbors();
    // Configure the Node object properties nessesary to be used on the search
    // and push to the open_list of nodes
    for(RouteModel::Node* neighbor : current_node->neighbors) {
        neighbor->parent = current_node;
        neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
        neighbor->h_value = CalculateHValue(neighbor);
        open_list.emplace_back(neighbor);
        neighbor->visited = true;
    }
}
