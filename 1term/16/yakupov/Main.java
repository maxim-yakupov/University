package yakupov;

public class Main {

    public static void main(String[] args) {
        //number of circles
        int n = 4;
        System.out.println("Recursive version");
        System.out.print(rec_hanoi(n, 1, 3, 2));
        System.out.println("Non-recursive version");
        System.out.print(hanoi(n));
        System.out.println("----TESTS----");
        for (int i = 1; i <= 9; i++) {
            System.out.println(rec_hanoi(i, 1, 3, 2).toString().equals(hanoi(i).toString()) ? "Passed" : "Failed");
        }
    }

    static StringBuilder rec_hanoi(int n, int from, int to, int dop)
    {
        StringBuilder sB = new StringBuilder("");
        if (n == 0) return sB;
        sB
                .append(rec_hanoi(n - 1, from, dop, to))
                .append("from ")
                .append(from)
                .append(" to ")
                .append(to)
                .append("\n")
                .append(rec_hanoi(n - 1, dop, to, from));
        return sB;
    }

    // Algorithm taken from
    // http://www.hpmuseum.org/guest/kakima/hanoin.pdf
    static StringBuilder hanoi(int n)
    {
        StringBuilder sB = new StringBuilder("");
        for (long k = 1; k < (1 << n); k++)
        {
            // the mth move is from peg (m&m-1)%3 to
            // peg ((m|m-1)+1)%3, where the disks begin on peg 0
            long h1 = ((k & (k - 1)) % 3) + 1;
            long h2 = ((k | (k - 1)) + 1) % 3 + 1;
            // and finish on peg 1 or 2
            // according as whether the number of disks is even or odd.
            if (n % 2 == 0) {
                if (h1 == 2) {
                    h1 = 3;
                } else if (h1 == 3) {
                    h1 = 2;
                }
                if (h2 == 2) {
                    h2 = 3;
                } else if (h2 == 3) {
                    h2 = 2;
                }
            }
            sB
                    .append("from ")
                    .append(h1)
                    .append(" to ")
                    .append(h2)
                    .append("\n");
        }
        return sB;
    }
}
