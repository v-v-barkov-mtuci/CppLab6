module;
#include <memory>
export module Containers:IStack;
import :ForwardList;

namespace Containers {
	export template<class T> class IStack {
	public:
		size_t capacity;
		ForwardList<T>* stack;
		IStack() :capacity(0) {
			stack = new ForwardList<T>;
		}
		IStack(size_t size):capacity(size){
			stack = new ForwardList<T>;
		}
		
		bool Pop() {
			if (IsEmpty())
			{
				return false;
			}
			stack->PopFront();
			return true;
		}
		bool Push(T value) {
			if (IsFull())
			{
				return false;
			}
			stack->PushFront(value);
			return true;
		}
		bool IsFull() {
			if (stack->GetSize() == capacity) {
				return true;
			}
			else return false;
		}
		bool IsEmpty() {
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
	/*export template<class T> std::unique_ptr<IStack<T>> CreateStack(size_t size) {
		std::unique_ptr<IStack<T>> tempStack(size);

		return tempStack;
	}
	export template<class T> std::unique_ptr<IStack<T>> CreateStack() {
		std::unique_ptr<IStack<T>> tempStack();

		return tempStack;
	}*/
}