module;
#include <iostream>
export module Containers:MiddleOutList;

namespace Containers {
	export template<class T> class MiddleOutList {
	public:
		struct Node {
			Node() : m_next(nullptr), m_prev(nullptr) { }
			Node(const T& t) : m_t(t), m_next(nullptr),m_prev(nullptr) { }
			T m_t;
			
			Node* m_next;
			Node* m_prev;
		};
		Node* m_head;
		Node* m_tail;
		class Iterator {
		public:
			Iterator(Node* node) : m_node(node) { }

			bool operator==(const Iterator& other) const {
				if (this == &other) {
					return true;
				}
				return m_node == other.m_node;
			}

			bool operator!=(const Iterator& other) const {
				return !operator==(other);
			}

			T operator*() const {
				if (m_node) {
					return m_node->m_t;
				}
				return T();
			}

			void operator++() {
				if (m_node) {
					m_node = m_node->m_next;
				}
			}

			Node* getNode() {
				return m_node;
			}
		private:
			Node* m_node;
		};

		MiddleOutList() : m_head(nullptr), m_tail(nullptr) {}
		~MiddleOutList() {
			while (m_head) {
				PopFront();
			}
		}
		MiddleOutList(const MiddleOutList& x)
		{
			MiddleOutList<T> tempList;
			Node* tempNode = x.m_head;
			tempList.PushFront(tempNode->m_t);

			while (tempNode->m_next != nullptr) {
				tempNode = tempNode->m_next;
				tempList.PushFront(tempNode->m_t);
			}

			tempNode = tempList.m_head;
			PushFront(tempNode->m_t);

			while (tempNode->m_next != nullptr) {
				tempNode = tempNode->m_next;
				PushFront(tempNode->m_t);
			}
		}

		MiddleOutList(MiddleOutList&& x)
		{
			MiddleOutList<T> tempList;
			Node* tempNode = x.m_head;
			tempList.PushFront(tempNode->m_t);

			while (tempNode->m_next != nullptr) {
				tempNode = tempNode->m_next;
				tempList.PushFront(tempNode->m_t);
			}

			tempNode = tempList.m_head;
			PushFront(tempNode->m_t);

			while (tempNode->m_next != nullptr) {
				tempNode = tempNode->m_next;
				PushFront(tempNode->m_t);
			}

			while (x.m_head) {
				PopFront();
			}
		}

		MiddleOutList<T>& operator=(const MiddleOutList<T>& x) {
			if (&x == this) return *this;

			MiddleOutList<T> tempList;
			Node* tempNode = x.m_head;
			tempList.PushFront(tempNode->m_t);

			while (tempNode->m_next != nullptr) {
				tempNode = tempNode->m_next;
				tempList.PushFront(tempNode->m_t);
			}

			tempNode = tempList.m_head;
			this->PushFront(tempNode->m_t);

			while (tempNode->m_next != nullptr) {
				tempNode = tempNode->m_next;
				this->PushFront(tempNode->m_t);
			}

			return *this;
		}
		MiddleOutList<T>& operator=(MiddleOutList<T>&& x) {
			if (&x == this) return *this;

			MiddleOutList<T> tempList;
			Node* tempNode = x.m_head;
			tempList.PushFront(tempNode->m_t);

			while (tempNode->m_next != nullptr) {
				tempNode = tempNode->m_next;
				tempList.PushFront(tempNode->m_t);
			}

			tempNode = tempList.m_head;
			this->PushFront(tempNode->m_t);

			while (tempNode->m_next != nullptr) {
				tempNode = tempNode->m_next;
				this->PushFront(tempNode->m_t);
			}

			while (x.m_head) {
				PopFront();
			}

			return *this;
		}

		bool InsertAfter(Iterator it, const T& t) {
			for (Iterator iterator = begin(); iterator != end(); ++iterator) {
				if (iterator == it) {
					if (Node* node = new Node(t)) {
						Iterator nextIt = iterator;
						++nextIt;
						node->m_next = nextIt.getNode();

						iterator.getNode()->m_next = node;
						return true;
					}
				}
			} return false;
		}

		bool RemoveAfter(Iterator it) {
			for (Iterator iterator = begin(); iterator != end(); ++iterator) {
				if (iterator == it) {
					Iterator forRemove = iterator;
					++forRemove;
					Iterator nextIt = forRemove;
					++nextIt;

					iterator.getNode()->m_next = nextIt.getNode();

					delete forRemove.getNode();
					return true;
				}
			} return false;
		}


		void PushFront(const T& t) {
			if (Node* node = new Node(t)) {
				if (m_head == nullptr) {
					m_head = node;
					m_tail = node;
					m_head->m_next = m_tail;
					m_tail->m_prev = m_head;
					return;
				}
				if(m_head != nullptr)m_head->m_prev = node;
				node->m_next = m_head;

				m_head = node;
			}
		}

		void PopFront() {
			if (m_head) {
				Node* newHead = m_head->m_next;
				if (m_head->m_next) {
					m_head->m_next->m_prev = nullptr;
				}
				delete m_head;

				m_head = newHead;
			}
		}
		void PushBack(const T& t) {
			if (Node* node = new Node(t)) {
				if (m_head == nullptr) {
					m_head = node;
					m_tail = node;
					m_head->m_next = m_tail;
					m_tail->m_prev = m_head;
					return;
				}
				if (m_tail != nullptr)m_tail->m_next = node;
				node->m_prev = m_tail;

				m_tail = node;
			}
		}

		void PopBack() {
			if (m_tail) {
				Node* newTail = m_tail->m_prev;
				if (m_tail->m_prev) {
					m_tail->m_prev->m_next = nullptr;
				}
				delete m_tail;

				m_tail = newTail;
			} 
		}

		T GetFront() const {
			return m_head->m_t;
		}
		T GetBack() const {
			return m_tail->m_t;
		}

		size_t GetSize() const {
			size_t s = 0;
			for (Iterator it = begin(); it != end(); ++it) {
				++s;
			}
			return s;
		}

		Iterator begin() const {
			return Iterator(m_head);
		}
		Iterator end() const {
			return Iterator(nullptr);
		}
	};
}