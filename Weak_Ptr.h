#pragma once
#include "Shared_Ptr.h"
template <typename Resource>
class WeakPtr
{
private:
	SharedPtr<Resource>* sharedPtr;
public:
	WeakPtr();

	// Construct from another weak_ptr
	WeakPtr(const WeakPtr<Resource>& rhs);

	// Construct from a shared_ptr
	WeakPtr(const SharedPtr<Resource>& rhs);


	WeakPtr<Resource>& operator=(const WeakPtr<Resource>& rhs);


	WeakPtr<Resource>& operator=(const SharedPtr<Resource>& rhs);


	~WeakPtr() = default; // No need to release, because sharedPtr is being managed by SharedPtr

	// Resets the weak_ptr to null
	void Reset();

	// Swaps this weak_ptr with another
	void Swap(WeakPtr<Resource>& rhs);

	// Returns the use count of the controlled resource
	long UseCount() const;

	// Checks whether the controlled resource has already been deleted
	bool Expired() const;

	// Attempts to obtain a shared_ptr that manages the controlled resource
	SharedPtr<Resource> Lock() const;
};

template <typename Resource>
WeakPtr<Resource>::WeakPtr() : sharedPtr(nullptr) {}

template <typename Resource>
WeakPtr<Resource>::WeakPtr(const WeakPtr<Resource>& rhs) : sharedPtr(rhs.sharedPtr) {}


template <typename Resource>
WeakPtr<Resource>::WeakPtr(const SharedPtr<Resource>& rhs)
	: sharedPtr(const_cast<SharedPtr<Resource>*>(&rhs)) {} // because sharedPtr is non-const

template <typename Resource>
WeakPtr<Resource>& WeakPtr<Resource>::operator=(const WeakPtr<Resource>& rhs) {
	sharedPtr = rhs.sharedPtr;
	return *this;
}

template <typename Resource>
WeakPtr<Resource>& WeakPtr<Resource>::operator=(const SharedPtr<Resource>& rhs) {
	sharedPtr = const_cast<SharedPtr<Resource>*>(&rhs); // because sharedPtr is non-const 
	return *this;
}

template <typename Resource>
void WeakPtr<Resource>::Reset() { sharedPtr = nullptr; }

template <typename Resource>
void WeakPtr<Resource>::Swap(WeakPtr<Resource>& rhs) { std::swap(sharedPtr, rhs.sharedPtr); }

template <typename Resource>
long WeakPtr<Resource>::UseCount() const { return sharedPtr ? sharedPtr->UseCount() : 0; }

template <typename Resource>
bool WeakPtr<Resource>::Expired() const { return UseCount() == 0; }

template <typename Resource>
SharedPtr<Resource> WeakPtr<Resource>::Lock() const {
	return Expired() ? SharedPtr<Resource>() : *sharedPtr;
}