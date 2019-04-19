#ifndef NODE_H
#define NODE_H

class node
{
public:
	node(const int& data = 0, node* parent = nullptr, node* left = nullptr, node* right = nullptr);
	int get_data() const noexcept;

private:
	int data;
	node* parent,
		* left,
		* right;
	friend class bin_tree;
};

#endif 
