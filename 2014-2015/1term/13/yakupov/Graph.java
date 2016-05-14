package yakupov;

import java.util.ArrayList;
import java.util.HashMap;

public class Graph {

    HashMap<Integer, ArrayList<Edge>> edges;

    Graph() {
        edges = new HashMap<Integer, ArrayList<Edge>>();
        edges.clear();
    }

    public void add(int v1, int v2) {
        Edge e = new Edge(v1, v2);
        int eHash = e.hashCode();
        if (edges.containsKey(eHash)) {
            if (!edges.get(eHash).contains(e)) {
                edges.get(eHash).add(e);
            }
        } else {
            ArrayList<Edge> l = new ArrayList<Edge>();
            edges.put(eHash, l);
            l.add(e);
        }
    }

    public boolean remove(int v1, int v2) {
        Edge e = new Edge(v1, v2);
        int eHash = e.hashCode();
        if (edges.containsKey(eHash)) {
            if (edges.get(eHash).contains(e)) {
                return edges.get(eHash).remove(e);
            }
        }
        return false;
    }

    @Override
    public String toString() {
        StringBuilder strB = new StringBuilder();
        for (ArrayList<Edge> l : edges.values())
        {
            for (Edge e : l) {
                strB.append("(");
                strB.append(e.toString());
                strB.append(") ");
            }
        }
        if (strB.length() == 0) {
            return "";
        }
        return strB.toString().substring(0, strB.toString().length() - 1);
    }

    public ArrayList<Edge> getListOfEdges() {
        ArrayList<Edge> l = new ArrayList<Edge>();
        for (ArrayList<Edge> lst : edges.values()) {
            l.addAll(lst);
        }
        return l;
    }

    public boolean contains(Edge e) {
        return edges.containsKey(e.hashCode()) &&
                edges.get(e.hashCode()).contains(e);
    }
}
