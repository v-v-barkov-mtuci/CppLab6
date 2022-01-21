module;
#include <memory>
export module Containers:ForwardList;

namespace Containers {
	export template<class T> class ForwardList {
	public:
		struct Node {
			Node() : m_next(nullptr) { }
			Node(const T& t) : m_t(t), m_next(nullptr) { }
			// �������� ����
			T m_t;
			// ��������� �� ��������� ����
			Node* m_next;
		};
		Node* m_head;
		class Iterator {
		public:
			Iterator(Node* node) : m_node(node) { }

			// �������� �� ���������
			bool operator==(const Iterator& other) const {
				if (this == &other) {
					return true;
				}
				return m_node == other.m_node;
			}

			// �������� �� �����������
			bool operator!=(const Iterator& other) const {
				return !operator==(other);
			}

			// ��������� �������� �������� ����
			T operator*() const {
				if (m_node) {
					return m_node->m_t;
				} // ����� ��������� ����� ������. ������� ��������� ����������
				return T();
			}

			// ������� � ���������� ����
			void operator++() {
				if (m_node) {
					m_node = m_node->m_next;
				} // ����� ��������� ����� ������. ������� ��������� ����������
			}

			Node* getNode() {
				return m_node;
			}
		private:
			Node* m_node;
		};

		ForwardList() : m_head(nullptr) {}
		~ForwardList() {
			while (m_head) {
				PopFront();
			}
		}
		// ����������� �����������, ������� ��������� �������� ����������� x.m_ptr � m_ptr
		ForwardList(const ForwardList& x)
		{
			ForwardList<T> tempList;
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

		// ����������� �����������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
		ForwardList(ForwardList&& x)
		{
			ForwardList<T> tempList;
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
		ForwardList<T>& operator=(const std::initializer_list<T>& x) { //�����������
			for (int i = 0; i < x.size(); i++) {
				*this->PushFront(x[i]);
			}

			return *this;
		}

		ForwardList<T>& operator=(const ForwardList<T>& x) { //�����������
			if (&x == this) return *this;

			ForwardList<T> tempList;
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
		ForwardList<T>& operator=(ForwardList<T>&& x) { //�����������
			if (&x == this) return *this;

			ForwardList<T> tempList;
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
			// ������� ����� ���� ��� ��������
			// �� ������� ���������, ��� ������ ������� ��������
			if (Node* node = new Node(t)) {
				// ����� ���� ������������� � ������� ��������� ��������
				node->m_next = m_head;

				// ����� ���� ��� ���������� �������� ���������
				m_head = node;
			}
		}

		void PopFront() {
			if (m_head) { // ���� ������ �� ����:
				// ��������� ��������� �� ������ ����, ������� ������ ����� �������� ���������
				Node* newHead = m_head->m_next;

				// ����������� ������, ���������� ��� ���������� ��������� ��������
				delete m_head;

				// ��������� ����� �������� �������
				m_head = newHead;
			} // ����� ����� �� ��������� ����������
		}

		T GetFront() const {
			return m_head->m_t;
		}

		size_t GetSize() const {
			size_t s = 0;
			for (Iterator it = begin(); it != end(); ++it) {
				++s;
			}
			return s;
		}

		Iterator begin() const {
			// �������� ������ �� ��������� ��������...
			return Iterator(m_head);
		}
		Iterator end() const {
			// ... � �� �����, �.�. NULL
			return Iterator(nullptr);
		}
	};
}