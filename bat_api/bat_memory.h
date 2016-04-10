#ifndef _BAT_MEMORY_H_
#define _BAT_MEMORY_H_

#include "bat_platform.h"

template <typename T>
void DELETE(T* obj) { delete obj; obj = nullptr; }
template <typename T>
void DELETE_ARR(T* arr) { delete[] arr; arr = nullptr; }
template <typename T>
void RELEASE(T* obj) { obj->Release(); delete obj; obj = nullptr; }

#endif