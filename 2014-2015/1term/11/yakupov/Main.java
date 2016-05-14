package yakupov;

import java.io.*;
import java.util.TreeSet;

public class Main {

    public static void main(String[] args) throws IOException {
        System.out.println(test() ? "Passed" : "Failed");

        BufferedReader reader = getBufferedReader();
        TreeSet<Double> set = minSearch(reader.readLine() + '\n');
        for (Double el: set) {
            System.out.print(el + " ");
        }
        reader.close();
    }

    private static boolean test() {
        TreeSet<Double> set = new TreeSet<Double>();
        set.add(0.0);
        set.add(1.0);
        set.add(2.0);
        set.add(4.0);
        set.add(6.0);
        return minSearch("D = 1.0; 0.0, 2.0, 4.0, 0.0, 6.0, 1.0, 7.0, 6.0;").equals(set);
    }

    private static TreeSet<Double> minSearch(String str) {
        Tokeniser t = new Tokeniser(str);

        double d = t.nextDouble();
        TreeSet<Double> set = new TreeSet<Double>();
        double lastRead = t.nextDouble();
        set.add(lastRead);

        do {
            lastRead = t.nextDouble();
            if (!set.contains(lastRead)) set.add(lastRead);
            if (!t.hasNextDouble()) break;
        } while (         !(set.lower(lastRead) != null &&
                (lastRead - set.lower(lastRead)) <= d) &&
                !(set.higher(lastRead) != null &&
                        (set.higher(lastRead) - lastRead) <= d)
                );
        return set;
    }

    private static BufferedReader getBufferedReader() {
        return new BufferedReader(
                    new InputStreamReader(
                            System.in
                    )
            );
    }
}
