// Copyright 2022 NNTU-CS
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "tree.h"

int main() {
  std::vector<int> sizes{1, 2, 3, 4, 5, 6, 7};
  std::mt19937 gen(std::random_device {}());
  std::cout << std::fixed << std::setprecision(3);
  std::cout << "n\tall(ms)\tperm1(ms)\tperm2(ms)\n";
  for (int n : sizes) {
    std::vector<char> in;
    for (int i = 0; i < n; ++i) in.push_back('A' + i);
    PMTree tree(in);
    int total = tree.countPermutations();
    std::uniform_int_distribution<> dist(1, total);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto a = getAllPerms(tree);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto d_all =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() /
        1000.0;
    t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i) getPerm1(tree, dist(gen));
    t1 = std::chrono::high_resolution_clock::now();
    auto d_p1 =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() /
        10000.0;
    t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i) getPerm2(tree, dist(gen));
    t1 = std::chrono::high_resolution_clock::now();
    auto d_p2 =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() /
        10000.0;
    std::cout << n << '\t' << d_all << '\t' << d_p1 << '\t' << d_p2 << '\n';
  }
  std::vector<char> demo{'1', '2', '3'};
  PMTree demo_tree(demo);
  for (const auto& p : getAllPerms(demo_tree)) {
    for (char c : p) std::cout << c;
    std::cout << '\n';
  }
}
