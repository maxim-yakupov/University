package yakupov.chat.client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.*;

import yakupov.chat.mode.Consts;

/**
 * Class of chat's client
 */
public class Client
{
    private BufferedReader in;
    private PrintWriter out;
    private Socket socket;

    private List<String> history;
    
    private Queue<String> deliveryQueue;
    public Queue<String> receiveQueue;

    private Receiver receiver;
    private ClientGUI gui;

    private boolean exit = false;
    private String name;

    /**
     * Constructor of 'Client' class
     *
     * Reads from console data to make connection with server;
     * runs GUI
     */
    public Client(){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter IP:");
        String ip = /*scan.nextLine();*/
                "localhost";
        System.out.print("Enter your nick-name:");
        String enteredName = scan.nextLine();
        new Client(ip, enteredName)
                .startGUI();
    }

    /**
     * Makes initialization and starts receiver-thread
     * @param ip IP of server
     * @param enteredName Nick-name of user
     */
    private Client(String ip, String enteredName) {
        history = new ArrayList<String>();
        history.clear();
        deliveryQueue = new PriorityQueue<String>();
        deliveryQueue.clear();

        receiveQueue = new PriorityQueue<String>();
        receiveQueue.clear();

        name = enteredName;

        try {
            socket = new Socket(ip, Consts.Port);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new PrintWriter(socket.getOutputStream(), true);

            receiver = new Receiver();
            receiver.start();

            out.println(name);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Activates GUI and runs sending of messages
     */
    private void startGUI() {
        gui = new ClientGUI(this);

        while (!exit) {
            sendMessages();
        }

        if (!exit) exit();
        close();
        System.exit(0);
    }

    /**
     * Sends messages from delivery queue
     */
    synchronized private void sendMessages() {
        if (!deliveryQueue.isEmpty()) {
            for (String aDeliveryQueue : deliveryQueue) {
                System.out.println("sending from queue [" + getName() + "]: " + aDeliveryQueue);//////
                out.println(aDeliveryQueue);
            }
            deliveryQueue.clear();
        }
    }

    /**
     * Adds message to delivery queue
     * @param str Message string
     */
    synchronized public void addMessageInQueue(String str) {
        if (str.equals(Consts.Exit)) {
            exit();
        } else {
            System.out.println("adding in queue [" + getName() + "]: " + str);//////
            deliveryQueue.add(str);
            System.out.println("check adding in queue [" + getName() + "]: " + deliveryQueue.peek());//////
            history.add(str);
        }
    }

    /**
     * Calls, when want to close client
     */
    public void exit() {
        receiver.setStop();
        sendMessages();
        exit = true;
        out.println(Consts.Exit);
    }

    /**
     * Returns users nick-name
     * @return nick-name
     */
    public String getName() {
        return name;
    }

    /**
     * Closes I/O Streams and socket;
     */
    private void close() {
        try {
            in.close();
            out.close();
            socket.close();
        } catch (Exception e) {
            System.err.println("Streams or socket were not closed");
        }
    }

    /**
     * Class, which receives messages from server
     */
    private class Receiver extends Thread {

        private boolean stoped = false;

        /**
         * Stops receiving
         * (makes flag 'stoped' true)
         */
        public void setStop() {
            stoped = true;
        }

        /**
         * Receives messages from server and adds them to receive queue
         */
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
            } catch (NullPointerException e) {
                System.err.println("NullPointer error while adding message to receive queue");
                e.printStackTrace();
            }
        }
    }
}