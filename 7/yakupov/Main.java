package yakupov;

import java.io.*;
import java.util.Arrays;

public class Main{

    static class Stack {
        int top;
        File file;
        byte s[];
        int n;

        Stack(int n, File f) {
            this.n = n;
            file = f;
            s = new byte[2 * n];
            top = -1;
        }

        void push(byte b) throws IOException {
            top++;
            if (top == 2 * n) {
                loadOut();
            }
            s[top] = b;
        }

        byte top() {
            return s[top];
        }

        byte pop() throws IOException {
            byte t = s[top];
            if (top == 0) {
                loadIn();
            }
            top--;
            return t;
        }
        boolean isEmpty() {
            return top == -1;
        }

        private void loadOut() throws IOException {
            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            byte tarr[] = new byte[n];
            System.arraycopy(s, 0, tarr, 0, n);
            raf.seek(raf.length());
            raf.write(tarr);
            raf.close();
            top -= n;
            System.arraycopy(s, n, s, 0, n);
        }

        private void loadIn() throws IOException {
            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            if (raf.length() == 0) {
                raf.close();
                return;
            }
            raf.seek(raf.length() - n);
            byte[] temp = raf.readLine().getBytes();
            System.arraycopy(temp, 0, s, 0, n);

            raf.setLength(raf.length() - n);
            raf.close();

            top += n;
        }

        void clear() throws IOException {
            top = -1;
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
        String str = "0123456789asdfghjkl;";
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
        return Arrays.equals(tAft, str);
    }
}
