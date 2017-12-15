#pragma once
#include "stdafx.h"
#include <iostream>
#include <type_traits>
#include <functional>

namespace struktury
{
	template <typename Type, class Comparable = std::less_equal<Type>>
	class bst
	{
	protected:
		class node
		{
		public:
			Type value;
			node *left;
			node *right;
			node(Type value);
			node(const node &pattern);
			~node();
			void insert(Type value);
			bool remove(Type value);
			bool find(Type value);
			void destruct();
			void* copy(const node *pattern);
			std::ostream& print(std::ostream &output);
		};

		//koniec klasy
		node *root;

	public:
		bst();
		bst(Type value);
		bst(std::initializer_list<Type> list);
		bst(const bst &pattern);
		bst(bst<Type, Comparable> &&pattern);
		bst<Type, Comparable>& operator=(const bst &pattern);
		bst<Type, Comparable>& operator=(bst &&pattern);
		~bst();
		void insert(Type value);
		bool remove(Type value);
		bool find(Type value);
		friend std::ostream& operator<<(std::ostream &output, const bst &pattern)
		{
			return pattern.root->print(output);
		}
	protected:
		bool isEmpty();
	};


	template<typename Type, class Comparable>
	class bst<Type*, Comparable> : public bst<Type, Comparable>
	{
	public:
		using bst<Type, Comparable>::bst;
		inline void insert(Type *value)
		{
			this->bst<Type, Comparable>::insert(*value);
		}

		inline bool remove(Type *value)
		{
			return this->bst<Type, Comparable>::remove(*value);
		}

		inline bool find(Type *value)
		{
			return this->bst<Type, Comparable>::find(*value);
		}

		friend std::ostream& operator<<(std::ostream &output, const bst &pattern)
		{
			return pattern.root->print(output);
		}
	};

	template<typename Type>
	class bst<Type*> : public bst<Type*, std::less_equal<Type>>
	{
	public:
		using bst<Type*, std::less_equal<Type>>::bst;
		friend std::ostream& operator<<(std::ostream &output, const bst &pattern)
		{
			return pattern.root->print(output);
		}
	};


	template<typename T>
	struct geq
	{
		bool operator()(const T& l, const T& r) const
		{
			return l >= r;
		}
	};

	template<>
	struct geq<const char*>
	{
		bool operator()(const char *l, const char *r) const
		{
			std::string left = l;
			std::string right = r;
			return l >= r;
		}
	};

	template<>
	struct geq<char*>
	{
		bool operator()(const char *l, const char *r) const
		{
			std::string left = l;
			std::string right = r;
			return l >= r;
		}
	};

	template<typename T>
	struct geq<T*>
	{
		bool operator()(const char *l, const char *r)
		{
			return (*l) >= (*r);
		}
	};
}




using namespace struktury;

template<typename Type, class Comparable>
struktury::bst<Type, Comparable>::bst()
{
	this->root = nullptr;
}

template<typename Type, class Comparable>
struktury::bst<Type, Comparable>::bst(Type value)
{
	node *add = new node(value);
	this->root = add;
}

template<typename Type, class Comparable>
struktury::bst<Type, Comparable>::bst(std::initializer_list<Type> list) : bst()
{
	for (auto i : list)
		this->insert(i);
}

template<typename Type, class Comparable>
struktury::bst<Type, Comparable>::bst(const bst &pattern)
{
	if (pattern.root == nullptr)
	{
		this->root = nullptr;
		return;
	}
	else
		this->root = reinterpret_cast<node*>(this->root->copy(pattern.root));
}


template<typename Type, class Comparable>
void* struktury::bst<Type, Comparable>::node::copy(const node *pattern)
{
	node *add = new node(pattern->value);
	if (pattern->left == nullptr && pattern->right == nullptr)
	{
		add->left = add->right = nullptr;
		return add;
	}

	if (pattern->left != nullptr)
		add->left = reinterpret_cast<node*>(this->copy(pattern->left));
	else
		add->left = nullptr;
	if (pattern->right != nullptr)
		add->right = reinterpret_cast<node*>(this->copy(pattern->right));
	else
		add->right = nullptr;
	return add;
}




template<typename Type, class Comparable>
struktury::bst<Type, Comparable>::bst(bst &&pattern)
{
	this->root = pattern.root;
	pattern.root = nullptr;
}


template<typename Type, class Comparable>
bst<Type, Comparable>& struktury::bst<Type,Comparable>::operator=(const bst &pattern)
{
	this->~bst();

	if (pattern.root == nullptr)
	{
		this->root = nullptr;
		return *this;
	}
	else
		this->root = reinterpret_cast<node*>(this->root->copy(pattern.root));
	return *this;
}


template<typename Type, class Comparable>
bst<Type, Comparable>& struktury::bst<Type, Comparable>::operator=(bst &&pattern)
{
	this->~bst();
	this->root = pattern.root;
	pattern.root = nullptr;
	return *this;
}



template<typename Type, class Comparable>
struktury::bst<Type, Comparable>::~bst()
{
	this->root->destruct();
}


template<typename Type, class Comparable>
void struktury::bst<Type, Comparable>::node::destruct()
{
	if (this == nullptr)
		return;
	if (this->left == nullptr && this->right == nullptr)
	{
		delete this;
		return;
	}
	this->left->destruct();
	this->right->destruct();
	delete this;
}



