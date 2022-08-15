// application.cpp
// Mohammed Aaqel Shaik Abdul Mazeed
//
// University of Illinois at Chicago
// CS 251: Fall 2021
// Project #7 - Openstreet Maps
//
// Creative Component:
// This application allows you to calculate the cost of
// laying an optical fibre cable telecommunication network
// between the nodes in a given area.
//
// This is done by obtaining a minimum spanning tree using
// Kruskal's algorithm so we prioritize the paths with the
// lowest weight.
//
// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <iomanip>    /*setprecision,   line 403*/
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <limits>     /*numeric_limits, line 50*/
#include <queue>      /*priority_queue, line 212*/
#include <stack>      /*stack,          line 261*/
#include <set>
#include <algorithm>  /*set_union,      line 96*/
#include <cmath>      /*ceil,           line 132*/

#include "tinyxml2.h"
#include "dist.h"
#include "osm.h"
#include "graph.h"

using namespace std;
using namespace tinyxml2;
const double INF = numeric_limits<double>::max();

// Prioritize, used in priority_queue
struct prioritize {
  bool operator()(const pair<long long, double>& p1,
                  const pair<long long, double>& p2) const {
    return p1.second > p2.second;
  }
};

//
// KruskalMST
//
// Returns an MST constructed from the graph passed in as parameter
//
graph<long long, double> KruskalMST(graph<long long, double> G) {
  // Collection of vertex sets, empty initially
  vector<set<long long>> vertexSets;
  graph<long long, double> Gmod;
  for (auto &v : G.getVertices()) {
    // Add new set containing only v to vertexSets
    vertexSets.push_back({v});
    Gmod.addVertex(v);
  }

  while (vertexSets.size() > 1 && G.NumEdges() > 0) {
    // Remove edge with minimum weight
    double minW = INF;
    long long from, to;
    G.findMinEdge(from, to, minW);
    G.eraseEdge(from, to);
    // vSet1 = Set containing 'from' vertex
    // vSet2 = Set containing 'to' vertex
    set<long long> vSet1, vSet2;
    int i1, i2;
    bool v1Found = false;
    bool v2Found = false;
    // Find sets containing 'from' and 'to'
    for (long unsigned int i = 0; i < vertexSets.size(); ++i) {
      if (!v1Found && vertexSets[i].count(from) == 1) {
        vSet1 = vertexSets[i];
        i1 = i;
        v1Found = true;
      }
      if (!v2Found && vertexSets[i].count(to) == 1) {
        vSet2 = vertexSets[i];
        i2 = i;
        v2Found = true;
      }
    }
    if (vSet1 != vSet2) {
      // Add edge to Gmod
      Gmod.addEdge(from, to, minW);
      Gmod.addEdge(to, from, minW);
      vertexSets.erase(vertexSets.begin() + i1);
      vertexSets.erase(vertexSets.begin() + i2);
      set<long long> vSetUnion;
      // Merge vSet1 and vSet2, add it to vertexSets
      set_union(begin(vSet1), end(vSet1),
                begin(vSet2), end(vSet2),
                inserter(vSetUnion, begin(vSetUnion)));
      vertexSets.push_back(vSetUnion);
    }
  }
  return Gmod;
}

//
// Creative component application
//
void creative(graph<long long, double> G) {
  cout << endl;
  cout << "Hey there!" << endl
       << "This application allows you to calculate"
       << "the cost of laying fiber optic" << endl
       << "cables to install a telecommunication"
       << "network between the given nodes." << endl;
  cout << endl;
  cout << "It does this by taking in the graph of"
       << "the osm file given and creating a" << endl
       << "minimum spanning tree from it using Kruskal's"
       << "algorithm. This allows us to" << endl
       << "prioritize the paths with the least weight"
       << "so we only pay for the cabling we need." << endl;
  cout << endl;
  cout << "This might take a while if the given map as a"
       << "lot of nodes, so sit tight!" << endl << endl;

  double totalDist = 0;
  graph<long long, double> Gmod = KruskalMST(G);
  set<pair<long long, long long>> visitedEdges;

  cout << "# of vertices in MST: " << Gmod.NumVertices() << endl;
  cout << "# of edges in MST: " << Gmod.NumEdges() << endl;

  // Calculate total distance 
  // (use visitedEdges to ensure we don't recount edges)
  for (auto &e : Gmod.getVertices()) {
    for (auto &f : Gmod.neighbors(e)) {
      if (visitedEdges.count(make_pair(f, e)) != 1) {
        double dist;
        Gmod.getWeight(e, f, dist);
        totalDist += dist;
        visitedEdges.emplace(make_pair(e, f));
      }
    }
  }

  cout << "Total distance of footways: " << ceil(totalDist) << " miles" << endl;
  cout << endl;
  cout << "The average cost for laying fiber optic cables"
       << "in the United States is" << endl 
       << "$1 - $6 per 30 cm" << endl;
  cout << "Therefore, the cost to install a fiber optic-based" 
       << "telecommunication network" << endl
       << "in the given area is $" << totalDist/0.0001864114 
       << " - $" << totalDist/0.00003106856 << endl;
}

