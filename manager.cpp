//
// Created by hp on 1/28/2023.
//

#include "manager.h"
user currentUser(3);
set<user>::iterator currPtr;
int manager :: questions_counter = 1;
void manager::LoadData() {
  ifstream file_users;
  file_users.open("file users.txt", ios::in);
  if (file_users.fail()) {
    cout << "NO data base\n\nPlease connect with developer";
    return;
  }
  if (file_users.eof()) {
    return;
  }
  string name, username, email, password;
  int id, ano;
  file_users >> name >> name >> name >> name >> name >> name;
  while (file_users.peek() != EOF) {
    file_users >> name >> id >> username >> email >> password >> ano;
    user use(id, name, username, email, password, ano);
    users.insert(use);
  }
  file_users.close();
  ifstream file_q;
  file_q.open("questions file.txt", ios::in);
  if (file_q.fail()) {
    cout << "NO data base\n\nPlease connect with developer";
    return;
  }
  int q_ID, sender_id, receiver_id, anon;
  string qustion_text, Answer;
  if (!file_q.eof()) {
  file_q >> Answer >> Answer >> Answer;
  file_q.ignore(256, '\n');
  getline(file_q, Answer, '\n');
  getline(file_q, Answer, '\n');
  getline(file_q, Answer, '\n');
  while (file_q.peek() != EOF) {
    file_q >> q_ID >> sender_id >> receiver_id;
    file_q.ignore(256, '\n');
    getline(file_q, qustion_text);
    getline(file_q, Answer);
    file_q >> anon;
    qustion qu(q_ID, sender_id, receiver_id, qustion_text, Answer, anon);
    questions_counter += q_ID;
    bool s1 = false, s2 = false;
    currPtr = users.begin();
    auto ptr = ++users.begin();
    user temp(1);
    for (; currPtr != users.end();) {
      if (currPtr->GetId() == sender_id) {
        temp = *currPtr;
        temp.push_q_I(qu);
        users.erase(currPtr);
        currPtr = ptr;
        if (ptr != users.end())
          ptr++;
        users.insert(temp);
//        for(auto s : users){
//          if(s.GetId() == temp.GetId())
//            break;
//          currPtr++;
//        }
        s1 = true;
      } else if (currPtr->GetId() == receiver_id) {
        temp = *currPtr;
        temp.push_q_was(qu);
        users.erase(currPtr);
        users.insert(temp);
        currPtr = ptr;
        if (ptr != users.end())
          ptr++;
//        for(auto s : users){
//          if(s.GetId() == temp.GetId())
//            break;
//          currPtr++;
//        }
        s2 = true;
      } else
        currPtr++;
      if (s1 && s2)
        break;
      if (ptr != users.end())
        ptr++;

    }
  }
}
  file_q.close();

  ifstream file_th;
  file_th.open("threated file.txt" , ios :: in);
  if(file_th.fail()){
    cout << "NO data base\n\nPlease connect with developer";
    return;
  }
    int pId;
  if(!file_th.eof()) {
    file_th >> Answer >> Answer >> Answer >> Answer;
    file_th.ignore(256, '\n');
    getline(file_th, Answer, '\n');
    getline(file_th, Answer, '\n');
    while (file_th.peek() != EOF) {
      questions_counter++;
      file_th >> q_ID >> pId >> sender_id >> receiver_id;
      file_th.ignore(256, '\n');
      getline(file_th, qustion_text, '\n');
      getline(file_th, Answer, '\n');
      threated thr(q_ID, pId, sender_id, receiver_id, qustion_text, Answer);
      bool s1 = false, s2 = false;

      for (currPtr = users.begin(); currPtr != users.end(); currPtr++) {
        user a = *currPtr;
        if (sender_id == a.GetId()) {
          user temp = a;
          auto it = currPtr;
          it++;
          temp.push_threatedQ(thr);
          users.erase(currPtr);
          users.insert(temp);
          currPtr = it;
          currPtr--;
          s1 = true;
        }
        if (receiver_id == a.GetId()) {
          user temp = a;
          auto it = currPtr;
          it++;
          temp.push_threatedQ(thr);
          users.erase(currPtr);
          users.insert(temp);
          currPtr = it;
          currPtr--;
          s2 = true;
        }
        if (s1 && s2)
          break;
      }
    }
  }
  file_th.close();
}

