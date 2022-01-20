module;

export module Containers:DynamicQueue;
import :DynamicArray;

namespace Containers {
	export template<class T> class DynamicQueue {
	public:
		DynamicArray<T> arr;

		DynamicQueue() {}
		~DynamicQueue() {}

		void Enqueue(const T& t) {
			size_t size = arr.GetSize();
			DynamicArray<T> temp = DynamicArray<T>(size + 1);
			for (int i = 0; i < size; i++) {
				temp[i] = arr[i];
			}
			temp[size] = t;
			arr = temp;
			return;
		}
		void Dequeue() {
			size_t size = arr.GetSize() - 1;
			DynamicArray<T> temp = DynamicArray<T>(size);
			for (int i = 0; i < size; i++) {
				temp[i] = arr[i+1];
			}
			arr = temp;
			return;
		}
		T Peek() {
			return arr[0];
		}
		size_t Size() {
			return arr.GetSize();
		}
	};
}