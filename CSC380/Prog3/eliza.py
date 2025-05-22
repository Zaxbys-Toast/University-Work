# Eliza chatbot - CBR chatbot - modeled after the first ever chatbot
import os
import re
from Dialog import Dialog

eliza = Dialog()

# keywords
eliza.addKeyword("always", ["Can you think of a specific example?", "Why do you feel this way"])
eliza.addKeyword("because", ["Is that the real reason?", ])
eliza.addKeyword("sorry", ["Please don't apologize."])
eliza.addKeyword("maybe", ["You don't seem very certain."])
eliza.addKeyword("i think", ["Do you really think so?"])
eliza.addKeyword("you", ["We were discussing you, not me"])
eliza.addKeyword("yes", ["Why do you think so", "You seem quite positive"])
eliza.addKeyword("no", ["Why not?", "Are you sure?"])
eliza.addKeyword("i am",["I am sorry to hear that you are ", "How long have you felt ", "Do you think it is normal to feel ", "Do you enjoy being "])
eliza.addKeyword("i'm",["I am sorry to hear that you feel", "How long have you felt ", "Do you think it is normal to feel ", "Do you enjoy being "])
eliza.addKeyword("i feel",["Tell me more about such feelings", "Why do you feel like that"])
eliza.addKeyword("family", ["Tell me more about your family.", 
                             "How do you get along with your family?", 
                             "Is your family important to you?"])
eliza.addKeyword("mother", ["Tell me more about your family.", 
                             "How do you get along with your family?", 
                             "Is your family important to you?"])
eliza.addKeyword("mom", ["Tell me more about your family.", 
                          "How do you get along with your family?", 
                          "Is your family important to you?"])
eliza.addKeyword("father", ["Tell me more about your family.", 
                             "How do you get along with your family?", 
                             "Is your family important to you?"])
eliza.addKeyword("dad", ["Tell me more about your family.", 
                           "How do you get along with your family?", 
                           "Is your family important to you?"])
eliza.addKeyword("sister", ["Tell me more about your family.", 
                              "How do you get along with your family?", 
                              "Is your family important to you?"])
eliza.addKeyword("brother", ["Tell me more about your family.", 
                               "How do you get along with your family?", 
                               "Is your family important to you?"])
eliza.addKeyword("husband", ["Tell me more about your family.", 
                               "How do you get along with your family?", 
                               "Is your family important to you?"])
eliza.addKeyword("wife", ["Tell me more about your family.", 
                            "How do you get along with your family?", 
                            "Is your family important to you?"])
eliza.addKeyword("dream", ["What does that dream suggest to you?", 
                           "Do you dream often?", 
                           "What persons appear in your dreams?", 
                           "Are you disturbed by your dreams?"])
eliza.addKeyword("nightmare", ["What does that nightmare suggest to you?", 
                               "Do you have nightmares often?", 
                               "What persons appear in your nightmares?", 
                               "Are you disturbed by your nightmares?"])

# Start the conversation
print("The doctor is in.")
print("What's on your mind?")

# Conversation loop
conversationEnded = False
while not conversationEnded:
	# Take user input
	userInput = input("- ")
	# End conversation if it is over
	if "bye" in userInput.lower():
		print("Goodbye!")
		conversationEnded = True
	# Emotions
	else:
		emotions = ["sad", "mad", "lonely", "upset", "angry"]
		for emotion in emotions:
			if emotion in userInput.lower():
				response = eliza.getResponse("i am") + emotion
				print(response)
				break
		# Normal responses
		else: 
			response = eliza.getResponse(userInput)
			print(response)
