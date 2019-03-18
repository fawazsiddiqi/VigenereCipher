//
//  main.cpp
//  VigenereCipher_5465163_CSCI321_Assignment1
//
//  Created by Fawaz Siddiqi on 3/15/19.
//  Copyright © 2019 Fawaz Siddiqi. All rights reserved.
//

#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//*******************************************************************************************
//FUNCTIONS
//*******************************************************************************************
bitset<4> hex_char_to_bin(char c);
vector<bitset<8>> read_file(string filename,int &countCipherText);
void findCommon(vector<pair<int,int>>&eLocations ,vector<pair<int,int>>&spaceLocations,vector<vector<bitset<8>>> extracted);
vector<vector<bitset<8>>> extract(int size,vector<bitset<8>> characters);
int findFrequency(bitset<8> character,vector<bitset<8>>);
int sum(int size,vector<bitset<8>> characters,vector<vector<bitset<8>>> extractedCharacters);
double calculateIC(int F,int N);
void findPlainText(vector<bitset<8>> KEY,vector<vector<bitset<8>>>& plaintext,vector<vector<bitset<8>>> extractedCharacters);
//*******************************************************************************************


int main()
{   //*******************************************************************************************
    // INITALIZATIONS
    //*******************************************************************************************
    int keySize=0;
    int countCipherText;
    int countPlainText=0;
    char dispCharacter;
    vector<pair<bitset<8>,double>> frequency_table;
    vector<vector<bitset<8>>> plaintext;
    vector<pair<int,int>> spaceLocations;
    vector<pair<int,int>> eLocations;
    vector<vector<bitset<8>>> extractedCharacters;
    vector<bitset<8>> characters;
    vector<bitset<8>> KEY;
    //*******************************************************************************************
   
    characters=read_file("new-extended-given-ciphertext.txt",countCipherText); //reading the file and storing the ciphertext into a vector
    
    for(int size=1;size<characters.size() && size<101;size++){ //Calculating and displaying IC for each and every keysize
        extractedCharacters.clear();
        extractedCharacters=extract(size, characters);
          
        cout<<"IC: "<<calculateIC(sum(size,characters,extractedCharacters), (int)characters.size())<<" For key size: "<<size<<endl;
           
    }
    cout<<"Enter key size\n";
    cin>>keySize;  //user enters most likely keysize
    
    extractedCharacters=extract(keySize,characters); //the extracted characters are then extracted into columns which correspond to the poition according to the keysize
  
    //*******************************************************************************************
    //INITIALIZING PLAINTEXT AND KEY
    //*******************************************************************************************
    for(int i=0;i<extractedCharacters.size();i++){
        plaintext.push_back(vector<bitset<8>>());
        for(int j=0;j<extractedCharacters.at(i).size();j++){
            plaintext.at(i).push_back(NULL);
        }
    }
    for(int i=0;i<keySize;i++){
        KEY.push_back(NULL);
    }
    
    //*******************************************************************************************
    //FINDING SPACES
    //*******************************************************************************************
    findCommon(eLocations,spaceLocations, extractedCharacters);
    
    for(int i=0;i<spaceLocations.size();i++){
        int f=spaceLocations.at(i).first;
        int s=spaceLocations.at(i).second;
        plaintext.at(f).at(s)=bitset<8>(32);
        KEY.at(f)=bitset<8>(32)^extractedCharacters.at(f).at(s); // finding the key
    }
    //*******************************************************************************************
    
    cout<<"KEY: "; //Getting the key
    for(int i=0;i<KEY.size();i++){
        if(i==0)
        {
            cout<<""<<(char)(KEY.at(i).to_ulong())<<"";
        }
        else if(i==KEY.size()-1)
        {
            cout<<""<<(char)(KEY.at(i).to_ulong())<<"\n";
        }
        else {
            cout<<""<<(char)(KEY.at(i).to_ulong())<<"";
        }
   }

    findPlainText(KEY, plaintext, extractedCharacters); //finding the plaintext
   
    for(int i=0;i<plaintext.at(0).size();i++){ //displaying the plaintext
        for(int j=0;j<KEY.size();j++)
        {
            if(i<plaintext.at(j).size() && countPlainText<=countCipherText){
                dispCharacter=(char)(plaintext.at(j).at(i).to_ulong());
                cout<<dispCharacter;
                countPlainText++;
            }
        }
    }
    cout<<endl;
    
    
    string partOfText="In Ethereum, smart contracts are written in the "; //the first 48 characters of the plaintext  and guessing the right letters
        

        for(int i=0;i<1;i++){ //Getting the key for the guess plaintext
            for(int j=0;j<KEY.size();j++)
            {
                KEY.at(j)=bitset<8>((int)(partOfText.at(j)))^extractedCharacters.at(j).at(i);
            }
        }
    cout<<"KEY: ";
    for(int i=0;i<KEY.size();i++){
        if(i==0)
        {
            cout<<""<<(char)(KEY.at(i).to_ulong())<<"";
        }
        else if(i==KEY.size()-1)
        {
            cout<<""<<(char)(KEY.at(i).to_ulong())<<"\n";
        }
        else {
            cout<<""<<(char)(KEY.at(i).to_ulong())<<"";
        }
    }
    
        findPlainText(KEY, plaintext, extractedCharacters); //finding the new final plaintext
        countPlainText=0;
        for(int i=0;i<plaintext.at(0).size();i++){
            for(int j=0;j<KEY.size();j++)
            {
                if(i<plaintext.at(j).size()&&countPlainText<=countCipherText){ //displaying the plaintext
                    dispCharacter=(char)(plaintext.at(j).at(i).to_ulong());
                    cout<<dispCharacter;
                    countPlainText++;
                }
            }
        }
        cout<<endl;
}

