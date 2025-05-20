#include <cstring>
#include <iostream>

class Node {
    public:
	    int data;
	    Node* prev;
	    Node* next;
	    
	    Node(int val) {
			data = val;
			prev = nullptr;
			next = nullptr;
	    }
};

class DoublyLinkedList {
	private: 
	  Node* head;
	  Node* tail;
	  int len;
	
	public:
	  DoublyLinkedList() {
		head = nullptr;
		tail = nullptr;
		len = 0;
	  }

	  void add(int val) {

	      Node * newnode = new Node(val);
	      if (!head) {
			head = tail = newnode;
	      }

	      // Add here adds to end of the doubly linked list
	      else {
			tail->next = newnode;
			newnode->prev = tail;
			newnode->next = nullptr;
			tail = newnode; // Update the tail to point to added node
		 }
		 len++;
	  }

	  // Prints out the whole list at once
	  void print() {
	     using namespace std;
	     if(!head) {
			cerr << "List is empty." << endl;
			return;
	     } else {
			Node * curr = head;
			for (int i = 0; i < len; i++) {
				if (curr) {
					cout << "Data for curr " << curr << ": " << curr->data << endl;
					curr = curr->next;
				} else {
					cout << "Reached end of list." << endl;
				}
			}
	     }
	  }


	  void remove(int index) {
		if (index < 0 || index >= len || !head) {
		    std::cerr << "Invalid index or empty list." << std::endl;
		    return;
		}

		Node* current = head;
		for (int i = 0; i < index && current; ++i) {
		    current = current->next;
		}

		if (!current) {
		    std::cerr << "Index out of bounds." << std::endl;
		    return;
		}

		if (current == head && current == tail) {
		    head = tail = nullptr;
		}

		else if (current == head) {
		    head = head->next;
		    head->prev = nullptr;
		
		}
	      
		else if (current == tail) {
		    tail = tail->prev;
		    tail->next = nullptr;
		    
		}
	    
		else {
		    current->prev->next = current->next;
		    current->next->prev = current->prev;
		}

		delete current;
		len--;
	}
		
	
};

int main() {
    DoublyLinkedList list;

    list.add(1);
    list.add(2);
    list.add(3);

    // Should be {1, 2, 3}
    list.print();    
    list.remove(1);
    printf("\n");
    // Should be {1, 3}
    list.print();

    printf("Done\n");

    return 0;
}
