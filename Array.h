#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>

//������ģ�嶨��
template <class T>
class Array {
private:
	T* list;//��Ŷ�̬����������ڴ��׵�ַ
	int size; //�����С
public:
	Array(int sz = 50); //���캯��
	Array(const Array<T>& a); //���ƹ��캯��
	~Array(); //��������
	Array<T>& operator = (const Array<T>& rhs); //����=
	T& operator[] (int i); //����[];
	const T& operator[] (int i) const; //const []
	operator T* (); //���أ�������ת����
	operator const T* () const; //const ();
	int getSize() const; //��ȡ��С
	void resize(int sz); //�޸Ĵ�С
};

//���캯��
template <class T>
Array<T>::Array(int sz) {
	assert(sz >= 0); //���������С�Ǹ�
	size = sz; //��Ԫ�ظ�������size
	list = new T[size]; //��̬����ռ�
}

//��������
template <class T>
Array<T>::~Array() {
	delete[] list;
}

//���ƹ��캯��
template <class T>
Array<T>::Array(const Array<T>& a) {
	size = a.size; //���ƴ�С
	list = new T[size]; //����ռ�
	for (int i = 0; i < size; i++)
		list[i] = a.list[i]; //����Ԫ��
}

//����=
template <class T>
Array<T>& Array<T>::operator= (const Array<T>& rhs) {
	if (&rhs != this){
		//����������������С��rhs��ͬ����ɾ������ԭ���ڴ棬Ȼ�����·���
		if (size != rhs.szie) {
			delete[] list;
			size = rhs.size;
			list = new T[size];
		}
		//����Ԫ��
		for (int i = 0; i < size; i++)
			list[i] = rhs.list[i];
	}
	return *this; //���ص�ǰ��������
}

//����[] ��Խ����
template <class T>
T& Array<T>::operator[] (int n){
	assert(n >= 0 && n < size); //����Խ��
	return list[n];
}

//const []
template <class T>
const T& Array<T>::operator[] (int n) const {
	assert(n >= 0 && n < size); //����Խ��
	return list[n];
}

//���� *
template <class T>
Array<T>::operator T* () {
	return list; //���ص�ǰ���������׵�ַ
}

//const *
template <class T>
Array<T>::operator const T* () const {
	return list; //���ص�ǰ���������׵�ַ
}

//��ȡ��С
template <class T>
int Array<T>::getSize() const {
	return size;
}

//�������С�޸�Ϊsz
template<class T>
void Array<T>::resize(int sz) {
	assert(sz >= 0); //����sz�Ǹ�
	if (sz == size)
		return;
	T* newList = new T[sz]; //�����¿ռ�
	int n = (sz < size) ? sz : size;
	
	for (int i = 0; i < n; i++)//����Ԫ��
		newList[i] = list[i];
	delete[] list; //ɾ��ԭ����
	list = newList;
	size = sz;
}

#endif // !ARRAY_H
