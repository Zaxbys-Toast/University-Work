import random 

class Dialog:
	
	def __init__(self, numKeywords, numResponses):
		self.keywordsArray = []
		self.responsesArray = []
		self.keywordCount = 0
		self.responseCount = 0

	def addKeyword(self, keyword, response):
		self.keywordsArray.append(keyword)
		self.keywordCount += 1
		
		self.responsesArray.append(response)
		self.responseCount += 1
	
	def getResponse(self, inputText):
        	for i, keyword in enumerate(self.keywordsArray):
            		if keyword in inputText:
                		return self.responsesArray[i]
        	return random.choice(self.responsesArray)	
