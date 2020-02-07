// to-do: debug mode release mode #define #ifndef etc
#pragma once

#include <cassert>

class ListInt {
#ifdef DEBUG_LOCAL
public:
	static int dest_calls_cnt;
	static int dest_nodes_cnt;
	static int nodes_created_cnt;
	static int nodes_destroyed_cnt;
#endif

private:
	struct Node {
		int data;
		Node* prev;
		Node* next;
		
		Node(int _x = 0, Node* _prev = nullptr, Node* _next = nullptr) 
			: data(_x), prev(_prev), next(_next) {
#ifdef DEBUG_LOCAL
			nodes_created_cnt++;
#endif
		}
	};

	Node* head;
	Node* tail;

	int sz;

public:	
	class Iter {
		friend class ListInt;

        Node* ptr;
#ifdef DEBUG_LOCAL
		ListInt* ListIntPtr;
#endif
	
	public: 
#ifndef DEBUG_LOCAL
		Iter() : ptr(nullptr) {}
		explicit Iter(Node* nptr) : ptr(nptr) {}
		Iter(const Iter& other) : ptr(other.ptr) {}
#else
		Iter() : ptr(nullptr), ListIntPtr(nullptr) {}
		explicit Iter(Node* nptr, ListInt* nListIntPtr) 
			: ptr(nptr), ListIntPtr(nListIntPtr) {}
		Iter(const Iter& other) 
			: ptr(other.ptr), ListIntPtr(other.ListIntPtr) {}
#endif

		inline int operator*() {
			return ptr->data;
		}

		inline Iter& operator++() {
#ifdef DEBUG_LOCAL
			assert(ptr != ListIntPtr->tail);
#endif
			ptr = ptr->next;
			return *this;
		}

		inline Iter operator++(int) {
#ifdef DEBUG_LOCAL
			assert(ptr != ListIntPtr->tail);
#endif
			Iter tmp(*this);
			ptr = ptr->next;
			return tmp;
		}

		inline Iter& operator--() {
#ifdef DEBUG_LOCAL
			assert(ptr != ListIntPtr->head);
#endif
			ptr = ptr->prev;
			return *this;
		}

		inline Iter operator--(int) {
#ifdef DEBUG_LOCAL
			assert(ptr != ListIntPtr->head);
#endif
			Iter tmp(*this);
			ptr = ptr->prev;
			return tmp;
		}

		inline bool operator==(const Iter& other) const {
			return ptr == other.ptr;
		}

		inline bool operator!=(const Iter& other) const {
			return ptr != other.ptr;
		}
	};

	class RIter {
        friend class ListInt;
		
		Node* ptr;
#ifdef DEBUG_LOCAL
		ListInt* ListIntPtr;
#endif
	
	public: 
#ifndef DEBUG_LOCAL	
		RIter() : ptr(nullptr) {}
		explicit RIter(Node* nptr) : ptr(nptr) {}
		RIter(const RIter& other) : ptr(other.ptr) {}
#else
		RIter() : ptr(nullptr), ListIntPtr(nullptr) {}
		explicit RIter(Node* nptr, ListInt* nListIntPtr) 
			: ptr(nptr), ListIntPtr(nListIntPtr) {}
		RIter(const RIter& other) 
			: ptr(other.ptr), ListIntPtr(other.ListIntPtr) {}
#endif
		inline int operator*() {
			return ptr->data;
		}

		inline RIter& operator--() {
#ifdef DEBUG_LOCAL
			assert(ptr != ListIntPtr->tail);
#endif			
			ptr = ptr->next;
			return *this;
		}

		inline RIter operator--(int) {
#ifdef DEBUG_LOCAL
			assert(ptr != ListIntPtr->tail);
#endif			
			RIter tmp(*this);
			ptr = ptr->next;
			return tmp;
		}

		inline RIter& operator++() {
#ifdef DEBUG_LOCAL
			assert(ptr != ListIntPtr->head);
#endif			
			ptr = ptr->prev;
			return *this;
		}

		inline RIter operator++(int) {
#ifdef DEBUG_LOCAL
			assert(ptr != ListIntPtr->head);
#endif			
			RIter tmp(*this);
			ptr = ptr->prev;
			return tmp;
		}

		inline bool operator==(const RIter& other) const {
			return ptr == other.ptr;
		}

		inline bool operator!=(const RIter& other) const {
			return ptr != other.ptr;
		}
	};

	ListInt() : sz(0) {
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->prev = head;
	}

	ListInt(const ListInt& other) {
        sz = other.sz;
        Node* p = head = new Node();
        for (Node* q = other.head->next; ; q = q->next) {
            p = p->next = new Node(q->data, p);
            if (q == other.tail) {
                tail = p;
                break;
            }
        }
	}

