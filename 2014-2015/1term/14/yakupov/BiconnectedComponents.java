package yakupov;

import java.util.*;

public class BiconnectedComponents {

    HashMap<Integer, Boolean> visited;
    Stack<Edge> stack;
    int curNumberInSearch;
    HashMap<Integer, Integer> numberInSearch;
    HashMap<Integer, Integer> low;

    List<List<Edge>> components;
    List<Integer> cutPoints;
    List<Edge> bridges;

    HashSet<Edge> edges;
    HashSet<Integer> vertex;

    BiconnectedComponents() {
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

    public boolean contains(Edge e) {
        return edges.contains(e);
    }

    public void update() {
        visited = new HashMap<>();
        for (int v : vertex) {
            visited.put(v, false);
        }

        stack = new Stack<>();

        curNumberInSearch = 0;
        numberInSearch = new HashMap<>();
        for (int v : vertex) {
            numberInSearch.put(v, 0);
        }
        low = new HashMap<>();
        for (int v : vertex) {
            low.put(v, 0);
        }

        components = new ArrayList<>();
        cutPoints = new ArrayList<>();
        bridges = new ArrayList<>();

        for (int u : vertex)
            if (!visited.get(u))
                search(u, -1);
    }

    void search(int u, int p) {
        visited.put(u, true);

        curNumberInSearch++;

        low.put(u, curNumberInSearch);
        numberInSearch.put(u, curNumberInSearch);

        int children = 0;
        boolean cutPoint = false;

        for (int v : vertex) {
            Edge curEdge = new Edge(v, u);
            if (!edges.contains(curEdge)) {//if have not arc between current 'u' and 'v'
                continue;
            }
            if (v == p) {//should not go back
                continue;
            }

            if (visited.get(v)) {
                if (numberInSearch.get(v) < numberInSearch.get(u)) {//if reverse edge
                    stack.add(curEdge);
                    low.put(u, Math.min(low.get(u), numberInSearch.get(v)));
                }
            } else {
                ++children;
                stack.add(curEdge);
                search(v, u);
                low.put(u, Math.min(low.get(u), low.get(v)));
                if (low.get(v) >= numberInSearch.get(u)) {//means there is no reverse edges from childs to parents

                    cutPoint = true;//--------------------

                    List<Edge> component = new ArrayList<>();
                    int calc = 0;
                    while (!stack.isEmpty()) {
                        //
                        Edge x = stack.pop();
                        component.add(x);
                        calc++;
                        if (x.equals(curEdge)) {
                            if (calc == 1) bridges.add(curEdge);// biconnected component consisted of 1 edge is a bridge
                            break;
                        }
                    }
                    components.add(component);
                }
            }
        }
        if (p == -1)
            cutPoint = children >= 2;
        if (cutPoint)
            cutPoints.add(u);
    }
}