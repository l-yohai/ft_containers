#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "List.hpp"

namespace ft
{

template <class T, class Container = List<T> >
class Queue
{
private:
	container_type _ctnr;

public:
	typedef T value_type;
	typedef Container container_type;
	typedef size_t size_type;

public:

	explicit queue (const container_type& ctnr = container_type())
	{
		this->_ctnr = ctnr;
	}

	value_type& back()
	{
		return (this->_ctnr.back());
	}

	const value_type& back() const
	{
		return (this->_ctnr.back());
	}

	// template <class... Args>
	// void emplace (Args&&... args);

	bool empty() const
	{
		return (this->_ctnr.empty());
	}

	value_type& front()
	{
		return (this->_ctnr.front());
	}

	const value_type& front() const
	{
		return (this->_ctnr.front());
	}

	void pop()
	{
		this->_ctnr.pop_front();
	}

	void push (const value_type& val)
	{
		this->_ctnr.push_back();
	}

	size_type size() const
	{
		return (this->_ctnr.size());
	}

	// void swap (queue& x) noexcept(/*see below*/);

	template <class T, class Container>
	bool operator==(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._ctnr == rhs.ctnr);
	}

	template <class T, class Container>
	bool operator!=(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._ctnr != rhs.ctnr);
	}

	template <class T, class Container>
	bool operator<(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._ctnr < rhs.ctnr);
	}

	template <class T, class Container>
	bool operator<=(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._ctnr <= rhs.ctnr);
	}

	template <class T, class Container>
	bool operator> (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._ctnr > rhs.ctnr);
	}

	template <class T, class Container>
	bool operator>=(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._ctnr >= rhs.ctnr);
	}

	// template <class T, class Container>
	// void swap(queue<T,Container>& x, queue<T,Container>& y) noexcept(noexcept(x.swap(y)));

	// template <class T, class Container, class Alloc>
	// struct uses_allocator<queue<T,Container>,Alloc>;
};

}

#endif