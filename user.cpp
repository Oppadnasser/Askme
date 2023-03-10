//
// Created by hp on 1/28/2023.
//

#include "user.h"
#include <regex>
#include <fstream>

bool validEmail(string s) {
  char regex_filename[] = "[a-zA-Z_0-9]+\\@[a-z]+\\.[a-z]+";
  return regex_match(s, regex(regex_filename));
}

void user::SetAnonymous() {
  int s;
  cout << "Allow anonymous questions? : (0 or 1)";
  cin >> s;
  while (s != 0 && s != 1) {
    cout << "Invalid input " << " \nAllow anonymous questions? : (0 or 1)";
    cin >> s;
  }
  anonymous = s;
}

void user::SetUserName() {
  cout << "Enter user name. (No spaces):";
  cin >> username;
}

void user::SetName() {
  cout << "Enter name:";
  cin >> name;

}

void user::SetEmail() {
  cout << "Enter email:";
  cin >> email;
  while (!validEmail(email)) {
    cout << "invalid email \nPlease enter valid email(xxx@gmil.com):";
    cin >> email;
  }
}

void user::SetPassword() {
  cout << "Enter password:";
  cin >> password;
}

user::user() {
  SetUserName();
  SetPassword();
  SetName();
  SetEmail();
  SetAnonymous();
}

void user::SetId(int i) {
  id = i;
}

int user::GetId() const {
  return id;
}

void user::get_qIAsked() {
  for(int i = 0 ; i < q_I_Asked.size(); ++i){
    q_I_Asked[i].printFrom1();
    q_I_Asked[i].printTo1();
  }
}

void user::get_qWasAsked() {
  for (int i = 0; i < q_was_Asked.size(); ++i) {
    q_was_Asked[i].printFrom();
  }

}

void user::push_q_I(qustion a) {
  q_I_Asked.push_back(a);
}

void user::push_q_was(qustion s) {
  q_was_Asked.push_back(s);
}

user::user(int i, string N, string usN, string emai, string pass , bool ano) {
  id = i ;
  name = N;
  username = usN;
  email = emai;
  password = pass;
  anonymous = ano;
}

bool user::operator<(const user &user1) const {
  return id < user1.id;
}

void user::push_threatedQ(threated a) {
  qustion temp;
  auto iter = q_I_Asked.begin();
  for(auto s : q_I_Asked){
    if(a.GetPId() == s.GetQId()){
      auto it = iter;
      it++;
      temp = s;
      temp.push_threated(a);
      q_I_Asked.erase(iter);
      q_I_Asked.insert(--it, temp);
      return;
    }
    iter++;
  }
  iter = q_was_Asked.begin();
  for(auto s : q_was_Asked){
    if(a.GetPId() == s.GetQId()){
      auto it = iter;
      it++;
      temp = s;
      temp.push_threated(a);
      q_was_Asked.erase(iter);
      q_was_Asked.insert(--it, temp);
      return;
    }
    iter++;
  }
  cout << "invalid question Id\n";
}

string user::GetUserName() {
  return username;
}
string user::GetPassWord() {
  return password;
}

string user::GetName() {
  return name;
}

string user::GetEmail() {
  return email;
}
void user::SaveData(ofstream &q_file, ofstream &thr_file , set<user> users) {
  for(auto a : q_was_Asked){
    q_file << '\n' << a.GetQId() << ' ' << a.GetSender() << ' ' << a.GetReceiver() << '\n' << a.get_q_text() << '\n'
    << a.get_Answer_text() << '\n' << a.Getanon();
    a.SaveData(thr_file);
  }
}

int user::SetAnswer(int id , string An) {
  for(int i = 0 ; i < q_was_Asked.size(); ++i){
    if(q_was_Asked[i].GetQId() == id){
      q_was_Asked[i].Set_Answer_text(An);
      return q_was_Asked[i].GetSender();
    }
    int re = q_was_Asked[i].setA2(id, An);
    if(re)
      return re;
  }
  for(int i = 0 ; i < q_I_Asked.size(); ++i){
    if(q_I_Asked[i].GetQId() == id){
      q_I_Asked[i].Set_Answer_text(An);
      return q_I_Asked[i].GetSender();
  }
    int re = q_I_Asked[i].setA2(id , An);
    if(re)
      return re;

    }
  cout << "invalid id question\n";

}

int user::DeleteQ(int i) {
  int re_sender = 0;

  deque<qustion>::iterator it;
  for (it = q_I_Asked.begin(); it != q_I_Asked.end(); it++) {
    if (it->GetQId() == i) {
      re_sender = it->GetReceiver();
      q_I_Asked.erase(it);
      return re_sender;
    }
    re_sender = it->DeleteQt(i , id);
    if(re_sender)
      return re_sender;
  }
    for (it = q_was_Asked.begin(); it != q_was_Asked.end(); it++) {
      if (it->GetQId() == i) {
        re_sender = it->GetSender();
        q_was_Asked.erase(it);
        return re_sender;
      }
      re_sender = it->DeleteQt(i , id);
      if(re_sender)
        return re_sender;
    }
    cout << "invalid question id\n";
}

user::user(int i) {

}

bool user::GetQ(int j) {
  for(int i = 0 ; i < q_was_Asked.size(); ++i){
    if(q_was_Asked[i].GetQId() == j){
//      q_was_Asked[i].Set_Answer_text();
      q_was_Asked[i].print_q();
      return true;
    }
    if(q_was_Asked[i].setA(j , id))
      return true;
  }
  for(int i = 0 ; i < q_I_Asked.size(); ++i){
    if(q_I_Asked[i].setA(j , id))
      return true;
  }
  cout << "invalid id question\n";
  return false;

}

void user::printFeeD() {
  for(auto a : q_I_Asked)
    a.printFeed();
  for(auto a : q_was_Asked)
    a.printFeed();
}
