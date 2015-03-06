package yakupov.chat.client;

import java.awt.event.*;

import yakupov.chat.common.Message;

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
        Thread displayReceivedMessages = new Thread(new Runnable() {
            public void run() {
                while (true) {
                    displayReceivedMessages();
                }
            }
        });
        displayReceivedMessages.setDaemon(true);
        displayReceivedMessages.start();
    }

    /**
     * Displays messages from receive queue
     */
    private void displayReceivedMessages() {
        if (!client.getReceiveQueue().isEmpty()) {
            for (Message message : client.getReceiveQueue()) {
                System.out.println("displaying from queue: " + message);//////
                gui.displaySetText(message + "\n", true);
            }
            client.getReceiveQueue().clear();
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
                String text = gui.typeAreaGetText();
                if (KeyEvent.getKeyText(kc).equals("Enter")
                        && !text.equals("")
                        ) {
                    Message msg = new Message(client.getName(), Message.Codes.MSG, text);
                    gui.displaySetText(msg + "\n", true);
                    gui.typeAreaSetText("");
                    System.out.println(msg);//////
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

    /**
     * Returns WindowListener, which processes closing of window
     * @return WindowListener
     */
    public WindowListener getWindowL() {
        return new WindowListener() {
            @Override
            public void windowOpened(WindowEvent e) {

            }

            @Override
            public void windowClosing(WindowEvent e) {
                client.exit();
            }

            @Override
            public void windowClosed(WindowEvent e) {
            }

            @Override
            public void windowIconified(WindowEvent e) {

            }

            @Override
            public void windowDeiconified(WindowEvent e) {

            }

            @Override
            public void windowActivated(WindowEvent e) {

            }

            @Override
            public void windowDeactivated(WindowEvent e) {

            }
        };
    }
}