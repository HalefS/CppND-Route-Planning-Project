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
    for(Model::Road const &road : roads) {
        if(road.type != Model::Road::Type::Footway) {
          auto counter = 0;
          for(int way : this->Ways()[road.way].nodes) {
              // if current road is not present in node_to_road, set value as
              // empty vactor of pointers and push a pointer to the current road(this)
              // to the back of the vector
            if(node_to_road.find(way) == node_to_road.end()) {
              node_to_road[way] = std::vector<const Model::Road*>{};
              node_to_road[way].push_back(&road);
            }
          }

        }

    }
}
