package Mproject.server;

import java.util.Hashtable;
import java.util.Set;
import java.util.concurrent.locks.ReentrantLock;
import java.net.Socket;


// thread safe hash table for associating sockets to clients based on client id
public class AssociationMap {

	private Hashtable<Integer, Socket> clientmap;
	private ReentrantLock lock;

	public AssociationMap() {
		clientmap = new Hashtable<Integer, Socket>();
		lock = new ReentrantLock();
	}

	public Set<Integer> getKeys() {
		return clientmap.keySet();
	}

	public Socket getSocket(int clientid) {
		lock.lock();
		Socket ret = clientmap.get(clientid);
		lock.unlock();
		return ret;
	}

	public void removeClient(int clientid) {
		lock.lock();
		if(clientmap.containsKey(clientid)) {
			clientmap.remove(clientid);
		}
		lock.unlock();
	}

	public boolean addClient(int clientid, Socket sock) {
		// TODO: should probably give an error if the mapping already exists
		boolean ret = false;
		lock.lock();
		if(clientmap.get(clientid) == null) {
			clientmap.put(clientid, sock);
			ret = true;
		}
		lock.unlock();
		return ret;
	}
}
