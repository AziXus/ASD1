#include "forwardListUtils.h"
#include "selectionSort.h"

int main() {
  using namespace std;

  auto L = readForwardList<int>();
  cout << L << endl;
  selectionSort(L);
  cout << endl;
}