	ListInt(ListInt&& other) {
		head = other.head;
		tail = other.tail;
		sz = other.sz;

		other.head = other.tail = nullptr;
		other.sz = 0;
	}

	~ListInt() {
#ifdef DEBUG_LOCAL
		dest_calls_cnt++;
#endif
		
		for (Node* p = head->next; ; p = p->next) {
#ifdef DEBUG_LOCAL
			dest_nodes_cnt++;
#endif

			delete p->prev;
			if (p == tail) {
				break;
			}
		}
		
#ifdef DEBUG_LOCAL
		dest_nodes_cnt++;
#endif

		delete tail;
	}

	inline ListInt operator=(const ListInt& other) {
		for (Node* p = head->next; ; p = p->next) {
#ifdef DEBUG_LOCAL
			nodes_destroyed_cnt++;
#endif

			delete p->prev;
            if (p == tail) {
#ifdef DEBUG_LOCAL
			nodes_destroyed_cnt++;
#endif

                delete p;
                break;
            }
        }
        sz = other.sz;
        Node* p = head = new Node();
        for (Node* q = other.head->next; ; q = q->next) {
            p = p->next = new Node(q->data, p);
            if (q == other.tail) {
                tail = p;
                break;
            }
        }
        return *this;
	}
	
	inline ListInt operator=(ListInt&& other) {
		for (Node* p = head->next; ; p = p->next) {
#ifdef DEBUG_LOCAL
			nodes_destroyed_cnt++;
#endif
			delete p->prev;
			if (p == tail) {
#ifdef DEBUG_LOCAL
				nodes_destroyed_cnt++;
#endif
				delete p;
				break;
			}
		}
		head = other.head;
		tail = other.tail;
		sz = other.sz;

		other.head = other.tail = nullptr;
		other.sz = 0;

		return *this;
	}

	inline const int size() const {
		return sz;
	}

	inline Iter begin() {
#ifndef DEBUG_LOCAL
		return Iter(head->next);
#else
		return Iter(head->next, this);
#endif
	}

	inline Iter end() {
#ifndef DEBUG_LOCAL
		return Iter(tail);
#else
		return Iter(tail, this);
#endif
	}

	inline RIter rbegin() {
#ifndef DEBUG_LOCAL
		return RIter(tail->prev);
#else
		return RIter(tail->prev, this);
#endif
	}

	inline RIter rend() {
#ifndef DEBUG_LOCAL
		return RIter(head);
#else
		return RIter(head, this);
#endif
	}

	inline void push_back(int x) {
		tail->prev = tail->prev->next = new Node(x, tail->prev, tail);
		++sz;
	}

	inline void pop_back() {
		if (sz > 0) {
#ifdef DEBUG_LOCAL
			nodes_destroyed_cnt++;
#endif
			Node* tmp = tail->prev;
			tail->prev->prev->next = tail;
			tail->prev = tail->prev->prev;
			delete tmp;
			--sz;
		}
	}

	inline void push_front(int x) {
		head->next = head->next->prev = new Node(x, head, head->next);
		++sz;
	}

	inline void pop_front() {
		if (sz > 0) {
#ifdef DEBUG_LOCAL
			nodes_destroyed_cnt++;
#endif
			Node* tmp = head->next;
			head->next->next->prev = head;
			head->next = head->next->next;
			delete tmp;
			--sz;
		}
	}

	inline Iter insert(const Iter& pos, int x) {
        Node* tmp = pos.ptr;
        Node* nwn = new Node(x, tmp->prev, tmp);
        nwn->prev->next = nwn->next->prev = nwn;
#ifndef DEBUG_LOCAL
        return Iter(nwn);
#else
		return Iter(nwn, this);
#endif
	}

	inline Iter erase(const Iter& pos) {
#ifdef DEBUG_LOCAL
		nodes_destroyed_cnt++;
#endif
		Node* tmp = pos.ptr;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        Node* next = tmp->next;
        delete tmp;
#ifndef DEBUG_LOCAL
        return Iter(next);
#else
		return Iter(next, this);
#endif
	}

	inline void clear() {
		if (sz > 0) {
			for (Node* p = head->next->next; ; p = p->next) {
#ifdef DEBUG_LOCAL
				nodes_destroyed_cnt++;
#endif

				delete p->prev;
				if (p == tail) {
					break;
				}
			}
			head->next = tail;
			tail->prev = head;
			sz = 0;
		}
	}
};

#ifdef DEBUG_LOCAL
int ListInt::dest_calls_cnt = 0;
int ListInt::dest_nodes_cnt = 0;
int ListInt::nodes_created_cnt = 0;
int ListInt::nodes_destroyed_cnt = 0;
#endif