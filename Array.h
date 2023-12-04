#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>

//数组类模板定义
template <class T>
class Array {
private:
	T* list;//存放动态分配的数组内存首地址
	int size; //数组大小
public:
	Array(int sz = 50); //构造函数
	Array(const Array<T>& a); //复制构造函数
	~Array(); //析构函数
	Array<T>& operator = (const Array<T>& rhs); //重载=
	T& operator[] (int i); //重载[];
	const T& operator[] (int i) const; //const []
	operator T* (); //重载（）类型转换用
	operator const T* () const; //const ();
	int getSize() const; //获取大小
	void resize(int sz); //修改大小
};

//构造函数
template <class T>
Array<T>::Array(int sz) {
	assert(sz >= 0); //断言数组大小非负
	size = sz; //将元素个数赋给size
	list = new T[size]; //动态分配空间
}

//析构函数
template <class T>
Array<T>::~Array() {
	delete[] list;
}

//复制构造函数
template <class T>
Array<T>::Array(const Array<T>& a) {
	size = a.size; //复制大小
	list = new T[size]; //分配空间
	for (int i = 0; i < size; i++)
		list[i] = a.list[i]; //复制元素
}

//重载=
template <class T>
Array<T>& Array<T>::operator= (const Array<T>& rhs) {
	if (&rhs != this){
		//如果本对象中数组大小与rhs不同，则删除数组原有内存，然后重新分配
		if (size != rhs.szie) {
			delete[] list;
			size = rhs.size;
			list = new T[size];
		}
		//复制元素
		for (int i = 0; i < size; i++)
			list[i] = rhs.list[i];
	}
	return *this; //返回当前对象引用
}

//重载[] ，越界检查
template <class T>
T& Array<T>::operator[] (int n){
	assert(n >= 0 && n < size); //断言越界
	return list[n];
}

//const []
template <class T>
const T& Array<T>::operator[] (int n) const {
	assert(n >= 0 && n < size); //断言越界
	return list[n];
}

//重载 *
template <class T>
Array<T>::operator T* () {
	return list; //返回当前对象数组首地址
}

//const *
template <class T>
Array<T>::operator const T* () const {
	return list; //返回当前对象数组首地址
}

//获取大小
template <class T>
int Array<T>::getSize() const {
	return size;
}

//将数组大小修改为sz
template<class T>
void Array<T>::resize(int sz) {
	assert(sz >= 0); //断言sz非负
	if (sz == size)
		return;
	T* newList = new T[sz]; //申请新空间
	int n = (sz < size) ? sz : size;
	
	for (int i = 0; i < n; i++)//复制元素
		newList[i] = list[i];
	delete[] list; //删除原数组
	list = newList;
	size = sz;
}

#endif // !ARRAY_H
