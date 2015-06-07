#include <iostream>
#include <sstream>
#include "data.h"

int main()
{
  std::string row;
  std::string op;
  std::string ID1, ID2;
  std::string PW1, PW2;
  int a;
  std::string logedinID = "";
  AccountT T;
  History Hist;
  while(std::getline(std::cin, row))
  {
    std::istringstream input(row);
    input >> op;

    if (op == "create") // find 하는데 드는 시간은 log n
    {
      input >> ID1 >> PW1;
      if (T.find(ID1) == T.end()) // 아무것도 없을 때도 성립?
      {
        Info temp;
        temp.password = PW1;
        temp.balance = 0;
        T[ID1] = temp;
      }
      else
        std::cout << "ID " << ID1 << " exists, ";
    }

    else if (op == "login") // log n
    {
      input >> ID1 >> PW1;
      AccountT::iterator id1_pos = T.find(ID1);
      if (id1_pos == T.end())
        std::cout << "ID " << ID1 << " not found\n";
      else if (id1_pos->second.password != PW1)
        std::cout << "wrong password\n";
      else
      {
        std::cout << "success\n";
        logedinID = ID1;
      }
    }

    else if (op == "delete") // log n
    {
      input >> ID1 >> PW1;
      AccountT::iterator id1_pos = T.find(ID1);
      if (id1_pos == T.end())
        std::cout << "ID " << ID1 << " not found\n";
      else if (id1_pos->second.password != PW1)
        std::cout << "wrong password\n";
      else
      {
        std::cout << "success\n";
        T.erase(ID1);
      }
    }

    else if (op == "merge") // n1 n2 -> log n1 log n2 h1 h2
    {
      input >> ID1 >> PW1 >> ID2 >> PW2;
      AccountT::iterator id1_pos = T.find(ID1);
      AccountT::iterator id2_pos = T.find(ID2);
      if (id1_pos == T.end())
        std::cout << "ID " << ID1 << " not found\n";
      else if (id2_pos == T.end())
        std::cout << "ID " << ID2 << " not found\n";
      else if (id1_pos->second.password != PW1)
        std::cout << "wrong password1\n";
      else if (id2_pos->second.password != PW2)
        std::cout << "wrong password2\n";
      else
      {
        std::vector<int>::iterator it1 = id1_pos->second.log_idx.begin();
        std::vector<int>::iterator it2 = id2_pos->second.log_idx.begin();
        std::vector<int> temp;

        while (it1 != id1_pos->second.log_idx.end() && it2 != id2_pos->second.log_idx.end())
        {
          if (*it1 < *it2)
          {
            temp.push_back(*it1);
            it1++;
          }
          else if (*it1 == *it2)
          {
            it1++; it2++;
//            Hist.erase(Hist.begin() + *it1); //지우는데 들어가는 시간?
            //지우고 나면 다른 인덱스 하나씩 당겨야한다!!
          }
          else
          {
            temp.push_back(*it2);
            if (Hist[*it2].from == ID2)
              Hist[*it2].from = ID1;
            else Hist[*it2].to = ID1;
            it2++;
          }
        }
        if (it1 != id1_pos->second.log_idx.end() && it2 == id1_pos->second.log_idx.end())
          for (;it1 != id1_pos->second.log_idx.end(); ++it1)
            temp.push_back(*it1);
        else if (it1 == id1_pos->second.log_idx.end() && it2 != id1_pos->second.log_idx.end())
        {
          for (;it2 != id2_pos->second.log_idx.end(); ++it2)
          {
            temp.push_back(*it2);
            if (Hist[*it2].from == ID2)
              Hist[*it2].from = ID1;
            else Hist[*it2].to = ID1;
          }
        }

        id1_pos->second.log_idx = temp;
        T.erase(ID2);
      }
    }
  }

  return 0;
}

