/*
================================================================================
COMPOSITION AND AGGREGATION - BUILDING RELATIONSHIPS BETWEEN OBJECTS
================================================================================
Part 2, Subtopic 14: Composition and Aggregation (File 1/2)

CONCEPTS COVERED:
- Composition: "Has-a" relationship (ownership)
- Aggregation: "Has-a" relationship (no ownership)
- Difference between composition and inheritance
- Object lifetime management
- Deep vs shallow copying
- When to use composition vs inheritance
- Design patterns with composition

KEY LEARNING POINTS:
1. Composition is strong association with ownership
2. Aggregation is weak association without ownership
3. Composition lifetime: component dies with composite
4. Aggregation lifetime: independent lifetimes
5. Prefer composition over inheritance for flexibility
6. Composition enables code reuse
7. Aggregation allows shared components

================================================================================
*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/*
================================================================================
THEORY SECTION: COMPOSITION AND AGGREGATION
================================================================================

COMPOSITION VS INHERITANCE:
Inheritance (Is-a):
- Dog IS-A Animal
- Tight coupling
- Fixed hierarchy
- Cannot change at runtime

Composition (Has-a):
- Car HAS-A Engine
- Loose coupling
- Flexible
- Can change at runtime

COMPOSITION:
- Strong association
- Composite owns component
- Component created/destroyed with composite
- Deep copy required
- No outside access to component
- "Part-of" relationship
- Example: Engine is part of Car

AGGREGATION:
- Weak association
- Composite does not own component
- Component lifetime independent
- Shallow copy/reference
- Outside can access component
- "Member-of" relationship
- Example: Student is member of Team

WHEN TO USE COMPOSITION:
1. Need ownership control
2. Want loose coupling
3. Component used by only one object
4. Need to manage lifecycle
5. Prefer interface contracts

WHEN TO USE AGGREGATION:
1. Component shared by multiple objects
2. Component lifetime independent
3. Component created externally
4. Want flexibility in components
5. Temporary groupings

WHEN NOT TO USE INHERITANCE:
1. Objects only share code (use composition)
2. Implementing interface contract (use composition)
3. Need runtime polymorphism in single direction
4. Multiple inheritance becomes complex

================================================================================
*/

/*
================================================================================
EXAMPLE 1: COMPOSITION - CAR AND ENGINE
================================================================================
*/

class Engine {
private:
  string type;
  double horsepower;
  bool running;

public:
  Engine(string t = "Diesel", double hp = 150.0)
      : type(t), horsepower(hp), running(false) {}

  void start() {
    running = true;
    cout << type << " engine started! Horsepower: " << horsepower << endl;
  }

  void stop() {
    running = false;
    cout << type << " engine stopped." << endl;
  }

  bool isRunning() const { return running; }

  void display() const {
    cout << "Engine: " << type << " (" << horsepower << " HP)" << endl;
  }

  ~Engine() {
    if (running)
      stop();
  }
};

class Car {
private:
  string model;
  Engine engine; // COMPOSITION: Car owns Engine

public:
  Car(string m, string engineType = "Petrol", double hp = 100.0)
      : model(m), engine(engineType, hp) {}

  void startCar() {
    cout << "Starting " << model << "..." << endl;
    engine.start();
  }

  void stopCar() {
    cout << "Stopping " << model << "..." << endl;
    engine.stop();
  }

  void displayInfo() {
    cout << "Car: " << model << endl;
    engine.display();
  }

  ~Car() { cout << "Car " << model << " destroyed" << endl; }
};

/*
OUTPUT:
--------
Starting Honda...
Petrol engine started! Horsepower: 100
Stopping Honda...
Petrol engine stopped.
Car Honda destroyed
--------
*/

/*
================================================================================
EXAMPLE 2: AGGREGATION - TEAM AND PLAYERS
================================================================================
*/

class Player {
private:
  string name;
  int jerseyNumber;
  double score;

public:
  Player(string n = "", int j = 0, double s = 0.0)
      : name(n), jerseyNumber(j), score(s) {}

  string getName() const { return name; }
  int getJerseyNumber() const { return jerseyNumber; }
  double getScore() const { return score; }

  void addScore(double points) { score += points; }

  void display() const {
    cout << name << " (#" << jerseyNumber << ") - Score: " << score << endl;
  }

