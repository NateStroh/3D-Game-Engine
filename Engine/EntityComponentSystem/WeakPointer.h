#pragma once

#include "SmartPointer.h"

struct Counters;
template <typename T> class SmartPointer;

template <typename T>
class WeakPointer {
private:
	T* m_ptr;
	Counters* m_count;
public:
	WeakPointer<T>(const SmartPointer<T>& i_other);

	WeakPointer<T>(const WeakPointer<T>& i_other);

	SmartPointer<T> CreateSmartPointer();

	operator bool();

	void operator=(const WeakPointer<T>& i_other);

	~WeakPointer();

	friend class SmartPointer<T>;

};

template <typename T>
WeakPointer<T>::WeakPointer(const SmartPointer<T>& i_other) :
	m_ptr(i_other.m_ptr),
	m_count(i_other.m_count)
{
	(*m_count).m_observers++;
}

template <typename T>
WeakPointer<T>::WeakPointer(const WeakPointer<T>& i_other) :
	m_ptr(i_other.m_ptr),
	m_count(i_other.m_count)
{
	(*m_count).m_observers++;
}

template <typename T>
SmartPointer<T> WeakPointer<T>::CreateSmartPointer() {
	if ((*m_count).m_owners > 0) {
		return SmartPointer<T>(*this);
	}
	else {
		return SmartPointer<T>(nullptr);
	}
}

template <typename T>
WeakPointer<T>::operator bool() {
	return m_ptr != nullptr;
}

template<typename T>
void WeakPointer<T>::operator=(const WeakPointer<T>& i_other) {
	(*m_count).m_observers--;

	if (((*m_count).m_observers <= 0) && ((*m_count).m_owners <= 0)) {
		delete m_count;
	}

	m_ptr = i_other.m_ptr;
	m_count = i_other.m_count;
	(*m_count).m_observers++;
}

template <typename T>
WeakPointer<T>::~WeakPointer() {
	(*m_count).m_observers--;

	if (((*m_count).m_observers <= 0) && ((*m_count).m_owners <= 0)) {
		delete m_count;
	}
}
