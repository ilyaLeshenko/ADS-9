// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <stdexcept>

PMTree::PMTree(const std::vector<char>& elements) : total_permutations_(0) {
    if (elements.empty()) return;
    root_ = std::make_unique<Node>('\0');  // Фиктивный корень
    BuildTree(root_.get(), elements);
}

void PMTree::BuildTree(Node* parent, const std::vector<char>& remaining_elements) {
    if (remaining_elements.empty()) {
        total_permutations_++;
        return;
    }

    for (size_t i = 0; i < remaining_elements.size(); ++i) {
        auto new_node = std::make_unique<Node>(remaining_elements[i]);
        std::vector<char> new_remaining = remaining_elements;
        new_remaining.erase(new_remaining.begin() + i);
        BuildTree(new_node.get(), new_remaining);
        parent->children.push_back(std::move(new_node));
    }
}

std::vector<std::vector<char>> PMTree::GetAllPerms() const {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    GetAllPermsHelper(root_.get(), current, result);
    return result;
}

void PMTree::GetAllPermsHelper(const Node* node, std::vector<char>& current,
                             std::vector<std::vector<char>>& result) const {
    if (node->children.empty() && !current.empty()) {
        result.push_back(current);
        return;
    }

    for (const auto& child : node->children) {
        current.push_back(child->value);
        GetAllPermsHelper(child.get(), current, result);
        current.pop_back();
    }
}

std::vector<char> PMTree::GetPerm1(int num) const {
    std::vector<char> result;
    if (num < 1 || num > total_permutations_) return result;
    int counter = 1;
    GetPerm1Helper(root_.get(), counter, num, result);
    return result;
}

void PMTree::GetPerm1Helper(const Node* node, int& counter, int target_num,
                          std::vector<char>& result) const {
    if (node->children.empty() && !result.empty()) {
        if (counter == target_num) return;
        counter++;
        return;
    }

    for (const auto& child : node->children) {
        result.push_back(child->value);
        GetPerm1Helper(child.get(), counter, target_num, result);
        if (counter == target_num) return;
        result.pop_back();
    }
}

std::vector<char> PMTree::GetPerm2(int num) const {
    std::vector<char> result;
    if (num < 1 || num > total_permutations_) return result;
    int adjusted_num = num;
    GetPerm2Helper(root_.get(), adjusted_num, result);
    return result;
}

void PMTree::GetPerm2Helper(const Node* node, int& num, std::vector<char>& result) const {
    if (node->children.empty()) return;

    int factorial = 1;
    int children_count = static_cast<int>(node->children.size());
    for (int i = 1; i <= children_count - 1; ++i) {
        factorial *= i;
    }

    int index = (num - 1) / factorial;
    result.push_back(node->children[index]->value);
    num = (num - 1) % factorial + 1;
    GetPerm2Helper(node->children[index].get(), num, result);
}

std::vector<std::vector<char>> GetAllPerms(const PMTree& tree) {
    return tree.GetAllPerms();
}

std::vector<char> GetPerm1(const PMTree& tree, int num) {
    return tree.GetPerm1(num);
}

std::vector<char> GetPerm2(const PMTree& tree, int num) {
    return tree.GetPerm2(num);
}
