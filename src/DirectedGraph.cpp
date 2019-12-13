#include "DirectedGraph.h"

//design taken from https://www.tutorialspoint.com/cplusplus-program-to-apply-dfs-to-perform-the-topological-sorting-of-a-directed-acyclic-graph
// and https://www.geeksforgeeks.org/cpp-program-for-topological-sorting/
DirectedGraph::DirectedGraph(Edge *edges, int size) {
    for (int i = 0; i < size; i++) {
        int src = edges[i].src, dest = edges[i].dest;
        if (nodes.count(src) == 0) {
            nodes[src] = new SingleLinkedList<int>();
        }
        nodes[src]->add(dest);
        if (nodes.count(dest) == 0) {
            nodes[dest] = new SingleLinkedList<int>();
        }
    }
}

DirectedGraph::~DirectedGraph() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        delete (*it).second;
    }
}

void DirectedGraph::printGraph() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        printf("node(%d) has edges: ", (*it).first);
        for (auto itl = (*it).second->begin(); itl != (*it).second->end(); itl++) {
            printf("%d ", (*itl));
        }
        printf("\n");
    }
}

void DirectedGraph::topoSort(int key, bool visited[], LinkedStack<int> &stack) {
    visited[key] = true;
    //check adjacent
    for (auto it = nodes[key]->begin()++; it != nodes[key]->end(); it++) {
        if (!visited[*it]) {
            //recurs if new node
            topoSort(*it, visited, stack);
        }
    }
    //otherwise push to stack
    stack.push(key);
}

vector<int> *DirectedGraph::topologySort() {
    LinkedStack<int> answer;
    vector<int> *ans = new vector<int>();
    bool *visited = new bool[nodes.size()];
    for (int i = 0; i < nodes.size(); i++) {
        //track/backtrack progress through graph
        visited[i] = false;
    }
    for (int k = 0; k < nodes.size(); k++)
        if (!visited[k]) {
            //recursively sort
            topoSort(k, visited, answer);
        }
    while (!answer.isEmpty()) {
        //return as vector
        ans->push_back(answer.peek());
        answer.pop();
    }
    return ans;
}


