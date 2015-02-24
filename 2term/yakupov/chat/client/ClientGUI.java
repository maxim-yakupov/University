package yakupov.chat.client;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

/**
 * Class of chat's graphics interface
 */
public class ClientGUI extends JFrame {

    private Client client;
    private JButton button;
    private JTextArea displayArea;
    private JTextField typingArea;

    /**
     * Constructor of client's GUI
     * @param client Client-parent
     */
    public ClientGUI(final Client client) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                ClientGUI frame = new ClientGUI(client, "Chat | user: " + client.getName());
                frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
                frame.addWindowListener(new WindowListener() {
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
                });
                frame.addComponentsToPane();
                frame.pack();
                frame.addListenersToComponents();
                frame.setVisible(true);
            }
        });
    }

    /**
     * Runs constructor of JFrame and init link to client
     * @param client Client
     * @param name Title of window
     */
    private ClientGUI(Client client, String name) {
        super(name);
        this.client = client;
    }

    /**
     * Place components on content pane
     */
    private void addComponentsToPane() {
        button = new JButton("Clear(history stays)");
        typingArea = new JTextField(20);

        displayArea = new JTextArea();
        displayArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(displayArea);
        scrollPane.setPreferredSize(new Dimension(375, 125));

        getContentPane().add(typingArea, BorderLayout.PAGE_START);
        getContentPane().add(scrollPane, BorderLayout.CENTER);
        getContentPane().add(button, BorderLayout.PAGE_END);
    }

    /**
     * Adds listeners to components
     */
    private void addListenersToComponents() {
        ClientGUIListeners control = new ClientGUIListeners(this, client);
        button.addActionListener(control.getActionL());
        typingArea.addKeyListener(control.getKeyL());
    }

    /**
     * Prints text in messages area
     * @param str text
     * @param append <ul>
     *               <li>if 'true' - append mode</li>
     *               <li>if 'false' - replace mode</li>
     *               </ul>
     */
    public void displaySetText(String str, boolean append) {
        if (append) {
            displayArea.append(str);
        } else {
            displayArea.setText(str);
        }
    }

    /**
     * Set text in editable area
     * @param str text
     */
    public void typeAreaSetText(String str) {
        typingArea.setText(str);
    }

    /**
     * Returns text from editable area
     * @return text
     */
    public String typeAreaGetText() {
        return typingArea.getText();
    }
}