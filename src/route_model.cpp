#include "route_model.h"
#include <iostream>


RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  // Create RouteModel::Nodes from Model::Nodes
  auto counter = 0;
  for(Model::Node node: Nodes()) {
    m_Nodes.push_back(Node(counter, this, node));
    counter++;
  }
  CreateNodeToRoadHashMap();
}

void RouteModel::CreateNodeToRoadHashMap() {
  auto roads = this->Roads();
  auto ways = this->Ways();
    for(const Model::Road &road : roads) {
        if(road.type != Model::Road::Type::Footway) {
          auto counter = 0;
          for(int node_idx : ways[road.way].nodes) {
            if(node_to_road.find(node_idx) == node_to_road.end()) {
              node_to_road[node_idx] = std::vector<const Model::Road*>();
            }
            node_to_road[node_idx].push_back(&road);
          }

        }

    }
}

RouteModel::Node* RouteModel::Node::FindNeighbor(std::vector<int> node_indices) {
  Node* closestNode = nullptr;
  Node node;
  for(int index : node_indices) {
      node = parent_model->SNodes()[index];
      if(this->distance(node) != 0 && !node.visited) {
        if(closestNode == nullptr || this->distance(node) < this->distance(*closestNode))
            closestNode = &node;
      }
  }
  return closestNode;
}

// Populate the neighbors vector in the Node class with all the connected nodes
void RouteModel::Node::FindNeighbors() {
    for(auto &road : parent_model->node_to_road[this->index]) {
      RouteModel::Node* potential_neighbor = this->FindNeighbor(parent_model->Ways()[road->way].nodes);
      if (potential_neighbor)
        this->neighbors.push_back(potential_neighbor);
    }
}
