package yakupov.list;

/**
 * Class 'List' - implements basic doubly-linked list's abilities
 * @author     Yakupov Maxim
 * @version    1.0
 * @since      JDK1.8
 */
public class List {

    /**
     * Class 'Element' - describes element of the doubly-linked list
     * @version 1.0
     */
    private class Element {
        char value;
        Element next;
        Element prev;

        /**
         * Constructor of class 'Element'
         * @param value Value for init element
         */
        Element(char value) {
            this.value = value;
            this.prev = null;
            this.next = null;
        }
    }

    Element begin;
    Element end;

    /**
     * Constructor of class 'List'
     */
    public List() {
        this.end = null;
        this.begin = null;
    }

    /**
     * Adds element in the end of the list
     * @param value Value for init element
     */
    public void insert(char value) {
        Element newEl = new Element(value);
        newEl.prev = this.end;
        if (this.begin != null) {
            this.end.next = newEl;
            this.end = this.end.next;
        }
        else {
            this.begin = newEl;
            this.end = this.begin;
        }
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
     * Writes elements of the list in 'System.out' in reverse order
     */
    public void printReverse() {
        Element currEl = this.end;
        while (currEl != null) {
            System.out.print(currEl.value);
            currEl = currEl.prev;
        }
    }

    /**
     * Returns 'true' if list is empty
     * @return 'true' if empty, 'false' in another way
     */
    public boolean isNull() {
        return (this.begin == null);
    }
}
