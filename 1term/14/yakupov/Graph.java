package yakupov;

import java.util.*;

public class Graph {

    HashSet<Edge> edges;
    HashSet<Integer> vertex;

    Graph() {
        edges = new HashSet<Edge>();
        edges.clear();
        vertex = new HashSet<Integer>();
        vertex.clear();
    }

    public void add(int v1, int v2) {
        Edge e = new Edge(v1, v2);
        if (!contains(e)) {
            vertex.add(v1);
            vertex.add(v2);
        }
        edges.add(e);
    }

    public boolean remove(int v1, int v2) {
        Edge e = new Edge(v1, v2);
        return edges.remove(e);
    }

    private boolean removeVertexWithEdges(Integer v) {
        if (!vertex.contains(v)) {
            return false;
        }
        Graph g = (Graph) clone();
        for (Edge e : g.edges) {
            if (e.vertex1 == v || e.vertex2 == v) {
                remove(e.vertex1, e.vertex2);
            }
        }
        vertex.remove(v);
        return true;
    }

    @Override
    public String toString() {
        StringBuilder strB = new StringBuilder();
        for (Edge e : edges) {
            strB.append("(");
            strB.append(e.toString());
            strB.append(") ");
        }
        if (strB.length() == 0) {
            return "";
        }
        return strB.toString().substring(0, strB.toString().length() - 1);
    }

    public ArrayList<Edge> getListOfEdges() {
        ArrayList<Edge> l = new ArrayList<Edge>();
        for (Edge e : edges) {
            l.add(e);
        }
        return l;
    }

    public ArrayList<Edge> bridges() {
        ArrayList<Edge> bridges = new ArrayList<Edge>();
        for (Edge e : edges) {
            HashSet<Integer> visitedVertex = new HashSet<Integer>();
            Graph g = (Graph) this.clone();
            g.remove(e.vertex1, e.vertex2);
            search(g, visitedVertex, e.vertex1);
            if (visitedVertex.size() != vertex.size()) {
                bridges.add(e);
            }
        }
        return bridges;
    }

    public ArrayList<Integer> pointsOfJunction() {
        ArrayList<Integer> pointsOfJunction = new ArrayList<Integer>();
        for (Integer v : vertex) {
            Graph g = (Graph) this.clone();
            g.removeVertexWithEdges(v);
            HashSet<Integer> visitedVertex = new HashSet<Integer>();
            search(g, visitedVertex, (Integer) g.vertex.toArray()[0]);
            if (visitedVertex.size() != g.vertex.size()) {
                pointsOfJunction.add(v);
            }
        }
        return pointsOfJunction;
    }

    public HashSet<Graph> doublyConnectedComponent() {
        HashSet<Graph> doublyConnectedComponent = new HashSet<Graph>();
        for (int v : vertex) {
            Graph g = (Graph) this.clone();
            g.removeVertexWithEdges(v);
            if (g.vertex.size() == 1) break;
            HashSet<Integer> visitedVertex = new HashSet<Integer>();
            search(g, visitedVertex, (Integer) g.vertex.toArray()[0]);
            if (g.pointsOfJunction().isEmpty() && visitedVertex.size() == g.vertex.size()) {
                doublyConnectedComponent.add(g);
            }
            doublyConnectedComponent.addAll(
                    g.doublyConnectedComponent()//recursion
            );
        }
        return doublyConnectedComponent;
    }

    /**
     * Search in graph from vertex 'v'
     * All in all, 'visitedVertex' - set of vertex, which we can gain from vertex 'v'
     * @param g Graph
     * @param visitedVertex Set of visited vertex
     * @param v Vertex of beginning
     */
    public void search(Graph g, HashSet<Integer> visitedVertex, Integer v) {
        visitedVertex.add(v); //mark vertex visited
        if (g.vertex.size() == visitedVertex.size()) return; //all vertexes are visited
        for (Integer sv : g.vertex) {//for each vertex
            if (!visitedVertex.contains(sv) && g.contains(new Edge(v, sv))) {//if can go from 'v' to 'sv'
                search(g, visitedVertex, sv);//run search from 'sv'
            }
        }
    }

    public boolean contains(Edge e) {
        return edges.contains(e);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null)
            return false;
        if (getClass() != o.getClass())
            return false;
        Graph g = (Graph) o;
        for (Integer v : vertex) {
            if (!g.vertex.contains(v)) {
                return false;
            }
        }
        for (Integer v : g.vertex) {
            if (!vertex.contains(v)) {
                return false;
            }
        }
        for (Edge e : edges) {
            if (!g.contains(e)) {
                return false;
            }
        }
        for (Edge e : g.edges) {
            if (!contains(e)) {
                return false;
            }
        }
        return true;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        for (Integer v : vertex) {
            hash += v.hashCode();
        }
        for (Edge e : edges) {
            hash += e.hashCode();
        }
        return hash;
    }

    @Override
    public Object clone() {
        Graph g = new Graph();
        for (Integer v : vertex) {
            g.vertex.add(v);
        }
        for (Edge e : edges) {
            g.edges.add(e);
        }
        return g;
    }
}
