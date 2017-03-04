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
    static T* Instance();
    /// @brief destroy the instance
    static void Destroy();

protected:
	/// @brief constructor
    Singleton() {
        assert(Singleton::_instance == 0);
        Singleton::_instance = static_cast<T*>(this);
    }
    /// @brief destructor
    ~Singleton() {
        Singleton::_instance = 0;
    }

private:
	/// @brief create an instance (only once)
    static T* CreateInstance();
    /// @brief schedule for destruction
    static void ScheduleForDestruction(void (*)());
    /// @brief destroy the instance
    static void DestroyInstance(T*);

	/// @brief the instance itself
    static T* _instance;

	/// @brief constructor overloader
    Singleton(Singleton const&) {}
    /// @brief operator= overloader
    Singleton& operator=(Singleton const&) { return *this; }
};

// ========================== implementation ==========================

template<class T>
T* Singleton<T>::Instance() {
    if ( Singleton::_instance == 0 ) {
        Singleton::_instance = CreateInstance();
        ScheduleForDestruction(Singleton::Destroy);
    }
    return Singleton::_instance;
}

template<class T>
void Singleton<T>::Destroy() {
    if ( Singleton::_instance != 0 ) {
        DestroyInstance(Singleton::_instance);
        Singleton::_instance = 0;
    }
}

template<class T>
inline T* Singleton<T>::CreateInstance() {
    return new T();
}

template<class T>
inline void Singleton<T>::ScheduleForDestruction(void (*pFun)()) {
    std::atexit(pFun);
}

template<class T>
inline void Singleton<T>::DestroyInstance(T* p) {
    delete p;
}

template<class T>
T* Singleton<T>::_instance = 0;

#endif /* SINGLETON_H */
