package Mproject.util;

import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;
import java.util.ArrayList;
import Mproject.message.*;

// Thread safe queue for message, sorted by timestamp
public class MessageQueue {
	private ArrayList<Message> msgs;
	private ReentrantLock lock;

	public MessageQueue() {
		msgs = new ArrayList<Message>();
		lock = new ReentrantLock();
	}

	public void add(Message m) {
		lock.lock();
			int count = msgs.size();
			boolean inserted = false;
			for(int i = 0; i < count; i++) {
				if(m.getTimeStamp().isBefore(msgs.get(i).getTimeStamp())) {
					// insert in time order
					msgs.add(i, m);
					break;
				}
			}
			// append if not inserted
			if(!inserted) msgs.add(m);
		lock.unlock();
	}

	public boolean available() {
		return !msgs.isEmpty();
	}

	public Message getNext() {
		Message ret = null;
		if(msgs.isEmpty()) return ret;
		lock.lock();
		ret = msgs.get(0);
		msgs.remove(0);
		lock.unlock();
		return ret;
	}
}