//
// searchBuilding
//
// Takes in a search query and returns the building associated with it
//
bool searchBuilding(vector<BuildingInfo> b, string query, BuildingInfo &bldg) {
  // First, search by abbreviation
  for (auto &e : b) {
    if (e.Abbrev == query) {
      bldg = e;
      return true;
    }
  }
  // If not found, search by parts of full name
  for (auto &e : b) {
    if (e.Fullname.find(query) != string::npos) {
      bldg = e;
      return true;
    }
  }
  // Return false if still not found
  return false;
}

//
// nearestBuilding
//
// Takes in coordinates and finds nearest building (ignores unreachable buildings)
//
BuildingInfo nearestBuilding(vector<BuildingInfo> b,
                             set<string> ub,
                             Coordinates midpoint) {
  BuildingInfo n;
  double min = INF;
  for (auto &e : b) {
    // If current building is NOT unreachable
    if (ub.count(e.Fullname) != 1) {
      double latB = e.Coords.Lat;
      double lonB = e.Coords.Lon;
      double latM = midpoint.Lat;
      double lonM = midpoint.Lon;
      double distance = distBetween2Points(latM, lonM, latB, lonB);
      if (distance < min) {
        min = distance;
        n = e;
      }
    }
  }
  return n;
}

//
// nearestNode
//
// Returns nearest node to building
//
long long nearestNode(vector<FootwayInfo> Footways,
                      map<long long, Coordinates> Nodes,
                      BuildingInfo b) {
  long long node;
  double min = INF;
  for (auto &e : Footways) {
    for (long unsigned int i = 0; i < e.Nodes.size(); ++i) {
      double latN = Nodes[e.Nodes[i]].Lat;
      double lonN = Nodes[e.Nodes[i]].Lon;
      double latB = b.Coords.Lat;
      double lonB = b.Coords.Lon;
      double distance = distBetween2Points(latN, lonN, latB, lonB);
      if (distance < min) {
        min = distance;
        node = e.Nodes[i];
      }
    }
  }
  return node;
}

//
// DjikstraShortestPath
//
// Returns a map of predecessor nodes after running Dijkstra's algorithm
//
map<long long, long long> DijkstraShortestPath(graph<long long, double>& G,
  long long startV,
  map<long long, double>& distances)
{
  set<long long> visited;
  map<long long, long long> predecessors;
  priority_queue <
    pair<long long, double>,
    vector<pair<long long, double>>,
    prioritize> unvisitedQueue;

  for (auto &currV : G.getVertices()) {
      if (currV != startV) {
        distances[currV] = INF;
        predecessors[currV] = 0;
        unvisitedQueue.push({currV, INF});
      }
  }

  // StartV has a distance of 0 from itself
  distances[startV] = 0;
  unvisitedQueue.push({startV, 0});

  while (!unvisitedQueue.empty()) {
    // Visit vertex with minimum distance from startV
    long long currV = unvisitedQueue.top().first;
    unvisitedQueue.pop();

    if (distances[currV] == INF)
      break;
    else if (visited.count(currV) == 1)
      continue;
    else
      visited.insert(currV);

    for (auto &adjV : G.neighbors(currV)) {
      double edgeWeight = 0;
      G.getWeight(currV, adjV, edgeWeight);
      double alternativePathDistance = distances[currV] + edgeWeight;

      // If shorter path from startV to adjV is found,
      // update adjV's distance
      if (alternativePathDistance < distances[adjV]) {
        distances[adjV] = alternativePathDistance;
        predecessors[adjV] = currV;
        unvisitedQueue.push({adjV, alternativePathDistance});
      }
    }
  }
  return predecessors;
}

