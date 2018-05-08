
template <class T>
class BST {
	public:

		BST(BST<T> *l, BST<T> *r, T v) : left(l), right(r), value(v) {}

		BST(T v) : left(NULL), right(NULL), value(v) {}

		bool insert(BST<T> * newNode) {
			if (newNode->value == value)
				return false;
			else if (newNode->value < value)
				if (hasLeft())
					return left->insert(newNode);
				else left = newNode;
			else
				if (hasRight())
					return right->insert(newNode);
				else right = newNode;
			return true;
		}

		bool insert(T v) {
			return insert(new BST(v));
		}

		bool contains(T v) {
			if (value == v)
				return true;
			if (hasLeft() && left->contains(v))
				return true;
			if (hasRight() && right->contains(v))
				return true;
			return false;
		}

		int maxDepth() {
			int depth = 0;
			if (hasLeft())
				depth = max(depth, left->maxDepth());
			if (hasRight())
				depth = max(depth, right->maxDepth());
			return depth + 1;
		}

		int minDepth(int currDepth, int max) {
			if (currDepth == max)
				return max;
			if (hasLeft())
				max = left->minDepth(currDepth + 1, max);
			if (hasRight())
				max = right->minDepth(currDepth + 1, max);
			return currDepth > max ? currDepth:max;
		}

		int minDepth() {
			return minDepth(0, -1);
		}

		void print(ostream &out) {
			if (hasLeft())
				left->print(out);
			out << value << " ";
			if (hasRight())
				right->print(out);
			out << flush;
		}

		T getValue() { return value; }
		BST<T> *getLeft() { return left; }
		BST<T> *getRight() { return right; }

		bool hasLeft() { return left != NULL; }
		bool hasRight() { return right != NULL; }

		~BST() {}

	private:
		BST<T> *left, *right;
		T value;
};

template <class T>
ostream &operator << (ostream &out, BST<T> bst) {
	bst.print(out);
}