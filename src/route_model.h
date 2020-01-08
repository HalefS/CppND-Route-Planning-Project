#pragma once

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>
#include <vector>

class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        Node* parent = nullptr;
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited = false;
        std::vector<Node*> neighbors;

        float distance(const Node other) {
            return std::sqrt(std::pow((other.x - x), 2) + std::pow((other.y - y), 2));
        }

        Node(){}
        Node(int idx, RouteModel *search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}
        void FindNeighbors();

      private:
        int index;
        RouteModel* parent_model = nullptr;
        RouteModel::Node* FindNeighbor(std::vector<int> node_indices);

        void CreateNodeToRoadHashMap();

    };

    // Add public RouteModel variables and methods here.
    RouteModel(const std::vector<std::byte> &xml);
    std::vector<Node> path;
    std::vector<Node> &SNodes() { return m_Nodes;}
    void CreateNodeToRoadHashMap();
    std::unordered_map<int, std::vector<const Model::Road*> > &GetNodeToRoadMap() { return node_to_road;}

  private:
    // Add private RouteModel variables and methods here.
    std::vector<Node> m_Nodes;
    std::unordered_map<int, std::vector<const Model::Road*> > node_to_road;

};
