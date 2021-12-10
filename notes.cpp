#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> quotes;
vector<string> affirmation;
vector<string> action;
vector<string> journal;
bool defaultsAdded=false;

void defaultNotes();
void checkUserPurpose(string outpoint);

int main(int argc, char* argv[])
{
  //./fileName outputfile and start
  //USAGE
  //g++ -std=c++17 notes.cpp -c
  //g++ -std=c++17 notes.cpp -o notes
  //./notes hi.txt start
  if (argc < 2 || argc > 3){
    cerr << "Usage: " << argv[0] << " [output file]" << " [(optional string) start]" <<"\n";
    exit(1);
  }

  ofstream output {argv[1]};
  string output1=argv[1];
  //throws an error if no output file provided and exits the program
  if(!output.is_open()){
      cerr << "could not open file: " << argv[1] << endl;
      exit(1);
  }

  cout<<"Welcome to Selfish Notes"<<endl;
  cout<<"Enter QUIT at any keyboard prompt to end your session."<<endl;
  cout<<""<<endl;

  if (argc==3){
    if(strcmp(argv[2], "start") == 0){
      cout << "Adding default Selfish Notes!" << endl;
      cout << " " << endl;
      defaultNotes();
      defaultsAdded=true;
      checkUserPurpose(output1);
    }
    else{
      checkUserPurpose(output1);
    }
  }

}

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

void checkUserPurpose(string outpoint){
  //direct instrutions to adding to file
  ofstream output {outpoint};
  cout<<""<<endl;
  cout << "Would you to add or read your Selfish Notes?" << endl;
  cout << "Enter ADD or READ on your keyboard." << endl;
  string addOrRead;
  cin >> addOrRead;
  if (addOrRead == ("ADD")){
    //add methods for adding
    cout<<""<<endl;
    cout << "Would you to add a quote, affirmation, action, or journal entry?" << endl;
    cout << "Enter QUOTE, AFFIRM, ACT, OR JOURNAL on your keyboard." << endl;
    cin >> addOrRead;
    if (addOrRead == ("QUOTE")){


      //add method for adding quotes
      cout << "Enter your new quote: " << endl;
      string input;
      cin >> input;
      quotes.push_back(input);
    }
    else if (addOrRead == ("AFFIRM")){
      //add method for adding quotes
      cout << "Enter your new affirmation: " << endl;
      string input;
      cin >> input;
      affirmation.push_back(input);
    }
    else if (addOrRead == ("ACT")){
      //add method for adding quotes
      cout << "Enter your new action: " << endl;
      string input;
      cin >> input;
      action.push_back(input);
    }
    else if (addOrRead == ("JOURNAL")){
      //add method for adding quotes
      cout << "Enter your new journal entry: " << endl;
      string input;
      cin >> input;
      action.push_back(input);
    }
    cout<<""<<endl;
    checkUserPurpose(outpoint);



  }
  else if (addOrRead == ("READ")){



    cout<<""<<endl;
    //output<<"\n"<<"--QUOTES--"<<"\n";
    cout<<"\n"<<"--QUOTES--"<<"\n";
    if (!quotes.empty()){
      for (int i=0; i<quotes.size();i++){
        cout<<"("<<i+1<<") "<<quotes.at(i)<<"\n";
      }
    }
    cout<<""<<endl;
    cout<<"\n"<<"--AFFIRMATIONS--"<<"\n";
    if (!affirmation.empty()){
      for (int i=0; i<affirmation.size();i++){
        cout<<"("<<i+1<<") "<<affirmation.at(i)<<"\n";
      }
    }
    cout<<""<<endl;
    output<<"\n"<<"--ACTIONS--"<<"\n";
    if (!action.empty()){
      for (int i=0; i<action.size();i++){
        output<<"("<<i+1<<") "<<action.at(i)<<"\n";
      }
    }
    cout<<""<<endl;
    output<<"\n"<<"--JOURNAL ENTRIES--"<<"\n";
    if (!journal.empty()){
      for (int i=0; i<journal.size();i++){
        output<<"("<<i+1<<") "<<journal.at(i)<<"\n";
      }
    }



    cout<<""<<endl;
    checkUserPurpose(outpoint);
  }
  else{
    if(addOrRead == ("QUIT")){
      cout<<"Bye for now, hope to see you soon! Take care of yourself."<<endl;
      output.close();
      return;
    }
    else{

    }
    cout<<"Sorry, I didn't understand that."<<endl;
    checkUserPurpose(outpoint);
  }
}
