package yakupov.chat.client;

import yakupov.chat.common.Message;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;

/**
 * Class of client's network part
 */
public class Network {

    private final Client client;
    private final Queue<Message> queue;
    private Socket socket;
    private ObjectOutputStream os;
    private ObjectInputStream is;
    private boolean stopped;

    /**
     * Constructor
     * @param client Client-parent
     */
    Network(Client client) {
        this.client = client;
        this.queue = new ArrayBlockingQueue<Message>(100);
        Settings settings = client.getSettings();
        try {
            this.socket = new Socket(settings.getIp(), settings.getPort());
            this.os = new ObjectOutputStream(socket.getOutputStream());
            this.is = new ObjectInputStream(socket.getInputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }
        this.stopped = false;
    }

    /**
     * Starts exchange of messages between client and server
     */
    public void start() {
        startSender();
        startReceiver();
    }

    /**
     * Sends initial message;<br>
     * runs thread, that processes queue
     */
    private void startSender() {
        try {
            os.writeObject(new Message(client.getSettings().getName(), Message.Codes.INIT, client.getSettings().getName()));
        } catch (IOException e) {
            e.printStackTrace();
        }
        new Thread(() -> {
            while (!isStopped()) {
                synchronized (queue) {
                    while (!queue.isEmpty()) {
                        System.out.println("sending from queue [" + client.getSettings().getName() + "]: " + queue.peek().getStr());//////
                        try {
                            os.writeObject(queue.remove());
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }).start();
    }

    /**
     * Runs message receiving cycle
     */
    private void startReceiver() {
        while (!isStopped()) {
            try {
                Message msg = (Message) is.readObject();
                System.out.println("received: " + msg);//////
                client.receivedMessage(msg);
            } catch (ClassNotFoundException | IOException e) {
                System.err.println("Serializable class of message not found[troubles in Message class]");
                e.printStackTrace();
            }
        }
    }

    /**
     * Stops this module;<br>
     * closes connection
     */
    public void stop() {
        stopped = true;
        try {
            os.writeObject(new Message(client.getSettings().getName(), Message.Codes.EXIT, ""));
            os.close();
            is.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Adds message in sending queue
     * @param msg Message
     */
    public void sendAsync(Message msg) {
        queue.add(msg);
    }

    /**
     * Returns status of network part
     * @return <ul>
     *         <li>'true' - if it stopped</li>
     *         <li>'false' - if it works</li>
     *         <ul/>
     */
    private boolean isStopped() {
        return stopped;
    }
}
