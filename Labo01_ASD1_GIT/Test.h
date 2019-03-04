#ifndef LABO_01_TEST_H
#define LABO_01_TEST_H

#include <vector>

std::vector<int> generateVector(std::size_t size);

unsigned trier2(std::vector<int>& v);
unsigned chercherSiContient2(const std::vector<int>& v, int val);
unsigned g2(std::vector<int>& v);

void testTrier(int nbValeurs, int base);
void testChercherSiContient(int nbValeurs, int base, int nbTests);
void testG(int nbValeurs, int base);



#endif //LABO_01_TEST_H