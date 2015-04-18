package yakupov.chat.mode;

import yakupov.chat.client.Client;
import yakupov.chat.server.Server;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Scanner;

/**
 * Demonstration of using of 'Client' and 'Server' classes
 */
public class Main {

    private static void cancelDialog(JFrame dialog, JFrame frame) {
        dialog.dispose();
        frame.setVisible(true);
    }

    private static void makeDialogWindow(final JFrame frame) {
        frame.setVisible(false);
        final JFrame dialog = new JFrame("Dialog");
        dialog.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
        dialog.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                cancelDialog(dialog, frame);
            }
        });
        final JTextField fieldIP = new JTextField();
        final JTextField fieldPort = new JTextField();
        final JTextField fieldName = new JTextField();
        final JButton ok = new JButton("OK");
        final JButton cancel = new JButton("Cancel");
        final JLabel lblIP = new JLabel("IP:");
        final JLabel lblPort = new JLabel("Port:");
        final JLabel lblName = new JLabel("Name:");
        dialog.getContentPane().setLayout(new GridLayout(4, 2));
        dialog.add(lblIP);
        dialog.add(fieldIP);
        dialog.add(lblPort);
        dialog.add(fieldPort);
        dialog.add(lblName);
        dialog.add(fieldName);
        dialog.add(ok);
        dialog.add(cancel);
        dialog.setPreferredSize(new Dimension(300, 200));
        dialog.pack();
        dialog.setResizable(false);
        ok.addActionListener(evt -> {
            new Client(fieldIP.getText(), Integer.valueOf(fieldPort.getText()), fieldName.getText());
            dialog.dispose();
            frame.dispose();
        });
        cancel.addActionListener(e -> cancelDialog(dialog, frame));
        dialog.setVisible(true);
    }

    private static void launchGUIDialog() {
        SwingUtilities.invokeLater(() -> {
            final JFrame frame = new JFrame("Launcher");
            frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
            JButton runClientButton = new JButton("Run client");
            JButton runServerButton = new JButton("Run server");
            frame.getContentPane().setLayout(new GridLayout(2, 1));
            frame.getContentPane().add(runClientButton);
            frame.getContentPane().add(runServerButton);
            frame.setPreferredSize(new Dimension(200, 150));
            frame.pack();

            runClientButton.addActionListener(evt -> makeDialogWindow(frame));
            runServerButton.addActionListener(evt -> {
                frame.dispose();
                new Server();
            });
            frame.setVisible(true);
        });
    }

    private static void launchTextDialog() {
        Scanner in = new Scanner(System.in);
        System.out.println("(s)erver/(c)lient");
        while (true) {
            char answer = Character.toLowerCase(in.nextLine().charAt(0));
            if (answer == 's') {
                new Server();
                break;
            } else if (answer == 'c') {
                new Client();
                break;
            } else {
                System.out.println("Incorrect input. Try again");
            }
        }
    }

    public static void main(String[] args) {
        if (args.length != 0) {
            launchTextDialog();
        } else {
            launchGUIDialog();
        }
    }
}
