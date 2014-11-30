package yakupov;

import java.util.HashSet;

public class Main {

    public static void main(String[] args) {
        Graph graph = new Graph();
        makeTests();

        String[] str = ("1-2 2-1 2-3 3-2 2-4 4-2 2-5 5-2 3-4 4-3 4-5 5-4 5-6 6-5").split(" ");
        System.out.print("Input string:");
        for (String s : str)
        {
            System.out.print(" " + s);
            String[] stt = s.split("-");
            int v1 = Integer.parseInt(stt[0]);
            int v2 = Integer.parseInt(stt[1]);
            graph.add(v1, v2);
        }
        System.out.println();

        System.out.println("Before changing:" + graph.toString());
        String[] forDel = ("1-2 2-3 3-2 2-5 5-2 3-4 5-4 5-6 6-5").split(" ");
        for (String s : forDel) {
            String[] stt = s.split("-");
            int v1 = Integer.parseInt(stt[0]);
            int v2 = Integer.parseInt(stt[1]);
            System.out.println("Trying to remove " + v1 + "-" + v2 + ": "
                    + (graph.remove(v1, v2) ? "success" : "not in graph")
            );
        }
        System.out.println("After changing :  " + graph.toString());
    }

    private static void makeTests() {
        HashSet<String> tests = new HashSet<String>();
        tests.add("1-2 2-3 2-4 2-5 3-4 4-5 5-6");
        tests.add("1-2 2-1 2-3 3-2 2-4 4-2 2-5 5-2 3-4 4-3 4-5 5-4 5-6 6-5");
        tests.add("1-1 1-1 1-2 2-3 3-1");
        tests.add("1-2 1-5 2-3 2-4 2-5 3-4 4-5");
        System.out.println("--------TESTS--------");
        for (String test : tests) {
            System.out.println(test(test) ? "Passed." : "Failed. test str: '" + test + "'");
        }
        System.out.println("-----END-OF-TESTS-----");
    }

    public static boolean test(String testData) {
        Graph graph = new Graph();
        HashSet<Edge> set = new HashSet<Edge>();
        String[] str = testData.split(" ");
        for (String s : str)
        {
            String[] stt = s.split("-");
            int v1 = Integer.parseInt(stt[0]);
            int v2 = Integer.parseInt(stt[1]);
            graph.add(v1, v2);
            Edge fEdge = new Edge(v1, v2);
            if (!fEdge.equals(new Edge(v2, v1))) {
                return false;
            }
            set.add(fEdge);
        }

        for (Edge e : set) {
            if (!graph.contains(e)) {
                return false;
            }
        }
        return true;
    }
}
