package yakupov;

import java.util.ArrayList;
import java.util.HashSet;

public class Main {

    public static void main(String[] args) {
        test("1-2 2-1 2-3 3-2 2-4 4-2 2-5 5-2 3-4 4-3 4-5 5-4 5-6 6-5");
        test("1-2 2-3 1-4 2-4 4-6 6-7 7-4");
    }

    public static boolean test(String testData) {
        Graph graph = new Graph();
        String[] str = testData.split(" ");
        for (String s : str)
        {
            String[] stt = s.split("-");
            int v1 = Integer.parseInt(stt[0]);
            int v2 = Integer.parseInt(stt[1]);
            graph.add(v1, v2);
        }

        System.out.println("-------------------------------------------");
        System.out.println("Graph: " + graph.toString());
        ArrayList<Edge> bridges = graph.bridges();
        for (Edge e : bridges) {
            System.out.println("Bridge: " + e.toString());
        }
        ArrayList<Integer> pointsOfJunction = graph.pointsOfJunction();
        for (Integer v : pointsOfJunction) {
            System.out.println("pointsOfJunction: " + v.toString());
        }
        HashSet<Graph> doublyConnectedComponent = graph.doublyConnectedComponent();
        for (Graph g : doublyConnectedComponent) {
            System.out.println("doublyConnectedComponent: [" + g.toString() + "]");
        }
        return true;
    }
}
