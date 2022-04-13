#pragma once

#include <iterator>
#include <stdexcept>
#include <memory>

template <class T>
class vector;

template<class T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs)
{
	if (lhs.size() == rhs.size())
	{
		for (size_t i = 0; i < lhs.size(); ++i)
		{
			if (lhs[i] != rhs[i])
			{
				return false;
			}
		}
		return lhs.capacity() == rhs.capacity();
	}
	return false;
}

//TODO: impl others operators

template <class T> //add class Allocator = std::allocator<T>
class vector
{
public:
	class iterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using difference_type = ptrdiff_t;

		iterator(pointer p)
			: _ptr(p)
		{}

		iterator& operator+=(size_t pos)
		{
			this->_ptr += pos;
			return *this;
		}
		iterator& operator+(size_t pos)
		{
			this->_ptr += pos;
			return *this;
		}
		iterator operator++()
		{
			iterator p = *this;
			++this->_ptr;
			return p;
		}
		iterator& operator++(int junk)
		{
			++this->_ptr;
			return *this;
		}
		iterator& operator-=(size_t pos)
		{
			this->_ptr -= pos;
			return *this;
		}
		iterator& operator-(size_t pos)
		{
			this->_ptr -= pos;
			return *this;
		}
		iterator operator--()
		{
			iterator p = *this;
			--this->_ptr;
			return p;
		}
		iterator& operator--(int junk)
		{
			--this->_ptr;
			return *this;
		}
		reference operator*() const
		{
			return *this->_ptr;
		}
		pointer operator->() const
		{
			return this->_ptr;
		}
		bool operator==(const iterator& other) const
		{
			return this->_ptr == other._ptr;
		}
		bool operator!=(const iterator& other) const
		{
			return !(*this == other);
		}
		bool operator<(const iterator& other) const
		{
			return this->_ptr < other._ptr;
		}
		bool operator>(const iterator& other) const
		{
			return this->_ptr > other._ptr;
		}
		bool operator<=(const iterator& other) const
		{
			return !(*this > other);
		}
		bool operator>=(const iterator& other) const
		{
			return !(*this < other);
		}
		pointer Ptr() const
		{
			return _ptr;
		}
	private:
		pointer _ptr;
	};

	class const_iterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;
		using difference_type = ptrdiff_t;

		const_iterator(pointer p)
			: _ptr(p)
		{}

		const_iterator(const iterator& It)
			: _ptr(It.operator->())
		{
		}

		const_iterator& operator+=(size_t pos)
		{
			this->_ptr += pos;
			return *this;
		}
		const_iterator& operator+(size_t pos)
		{
			this->_ptr += pos;
			return *this;
		}
		const_iterator operator++()
		{
			const_iterator p = *this;
			++this->_ptr;
			return p;
		}
		const_iterator& operator++(int junk)
		{
			++this->_ptr;
			return *this;
		}
		const_iterator& operator-=(size_t pos)
		{
			this->_ptr -= pos;
			return *this;
		}
		const_iterator& operator-(size_t pos)
		{
			this->_ptr -= pos;
			return *this;
		}
		const_iterator operator--()
		{
			const_iterator p = *this;
			--this->_ptr;

		}
		const_iterator& operator--(int junk)
		{
			--this->_ptr;
			return *this;
		}
		const reference operator*() const
		{
			return *this->_ptr;
		}
		const pointer operator->() const
		{
			return this->_ptr;
		}
		bool operator==(const const_iterator& other) const
		{
			return this->_ptr == other._ptr;
		}
		bool operator!=(const const_iterator& other) const
		{
			return !(*this == other);
		}
		bool operator<(const const_iterator& other) const
		{
			return this->_ptr < other._ptr;
		}
		bool operator>(const const_iterator& other) const
		{
			return this->_ptr > other._ptr;
		}
		bool operator<=(const const_iterator& other) const
		{
			return !(*this > other);
		}
		bool operator>=(const const_iterator& other) const
		{
			return !(*this < other);
		}
		pointer Ptr() const
		{
			return _ptr;
		}
	private:
		pointer _ptr;
	};
