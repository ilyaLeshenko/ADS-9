// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <utility>
#include <memory>
#include <algorithm>
#include <vector>
#include "tree.h"

void PMTree::buildTree(Node* parent, const std::vector<char>& remaining) {
  for (size_t i = 0; i < remaining.size(); ++i) {
    auto newNode = std::make_unique<Node>();
    newNode->value = remaining[i];
    std::vector<char> newRemaining;
    for (size_t j = 0; j < remaining.size(); ++j) {
      if (j != i) newRemaining.push_back(remaining[j]);
    }
    buildTree(newNode.get(), newRemaining);
    parent->children.push_back(std::move(newNode));
  }
}

PMTree::PMTree(const std::vector<char>& input) : elements(input) {
  std::sort(elements.begin(), elements.end());
  root = std::make_unique<Node>();
  buildTree(root.get(), elements);
}

int PMTree::factorial(int n) const {
  int res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

int PMTree::countPermutations() const {
  return factorial(elements.size());
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
  std::vector<std::vector<char>> res;
  if (!root) return res;
  std::function<void(Node*, std::vector<char>&)> collectPerms;
  collectPerms = [&](Node* node, std::vector<char>& current) {
      current.push_back(node->value);
      if (node->children.empty()) {
          res.push_back(current);
      } else {
          for (auto& child : node->children) {
              collectPerms(child.get(), current);
          }
      }
      current.pop_back();
  };
  std::vector<char> current;
  for (auto& child : root->children) {
      collectPerms(child.get(), current);
  }
  return res;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  return tree.getAllPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = getAllPerms(tree);
  if (num < 1 || num > all.size()) return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  const auto& elements = tree.getElements();
  int total = tree.countPermutations();
  if (num < 1 || num > total) return {};
  std::vector<char> res;
  std::vector<char> remaining = elements;
  int currentNum = num - 1;
  for (int n = elements.size(); n > 0; --n) {
    int fact = 1;
    for (int i = 1; i < n; ++i) fact *= i;
    int index = currentNum / fact;
    if (index >= remaining.size()) return {};
    res.push_back(remaining[index]);
    remaining.erase(remaining.begin() + index);
    currentNum %= fact;
  }
  return res;
}
