//
// Created by hp on 1/28/2023.
//
#include "qustion.h"
using namespace std;
#ifndef ASKME_USER_H
#define ASKME_USER_H
#include <set>

class user {
private:
  string name, username ,  email , password;
  int id;
  deque<qustion> q_was_Asked;
 public:
  deque<qustion> q_I_Asked;
  bool anonymous;
  void SetAnonymous();
  void SetUserName();
  void SetName();
  void SetEmail();
  void SetPassword();
  void SetId(int i);
  void printFeeD();
  int SetAnswer(int id , string An);
  int DeleteQ(int i);
  user();
  user(int i);
  user(int i , string N , string usN , string emai , string pass , bool ano);
  int GetId() const;
  string GetUserName();
  string GetPassWord();
  string GetName();
  string GetEmail();
  void get_qIAsked();
  void get_qWasAsked();
  void push_q_I(qustion a);
  void push_q_was(qustion s);
  void push_threatedQ(threated a);
  void SaveData(ofstream& q_file , ofstream& thr_file , set<user> users);
  bool GetQ(int i);
  bool operator <(const user& user1)const;
};


#endif //ASKME_USER_H