  ~Player() { cout << "Player " << name << " destroyed" << endl; }
};

class Team {
private:
  string teamName;
  vector<Player *> players; // AGGREGATION: Team has pointers to Players

public:
  Team(string name) : teamName(name) {}

  void addPlayer(Player *player) {
    if (player != nullptr) {
      players.push_back(player);
      cout << "Added " << player->getName() << " to team." << endl;
    }
  }

  void removePlayer(Player *player) {
    auto it = find(players.begin(), players.end(), player);
    if (it != players.end()) {
      players.erase(it);
      cout << "Removed " << player->getName() << " from team." << endl;
    }
  }

  double getTeamScore() const {
    double total = 0;
    for (const auto *p : players) {
      total += p->getScore();
    }
    return total;
  }

  void displayTeam() const {
    cout << "=== Team: " << teamName << " ===" << endl;
    for (const auto *p : players) {
      p->display();
    }
    cout << "Total Score: " << getTeamScore() << endl;
  }

  ~Team() {
    cout << "Team " << teamName << " destroyed (players not deleted)" << endl;
  }
};

/*
OUTPUT:
--------
Added Alice to team.
Added Bob to team.
=== Team: Warriors ===
Alice (#1) - Score: 30
Bob (#2) - Score: 25
Total Score: 55
--------
*/

/*
================================================================================
EXAMPLE 3: COMPOSITION - STUDENT AND COURSES
================================================================================
*/

class Course {
private:
  string courseCode;
  string courseName;
  int credits;

public:
  Course(string code = "", string name = "", int cr = 3)
      : courseCode(code), courseName(name), credits(cr) {}

  string getCode() const { return courseCode; }
  string getName() const { return courseName; }
  int getCredits() const { return credits; }

  void display() const {
    cout << courseCode << " - " << courseName << " (" << credits << " credits)"
         << endl;
  }
};

class Student {
private:
  string studentId;
  string name;
  vector<Course> courses; // COMPOSITION: Student owns Courses

public:
  Student(string id, string n) : studentId(id), name(n) {}

  void enrollCourse(const Course &course) {
    courses.push_back(course);
    cout << "Enrolled " << name << " in " << course.getName() << endl;
  }

  int getTotalCredits() const {
    int total = 0;
    for (const auto &course : courses) {
      total += course.getCredits();
    }
    return total;
  }

  void displayCourses() const {
    cout << "=== Student: " << name << " (ID: " << studentId << ") ===" << endl;
    for (const auto &course : courses) {
      course.display();
    }
    cout << "Total Credits: " << getTotalCredits() << endl;
  }

  ~Student() {
    cout << "Student " << name << " destroyed (courses deleted with student)"
         << endl;
  }
};

/*
OUTPUT:
--------
Enrolled Alice in Data Structures
Enrolled Alice in Algorithms
=== Student: Alice (ID: S001) ===
CS201 - Data Structures (3 credits)
CS202 - Algorithms (3 credits)
Total Credits: 6
--------
*/

/*
================================================================================
EXAMPLE 4: COMPOSITION - COMPANY AND DEPARTMENTS
================================================================================
*/

class Department {
private:
  string departmentName;
  int employeeCount;
  double budget;

public:
  Department(string name = "", int count = 0, double b = 0)
      : departmentName(name), employeeCount(count), budget(b) {}

  string getName() const { return departmentName; }
  int getEmployeeCount() const { return employeeCount; }
  double getBudget() const { return budget; }

  void updateBudget(double amount) { budget += amount; }

  void display() const {
    cout << "Department: " << departmentName
         << " | Employees: " << employeeCount << " | Budget: $" << budget
         << endl;
  }

  ~Department() {
    cout << "Department " << departmentName << " destroyed" << endl;
  }
};

class Company {
private:
  string companyName;
  vector<Department> departments; // COMPOSITION: Company owns Departments

public:
  Company(string name) : companyName(name) {}

  void addDepartment(const Department &dept) {
    departments.push_back(dept);
    cout << "Added department: " << dept.getName() << endl;
  }

  double getTotalBudget() const {
    double total = 0;
    for (const auto &dept : departments) {
      total += dept.getBudget();
    }
    return total;
  }

  int getTotalEmployees() const {
    int total = 0;
    for (const auto &dept : departments) {
      total += dept.getEmployeeCount();
    }
    return total;
  }

