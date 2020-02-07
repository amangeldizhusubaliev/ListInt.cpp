#include <bits/stdc++.h>

#include "ListInt.hpp"

using namespace std;

int main() {
#ifdef DEBUG_LOCAL
	{
		ListInt l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);

		ListInt::Iter i = l.end();
		i++;
	}

	cout << "ListInt::~ListInt() calls: " << ListInt::dest_calls_cnt << "\n";
	cout << "ListInt::~ListInt() nodes destroyed: " << ListInt::dest_nodes_cnt << "\n";
	cout << "ListInt created nodes: " << ListInt::nodes_created_cnt << "\n";
	cout << "ListInt destroyed nodes: " << ListInt::nodes_destroyed_cnt << "\n";
#endif

	return 0;
}