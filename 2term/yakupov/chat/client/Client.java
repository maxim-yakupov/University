package yakupov.chat.client;

import java.io.*;
import java.net.Socket;
import java.util.*;

import yakupov.chat.common.Message;

/**
 * Class of chat's client
 */
public class Client
{
    private Socket socket;

    private ObjectOutputStream oos;
    
    private Queue<Message> deliveryQueue;
    private Queue<Message> receiveQueue;

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
        String ip = scan.nextLine();
        System.out.println("Enter port:");
        int port = Integer.parseInt(scan.nextLine());
        System.out.print("Enter your nick-name:");
        String enteredName = scan.nextLine();
        new Client(ip, port, enteredName)
                .startGUI();
    }

    /**
     * Makes initialization and starts receiver-thread
     * @param ip IP of server
     * @param port Port, using by server
     * @param name Nick-name of user
     */
    private Client(String ip, int port, String name) {
        deliveryQueue = new PriorityQueue<Message>();
        deliveryQueue.clear();

        receiveQueue = new PriorityQueue<Message>();
        receiveQueue.clear();

        this.name = name;

        try {
            socket = new Socket(ip, port);

            oos = new ObjectOutputStream(socket.getOutputStream());

            receiver = new Receiver();
            receiver.start();

            oos.writeObject(new Message(name, Message.Codes.INIT, name));
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
            try {
                sendMessages();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        if (!exit) exit();
    }

    /**
     * Sends messages from delivery queue
     */
    synchronized private void sendMessages() throws IOException {
        if (!deliveryQueue.isEmpty()) {
            for (Message message : deliveryQueue) {
                System.out.println("sending from queue [" + getName() + "]: " + message.getStr());//////
                oos.writeObject(message);
            }
            deliveryQueue.clear();
        }
    }

    /**
     * Adds message to delivery queue
     * @param message Message string
     */
    synchronized public void addMessageInQueue(Message message) {
        if (message.getCode() == Message.Codes.EXIT) {
            exit();
        } else {
            System.out.println("adding in queue [" + getName() + "]: " + message.getStr());//////
            deliveryQueue.add(message);
            System.out.println("check adding in queue [" + getName() + "]: " + deliveryQueue.peek());//////
        }
    }

    /**
     * Calls, when want to close client
     */
    public void exit() {
        receiver.setStop();
        try {
            sendMessages();
        } catch (IOException e) {
            e.printStackTrace();
        }
        exit = true;
        try {
            oos.writeObject(new Message(getName(), Message.Codes.EXIT, ""));
        } catch (IOException e) {
            e.printStackTrace();
        }
        //
        close();
        System.exit(0);
    }

    /**
     * Returns users nick-name
     * @return nick-name
     */
    public String getName() {
        return name;
    }

    /**
     * Closes Output Stream and socket;
     */
    private void close() {
        try {
            oos.close();
            socket.close();
        } catch (Exception e) {
            System.err.println("Streams or socket were not closed");
            e.printStackTrace();
        }
    }

    /**
     * Returns receive queue
     * @return Queue
     */
    public Queue<Message> getReceiveQueue() {
        return receiveQueue;
    }

    /**
     * Class, which receives messages from server
     */
    private class Receiver extends Thread {

        private boolean stopped = false;
        private ObjectInputStream ois;

        /**
         * Stops receiving
         * (makes flag 'stopped' true)
         */
        public void setStop() {
            stopped = true;
        }

        /**
         * Receives messages from server and adds them to receive queue
         */
        @Override
        public void run() {
            try {
                ois = new ObjectInputStream(socket.getInputStream());
                while (!stopped) {
                    Message msg = (Message) ois.readObject();
                    System.out.println("received: " + msg);//////
                    Client.this.getReceiveQueue().add(msg);
                }
                ois.close();
            } catch (IOException e1) {
                System.err.println("[It's OK if occurs on closing]: Can't receive message [occurs when trying to read but socket closes]");
//                e1.printStackTrace();
            } catch (NullPointerException e2) {
                System.err.println("NullPointer error while adding message to receive queue[troubles with input stream]");
                e2.printStackTrace();
            } catch (ClassNotFoundException e3) {
                System.err.println("Serializable class of message not found[troubles in Message class]");
                e3.printStackTrace();
            }
        }
    }
}