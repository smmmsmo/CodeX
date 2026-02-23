#include "node.cpp"
  //create a function to create a node 10 20 30 40
  Node* createNode() {
    //create a node
    Node *head = new Node(10);
    Node *second = new Node(20);
    Node *third = new Node(30);
    Node *fourth = new Node(40);
  
    //link the nodes
    head->next = second;
    second->next = third;
    third->next = fourth;

    return head;
  }   

  //create a function to print the node
  void printNode(Node *head) {
    Node *temp = head;
    while (temp != nullptr) {
      std::cout << temp->data << " ";
      temp = temp->next;
    }
    std::cout << std::endl;
  }