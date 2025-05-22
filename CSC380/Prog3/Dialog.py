import random

class Dialog:
    def __init__(self):
        self.keywords = {}

    def addKeyword(self, keyword, responses):
	# We are going to set all of the text to lower case so this is making sure all of the keywords are also lowercase
        keyword = keyword.lower()
	# Adds the responses as a list found in the keyword array at that keyword 
        self.keywords[keyword] = responses
###
	# def addResponse(self, keyword, response):
	# Was originally going to have seperate methods for adding responses and keywords, but that felt overly complicated when I could do it at the same time
###
    def getResponse(self, inp):
	# For each keyword in the Dialog object, if the input text (inp) is a keyword then return a random choice from the list of responses, otherwise say you don't understand
        for keyword, responses in self.keywords.items():
            if keyword.lower() in inp.lower():
                return random.choice(responses)
        return "I'm not sure I understand you fully."