  void displayInfo() const {
    cout << "=== Company: " << companyName << " ===" << endl;
    for (const auto &dept : departments) {
      dept.display();
    }
    cout << "Total Employees: " << getTotalEmployees() << endl;
    cout << "Total Budget: $" << getTotalBudget() << endl;
  }

  ~Company() { cout << "Company " << companyName << " destroyed" << endl; }
};

/*
OUTPUT:
--------
Added department: Engineering
Added department: Sales
=== Company: TechCorp ===
Department: Engineering | Employees: 50 | Budget: $500000
Department: Sales | Employees: 30 | Budget: $200000
Total Employees: 80
Total Budget: $700000
--------
*/

/*
================================================================================
EXAMPLE 5: AGGREGATION - UNIVERSITY AND STUDENTS
================================================================================
*/

class University {
private:
  string universityName;
  vector<Student *> students; // AGGREGATION: University has Students

public:
  University(string name) : universityName(name) {}

  void enrollStudent(Student *student) {
    if (student != nullptr) {
      students.push_back(student);
      cout << "Enrolled student at " << universityName << endl;
    }
  }

  void removeStudent(Student *student) {
    auto it = find(students.begin(), students.end(), student);
    if (it != students.end()) {
      students.erase(it);
      cout << "Student removed from " << universityName << endl;
    }
  }

  int getEnrollmentCount() const { return students.size(); }

  void displayRoster() const {
    cout << "=== " << universityName << " Roster ===" << endl;
    cout << "Total Students: " << students.size() << endl;
  }

  ~University() {
    cout << "University " << universityName << " destroyed" << endl;
  }
};

/*
OUTPUT:
--------
Enrolled student at Harvard
University Harvard roster: 1 student
--------
*/

/*
================================================================================
EXAMPLE 6: COMPOSITE PATTERN - FILE SYSTEM
================================================================================
*/

class FileSystemComponent {
public:
  virtual ~FileSystemComponent() = default;
  virtual void display(int indent = 0) const = 0;
  virtual int getSize() const = 0;
};

class File : public FileSystemComponent {
private:
  string fileName;
  int fileSize;

public:
  File(string name, int size) : fileName(name), fileSize(size) {}

  void display(int indent = 0) const override {
    for (int i = 0; i < indent; i++)
      cout << "  ";
    cout << "[File] " << fileName << " (" << fileSize << " bytes)" << endl;
  }

  int getSize() const override { return fileSize; }
};

class Directory : public FileSystemComponent {
private:
  string dirName;
  vector<FileSystemComponent *>
      contents; // COMPOSITION: Directory owns components

public:
  Directory(string name) : dirName(name) {}

  void addComponent(FileSystemComponent *component) {
    contents.push_back(component);
  }

  void display(int indent = 0) const override {
    for (int i = 0; i < indent; i++)
      cout << "  ";
    cout << "[Dir] " << dirName << "/" << endl;
    for (const auto *comp : contents) {
      comp->display(indent + 1);
    }
  }

  int getSize() const override {
    int total = 0;
    for (const auto *comp : contents) {
      total += comp->getSize();
    }
    return total;
  }

  ~Directory() {
    for (auto *comp : contents) {
      delete comp;
    }
  }
};

/*
OUTPUT:
--------
[Dir] root/
  [File] readme.txt (1024 bytes)
  [Dir] documents/
    [File] report.pdf (2048 bytes)
    [File] notes.txt (512 bytes)
Total Size: 3584 bytes
--------
*/

/*
================================================================================
EXAMPLE 7: MIXED - COMPOSITION WITH SMART POINTERS
================================================================================
*/

class House {
private:
  string address;
  unique_ptr<Engine> heater; // COMPOSITION with smart pointer

public:
  House(string addr, string heaterType)
      : address(addr), heater(make_unique<Engine>(heaterType, 10)) {
    cout << "House constructed at " << address << endl;
  }

  void turnOnHeater() {
    cout << "Turning on heater..." << endl;
    heater->start();
  }

  void turnOffHeater() {
    cout << "Turning off heater..." << endl;
    heater->stop();
  }

  void displayInfo() {
    cout << "House at: " << address << endl;
    heater->display();
  }

  ~House() {
    cout << "House destroyed, heater automatically cleaned up" << endl;
  }
};

