package yakupov.list;

/**
 * Class 'List' - implements basic singly-linked list's abilities
 * @author     Yakupov Maxim
 * @version    1.0
 * @since      JDK1.8
 */
public class SLList {

    /**
     * Class 'Element' - describes element of the doubly-linked list
     * @version 1.0
     */
    private class Element {
        char value;
        Element next;

        /**
         * Constructor of class 'Element'
         * @param value Value for init element
         */
        Element(char value) {
            this.value = value;
            this.next = null;
        }
    }

    Element begin;
    Element end;
    int length;

    /**
     * Constructor of class 'SLList'
     */
    public SLList() {
        this.begin = null;
        this.end = null;
        length = 0;
    }

    /**
     * Adds element in the end of the list
     * @param value Value for init element
     */
    public void insert(char value) {
        Element newEl = new Element(value);
        if (this.begin != null) {
            this.end.next = newEl;
            this.end = this.end.next;
        }
        else {
            this.begin = newEl;
            this.end = this.begin;
        }
        this.length++;
    }

    /**
     * Adds element in the beginning of the list
     * @param value Value for init element
     */
    public void insertInBeginning(char value) {
        Element newEl = new Element(value);
        if (this.begin != null) {
            newEl.next = this.begin;
            this.begin = newEl;
        }
        else {
            this.begin = newEl;
            this.end = this.begin;
        }
        this.length++;
    }

    /**
     * Returns value of element with position 'pos' (numeration begins with 0[zero])
     * @param pos Number of element
     * @return Value of element with number 'pos'
     * @throws WrongIndexException If there is no element with number 'pos' in the list
     */
    public char value(int pos) throws WrongIndexException {
        if (this.length <= pos || pos < 0) throw new WrongIndexException();
        Element curEl = this.begin;
        for (int i = 0; i < pos; i++) {
            curEl = curEl.next;
        }
        return curEl.value;
    }

    /**
     * Removes element with position 'pos' (numeration begins with 0[zero])
     * @param pos Number of element
     * @throws WrongIndexException If there is no element with number 'pos' in the list
     */
    public void remove(int pos) throws WrongIndexException {
        if (this.length <= pos || pos < 0) throw new WrongIndexException();
        if (pos == 0) {
            this.begin = this.begin.next;
            if (this.length == 1) this.end = null;
        } else {
            Element curPrevEl = this.begin;
            for (int i = 1; i < pos; i++) {
                curPrevEl = curPrevEl.next;
            }
            curPrevEl.next = curPrevEl.next.next;
        }
        this.length--;
    }

    /**
     * Writes elements of the list in 'System.out'
     */
    public void print() {
        Element currEl = this.begin;
        while (currEl != null) {
            System.out.print(currEl.value);
            currEl = currEl.next;
        }
    }

    /**
     * Returns 'true' if list is empty
     * @return 'true' if empty, 'false' in another way
     */
    public boolean isNull() {
        return (this.begin == null);
    }

    /**
     * Returns length of the list
     * @return Length of list
     */
    public int getLength() {
        return this.length;
    }
}
