#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

//class
class Player{
private:
    string name;
    int score;

public:
    //sets and gets
    void setName(string n);
    string getName();
    void setScore(int p);
    int getScore();

    //class function prototypes
    void readFile(Player fileContent[]);
    void addScores(Player fileContent[]);
};

//function prototypes
void sortArray(Player fileContent[]);
void addScore(Player fileContent[], int l, int h);

//int main
int main(){
    //class object
    Player player;

    //array that holds the hiscores
    Player fileContent[5];
    //variable declerations
    bool ScoresToAdd = true;
    int lScore, hScore;
    char answer;

    //ifstream created so I can check to make sure the file is not empty so it can be poulated with highscore if it is empty. 
    ifstream myReadFile;
    myReadFile.open("scores.txt");

    cout<<"Welcome!"<<endl;

    //checks to see if the file is empty
    if(myReadFile.peek() == EOF){// if file is empty ask the user if they would like to populate the file with scores
        cout<<"There currently isnt any high scores, would you like to populate the high scores? "<<endl;
        cout<<" Enter y for yes and n for no"<<endl;
        cin>>answer;// takes in users answer

        switch(answer){
            case 'y': // if the do want to populate the socres file
                player.addScores(fileContent);// call function to populate all five scores
                player.readFile(fileContent);// print out the populated file.
                break;

            case 'n':
                cout<<"You chose not to populate the high scores"<<endl;// out put if the user chose not to populate the file
                cout<<"High scores hall of fame!"<<endl; // header for the highscores area
                player.readFile(fileContent);// prints out current high scores
                break;
        }
    }
    else{

        cout<<"High scores hall of fame!"<<endl; // header for the highscores area
        player.readFile(fileContent);// prints out current high scores
    }

    while(ScoresToAdd == true){ // allows the user to keep addiing in highscores     
        cout<<"Would you Like to add in any high scores?\n "
        <<"Press y for yes and n for no. "<<endl;
        cin>>answer;
        lScore = fileContent[4].getScore();//sets low score to the value of the lowest score in the array
        hScore = fileContent[0].getScore();//sets low score to the value of the lowest score in the array

        switch(answer){
            case'y':
                ScoresToAdd = true;
                addScore(fileContent, lScore, hScore);// if player would like to add in high scores the addscore function is called so they can
                for (int x = 0; x < 5; ++x)
                {
                    cout<<setw(12)<<fileContent[x].getName();
                    cout<<setw(12)<<fileContent[x].getScore()<<endl;
                }
                break;

            case 'n': // if user chose not to add in any highscores
                ScoresToAdd = false; // ScoresToAdd is set to false so it will brake out of the loop
                cout<<"Ok, goodbye!!"<<endl; // prints out current highscores   
                player.readFile(fileContent);// prints out high scores        
                break;
            default:
                cout<<"You didn't enter the right letter"<<endl;// out put if the choice was incorrct
        }
    }
    return 0;
}
//sets and gets
//setName
void Player :: setName(string n){
    name = n;
}

//getName
string Player :: getName(){
    return name;
}

//setPlayerScore
void Player :: setScore(int s){
    score = s;
}

//getPlayerScore
int Player :: getScore(){
    return score;
}
//end sets and gets

//reads out the scores from the file
void Player :: readFile(Player fileContent[]){
    //variable decleration
    int numScore=0;//incrementer
    int curScore;
    string curName;
    //filestream
    ifstream myReadFile;
    myReadFile.open("scores.txt");

    if (myReadFile.is_open()) { // if file is open
        while (!myReadFile.eof()) {// not end of file

            while(myReadFile >> curName){ // reads in content of file to the appropriate variables
                myReadFile >> curScore;
                fileContent[numScore].setName(curName);
                fileContent[numScore].setScore(curScore);
                ++numScore;
            }
        }
    }
    sortArray(fileContent);// sorts the array in descending order
    myReadFile.close();// closses file

    cout<<setw(12)<< "Name"<<setw(12)<<"Score"<<endl; // formats the file output and prints it to the screen
    for(int i=0;i<5;i++){
        cout<<setw(12)<<fileContent[i].getName();
        cout<<setw(12)<<fileContent[i].getScore()<<endl;
    }
}

//initial highscores population, the scores are added to the file
void Player::addScores(Player fileContent[]){
    int curScore;
    string curName;
    //ofstream to write to the file
    ofstream outputFile;
    outputFile.open("scores.txt");

    for(int x = 0; x < 5; ++x){
        cout<<" Enter a player name. "<<endl;// sends player name to the file
        cin >> curName;
        outputFile << curName << endl;
        cout<<" Enter a player score. "<<endl;// sends in players score to the file
        cin >> curScore;
        outputFile << curScore << endl;
    }
    outputFile.close();// closes file
}

//sorts the array in descending order.
void sortArray(Player fileContent[]){
    Player temp;

    for(int i = 0; i<5; i++){
        for(int j = i +1; j <5; j++){
            if(fileContent[i].getScore() < fileContent[j].getScore()){
                temp = fileContent[j];
                fileContent[j] = fileContent[i];
                fileContent[i] = temp;
            }
        }
    }
}

// add to the array and only scores higher than the current ones will be placed on the list
void addScore(Player fileContent[], int lScore, int hScore){
    int curScore;
    string curName;
    int size;
    ofstream outputFile;
    outputFile.open("scores.txt");

    cout<<" Enter a player name. "<<endl; // adds user name to file
    cin.ignore();
    cin >> curName;
    outputFile << curName << endl;
    cout<<" Enter a player score. "<<endl;//adds the player score to file
    cin >> curScore;
    outputFile << curScore << endl;

    if (curScore > lScore) // && curScore < hScore){ // if the scores is the same or higher than any players on the list
    {										// add the player and their score to the list. Then remove smaller scores.
        fileContent[4].setName(curName);
        fileContent[4].setScore(curScore);
    }
    sortArray(fileContent);
}
