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

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream find(filename);
    string line_of_string;
    vector<string> s;
    int i = 0;
    while(getline(find, line_of_string)){
        s.push_back(line_of_string);
        const char *text = s[i].c_str();
        char format[] = "%[^:]: %d %d %d";
        char _name[100];
        int a = 0, b = 0, c = 0, sum = 0;
        sscanf(text, format, &_name, &a, &b, &c);
        string _namename = _name;
        names.push_back(_name);
        sum = a + b + c;
        scores.push_back(sum);
        char _grade[100];
        _grade[100] = score2grade(sum);
        grades.push_back(_grade[100]);
        i++;
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cout << "\n";
    string line;
    getline(cin, line);

    if(line.empty()){
        command = "";
        key = "";
        return ;
    }
    int Num = 0;
    int position = line.find(" ");
    command = line.substr(Num, position-Num);
    Num = position + 1;
    key = line.substr(Num, position-Num);
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    for(int i = 0; i < (int)names.size(); i++){
        if(toUpperStr(names[i]) == toUpperStr(key)){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(int i = 0; i < (int)names.size(); i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
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
