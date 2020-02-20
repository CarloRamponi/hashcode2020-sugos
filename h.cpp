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
  float punteggio;
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

    unsigned int score = 0;

    for(int j = 0; j < b; j++) {
      int tmp;
      cin >> tmp;
      libraries.at(i).books.push_back(tmp);
      score += books[tmp];
    }

    libraries.at(i).punteggio = static_cast<float>((score * libraries.at(i).bookPDay)) / (libraries.at(i).booksSize * libraries.at(i).regTime * libraries.at(i).regTime);

    sort(libraries.at(i).books.begin(), libraries.at(i).books.end(), [=](int b1, int b2) { return books[b1] > books[b2]; });
  }

  sort(libOrder, libOrder + M, [=](int l1, int l2) {
    if(libraries.at(l1).punteggio == libraries.at(l2).punteggio)
      return libraries.at(l1).regTime < libraries.at(l2).regTime;
    return libraries.at(l1).punteggio > libraries.at(l2).punteggio;
  });

  // for(int l = 0; l < M; l++) {
  //   cout << "Library " << libraries.at(libOrder[l]).id << ", regTime: " << libraries.at(libOrder[l]).regTime << ", score: " << libraries.at(libOrder[l]).punteggio << endl;
  //   for(auto &b : libraries.at(libOrder[l]).books) {
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

  unsigned int lmao = 0;

  while(day < D) {

    //cerr << "Day " << day << endl;

    for(auto &l : simLibraries) {
      //cerr << "Lib " << l << " bpd " << libraries.at(l).bookPDay << " ";
      int bookScannedToday = 0;
      while(bookScannedToday < libraries.at(l).bookPDay && libraries.at(l).simBookIndex < libraries.at(l).booksSize) {
        //cerr << "Book " << libraries.at(l).books.at(libraries.at(l).simBookIndex) << " ";
        if(!bookScanned.at(libraries.at(l).books.at(libraries.at(l).simBookIndex))) {
          //cerr << "scanning" << " value " << books[libraries.at(l).books.at(libraries.at(l).simBookIndex)] << " " << endl;
          simBooks.at(l).push_back(libraries.at(l).books.at(libraries.at(l).simBookIndex));
          bookScanned.at(libraries.at(l).books.at(libraries.at(l).simBookIndex)) = true;
          lmao += books[libraries.at(l).books.at(libraries.at(l).simBookIndex)];
          bookScannedToday++;
          libraries.at(l).simBookIndex++;
        } else {
          //cerr << "already scanned" << endl;
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

  cerr << lmao << endl;

  return 0;
}
