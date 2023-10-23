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
    if 3<=word_length<=16:
        # first_letter=1 if word[0]<'m' else 2
        # if 5<=word_length<=14:
        # first_letter= 1 if word[0]<'f' else 2 if word[0]<'m' else 3 if word[0]<'u' else 4
        first_letter=mmh3.hash(word)%10
        # first_letter=''

    else:
        first_letter=''
    key = f"{word_length}_{first_letter}"
    word_distribution[key] += 1

# Following Brevity law see: https://en.wikipedia.org/wiki/Brevity_law
# for item in word_distribution.items():
    # word_distribution[item[0]]=item[1]/int(item[0].split('_')[0])
#our distribution must have constant product of le

sorted_data = dict(sorted(word_distribution.items(), key=lambda item: item[1], reverse=True))

file_path = "lenght_word_distribution.json"

import json
# Write the dictionary to a JSON file
with open(file_path, 'w') as file:
    json.dump(sorted_data, file)
