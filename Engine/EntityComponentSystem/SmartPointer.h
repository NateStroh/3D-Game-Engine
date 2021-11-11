#pragma once

#include <cassert>

#include "WeakPointer.h"

struct Counters {
	unsigned long m_owners;
	unsigned long m_observers;

	Counters(unsigned long i_owners, unsigned long i_observers) :
		m_owners(i_owners),
		m_observers(i_observers)
	{ }
};

template <typename T> class WeakPointer;

template <typename T>
class SmartPointer {
private:
	T* m_ptr;
	Counters* m_count;
public:
	SmartPointer<T>();

	SmartPointer<T>(T* i_pGameObject);

	SmartPointer<T>(const SmartPointer<T>& i_other);

	SmartPointer<T>(const WeakPointer<T>& i_other);

	operator bool();

	bool operator==(SmartPointer<T>* i_other);

	bool operator==(WeakPointer<T>* i_other);
	
	void operator=(const SmartPointer<T> &i_other);

	T* operator->();

	T& operator*();

	~SmartPointer();

	friend class WeakPointer<T>;
};

template <typename T>
SmartPointer<T>::SmartPointer() :
	m_ptr(nullptr),
	m_count(new Counters(1, 0))
{ }

template <typename T>
SmartPointer<T>::SmartPointer(T* i_pObject) :
	m_ptr(i_pObject),
	m_count(new Counters(1, 0))
{ }

template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer& i_other) {
	m_ptr = i_other.m_ptr;
	m_count = i_other.m_count;
	(*m_count).m_owners++;
}

template <typename T>
SmartPointer<T>::SmartPointer(const WeakPointer<T>& i_other) :
	m_ptr(i_other.m_ptr),
	m_count(i_other.m_count)
{
	(*m_count).m_owners++;
}

template <typename T>
SmartPointer<T>::operator bool() {
	return m_count->m_owners > 0;
}

template <typename T>
bool SmartPointer<T>::operator==(SmartPointer* i_other) {
	return m_ptr == i_other->m_ptr;
}

template <typename T>
bool SmartPointer<T>::operator==(WeakPointer<T>* i_other)
{
	return m_ptr == i_other->m_ptr;
}

template<typename T>
void SmartPointer<T>::operator=(const SmartPointer<T>& i_other)
{	
	if (--(*m_count).m_owners <= 0) {
		if (m_ptr != nullptr) {
			delete m_ptr;
		}
		if ((*m_count).m_observers <= 0) {
			delete m_count;
		}
	}
	
	m_ptr = i_other.m_ptr;
	m_count = i_other.m_count;
	(*m_count).m_owners++;
}

template <typename T>
T* SmartPointer<T>::operator->() {
	return m_ptr;
}

template <typename T>
T& SmartPointer<T>::operator*() {
	assert(m_ptr);
	return *m_ptr;
}

template <typename T>
SmartPointer<T>::~SmartPointer() {
	if (--(*m_count).m_owners <= 0) {
		if (m_ptr != nullptr) {
			delete m_ptr;
		}
		if ((*m_count).m_observers <= 0) {
			delete m_count;
		}
	}
}
