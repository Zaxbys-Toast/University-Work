package client;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;

public class WeChatDemo extends JPanel {
	JTabbedPane tabbedPane;
    ImageIcon icon;
    JTextField textBox;
    JPanel panel1;

    // create a panel with a scroll pane, and add entries as boxes
	// and piling them up vertically
	public WeChatDemo() {
	    //super(new GridLayout(1, 1));
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
	    
        //add(tabbedPane);
        
        //The following line enables to use scrolling tabs.
        //tabbedPane.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);
        JScrollPane scroller = new JScrollPane(tabbedPane);
        scroller.setPreferredSize(new Dimension(350, 550));
        add(scroller, BorderLayout.CENTER);
	}

	private static void createAndShowGUI() {
        //Create and set up the window.
        JFrame frame = new JFrame("Let's Chat");
        Image image = new ImageIcon("images/icon.png").getImage();

        frame.setIconImage(image);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         
        //Add content to the window.
        WeChatDemo contentPane = new WeChatDemo();
        frame.add(contentPane, BorderLayout.CENTER);
        
        JPanel inputPane = new JPanel();
        contentPane.textBox = new JTextField(
        		"                                                         ");
        inputPane.add(contentPane.textBox);
        JButton submit = new JButton(new ImageIcon("images/sendBtn.png"));
        submit.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				String text = contentPane.textBox.getText();
				System.out.println("Text in field is: " + text);
				MsgBox box = new MsgBox(text);
				
				contentPane.panel1.add(box);
				frame.repaint();
			}
        	
        });
        inputPane.add(submit);
        frame.add(inputPane, BorderLayout.SOUTH);
         
        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }
	
	public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                //Turn off metal's use of bold fonts
		        UIManager.put("swing.boldMetal", Boolean.FALSE);
		        createAndShowGUI();
            }
       });
	}
}
    
	class MsgBox extends JPanel {
		JLabel senderIcon = new JLabel(new ImageIcon("image/gsc.png"));
		JLabel contentBox = new JLabel("Some text...");
		
		public MsgBox(String text) {
			contentBox.setText(text);
			add(senderIcon);
			add(contentBox);
			System.out.println("Text in box is: " + text);
		}
	}

