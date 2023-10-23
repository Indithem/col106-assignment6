import nltk
nltk.download('words')
from nltk.corpus import words

# Get the English words and convert them to lowercase
english_words = [word.lower() for word in words.words()]

# Now, `english_words` contains all the words in lowercase
from collections import defaultdict
import mmh3

word_distribution = defaultdict(int)

# Iterate through the word list
for word in english_words:
    # first_letter = word[0]
    word_length = len(word)
    # hash_value = mmh3.hash(word)
    # key = f"{first_letter}{word_length}"
    word_distribution[word_length] += 1

sorted_data = dict(sorted(word_distribution.items(), key=lambda item: item[1], reverse=True))

file_path = "lenght_word_distribution.json"

import json
# Write the dictionary to a JSON file
with open(file_path, 'w') as file:
    json.dump(sorted_data, file)
