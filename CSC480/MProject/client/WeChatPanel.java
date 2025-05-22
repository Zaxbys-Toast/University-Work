package client;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.util.Random;

import javax.swing.BoxLayout;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.Timer;
import javax.swing.UIManager;

public class WeChatPanel extends JPanel {
	JTabbedPane tabbedPane;
    ImageIcon icon;
    JTextField textBox;
    JPanel panel1;
    
    JFrame theChatFrame;
    
    //String sendText;
    
    WcClient theClient;

    // create a panel with a scroll pane, and add entries as boxes
	// and piling them up vertically
	public WeChatPanel() {
	    super(new BorderLayout());
	    
	    tabbedPane = new JTabbedPane();
	    //Dimension dim = new Dimension(350, 850);
		//tabbedPane.setPreferredSize(dim );
	    
	    panel1 = new JPanel();
	    panel1.setLayout(new BoxLayout(panel1, BoxLayout.Y_AXIS));
	    tabbedPane.addTab("Chat", null, panel1,
	            "Default");
	    tabbedPane.setMnemonicAt(0, KeyEvent.VK_H);
	    
	    //addLessonButtons(panel1);
	    
        //JScrollPane scroller = new JScrollPane(tabbedPane);
        //scroller.setPreferredSize(new Dimension(350, 550));
        add(tabbedPane, BorderLayout.CENTER);
        
        theChatFrame = new JFrame();
	}

	public WeChatPanel(WcClient wcClient) {
		this();
		theClient = wcClient;
	}

	public void createAndShowGUI() {
		createAndShowGUI("Let's Chat");
	}

	public void createAndShowGUI(String title) {
        //Create and set up the window.
        Image image = new ImageIcon("images/icon.png").getImage();
         
        //Add content to the window.
        //WeChatPanel contentPane = new WeChatPanel();
        JFrame frame = theChatFrame;
        frame.setTitle(title);

        frame.setIconImage(image);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JScrollPane scroller = new JScrollPane(this);
        scroller.setPreferredSize(new Dimension(350, 550));
        frame.add(scroller, BorderLayout.CENTER);
        
        JPanel inputPane = new JPanel();
        textBox = new JTextField(
        		"                                                         ");
        inputPane.add(textBox);
        JButton submit = new JButton("Send");
        submit.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String text = textBox.getText();
				System.out.println("in gui - trying to send " + text);
				theClient.setSendingText(text);
				addChatBox(text);
			}
        });
        inputPane.add(submit);
				
        // just for testing friend box
        JButton reply = new JButton("Reply");
        reply.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				addReplyBox("Replying...");
			}
        	
        });
        inputPane.add(reply);
        // just for testing friend box - end
        
        frame.add(inputPane, BorderLayout.SOUTH);
         
        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }
	
	protected void addChatBox(String text) {
		// TODO Auto-generated method stub
		MessageBox box = new OwnerMessageBox();
		box.setText(text);
		textBox.setText("");
		
		panel1.add(box);
		theChatFrame.repaint();
	}

	protected void addReplyBox(String msg) {
		// TODO Auto-generated method stub
				MessageBox fMsgBox = new FriendMessageBox(new ImageIcon("image/gsc.png"), msg);
				panel1.add(fMsgBox);
				theChatFrame.repaint();
		
	}

	public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                //Turn off metal's use of bold fonts
		        UIManager.put("swing.boldMetal", Boolean.FALSE);
		        WeChatPanel chat = new WeChatPanel();
		        chat.createAndShowGUI();
            }
       });
	}

	public String getSendingText() {
		// TODO Auto-generated method stub
		return null;
	}
}
    
class MessageBox extends JPanel {
	JLabel senderIcon;
	JLabel contentBox = new JLabel("Some text...");
	
	public void setText(String text) {
		contentBox.setText(text);
		System.out.println("Text in box is now: " + text);
	}
		
}

class OwnerMessageBox extends MessageBox {
	
	public OwnerMessageBox() {
		senderIcon = new JLabel(new ImageIcon("image/wsc.png"));
		add(contentBox);
		add(senderIcon);
	}
}


class FriendMessageBox extends MessageBox {
	
	public FriendMessageBox(Icon friendIcon, String text) {
		senderIcon = new JLabel(friendIcon);
		contentBox.setText(text);
		add(senderIcon);
		add(contentBox);
	}
}

