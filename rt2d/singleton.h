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

#include <cstdlib>

/// @brief a template class to create a Singleton
template<class T>
class Singleton {
public:
    /// @brief a pointer to the instance
    static T* instance();
    /// @brief destroy the instance
    static void destroy();

protected:
	/// @brief constructor
    Singleton() {
        assert(Singleton::_instance == 0);
        Singleton::_instance = static_cast<T*>(this);
    }
    /// @brief destructor
    ~Singleton() {
        Singleton::destroy();
    }

private:
    /// @brief schedule for destruction
    static void scheduleForDestruction(void (*)());

	/// @brief the instance itself
    static T* _instance;

	/// @brief overloaded copy constructor
    Singleton(Singleton const&) {}
    /// @brief overloaded operator=
    Singleton& operator=(Singleton const&) { return *this; }
};

// ========================== implementation ==========================

template<class T>
T* Singleton<T>::instance() {
    if ( Singleton::_instance == 0 ) {
        Singleton::_instance = new T();
        scheduleForDestruction(Singleton::destroy);
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
inline void Singleton<T>::scheduleForDestruction(void (*pFun)()) {
    std::atexit(pFun);
}

template<class T>
T* Singleton<T>::_instance = 0;

#endif /* SINGLETON_H */
