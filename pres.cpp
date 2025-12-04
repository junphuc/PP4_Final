/*GRAPH
Header:*/

/*----------------------------------
DIJKSTRA's*/
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path) {
    if (!vertices.count(startLabel) || !vertices.count(endLabel)) return infinity;

    // Initialize — Set all distances to infinity, start node to 0
    for (auto& [lbl, v]: vertices) v->resetState();

    Vertex* start = vertices[startLabel];
    Vertex* goal = vertices[endLabel];

    PriorityQueue pq;
    start->distance = 0;
    //
    pq.push(0, start);

    while (!pq.isEmpty()) {
        // Select — Extract the unvisited vertex with minimum distance
        auto [dist, current] = pq.pop();
        if (!current || current->visited) continue;

        current->visited = true;
        //
        if (current == goal) break;

        //Relax — Update distances to neighbors if shorter path found
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
        //
    }

    if (goal->distance == infinity) return infinity;

    //Reconstruct — Build the path using predecessor information
    std::vector<std::string> rev;
    for (Vertex* v = goal; v; v = v->previous) rev.push_back(v->label);
    std::reverse(rev.begin(), rev.end());
    path = rev;
// 
    return goal->distance;
}


/*PQ
Header:*/
class PriorityQueue {
    std::vector<std::pair<unsigned long, Vertex*>> heap;
    void bubbleUp(int index);
    void bubbleDown(int index);

public:
    PriorityQueue() = default;

    bool isEmpty() const{return heap.empty();};
    void push(unsigned long dist, Vertex* v);
    std::pair<unsigned long, Vertex*> pop();
};
/*implementation:
*/
void PriorityQueue::bubbleUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].first >= heap[parent].first) break;

        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}

void PriorityQueue::bubbleDown(int index) {
    int size = heap.size();
    while (true) {
        int left = 2*index + 1;
        int right = 2*index + 2;
        int smallest = index;

        if (left < size && heap[left].first < heap[smallest].first)
            smallest = left;
        if (right < size && heap[right].first < heap[smallest].first)
            smallest = right;
        if (smallest == index) break;

        std::swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

void PriorityQueue::push(unsigned long dist, Vertex* v) {
    heap.push_back({dist, v});
    bubbleUp(heap.size() - 1);
}

std::pair<unsigned long, Vertex*> PriorityQueue::pop() {
    if (heap.empty()) return {infinity, nullptr};

    auto top = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) bubbleDown(0);

    return top;
}



