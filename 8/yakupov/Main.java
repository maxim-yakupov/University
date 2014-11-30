package yakupov;

import java.util.Arrays;
import java.util.Random;

public class Main {

    public static void main(String[] args) {
        tests(555);
    }

    public static void tests(int quantity) {
        int success = 0;
        Random rand;
        for (int kek = 1; kek <= quantity; kek++) {
            rand = new Random(System.nanoTime());
            int[] data = new int[kek];

            for (int i = 0; i < data.length; i++) {
                data[i] = rand.nextInt(2000);
//                System.out.print(data[i] + " ");
            }
//            System.out.println();

            int[] copy = data.clone();
            qSortSingleCallRecursion(copy, 0, copy.length - 1);
            Arrays.sort(data);

            boolean check = Arrays.equals(copy, data);
            if (check) {
                success++;
            }
            System.out.println(kek + ") " + (check ? "Passed" : "Failed"));
        }
        System.out.println(success + " of " + quantity + " done successfully");
    }

    /**
     * Sorts array
     * @param mas Array
     * @param leftBorder Left border of array
     * @param rightBorder Right border of array
     */
    public static void qSortSingleCallRecursion(int[] mas, int leftBorder, int rightBorder)
    {
        while (leftBorder < rightBorder) {
            //find index of placed on correct index number
            int foundPos = placeInRightPos(mas, leftBorder, rightBorder);
            //sort part, which before foundPos
            qSortSingleCallRecursion(mas, leftBorder, foundPos);
            //shift right leftBorder pointer for new while iteration
            leftBorder = foundPos + 1;
        }
    }

    /**
     * Places x = mas[med] (med - random number) in correct position
     * in segment [leftBorder, rightBorder] in array mas
     * (based on Hoare-partition algorithm)
     * @param mas Array
     * @param leftBorder left edge index
     * @param rightBorder right edge index
     * @return Correct index of x
     */
    public static int placeInRightPos(int[] mas, int leftBorder, int rightBorder)
    {
        Random rnd = new Random();
        int med = rnd.nextInt(rightBorder - leftBorder + 1) + leftBorder;
        int x = mas[med];
        int i = leftBorder - 1;
        int j = rightBorder + 1;
        while (i < j) {
            do {
                i++;
            } while (mas[i] < x);
            do {
                j--;
            } while (x < mas[j]);
            if (i < j) {
                swap(mas, i, j);
            }
        }
        return j;
    }

    public static void swap(int[] mas, int leftBorder, int rightBorder)
    {
        int temp = mas[leftBorder];
        mas[leftBorder] = mas[rightBorder];
        mas[rightBorder] = temp;
    }
}
