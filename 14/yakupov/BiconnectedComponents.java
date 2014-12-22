package yakupov;

import java.util.*;

public class BiconnectedComponents {

    HashMap<Integer, Boolean> visited;
    Stack<Edge> stack;
    int curNumberInSearch;
    HashMap<Integer, Integer> numberInSearch;
    HashMap<Integer, Integer> lowlink;
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
        lowlink = new HashMap<>();
        for (int v : vertex) {
            lowlink.put(v, 0);
        }

        components = new ArrayList<>();
        cutPoints = new ArrayList<>();
        bridges = new ArrayList<>();

        for (int u : vertex)
            if (!visited.get(u))
                dfs(u, -1);
    }

    void dfs(int u, int p) {
        visited.put(u, true);

        curNumberInSearch++;

        lowlink.put(u, curNumberInSearch);
        numberInSearch.put(u, curNumberInSearch);

        int children = 0;
        boolean cutPoint = false;

        for (int v : vertex) {
            Edge curEdge = new Edge(v, u);
            if (!edges.contains(curEdge)) {
                continue;
            }
            if (v == p)
                continue;

            if (visited.get(v)) {
                if (numberInSearch.get(v) < numberInSearch.get(u)) {
                    stack.add(curEdge);
                    lowlink.put(u, Math.min(lowlink.get(u), numberInSearch.get(v)));
                }
            } else {
                ++children;
                stack.add(curEdge);
                dfs(v, u);
                lowlink.put(u, Math.min(lowlink.get(u), lowlink.get(v)));
                if (lowlink.get(v) >= numberInSearch.get(u)) {
                    cutPoint = true;

                    List<Edge> component = new ArrayList<>();
                    int calc = 0;
                    while (!stack.isEmpty()) {
                        //
                        Edge x = stack.pop();
                        component.add(x);
                        calc++;
                        if (x.equals(curEdge)) {
                            if (calc == 1) bridges.add(curEdge);
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