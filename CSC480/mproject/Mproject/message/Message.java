package Mproject.message;

import java.io.Serializable;
import java.time.Instant;
import java.util.ArrayList;

public abstract class Message implements Serializable {
	public enum MessageType {
		Text,
		Image,
		Command,
	}
	
	protected MessageType messagetype;
	protected Instant timestamp;
	protected int userid;
	protected ArrayList<Integer> recipients;
	protected int groupid;

	public int groupid() {
		return groupid;
	}

	public MessageType getMessageType() {
		return messagetype;
	}

	public Instant getTimeStamp() {
		return timestamp;
	}

	public ArrayList<Integer> recipients() {
		return recipients;
	}

	public int userid() {
		return userid;
	}

}
