package client;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

import javax.swing.SwingUtilities;
import javax.swing.UIManager;

public class WcClient {
	WeChatPanel gui;
	String id;
	
	static int ServerPort = 1234;
	DataOutputStream dos;
	DataInputStream dis;
	
	//boolean sending, receiving;
	String sendingText, receivingText;
	
	public WcClient() {
		gui = new WeChatPanel(this);
		//sending = false;
		//receiving = false;
	}
	
	public static void main(String[] args) {
		WcClient client = new WcClient();
		if (args.length == 0)
			client.id = "client 0";
		else
			client.id = "client " + args[0];
		client.gui.createAndShowGUI(client.id);
		/*
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                //Turn off metal's use of bold fonts
		        UIManager.put("swing.boldMetal", Boolean.FALSE);
            }
       });
       */
		client.doIt();
	}

	public void setSendingText(String text) {
		System.out.print("in client - trying rest sendingText from |" + sendingText);
		sendingText = text;
		System.out.println("| to " + sendingText);
		//this.sending = true;
		//System.out.println("in client - the sending flag now == " + sending);
		
		try {
            // write on the output stream
            dos.writeUTF(text);
    		//System.out.print("in sending thread - setting sending flag to " + (!sending));
            // set sending to false after sending the msg
            //sending = false;
        } catch (IOException e) {
            e.printStackTrace();
        }
	}

	//public void setReceiving(boolean status) {
	//	this.receiving = status;
	//}
	
	public void doIt() {
        Scanner scn = new Scanner(System.in);
        
        // getting localhost ip
        InetAddress ip = null;
		try {
			ip = InetAddress.getByName("localhost");
		} catch (UnknownHostException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
          
        // establish the connection
        Socket s = null;
		try {
			s = new Socket(ip, ServerPort);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
          
        // obtaining input and out streams
        //DataInputStream dis = null;
		try {
			dis = new DataInputStream(s.getInputStream());
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
        //DataOutputStream dos = null;
		try {
			dos = new DataOutputStream(s.getOutputStream());
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		/*
  
        // sendMessage thread
        Thread sendMessage = new Thread(new Runnable() 
        {
            @Override
            public void run() {
                while (true) {
                	if (sending) {
  
	                    // read the message to deliver.
	                    //String msg = scn.nextLine();
	                    //gui.addChatBox(msg);
                		String msg = sendingText;
                		System.out.print("in sending thread - sendingText is now |" + msg + "|");
                		
	                    try {
	                        // write on the output stream
	                        dos.writeUTF(msg);
	                		System.out.print("in sending thread - setting sending flag to " + (!sending));
	                        // set sending to false after sending the msg
	                        sending = false;
	                    } catch (IOException e) {
	                        e.printStackTrace();
	                    }
                	}
                }
            }
        });
        sendMessage.start();
		*/
          
        // readMessage thread
        Thread readMessage = new Thread(new Runnable() 
        {
            @Override
            public void run() {
  
                while (true) {
                    try {
                        // read the message sent to this client
                        String msg = dis.readUTF();
                        gui.addReplyBox(msg);
                        
                        System.out.println(msg);
                    } catch (IOException e) {
  
                        e.printStackTrace();
                    }
                }
            }
        });
  
        readMessage.start();
    }

}

