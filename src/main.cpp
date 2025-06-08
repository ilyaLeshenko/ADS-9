// Copyright 2022 NNTU-CS
#include "tree.h"

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <random>
#include <vector>

void PrintVector(const std::vector<char>& vec) {
  for (char c : vec) {
    std::cout << c;
  }
  std::cout << std::endl;
}

void RunExperiment() {
  std::ofstream data_file("experiment_data.csv");
  data_file << "n,AllPerms(µs),GetPerm1(µs),GetPerm2(µs)\n";

  for (int n = 1; n <= 8; ++n) {
    std::vector<char> elements;
    for (int i = 0; i < n; ++i) {
      elements.push_back('1' + i);
    }

    PMTree tree(elements);

    auto start = std::chrono::high_resolution_clock::now();
    auto all_perms = GetAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_all = std::chrono::duration_cast<std::chrono::microseconds>(
        end - start).count();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, tree.GetTotalPermutations());
    int random_num = distr(gen);

    start = std::chrono::high_resolution_clock::now();
    auto perm1 = GetPerm1(tree, random_num);
    end = std::chrono::high_resolution_clock::now();
    auto duration_perm1 = std::chrono::duration_cast<std::chrono::microseconds>(
        end - start).count();

    start = std::chrono::high_resolution_clock::now();
    auto perm2 = GetPerm2(tree, random_num);
    end = std::chrono::high_resolution_clock::now();
    auto duration_perm2 = std::chrono::duration_cast<std::chrono::microseconds>(
        end - start).count();

    data_file << n << "," << duration_all << "," << duration_perm1 << ","
              << duration_perm2 << "\n";
    std::cout << "n=" << n << " | AllPerms: " << duration_all << "µs"
              << " | GetPerm1: " << duration_perm1 << "µs"
              << " | GetPerm2: " << duration_perm2 << "µs" << std::endl;
  }
  data_file.close();
}

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  std::cout << "All permutations:" << std::endl;
  auto perms = GetAllPerms(tree);
  for (const auto& perm : perms) {
    PrintVector(perm);
  }

  std::cout << "\nPermutation #2 (GetPerm1): ";
  PrintVector(GetPerm1(tree, 2));

  std::cout << "Permutation #2 (GetPerm2): ";
  PrintVector(GetPerm2(tree, 2));

  std::cout << "\nRunning experiment..." << std::endl;
  RunExperiment();

  return 0;
}