/*
OUTPUT:
--------
House constructed at 123 Main St
House at: 123 Main St
Turning on heater...
House destroyed, heater automatically cleaned up
--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

COMPOSITION CHARACTERISTICS:
- Ownership: Parent owns child
- Lifetime: Child dies when parent dies
- Copying: Deep copy required
- Visibility: Child usually private
- Access: Only through parent
- Data type: Store objects directly

AGGREGATION CHARACTERISTICS:
- Ownership: Parent doesn't own child
- Lifetime: Independent lifetimes
- Copying: Shallow copy (references)
- Visibility: Child often shared
- Access: Direct or through parent
- Data type: Store pointers/references

COMPOSITION PATTERN USAGE:
- Car HAS-A Engine (strong)
- Student HAS-A Courses (strong)
- Company HAS-A Departments (strong)
- House HAS-A Rooms (strong)
- Use: When component is essential part

AGGREGATION PATTERN USAGE:
- Team HAS-A Players (weak)
- University HAS-A Students (weak)
- Library HAS-A Books (weak)
- Classroom HAS-A Desks (weak)
- Use: When component can exist independently

WHEN TO USE INSTEAD OF INHERITANCE:
1. Need flexibility in changing behavior
2. Sharing code with unrelated classes
3. Multiple types of same concept
4. Runtime polymorphism not needed
5. Cleaner design with fewer levels

================================================================================
*/