//
// getPath
//
// Gets the path from a predecessor map using stack reversal
//
vector<long long> getPath(map<long long, long long> pred, long long endV) {
  long long currV  = endV;
  vector<long long> V;
  stack <long long> S;
  while(currV) {
    S.push(currV);
    currV = pred[currV];
  }
  while(!S.empty()) {
    currV = S.top();
    S.pop();
    V.push_back(currV);
  }
  return V;
}

//
// Standard application
//
void application(
    map<long long, Coordinates>& Nodes, vector<FootwayInfo>& Footways,
    vector<BuildingInfo>& Buildings, graph<long long, double> G) {
  string person1Building, person2Building;
  BuildingInfo building1, building2;

  cout << endl;
  cout << "Enter person 1's building (partial name or abbreviation), or #> ";
  getline(cin, person1Building);

  while (person1Building != "#") {
    bool pathFound = false;
    bool bldgFound = true;
    cout << "Enter person 2's building (partial name or abbreviation)> ";
    getline(cin, person2Building);

    // MILESTONE 7: Search buildings 1 and 2
    if (!searchBuilding(Buildings, person1Building, building1)) {
      cout << "Person 1's building not found" << endl;
      bldgFound = false;
    } else if (!searchBuilding(Buildings, person2Building, building2)) {
      cout << "Person 2's building not found" << endl;
      bldgFound = false;
    }

    if (bldgFound) {
      set<string> unreachableBuildings;

      while (!pathFound) {
        // MILESTONE 8: Locate center building
        double lat1 = building1.Coords.Lat;
        double lon1 = building1.Coords.Lon;
        double lat2 = building2.Coords.Lat;
        double lon2 = building2.Coords.Lon;
        Coordinates midpoint = centerBetween2Points(lat1, lon1, lat2, lon2);
        BuildingInfo buildingCenter =
        nearestBuilding(Buildings, unreachableBuildings, midpoint);
        if (unreachableBuildings.size() == 0) {
          cout << "Person 1's point:" << endl
               << " " << building1.Fullname << endl
               << " (" << building1.Coords.Lat << ", "
               << building1.Coords.Lon << ")" << endl;
          cout << "Person 2's point:" << endl
               << " " << building2.Fullname << endl
               << " (" << building2.Coords.Lat << ", "
               << building2.Coords.Lon << ")" << endl;
          cout << "Destination Building:" << endl
               << " " << buildingCenter.Fullname << endl
               << " (" << buildingCenter.Coords.Lat << ", "
               << buildingCenter.Coords.Lon << ")" << endl;
          cout << endl;
        } else {
          cout << "New destination building:" << endl
               << " " << buildingCenter.Fullname << endl
               << " (" << buildingCenter.Coords.Lat << ", "
               << buildingCenter.Coords.Lon << ")" << endl;
        }

        // MILESTONE 9: Find nearest nodes from buildings 1, 2 & center
        long long node1 = nearestNode(Footways, Nodes, building1);
        long long node2 = nearestNode(Footways, Nodes, building2);
        long long nodeCenter = nearestNode(Footways, Nodes, buildingCenter);
        if (unreachableBuildings.size() == 0) {
          cout << "Nearest P1 node:" << endl
               << " " << node1 << endl
               << " (" << Nodes[node1].Lat << ", "
               << Nodes[node1].Lon << ")" << endl;
          cout << "Nearest P2 node:" << endl
               << " " << node2 << endl
               << " (" << Nodes[node2].Lat << ", "
               << Nodes[node2].Lon << ")" << endl;
        }
        cout << "Nearest destination node:" << endl
             << " " << nodeCenter << endl
             << " (" << Nodes[nodeCenter].Lat << ", "
             << Nodes[nodeCenter].Lon << ")" << endl;
        cout << endl;

        // MILESTONE 10: Run Dijkstra's algorithm
        map<long long, double> dist1, dist2;
        map<long long, long long> pred1, pred2;
        pred1 = DijkstraShortestPath(G, node1, dist1);
        if (dist1[node2] >= INF) {
          cout << "Sorry, destination unreachable." << endl;
          pathFound = true;
        } else {
          pred2 = DijkstraShortestPath(G, node2, dist2);

          // MILESTONE 11: Print paths if found (break)
          if (dist1[nodeCenter] < INF && dist2[nodeCenter] < INF) {
            vector<long long> path1 = getPath(pred1, nodeCenter);
            vector<long long> path2 = getPath(pred2, nodeCenter);
            cout << "Person 1's distance to dest: "
                 << dist1[nodeCenter] << " miles" << endl
                 << "Path: " << path1[0];
            for (long unsigned int i = 1; i < path1.size(); i++) {
              cout << "->" << path1[i];
            }
            cout << endl << endl;
            cout << "Person 2's distance to dest: "
                 << dist2[nodeCenter] << " miles" << endl
                 << "Path: " << path2[0];
            for (long unsigned int i = 1; i < path2.size(); i++) {
              cout << "->" << path2[i];
            }
            cout << endl;
            pathFound = true;
          } else { //If not found, find second nearest destination (loop again)
            unreachableBuildings.insert(buildingCenter.Fullname);
            cout << "At least one person was unable to reach the "
                 << "destination building. Finding next closest building..." << endl << endl;
          }
        }
      }
    }

    //
    // another navigation?
    //
    cout << endl;
    cout << "Enter person 1's building (partial name or abbreviation), or #> ";
    getline(cin, person1Building);
  }
}

