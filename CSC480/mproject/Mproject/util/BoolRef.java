package Mproject.util;

import java.util.concurrent.locks.ReentrantLock;

public class BoolRef {
	private ReentrantLock lock;
	private boolean value;
	
	public BoolRef(boolean init) {
		lock = new ReentrantLock();
		value = init;
		lock = new ReentrantLock();
	}

	public boolean get() {
		lock.lock();
		boolean ret = value;
		lock.unlock();
		return ret;
	}

	public void set(boolean val) {
		lock.lock();
		value = val;
		lock.unlock();
	}
	
}
