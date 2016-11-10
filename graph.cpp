/*!
 * \file
 * \biref This module provides the Dijsktra algorithm on graph, the rest (graph
 * definition) is in the header file.
 *
 * \author PASD
 * \date 2016
 */

#include "graph.hpp"
#include "heap_id.hpp"

using namespace std;

namespace {

/*!
 * Class used to put a Head_Id to store, for a vertex (identifyed by \c i ):
 */
class Vertex_Distance {

  /*! Reachable vertex number. */
  unsigned int i;

  /*! Lower distance found to get to i, yet. */
  float distance;

  /*! From where to come from to get this distance. */
  unsigned int from;

public:
  //
  //  CONSTRUCTORS
  //

  Vertex_Distance() {}
  Vertex_Distance(unsigned int _i, float _distance, unsigned int _from)
      : i(_i), distance(_distance), from(_from) {}

  //
  //  PUBLIC METHODS
  //

  /*! Comparison according to distance.
   * \param cd2 Vertex_Distance to compare to.
   * \return true if vd2 is at a longer distance.
   */
  bool operator<(Vertex_Distance const &vd2) const {
    return distance < vd2.distance;
  }

  /*! Comparison according to distance.
   * \param cd2 Vertex_Distance to compare to.
   * \return true if vd2 is at a longer or equal distance.
   */
  bool operator<=(Vertex_Distance const &vd2) const {
    return distance <= vd2.distance;
  }

  /*!
   * To change the value held.
   * \param _distance new value for distance.
   * \param _from new value for from.
   * \pre distance should be decreasing.
   */
  void update(float const _distance, unsigned int const _from) {
    assert(_distance < distance);
    distance = _distance;
    from = _from;
  }

  //
  //  FRIENDS
  //

  friend class ::Graph;
};

/*! Constant to indicate that the node is not reachable yet. */
int const id_undefined = -1;

/*! Constant to indicate that the node was treated. */
int const id_treated = -2;
}

void Graph::print_dijkstra(unsigned int from, unsigned int to) const {
  assert(from < nbr_vertices);
  assert(to < nbr_vertices);

  // HEAP
  Heap_Id<Vertex_Distance> heap(nbr_vertices);

  // Associate vertices id to heap id
  int *vertices_ids = new int[nbr_vertices];
  for (unsigned int i = 0; i < nbr_vertices; i++) {
    vertices_ids[i] = id_undefined;
  }

  // Vertex_Distance array
  Vertex_Distance *vertices_dist = new Vertex_Distance[nbr_vertices];

  // Add start vertex to heap
  vertices_dist[from] = Vertex_Distance(from, 0, from);
  vertices_ids[from] = heap.push(vertices_dist[from]);

  // CALCULATE DISTANCES
  // While we don't have check all vertex
  while (!heap.is_empty()) {
    // Get the vertex at minimal distance
    Vertex_Distance vd = heap.pop();
    // Add vertices distance to heap
    for (unsigned int i = 0; i < vertices[vd.i].second.size(); i++) {
      Edge e = vertices[vd.i].second[i];
      if (vertices_ids[e.first] == id_undefined) {
        vertices_dist[e.first] =
            Vertex_Distance(e.first, vd.distance + e.second, vd.i);
        vertices_ids[e.first] = heap.push(vertices_dist[e.first]);

      } else if (vertices_dist[e.first].distance > vd.distance + e.second) {
        vertices_dist[e.first].distance = vd.distance + e.second;
        vertices_dist[e.first].from = vd.i;
        heap.reposition(vertices_ids[e.first]);
      }
    }
    vertices_ids[vd.i] = id_treated;
  }

  // PRINT PATH
  unsigned int i_current = to; // Vertex id
  while (i_current != from) {
    // Print vertex and distance
    cout << "n" << vertices_dist[i_current].i << " "
         << vertices_dist[i_current].distance << endl;
    i_current = vertices_dist[i_current].from;
  }
  cout << "n0" << endl;

  delete[] vertices_ids;
  delete[] vertices_dist;
}
