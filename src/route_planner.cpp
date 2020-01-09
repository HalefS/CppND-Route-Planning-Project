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
    std::vector<RouteModel::Node> path_found;
    this->distance = 0.0;
    // Iterate from end to start node using the parent pointer to create
    // the path
    while(current_node != nullptr) {
      path_found.push_back(*current_node);
      if(current_node->parent)
      // Add to the total distance and change pointer to parent
        distance += current_node->distance(*(current_node->parent));
      current_node = current_node->parent;
    }
    // Scale the distance using the model scale method
    distance *= m_Model.MetricScale();
    return path_found;
}

void RoutePlanner::AStarSearch() {
  end_node->parent = start_node;
  m_Model.path = ConstructFinalPath(end_node);
  return;
}
