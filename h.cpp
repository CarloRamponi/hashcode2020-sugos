#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

class Library {
public:
  unsigned int id;
  unsigned int regTime;
  unsigned int bookPDay;
  vector<int> books;

};

int main(int argc, char const *argv[]) {

  ifstream in;
  in.open(argv[1]);

  int N, M, D;
  in >> N >> M >> D;

  cout << "N " << N << " M " << M << "D " << D << endl;

  unsigned int *books = new unsigned int[N];
  vector<Library> libraries(M);

  for(int i = 0; i < N; i++) {
    in >> books[i];
  }

  for(int i = 0; i < M; i++) {
    int b;
    in >> b;

    libraries.at(i).id = i;
    in >> libraries.at(i).regTime;
    in >> libraries.at(i).bookPDay;

    for(int j = 0; j < b; j++) {
      int tmp;
      in >> tmp;
      libraries.at(i).books.push_back(tmp);
    }
    sort(libraries.at(i).books.begin(), libraries.at(i).books.end(), [=](int b1, int b2) { return books[b1] > books[b2]; });
  }

  sort(libraries.begin(), libraries.end(), [=](Library &l1, Library &l2) { return l1.regTime < l2.regTime; });

  for(auto &l : libraries) {
    cout << "Library " << l.id << ", regTime: " << l.regTime << endl;
    for(auto &b : l.books) {
      cout << "(" << b << ", " << books[b] << "), ";
    }
    cout << endl;
  }

  return 0;
}
