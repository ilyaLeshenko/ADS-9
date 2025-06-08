// Copyright 2022 NNTU-CS
#ifndef TREE_H_
#define TREE_H_

#include <memory>
#include <vector>

class PMTree {
 public:
  struct Node {
    explicit Node(char v) : value(v) {}
    char value;
    std::vector<std::unique_ptr<Node>> children;
  };

  explicit PMTree(const std::vector<char>& input);

  const std::vector<char>& getElements() const { return elements_; }
  int countPermutations() const;
  std::vector<std::vector<char>> getAllPerms() const;

 private:
  std::unique_ptr<Node> root_;
  std::vector<char> elements_;

  static int factorial(int n);
  static void build(Node* parent, const std::vector<char>& remaining);
  static void collect(const Node* node,
                      std::vector<char>& path,
                      std::vector<std::vector<char>>& out);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // TREE_H_
