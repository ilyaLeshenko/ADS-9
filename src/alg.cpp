// Copyright 2022 NNTU-CS
#include <algorithm>

#include "tree.h"

namespace {

int safeFactorial(int n) {
  int r = 1;
  for (int i = 2; i <= n; ++i) r *= i;
  return r;
}

}  // namespace

int PMTree::factorial(int n) { return safeFactorial(n); }

void PMTree::build(Node* parent, const std::vector<char>& remaining) {
  if (remaining.empty()) return;
  for (char c : remaining) {
    auto child = std::make_unique<Node>(c);
    std::vector<char> next;
    next.reserve(remaining.size() - 1);
    for (char d : remaining) {
      if (d != c) next.push_back(d);
    }
    build(child.get(), next);
    parent->children.push_back(std::move(child));
  }
}

PMTree::PMTree(const std::vector<char>& input) : elements_(input) {
  std::sort(elements_.begin(), elements_.end());
  root_ = std::make_unique<Node>('\0');
  build(root_.get(), elements_);
}

int PMTree::countPermutations() const {
  return factorial(static_cast<int>(elements_.size()));
}

void PMTree::collect(const Node* node,
                     std::vector<char>& path,
                     std::vector<std::vector<char>>& out) {
  if (node->value != '\0') path.push_back(node->value);
  if (node->children.empty()) {
    if (!path.empty()) out.push_back(path);
  } else {
    for (const auto& child : node->children) {
      collect(child.get(), path, out);
    }
  }
  if (!path.empty()) path.pop_back();
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
  std::vector<std::vector<char>> out;
  std::vector<char> path;
  collect(root_.get(), path, out);
  return out;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  return tree.getAllPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = tree.getAllPerms();
  if (num < 1 || num > static_cast<int>(all.size())) return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  const auto& elems = tree.getElements();
  int total = tree.countPermutations();
  if (num < 1 || num > total) return {};
  std::vector<char> remaining = elems;
  std::vector<char> result;
  int idx = num - 1;
  for (int m = static_cast<int>(elems.size()); m > 0; --m) {
    int fact = safeFactorial(m - 1);
    int pos = idx / fact;
    result.push_back(remaining[pos]);
    remaining.erase(remaining.begin() + pos);
    idx %= fact;
  }
  return result;
}
