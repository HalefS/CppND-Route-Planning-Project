#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
<<<<<<< HEAD
    float GetDistance() {
        return distance;
    }
    void AStarSearch();
    void AddNeighbors(RouteModel::Node* currend_neighbor);

private:
=======
    // Add public variables or methods declarations here.
    float GetDistance() const {return distance;}
    void AStarSearch();

    // The following methods have been made public so we can test them individually.
    void AddNeighbors(RouteModel::Node *current_node);
    float CalculateHValue(RouteModel::Node const *node);
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *);
    RouteModel::Node *NextNode();

  private:
    // Add private variables or methods declarations here.
    std::vector<RouteModel::Node*> open_list;
    RouteModel::Node *start_node;
    RouteModel::Node *end_node;

    float distance = 0.0f;
>>>>>>> b42701f6a2beb50b978d1e2cb73ed22fb9e90a68
    RouteModel &m_Model;
    RouteModel::Node* start_node;
    RouteModel::Node* end_node;
    float distance;
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node* current_node);
    float CalculateHValue(RouteModel::Node* otherNode);
    std::vector<RouteModel::Node*> open_list;
    RouteModel::Node* NextNode();
};

#endif