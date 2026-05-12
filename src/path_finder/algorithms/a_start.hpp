#include <vector>
#include <unordered_map>

struct Vector2 {
    float x, y;
};

struct Connection {
    float Cost;
    int FromNode;
    int ToNode;
};

struct Node {
    int id;
    Vector2 position;
};

struct Graph {
    std::unordered_map<int, Node> Nodes;
    std::unordered_map<int, std::vector<Connection>> Connections;

    Node getNode(int id) {
        return Nodes[id];
    }

    // Returns a list of connections outgoing from the given node
    std::vector<Connection> getConnections(int node) {
        return Connections[node];
    }
};

struct NodeRecord {
    int NodeID;
    Connection connection;
    float CostSoFar;
    float EstimatedTotalCost;

    bool operator>(const NodeRecord& other) const {
        return EstimatedTotalCost > other.EstimatedTotalCost;
    }
};

class AStart {
private:
    /// TODO: Bring back the polygons
    // Vector2 GetCentroid(const Polygon& poly);
    float GetDistance(Vector2 a, Vector2 b);

    // float g(const Polygon& current, const Polygon& neighbor);
    float heuristic(int current, int target, Graph graph);

public:
    AStart();
    ~AStart();

    std::vector<Connection> GetPath(int startId, int endId, Graph graph);
};