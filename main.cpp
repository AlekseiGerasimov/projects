//--------------------------------------------------------------------------
//! file Stack.cpp
//! Класс стэк
//! Автор Герасимов А.А.
//!
//! Public:
//! Метод capacity() выводит максимальное количество членов стэка
//! Метод size() выводит текущее количество элементов в стэке
//! Метод empty() возвращает пустой массив или нет
//! Метод top() выводит верхнее значение элемента стэка
//! Метод push() вводит новое значение в стэк
//! Метод pop() удаляет верхнее значение стэка
//! Метод getelement() возвращает значение конкретного элемента стэка
//! Метод print() печатает весь стэк
//!
//! Private:
//! Поле *stk является указателем на начало стэка
//! Поле maxsize хранит максимальное количество элементов в стэке
//! Поле cursize хранит текущее количество элементов в стэке
//! Метод stk_crowded() тихий верификатор
//! Метод dump() выводится в случае ошибки и выводит информацию по ней
//--------------------------------------------------------------------------

#include <iostream>
#include <assert.h>

using namespace std;
typedef float stacktype;
const size_t default_value = 10;

/*******************************************************************************/

#define assert_ok_empty() 													\
		if(empty()){														\
		dump();             												\
		assert(!"Object is OK");					\
		}								

#define assert_ok_crowded() 												\
		if(stk_crowded()){													\
		dump();             												\											
		assert(!"Object is OK");				\
		}

/*******************************************************************************/

#define TEST(what,case) 

/*******************************************************************************/

class Stack{
	public:
		Stack();
		Stack(size_t);
		
		size_t capacity() const;  
		size_t size() const;
		bool empty() const;
		
		stacktype top() const;	
		bool push(const stacktype);
		void pop();
		stacktype getelement(const size_t) const;
		void print() const;
		virtual ~Stack();
	private:
		stacktype *stk;
		const size_t maxsize;	
		size_t cursize;
		bool stk_crowded() const;
		void dump() const;
};

/*******************************************************************************/

Stack::Stack() : maxsize(default_value),cursize(0){
	stk = new stacktype[maxsize];
	if(!stk) assert(!"Memory error. Cant reserve memory for new object.");
	for(int i=0;i<maxsize;i++)
		stk[i] = 1.0/0.0;
}

Stack::Stack(size_t size) : maxsize(size),cursize(0){
	stk = new stacktype[maxsize];
	if(!stk) assert(!"Memory error. Cant reserve memory for new object.");
	for(int i=0;i<maxsize;i++)
		stk[i] = 1.0/0.0;
}

/*******************************************************************************/

size_t Stack::capacity() const{
	return maxsize;
}

size_t Stack::size() const{
	return cursize;
}

bool Stack::empty() const{
	if(cursize==0) return true;
	return false;
}

bool Stack::push(const stacktype data){
	assert_ok_crowded();
	stk[cursize++] = data;
}

stacktype Stack::top() const{
	if(cursize==0) return 1.0/0.0;
	return stk[cursize-1];
}

void Stack::pop(){
	assert_ok_empty();
	stk[--cursize] = 1.0/0.0;
}

stacktype Stack::getelement(const size_t number) const{
	if(number>=maxsize) assert(!"You can't get this element. A number of element isn't valid.Check the maxsize of stack.");
	return stk[number];
}

void Stack::print() const{
	cout << "maxsize: " << maxsize << endl;
	cout << "cursize: " << cursize << endl;
	for(int i=cursize;i>=0;--i)
		cout << "stk[" << i << "]=" << stk[i] << endl;
}

/*******************************************************************************/

bool Stack::stk_crowded() const{
	if(cursize>=maxsize) return true;
	return false;	
}


void Stack::dump() const{
	if(cursize == 0){
	cout << "You cant pop the empty stack" << endl;
	cout << "stc[-1] <- Error" << endl;
	print();
	}
	if(cursize>=maxsize){
	cout << "You cant push a new element. The stack is full" << endl;
	print();
	cout << "stc[" << cursize << "] <- Error" << endl;
	}
}

/*******************************************************************************/

Stack::~Stack(){
	delete []stk;
}

/*******************************************************************************/

// Я не очень понял,как делать тестирование, поэтому может быть полная фигня.
// И вообще тестирование я сделал бы отдельным методом,но я вообще не уверен, что
// то что я сделал является подобием тестирования.

/*******************************************************************************/
int main(int argc, char** argv) {
	TEST(Stack,PopEmptyStack){ //(+)
	Stack s;
	s.pop();	
	}
	TEST(Stack,PushFullStack){ //(+)
	Stack s(8);
	for(int i=0;i<s.capacity();i++)	
		s.push(i);
	s.push(100);
	}
	TEST(Stack,CheckMethods){ //(+)
	Stack s(5);
	cout << s.capacity() << endl;
	cout << s.size() << endl;
	cout << s.empty() << endl;
	}	
	return 0;
}
