#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string>& names,vector<int>& scores,vector<char>& grades){
    ifstream fnn(filename); 
    string imd;
    while (getline(fnn,imd))
    {
        const char *text = imd.c_str();
        char namearr[100];
        int s1,s2,s3;
        sscanf(text,"%[^:]: %d %d %d",namearr,&s1,&s2,&s3);
        names.push_back(namearr);
        scores.push_back((s1+s2+s3));
        grades.push_back(score2grade(s1+s2+s3));
    }
    
}

void getCommand(string &command,string &key){
    cout << "Please input your command: " ;
    string gett;
    getline(cin,gett);
    const char *textt = gett.c_str();
    char format[] = "%[^ ] %[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. ]";
    char scommand[100];
    char skey[100];
    sscanf(textt,format,scommand,skey);
    command = scommand;
    key = skey;
}

void searchName(vector<string>& names,vector<int>& scores,vector<char>& grades,string key){
    int findk = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size();i++){
      if(toUpperStr(names[i]) == key){
        cout << names[i] << "'s score = " << scores[i] << endl;
        cout << names[i] << "'s grade = " << grades[i] << endl;
        cout << "---------------------------------\n";
        findk = 1;
      }
      else if(i == names.size()-1 && findk == 0 && toUpperStr(names[i]) != key){
      cout << "Cannot found.\n";
      cout << "---------------------------------\n";
      }
    }
}

void searchGrade(vector<string>& names,vector<int>& scores,vector<char>& grades,string key){
    int findk = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size();i++){
      if(grades[i] == key.c_str()[0]){
        cout << names[i] << " (" << scores[i] << ")" << endl;
        findk = 1;
      }
      else if(i == names.size()-1 && findk == 0 && grades[i] != key.c_str()[0]){
      cout << "Cannot found.\n";
      }
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