void manager::menu() {
  int i = 0 ;
  while(i != 9) {
    do {
      cout << "1)Log in\n2)Sign up\n9)exit";
      cin >> i;
    } while (i != 1 && i != 2 && i != 9);
    if (i == 1)
      logIn();
    else if(i == 2)
      SignUp();
    else
      break;
    while (i != 8) {
      cout << "menu:\n"
              "            1: Print questions To me\n"
              "            2: Print questions From me\n"
              "            3: Answer question\n"
              "            4: Delete question\n"
              "            5: Ask question\n"
              "            6: List system users\n"
              "            7: Feed\n"
              "            8: Log out\n"
              "            9: exit\n\n"
              "Enter number in range 1-8: ";
      cin >> i;
      while (i > 9 || i < 1) {
        cout << "Error  invalid number...try again\n";
        cout << "menu:\n"
                "            1: Print questions To me\n"
                "            2: Print questions From me\n"
                "            3: Answer question\n"
                "            4: Delete question\n"
                "            5: Ask question\n"
                "            6: List system users\n"
                "            7: Feed\n"
                "            8: Log out\n\n"
                "Enter number in range 1-8: ";
        cin >> i;
      }
      if (i == 1) {
        currentUser.get_qWasAsked();
      } else if (i == 2)
        currentUser.get_qIAsked();
      else if (i == 3) {
        int id, re_id;
        string s;
        cout << "Enter question id or -1 to cancel : ";
        cin >> id;
        if (currentUser.GetQ(id)) {
          cin.ignore(256, '\n');
          getline(cin, s);
          re_id = currentUser.SetAnswer(id, s);
          auto other = users.begin();
          for (auto a: users) {
            if (a.GetId() == re_id) {
              user temp = a;
              re_id = temp.SetAnswer(id, s);
              users.erase(other);
              users.insert(temp);
              break;
            }
            other++;
          }
          auto ptr = currPtr;
          ptr++;
          users.erase(currPtr);
          users.insert(currentUser);
          currPtr = --ptr;
        }
        SaveData();
      } else if (i == 4) {
        int rec_id, idq;
        cout << "Enter question id or -1 to cancel:";
        cin >> idq;
        rec_id = currentUser.DeleteQ(idq);
        {
          auto rec = users.begin();
          for (auto a: users) {
            if (a.GetId() == rec_id) {
              user temp = a;
              rec_id = temp.DeleteQ(idq);
              users.erase(rec);
              users.insert(temp);
              break;
            }
            rec++;
          }
        }
        auto ptr = currPtr;
        ptr++;
        users.erase(currPtr);
        users.insert(currentUser);
        currPtr = --ptr;
        SaveData();
      } else if (i == 5) {
        AskQ();
        SaveData();
      } else if (i == 6) {
        list_users();
      } else if (i == 7) {
        currentUser.printFeeD();
      } else if (i == 8 || i == 9)
        break;
    }
  }

}

void manager::logIn() {
  string userName , pass;
  cout << "Enter user name && password :";
  cin >> userName >> pass;
  currPtr = users.begin();
  for(auto a : users){
    if(userName == a.GetUserName() && pass == a.GetPassWord()){
      currentUser = a;
      return;
    }
    currPtr++;
  }
  cout << "invalid user name and password\n";
  logIn();
}

void manager::SignUp() {
  user use;
  use.SetId(users.size()+1);
  currentUser = use;
  users.insert(use);
  currPtr = users.begin();
  for(auto a : users){
    if(a.GetId() == use.GetId()){
      break;
    }
    currPtr++;
  }
  SaveData();
}

void manager::SaveData() {
  ofstream file_users , file_q , file_th;
  file_users.open("file users.txt" , ios::out);
  file_q.open("questions file.txt" , ios::out);
  file_th.open("threated file.txt" , ios::out);
  file_users << "name " << "Id " << "username " << "email " << "password " << "anonymous";
  file_q << "question_Id " << "sender_ID " << "receiver_ID\n" <<"question\n" << "Answer\n" << "anonymous";
  file_th << "QId " << "QPairentid " << "seID " << "recID\n" << "qtext\n" << "Answer";
  for(auto a : users){
    file_users << endl << a.GetName() << ' ' << a.GetId() << ' ' << a.GetUserName()<< ' '  << a.GetEmail() << ' ' << a.GetPassWord() << ' ' << a.anonymous;
    a.SaveData(file_q , file_th , users);
  }
  file_users.close();
  file_th.close();
  file_q.close();

}

void manager::AskQ() {
  int i, threId;
  string q;
  set<user>::iterator it = users.begin();
  cout << "Enter user id or -1 to cancel:";
  cin >> i;
  if(i == -1)
    return;
  for(auto a : users){
    if(a.GetId() == i){
      user temp = a;
      if(!a.anonymous)
        cout << "Note: Anonymous questions not allowed for this user\n";
      cout << "for thread question: Enter question id or -1 for new question:";
      cin >> threId;
      if(threId == -1){
        cout << "Enter question text: ";
        cin.ignore(256, '\n');
        getline(cin , q);
        qustion qu(questions_counter , currentUser.GetId() , i , q, a.anonymous);
        questions_counter++;
        currentUser.push_q_I(qu);
        users.erase(currPtr);
        users.insert(currentUser);
        temp.push_q_was(qu);
        users.erase(it);
        users.insert(temp);
        return;
      }
      else{
        cout << "Enter question text: ";
        cin.ignore(256, '\n');
        getline(cin , q);
        threated qu(questions_counter, threId , currentUser.GetId() , i , q , a.anonymous);
        questions_counter++;
        temp.push_threatedQ(qu);
        currentUser.push_threatedQ(qu);
        users.erase(it);
        auto itr = currPtr;
        itr++;
        users.erase(currPtr);
        users.insert(temp);
        users.insert(currentUser);
        currPtr = --itr;
        return;
      }
    }
    it++;
  }
  cout << "invalid user id or question id\n";

}

void manager::list_users() {
  for(auto a : users){
    cout << "ID:" << a.GetId()<< "    Name:" << a.GetName()<< '\n';
  }

}

manager::manager() {
  LoadData();
  menu();


}
