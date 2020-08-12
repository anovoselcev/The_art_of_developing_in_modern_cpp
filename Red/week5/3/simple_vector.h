#pragma once

#include <algorithm>
using namespace std;

template <typename T>
class SimpleVector {
public:
	SimpleVector() = default;
	explicit SimpleVector(size_t size);
	~SimpleVector();
	SimpleVector(const SimpleVector<T>& other):
		data(new T[other.capacity]),
		size(other.size),
		capacity(other.capacity)
	{
		copy(other.begin(), other.end(), begin());
	}

	T& operator[](size_t index);

	T* begin();
	const T* begin() const;
	T* end();
	const T* end() const;

	size_t Size() const;
	size_t Capacity() const;
	void PushBack(const T& value);

	void operator=(const SimpleVector& rhs) {
		if (rhs.size <= capacity) {
			copy(rhs.begin(), rhs.end(), begin());
			size = rhs.size;
		}
		else {
			SimpleVector<T> tmp(rhs);
			swap(tmp.data, data);
			swap(tmp.size, size);
			swap(tmp.capacity, capacity);
		}
	}
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;
};

template <typename T>
SimpleVector<T>::SimpleVector(size_t size)
	: data(new T[size])
	, size(size)
	, capacity(size)
{
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
	delete[] data;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
	return data[index];
}

template <typename T>
size_t SimpleVector<T>::Size() const {
	return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
	return capacity;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
	if (size >= capacity) {
		auto new_cap = capacity == 0 ? 1 : 2 * capacity;
		auto new_data = new T[new_cap];
		copy(begin(), end(), new_data);
		delete[] data;
		data = new_data;
		capacity = new_cap;
	}
	data[size++] = value;
}

template <typename T>
T* SimpleVector<T>::begin() {
	return data;
}

template <typename T>
const T* SimpleVector<T>::begin() const {
	return data;
}

template <typename T>
T* SimpleVector<T>::end() {
	return data + size;
}

template <typename T>
const T* SimpleVector<T>::end() const {
	return data + size;
}
