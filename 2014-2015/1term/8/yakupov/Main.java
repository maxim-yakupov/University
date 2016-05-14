package yakupov;

import java.util.Arrays;
import java.util.Random;

public class Main {

    public static void main(String[] args) {
        tests(555);
    }

    public static void tests(int quantity) {
        System.out.println("=================TESTS===================");
        int
                success = 0,
                wikiSuccess = 0;
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
            int[] qs = data.clone();

            qsort(qs, 0, qs.length - 1);
            qSortSingleCallRecursion(copy, 0, copy.length - 1);

            Arrays.sort(data);

            boolean check = Arrays.equals(copy, data),
                    wikiCheck = Arrays.equals(qs, data);
            if (check) {
                success++;
            }
            if (wikiCheck) {
                wikiSuccess++;
            }
            System.out.println(kek + ")");
            System.out.println("Mine:  " + (check ? "Passed" : "Failed"));
            System.out.println("Wiki:  " + (wikiCheck ? "Passed" : "Failed"));
        }
        System.out.println("-----------------------------------------");
        System.out.println("Mine:  " + success + " of " + quantity + " done successfully");
        System.out.println("Wiki:  " + wikiSuccess + " of " + quantity + " done successfully");
        System.out.println("================END==TESTS===============");
    }

    /**
     * qSort implementation from Wikipedia
     * @param a Array
     * @param l Left border
     * @param r Right border
     */
    public static void qsort(int[] a, int l, int r){
        if (l == r) return;//if length equals 1 - finish
        if ((r - l) == 1 && a[l] < a[r]) {
            swap(a, l, r);//if length equals 2 - swap if necessary & finish
        }
        do {//do until both of borders become equal
            int
                    i = l,
                    j = r,
                    med = a[(i + j) / 2];

            do {
                while (a[i] < med) {
                    i++;
                }
                while (a[j] > med) {
                    j--;
                }
                if (i <= j){
                    if (i < j) {
                        swap(a, i, j);
                    }
                    i++;
                    j--;
                }
            } while (i <= j);

            if (j - l < r - i){//in part, which length is less, run qsort & shift border
                if (l < j) {
                    qsort(a, l, j);
                }
                l = i;
            } else {
                if (i < r) {
                    qsort(a, i, r);
                }
                r = j;
            }
        } while (l != r);
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
        while (true) {
            do {
                i++;
            } while (mas[i] < x);
            do {
                j--;
            } while (x < mas[j]);
            if (i < j) {
                swap(mas, i, j);
            } else {
                return j;
            }
        }
    }

    public static void swap(int[] mas, int leftBorder, int rightBorder)
    {
        int temp = mas[leftBorder];
        mas[leftBorder] = mas[rightBorder];
        mas[rightBorder] = temp;
    }
}
