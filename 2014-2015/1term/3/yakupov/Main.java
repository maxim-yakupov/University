package yakupov;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.Scanner;

public class Main {

    /**
     * Swaps two elements in list
     * @param a List
     * @param i First position
     * @param j Second position
     */
    public static void swap(LinkedList<Integer> a, int i, int j){
        int t = a.get(i);
        a.set(i, a.get(j));
        a.set(j, t);
    }

    /**
     * Finds k-th maximal element
     * @param a List
     * @param leftBorder Left border of a part
     * @param rightBorder Right border of a part
     * @param k Number of searching maximal
     * @return k-th maximal element
     */
    public static int findKMax(LinkedList<Integer> a, int leftBorder, int rightBorder, int k){
        int x = a.get(k);
        int i = leftBorder;
        int j = rightBorder;

        while (i <= j){
            while (a.get(i) < x) i++;
            while (a.get(j) > x) j--;

            if (i <= j){
                swap(a, i, j);
                i++;
                j--;
            }
        }

        if ((leftBorder <= k) && (k <= j)){
            return findKMax(a, leftBorder, j, k);
        }

        if ((i <= k) && (k <= rightBorder)){
            return findKMax(a, i, rightBorder, k);
        }

        return a.get(k);
    }

    public static void main(String[] args) throws IOException {
        File readFile = new File("input.txt");
        File writeFile = new File("output.txt");

        Scanner myScanner = new Scanner(readFile);
        PrintWriter myPrintWriter = new PrintWriter(writeFile);
        LinkedList<Integer> a = new LinkedList<Integer>();
        a.clear();

        int k = myScanner.nextInt() - 1;

        while (myScanner.hasNextInt()){
            a.add(myScanner.nextInt());
        }

        myPrintWriter.print(findKMax(a, 0, a.size() - 1, k));

        myScanner.close();
        myPrintWriter.close();
    }
}

