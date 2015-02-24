package yakupov.chat.server;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import yakupov.chat.common.Consts;
import yakupov.chat.common.Message;

/**
 * Class of chat's server
 */
public class Server {

    private List<Connection> connections = new ArrayList<Connection>();
    private ServerSocket server;

    /**
     * Constructor of 'Server' class
     *
     * Listens for sockets and adds connections to the list
     */
    public Server() {
        try {
            server = new ServerSocket(Consts.Port);
            System.out.println("Server started\nChat log:");
            while (true) {
                Socket socket = server.accept();

                Connection con = new Connection(socket);
                connections.add(con);

                con.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            closeAll();
        }
    }

    /**
     * Closes connections
     */
    private void closeAll() {
        try {
            server.close();

            Iterator<Connection> iter = connections.iterator();
            while(iter.hasNext()) {
                iter.next().close();
            }
        } catch (Exception e) {
            System.err.println("Streams was not closed");
        }
    }

    /**
     * Class, which:
     *  - contains connection between client and server
     *  - resend messages to other clients
     */
    class Connection extends Thread {
        private ObjectInputStream ois;
        private ObjectOutputStream oos;
        private Socket socket;

        private String name = "";

        /**
         * Constructor of 'Connection' class
         * @param socket Socket, which links server and client
         */
        public Connection(Socket socket) {
            this.socket = socket;

            try {
                ois = new ObjectInputStream(socket.getInputStream());
                oos = new ObjectOutputStream(socket.getOutputStream());

            } catch (IOException e) {
                e.printStackTrace();
                close();
            }
        }

        /**
         * Sends messages to other clients
         */
        @Override
        public void run() {
            Message msg;
            try {
                name = ((Message) ois.readObject()).getStr();
                Iterator<Connection> iter = connections.iterator();
                System.out.println(name + " has joined us");
                while(iter.hasNext()) {
                    Connection currIter = iter.next();
                    if (!currIter.socket.isClosed() && !currIter.equals(this)) {
                        currIter.oos.writeObject(new Message("SERVER", Message.Codes.MSG, name + " has joined us"));
                    }
                    else {
                        currIter.oos.writeObject(new Message("SERVER", Message.Codes.INIT, "WELCOME"));
                    }
                }

                while (true) {
                    msg = (Message) ois.readObject();
                    if(msg.getCode() == Message.Codes.EXIT) {
                        break;
                    }

                    iter = connections.iterator();
                    System.out.println(name + ": " + msg.getStr());
                    while(iter.hasNext()) {
                        Connection currIter = iter.next();
                        if (!currIter.socket.isClosed() && !currIter.equals(this)) {
                            currIter.oos.writeObject(msg);
                        }
                    }
                }

                iter = connections.iterator();
                System.out.println(name + " has left us");
                while(iter.hasNext()) {
                    Connection currIter = iter.next();
                    if (!currIter.equals(this) && !currIter.socket.isClosed()) {
                        currIter.oos.writeObject(new Message("SERVER", Message.Codes.MSG, name + " has left us"));
                    }
                }

            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            } finally {
                close();
            }
        }

        /**
         * Closes I/O Streams and socket;
         * Removes this connection from list of connections
         * (if list became empty - shutdown server)
         */
        public void close() {
            try {
                ois.close();
                oos.close();
                socket.close();

                connections.remove(this);
                if (connections.size() == 0) {
                    Server.this.closeAll();
                    System.exit(0);
                }
            } catch (Exception e) {
                System.err.println("Streams was not closed");
            }
        }
    }
}