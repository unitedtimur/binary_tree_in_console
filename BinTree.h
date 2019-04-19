#ifndef BIN_TREE_H
#define BIN_TREE_H

#include "Node.h"
#include <ostream>

class bin_tree
{
public:
	explicit bin_tree(const int& n);
	bin_tree(const int& n, const int* arr);
	explicit bin_tree(const bin_tree& tree);
	~bin_tree();

	int find_hight(node* _node) const noexcept;
	void add_node(node* _node, const int& data) const noexcept;
	void print_lrd(node* _node) const noexcept;
	void print_rld(node* _node) const noexcept;
	void print_drl(node* _node) const noexcept;
	void delete_leaf(node* _node) const noexcept;
	void delete_tree(node* _node) const noexcept;
	void clean_tree() const noexcept;
	bin_tree& operator = (const bin_tree& tree);
	node* find_key(node* _node, const int& data) const noexcept;
	node* find_min(node* _node) const noexcept;
	node* find_max(node* _node) const noexcept;
	node* get_root() const noexcept;
	friend std::ostream& operator << (std::ostream& os, bin_tree& bin);
private:
	node* root;
	bool flag;
	void copy_tree(node* from, node* to, bool flag);

	node* build_tree(node* _node, const int& n) const noexcept;
	node* build_tree(node* _node, const int& n, const int* arr, int& i) const noexcept;
};

#endif
