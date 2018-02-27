#pragma once

#if defined(ROBOTPEN_DLL)
#define ROBOTPEN_API __declspec(dllexport)
#else
#define ROBOTPEN_API __declspec(dllimport)
#endif


template <typename T> static inline T *qGetPtrHelper(T *ptr) { return ptr; }
template <typename Wrapper> static inline typename Wrapper::pointer qGetPtrHelper(const Wrapper &p) { return p.data(); }

#define R_DECLARE_PRIVATE(Class) \
	inline Class##Private* d_func() { return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_ptr)); } \
	inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_ptr)); } \
	friend class Class##Private;

#define Q_DECLARE_PUBLIC(Class)                                    \
	inline Class* q_func() { return static_cast<Class *>(q_ptr); } \
	friend class Class;
	//inline const Class* q_func() const { return static_cast<const Class *>(q_ptr); } 

#define Q_D(Class) Class##Private * const d = d_func()
#define Q_Q(Class) Class * const q = q_func()