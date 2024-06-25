#include <cmath>
#include <iostream>
#include <string>

bool permutacija(std::string s1, std::string s2) {
    if(s1.length()!=s2.length()) throw std::logic_error("Razlicite duzine stringa!");
  int histogram1[26]{};
  int histogram2[26]{};
  for (int i = 0; i < s1.length(); i++) {
    histogram1[s1[i] - 97]++;
    histogram2[s2[i] - 97]++;
  }
  for(int i=0;i<s1.length();i++){
    if(histogram1[i]!=histogram2[i]) return false;
  }
  return true;
}

int main() {
  if(permutacija("mahire prestani panicariti","itiracinap inatserp eriham"))
      std::cout<<"Vracamo se u igru";
    else std::cout<<"Nista od toga!";


      return 0;
}