package Mproject.gui;

import java.util.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import Mproject.manager.DisplayManager;
import Mproject.util.BoolRef;
import Mproject.util.UserInfo;
import Mproject.client.Client;
import java.net.InetAddress;

public class ChatLogin extends JPanel {
    private BoolRef loginSucceeded;
    private Client client;
    private JLabel loginFailed;  // Instance variable

    public ChatLogin(BoolRef loginComplete, MessagePickerGUI mp) {
        setLayout(new BorderLayout());
        JPanel fields = new JPanel(new FormLayout());
        loginSucceeded = loginComplete;

        // set up the username and password fields
        fields.add(new JLabel("Username:"));
        JTextField userfield = new JTextField(30);
        fields.add(userfield);
        fields.add(new JLabel("Password:"));
        JPasswordField passfield = new JPasswordField(30);
        fields.add(passfield);

        // add the fields to the main panel
        add(fields);

        // Button for login action
        JButton loginbutton = new JButton("Login");
        loginbutton.addActionListener(new LoginButtonCallback(userfield, passfield, loginComplete, mp, this));  // Pass the ChatLogin instance
        add(loginbutton, BorderLayout.SOUTH);

        // Initialize and add the loginFailed label to the panel
        loginFailed = new JLabel("Incorrect Username or Password");
        loginFailed.setVisible(false);
        loginFailed.setForeground(Color.red);
        add(loginFailed, BorderLayout.NORTH);
    }

    private class LoginButtonCallback implements ActionListener {
        JTextField user, pass;
        BoolRef loginSucceeded;
        MessagePickerGUI mpg;
        ChatLogin chatLogin;  // Reference to outer ChatLogin

        // Constructor to accept the ChatLogin reference
        LoginButtonCallback(JTextField userfield, JPasswordField passfield, BoolRef logincomplete, MessagePickerGUI mp, ChatLogin chatLogin) {
            mpg = mp;
            user = userfield;
            pass = passfield;
            loginSucceeded = logincomplete;
            this.chatLogin = chatLogin;  // Store the reference
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            boolean ret = authenticateLogin(user.getText(), pass.getText());
            loginSucceeded.set(ret);
            if (ret) {
                UserInfo test = new UserInfo();
                int uid = test.userID(user.getText());
                DisplayManager mgr = DisplayManager.getInstance();
                mgr.set("messagePicker");
                InetAddress ip;
                try {
                    ip = InetAddress.getByName("10.200.4.111");
                    mpg.setClient(new Client(ip, Mproject.server.Server.DEFPORT, uid, mpg.getMessageLists()));
                } catch (Exception ex) {
                    System.err.println(ex);
                }
            } else {
                // Access the loginFailed label via the passed reference to the ChatLogin instance
                chatLogin.loginFailed.setVisible(true);  // No more NullPointerException
            }
        }

        private boolean authenticateLogin(String username, String password) {
            UserInfo test = new UserInfo();
            return test.checkUserExistence(username, password);
        }
    }
}
