#include <iostream>
#include <string>
#include "BSTree.h"
#include "Node.h"

BSTree::BSTree() 
	: root(nullptr) {}


BSTree::~BSTree() {
    //cout << "Testing" << endl;
    destroyTree(root);
}

// Call the destructor recursively to delete both side

void BSTree::destroyTree(Node* currNode) {
    if (currNode != nullptr) {
        if (currNode->getLeft() == nullptr && currNode->getRight() == nullptr) {
            delete currNode;
            currNode = nullptr;
            // cout << "Deleting" << endl;
        } else {
            destroyTree(currNode->getLeft());
            destroyTree(currNode->getRight());
        }
    }
}


void BSTree::remove(const string &key) {
    if(search(key)) {
        Node *curr = search(key, root);
        
        if(curr->getCount() > 1) {
            curr->setCount(curr->getCount() - 1);
        }
        else {
            remove(curr);
        }
    }
}


// void BSTree::remove(Node *data) {
// 	Node *currNode = data;
// 	Node *succNode = 0;

// 	if(curr->left == nullptr && curr->right == nullptr) {
// 		if(curr->parent != nullptr) {
// 			if(curr->parent->left == curr) {
// 				curr->parent->left = nullptr;
// 			}
// 			else {
// 				curr->parent->right = nullptr;
// 			}
// 		}
// 		else {
// 			root = nullptr;
// 		}
// 		delete curr;
// 	}
// 	else if(curr->left != nullptr) {
// 		succNode = curr->left;
// 		while(succNode->right != nullptr) {
// 			succNode = succNode->right;
// 		}
// 		*curr = *succNode;
// 		remove(succNode);
// 	}
// 	else {
// 		succNode = curr->right;
// 		while(succNode->left != 0) {
// 			succNode = succNode->left;
// 		}
// 		*curr = *succNode;
// 		remove(succ);
// 	}
// }


void BSTree::remove(Node *curr) {
    // check if node to remove is a leaf node
    if (curr->getLeft() == nullptr && curr->getRight() == nullptr) {
        Node *parentNode = curr->getParent();
        if (parentNode != nullptr) {
            if (parentNode->getLeft() == curr) {
                parentNode->setLeft(nullptr);
            } else {
                parentNode->setRight(nullptr);
            }
        } else {
            root = nullptr;
        }
        delete curr;
    }
    // check if node to remove has only left child
    else if (curr->getLeft() != nullptr && curr->getRight() == nullptr) {
        Node *childNode = curr->getLeft();
        Node *parentNode = curr->getParent();
        if (parentNode != nullptr) {
            if (parentNode->getLeft() == curr) {
                parentNode->setLeft(childNode);
            } else {
                parentNode->setRight(childNode);
            }
        } else {
            root = childNode;
        }
        childNode->setParent(parentNode);
        delete curr;
    }
    // check if node to remove has only right child
    else if (curr->getLeft() == nullptr && curr->getRight() != nullptr) {
        Node *childNode = curr->getRight();
        Node *parentNode = curr->getParent();
        if (parentNode != nullptr) {
            if (parentNode->getLeft() == curr) {
                parentNode->setLeft(childNode);
            } else {
                parentNode->setRight(childNode);
            }
        } else {
            root = childNode;
        }
        childNode->setParent(parentNode);
        delete curr;
    }
    // node to remove has two children
    else {
        Node *succNode = curr->getRight();
        while (succNode->getLeft() != nullptr) {
            succNode = succNode->getLeft();
        }
        curr->setString(succNode->getString());
        curr->setCount(succNode->getCount());
        remove(succNode);
    }
}

void BSTree::insert(const string& data) {
    Node* curr = root;
    if(search(data)) {
        curr = search(data, root);
        curr->setCount(curr->getCount() + 1);
    }
    else {
        Node* newNode = new Node(data);
        if(root == nullptr) {
            root = newNode;
        }
        else {
            while(true) {
                if(data < curr->getString()) {
                    if(curr->getLeft() == nullptr) {
                        curr->setLeft(newNode);
                        newNode->setParent(curr);

                        return;
                    }
                    else {
                        curr = curr->getLeft();
                    }
                }
                else {
                    if(curr->getRight() == nullptr) {
                        curr->setRight(newNode);
                        newNode->setParent(curr);
                        return;
                    }
                    else {
                        curr = curr->getRight();
                    }
                }
            }
        }
    }
}


bool BSTree::search(const string& data) const {
	return search(data, root);
}
Node* BSTree::search(const string &data, Node* curr) const {
    if(curr != nullptr) {
        if(data == curr->getString()) {
            return curr;
        }
        else {
            if(data < curr->getString()) {
                return search(data, curr->getLeft());
            }
            else {
                return search(data, curr->getRight());
            }
        }
    }
    else {
        return nullptr;
    }
}

string BSTree::largest() const {
	Node* curr = root;
	if(curr == nullptr) {
		return "";
	}
	else {
		while(1) {
			if(curr->getRight() == nullptr) {
				return curr->getString();
			}
			else {
				curr = curr->getRight();
			}
		}
	}
}

string BSTree::smallest() const {
    Node* curr = root;
    
    if(curr == nullptr) {
        return "";
    }
    else {
        while(true) {
            if(curr->getLeft() == nullptr) {
                return curr->getString();
            }
            else {
                curr = curr->getLeft();
            }
        }
    }
}

int BSTree::height(const string &data) const {
    if(!search(data)) {
        return -1;
    }
    Node *curr = search(data, root);
    int leftCnt = 0;
    int rightCnt = 0;
    
    if(curr->getLeft() != nullptr) {
        leftCnt = 1 + height(curr->getLeft()->getString());
    }
    if(curr->getRight() != nullptr) {
        rightCnt = 1 + height(curr->getRight()->getString());
    }
    if(leftCnt >= rightCnt) {
        return leftCnt;
    }
    else {
        return rightCnt;
    }
}


void BSTree::preOrder() const {
	preOrder(root);
}

void BSTree::preOrder(Node *curr) const {
	if(curr != nullptr) {
		cout << curr->getString() << '(' << curr->getCount() << "), ";
		preOrder(curr->getLeft());
		preOrder(curr->getRight());
	}
}


void BSTree::inOrder() const {
	inOrder(root);
}

void BSTree::inOrder(Node *curr) const {
	if(curr != nullptr) {
		inOrder(curr->getLeft());
		cout << curr->getString() << '(' << curr->getCount() << "), ";
		inOrder(curr->getRight());
	}
}


void BSTree::postOrder() const {
	postOrder(root);
}

void BSTree::postOrder(Node *curr) const {
	if(curr != 0) {
		postOrder(curr->getLeft());
		postOrder(curr->getRight());
		cout << curr->getString() << '(' << curr->getCount() << "), ";
	}
}









