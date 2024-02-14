import pyperclip
import re

while(1):
	FilePath = str(input("File path: "))
	
	File = open(FilePath, "r")	#Open file on read mode
	TheFileAsList = File.read().splitlines()	#List with stripped line-breaks
	File.close()
	
	TheFileAsString = ""
	for i in range(len(TheFileAsList)):
		if(TheFileAsList[i] == "   "):
			continue
		
		TheFileAsList[i] = re.sub("^(\\t)*", "", TheFileAsList[i])
		TheFileAsString = TheFileAsString + str(TheFileAsList[i])
	
	TheFileAsString = re.sub("\"", "\\\"", str(TheFileAsString))
	TheFileAsString = re.sub("//", "\\//", TheFileAsString)
	
	pyperclip.copy(str(TheFileAsString))
	pyperclip.paste()
	print("SUCCESS, 1line in clipboard")