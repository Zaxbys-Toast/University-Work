package Mproject.message;

import java.time.Instant;


public class CommandMessage extends Message {
	public enum Command {
		Associate, Disconnect;
	}

	private Command command;

	public CommandMessage(Command cmd, int user) {
		messagetype = Message.MessageType.Command;
		userid = user;
		command = cmd;
		timestamp = Instant.now();
		recipients = null;
	}

	public Command getCommand() {
		return command;
	}
}
