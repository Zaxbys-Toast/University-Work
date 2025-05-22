# Finding the top 100 most common words in good reviews using NLP

import os
import re
from collections import Counter

def cleanText(text):
	text = re.sub(r'[^a-zA-Z\s]', '', text)
	
	text = text.lower()
	return text

def removeStopWords(text):
	stopWords = {
		'this', 'that', 'take', 'want', 'which', 'then', 'will', 'with', 'have', 'after', 'such', 
		'when', 'some', 'them', 'could', 'make', 'through', 'from', 'were', 'also', 'into', 'they',
	 	'their', 'there', 'because'
	}
	
	newText = []
	
	for word in text.split():
		cleanedWord = word.strip()
		if cleanedWord not in stopWords and len(cleanedWord) >= 4:
			newText.append(word)

	return ' '.join(newText)

subPath = '/home/king_jw/CSC380/Labs/Lab7/reviews'
files = os.listdir(subPath)

mostCommonCounter = Counter()

for filename in files:
	if '_6' in filename or '_7' in filename or '_8' in filename or '_9' in filename or '_10' in filename:
		filepath = os.path.join(subPath, filename)
		with open(filepath, 'r') as file:
			fileContents = file.read()
			fileContents = cleanText(fileContents)
			fileContents = removeStopWords(fileContents)
			mostCommonCounter.update(fileContents.split())

mostCommonWords = mostCommonCounter.most_common(100)
print("Top 100 Most Common Words in Positive Reviews\n---------------------------------------------") 
i = 1
for word, _ in mostCommonWords:
	print(f"{word:{10}}", end=' ')	
	i += 1
	if i % 10 == 0:
		print('')		
