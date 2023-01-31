//
// Created by hp on 1/28/2023.
//

#include <fstream>
#include "qustion.h"
#include <map>
void threated::set_id(int i) {
  q_ID = i;
}

void threated ::Set_senderId(int i) {
  sender_id = i;
}

void threated::Set_receiverId(int i) {
  receiver_id = i;
}

void threated::Set_q_text() {
  cout << "Enter question text: ";
  cin >> qustion_text;
}

void threated::Set_Answer_text() {
  cout << "question ID(" << q_ID << ") from user id(" << sender_id << ')' << endl;
  cout << "Question : " << qustion_text << '\n';
  if(Answer == "Not"){
    cout << "Not answered yet\n";
  }
  else{
    cout << "Answer : " << Answer << '\n' << "warning : Already answered , answer will be updated \n";
  }
  cout << "Enter answer : ";
  cin >> Answer;
}

string threated::get_q_text() {
  return qustion_text;
}

string threated::get_Answer_text() {
  return Answer;
}

void threated::printFrom() {
  cout << "thread:  question ID(" << q_ID << ") from user id(" << sender_id << ')';
  cout << "      Question : " << qustion_text << '\n';
  cout << "thread:          Answer : ";
  if(Answer == "Not")
    cout << "Not Answered yet\n\n";
  else
    cout << Answer << "\n\n";
}

void threated::printTo() {
  cout << "question ID(" << q_ID << ") to user id(" << receiver_id << ')';
  cout << "Question : " << qustion_text ;
  cout << "         Answer : ";
  if(Answer == "Not")
    cout << "Not Answered yet\n";
  else
    cout << Answer << '\n';
}

void threated::SetPId(int i) {
  parentId = i;
}

int threated::GetPId() {
  return parentId;
}

int threated::GetQId() {
  return q_ID;
}

threated::threated(int i, int p, int sId, int reId, string qt, string An) {
  set_id(i);
  SetPId(p);
  Set_senderId(sId);
  Set_receiverId(reId);
  qustion_text = qt;
  Answer = An;
}

threated::threated(int i, int sId, int reId, string qt, string An , int a) {
  set_id(i);
  Set_senderId(sId);
  Set_receiverId(reId);
  qustion_text = qt;
  Answer = An;
  anonymous = a;
}

int threated::GetSender() {
  return sender_id;
}

int threated::GetReceiver() {
  return receiver_id;
}

threated::threated(int i, int sId, int reId, string qt , int anon) {
  set_id(i);
  Set_senderId(sId);
  Set_receiverId(reId);
  qustion_text = qt;
  anonymous = anon;
}

threated::threated(int i, int pId, int sId, int reId, string qt , int anon) {
  set_id(i);
  Set_senderId(sId);
  Set_receiverId(reId);
  qustion_text = qt;
  parentId = pId;
  anonymous = anon;
}

threated::threated() {

}

void qustion::printFrom() {
  cout << "question ID(" << q_ID << ") from user id(" << sender_id << ')';
  cout << "       Question : " << qustion_text << '\n';
  cout << "        Answer : " << Answer << "\n\n";
  for(int i = 0 ; i < threated_q.size(); ++i){
    cout << "        ";
    threated_q[i].printFrom();
  }
}

void qustion::printTo() {
  cout << "question ID(" << q_ID << ") to user id(" << receiver_id << ')' << endl;
  cout << "Question : " << qustion_text << '\n';
  cout << "        Answer : " << Answer << '\n';
  for(int i = 0 ; i < threated_q.size(); ++i){
    cout << "        ";
    threated_q[i].printTo();
  }
}

qustion::qustion(int i, int sId, int reId, string qt, string An , int j) : threated(i,sId,reId,qt,An , j) {

}

void qustion::push_threated(threated a) {
  threated_q.push_back(a);

}
map<int , string> Answers;
void qustion::SaveData(ofstream& thr_file) {
//  bool founded = false;
  for(int i = 0 ; i < threated_q.size() ; i++){
//    for(auto it = Answers.begin() ; it != Answers.end();it++){
//      if(it->first==threated_q[i].GetQId()){
//        founded = true;
//        break;
//      }
//    }
      thr_file << '\n' << threated_q[i].GetQId() << " "
               << threated_q[i].GetPId() << ' ' << threated_q[i].GetSender()
               << ' '
               << threated_q[i].GetReceiver() << ' '
               << threated_q[i].get_q_text() << ' '
               << threated_q[i].get_Answer_text();
      Answers[threated_q[i].GetQId()] = threated_q[i].get_Answer_text();

    }
}

void qustion::printFrom1() {
  cout << "question ID(" << q_ID << ") ";
  if(!anonymous)
    cout <<" !AQ";
  cout <<" to user id(" << receiver_id << ')';
  cout << "    Question : " << qustion_text;
  cout << "      Answer : " ;
  if(Answer != "Not")
    cout<< Answer << '\n';
  else
    cout << "Not answered yet\n";
}

void qustion::printTo1() {
  for(int i = 0 ; i < threated_q.size();++i){
    threated_q[i].printTo();
  }
//  cout << "question ID(" << q_ID << ") to user id(" << receiver_id << ')' << endl;
//  cout << "Question : " << qustion_text << '\n';
//  cout << "        Answer : " ;
//  if(Answer != "Not")
//    cout<< Answer << '\n';
//  else
//    cout << "Not answered yet\n";
}

qustion::qustion(int i, int sId, int reId, string qt , int anon) : threated (i,sId,reId,qt , anon){

}

qustion::qustion() {

}

bool qustion::setA(int s) {
  for(int i = 0 ; i < threated_q.size();i++){
    if(threated_q[i].GetQId() == s){
      threated_q[i].Set_Answer_text();
      return true;
    }
  }
  return false;
}
