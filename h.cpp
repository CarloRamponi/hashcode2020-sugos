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
  unsigned int booksSize;
  unsigned int simBookIndex = 0;
  vector<int> books;
};

int main(int argc, char const *argv[]) {

  int N, M, D;
  cin >> N >> M >> D;

  // cout << "N " << N << " M " << M << "D " << D << endl;

  unsigned int *books = new unsigned int[N];
  unsigned int *libOrder = new unsigned int[M];
  vector<Library> libraries(M);

  for(int i = 0; i < N; i++) {
    cin >> books[i];
  }

  for(int i = 0; i < M; i++) {
    libOrder[i] = i;
    int b;
    cin >> b;

    libraries.at(i).id = i;
    libraries.at(i).booksSize = b;
    cin >> libraries.at(i).regTime;
    cin >> libraries.at(i).bookPDay;

    for(int j = 0; j < b; j++) {
      int tmp;
      cin >> tmp;
      libraries.at(i).books.push_back(tmp);
    }
    sort(libraries.at(i).books.begin(), libraries.at(i).books.end(), [=](int b1, int b2) { return books[b1] > books[b2]; });
  }

  sort(libOrder, libOrder + M, [=](int l1, int l2) { return libraries.at(l1).regTime < libraries.at(l2).regTime; });

  // for(auto &l : libraries) {
  //   cout << "Library " << l.id << ", regTime: " << l.regTime << endl;
  //   for(auto &b : l.books) {
  //     cout << "(" << b << ", " << books[b] << "), ";
  //   }
  //   cout << endl;
  // }

  /* Order has been decided, now run simulation. */

  vector<bool> bookScanned(N, false);
  unsigned int registering = 0;
  vector<int> simLibraries;
  vector<vector<int>> simBooks(M, vector<int>());

  unsigned int day = 0;
  unsigned int libIndex = 0;

  while(day <= D) {

    for(auto &l : simLibraries) {
      int bookScannedToday = 0;
      while(bookScannedToday < libraries.at(l).bookPDay && libraries.at(l).simBookIndex < libraries.at(l).booksSize) {
        if(!bookScanned.at(libraries.at(l).books.at(libraries.at(l).simBookIndex))) {
          simBooks.at(l).push_back(libraries.at(l).books.at(libraries.at(l).simBookIndex));
          bookScanned.at(libraries.at(l).books.at(libraries.at(l).simBookIndex)) = true;
          bookScannedToday++;
          libraries.at(l).simBookIndex++;
        } else {
          libraries.at(l).simBookIndex++;
        }
      }
    }

    if(registering >= day && libIndex < M) {
      simLibraries.push_back(libraries.at(libOrder[libIndex]).id);
      registering += libraries.at(libOrder[libIndex]).regTime;
      libIndex++;
    }

    day++;
  }

  int zeros = 0;
  for(auto &l : simLibraries) {
    if(simBooks.at(l).size() == 0) zeros++;
  }

  cout << simLibraries.size() - zeros << endl;

  for(auto &l : simLibraries) {
    if(simBooks.at(l).size() > 0) {
      cout << l << " " << simBooks.at(l).size() << endl;
      for(auto &b : simBooks.at(l)) {
        cout << b << " ";
      }
      cout << endl;
    }
  }

  return 0;
}
