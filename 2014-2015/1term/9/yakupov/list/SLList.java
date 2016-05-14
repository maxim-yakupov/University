package yakupov.list;

/**
 * Class 'SLList' - implements small part of singly-linked list's abilities
 */
public class SLList {

    /**
     * Class 'Element' - describes element of the singly-linked list
     */
    public class Element {
        char value;
        public Element next;

        /**
         * Constructor of class 'Element'
         * @param value Value for init element
         */
        Element(char value) {
            this.value = value;
            this.next = null;
        }

    }

    public Element begin;
    public Element end;
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

    public boolean checkForCycles() {
        Element first = this.begin;
        Element second = this.begin.next;
        while (first != second) {
            if (first == null || second == null) return false;
            first = first.next;
            if (second.next != null) second = second.next.next;
            else return false;
        }
        return true;
    }
}
