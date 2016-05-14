package yakupov;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StringReader;

public class Main {

    /**
     * Class of tree
     */
    private static class TreeElement {
        char value;
        TreeElement leftChild;
        TreeElement rightChild;

        /**
         * Constructor
         * @param v Value
         * @param l leftChild
         * @param r rightChild
         */
        TreeElement(char v, TreeElement l, TreeElement r) {
            this.value = v;
            this.leftChild = l;
            this.rightChild = r;
        }

        /**
         * Returns priority of operation in element
         * @return 0 if letter;
         *         1 if '+', '-';
         *         2 if '*',
         *         3 if '/'
         */
        public int priority() {
            int p = 0;
            if (this.value == '/') {
                p = 4; // cause not associative operation
            } else if (this.value == '*') {
                p = 3;
            } else if (this.value == '-') {
                p = 2;
            } else if (this.value == '+') {
                p = 1;
            }
            return p;
        }
        public boolean isAssoc(char op) {
            return op == '/' || op == '-';
        }
        /**
         * Makes toInfex
         * @return String with expression
         */
        public StringBuilder toInfex() {
            StringBuilder str = new StringBuilder();
            if (this.priority() == 0) {
                str.append(this.value);
            } else {
                String lStr = leftChild.toInfex().toString();
                String rStr = rightChild.toInfex().toString();

                if (((this.priority() > leftChild.priority())
                ) &&
                        (leftChild.priority() != 0)) {
                    str.append('(');
                    str.append(lStr);
                    str.append(')');
                } else {
                    str.append(lStr);
                }

                str.append(this.value);

                if ((this.priority() > rightChild.priority() ||
                        (this.priority() == rightChild.priority()  && isAssoc(this.value))
                ) &&
                        (rightChild.priority() != 0)) {
                    str.append('(');
                    str.append(rStr);
                    str.append(')');
                } else {
                    str.append(rStr);
                }
            }
            return str;
        }
    }

    /**
     * Makes tree
     * @param buffered_reader BufferedReader, from which we reading
     * @return Red TreeElement
     * @throws IOException If problems with reading
     */
    public static TreeElement readTreeElement(BufferedReader buffered_reader) throws IOException {
        char ch = (char) buffered_reader.read();
        if (ch != '*' &&
                ch != '/' &&
                ch != '+' &&
                ch != '-'
        ) {
            return new TreeElement(ch, null, null);
        } else {
            return new TreeElement(ch,
                    readTreeElement(buffered_reader),
                    readTreeElement(buffered_reader)
            );
        }
    }

    public static void main(String[] args) throws IOException{
        System.out.println(test_bypass() ? "Test passed" : "Test FAILED");

            System.out.print("Write expression in prefix form: ");
            TreeElement root = readTreeElement(new BufferedReader(
                    new InputStreamReader(System.in)
            ));
            System.out.print("Result: ");
            System.out.print(root.toInfex());
    }

    /**
     * Test
     * @return 'true' if passed, 'false' if failed
     */
    private static boolean test_bypass() throws IOException {
        return (getTreeElement("-*/a-b+cde+f+gh").toInfex().
                toString().equals("a/(b-(c+d))*e-(f+g+h)"));
    }

    private static TreeElement getTreeElement(String s) throws IOException {
        return readTreeElement(
                            new BufferedReader(
                                    new StringReader(s)
                            )
                       );
    }
}