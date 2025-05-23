package Mproject.client;

import java.net.InetAddress;
import java.net.Socket;
import java.io.BufferedOutputStream;
import java.io.ObjectOutputStream;
import java.io.BufferedInputStream;
import java.io.ObjectInputStream;
import java.time.Instant;
import java.util.ArrayList;
import java.util.HashMap;

import Mproject.message.Message;
import Mproject.message.TextMessage;
import Mproject.message.CommandMessage;
import Mproject.util.MessageQueue;
import Mproject.util.BoolRef;

public class Client {
	private int associateduser;
	private Socket socket;
	private BoolRef shouldStop;
	private static final int defaultport = 50498; // TODO move this to common location
	private MessageQueue recvmessages;
	private HashMap<Integer, ArrayList<Message>> messageLists;
	
	public Client(InetAddress ip, int port, int userid, HashMap<Integer, ArrayList<Message>> msgLists) {
		messageLists = msgLists;
		recvmessages = new MessageQueue();
		associateduser = userid;
		shouldStop = new BoolRef(false);
		try {
			System.err.println("Starting Client Connection on " + ip + ":" + port);
			socket = new Socket(ip, port);
			System.err.println("socket established, sending cmd");
			send(new CommandMessage(CommandMessage.Command.Associate, associateduser));
			ReceiveThread recvthread = new ReceiveThread(recvmessages, shouldStop, messageLists);
			System.err.println("Client Connection Established");
			recvthread.start();
		} catch (Exception e) {
			e.getStackTrace();
			System.out.println(e);
		}
	}

	public int userid() {
		return associateduser;
	}

	public void send(Message msg) {
		try {
			BufferedOutputStream bs = new BufferedOutputStream(socket.getOutputStream());
			ObjectOutputStream os = new ObjectOutputStream(bs);
			os.writeObject(msg);
			os.flush();
		} catch (Exception e) {
			e.getStackTrace();
			System.out.println(e);
		}
	}

	public void stop() {
		shouldStop.set(true);
		close();
	}

	private void close() {
		try {
			socket.close();
		} catch (Exception e) {
			e.getStackTrace();
			System.out.println(e);
		}
	}

	public int userId() {
		return associateduser;
	}

	// uses hard coded ids to test server functionality
/*
	public static void main(String[] args) {
		Client client = null;
		ArrayList<Integer> recipients = new ArrayList<Integer>();
		int userid;

		for(int i = 0; i <= 10; i++) {
			recipients.add(i);
		}
		recipients.add(27);

		try {
			// InetAddress loopback = InetAddress.getLoopbackAddress();
			InetAddress loopback = InetAddress.getByName("10.200.4.111");
			client = new Client(loopback, defaultport, 26);
		} catch (Exception e) {
			System.err.println(e);
		}

		Message msg = null;
		if(client != null) {
			if(args.length == 1) {
				msg = new TextMessage(args[0], 26 ,new ArrayList<Integer>(),1);
				client.send(msg);
			} else {
				client.send(new TextMessage("Test Message", 26, new ArrayList<Integer>(),1));
			}
		}

		while(true) {
			if(!client.messageAvailable()) {
				try {
					Thread.sleep(250);
				} catch (Exception e) {
				}
			} else {
				Message m = client.nextMessage();
				if(m != null) {
					if(m.getMessageType() == Message.MessageType.Text) {
						TextMessage tm = (TextMessage)m;
						System.out.println("Received message: " + tm.getText());
						System.out.println("From: " + tm.userid());
					} else if(m.getMessageType() == Message.MessageType.Command) {
						break;
					}
				} 
			}
		}

		client.stop();
	}
*/

	public Message nextMessage() {
		return recvmessages.getNext();
	}

	public boolean messageAvailable() {
		return recvmessages.available();
	}

	private class ReceiveThread extends Thread {
		private MessageQueue msgs;
		BoolRef shouldStop;
		HashMap<Integer, ArrayList<Message>> msglist;

		public ReceiveThread(MessageQueue messages, BoolRef shouldStop, HashMap<Integer, ArrayList<Message>> msgList) {

			msgs = messages;
			this.shouldStop = shouldStop;
			msglist = msgList;
		}

		public void run() {
			while(!shouldStop.get()) {
				try {
					ObjectInputStream os = new ObjectInputStream(new BufferedInputStream(socket.getInputStream()));
					Message m = (Message) os.readObject();
					if(m != null) {
						msglist.get(m.groupid()).add(m);
						msgs.add(m);
						System.out.println("Message Received");
					}
				} catch (Exception e) {
					System.err.println(e);
				}
			}
		}
	}


}
