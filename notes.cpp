/*
Author: Mamnuya Rinki

Summary: C++ notes program for quotes, affirmations, actions, and journal entries.

  //USAGE
  //g++ -std=c++17 notes.cpp -c
  //g++ -std=c++17 notes.cpp -o notes
  //./notes outputfile and (optional field) "default" and (optional field) inputfile

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

vector<string> quotes;
vector<string> affirmation;
vector<string> action;
vector<string> journal;
bool inputExists=false;

void defaultNotes();
void checkUserPurpose(string outpoint);
void inputParse(string inpoint);
void quitting(string out, string userInput);
void cleanInput(string reusedInput);

int main(int argc, char* argv[])
{
  if (argc < 2 || argc > 4){
    cerr << "Usage: " << argv[0] << " [output file]" << " [(optional string) \"default\"]" << " [(optional input file)]"<<"\n";
    exit(1);
  }

  //ios::app allows file appending instead of overwriting
  ofstream output {argv[1], ios::app}; 

  string output1=argv[1];
  //throws an error if no output file provided and exits the program
  if(!output.is_open()){
      cerr << "could not open output file: " << argv[1] << endl;
      exit(1);
  }

  cout<<"Welcome to Selfish Notes"<<endl;
  cout<<"Enter \"quit\" at any keyboard prompt to end your session."<<endl;
  cout<<""<<endl;

  ifstream input(argv[0]); //initial default value for input file

  if (argc==3){

    string input1; 

    if(strcmp(argv[2], "default") == 0){
      cout << "Adding default Selfish Notes!" << endl;
      cout << " " << endl;
      defaultNotes();
      checkUserPurpose(output1);
    }
    else{
      //Command line prompt ./notes output input
      input1=argv[2];
      if(!input.is_open()){
        cerr << "could not open input file: " << input1 << endl;
        exit(1);
      }

      inputExists=true;
      
      //Adjust old generated output files
      //to incorporate input file syntax
      cleanInput(input1);


      cout << "Adding input file Selfish Notes!" << endl;
      cout << " " << endl;
      inputParse(input1);
      checkUserPurpose(output1);

    }
  }
  else if (argc==4){
     //Command line prompt ./notes output default input
     // or ./notes output input default
     //call input file parser

  string input1;

    if (strcmp(argv[2], "default") == 0){
      input1=argv[3];
    }
    else if (strcmp(argv[3], "default") == 0){
      input1 =argv[2];
    }

    if(!input.is_open()){
      cerr << "could not open input file: " << input1 << endl;
      exit(1);
    }
    inputExists=true;

    //Adjust old generated output files
    //to incorporate input file syntax
    cleanInput(input1);


    cout << "Adding default Selfish Notes!" << endl;
    defaultNotes();
    cout << "Adding input file Selfish Notes!" << endl;
    cout << " " << endl;
    inputParse(input1);
    checkUserPurpose(output1);
  }
  else{
    checkUserPurpose(output1);
  }

  if (inputExists){
      input.close();
    }

    output.close();

}

/*
When an old output file is used as a new input file,
replaces old output file syntax with input file syntax accordingly
*/
void cleanInput(string reusedInput){
  //open and read the input file
  ifstream oldFile {reusedInput}; 
  string currLine;
  bool cleaningQuotes=false;
  bool cleaningAffirmations=false;
  bool cleaningActions=false;
  bool cleaningJournalEntries=false;
  vector<string> replacement;


  while(getline(oldFile, currLine)){
    //implement <start TYPE> and <end TYPE> tags
    if(currLine.find("--") != string::npos){
      if (currLine.find("--QUOTE") != string::npos){
            if (cleaningJournalEntries==true){
              //add journal entries tag and reset boolean
              //if there are more quotes and values after first journal entries section
              replacement.push_back("<end journal entries>");
              cleaningJournalEntries=false;
            }
            cleaningQuotes=true;
            replacement.push_back("<start quotes>");
        }
        else if(currLine.find("--AFFIRM") != string::npos ){ 
          cleaningAffirmations=true;
          replacement.push_back("<end quotes>");
          replacement.push_back("<start affirmations>");
        }
        else if(currLine.find("--ACT") != string::npos ){ 
          cleaningActions=true;
          replacement.push_back("<end affirmations>");
          replacement.push_back("<start actions>");
        }
        else if(currLine.find("--JOURNAL") != string::npos ){
          cleaningJournalEntries=true;
          replacement.push_back("<end actions>");
          replacement.push_back("<start journal entries>");

          //if reaching the end of quotes, reset all cleaning booleans
          if (cleaningQuotes==true){ 
            cleaningQuotes=false;
            cleaningAffirmations=false;
            cleaningActions=false;
          }
        }
  }
  else if(currLine ==""){
    //add blank lines to vector of new lines
    replacement.push_back(currLine);
  }
  else{
    if(currLine.find ("(") && currLine.find (")") && !currLine.find ("--")){ 
      //add line from after (#) until end of line, into the vector of new lines
      replacement.push_back(currLine.substr(currLine.find(") ") +2));
    }
    else{
      replacement.push_back(currLine);
    }
  }
}

//open and overwrite the input file
//ios::app allows file overwriting instead of appending
ofstream cleaned {reusedInput, ios::trunc};
for (int i=0; i<replacement.size();i++){
  cleaned<<replacement.at(i)<<"\n";
}
cleaned.close(); 


}


