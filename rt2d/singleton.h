/**
 * @file singleton.h
 *
 * @brief The Singleton header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef SINGLETON_H
#define SINGLETON_H

/// @brief a template class to create a Singleton
template<class T>
class Singleton {
public:
	/// @brief a pointer to the instance
	static T* instance();
	/// @brief destroy the instance
	static void destroy();

private:
	/// @brief constructor
	Singleton() {
		Singleton::_instance = static_cast<T*>(this);
	}
	/// @brief destructor
	~Singleton() {
		Singleton::destroy();
	}

	/// @brief overloaded copy constructor (no implementation)
	Singleton(Singleton const&);
	/// @brief overloaded operator= (no implementation)
	Singleton& operator=(Singleton const&);

	/// @brief the instance itself
	static T* _instance;
};

// ========================== implementation ==========================
template<class T>
T* Singleton<T>::instance() {
	if ( Singleton::_instance == 0 ) {
		Singleton::_instance = new T();
		std::atexit(Singleton::destroy);
	}
	return Singleton::_instance;
}

template<class T>
void Singleton<T>::destroy() {
	if ( Singleton::_instance != 0 ) {
		delete Singleton::_instance;
		Singleton::_instance = 0;
	}
}

template<class T>
T* Singleton<T>::_instance = 0;

#endif /* SINGLETON_H */
