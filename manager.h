//
// Created by hp on 1/28/2023.
//
#include "user.h"
#ifndef ASKME_MANAGER_H
#define ASKME_MANAGER_H
#include <fstream>
#include <set>

class manager {
 private:
  set<user> users;
 public:
  static int questions_counter;
  manager();
  void LoadData();
  void logIn();
  void SignUp();
  void AskQ();
  void menu();
  void list_users();
  void SaveData();
};


#endif //ASKME_MANAGER_H
