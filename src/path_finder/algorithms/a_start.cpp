#include <cmath>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include "a_start.hpp"

AStart::AStart() {}

AStart::~AStart() {}

// Vector2 AStart::GetCentroid(const Polygon& poly) {
//     Vector2 center = {0, 0};
//     for(auto v : poly.vertices) { center.x += v.x; center.y += v.y; }
//     center.x /= poly.vertices.size();
//     center.y /= poly.vertices.size();
//     return center;
// }

float AStart::GetDistance(Vector2 a, Vector2 b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float AStart::heuristic(int currentID, int targetID, Graph graph) {
    Node currentNode = graph.getNode(currentID);
    Node targetNode = graph.getNode(targetID);

    return GetDistance(currentNode.position, targetNode.position);
}

std::vector<Connection> AStart::GetPath(int startId, int endId, Graph graph) {
    std::cout << "Finding path" << std::endl;
    NodeRecord StartRecord;
    StartRecord.NodeID = startId;
    StartRecord.CostSoFar = 0;
    StartRecord.EstimatedTotalCost = heuristic(startId, endId, graph);
    
    NodeRecord current;

    // A priority queue for fast retrieval of the node with the lowest estimated total cost. 
    std::priority_queue<NodeRecord, std::vector<NodeRecord>, std::greater<NodeRecord>> openSet;
    openSet.push(StartRecord);
    
    // A hash map for fast look up 
    std::unordered_map<int, NodeRecord> OpenSetMap;
    OpenSetMap[startId] = StartRecord;

    std::unordered_map<int, NodeRecord> ClosedSet;

    while (!openSet.empty()) {
        std::cout << "Open set size: " << OpenSetMap.size() << std::endl;
        current = openSet.top();
        openSet.pop();

        if (ClosedSet.count(current.NodeID) && current.CostSoFar > ClosedSet[current.NodeID].CostSoFar) {
            continue;
        }

        if (current.NodeID == endId) {
            break;
        }

        ClosedSet[current.NodeID] = current;
        OpenSetMap.erase(current.NodeID);

        std::vector<Connection> connections = graph.getConnections(current.NodeID);

        for (Connection c : connections) {
            NodeRecord endNodeRecord;
            int endNodeID = c.ToNode;
            float endNodeCost = current.CostSoFar + c.Cost;
            float endNodeHeuristic;

            if (ClosedSet.find(endNodeID) != ClosedSet.end()) {
                endNodeRecord = ClosedSet[endNodeID];
                
                if (endNodeRecord.CostSoFar <= endNodeCost) {
                    continue;
                }
            
                ClosedSet.erase(endNodeID);

                endNodeHeuristic = endNodeRecord.EstimatedTotalCost - endNodeRecord.CostSoFar;
            }
            else if (OpenSetMap.find(endNodeID) != OpenSetMap.end()) {
                endNodeRecord = OpenSetMap[endNodeID];

                if (endNodeRecord.CostSoFar <= endNodeCost) {
                    continue;
                }

                endNodeHeuristic = endNodeRecord.EstimatedTotalCost - endNodeRecord.CostSoFar;
            }

            else {
                endNodeRecord.NodeID = endNodeID;
                endNodeHeuristic = heuristic(endNodeID, endId, graph);
            }
            
            endNodeRecord.CostSoFar = endNodeCost;
            endNodeRecord.connection = c;
            endNodeRecord.EstimatedTotalCost = endNodeCost + endNodeHeuristic;

            if (OpenSetMap.find(endNodeID) == OpenSetMap.end()) {
                OpenSetMap[endNodeID] = endNodeRecord;
                openSet.push(endNodeRecord);
            }
        }

        OpenSetMap.erase(current.NodeID);

        ClosedSet[current.NodeID] = current;
    }

    if (current.NodeID != endId) {
        return {};
    }

    std::vector<Connection> path;

    while (current.NodeID != startId) {
        path.push_back(current.connection);
        current = ClosedSet[current.connection.FromNode];
    }
    std::reverse(path.begin(), path.end());

    return path;
}