/*
Parses input file contained in blocks of <start [TYPE]> <end [TYPE]>
*/
void inputParse(string inpoint){
  ifstream input(inpoint);
  string currLine;
  bool parsingQuotes=false;
  bool parsingAffirmations=false;
  bool parsingActions=false;
  bool parsingJournalEntries=false;

  while (getline(input, currLine)){

    //skips blank lines
    if (currLine == "")
        {
            continue;
        }

    //parse the input file through it's contained blocks
    //uses incomplete .find strings to match atleast half
    //of the desired input fields
    //ie. finding "act" instead of "action" allows flexibility
    //for act, actions, action, acts, etc

    //parsing quotes
    if(currLine.find("<start quot") != string::npos){
      parsingQuotes=true;
      continue;
    }
    else if (currLine.find("<end quot") != string::npos){
      parsingQuotes=false;
      continue;
    }

    if (parsingQuotes==true){
      quotes.push_back(currLine);
    }

    //parsing affirmations
    if(currLine.find("<start affirm") != string::npos){
      parsingAffirmations=true;
      continue;
    }
    else if (currLine.find("<end affirm") != string::npos){
      parsingAffirmations=false;
      continue;
    }

    if (parsingAffirmations==true){
      affirmation.push_back(currLine);
    }

    //parsing actions
    if(currLine.find("<start act") != string::npos){
      parsingActions=true;
      continue;
    }
    else if (currLine.find("<end act") != string::npos){
      parsingActions=false;
      continue;
    }

    if (parsingActions==true){
      action.push_back(currLine);
    }

    //parsing journal entries
    if(currLine.find("<start journal") != string::npos){
      parsingJournalEntries=true;
      continue;
    }
    else if (currLine.find("<end journal") != string::npos){
      parsingJournalEntries=false;
      continue;
    }

    if (parsingJournalEntries==true){
      journal.push_back(currLine);
    }



  }

  


}

