package yakupov;

import yakupov.list.SLList;

public class Main {

    public static void main(String[] args) {
        SLList list = new SLList();
        list.insert('1');
        list.insert('2');
        list.insert('3');
        list.end.next = list.begin;
        System.out.println(list.checkForCycles() ? "cycled" : "not cycled");

        list = new SLList();
        list.insert('1');
        list.insert('2');
        list.insert('3');
        System.out.println(list.checkForCycles() ? "cycled" : "not cycled");
    }
}
