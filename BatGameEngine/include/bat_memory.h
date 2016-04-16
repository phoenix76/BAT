#ifndef _BAT_MEMORY_H_
#define _BAT_MEMORY_H_

template <typename T>
void _DELETE(T* obj) { delete obj; obj = nullptr; }
template <typename T>
void _DELETE_ARR(T* arr) { delete[] arr; arr = nullptr; }
template <typename T>
void _RELEASE(T* obj) { obj->Release(); delete obj; obj = nullptr; }

#endif