/* 
  Add default selfish notes if "default" is command line argument
*/
void defaultNotes(){
  quotes.push_back("\"This time in your life is asking for your self compassion.\" -Morgan Love " );
  quotes.push_back("\"You could be the world's best garbage man, the world's best model; it don't matter what you do if you're the best.\" -Muhammad Ali" );
  quotes.push_back("\"It always seems impossible until it's done.\" -Nelson Mandela");
  quotes.push_back("\"Find people who will make you better.\" -Michelle Obama");
  quotes.push_back("\"Let go of what has passed.\" -Imam Ali");
  quotes.push_back("\"The best way to predict the future is to invent it.\" -Alan Kay " );
  quotes.push_back("\"Richness is not having many belongings, but richness is contentment of the soul.\" -Prophet Muhammad SAS (PBUH)" );
  quotes.push_back("\"I alone cannot change the world, but I can cast a stone across the water to create many ripples.\" -Mother Teresa");
  quotes.push_back("\"Every moment is a fresh beginning.\" -T.S. Eliot");
  quotes.push_back("\"Happiness depends upon ourselves.\" -Aristotle");
  quotes.push_back("\"Normality is a paved road: it's comfortable to walk but no flowers grow.\" -Vincent Van Gogh " );
  quotes.push_back("\"To get what you love, you must first be patient with what you hate.\" -Imam Al-Ghazali" );
  quotes.push_back("\"I can't change the direction of the wind, but I can adjust my sails to always reach my destination.\" -Jimmy Dean");
  quotes.push_back("\"Be patient; patience is a pillar of faith.\" -Umar Ibn Al-Khattab");
  quotes.push_back("\"Healing takes courage, and we all have courage, even if we have to dig a little to find it.\" -Tori Amos");
  quotes.push_back("\"Trust yourself, you know more than you think you do.\" -Benjamin Spock " );
  quotes.push_back("\"Work hard in silence, let your success be your noise.\" -Frank Ocean" );
  quotes.push_back("\"With every hardship there is ease.\" -Quran 94:6");
  quotes.push_back("\"Be in the company of those who boost your spirituality and motivate you to do good than those who make you feel low and unworthy.\" -Mufti Menk");

  affirmation.push_back("I am growing.");
  affirmation.push_back("I am safe.");
  affirmation.push_back("I let go of all that no longer serves me.");
  affirmation.push_back("I radiate positive energy.");
  affirmation.push_back("I deserve to be surrounded by people who love and respect me.");
  affirmation.push_back("My mind and my heart will remain open today.");
  affirmation.push_back("I forgive myself for not being perfect.");
  affirmation.push_back("I deserve and choose to be happy.");
  affirmation.push_back("Every breath I inhale calms me.");
  affirmation.push_back("I'm proud of myself.");
  affirmation.push_back("I alone hold the truth of who I am.");
  affirmation.push_back("I have come farther that I would have ever thought possible, and I'm learning along the way.");
  affirmation.push_back("I invite abundance and generous hearts.");
  affirmation.push_back("I practice gratitude for all that I have, and all that is yet to come.");
  affirmation.push_back("My times of rest are productive.");
  affirmation.push_back("When I speak my needs, I receive them abundantly.");
  affirmation.push_back("Today, I will hold compassion for myself.");
  affirmation.push_back("I gently and easily return to the present moment.");
  affirmation.push_back("I am defined on my own terms.");

  action.push_back("Stay hydrated. ");
  action.push_back("Let people know when you need a break.");
  action.push_back("Ask for help as needed, you don't need to do this alone. ");
  action.push_back("Be lenient with responding to others, if you decide to do so. ");
  action.push_back("Congratulate yourself for completed tasks. ");
  action.push_back("Take a deep breath.");
  action.push_back("Give someone a hug.");
  action.push_back("Go on a short walk. ");
  action.push_back("Set intentions.");
  action.push_back("Laugh and chat with a loved one.");
  action.push_back("Watch a show.");
  action.push_back("Listen to your favorite podcast.");
  action.push_back("Cleanse your space.");
  action.push_back("Have a snack.");
  action.push_back("Meditate for five minutes.");
  action.push_back("Start a hobby.");
  action.push_back("Read a book or article.");
  action.push_back("Exercise or stretch.");
  action.push_back("Make your bed.");
}


