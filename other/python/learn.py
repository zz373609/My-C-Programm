def counts(fname):
	clines = 0
	cwords = 0
	file = open(fname);
	for sentence in file:
		word = sentence.split()
		clines += 1
		cwords = len(word)
		print(clines,cwords) 	


def ngrams(fname):
	lettercount = {}
	file = open(fname)
	for sentence in file:
		word = sentence.split()
		for letters in word:
			letternum = 0;
			for letter in letters:
				if letter.isalpha():
					letternum = letternum+1
			if letternum not in lettercount:
				lettercount[letternum] = 1
			else:
				lettercount[letternum] += 1

	return(lettercount)

def vc(fname):
	cvowels = 0
	cconsonants = 0
	vowels = set("aeiouAEIOU")
	file = open(fanme)
	sentence = file.readline()
	while sentence != '':
		for word in sentence:
			for ch in word:
				if ch.isalpha():
					if ch in vowels:
						cvowels += 1
					else:
						cconsonants+=1
		sentence = file.readline()
	print(cvowels,cconsonants)


def genlines(fname):
	file = open(fname)
	line = file.readline()
	save = []
	while line != '':
		sentence = line.split()
		save.append(sentence)
		line = file.readline()

	while save:
		for v in save:
			str1 = " ".join(v)
			yield str1


def swap(fanme,w1,w2):
	file = open(fanme)
	sentence = file.read()
	found = -1
	word = sentence.split()
	if w1 in word:
		found+=1
	if w2 in word:
		found+=1

	if found ==1:
		sentence = sentence.replace(w1,"#")
		sentence = sentence.replace(w2,"$")
		sentence = sentence.replace("#",w2)
		sentence = sentence.replace("$",w1)
	else:
		print "There in no string exit"
		exit()

	print sentence























