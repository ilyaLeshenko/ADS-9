// Copyright 2022 NNTU-CS
#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <memory>
#include <string>

class PMTree {
public:
    explicit PMTree(const std::vector<char>& elements);
    ~PMTree() = default;

    std::vector<std::vector<char>> GetAllPerms() const;
    std::vector<char> GetPerm1(int num) const;
    std::vector<char> GetPerm2(int num) const;
    int GetTotalPermutations() const { return total_permutations_; }

private:
    struct Node {
        char value;
        std::vector<std::unique_ptr<Node>> children;
        explicit Node(char v) : value(v) {}
    };

    std::unique_ptr<Node> root_;
    int total_permutations_;

    void BuildTree(Node* parent, const std::vector<char>& remaining_elements);
    void GetAllPermsHelper(const Node* node, std::vector<char>& current,
                         std::vector<std::vector<char>>& result) const;
    void GetPerm1Helper(const Node* node, int& counter, int target_num,
                      std::vector<char>& result) const;
    void GetPerm2Helper(const Node* node, int& num, std::vector<char>& result) const;
};

std::vector<std::vector<char>> GetAllPerms(const PMTree& tree);
std::vector<char> GetPerm1(const PMTree& tree, int num);
std::vector<char> GetPerm2(const PMTree& tree, int num);

#endif  // TREE_H_