/*
  Checks if user would like to add, read, edit, delete or quit their selfish notes.
*/
void checkUserPurpose(string outpoint){
  //direct instrutions to adding to file
  ofstream output {outpoint, ios::app};
  //ios::app allows file appending instead of overwriting

  cout<<""<<endl;
  cout << "Would you like to add, read, edit, or delete output in your Selfish Notes?" << endl;
  cout << "Enter \"add\",\"read\", \"edit\", or \"delete\" on your keyboard." << endl;
  string purpose;
  cin >> purpose;
  //Checks if user is adding
  if (purpose == ("add")){
    //add methods for adding
    cout<<""<<endl;
    cout << "Would you like to add a quote, affirmation, action, or journal entry?" << endl;
    cout << "Enter \"quote\", \"affirm\", \"act\", OR \"journal\" on your keyboard." << endl;
    cin >> purpose;
    //inputs the user's quote, affirmation, action, or journal entry 
    //based on user input
    if (purpose == ("quote")){


      //add quote
      cout << "Enter your new quote: " << endl;
      string input;
      cin >> input;
      quotes.push_back(input);
    }
    else if (purpose == ("affirm")){
      //add affirmation
      cout << "Enter your new affirmation: " << endl;
      string input;
      cin >> input;
      affirmation.push_back(input);
    }
    else if (purpose == ("act")){
      //add action
      cout << "Enter your new action: " << endl;
      string input;
      cin >> input;
      action.push_back(input);
    }
    else if (purpose == ("journal")){
      //add journal entry
      cout << "Enter your new journal entry: " << endl;
      string input;
      cin >> input;
      journal.push_back(input);
    }
    cout<<""<<endl;
    checkUserPurpose(outpoint);
    return;



  }
  //Checks if user is reading
  else if (purpose == ("read")){



    cout<<""<<endl;
    cout<<"\n"<<"--QUOTES--"<<"\n";
    //quotes sent to output file
    if (!quotes.empty()){
      for (int i=0; i<quotes.size();i++){
        cout<<"("<<i+1<<") "<<quotes.at(i)<<"\n";
      }
    }
    cout<<""<<endl;
    cout<<"\n"<<"--AFFIRMATIONS--"<<"\n";
    //affirmations sent to output file
    if (!affirmation.empty()){
      for (int i=0; i<affirmation.size();i++){
        cout<<"("<<i+1<<") "<<affirmation.at(i)<<"\n";
      }
    }
    cout<<""<<endl;
    cout<<"\n"<<"--ACTIONS--"<<"\n";
    //actions sent to output file
    if (!action.empty()){
      for (int i=0; i<action.size();i++){
        cout<<"("<<i+1<<") "<<action.at(i)<<"\n";
      }
    }
    cout<<""<<endl;
    cout<<"\n"<<"--JOURNAL ENTRIES--"<<"\n";
    //journal entries sent to output file
    if (!journal.empty()){
      for (int i=0; i<journal.size();i++){
        cout<<"("<<i+1<<") "<<journal.at(i)<<"\n";
      }
    }



    output<<""<<endl;
    checkUserPurpose(outpoint);
  }
  //Checks if user is editing
  else if (purpose == ("edit")){
    cout<<"Which category's entry would you like to edit?"<<endl;
    cout<<"Enter \"quote\", \"affirm\", \"act\", OR \"journal\" on your keyboard." << endl;

    vector<string> designatedVector;
    string entry;
    cin >> entry;
    bool editQuotes=false;
    bool editAffirmations=false;
    bool editActions=false;
    bool editJournalEntries=false;
    
    if(entry==("quote")){
      designatedVector=quotes;
      editQuotes=true;
    }
    else if(entry==("affirm")){
      designatedVector=affirmation;
      editAffirmations=true;
    }
    else if(entry==("act")){
      designatedVector=action;
      editActions=true;
    }
    else if(entry==("journal")){
      designatedVector=journal;
      editJournalEntries=true;
    }
    else if(entry==("quit")){
      quitting(outpoint,entry);
      return; //exits program
    }
    else{
      //recursive call if user input isn't valid
    cout<<"Sorry, I didn't understand that."<<endl;
    checkUserPurpose(outpoint);
    }

    if (designatedVector.empty()){
      cout<<"Sorry, we can't edit an empty entry."<<endl;
      checkUserPurpose(outpoint);
    }

    cout<<"Enter the number of the entry you would like to change."<<endl;
    cin>>entry;

  //check that user put in an entry of only digits and a valid index
    if(entry.find_first_not_of("0123456789") == std::string::npos
    && stoi(entry)-1>=0 && stoi(entry)-1<designatedVector.size()){
      int indexOfEdit=stoi(entry)-1;
      cout<<"Let's get that changed for you."<<endl;
      cout<<""<<endl;
      cout<<"The entry was previously: "<<designatedVector.at(indexOfEdit)<<endl;
      cout<<""<<endl;
      cout<<"What would you like the entry to be replaced with?"<<endl;
      cout <<"Enter the desired entry."<<endl;
      cin>>entry;
      //replace the value that must be edited
      designatedVector.at(indexOfEdit)= entry;   //insertion/replacement
      cout<<"Thank you, you're all good!"<<endl;

      //reset the designatedVector to it's corresponding category
      if(editQuotes==true){
        quotes=designatedVector;
      }
      else if(editAffirmations==true){
        affirmation=designatedVector;
      }
      else if(editActions==true){
        action=designatedVector;
      }
      else if(editJournalEntries==true){
        journal=designatedVector;
      }

      checkUserPurpose(outpoint);
    }
    else if(entry==("quit")){
      quitting(outpoint,entry);
      return; //exits program
    }
    else{
      cout<<"Sorry, no entry exists with this number."<<endl;
      checkUserPurpose(outpoint);
    }

  }
  //Checks if user is deleting
  else if (purpose == ("delete")){


    
    cout<<"Which category's entry would you like to delete?"<<endl;
    cout<<"Enter \"quote\", \"affirm\", \"act\", OR \"journal\" on your keyboard." << endl;
    vector<string> designatedVector;
    string entry;
    cin >> entry;

    bool deleteQuotes=false;
    bool deleteAffirmations=false;
    bool deleteActions=false;
    bool deleteJournalEntries=false;
    
    if(entry==("quote")){
      designatedVector=quotes;
      deleteQuotes=true;
    }
    else if(entry==("affirm")){
      designatedVector=affirmation;
      deleteAffirmations=true;
    }
    else if(entry==("act")){
      designatedVector=action;
      deleteActions=true;
    }
    else if(entry==("journal")){
      designatedVector=journal;
      deleteJournalEntries=true;
    }
    else if(entry==("quit")){
      quitting(outpoint,entry);
      return; //exits program
    }
    else{
      //recursive call if user input isn't valid
    cout<<"Sorry, I didn't understand that."<<endl;
    checkUserPurpose(outpoint);
    }

    if (designatedVector.empty()){
      cout<<"Sorry, we can't delete an empty entry."<<endl;
      checkUserPurpose(outpoint);
    }

    cout<<"Enter the number of the entry you would like to delete."<<endl;
    cin>>entry;

    //check that user put in an entry of only digits and a valid index
    if(entry.find_first_not_of("0123456789") == std::string::npos
    && stoi(entry)-1>=0 && stoi(entry)-1<designatedVector.size()){
      int indexOfEdit=stoi(entry)-1;
      cout<<"Let's get that deleted for you."<<endl;
      designatedVector.erase (designatedVector.begin()+ indexOfEdit);
      cout<<"The entry has successfully deleted. Take a deep breath to welcome a fresh start."<<endl;

      //reset the designatedVector to it's corresponding category
      if(deleteQuotes==true){
        quotes=designatedVector;
      }
      else if(deleteAffirmations==true){
        affirmation=designatedVector;
      }
      else if(deleteActions==true){
        action=designatedVector;
      }
      else if(deleteJournalEntries==true){
        journal=designatedVector;
      }

      checkUserPurpose(outpoint);
    }
    else if(entry==("quit")){
      quitting(outpoint,entry);
    }
    else{
      cout<<"Sorry, no entry exists with this number."<<endl;
      checkUserPurpose(outpoint);
    }

  }
  else if (purpose==("quit")){
    quitting(outpoint,purpose);
    return; //exits program
    }
  else{
    //recursive call if user input isn't valid
    cout<<"Sorry, I didn't understand that."<<endl;
    checkUserPurpose(outpoint);
    }
}

