#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class CPUProcess {
private:
    int process_id;
    string process_name;
    double time_needed;
public:
    CPUProcess() {
        process_name ="";
        process_id = 0;
        time_needed = 0;
    };
    CPUProcess(int id, string pn, double time_need) {
        process_name = pn;
        process_id = id;
        time_needed = time_need;
    }
    void printProcessInfo();
    void setprocess_id(int id) {
        process_id = id;
    }
    int getprocess_id() {
        return process_id;
    }
    void setprocess_name(string name) {
        process_name = name;
    }
    string getprocess_name() {
        return process_name;
    }
    void settime_needed(double time) {
        time_needed = time;
    }
    double gettime_needed() {
        return time_needed;
    }
};
void CPUProcess::printProcessInfo() {
    cout << "the process ID: " << getprocess_id() << endl;
    cout << "the process name: " << getprocess_name() << endl;
    cout << "the time needed: " << gettime_needed() << endl;
}

template <class T>
class ProcessNode {
public:
    T data;
    ProcessNode<T>* next;
    ProcessNode(T datainput) {
        data = datainput;
        next = NULL;
    }
};

template <class T>
class StackLL {
    ProcessNode<T>* top;
public:
    StackLL() {
        top = NULL;
    }
    bool isemptystack() {
        return top == NULL;
    }
    bool  emptyStack();
    bool pushProcess(T process);
    bool  stackOfProcesses();
    CPUProcess lateProcess();
};
template <class T>
bool StackLL<T>::emptyStack() {
    if (top == NULL) {
        cout << "the stack empty" << endl;
        return false;
    }
    else {
        lateProcess();
        return true;
    }
}
template <class T>
bool StackLL<T>::pushProcess(T process) {
    ProcessNode<T>* newNode = new ProcessNode<T>(process);
    if (isemptystack()) {
        cout << "it is empty stack" << endl;
        newNode->next = NULL;
        top = newNode;
        return true;
    }
    else {
        newNode->next = top;
        top = newNode;
        return false;
    }
}
template <class T>
bool StackLL<T>::stackOfProcesses() {
    ProcessNode<T>* temp = top;
    if (isemptystack()) {
        cout << "the stack is empty already so, no element to print" << endl;
        return false;
    }
    else {

        while (temp != NULL) {
            temp->data.printProcessInfo();
            temp = temp->next;
        }
        return true;
    }
}
template <class T>
CPUProcess StackLL<T>::lateProcess() {
    ProcessNode<T>* temp = top;
    int count = 0;
    T process;
    while (temp != NULL) {
        count += 1;
        temp = temp->next;
    }
    cout << "the number of the process in the stack is:" << count << endl;
    if (isemptystack()) {
        cout << "there is no process in the stack" << endl;
        return process;
    }
    else {
        return top->data;
    }
}

template <class T>
class QueueLL {
    ProcessNode<T>* head;
    ProcessNode<T>* front;
    ProcessNode<T>* rear;
    int capacity = 3;
public:
    QueueLL() {
        head = NULL;
        front = rear = NULL;
    }
    bool isemptyqueue() {
        return head == NULL;
    }
    bool execute(T process);
    CPUProcess runProcess();
    void cpuSchedule();
    void killProcess(StackLL <CPUProcess>* sll);
    bool emptyqueue();
};

template <class T>
// the complexity
// T(n)=6+2+n+2n+n+n+3n+2n+n+n+3n+n+n+1+1+1+1+1+1
// Big O = O(n) 
bool QueueLL<T>::execute(T process) {
    ProcessNode<T>* newNode = new ProcessNode<T>(process); // 1
    if (front == NULL) { // 1
        head = newNode; // 1
        front = rear = newNode; // 2
        newNode->next = NULL;// 1
    }
    else {
        ProcessNode <T>* temp = head; // 1
        ProcessNode <T>* ptr = NULL; //1
        while (temp != NULL) {  // n
            if (process.getprocess_id() == temp->data.getprocess_id() && ptr == NULL) { // first node    // 2n 
                ptr = head; // n
                cout << "the process already exists" << endl; // 1n
                temp->data.printProcessInfo(); // 3n
                break;
            }
            if (process.getprocess_id() == temp->data.getprocess_id() && ptr != NULL) { //more node   // 2n
                ptr = temp;  //1n
                cout << "the process already exists" << endl;// 1n
                temp->data.printProcessInfo(); // 3n
                break;
            }
            ptr = temp; //n
            temp = temp->next; //n
        }
        if (process.getprocess_id() != ptr->data.getprocess_id()) {  //1
            newNode->next = NULL; // 1
            ptr->next = newNode; // 1
            rear = newNode; //1
            return false; //1
        }
        return true; //1
    }
}

