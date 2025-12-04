/*----------------------------------
DIJKSTRA's*/
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path) {
    if (!vertices.count(startLabel) || !vertices.count(endLabel)) return infinity;

    for (auto& [lbl, v]: vertices) v->resetState();

    Vertex* start = vertices[startLabel];
    Vertex* goal = vertices[endLabel];

    PriorityQueue pq;
    start->distance = 0;
    pq.push(0, start);

    while (!pq.isEmpty()) {
        auto [dist, current] = pq.pop();
        if (!current || current->visited) continue;

        current->visited = true;
        if (current == goal) break;

        for (Edge* e : current->adjEdges) {
            Vertex* next = e->getOtherVertex(current);
            if (!next || next->visited) continue;

            unsigned long newDist = current->distance + e->weight;
            if (newDist < next->distance) {
                next->distance = newDist;
                next->previous = current;
                pq.push(newDist, next);
            }
        }
    }

    if (goal->distance == infinity) return infinity;

    std::vector<std::string> rev;
    for (Vertex* v = goal; v; v = v->previous) rev.push_back(v->label);
    std::reverse(rev.begin(), rev.end());
    path = rev;

    return goal->distance;
}


/*PQ*/

