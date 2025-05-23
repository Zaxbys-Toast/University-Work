
package Mproject.server;

import java.net.Socket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;
import java.net.SocketTimeoutException;
import java.io.InputStream;
import java.io.BufferedInputStream;
import java.io.ObjectInputStream;
import java.io.BufferedOutputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

import Mproject.message.Message;
import Mproject.message.TextMessage;
import Mproject.message.CommandMessage;
import Mproject.util.MessageQueue;

public class Server {
	private static final int maxclients = 10;
	private Thread threadaccept;
	private ConnectionHandler connectionhandler;
	private static final int defaultport = 50498;
	public static final int DEFPORT = 50498;

	public Server() {
	}

	public void start(InetAddress ip, int port) {
		System.err.println("Starting connection handler on " + ip + ":" + port);
		connectionhandler = new ConnectionHandler("Conn Handler", ip, port, maxclients);
		threadaccept = new Thread(connectionhandler);
		threadaccept.start();
	}

	public void shutdown() {
		System.out.println("Server Shutdown");
		connectionhandler.shutdown();
	}

	public static void main(String[] args) {
		System.out.println("hello server");
		// TODO: arg parsing
		InetAddress loopback;
		Server server = new Server();
		try {
			// loopback = InetAddress.getLoopbackAddress();
			loopback = InetAddress.getByName("10.200.4.111");
		} catch (Exception e) {
			e.getStackTrace();
			System.err.println(e);
			return;
		}

		// TODO: implement cli args for ip, port
		server.start(loopback, defaultport);
		boolean f = true;
		while(f) {
			// hang indef for now.
			// should implement some mechanism for shutdown
		}
		try {
			Thread.sleep(10000);
		} catch (Exception e) {
			e.getStackTrace();
		}
		server.shutdown();
	}

	private class ConnectionHandler extends Thread {
		private ServerSocket acceptsocket;
		private int maxclients;
		boolean ready, running;
		private MessageQueue sendqueue;
		private AssociationMap associations;

		private ConnectionHandler(String name, InetAddress ipaddr, int port, int nclients) {
			super(name);
			sendqueue = new MessageQueue();
			associations = new AssociationMap();
			try { 
				maxclients = nclients;
				acceptsocket = new ServerSocket(port, nclients, ipaddr);
				acceptsocket.setSoTimeout(500);
				acceptsocket.setReuseAddress(true);
				System.out.println("Socket created on: " + acceptsocket.getInetAddress() + ":" + port);
				SendThread sendthread = new SendThread(sendqueue, associations);
				sendthread.start();
			} catch (Exception e) {
				e.getStackTrace();
				ready = false;
			}
			ready = true;
		}

		public void run() {
			System.out.println("ConnectionHandler start");
			if(!ready) {
				System.err.println("Not Ready");
				// TODO: handle this
			}
			running = true;
			Socket s;

			while(running) {
				try {
					System.out.println("Accepting connection");
					s = acceptsocket.accept();

					int i;
					System.out.println("Accepted connection");
					System.out.println("Starting Receive Handler");
					ReceiveThread recvhandler = new ReceiveThread("ReceiveThread", s, sendqueue, associations);
					recvhandler.start();
				} catch (SocketTimeoutException ste) {
					continue;
				} catch (Exception e) {
					// TODO: should probably handle these
					e.getStackTrace();
					ready = false;
					break;
				} finally {
				}
			}

			try {
				acceptsocket.close();
			} catch (Exception e) {
				e.getStackTrace();
			}
		}

		public void shutdown() {
			System.out.println("Connection handler shutdown");
			running = false;
		}
	}

	private class ReceiveThread extends Thread {
		Socket incoming;
		MessageQueue sendqueue;
		AssociationMap associations;
		int user;
		int[] threadctrl;

		public ReceiveThread(String name, Socket s, MessageQueue msgs, AssociationMap am) {
			super(name);
			incoming = s;
			sendqueue = msgs;
			associations = am;
		}

		public void run() {
			System.out.println("ReceiveThread start");
			String input = "";
			int nrecv = 0;
			while(true) {
				try {
					byte[] buf = new byte[incoming.getReceiveBufferSize()];
					BufferedInputStream inputstream = new BufferedInputStream(incoming.getInputStream());
					ObjectInputStream msginput = new ObjectInputStream(inputstream);
					Message m = (Message) msginput.readObject();
					System.out.println(m.getMessageType() + " Message recieved at " + m.getTimeStamp());
					user = m.userid();

					if(m.getMessageType() == Message.MessageType.Text) {
						TextMessage tm = (TextMessage)m;
						String recipients = "";
						ArrayList<Integer> recip = tm.recipients();
						for(int r : recip) {
							recipients += "" + r + ", ";
						}
						System.out.println("Text received: " + tm.getText() + "\n"
								+ "From: " + tm.userid() + "\nTo: " + recipients);
						sendqueue.add(m);
					} else if(m.getMessageType() == Message.MessageType.Command) {
						CommandMessage cm = (CommandMessage)m;
						System.out.println("Command Message Received");
						System.out.println(cm.getCommand());
						if(cm.getCommand() == CommandMessage.Command.Disconnect) {
							incoming.close();
							break;
						} else if(cm.getCommand() == CommandMessage.Command.Associate) {
							System.out.println("adding user: " + m.userid());
							System.out.println("socket: " + incoming);
							associations.addClient(m.userid(), incoming);
						}
					}
				} catch (Exception e) {
					System.err.println(e);
					associations.removeClient(user);
					try {
					incoming.close();
					} catch (Exception ex) {
						System.err.println(ex);
					}
					break;
				}
			}

		}
	}

	private class SendThread extends Thread {
		private MessageQueue sendqueue;
		private AssociationMap associations;

		public SendThread(MessageQueue msgs, AssociationMap activeConnections) {
			sendqueue = msgs;
			associations = activeConnections;
		}

		public void run() {

			// TODO: boolean ref; should stop
			while(true) {
				if(sendqueue.available()) {
					System.out.println("Message Available to Send");
					Message m = sendqueue.getNext();
					if(m != null) {
						// TODO: handle case if message not sent to all recipients,
						// to resent when the user reconnects
						if( m.recipients().isEmpty()) {
							for (int r : associations.getKeys()) {
								System.out.println("Routing Global Chat Message");
								Socket s = associations.getSocket(r);
								if(s != null) {
									try {
										BufferedOutputStream bs =
											new BufferedOutputStream(s.getOutputStream());
										ObjectOutputStream os = 
											new ObjectOutputStream(bs);
										os.writeObject(m);
										os.flush();
										System.out.println("Message Routed");
									} catch (Exception e) {
										System.err.println(e);
									}
								}
							}
						} else {
							for (int recipient : m.recipients()) {
								Socket s = associations.getSocket(recipient);
								if(s != null) {
									System.out.println("Routing to uid: " + recipient);
									try {
										BufferedOutputStream bs =
											new BufferedOutputStream(s.getOutputStream());
										ObjectOutputStream os = 
											new ObjectOutputStream(bs);
										os.writeObject(m);
										os.flush();
										System.out.println("Message Routed");
									} catch (Exception e) {
										System.err.println(e);
									}
								} // else user is not connected
							}
						}
					} // else message was malformed
				} else {
					try {
						sleep(250);
					} catch (Exception e) {
					}
				}
			}
		}
	}
}