template<typename Type, class Comparable>
void struktury::bst<Type, Comparable>::insert(Type value)
{
	if (this->isEmpty())
	{
		node *add = new node(value);
		this->root = add;
		return;
	}
	this->root->insert(value);
}


template<typename Type, class Comparable>
bool struktury::bst<Type, Comparable>::remove(Type value)
{
	if (!this->find(value))
		return false;

	node *start = this->root;

	if (start->value == value)
	{
		if (start->left == nullptr && start->right == nullptr)
		{
			delete this->root;
			this->root = nullptr;
		}

		else if (start->right == nullptr)
		{
			node *temp = start;
			start = start->left;
			delete temp;
			root = start;
		}

		else if (start->left == nullptr)
		{
			node *temp = start;
			start = start->right;
			delete temp;
			root = start;
		}

		else
		{
			node *help = start->right;
			if (help->left == nullptr)
			{
				start->value = help->value;
				start->right = start->right->right;
			}
			else
			{
				while (help->left->left != nullptr)
					help = help->left;
				start->value = help->left->value;
				help->left = help->left->right;
			}
		}

		return true;
	}


	return this->root->remove(value);
}



template<typename Type, class Comparable>
bool struktury::bst<Type, Comparable>::find(Type value)
{
	return this->root->find(value);
}


template<typename Type, class Comparable>
bool struktury::bst<Type, Comparable>::isEmpty()
{
	return this->root == nullptr;
}


template<typename Type, class Comparable>
std::ostream& struktury::bst<Type,Comparable>::node::print(std::ostream &output)
{
	if (this == nullptr)
		return output;
	if (this->left == nullptr && this->right == nullptr)
	{
		output << this->value << " ";
		return output;
	}
	this->left->print(output);
	output << this->value << " ";
	this->right->print(output);
	return output;
}




template<typename Type, class Comparable>
struktury::bst<Type, Comparable>::node::node(Type value)
{
	this->value = value;
	this->left = nullptr;
	this->right = nullptr;
}

template<typename Type, class Comparable>
struktury::bst<Type, Comparable>::node::node(const node &pattern)
{
	this->value = pattern.value;
	this->left = nullptr;
	this->right = nullptr;
}

template<typename Type, class Comparable>
struktury::bst<Type, Comparable>::node::~node()
{
	this->left = this->right = nullptr;
}

template<typename Type, class Comparable>
void struktury::bst<Type, Comparable>::node::insert(Type value)
{
	Comparable compare;
	if (!compare(this->value, value))
	{
		if (this->left == nullptr)
		{
			node *add = new node(value);
			this->left = add;
			return;
		}
		this->left->insert(value);
	}
	else
	{
		if (this->right == nullptr)
		{
			node *add = new node(value);
			this->right = add;
			return;
		}
		this->right->insert(value);
	}
}


template<typename Type, class Comparable>
bool struktury::bst<Type, Comparable>::node::remove(Type value)
{
	if (this == nullptr)
		return false;
	if (this->left == nullptr && this->right == nullptr)
		return false;
	Comparable compare;
	std::greater_equal<Type> compg;
	if (this->left != nullptr && compare(this->left->value, value) && compg(this->left->value, value))
	{
		if (this->left->left == nullptr && this->left->right == nullptr)
		{
			delete this->left;
			this->left = nullptr;
		}

		else if (this->left->right == nullptr)
		{
			node *temp = this->left;
			this->left = this->left->left;
			delete temp;
		}

		else if (this->left->left == nullptr)
		{
			node *temp = this->left;
			this->left = this->left->right;
			delete temp;
		}

		else
		{
			node *help = this->left->right;
			if (help->left == nullptr)
			{
				this->left->value = help->value;
				this->left->right = this->left->right->right;
			}
			else
			{
				while (help->left->left != nullptr)
					help = help->left;
				this->left->value = help->left->value;
				help->left = help->left->right;
			}
		}
		return true;
	}


	else if (this->right != nullptr && compare(this->right->value, value) && compg(this->right->value, value))
	{
		if (this->right->left == nullptr && this->right->right == nullptr)
		{
			delete this->right;
			this->right = nullptr;
		}

		else if (this->right->right == nullptr)
		{
			node *temp = this->right;
			this->right = this->right->left;
			delete temp;
		}

		else if (this->right->left == nullptr)
		{
			node *temp = this->right;
			this->right = this->right->right;
			delete temp;
		}

		else
		{
			node *help = this->right->right;
			if (help->left == nullptr)
			{
				this->right->value = help->value;
				this->right->right = this->right->right->right;
			}
			else
			{
				while (help->left->left != nullptr)
					help = help->left;
				this->right->value = help->left->value;
				help->left = help->left->right;
			}
		}
		return true;
	}

	else if (compare(this->value, value))
		return this->right->remove(value);
	else
		return this->left->remove(value);
}


template<typename Type, class Comparable>
bool struktury::bst<Type, Comparable>::node::find(Type value)
{
	Comparable compare;
	std::greater_equal<Type> compg;
	if (compare(this->value, value) && compg(this->value, value))
		return true;
	else if (compare(this->value, value))
		if (this->right == nullptr)
			return false;
		else
			return this->right->find(value);
	else
		if (this->left == nullptr)
			return false;
		else
			return this->left->find(value);
}