package yakupov;

public class Edge {
    int vertex1, vertex2;

    Edge(int v1, int v2) {
        vertex1 = v1;
        vertex2 = v2;
    }

    @Override
    public boolean equals(Object e) {
        if (this == e)
            return true;
        if (e == null)
            return false;
        if (getClass() != e.getClass())
            return false;
        Edge other = (Edge) e;
        return (vertex1 == other.vertex1) && (vertex2 == other.vertex2) ||
                (vertex1 == other.vertex2) && (vertex2 == other.vertex1);
    }

    @Override
    public int hashCode() {
        return Integer.hashCode(vertex1) + Integer.hashCode(vertex2);
    }

    @Override
    public String toString() {
        return Integer.toString(vertex1) + "-" + Integer.toString(vertex2);
    }
}