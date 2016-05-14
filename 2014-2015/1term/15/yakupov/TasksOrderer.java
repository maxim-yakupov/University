package yakupov;

import java.util.ArrayList;
import java.util.Collections;

public class TasksOrderer {
    private int[][] dataLinks;
    private ArrayList<Integer> orderedList;

    private int[] time;

    TasksOrderer(int[][] connections, int[] times)
    {
        time = times;

        orderedList = new ArrayList<Integer>();
        dataLinks = new int[time.length][];

        for (int i = 0; i < time.length; i++) {
            dataLinks[i] = connections[i].clone();
        }
        order();
    }

    private void order()
    {
        for (int i = 0; i < time.length; i++) {
            if (!orderedList.contains(i)) {
                search(i);
            }
        }
        Collections.reverse(orderedList);
    }

    public void print() {
        int elapsedTime = 0;

        for (int task : orderedList) {
            System.out.println("Number of task: " + task + " (time: " + elapsedTime + ")");
            elapsedTime += time[task];
        }
        System.out.println("End of execution. Elapsed time: " + elapsedTime);
    }

    public ArrayList<Integer> getOrderedList() {
        return (ArrayList<Integer>) orderedList.clone();
    }

    public int getTime(int task) {
        return time[task];
    }

    private void search(int task) {
        for (int i : dataLinks[task]) {
            if (!orderedList.contains(i)) {
                search(i);
            }
        }
        orderedList.add(task);
    }
}
