package yakupov;

import java.io.*;
import java.util.Arrays;

public class Main{

    static class Stack {
        RandomAccessFile raf;
        int top;
        File file;
        byte s[];
        int shift;
        int n;

        Stack(int n, File f) throws IOException {
            raf = new RandomAccessFile(f, "rw");
            this.n = n;
            file = f;
            shift = 0;
            s = new byte[2 * n];
            top = -1;
        }

        private int topInd() {
            return top % (2 * n);
        }

        private int beginningInd() {
            return shift % (2 * n);
        }

        void push(byte b) throws IOException {
            top++;
            if (top != 0 && topInd() == beginningInd()) {
                loadOut();
            }
            s[topInd()] = b;
        }

        byte top() {
            return s[topInd()];
        }

        byte pop() throws IOException {
            byte t = s[topInd()];
            if (topInd() == beginningInd()) {
                loadIn();
            }
            top--;
            return t;
        }

        boolean isEmpty() {
            return top == -1;
        }

        private void loadOut() throws IOException {
            raf.seek(raf.length());
            raf.write(s, beginningInd(), n);
            shift += n;
        }

        private void loadIn() throws IOException {
            if (raf.length() == 0) {
                return;
            }
            shift -= n;
            raf.seek(raf.length() - n);
            raf.read(s, beginningInd(), n);
            raf.setLength(raf.length() - n);
        }

        void clear() throws IOException {
            top = -1;
            shift = 0;
            PrintStream fstr = new PrintStream(
                    new BufferedOutputStream(
                            new FileOutputStream(file, false)
                    )
            );
            fstr.print("");
            fstr.close();
        }
    }

    public static void main(String[] args) throws IOException {
        File file = new File("buffer.txt");
        String str = "123456789asdfghjkl;";
        System.out.println(test(2, file, str.getBytes()) ? "Passed" : "Failed");
    }

    static boolean test(int n, File file, byte[] str) throws IOException{
        Stack s = new Stack(n, file);
        //filling stack
        for (int i = 0; i < str.length; i++) {
            s.push(
                    str[i]
            );
        }
        //reading from stack(reverse order of basic array)
        byte[] tt = new byte[str.length];
        int i = 0;
        while (!s.isEmpty()) {
            tt[i] = s.pop();
            i++;
        }
        //reverse popped data(reconstruct order)
        byte[] tAft = new byte[str.length];
        while (i > 0) {
            i--;
            tAft[i] = tt[tt.length - i - 1];
        }
        s.clear();
        //
        for (byte b : tAft) {
            System.out.print((char) b);
        }
        System.out.println();
        for (byte b : str) {
            System.out.print((char) b);
        }
        System.out.println();
        //
        return Arrays.equals(tAft, str);
    }
}
