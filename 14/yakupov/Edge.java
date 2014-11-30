package yakupov;

public class Edge {
    Integer vertex1, vertex2;

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
        return (vertex1.equals(other.vertex1)) && (vertex2.equals(other.vertex2)) ||
                (vertex1.equals(other.vertex2)) && (vertex2.equals(other.vertex1));
    }

    @Override
    public int hashCode() {
        return vertex1.hashCode() + vertex2.hashCode();
    }

    @Override
    public String toString() {
        return vertex1.toString() + "-" + vertex2.toString();
    }
}