/*
================================================================================
COMMON MISTAKES
================================================================================

❌ MISTAKE 1: Aggregation when should be Composition
    Team team;
    Player p("Alice", 1);
    team.addPlayer(&p);  // p destroyed, dangling pointer!

✓ CORRECT:
    Player p = make_unique<Player>("Alice", 1);
    // Or ensure Player lives longer than Team

-----

❌ MISTAKE 2: Shallow copy in Composition
    class Student {
        vector<Course> courses;
    };
    Student s1, s2;
    s2 = s1;  // If Course has pointers, shallow copy!

✓ CORRECT:
    Implement proper copy constructor and assignment

-----

❌ MISTAKE 3: Using raw pointers in Composition
    class Car {
        Engine* engine;  // Dangerous!
    };

✓ CORRECT:
    class Car {
        unique_ptr<Engine> engine;  // Safe!
    };

-----

❌ MISTAKE 4: Deleting aggregated objects
    Team team;
    Player* p = new Player("Alice", 1);
    team.addPlayer(p);
    delete p;  // Team still has pointer!

✓ CORRECT:
    Team owns lifetime, or delete after team destroyed

-----

❌ MISTAKE 5: Too deep composition hierarchies
    Company -> Division -> Department -> Team -> Player
    // Difficult to navigate

✓ CORRECT:
    Keep hierarchies 2-3 levels deep

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: Library System
Book class with ISBN, title, author
Library aggregates Books
Track book availability

Exercise 2: Restaurant System
MenuItem with name, price, ingredients
Restaurant composes Menu (multiple MenuItems)
Calculate menu total

Exercise 3: Computer Assembly
CPU, GPU, RAM, Storage classes
Computer composes all components
Calculate total power consumption

Exercise 4: Board Game
Card class for game cards
Deck class composes Cards
Shuffling and drawing mechanics

Exercise 5: Playlist Manager
Song class with duration, artist
Playlist aggregates Song pointers
Add/remove/calculate total duration

Exercise 6: Factory Pattern
Product with name, price
Factory composes Products
Create and manage product inventory

Exercise 7: Observer Pattern
Observer objects in Subject
Subject composes list of Observers
Notify all observers of changes

Exercise 8: Graphics Scene
GameObject as base
SceneGraph composes GameObjects
Render all objects hierarchically

Exercise 9: Document Structure
Paragraph, Image, Table classes
Document composes content
Print document with formatting

Exercise 10: Route Planning
RoutePoint class
Route composes points
Calculate distance and time

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== COMPOSITION AND AGGREGATION "
          "==================\n\n";

  // Example 1: Composition - Car and Engine
  cout << "--- EXAMPLE 1: COMPOSITION (Car and Engine) ---\n";
  {
    Car car("Honda Civic", "Petrol", 100);
    car.displayInfo();
    car.startCar();
    car.stopCar();
  }
  cout << "\n";

  // Example 2: Aggregation - Team and Players
  cout << "--- EXAMPLE 2: AGGREGATION (Team and Players) ---\n";
  {
    Player p1("Alice", 1, 30);
    Player p2("Bob", 2, 25);

    Team team("Warriors");
    team.addPlayer(&p1);
    team.addPlayer(&p2);
    team.displayTeam();
  }
  cout << "\n";

  // Example 3: Composition - Student and Courses
  cout << "--- EXAMPLE 3: COMPOSITION (Student and Courses) ---\n";
  {
    Student student("S001", "Alice");
    student.enrollCourse(Course("CS201", "Data Structures", 3));
    student.enrollCourse(Course("CS202", "Algorithms", 3));
    student.displayCourses();
  }
  cout << "\n";

  // Example 4: Composition - Company and Departments
  cout << "--- EXAMPLE 4: COMPOSITION (Company and Departments) ---\n";
  {
    Company company("TechCorp");
    company.addDepartment(Department("Engineering", 50, 500000));
    company.addDepartment(Department("Sales", 30, 200000));
    company.displayInfo();
  }
  cout << "\n";

  // Example 5: Aggregation - University and Students
  cout << "--- EXAMPLE 5: AGGREGATION (University and Students) ---\n";
  {
    Student s1("S001", "Charlie");
    Student s2("S002", "Diana");

    University uni("Harvard");
    uni.enrollStudent(&s1);
    uni.enrollStudent(&s2);
    uni.displayRoster();
  }
  cout << "\n";

  // Example 6: Composite Pattern - File System
  cout << "--- EXAMPLE 6: COMPOSITE PATTERN (File System) ---\n";
  {
    Directory root("root");
    root.addComponent(new File("readme.txt", 1024));

    Directory *docs = new Directory("documents");
    docs->addComponent(new File("report.pdf", 2048));
    docs->addComponent(new File("notes.txt", 512));
    root.addComponent(docs);

    root.display();
    cout << "Total Size: " << root.getSize() << " bytes\n";
  }
  cout << "\n";

  // Example 7: Smart Pointer Composition
  cout << "--- EXAMPLE 7: SMART POINTER COMPOSITION ---\n";
  {
    House house("123 Main St", "Electric");
    house.displayInfo();
    house.turnOnHeater();
    house.turnOffHeater();
  }
  cout << "\n";

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== COMPOSITION AND AGGREGATION ==================

--- EXAMPLE 1: COMPOSITION (Car and Engine) ---
Car: Honda Civic
Engine: Petrol (100 HP)
Starting Honda...
Petrol engine started! Horsepower: 100
Stopping Honda...
Petrol engine stopped.
Car Honda destroyed

--- EXAMPLE 2: AGGREGATION (Team and Players) ---
Added Alice to team.
Added Bob to team.
=== Team: Warriors ===
Alice (#1) - Score: 30
Bob (#2) - Score: 25
Total Score: 55

--- EXAMPLE 3: COMPOSITION (Student and Courses) ---
Enrolled Alice in Data Structures
Enrolled Alice in Algorithms
=== Student: Alice (ID: S001) ===
CS201 - Data Structures (3 credits)
CS202 - Algorithms (3 credits)
Total Credits: 6

--- EXAMPLE 4: COMPOSITION (Company and Departments) ---
Added department: Engineering
Added department: Sales
=== Company: TechCorp ===
Department: Engineering | Employees: 50 | Budget: $500000
Department: Sales | Employees: 30 | Budget: $200000
Total Employees: 80
Total Budget: $700000

--- EXAMPLE 5: AGGREGATION (University and Students) ---
Enrolled student at Harvard
=== Harvard Roster ===
Total Students: 2

--- EXAMPLE 6: COMPOSITE PATTERN (File System) ---
[Dir] root/
  [File] readme.txt (1024 bytes)
  [Dir] documents/
    [File] report.pdf (2048 bytes)
    [File] notes.txt (512 bytes)
Total Size: 3584 bytes

--- EXAMPLE 7: SMART POINTER COMPOSITION ---
House constructed at 123 Main St
House at: 123 Main St
Turning on heater...
Engine started! Horsepower: 10
Turning off heater...
Engine stopped.
House destroyed, heater automatically cleaned up

================================================================================
*/
