package yakupov.chat.client;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class ClientGUIListeners {

    private ClientGUI gui;
    private Client client;

    ClientGUIListeners(ClientGUI gui, Client client) {
        this.gui = gui;
        this.client = client;
        (new Thread(new Runnable() {
                    public void run() {
                        while (true) {
                            displayReceivedMessages();
                        }
                    }
                })).start();
    }

    private void displayReceivedMessages() {
        if (!client.receiveQueue.isEmpty()) {
            System.out.println("<<" + client.receiveQueue.toString() + ">>");//////
            for (String receiveQueueEl : client.receiveQueue) {
                System.out.println("displaying from queue: " + receiveQueueEl);//////
                gui.displaySetText(receiveQueueEl + "\n", true);
            }
            client.receiveQueue.clear();
        }
    }

    public KeyListener getKeyL() {
        return new KeyListener() {
            @Override
            public void keyTyped(KeyEvent e) {
            }

            @Override
            public void keyPressed(KeyEvent e) {
                int kc = e.getKeyCode();
                String msg = gui.typeAreaGetText();
                if (KeyEvent.getKeyText(kc).equals("Enter")
                        && !msg.equals("")
                        ) {
                    gui.displaySetText("[" + client.getName() + "]: " + msg + "\n", true);
                    gui.typeAreaSetText("");
                    System.out.println("[" + client.getName() + "]: " + msg);//////
                    client.addMessageInQueue(msg);
                }
            }

            @Override
            public void keyReleased(KeyEvent e) {
            }
        };
    }

    public ActionListener getActionL() {
        return new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                gui.displaySetText("", false);
                gui.typeAreaSetText("");
            }
        };
    }
}