/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K & key) const
{
	return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node * subtree, const K & key) const
{
	if (subtree == NULL)
		return V();
	else if (key == subtree->key)
		return subtree->value;
	else
	{
		if (key < subtree->key)
			return find(subtree->left, key);
		else
			return find(subtree->right, key);
	}
}


template <class K, class V>
int AVLTree<K, V>::heightOrNeg2(const Node* node) const
{	if(node == NULL)
		return -1;
	else if (node->right == NULL && node ->left == NULL){
		node->height = 1;
		return 1;
	}else{
		node->height = max(heightOrNeg1(node->left),heightOrNeg1(node->right))+1;	
		return node->height;
	}
	
	

}


template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    
    Node * y = t->right;
	t->right = y->left;
	y ->left = t;
	t->height = heightOrNeg1(t);
	t = y;
	t->height = heightOrNeg1(t);
    
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	// Implemented for you:
	rotateLeft(t->left);
	rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    
    Node * y = t->left;
    t->left = y -> right;
    y -> right = t;
    t->height = heightOrNeg1(t);
    t = y;
	t->height = heightOrNeg1(t);

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
	insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node* & subtree, const K & key, const V & value)
{

    // your code here
    
    if(subtree == NULL)
		subtree = new Node(key, value);
	else if(subtree->right == NULL && subtree->left == NULL){
		if(key < subtree->key)
			subtree->left = new Node(key, value);
		else
			subtree->right = new Node(key, value);
		subtree->height++;
		
	}else{
		
		if(subtree->key < key){
			insert(subtree->right, key, value);	
			if(subtree->right != NULL)
				subtree->height++;
		}
		if(key < subtree->key){
			insert(subtree->left, key, value);
			if(subtree->left != NULL)
				subtree->height++;
		}

		
	}
    
}
