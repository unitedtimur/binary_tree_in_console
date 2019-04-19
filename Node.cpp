#include  "Node.h"

node::node(const int& data, node* parent, node* left, node* right) : 
	data(data),
	parent(parent),
	left(left),
	right(right)
	{}

int node::get_data() const noexcept
{
	return data;
}