int main() {
  // maps a Node ID to it's coordinates (lat, lon)
  map<long long, Coordinates>  Nodes;
  // info about each footway, in no particular order
  vector<FootwayInfo>          Footways;
  // info about each building, in no particular order
  vector<BuildingInfo>         Buildings;
  XMLDocument                  xmldoc;

  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << std::setprecision(8);

  string def_filename = "map.osm";
  string filename;

  cout << "Enter map filename> ";
  getline(cin, filename);

  if (filename == "") {
    filename = def_filename;
  }

  //
  // Load XML-based map file
  //
  if (!LoadOpenStreetMap(filename, xmldoc)) {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }

  //
  // Read the nodes, which are the various known positions on the map:
  //
  int nodeCount = ReadMapNodes(xmldoc, Nodes);

  //
  // Read the footways, which are the walking paths:
  //
  int footwayCount = ReadFootways(xmldoc, Footways);

  //
  // Read the university buildings:
  //
  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

  //
  // Stats
  //
  assert(nodeCount == (int)Nodes.size());
  assert(footwayCount == (int)Footways.size());
  assert(buildingCount == (int)Buildings.size());

  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;

  graph<long long, double> G;

  // MILESTONE 5: add vertices
  for (auto &e : Nodes) {
    G.addVertex(e.first);
  }

  // MILESTONE 6: add edges
  for (auto &e : Footways) {
    for (long unsigned int i = 0; i < e.Nodes.size() - 1; ++i) {
      double lat1 = Nodes[e.Nodes[i]].Lat;
      double lon1 = Nodes[e.Nodes[i]].Lon;
      double lat2 = Nodes[e.Nodes[i + 1]].Lat;
      double lon2 = Nodes[e.Nodes[i + 1]].Lon;
      double distance = distBetween2Points(lat1, lon1, lat2, lon2);
      G.addEdge(e.Nodes[i], e.Nodes[i + 1], distance);
      G.addEdge(e.Nodes[i + 1], e.Nodes[i], distance);
    }
  }

  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  cout << endl;

  //
  // Menu
  //
  string userInput;
  cout << "Enter \"a\" for the standard application or " 
        << "\"c\" for the creative component application> ";
  getline(cin, userInput);
  if (userInput == "a") {
    application(Nodes, Footways, Buildings, G);
  } else if (userInput == "c") {
    creative(G);
  }
  //
  // done:
  //
  cout << "** Done **" << endl;
  return 0;
}
