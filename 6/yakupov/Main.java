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

    /*
    Обоснование алгоритма superScientificAlgorithm
f(0) = 1
- за ноль щелбанов гарантированно угадать число мы можем только на массиве длиной не более 1
(если у нас всего одно число, то мы его сразу угадываем)
f(1) = 2
- за один щелбан гарантированно угадать число мы можем только на массиве длиной не более 2
(берем первый элемент, если угадали, то 0 щелбанов, если нет, то он меньше второго, которое загаданное -> 1 щелбан)

Выполнив бросок, мы либо угадаем число(0 щелбанов),
либо назовем число меньшее загаданного(1 щелбан),
либо назовем число большее загаданного(2 щелбана)

Случай "Назвали число меньшее загаданного(1 щелбан)":
за 1 щелбан гарантированно можем угадать на массиве вплоть до длины 2(из f(1) = 2)
Т.е. (наше_число)[массив_длины_<=2_]
Итого: 1 + 1 щелбан в худшем случае

Случай "Назвали число большее загаданного(2 щелбана)":
за 0 щелбанов гарантированно можем угадать на массиве вплоть до длины 1(из f(0) = 1)
Т.е. [массив_длины_<=1_](наше_число)
Итого: 2 + 0 щелбанов в худшем случае

Объединияя, получим, что за 2 щелбана мы можем угадать число на массиве вплоть до длины f(2) = f(0) + 1 + f(1).
f(2) = 1 + 1 + 2 = 4.

Аналогично можем расписывать дальше. Это эквивалентно такой формуле: f(k) = 1 + f(k - 1) + f(k - 2)

f(3) = 1 + 4 + 2 = 7
f(4) = 1 + 7 + 4 = 12
f(5) = 1 + 12 + 7 = 20
f(6) = 1 + 20 + 12 = 33
f(7) = 1 + 33 + 20 = 54
f(8) = 1 + 54 + 33 = 88
f(9) = 1 + 88 + 54 = 143

Таким образом, мы можем гарантированно найти загаданное число на упорядоченном массиве длины 100 за 9 щелбанов
     */
    /**
     * f[k] - length of a part, in which we can guaranty finding of 'x' with cost = 'k' flicks
     */
    static int[] f = {1, 2, 4, 7, 12, 20, 33, 54, 88, 143};

    /**
     * How much flicks we gain by searching 'x' in range 1..100 with function superScientificAlgorithm()
     * @param x Number, which we should guess
     * @return Number of gained flicks
     */
    private static int findX(int x){
        return superScientificAlgorithm(1, 100, x, 9);
    }

    /**
     * How much flicks we gain by searching 'x' in range leftBorder..rightBorder
     * @param leftBorder Minimal element in range
     * @param rightBorder Maximal element in range
     * @param x Number, which we should guess
     * @param flicksAllowed Maximal amount of flicks, we want to get
     * @return Number of gained flicks
     */
    private static int superScientificAlgorithm(int leftBorder, int rightBorder, int x, int flicksAllowed){
        int delta = rightBorder - leftBorder;
        //comparing of delta value for check if algorithm is correct
        if ((flicksAllowed == 1) && (delta == 1)) {
            if (leftBorder == x) {
                return 0;
            } else if (rightBorder == x) {
                return 1;
            }
        } else if ((flicksAllowed == 0) && (leftBorder == x) && (delta == 0)) {
            return 0;
        }
        if (delta < f[flicksAllowed - 2]) {
            flicksAllowed--;
        }
        int guess = leftBorder + f[flicksAllowed - 2];
        if (guess == x) {
            return 0;
        } else if (guess < x) {
            return 1 + superScientificAlgorithm(guess + 1, rightBorder, x, flicksAllowed - 1);
        } else {
            return 2 + superScientificAlgorithm(leftBorder, guess - 1, x, flicksAllowed - 2);
        }
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
        int flicksTotalSS = 0;

        int worstFirst = 0;
        int worstSecond = 0;
        int worstThird = 0;
        int worstSS = 0;

        for (int i = 1; i <= 100; i++){
            int f = strategyFirst(i);
            int s = strategySecond(i);
            int t = strategyThird(i);
            int SS = findX(i);

            if (f > worstFirst) worstFirst = f;
            if (s > worstSecond) worstSecond = s;
            if (t > worstThird) worstThird = t;
            if (SS > worstSS) worstSS = SS;


            flicksTotalFirst += f;
            flicksTotalSecond += s;
            flicksTotalThird += t;
            flicksTotalSS += SS;

            StringBuilder bestStrat = new StringBuilder("");
//
            if (f < s && f < t) {
                if (SS < f) {
                    bestStrat.append("SS ");
                } else {
                    bestStrat.append("   ");
                }
                bestStrat.append("first             ");
            }
            else if (s < f && s < t) {
                if (SS < s) {
                    bestStrat.append("SS ");
                } else {
                    bestStrat.append("   ");
                }
                bestStrat.append("second            ");
            }
            else if (t < f && t < s) {
                if (SS < t) {
                    bestStrat.append("SS ");
                }else {
                    bestStrat.append("   ");
                }
                bestStrat.append("third             ");
            }
            else if (f < t && s == f) {
                if (SS < f) {
                    bestStrat.append("SS ");
                }else {
                    bestStrat.append("   ");
                }
                bestStrat.append("first second      ");
            }
            else if (s < f && s == t) {
                if (SS < s) {
                    bestStrat.append("SS ");
                }else {
                    bestStrat.append("   ");
                }
                bestStrat.append("second third      ");
            }
            else if (f < s && t == f) {
                if (SS < f) {
                    bestStrat.append("SS ");
                }else {
                    bestStrat.append("   ");
                }
                bestStrat.append("first third       ");
            }
            else {
                if (SS < f) {
                    bestStrat.append("SS ");
                }else {
                    bestStrat.append("   ");
                }
                bestStrat.append("first second third");
            }
//
            myPrintWriter.println(i + ". best strategy: " + bestStrat +
                    "| strategyFirst:" + f +
                    " strategySecond:" + s +
                    " strategyThird:" + t +
                    " my SUPA STRRRRRATEGY:" + SS);
        }
        myPrintWriter.println("--------average-score---------");
        myPrintWriter.println("first strategy:" + (double) flicksTotalFirst / 100.0);
        myPrintWriter.println("second strategy:" + (double) flicksTotalSecond / 100.0);
        myPrintWriter.println("third strategy:" + (double) flicksTotalThird / 100.0);
        myPrintWriter.println("SUPA strategy:" + (double) flicksTotalSS / 100.0);
        myPrintWriter.println("--------worst-score---------");
        myPrintWriter.println("first strategy:" + worstFirst);
        myPrintWriter.println("second strategy:" + worstSecond);
        myPrintWriter.println("third strategy:" + worstThird);
        myPrintWriter.println("SUPA strategy:" + worstSS);
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

        myPrintWriter = new PrintWriter(new File("SUPA_strategy_results.txt"));
        for (int i = 1; i <= 100; i++){
            myPrintWriter.println(i + ". " + findX(i));
        }
        myPrintWriter.close();

        compareStrategies();
    }
}
