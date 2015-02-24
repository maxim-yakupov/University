package yakupov.chat.server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import yakupov.chat.mode.Consts;

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
        private BufferedReader in;
        private PrintWriter out;
        private Socket socket;

        private String name = "";

        /**
         * Constructor of 'Connection' class
         * @param socket Socket, which links server and client
         */
        public Connection(Socket socket) {
            this.socket = socket;

            try {
                in = new BufferedReader(
                        new InputStreamReader(
                            socket.getInputStream()
                        )
                );
                out = new PrintWriter(socket.getOutputStream(), true);

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
            String str;
            try {
                name = in.readLine();
                Iterator<Connection> iter = connections.iterator();
                System.out.println(name + " has joined us");
                while(iter.hasNext()) {
                    Connection currIter = iter.next();
                    if (!currIter.equals(this)) {
                        currIter.out.println(name + " has joined us");
                    }
                    else {currIter.out.println(Consts.Init);}
                }

                while (true) {
                    str = in.readLine();
                    if(str.equals(Consts.Exit)) {
                        break;
                    }

                    iter = connections.iterator();
                    System.out.println(name + ": " + str);
                    while(iter.hasNext()) {
                        Connection currIter = iter.next();
                        if (!currIter.equals(this)) {
                            currIter.out.println(name + ": " + str);
                        }
                    }
                }

                iter = connections.iterator();
                System.out.println(name + " has left us");
                while(iter.hasNext()) {
                    Connection currIter = iter.next();
                    if (!currIter.socket.isClosed()) {
                        currIter.out.println(name + " has left us");
                    }
                }
            } catch (IOException e) {
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
                in.close();
                out.close();
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