#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

#define SIZE 200

using namespace std;

class Project {
  private:
    //>>>Record data<<<
    char buf[SIZE];
    
    
    void pack();
    void unpack();
  public:
    void menu();
    void insert();
    void display();
    void search();
    void modify();
    void delete();
};

void menu() {
  while(1) {
    int ch;
    cout << "FS Weblink\n\n";
    cout << "\t1) Insert\n";
    cout << "\t2) Display\n";
    cout << "\t3) Search\n";
    cout << "\t4) Modify\n";
    cout << "\t5) Delete\n";
    cout << "\t6) Exit\n";
    cout << ">>> ";
    cin >> ch;
    cout << "\n\n";
    
    switch(ch) {
      case 1:
        p.insert();
      break;
      case 2:
        p.display();
      break;
      case 3:
        p.search();
      break;
      case 4:
        p.modify();
      break;
      case 5:
        p.delete();
      break;
      case 6:
        exit(0);
      break;
      default:
      continue;
    }
  }
}

int main() {
  Project p;
  p.menu();
  return 0;
}
