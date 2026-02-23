#include "node.cpp"
#include <iostream>
#include <sstream>
#include <vector>

void assert_equal(int actual, int expected, const std::string &message) {
  if (actual != expected) {
    std::cerr << "FAIL: " << message << " - Expected: " << expected
              << ", Actual: " << actual << std::endl;
    exit(1);
  }
}

void assert_true(bool condition, const std::string &message) {
  if (!condition) {
    std::cerr << "FAIL: " << message << std::endl;
    exit(1);
  }
}

void test_node_construction() {
  std::cout << "Running test_node_construction..." << std::endl;
  Node n(10);
  assert_equal(n.data, 10, "Node data should be initialized correctly");
  assert_true(n.next == nullptr,
              "Node next pointer should be initialized to nullptr");
  std::cout << "PASSED" << std::endl;
}

void test_manual_linking() {
  std::cout << "Running test_manual_linking..." << std::endl;
  Node head(10);
  Node second(20);
  head.next = &second;

  assert_true(head.next == &second, "Head should point to second node");
  assert_equal(head.next->data, 20, "Linked node data should be accessible");
  std::cout << "PASSED" << std::endl;
}

void test_print_node() {
  std::cout << "Running test_print_node..." << std::endl;

  // Setup list 10 -> 20 -> 30
  Node n1(10);
  Node n2(20);
  Node n3(30);
  n1.next = &n2;
  n2.next = &n3;

  // Redirect stdout
  std::stringstream buffer;
  std::streambuf *old_cout = std::cout.rdbuf(buffer.rdbuf());

  // Call function
  n1.printNode(&n1);

  // Restore stdout
  std::cout.rdbuf(old_cout);

  std::string output = buffer.str();
  std::string expected = "10 20 30 \n";

  if (output != expected) {
    std::cerr << "FAIL: Output mismatch in test_print_node" << std::endl;
    std::cerr << "Expected: '" << expected << "'" << std::endl;
    std::cerr << "Actual:   '" << output << "'" << std::endl;
    exit(1);
  }
  std::cout << "PASSED" << std::endl;
}

void test_create_node() {
  std::cout << "Running test_create_node..." << std::endl;
  Node temp(0); // Dummy node to call the method
  Node *head = temp.createNode();

  assert_true(head != nullptr, "Head should not be nullptr");
  assert_equal(head->data, 10, "First node data should be 10");

  assert_true(head->next != nullptr, "Second node should exist");
  assert_equal(head->next->data, 20, "Second node data should be 20");

  assert_true(head->next->next != nullptr, "Third node should exist");
  assert_equal(head->next->next->data, 30, "Third node data should be 30");

  assert_true(head->next->next->next != nullptr, "Fourth node should exist");
  assert_equal(head->next->next->next->data, 40,
               "Fourth node data should be 40");

  assert_true(head->next->next->next->next == nullptr,
              "Fifth node should be nullptr");

  std::cout << "PASSED" << std::endl;

  // Clean up to avoid memory leaks in test
  // In a real scenario, we might want a destructor or a helper to delete the
  // list
  Node *current = head;
  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
  }
}

int main() {
  std::cout << "Starting tests for node.cpp..." << std::endl;
  test_node_construction();
  test_manual_linking();
  test_print_node();
  test_create_node();

  std::cout << "\nAll tests passed successfully!" << std::endl;

  return 0;
}
