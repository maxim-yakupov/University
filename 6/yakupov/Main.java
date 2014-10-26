package yakupov;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

public class Main {

    /**
     * The first strategy: dichotomy
     * @param x Number, which we should guess
     * @return Number of flicks, gained by guessing
     */
    private static int strategyFirst(int x){
        int flicks = 0;
        int leftBorder = 1;
        int rightBorder = 100;
        int delta = rightBorder - leftBorder;
        int guess = leftBorder + delta / 2;

        while (guess != x){
            if (guess < x){
                flicks += 1;
                leftBorder = guess;
                delta = rightBorder - leftBorder;
                guess = leftBorder + delta / 2;
                if (delta < 2){
                    guess = rightBorder;
                }
            } else {
                flicks += 2;
                rightBorder = guess;
                delta = rightBorder - leftBorder;
                guess = leftBorder + delta / 2;
                if (delta < 2){
                    guess = leftBorder;
                }
            }
        }
        return flicks;
    }

    /**
     * The second strategy: trichotomy
     * @param x Number, which we should guess
     * @return Number of flicks, gained by guessing
     */
    private static int strategySecond(int x){
        int flicks = 0;
        int leftBorder = 1;
        int rightBorder = 100;
        int delta = rightBorder - leftBorder;
        int guess = leftBorder + delta / 3;

        while (guess != x){
            if (guess < x){
                flicks += 1;
                leftBorder = guess;
                delta = rightBorder - leftBorder;
                if (delta < 3) {
                    if (delta == 2) {
                        guess = leftBorder + delta / 2;
                    } else {
                        guess = rightBorder;
                    }
                } else {
                    guess = leftBorder + delta / 3;
                }
            } else {
                flicks += 2;
                rightBorder = guess;
                delta = rightBorder - leftBorder;
                if (delta < 3) {
                    if (delta == 2) {
                        guess = leftBorder + delta / 2;
                    } else {
                        guess = leftBorder;
                    }
                } else {
                    guess = leftBorder + delta / 3;
                }
            }
        }
        return flicks;
    }

    /**
     * Writes comparing of strategies in file 'compare.txt'
     * (it shows, that this two strategies are equally effective)
     * P.S. strategySecond a bit better
     * @throws IOException
     */
    private static void compareStrategies() throws IOException  {
        PrintWriter myPrintWriter = new PrintWriter(new File("compare.txt"));
        int better = 0;
        int eq = 0;
        int worse = 0;

        int totalDeltaB = 0;
        int totalDeltaW = 0;
        for (int i = 1; i <= 100; i++){
            int s = strategySecond(i);
            int f = strategyFirst(i);

            if (s < f) { better++; totalDeltaB += f - s; }
            else if (s == f) { eq++; }
            else { worse++; totalDeltaW += s - f; }

            myPrintWriter.println(i + "." + (s < f ? "better " : "not better ") + "| strategySecond:" + s + " strategyFirst:" + f);
        }
        myPrintWriter.println("--------strategySecond-compares-with-strategyFirst---------");
        myPrintWriter.println("better:" + better + " eq:" + eq + " worse:" + worse);
        myPrintWriter.println("----------for-strategySecond----------");
        myPrintWriter.println("average win:" + ((double)totalDeltaB) / ((double)better) +
                " average lose:" + ((double)totalDeltaW) / ((double)worse));
        myPrintWriter.close();
    }

    public static void main(String[] args) throws IOException {

        PrintWriter myPrintWriter = new PrintWriter(new File("first_strategy_results.txt"));
        for (int i = 1; i <= 100; i++){
            myPrintWriter.println(i + ". " + strategyFirst(i));
        }
        myPrintWriter.close();

        myPrintWriter = new PrintWriter(new File("second_strategy_results.txt"));
        for (int i = 1; i <= 100; i++){
            myPrintWriter.println(i + ". " + strategySecond(i));
        }
        myPrintWriter.close();

        compareStrategies();
    }
}
