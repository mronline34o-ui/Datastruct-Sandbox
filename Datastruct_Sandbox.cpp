/**
 * PROJECT: DataStruct Sandbox - Enhanced Practical Learning Workbench
 * Enhancements Added:
 *   1. Crash-Proof Input Validation (safely handles letters/symbols without freezing)
 *   2. Live Heap Memory Tracing ([HEAP LOG] prints exact allocation & deallocation addresses)
 *   3. Session Analytics Dashboard (tracks peak size, current nodes, and total operations)
 *   4. Built-in Theory & Time Complexity Reference (O(1) vs O(N) viva reference guide)
 *   5. Line 81 fix applied (curr->data pointer access)
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// ============================================================================
// UTILITY: Crash-Proof Input Validator
// ============================================================================
int getValidatedInt(const string& promptMessage) {
    int value;
    while (true) {
        cout << promptMessage;
        if (cin >> value) {
            return value;
        } else {
            cout << "  [!] Invalid input! Please enter a valid whole number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// ============================================================================
// WORKBENCH 1: Enhanced Stack (LIFO) with Live Memory Tracing & Analytics
// ============================================================================
struct StackNode {
    int data;
    StackNode* next;

    StackNode(int val) : data(val), next(nullptr) {
        cout << "  [HEAP LOG (+)] Node with value " << val 
             << " allocated at memory address: " << this << "\n";
    }

    ~StackNode() {
        cout << "  [HEAP LOG (-)] Node with value " << data 
             << " freed from memory address: " << this << "\n";
    }
};

class InteractiveStack {
private:
    StackNode* top;
    int size;
    int peakSize;
    int totalPushes;
    int totalPops;

public:
    InteractiveStack() : top(nullptr), size(0), peakSize(0), totalPushes(0), totalPops(0) {}

    ~InteractiveStack() {
        while (top != nullptr) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(int val) {
        StackNode* newNode = new StackNode(val);
        newNode->next = top;
        top = newNode;
        size++;
        totalPushes++;
        if (size > peakSize) peakSize = size;
        cout << "  [SUCCESS] Pushed " << val << " onto Stack Top.\n";
    }

    void pop() {
        if (top == nullptr) {
            cout << "  [!] Stack Underflow! Cannot pop from an empty stack.\n";
            return;
        }
        StackNode* temp = top;
        top = top->next;
        delete temp; // Triggers ~StackNode() destructor with memory log
        size--;
        totalPops++;
        cout << "  [SUCCESS] Element popped from Stack Top.\n";
    }

    void peek() const {
        if (top == nullptr) {
            cout << "  [!] Stack is empty.\n";
            return;
        }
        cout << "  [PEEK] Top element is: " << top->data 
             << " (Memory Address: " << top << ")\n";
    }

    void display() const {
        cout << "\n  +--------------------------------------------------------------+\n";
        cout << "  | LIVE STACK WORKBENCH (LIFO - Last In, First Out)             |\n";
        cout << "  +--------------------------------------------------------------+\n";
        cout << "  | Current Size: " << setw(3) << size 
             << " | Peak Size: " << setw(3) << peakSize 
             << " | Total Pushes: " << setw(3) << totalPushes 
             << " | Total Pops: " << setw(3) << totalPops << " |\n";
        cout << "  +--------------------------------------------------------------+\n";
        
        if (top == nullptr) {
            cout << "    [TOP] -> [ EMPTY STACK ]\n";
        } else {
            cout << "    [TOP] -> ";
            StackNode* curr = top;
            while (curr != nullptr) {
                cout << "[" << curr->data << "]" << (curr->next ? " -> " : "");
                curr = curr->next;
            }
            cout << " -> NULL\n";
        }
        cout << "  ----------------------------------------------------------------\n";
    }
};

// ============================================================================
// WORKBENCH 2: Enhanced Queue (FIFO) with Live Memory Tracing & Analytics
// ============================================================================
struct QueueNode {
    int data;
    QueueNode* next;

    QueueNode(int val) : data(val), next(nullptr) {
        cout << "  [HEAP LOG (+)] Node with value " << val 
             << " allocated at memory address: " << this << "\n";
    }

    ~QueueNode() {
        cout << "  [HEAP LOG (-)] Node with value " << data 
             << " freed from memory address: " << this << "\n";
    }
};

class InteractiveQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int size;
    int peakSize;
    int totalEnqueues;
    int totalDequeues;

public:
    InteractiveQueue() : front(nullptr), rear(nullptr), size(0), peakSize(0), totalEnqueues(0), totalDequeues(0) {}

    ~InteractiveQueue() {
        while (front != nullptr) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(int val) {
        QueueNode* newNode = new QueueNode(val);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
        totalEnqueues++;
        if (size > peakSize) peakSize = size;
        cout << "  [SUCCESS] Enqueued " << val << " at Queue Rear.\n";
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "  [!] Queue Underflow! Cannot dequeue from an empty queue.\n";
            return;
        }
        QueueNode* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp; // Triggers ~QueueNode() destructor
        size--;
        totalDequeues++;
        cout << "  [SUCCESS] Element dequeued from Queue Front.\n";
    }

    void display() const {
        cout << "\n  +--------------------------------------------------------------+\n";
        cout << "  | LIVE QUEUE WORKBENCH (FIFO - First In, First Out)            |\n";
        cout << "  +--------------------------------------------------------------+\n";
        cout << "  | Current Size: " << setw(3) << size 
             << " | Peak Size: " << setw(3) << peakSize 
             << " | Total Enq: " << setw(4) << totalEnqueues 
             << " | Total Deq: " << setw(4) << totalDequeues << " |\n";
        cout << "  +--------------------------------------------------------------+\n";
        
        if (front == nullptr) {
            cout << "    [FRONT] -> [ EMPTY QUEUE ] <- [REAR]\n";
        } else {
            cout << "    [FRONT] -> ";
            QueueNode* curr = front;
            while (curr != nullptr) {
                cout << "[" << curr->data << "]" << (curr->next ? " -> " : "");
                curr = curr->next;
            }
            cout << " <- [REAR]\n";
        }
        cout << "  ----------------------------------------------------------------\n";
    }
};

// ============================================================================
// WORKBENCH 3: Enhanced Singly Linked List with Explicit Node Tracing
// ============================================================================
struct LinkedListNode {
    int data;
    LinkedListNode* next;

    LinkedListNode(int val) : data(val), next(nullptr) {
        cout << "  [HEAP LOG (+)] Linked List Node (" << val 
             << ") created at address: " << this << "\n";
    }

    ~LinkedListNode() {
        cout << "  [HEAP LOG (-)] Linked List Node (" << data 
             << ") safely destroyed at address: " << this << "\n";
    }
};

class InteractiveLinkedList {
private:
    LinkedListNode* head;
    int count;

public:
    InteractiveLinkedList() : head(nullptr), count(0) {}

    ~InteractiveLinkedList() {
        clear();
    }

    void clear() {
        while (head != nullptr) {
            LinkedListNode* temp = head;
            head = head->next;
            delete temp;
        }
        count = 0;
    }

    void insertAtTail(int val) {
        LinkedListNode* newNode = new LinkedListNode(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            LinkedListNode* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
        count++;
        cout << "  [SUCCESS] Inserted node " << val << " at the list tail.\n";
    }

    void deleteByValue(int val) {
        if (head == nullptr) {
            cout << "  [!] List is empty. Nothing to delete.\n";
            return;
        }
        if (head->data == val) {
            LinkedListNode* temp = head;
            head = head->next;
            delete temp;
            count--;
            cout << "  [SUCCESS] Deleted " << val << " from the head of the list.\n";
            return;
        }

        LinkedListNode* prev = head;
        LinkedListNode* curr = head->next;
        bool found = false;
        while (curr != nullptr) {
            if (curr->data == val) {
                prev->next = curr->next;
                delete curr;
                count--;
                found = true;
                cout << "  [SUCCESS] Unlinked and deleted node " << val << " from memory.\n";
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        if (!found) {
            cout << "  [!] Value " << val << " not found in the Linked List.\n";
        }
    }

    void display() const {
        cout << "\n  +--------------------------------------------------------------+\n";
        cout << "  | LIVE SINGLY LINKED LIST WORKBENCH                            |\n";
        cout << "  +--------------------------------------------------------------+\n";
        cout << "    Total Nodes Linked: " << count << "\n";
        
        if (head == nullptr) {
            cout << "    [HEAD] -> NULL\n";
        } else {
            cout << "    [HEAD] -> ";
            LinkedListNode* curr = head;
            while (curr != nullptr) {
                cout << "[" << curr->data << " | Next: " << curr->next << "] -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
        }
        cout << "  ----------------------------------------------------------------\n";
    }
};

// ============================================================================
// WORKBENCH 4: Memory Pointer Mutator Sandbox
// ============================================================================
void pointerSwapOrModify(int *a, int *b) {
    int temp = *a;
    *a = *b * 2;     // Double b and store into memory of a
    *b = temp + 10;  // Add 10 to old a and store into memory of b
}

void runPointerSandbox() {
    cout << "\n+------------------------------------------------------------+\n";
    cout << "| MEMORY POINTER MUTATOR SANDBOX                             |\n";
    cout << "+------------------------------------------------------------+\n";
    cout << "  Demonstrates in-place mutation of variables via raw pointers.\n\n";

    int x = getValidatedInt("  Enter initial integer for variable X: ");
    int y = getValidatedInt("  Enter initial integer for variable Y: ");

    cout << "\n  [Memory State Before Function Call]\n";
    cout << "    Address of X (" << &x << ") holds value: " << x << "\n";
    cout << "    Address of Y (" << &y << ") holds value: " << y << "\n";

    pointerSwapOrModify(&x, &y);

    cout << "\n  [Memory State After pointerSwapOrModify(&x, &y)]\n";
    cout << "    Address of X (" << &x << ") now holds: " << x << " (*b * 2)\n";
    cout << "    Address of Y (" << &y << ") now holds: " << y << " (old *a + 10)\n";
    cout << "  *(Notice how memory addresses remained identical while values mutated in-place!)*\n";
}

// ============================================================================
// WORKBENCH 5: Variadic Function Playground (va_list)
// ============================================================================
int computeVariadicSum(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

void runVariadicSandbox() {
    cout << "\n+------------------------------------------------------------+\n";
    cout << "| VARIADIC FUNCTION PLAYGROUND (va_list)                     |\n";
    cout << "+------------------------------------------------------------+\n";
    cout << "  Demonstrates passing variable numbers of arguments using '...'\n\n";

    int count = getValidatedInt("  How many numbers do you want to pass? (Choose 3, 5, or 10): ");
    while (count != 3 && count != 5 && count != 10) {
        cout << "  [!] For this demonstration, please choose exactly 3, 5, or 10 arguments.\n";
        count = getValidatedInt("  Count (3, 5, or 10): ");
    }

    vector<int> nums(count);
    cout << "  Enter " << count << " space-separated integers:\n";
    for (int i = 0; i < count; i++) {
        nums[i] = getValidatedInt("    Element [" + to_string(i + 1) + "]: ");
    }

    int result = 0;
    if (count == 3) {
        result = computeVariadicSum(3, nums[0], nums[1], nums[2]);
    } else if (count == 5) {
        result = computeVariadicSum(5, nums[0], nums[1], nums[2], nums[3], nums[4]);
    } else if (count == 10) {
        result = computeVariadicSum(10, nums[0], nums[1], nums[2], nums[3], nums[4],
                                       nums[5], nums[6], nums[7], nums[8], nums[9]);
    }

    cout << "\n  [Variadic Output] Successfully processed " << count 
         << " arguments through single va_list loop.\n";
    cout << "  Total Sum = " << result << "\n";
}

// ============================================================================
// WORKBENCH 6: Interactive Theory & Time Complexity Guide (Viva Helper)
// ============================================================================
void displayTheoryGuide() {
    cout << "\n+--------------------------------------------------------------------+\n";
    cout << "| DATA STRUCTURES TIME COMPLEXITY & MEMORY CHEAT SHEET               |\n";
    cout << "+--------------------------------------------------------------------+\n";
    cout << "  STRUCTURE   | OPERATION   | TIME COMPLEXITY | WHY / EXPLANATION     \n";
    cout << "  ------------+-------------+-----------------+----------------------\n";
    cout << "  Stack       | Push / Pop  | O(1) Constant   | Top pointer shifts directly\n";
    cout << "  Queue       | Enq / Deq   | O(1) Constant   | Rear & Front pointers update\n";
    cout << "  Linked List | Insert Tail | O(N) or O(1)    | Traverse to end or use tail ptr\n";
    cout << "  Linked List | Delete Node | O(N) Linear     | Search element + relink ptrs\n";
    cout << "  Pointers    | Mutate Value| O(1) Constant   | Direct hardware RAM access\n";
    cout << "  Variadic    | va_list Sum | O(N) Linear     | Sequential stack-frame crawl\n";
    cout << "+--------------------------------------------------------------------+\n";
}

// ============================================================================
// MAIN APPLICATION CONTROLLER
// ============================================================================
int main() {
    InteractiveStack myStack;
    InteractiveQueue myQueue;
    InteractiveLinkedList myList;

    int choice = -1;

    while (true) {
        cout << "\n====================================================================\n";
        cout << "        DATASTRUCT SANDBOX: PRACTICAL LEARNING WORKBENCH            \n";
        cout << "====================================================================\n";
        cout << "  [1] Interactive Stack Workbench (Push, Pop, Peek, LIFO Analytics)\n";
        cout << "  [2] Interactive Queue Workbench (Enqueue, Dequeue, FIFO Analytics)\n";
        cout << "  [3] Interactive Linked List Workbench (Insert, Delete, Node RAM)\n";
        cout << "  [4] Memory Pointer Mutator Sandbox (In-Place Address Editing)\n";
        cout << "  [5] Variadic Function Playground (Variable Argument Lists)\n";
        cout << "  [6] View Theory & Time Complexity Reference Guide (Viva Prep)\n";
        cout << "  [0] Exit Application\n";
        cout << "--------------------------------------------------------------------\n";

        choice = getValidatedInt("  Select workbench option (0-6): ");

        if (choice == 0) {
            cout << "\n  Exiting DataStruct Sandbox. Best of luck with your evaluation!\n";
            break;
        }

        switch (choice) {
            case 1: {
                int subChoice = -1;
                while (subChoice != 0) {
                    myStack.display();
                    cout << "\n  Stack Actions: [1] Push [2] Pop [3] Peek [0] Back to Main Menu\n";
                    subChoice = getValidatedInt("  Choice: ");
                    if (subChoice == 1) {
                        int val = getValidatedInt("  Enter integer value to push: ");
                        myStack.push(val);
                    } else if (subChoice == 2) {
                        myStack.pop();
                    } else if (subChoice == 3) {
                        myStack.peek();
                    }
                }
                break;
            }
            case 2: {
                int subChoice = -1;
                while (subChoice != 0) {
                    myQueue.display();
                    cout << "\n  Queue Actions: [1] Enqueue [2] Dequeue [0] Back to Main Menu\n";
                    subChoice = getValidatedInt("  Choice: ");
                    if (subChoice == 1) {
                        int val = getValidatedInt("  Enter integer value to enqueue: ");
                        myQueue.enqueue(val);
                    } else if (subChoice == 2) {
                        myQueue.dequeue();
                    }
                }
                break;
            }
            case 3: {
                int subChoice = -1;
                while (subChoice != 0) {
                    myList.display();
                    cout << "\n  Linked List Actions: [1] Insert Tail [2] Delete by Value [3] Clear List [0] Back\n";
                    subChoice = getValidatedInt("  Choice: ");
                    if (subChoice == 1) {
                        int val = getValidatedInt("  Enter integer value to insert: ");
                        myList.insertAtTail(val);
                    } else if (subChoice == 2) {
                        int val = getValidatedInt("  Enter integer value to delete: ");
                        myList.deleteByValue(val);
                    } else if (subChoice == 3) {
                        myList.clear();
                        cout << "  [SUCCESS] Cleared Linked List from heap memory.\n";
                    }
                }
                break;
            }
            case 4:
                runPointerSandbox();
                cout << "\n  Press Enter to return to main menu...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            case 5:
                runVariadicSandbox();
                cout << "\n  Press Enter to return to main menu...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            case 6:
                displayTheoryGuide();
                cout << "\n  Press Enter to return to main menu...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            default:
                cout << "  [!] Invalid choice. Please choose a number between 0 and 6.\n";
                break;
        }
    }

    return 0;
}