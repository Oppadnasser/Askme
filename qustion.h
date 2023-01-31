//
// Created by hp on 1/28/2023.
//
#include <iostream>
#include <deque>
using namespace std;
#ifndef ASKME_QUSTION_H
#define ASKME_QUSTION_H

class threated{
 private:
  int parentId;
 protected:
  int q_ID , sender_id , receiver_id , anonymous;
  string qustion_text , Answer = "Not";
 public:
  void SetPId(int i);
  void set_id(int i);
  void Set_senderId( int i);
  void Set_receiverId(int i);
  void Set_q_text();
  void Set_Answer_text(string str);
  void print_q();
  threated();
  threated(int i , int sId , int reId , string qt , string An , int a);
  threated(int i , int sId , int reId , string qt , int anon);
  threated(int i ,int pId ,  int sId , int reId , string qt , string An);
  threated(int i ,int pId ,  int sId , int reId , string qt , int anon);
  string get_q_text();
  string get_Answer_text();
  int GetPId();
  int GetQId();
  int GetSender();
  int GetReceiver();
  int Getanon(){return anonymous;};
  virtual void printFrom(); 
  virtual void printTo();
};
class qustion : public threated {
 private:
  deque <threated> threated_q;
 public:
  qustion();
  qustion(int i , int sId , int reId , string qt , string An , int j);
  qustion(int i , int sId , int reId , string qt , int anon);
  void printFrom(); // to print questions in case 1
  void printTo();
  void printFrom1(); // to print question in case 2
  void printTo1();
  void printFeed();
  void push_threated(threated a);
  void SaveData(ofstream& thr_file);
  bool setA(int s , int rid);
  int setA2(int s , string An);
  int DeleteQt(int i , int ID);
};


#endif //ASKME_QUSTION_H
