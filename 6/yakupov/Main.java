package yakupov;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.TreeSet;

public class Main {

    /**
     * dichotomy
     * @param x Number, which we should guess
     * @param leftBorder Left border of guessing
     * @param rightBorder Right border of guessing
     * @return Number of flicks, gained by guessing
     */
    private static int dichotomy(int x, int leftBorder, int rightBorder){
        int flicks = 0;
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
     * The first strategy: dichotomy
     * @param x Number, which we should guess
     * @return Number of flicks, gained by guessing
     */
    private static int strategyFirst(int x){
        return dichotomy(x, 1, 100);
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
     * How many flicks we got for try
     * @param x Number, which we should guess
     * @param guess Guessing
     * @return 2 if x less,
     *         1 if x more,
     *         0 if x=guess(done)
     */
    private static int flicksNumber(int x, int guess) {
        if (guess > x) { return 2; }
        else if (guess < x) { return 1; }
        return 0;
    }

    /**
     * The third strategy: fibonacci
     * @param x Number, which we should guess
     * @return Number of flicks, gained by guessing
     */
    private static int strategyThird(int x){
        int fib = 21;
        int fibPrev = 13;

        int flicks = 0;

        TreeSet<Integer> list = new TreeSet<Integer>(); //list of bad guessings

        //dividing interval from 1 to 100 for 3 parts
        int guess1 = 34;
        int guess2 = 67;
        if (x == guess1) return 0; // try 34
        if (x == guess2) return 1; // try 67

        int guess = 0;

        if (x < guess1){ // x < 34
            guess = 1;
            flicks += flicksNumber(x, guess1);
            flicks += flicksNumber(x, guess);
            list.add(guess1);
        }
        else if (x < guess2){ // 34 < x < 67
            guess = guess1;
            flicks += flicksNumber(x, guess1);
            flicks += flicksNumber(x, guess2);
            list.add(guess1);
            list.add(guess2);
        }
        else { // x > 67
            guess = guess2;
            flicks += flicksNumber(x, guess1);
            flicks += flicksNumber(x, guess2);
            list.add(guess2);
        }

        int curFlicks = flicksNumber(x,guess);
        int prevFlicks;
        int prevGuess;

        do {
            prevGuess = guess;
            prevFlicks = curFlicks;

            if(!list.contains(prevGuess)){
                list.add(prevGuess);
            }

            while (list.contains(guess) && x != guess){
                int t = fib;
                fib = fibPrev;
                fibPrev = t - fibPrev;

                curFlicks = flicksNumber(x,guess);
                if (curFlicks == 2) {
                    guess -= fib;
                }
                else if(curFlicks == 1){
                    guess += fib;
                }
            }
            curFlicks = flicksNumber(x,guess);
            flicks += flicksNumber(x,guess);

        } while (prevFlicks == curFlicks && x != guess);

        if (x != guess) {
            flicks += dichotomy(x,
                    (guess < prevGuess ? guess : prevGuess),
                    (guess > prevGuess ? guess : prevGuess)
            );
        }

        return flicks;
    }

    /**
     * Writes comparing of strategies in file 'compare.txt'
     * (it shows, that first two strategies are equally effective and the third is the best)
     * @throws IOException
     */
    private static void compareStrategies() throws IOException  {
        PrintWriter myPrintWriter = new PrintWriter(new File("compare.txt"));
        int flicksTotalFirst = 0;
        int flicksTotalSecond = 0;
        int flicksTotalThird = 0;

        int worstFirst = 0;
        int worstSecond = 0;
        int worstThird = 0;

        for (int i = 1; i <= 100; i++){
            int f = strategyFirst(i);
            int s = strategySecond(i);
            int t = strategyThird(i);

            if (f > worstFirst) worstFirst = f;
            if (s > worstSecond) worstSecond = s;
            if (t > worstThird) worstThird = t;

            flicksTotalFirst += f;
            flicksTotalSecond += s;
            flicksTotalThird += t;

            StringBuilder bestStrat = new StringBuilder("");

            if (f < s && f < t) { bestStrat.append("first             "); }
            else if (s < f && s < t) { bestStrat.append("second            "); }
            else if (t < f && t < s) { bestStrat.append("third             "); }
            else if (f < t && s == f) { bestStrat.append("first second      "); }
            else if (s < f && s == t) { bestStrat.append("second third      "); }
            else if (f < s && t == f) { bestStrat.append("first third       "); }
            else { bestStrat.append("first second third"); }

            myPrintWriter.println(i + ". best strategy: " + bestStrat +
                    "| strategyFirst:" + f +
                    " strategySecond:" + s +
                    " strategyThird:" + t);
        }
        myPrintWriter.println("--------average-score---------");
        myPrintWriter.println("first strategy:" + (double) flicksTotalFirst / 100.0);
        myPrintWriter.println("second strategy:" + (double) flicksTotalSecond / 100.0);
        myPrintWriter.println("third strategy:" + (double) flicksTotalThird / 100.0);
        myPrintWriter.println("--------worst-score---------");
        myPrintWriter.println("first strategy:" + worstFirst);
        myPrintWriter.println("second strategy:" + worstSecond);
        myPrintWriter.println("third strategy:" + worstThird);
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

        myPrintWriter = new PrintWriter(new File("third_strategy_results.txt"));
        for (int i = 1; i <= 100; i++){
            myPrintWriter.println(i + ". " + strategyThird(i));
        }
        myPrintWriter.close();

        compareStrategies();
    }
}