template <class T>
CPUProcess QueueLL<T>::runProcess() {
    T process;
    if (front == NULL) {
        cout << "the queue is empty" << endl;
    }
    else {
        if (front->data.gettime_needed() <= capacity && front == rear) {
            T datadeleted = front->data;
            delete front;
            front = NULL;
            rear = NULL;
            cout << "Process Execution is Completed" << endl;
            return datadeleted;
        }
        else if (front->data.gettime_needed() <= capacity && front != rear) {
            ProcessNode<T>* temp1 = front;
            T dataf = temp1->data;
            front = front->next;
            delete temp1;
            return dataf;
        }
        else if (front->data.gettime_needed() > capacity && front != rear) {
            cout << "the process is not excuted" << endl;
            return process;
        }
    }
}

template <class T>
void QueueLL<T>::cpuSchedule() {
    ProcessNode<T>* temp1 = front;
    if (isemptyqueue()) {
        cout << "there is no values in the queue to print" << endl;
    }
    else {
        while (temp1 != NULL) {
            temp1->data.printProcessInfo();
            temp1 = temp1->next;
        }
    }
}

template <class T>
void QueueLL<T>::killProcess(StackLL <CPUProcess>* sll) {
    if (isemptyqueue()) {
        cout << "there is no element in the queue" << endl;
    }
    else {
        if (front->data.gettime_needed() > capacity) {
            ProcessNode<T>* temp1 = front;
            T datad = front->data;
            front = front->next;
            delete temp1;
            sll->pushProcess(datad);
        }
    }
}

template <class T>
bool QueueLL<T>::emptyqueue() {
    StackLL <CPUProcess> sll;

    if (head == NULL) {
        cout << "the queue is empty!" << endl;
        return false;
    }
    else {
        killProcess(&sll);
        return true;
    }
}
class node {
    int data;
    node* left;
    node* right;
public:
    node(int d) {
        data = d;
        left = right = NULL;
    }
    void setdata(int d) {
        data = d;
    }
    int getdata() {
        return data;
    }
    void setleft(node* ptr) {
        left = ptr;
    }
    void setright(node* ptr1) {
        right = ptr1;
    }
    node* getleft() {
        return left;
    }
    node* getright() {
        return right;
    }
};

class bst {
public:
    node* root;
    bst() {
        root = NULL;
    }
    node* insert(node* r, int datai);
    void insert(int datai);
    void preorder(node* r);
};

node* bst::insert(node* r, int datai) {
    if (r == NULL) {
        node* newnode = new node(datai);
        r = newnode;
    }
    else {
        if (r->getdata() < datai) {
            r->setright(insert(r->getright(), datai));
        }
        else {
            r->setleft(insert(r->getleft(), datai));
        }
    }
    return r;
}

void bst::insert(int datai) {
    root = insert(root, datai);
}

void bst::preorder(node* r) {
    if (r == NULL) {
        return;
    }
    else {
        cout << r->getdata() << "\t";
        preorder(r->getleft());
        preorder(r->getright());
    }
}

int main() {
    CPUProcess p1(1, "p1", 10);
    CPUProcess p2(2, "p2", 4);
    CPUProcess p3(3, "p3", 1);
    CPUProcess p4(4, "p4", 5);
    CPUProcess p5(5, "p5", 15);
   
    QueueLL <CPUProcess>qll;
    qll.execute(p1);
    qll.execute(p2);
    qll.execute(p3);
    qll.execute(p4);
    qll.execute(p5);

    qll.cpuSchedule();
    StackLL<CPUProcess>sll;
    qll.killProcess(&sll);
    cout << "=================== process-kill=====================" << endl;;
    sll.stackOfProcesses();
    sll.lateProcess().printProcessInfo();
    cout << "===================process-run=======================" << endl;
    qll.runProcess().printProcessInfo();
    bst tree1;
    int x;
    cout << "entre the number of nodes to insert:" << endl;
    cin >> x;
    for (int i = 1; i <= x; i++) {
        int value;
        cout << "entre the value:" << endl;
        cin >> value;
        tree1.insert(value);
    }
    tree1.preorder(tree1.root);
    return 0;
}