public:
	//Constructors
	vector()
		: _data(nullptr)
		, _size(0), _capacity(0)
	{}

	explicit vector(size_t size)
		: _data(std::make_unique<T[]>(size + size / 2))
		, _size(size), _capacity(size + size / 2)
	{}

	vector(size_t size, const T& by_def)
		: _data(std::make_unique<T[]>(size + size / 2))
		, _size(size), _capacity(size + size / 2)
	{
		std::fill(begin(), end(), by_def);
	}

	vector(const vector& other)
		: vector(other.size())
	{
		std::memcpy(other._data.get(), _data.get(), sizeof(T) * _size);
	}

	vector(vector&& other) noexcept
		: _data(other._data.get())
		, _size(other._size), _capacity(other._capacity)
	{
		other._data.release();
		other._size = 0;
		other._capacity = 0;
	}

	template <class InputIt>
	vector(InputIt first, InputIt last)
		: _data(nullptr)
		, _size(0), _capacity(0)
	{
		ptrdiff_t dist = std::distance(first, last);
		
		_data = std::make_unique<T[]>(dist);

		for (; first != last; ++first)
		{
			emplace_back(*first);
		}
	}

	template <class _Ty> 
	vector(const std::initializer_list<_Ty>& list)
		: _data(new T[list.size() + list.size() / 2])
		, _size(list.size()), _capacity(list.size() + list.size() / 2)
	{
		std::copy(list.begin(), list.end(), begin());
	}

	vector<T>& operator=(const vector& other)
	{
		if (other != *this)
		{
			_size = other._size;
			_capacity = other._capacity;
			_data.reset(new T[other._size]);
			std::memcpy(_data.get(), other._data.get(), sizeof(T) * other._size);
		}
		return *this;
	}

	vector<T>& operator=(vector&& other) noexcept
	{
		_data.reset(other._data.get());
		_size = other._size;
		_capacity = other._capacity;

		other._data.release();
		other._size = 0;
		other._capacity = 0;

		return *this;
	}

	//Element access
	T& at(size_t pos)
	{
		if (pos >= _size)
		{
			throw std::out_of_range("out of range.");
		}
		return _data[pos];
	}
	const T& at(size_t pos) const
	{
		if (pos >= _size)
		{
			throw std::out_of_range("out of range.");
		}
		return _data[pos];
	}

	T& operator[](size_t pos)
	{
		return _data[pos];
	}

	const T& operator[](size_t pos) const
	{
		return _data[pos];
	}

	T& front()
	{
		return *begin();
	}
	const T& front() const
	{
		return *cbegin();
	}

	T& back()
	{
		return *std::prev(end());
	}
	const T& back() const
	{
		return *std::prev(cend());
	}
	T* data()
	{
		return _data.get();
	}
	const T* data() const
	{
		return _data.get();
	}

	//Iterators
	iterator begin()
	{
		return iterator(_data.get());
	}
	iterator end()
	{
		return iterator(_data.get() + _size);
	}
	//iterator rbegin();
	//iterator rend();
	const_iterator cbegin() const
	{
		return const_iterator(_data.get());
	}
	const_iterator cend() const
	{
		return const_iterator(_data.get() + _size);
	}
	//const_iterator crbegin() const;
	//const_iterator crend() const;

	//Capacity
	bool empty() const
	{
		return _size == 0;
	}
	size_t size() const
	{
		return _size;
	}

	void reserve(size_t size)
	{
		if (_capacity <= size)
		{
			T* temp = new T[size]();
			if (_data.get() != nullptr)
			std::memcpy(temp, _data.get(), sizeof(T) * _size); //sizeof(what???)

			_data.reset(temp);
			_capacity = size;
		}
	}
	size_t capacity() const
	{
		return _capacity;
	}
	void shrink_to_fit()
	{
		if (_size != _capacity)
		{
			T* temp = new T[_size];
			std::memcpy(temp, _data.get(), sizeof(T) * _size);

			_data.reset(temp);
			_capacity = _size;
		}
	}

	//Modifiers
	void clear()
	{}
	//insert() and emplace() dunno how to impl
	//void erase(iterator first, iterator last);
	void push_back(const T& val)
	{
		if (_size >= _capacity)
		{
			reserve(_capacity + 5);
		}
			
		_data.get()[_size] = val;
		++_size;
	}
	template <class ...Args>
	void emplace_back(Args&&... args)
	{

	}

	void pop_back()
	{
		--_size;
	}
	void resize(size_t size)
	{
		if (size != _size)
		{
			size_t max_size = _size > size ? _size : size;
			T* temp = new T[size];
			std::memcpy(temp, _data.get(), sizeo(T) * _size);

			_data.reset(temp);
			_size = max_size;
			_capacity = _capacity > max_size ? _capacity : max_size;
		}
	}
private:
	std::unique_ptr<T[]> _data;
	size_t _size;
	size_t _capacity;
};

