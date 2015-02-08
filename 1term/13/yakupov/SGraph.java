package yakupov;

import java.util.ArrayList;
import java.util.HashSet;

public class SGraph {

    HashSet<Edge> edges;

    SGraph() {
        edges = new HashSet<Edge>();
        edges.clear();
    }

    public void add(int v1, int v2) {
        Edge e = new Edge(v1, v2);
        edges.add(e);
    }

    public boolean remove(int v1, int v2) {
        Edge e = new Edge(v1, v2);
        return edges.remove(e);
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

    public boolean contains(Edge e) {
        return edges.contains(e);
    }
}
