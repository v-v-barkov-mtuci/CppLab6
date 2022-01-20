module;
#include <memory>
export module Containers:Queue;
import :MiddleOutList;

namespace Containers {
	export template<class T> class Queue {
	public:
		MiddleOutList<T> list;

		Queue(){}
		~Queue() {}

		void Enqueue(const T& t){
			list.PushBack(t);
		}
		void Dequeue() {
			list.PopFront();
		}
		T Peek() {
			return list.GetFront();
		}
		size_t Size() {
			return list.GetSize();
		}
		bool IsEmpty() {
			if (list.GetSize() > 0) return false;
			else return true;
		}
	};
	export template<class T> std::unique_ptr<Queue<T>> CreateQueue(size_t size) {
		std::unique_ptr<Queue<T>> tempStack(size);

		return tempStack;
	}
	export template<class T> std::unique_ptr<Queue<T>> CreateQueue() {
		std::unique_ptr<Queue<T>> tempStack();

		return tempStack;
	}
}