bitset<4> hex_char_to_bin(char c){
    // TODO handle default / error
    switch(toupper(c))
    {
        case '0': return bitset<4>("0000");
        case '1': return bitset<4>("0001");
        case '2': return bitset<4>("0010");
        case '3': return bitset<4>("0011");
        case '4': return bitset<4>("0100");
        case '5': return bitset<4>("0101");
        case '6': return bitset<4>("0110");
        case '7': return bitset<4>("0111");
        case '8': return bitset<4>("1000");
        case '9': return bitset<4>("1001");
        case 'A': return bitset<4>("1010");
        case 'B': return bitset<4>("1011");
        case 'C': return bitset<4>("1100");
        case 'D': return bitset<4>("1101");
        case 'E': return bitset<4>("1110");
        case 'F': return bitset<4>("1111");
    }
    return bitset<4>("0000");
}

vector<bitset<8>> read_file(string filename,int &countCipherText){
    fstream file;
    char character1;
    char character2;
    string result;
    vector<bitset<8>> characters;
    file.open(filename,ios::in);
    int count=0;
    if(file.fail()){
        cout<<"File not found"<<endl;
    }else{
        while(file>>character1){
            file>>character2;
            result=hex_char_to_bin(character1).to_string()+hex_char_to_bin(character2).to_string();
            characters.push_back(bitset<8>(result));
            count++;
        }
        cout<<"COUNT: "<<count<<endl;
        countCipherText=count;
        file.close();
    }
    return characters;
}

int mostFreq(vector<bitset<8>> col){
    int largest=0;
    int count;
    for(int i=0;i<col.size();i++){
        count=findFrequency(col.at(i),col);
        if(count>largest)
        {
            largest=count;
        }
    }
    return largest;
}

void findCommon(vector<pair<int,int>>&eLocations ,vector<pair<int,int>>&spaceLocations,vector<vector<bitset<8>>> extracted){
    int largest;
    pair<int,int>P;
    for(int i=0;i<extracted.size();i++){
        largest=mostFreq(extracted.at(i));
        for(int j=0;j<extracted.at(i).size();j++){
            if(findFrequency(extracted.at(i).at(j), extracted.at(i))==largest)
            {
                    P.first=i;P.second=j;
                    cout<<(double)((double)(largest)/(extracted.at(i).size()))<<" Space found at "<<P.first<<","<<P.second<<endl;
                    spaceLocations.push_back(P);
            }
        }
    }
}

vector<vector<bitset<8>>> extract(int size,vector<bitset<8>> characters){
    vector<vector<bitset<8>>> temp;
    int pos=0;
    for(int i=0;i<size;i++){
        temp.push_back(vector<bitset<8>>());
    }
    for(int i=0;i<characters.size();i=i+size){
        pos=0;
        for(int j=i;j<i+size;j++){
            temp.at(pos).push_back(characters[j]);
            pos++;
        }
    }
    return temp;
}


int findFrequency(bitset<8> character,vector<bitset<8>>characters){
    int count=0;
    for(int i=0;i<characters.size();i++){
        if(character==characters[i]){
            count++;
        }
    }
    return count;
}

int sum(int size,vector<bitset<8>> characters,vector<vector<bitset<8>>> extractedCharacters){
    int pos=0;
    int F;
    int sum=0;
    for(int i=0;i<characters.size();i++){
        pos=0;
        for(int j=i;j<size;j++){
            F=findFrequency(characters[i], extractedCharacters[pos]);
            sum=sum+(F*(F-1));
            pos++;
        }
    }
    return sum;
}

double calculateIC(int F,int N){
    return (1/(double)(N*(N-1)))*(double)F;
}

void findPlainText(vector<bitset<8>> KEY,vector<vector<bitset<8>>>& plaintext,vector<vector<bitset<8>>> extractedCharacters){
    for(int i=0;i<KEY.size();i++){
        for(int j=0;j<extractedCharacters.at(i).size();j++){
            plaintext.at(i).at(j)=extractedCharacters.at(i).at(j)^KEY.at(i);
        }
    }
}
