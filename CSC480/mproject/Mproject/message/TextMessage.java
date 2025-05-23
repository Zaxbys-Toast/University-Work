package Mproject.message;

import java.time.Instant;
import java.util.ArrayList;

public class TextMessage extends Message {
	private String content;
	public TextMessage(String text, int userid, ArrayList<Integer> recipients, int groupid) {
		messagetype = MessageType.Text;
		timestamp = Instant.now();
		content = text;
		this.userid = userid;
		this.recipients = recipients;
		this.groupid = groupid;
	}

	public String getText() {
		return content;
	}

}
