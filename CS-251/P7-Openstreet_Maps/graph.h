// graph.h
// Mohammed Aaqel Shaik Abdul Mazeed
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.
//
// University of Illinois at Chicago
// CS 251: Fall 2021
// Project #7 - Openstreet Maps
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {
 private:
  // We declare an unordered_map where the first value is each vertex in the
  // graph, and the second value is the unordered_map that contains all the
  // edges it has in the form of <Neighbor vertex, weight of edge>.
  unordered_map <VertexT, unordered_map<VertexT, WeightT>> adjList;

 public:
  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const {
    return static_cast<int>(this->adjList.size());
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    int count = 0;
    for (auto &e : adjList) {
      count += e.second.size();
    }
    return count;
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph and returns true.  
  // If the vertex already exists in the graph, then 
  // false is returned.
  //
  bool addVertex(VertexT v) {
    //
    // is the vertex already in the graph?
    //
    if (adjList.count(v) == 1) {
      return false;
    }

    //
    // if we get here, vertex does not exist so insert.
    //
    unordered_map<VertexT, WeightT> t;
    this->adjList.emplace(v, t);

    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight) {
    if (adjList.count(from) != 1) {
      return false;
    }

    if (adjList.count(to) != 1) {
      return false;
    }

    //
    // the vertices exist, so insert / update the edge:
    //
    adjList[from][to] = weight;
    return true;
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
    //
    // we need to check if the given vertices
    // 'from' and 'to' exist in the current graph.
    //
    if (adjList.count(from) != 1) {
      return false;
    }

    if (adjList.count(to) != 1) {
      return false;
    }
    //
    // the vertices exist, but does the edge exist?
    //
    if (adjList.at(from).count(to) != 1) {
      return false;
    }

    //
    // Okay, the edge exists, return the weight via the
    // reference parameter:
    //
    weight = this->adjList.at(from).at(to);
    return true;
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    set<VertexT>  S;

    // Check if V has any neighbors.
    if (adjList.count(v) != 1) {
      return S;
    }

    //
    // V does have neighbors, so now we iterate through its
    // unordered_map to insert all neighbor vertices into the set.
    for (auto &e: adjList.at(v)) {
      S.insert(e.first);
    }
    return S;
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const {
    vector<VertexT> v;
    for (auto &e : adjList) {
      v.push_back(e.first);
    }
    return v;  // returns a copy:
  }

  //
  // eraseEdge
  //
  // Erases the edge with minimum weight from graph (
  // Used in Creative Component
  //
  void eraseEdge(VertexT from, VertexT to) {
    adjList[from].erase(to);
  }

  //
  // findMinEdge
  //
  // Finds the edge with minimum weight in the graph
  // Used in creative component
  //
  void findMinEdge(VertexT& from, VertexT& to, WeightT& min) {
    for (auto& e : adjList) {
      for (auto& f : e.second) {
        if (f.second < min) {
          min = f.second;
          from = e.first;
          to = f.first;
        }
      }
    }
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  void dump(ostream& output) const {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
    int i = 0;
    for (auto &e : adjList) {
      output << " " << i << ". " << e.first << endl;
      i++;
    }

    output << endl;
    output << "**Edges:\n (Source) => (Neighbor, Weight)" << endl;
    for (auto &e : adjList) {
      for (auto &f : e.second) {
        output << " " << e.first << " => " << f.first << ", " << f.second << endl;
      }
      output << endl;
    }
    output << "**************************************************" << endl;
  }
};