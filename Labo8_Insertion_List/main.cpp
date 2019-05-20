#include "listUtils.h"
#include "insertionSort.h"

int main() {
  using namespace std;

  auto L = readList<int>();
  cout << L << endl;
  insertionSort(L);
  cout << endl;
}