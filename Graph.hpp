#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>

class Vertex;

// Define a value of infinity for comparison/initialization
#define infinity static_cast<unsigned long>(~0)

/*PriorityQueue Class: Unique Indexed priority queue implementation for performing Dijkstra's algorithm
- Uses vector heap for storage
- Stores pairs of (distance, vertex)
- Uses "distance" as the key for sorting entries
*/
class PriorityQueue {
    std::vector<std::pair<unsigned long, Vertex*>> heap;
    std::unordered_map<std::string, unsigned long> hash_table; //for quickly knowing hash index of a node based on unique label
    void bubbleUp(int index);
    void bubbleDown(int index);

public:
    PriorityQueue() = default;

    bool isEmpty() const{return heap.empty();};
    void push(unsigned long dist, Vertex* v);
    void updateDistance(std::string label, unsigned long newKey);
    std::pair<unsigned long, Vertex*> pop();
};
/*Edge Class: implementation of undirected edge 
*/
class Edge{
    public:
    Vertex* u;
    Vertex* v;
    unsigned long weight;
    
    // returns the other vertex in the pair (u,v) given that the input is u or v
    // otherwise returns nullptr.
    // 'inline' in case of override (header file function implementation)
    inline Vertex* getOtherVertex(Vertex* currentVertex){
        if(currentVertex == u){
            return v;
        }else if(currentVertex == v){
            return u;
        }
        return nullptr;
    }

};
/*Vertex Class: 
*/
class Vertex{
    public:
    std :: string label;
    std::vector<Edge*> adjEdges; //adjacency list (label.adjEdges.begin() for iterator)

    // For Dijkstra's 
    unsigned long distance;
    Vertex* previous;
    bool visited;
    // Resets/sets state for new shortestPath calculation
    // i.e. for(auto const& [label, v]: vertices) {v->resetState();}
    // 'inline' in case of override (header file function implementation)
    inline void resetState(){ 
        distance = infinity; 
        previous = nullptr;
        visited = false;
    }


};
class Graph : public GraphBase{
public:
    // Using std::unordered_map for the vertex sequence
    // provides ease of use in retrieving by lable
    // without sacrificing constant time complexity.
    std::unordered_map<std::string, Vertex*> vertices;

    Graph() = default; // default in case of memcpy

    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std:: string label1, std:: string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    /*shortestPath(): 
    - finds shortest path between two vertexes by performing dijkstra's algorithm
      over a 
    algorithm:
      Input: Weighted graph G ()
    */
    unsigned long shortestPath(std::string startLabel, std::string EndLabel, std::vector<std::string> &path);

};

#endif
