#pragma once
#include <utility> // for std::swap
#include <iostream>
template <typename Resource>
class SharedPtr {
private:
	Resource* res;
	long* count;

public:
	SharedPtr();

	explicit SharedPtr(Resource* res);
	
	SharedPtr(const SharedPtr<Resource>& rhs);

	// SharedPtr(const WeakPtr<Resource>& rhs);
	SharedPtr<Resource>& operator=(const SharedPtr<Resource>& rhs);
	~SharedPtr();

	// Resets the shared pointer, deleting the managed object if this was the last owner
	void Reset();

	// Resets the shared pointer with a new object
	void Reset(Resource* res);

	// Swaps the managed object with another shared pointer
	void Swap(SharedPtr<Resource>& rhs);

	// Returns a pointer to the managed object
	Resource* Get() const;

	Resource& operator*() const;
	Resource* operator->() const;

	// Returns the number of shared_ptr objects managing the resource
	long UseCount() const;
};

template <typename Resource>
SharedPtr<Resource>::SharedPtr() : res(nullptr), count(new long{ 0 }) {}

template <typename Resource>
SharedPtr<Resource>::SharedPtr(Resource* res) : res(res), count(new long{ 1 }) {}

template <typename Resource>
SharedPtr<Resource>::SharedPtr(const SharedPtr<Resource>& rhs)
	: res(rhs.res), count(rhs.count)
{
	++(*count);
}

template <typename Resource>
SharedPtr<Resource>& SharedPtr<Resource>::operator=(const SharedPtr<Resource>& rhs) {
	if (this != &rhs) 
	{
		if (this->res) // Check if there is a resource
		{
			--(*count);
			if ((*count) == 0)
			{
				delete res;
				delete count;
			}
		}

		res = rhs.res;
		count = rhs.count;
		++(*count);
	}
	return *this;
}
template <typename Resource>
SharedPtr<Resource>::~SharedPtr() { 
	if (this->res)
	{
		--(*count);
		if ((*count) == 0)
		{
			delete res;
			delete count;
		}
	}
}

template <typename Resource>
void SharedPtr<Resource>::Reset() {
	if (this->res) { // Check if there is a resource
		--(*count);
		if ((*count) == 0)
		{
			delete res;
			delete count;
		}
	}
	res = nullptr;
	count = new long(0);
}

template <typename Resource>
void SharedPtr<Resource>::Reset(Resource* res) {
	if (this->res) { // Check if there is a resource
		--(*count);
		if ((*count) == 0)
		{
			delete this->res;
			delete count;
		}
	}
	if (res) // if another object is valid then
	{
		this->res = res;
		count = new long(1);
	}
	else
	{
		this->res = nullptr;
		count = new long(0);
	}
}

template <typename Resource>
void SharedPtr<Resource>::Swap(SharedPtr<Resource>& rhs) {
	std::swap(res, rhs.res);
	std::swap(count, rhs.count);
}

template <typename Resource>
Resource* SharedPtr<Resource>::Get() const { return res; }

template <typename Resource>
Resource& SharedPtr<Resource>::operator*() const { return *res; }

template <typename Resource>
Resource* SharedPtr<Resource>::operator->() const { return res; }

template <typename Resource>
long SharedPtr<Resource>::UseCount() const { return *count; }