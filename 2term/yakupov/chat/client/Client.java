package yakupov.chat.client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.*;

import yakupov.chat.mode.Consts;

public class Client
{
    private BufferedReader in;
    private PrintWriter out;
    private Socket socket;

    private List<String> history;
    
    private Queue<String> deliveryQueue;
    public Queue<String> receiveQueue;

    private boolean exit = false;
    private String name;

    public Client() {
        history = new ArrayList<String>();
        history.clear();
        deliveryQueue = new PriorityQueue<String>();
        deliveryQueue.clear();

        receiveQueue = new PriorityQueue<String>();
        receiveQueue.clear();

        Scanner scan = new Scanner(System.in);

        System.out.println("Enter IP:");

        String ip = /*scan.nextLine();*/
        "127.000.000.001";

        try {
            socket = new Socket(ip, Consts.Port);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new PrintWriter(socket.getOutputStream(), true);

            System.out.print("Enter your nick-name:");
            name = scan.nextLine();
            out.println(name);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    //
    public void startMagic() {
        ClientGUI gui = new ClientGUI(this);
        Receiver receiver = new Receiver();
        receiver.start();

        gui.displaySetText("magic starts!", true);//////

        while (!exit) {
            sendMessages();
        }

        receiver.setStop();
        out.println("exit");
        close();
        System.exit(0);
    }

    synchronized private void sendMessages() {
        //System.out.println("sendMessages----");//////
        if (!deliveryQueue.isEmpty()) {
            System.out.println("<<" + deliveryQueue.toString() + ">>");//////
            for (String aDeliveryQueue : deliveryQueue) {
                System.out.println("sending from queue [" + getName() + "]: " + aDeliveryQueue);//////
                out.println(aDeliveryQueue);
            }
            deliveryQueue.clear();
        }
    }

    synchronized public void addMessageInQueue(String str) {
        if (str.equals("exit")) {
            exit();
        } else {
            System.out.println("adding in queue [" + getName() + "]: " + str);//////
            deliveryQueue.add(str);
            System.out.println("check adding in queue [" + getName() + "]: " + deliveryQueue.peek());//////
            history.add(str);
        }
        //System.out.println("<<" + deliveryQueue.toString() + ">>");//////
    }

    public void exit() {
        sendMessages();
        exit = true;
    }

    public String getName() {
        return name;
    }

    private void close() {
        try {
            in.close();
            out.close();
            socket.close();
        } catch (Exception e) {
            System.err.println("Streams or socket were not closed");
        }
    }

    private class Receiver extends Thread {

        private boolean stoped = false;

        public void setStop() {
            stoped = true;
        }

        @Override
        public void run() {
            try {
                while (!stoped) {
                    String str = in.readLine();
                    System.out.println("received: " + str);//////
                    receiveQueue.add(str);
                }
            } catch (IOException e) {
                System.err.println("Message receiving error");
                e.printStackTrace();
            }
        }
    }
}