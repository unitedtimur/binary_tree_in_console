#include "BinTree.h"
#include <cstdlib>
#include <iostream>

bin_tree::bin_tree(const int& n) :
	root(build_tree(nullptr, n))
	{}

bin_tree::bin_tree(const int& n, const int* arr)
{
	auto i = 0;
	root = build_tree(nullptr, n, arr, i);
}

bin_tree::bin_tree(const bin_tree& tree)
{
	if (tree.root == nullptr)
	{
		root = nullptr;
	}
	else
	{
		root = new node(tree.root->data);
		copy_tree(tree.root->left, root, false);
		copy_tree(tree.root->right, root, true);
	}
}

bin_tree::~bin_tree()
{
	clean_tree();
	if (root == nullptr) delete root;
}

int bin_tree::find_hight(node* _node) const noexcept
{
	if (_node == nullptr) return 0;

	static int h1{}, h2{};

	if (_node->left) h1 = find_hight(_node->left);
	if (_node->right) h2 = find_hight(_node->right);

	return h1 > h2 ? h1 + 1: h2 + 1; //TODO верная высота?
}

void bin_tree::add_node(node* _node, const int& data) const noexcept
{
	if (_node->left == nullptr)
	{
		node* obj = new node(data, _node);
		_node->left = obj;
		return;
	}

	if (_node->right == nullptr)
	{
		node* obj = new node(data, _node);
		_node->right = obj;
		return;
	}

	rand() % 2 ? add_node(_node->left, data) : add_node(_node->right, data);
}

void bin_tree::print_lrd(node* _node) const noexcept
{
	if (_node == nullptr) return;

	try
	{
		print_lrd(_node->left);
		print_lrd(_node->right);
		std::cout << _node->data << " ";
	}
	catch (_exception ex)
	{
		std::cout << "//Here fatal error --->" << ex.name << std::endl;
	}
}

void bin_tree::print_rld(node* _node) const noexcept
{
	if (_node == nullptr) return;

	try
	{
		print_lrd(_node->right);
		print_lrd(_node->left);
		std::cout << _node->data << " ";
	}
	catch (_exception ex)
	{
		std::cout << "//Here fatal error --->" << ex.name << std::endl;
	}
}

void bin_tree::print_drl(node* _node) const noexcept
{
	if (_node == nullptr) return;

	try
	{
		std::cout << _node->data << " ";
		print_lrd(_node->right);
		print_lrd(_node->left);
	}
	catch (_exception ex)
	{
		std::cout << "//Here fatal error --->" << ex.name << std::endl;
	}
}

void bin_tree::delete_leaf(node* _node) const noexcept
{
	if (_node->left == nullptr && _node->right == nullptr)
	{
		_node->parent->left == _node ? _node->parent->left = nullptr : _node->parent->right = nullptr;

		delete _node;
		return;
	}

	_node->left != nullptr ? delete_leaf(_node->left) : delete_leaf(_node->right);
}

void bin_tree::delete_tree(node* _node) const noexcept
{
	if (_node->left == nullptr && _node->right == nullptr)
	{
		delete_leaf(_node);
		return;
	}

	if (_node->left && _node->right == nullptr)
	{
		node* obj = _node->parent;

		obj->left == _node ? obj->left = _node->right : obj->right = _node->left;

		_node->left->parent = obj;

		delete _node;

		return;
	}

	if (_node->left == nullptr && _node->right)
	{
		node* obj = _node->parent;

		obj->left == _node ? obj->left = _node->right : obj->right = _node->right;

		_node->right->parent = obj;

		delete _node;

		return;
	}

	node* obj1 = _node->parent;
	node* obj2 = _node;

	while(obj2->left)
	{
		obj2 = obj2->left;
	}

	if (obj2->right == nullptr)
	{
		obj2->parent->left = nullptr;
	}
	else
	{
		obj2->parent->left = obj2->right;
		obj2->right->parent = obj2->parent;
	}

	obj1->left == _node ? obj1->left = obj2 : obj1->right = obj2;

	obj2->left = _node->left;
	obj2->right = _node->right;
	obj2->parent = obj1;

	if (obj2->left)
	{
		obj2->left->parent = obj2;
	}

	obj2->right->parent = obj2;

	delete _node;
}

void bin_tree::clean_tree() const noexcept
{
	if (root == nullptr) return;

	node * obj = root;

	while (obj->left)
	{
		delete_tree(obj->left);
	}

	while(obj->right)
	{
		delete_tree(obj->right);
	}
}

bin_tree& bin_tree::operator=(const bin_tree& tree)
{
	return *this;
}

node* bin_tree::find_key(node* _node, const int& data) const noexcept
{
	if (_node == nullptr) return nullptr;

	if (_node->data == data) return _node;

	return find_key(_node->left, data) ? find_key(_node->left, data) : find_key(_node->right, data);
}

node* bin_tree::find_min(node* _node) const noexcept
{
	if (_node == nullptr) return nullptr;

	auto min = _node;
	auto left = find_min(_node->left);
	auto right = find_min(_node->right);

	if (left && left->data < min->data) min = left;
	if (right && right->data < min->data) min = right;

	return min;
}

node* bin_tree::find_max(node* _node) const noexcept
{
	if (_node == nullptr) return nullptr;

	auto max = _node;
	auto left = find_max(_node->left);
	auto right = find_max(_node->right);

	if (left && left->data > max->data) max = left;
	if (right && right->data > max->data) max = right;

	return max;
}

node* bin_tree::get_root() const noexcept
{
	return root;
}

void bin_tree::copy_tree(node* from, node* to, bool flag)
{
	if (from == nullptr) return;

	auto obj = new node(from->data, to);

	flag ? to->right = obj : to->left = obj;

	copy_tree(from->left, obj, false);
	copy_tree(from->right, obj, true);
}

node* bin_tree::build_tree(node* _node, const int& n) const noexcept
{
	if (n == 0) return nullptr;

	node* obj = new node(rand() % 50, _node);
	
	auto nL = (n - 1) / 2;
	auto nR = n - 1 - nL;

	obj->left = build_tree(obj, nL);
	obj->right = build_tree(obj, nR);

	return obj;
}

node* bin_tree::build_tree(node* _node, const int& n, const int* arr, int& i) const noexcept
{
	node* obj = new node(arr[i], _node);

	auto nL = (n - 1) / 2;
	auto nR = n - 1 - nL;

	if (nL)
	{
		++i;
		obj->left = build_tree(obj, nL, arr, i);
	}
	if (nR)
	{
		++i;
		obj->right = build_tree(obj, nR, arr, i);
	}

	return obj;
}

std::ostream& operator<<(std::ostream& os, bin_tree& bin)
{
	bin.print_lrd(bin.get_root());
	return os;
}
