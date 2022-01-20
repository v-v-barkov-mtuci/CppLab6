module;
#include <memory>
export module Containers:IStackDyn;
import :DynamicArray;

namespace Containers {
	export template<class T> class IStack {
	private:
		//T top;
		size_t capacity;
		DynamicArray<T>* stack;
	public:
		IStack() :capacity(0) {
			stack = new DynamicArray<T>;
		}
		IStack(size_t size) :capacity(size) {
			stack = new DynamicArray<T>;
		}

		bool Pop() {
			if (isEmpty())
			{
				return false;
			}
			stack->PopFront();
			return true;
		}
		bool Push(T value) {
			if (isFull())
			{
				return false;
			}
			stack->PushFront(value);
			return true;
		}
		bool isFull() {
			if (stack->GetSize() == capacity) {
				return true;
			}
			else return false;
		}
		bool isEmpty() {
			if (capacity == 0) {
				return true;
			}
			else return false;
		}
		T Peek() {
			return stack->GetFront();
		}
		size_t Size() {
			return capacity;
		}
	};
	export template<class T>
		IStack<T> CreateStack(size_t size) {
		IStack<T> tempStack(size);

		return tempStack;
	}
	export template<class T>
		IStack<T> CreateStack() {
		IStack<T> tempStack();

		return tempStack;
	}
}