# Selfish Notes
#### A program that promotes the idea of self-care, that may be deemed an act of "selfishness," in a positive manner.

#### About
This program takes an output file to display quotes, affirmations, actions, and journal entries. There are various options for input and output files. Entries can be added, read, edited, or deleted. This is version 2 of Selfish Notes. 

#### Usage
Download the files in the directory. Enter the following into the command line.
```
Compile: g++ -std=c++17 notes.cpp -c
Output: g++ -std=c++17 notes.cpp -o notes
Command Line: ./notes outputfile and (optional field) default and (optional field) inputfile
```
#### Features
Users can add, read, edit, or delete any of the quotes, affirmations, actions, or journal entries. 

If at any point the user would like to end their session, the user may enter "quit" as any prompt for their session to terminate. Quitting ends the session as well as ensures the current quotes, affirmation, actions, and journal entries are appended to the output file.

An output file previously generated by this program can be used as an input file. 

Input files can have multiple sections of quotes, actions, affirmations, and journal entries.

#### Command Line "default" Input
Placing the string "default" before or after any (optional) input file, inserts a list of default quotes, affirmations, and actions into the output file.

#### Input File Format
Placing the input file before or after any (optional) "default" string reads in any quote, affirmations, and actions to the desired output file. The input file should follow the format as indicated by the [testinput.txt](https://github.com/mamnuya/Selfish-Notes/blob/main/testinput.txt) file in the directory. 

This file adheres to a the following tag format:
```
<start quotes>
<end quotes>
<start affirmations>
<end affirmations>
<start actions>
<end actions>
<start journal entries>
<end journal entries>
```

#### Output File Format
If a file existing with the desire output file name, it will be appended to upon the "quit" command. If a file does not already exist with the desired output file name, a new file will be created then appeneded to. This is a great way to record entries per day by assigning an output file name by day, or record entries over a longer period of time. 

The output file follows the format as indicated by the [reusedoutput.txt](https://github.com/mamnuya/Selfish-Notes/blob/main/reusedoutput.txt) file in the directory. This output file uses [testinput.txt](https://github.com/mamnuya/Selfish-Notes/blob/main/testinput.txt) as an input file.

This file produces the following section format:
```
--QUOTES--

--AFFIRMATIONS--

--ACTIONS--

--JOURNAL ENTRIES--

```

#### Generated Output Files as New Input Files
If a user desires to edit a previous session's generated output file, they can use the previous output file to be used as in input file. The cleanInput() method will remove any numbers preceding an entry ((#) example entry). Therefore, the (#) would need to be removed to prevent number overlap, and the input file tag format will be inserted and maintained.

#### What's Next?
This version can be adapted for future versions. The following improvements can be made:
1. Allow user's to create their own categories beyond quotes, actions, affirmations, and journal entries.
2. When using previously generated output files as input files, check input file for indications of previously generated output file. If there are NO indications, exit the cleanInput() method.
3. Specify (#) syntax in the if-statement of the cleanInput() method.
