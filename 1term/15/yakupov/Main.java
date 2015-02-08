package yakupov;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        System.out.println(test(false) ? "Passed" : "Failed");
    }

    public static boolean test(boolean log) {
        int[][] dataLinks = new int[9][];
        dataLinks[0] = new int[]{3, 4};
        dataLinks[1] = new int[]{4};
        dataLinks[2] = new int[]{};
        dataLinks[3] = new int[]{4,5};
        dataLinks[4] = new int[]{};
        dataLinks[5] = new int[]{8};
        dataLinks[6] = new int[]{5, 7};
        dataLinks[7] = new int[]{8};
        dataLinks[8] = new int[]{};
        int[] weights = new int[]{2, 4, 6, 4, 8, 4, 6, 1, 9};

        if (log) {
            new TasksOrderer(dataLinks, weights).print();
        }

        return new TasksOrderer(dataLinks, weights).getOrderedList().equals(
                new ArrayList<Integer>(){{
                    add(6);
                    add(7);
                    add(2);
                    add(1);
                    add(0);
                    add(3);
                    add(5);
                    add(8);
                    add(4);
                }}
        );
    }
}