void quitting(string out, string userInput){
  ofstream output {out, ios::app};
  if(userInput==("quit")){
    cout<<""<<endl;
      cout<<"You should see your Selfish Notes in your output file."<<endl;
      cout<<"Bye for now, hope to see you soon! Take care of yourself."<<endl;

    output<<""<<endl;
    output<<"\n"<<"--QUOTES--"<<"\n";
    //quotes sent to output file
    if (!quotes.empty()){
      for (int i=0; i<quotes.size();i++){
        output<<"("<<i+1<<") "<<quotes.at(i)<<"\n";
      }
    }
    output<<""<<endl;
    output<<"\n"<<"--AFFIRMATIONS--"<<"\n";
    //affirmations sent to output file
    if (!affirmation.empty()){
      for (int i=0; i<affirmation.size();i++){
        output<<"("<<i+1<<") "<<affirmation.at(i)<<"\n";
      }
    }
    output<<""<<endl;
    output<<"\n"<<"--ACTIONS--"<<"\n";
    //actions sent to output file
    if (!action.empty()){
      for (int i=0; i<action.size();i++){
        output<<"("<<i+1<<") "<<action.at(i)<<"\n";
      }
    }
    output<<""<<endl;
    output<<"\n"<<"--JOURNAL ENTRIES--"<<"\n";
    //journal entries sent to output file
    if (!journal.empty()){
      for (int i=0; i<journal.size();i++){
        output<<"("<<i+1<<") "<<journal.at(i)<<"\n";
      }
    }

    output<<""<<endl;
    
  }
}
