#include <iostream>
#include <vector>
using namespace std;

// Example struct for learning vectors of objects
struct Student {
  string name;
  int age;
  double gpa;

  Student(string n, int a, double g) : name(n), age(a), gpa(g) {}
};

int main() {
  cout << "=== C++ VECTOR TUTORIAL ===" << endl << endl;

  // 1. CREATING AND INITIALIZING VECTORS
  cout << "1. CREATING VECTORS" << endl;

  vector<int> v1;                   // Empty vector
  vector<int> v2(5);                // Vector with 5 elements (initialized to 0)
  vector<int> v3(5, 10);            // Vector with 5 elements, all set to 10
  vector<int> v4 = {1, 2, 3, 4, 5}; // Vector initialized with values

  cout << "v4 initialized with {1, 2, 3, 4, 5}" << endl;
  cout << "Size of v4: " << v4.size() << endl << endl;

  // 2. ADDING ELEMENTS
  cout << "2. ADDING ELEMENTS" << endl;

  v1.push_back(100);
  v1.push_back(200);
  v1.push_back(300);

  cout << "After push_back(100), push_back(200), push_back(300):" << endl;
  cout << "v1 size: " << v1.size() << endl;
  cout << "v1 capacity: " << v1.capacity() << endl << endl;

  // 3. ACCESSING ELEMENTS
  cout << "3. ACCESSING ELEMENTS" << endl;

  cout << "Access using [] operator:" << endl;
  cout << "v4[0] = " << v4[0] << endl;
  cout << "v4[2] = " << v4[2] << endl;

  cout << "\nAccess using .at() method (with bounds checking):" << endl;
  cout << "v4.at(1) = " << v4.at(1) << endl;

  cout << "\nFirst and last elements:" << endl;
  cout << "v4.front() = " << v4.front() << endl;
  cout << "v4.back() = " << v4.back() << endl << endl;

  // 4. ITERATING THROUGH VECTORS
  cout << "4. ITERATING THROUGH VECTORS" << endl;

  cout << "Using for loop with index:" << endl;
  for (int i = 0; i < v4.size(); i++) {
    cout << v4[i] << " ";
  }
  cout << endl;

  cout << "Using range-based for loop:" << endl;
  for (int val : v1) {
    cout << val << " ";
  }
  cout << endl;

  cout << "Using iterator:" << endl;
  for (auto it = v4.begin(); it != v4.end(); it++) {
    cout << *it << " ";
  }
  cout << endl << endl;

  // 5. MODIFYING ELEMENTS
  cout << "5. MODIFYING ELEMENTS" << endl;

  v4[0] = 999;
  cout << "After v4[0] = 999: ";
  for (int val : v4)
    cout << val << " ";
  cout << endl;

  v4.at(2) = 777;
  cout << "After v4.at(2) = 777: ";
  for (int val : v4)
    cout << val << " ";
  cout << endl << endl;

  // 6. REMOVING ELEMENTS
  cout << "6. REMOVING ELEMENTS" << endl;

  v4.pop_back(); // Remove last element
  cout << "After pop_back(), v4 size: " << v4.size() << endl;
  cout << "v4: ";
  for (int val : v4)
    cout << val << " ";
  cout << endl;

  v4.erase(v4.begin()); // Remove first element
  cout << "After erasing first element, v4: ";
  for (int val : v4)
    cout << val << " ";
  cout << endl << endl;

  // 7. VECTOR SIZE AND CAPACITY
  cout << "7. SIZE VS CAPACITY" << endl;

  vector<int> v5;
  cout << "Empty vector - Size: " << v5.size()
       << ", Capacity: " << v5.capacity() << endl;

  for (int i = 0; i < 10; i++) {
    v5.push_back(i);
    cout << "After adding element " << i << " - Size: " << v5.size()
         << ", Capacity: " << v5.capacity() << endl;
  }
  cout << endl;

  // 8. CLEARING AND CHECKING IF EMPTY
  cout << "8. CLEARING AND CHECKING" << endl;

  vector<int> v6 = {1, 2, 3};
  cout << "v6 empty? " << (v6.empty() ? "Yes" : "No") << endl;

  v6.clear();
  cout << "After clear() - v6 empty? " << (v6.empty() ? "Yes" : "No") << endl;
  cout << "Size after clear: " << v6.size() << endl << endl;

  // 9. VECTOR OF OBJECTS
  cout << "9. VECTOR OF OBJECTS" << endl;

  vector<Student> students;
  students.push_back(Student("Alice", 20, 3.8));
  students.push_back(Student("Bob", 21, 3.5));
  students.push_back(Student("Charlie", 19, 3.9));

  cout << "Students in the vector:" << endl;
  for (int i = 0; i < students.size(); i++) {
    cout << students[i].name << " - Age: " << students[i].age
         << ", GPA: " << students[i].gpa << endl;
  }
  cout << endl;

  // 10. USEFUL VECTOR OPERATIONS
  cout << "10. USEFUL OPERATIONS" << endl;

  vector<int> v7 = {5, 2, 8, 1, 9};

  // Insert at specific position
  v7.insert(v7.begin() + 2, 999);
  cout << "After inserting 999 at position 2: ";
  for (int val : v7)
    cout << val << " ";
  cout << endl;

  // Resize
  v7.resize(3);
  cout << "After resize to 3: ";
  for (int val : v7)
    cout << val << " ";
  cout << endl << endl;

  // 11. 2D VECTORS
  cout << "11. 2D VECTORS" << endl;

  vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  cout << "2D Vector (3x3 matrix):" << endl;
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
