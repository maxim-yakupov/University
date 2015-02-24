package yakupov.chat.client;

import yakupov.chat.mode.Consts;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

/**
 * Layer between client and GUI
 */
public class ClientGUIListeners {

    private ClientGUI gui;
    private Client client;

    /**
     * Constructor: inits 'gui' and 'client' links;
     * runs thread, which displays received messages
     * @param gui GUI-parent
     * @param client Client-parent
     */
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

    /**
     * Displays messages from receive queue
     */
    private void displayReceivedMessages() {
        if (!client.receiveQueue.isEmpty()) {
            for (String receiveQueueEl : client.receiveQueue) {
                if (receiveQueueEl.equals(Consts.Init)) continue;
                System.out.println("displaying from queue: " + receiveQueueEl);//////
                gui.displaySetText(receiveQueueEl + "\n", true);
            }
            client.receiveQueue.clear();
        }
    }

    /**
     * Returns KeyListener, which processes user's input
     * @return KeyListener
     */
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

    /**
     * Returns ActionListener, which processes clicking on 'clear-button'
     * @return ActionListener
     */
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