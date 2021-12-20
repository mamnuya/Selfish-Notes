# Selfish Notes

#### About
This program takes an output file to display quotes, affirmations, actions, and journal entries. There are various options for input and output files. Entries can be added, read, edited, or deleted. This is version 1 of Selfish Notes.

#### Usage
Download the files in the directory. Enter the following into the command line.
```
Compile: g++ -std=c++17 notes.cpp -c
Output: g++ -std=c++17 notes.cpp -o notes
Command Line: ./notes outputfile and (optional field) default and (optional field) inputfile
```

#### Command Line "default" Input
Placing the string "default" before or after any (optional) input file, inserts a list of default quotes, affirmations, and actions into the output file.

#### Input File Format
Placing the input file before or after any (optional) "default" string reads in any quote, affirmations, and actions to the desired output file. The input file should follow the format as indicated by the ()[].

