#include<iostream>
#include<stack>
using namespace std;

template<typename T>
class Queue {
protected:
    int maxSize;
    T* arr;
public:
    Queue(int s) {
        maxSize = s;
        arr = new T[s];
    }
    virtual void enqueue(T) = 0;
    virtual T dequeue() = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() = 0;
    virtual T peak() const = 0;
};

template<typename T>
class CircularQueue :public Queue<T> {
    int rear;
    int front;
public:
    CircularQueue(int s) :Queue<T>(s) {
        rear = front = -1;
    }
    ~CircularQueue() {
        delete[] this->arr;
    }
    void enqueue(T x) {
        if (!isFull()) {
            rear = (rear + 1) % this->maxSize;
            this->arr[rear] = x;
            if (front == -1)
                front = 0;
        }
        else {
            cerr << "\nQueue is Full";
        }
    }
    T dequeue() {
        if (!isEmpty()) {
            T data = this->arr[front];
            if (front == rear) {
                front = rear = -1;
            }
            else {
                front = (front + 1) % this->maxSize;
            }
            return data;
        }
        else {
            cerr << "\nQueue is Empty";
            return -1;
        }
    }
    bool isEmpty() const {
        return front == -1;
    }
    bool isFull() {
        return front == (rear + 1) % this->maxSize;
    }
    T peak() const {
        if (!isEmpty()) {
            return this->arr[front];
        }
        cerr << "\nQueue is Empty";
        return -1;
    }
    int size() {
        return ((rear - front + this->maxSize) % this->maxSize);
    }
    void display() {
        if (!isEmpty()) {
            for (int i = front; i != (rear + 1) % this->maxSize; i = (i + 1) % this->maxSize) {
                cout << this->arr[i] << " ";
            }
            cout << endl;
            cout << "Size: " << (rear - front + this->maxSize) % this->maxSize + 1 << endl;
            cout << "Rear: " << rear << endl;
            cout << "Front: " << front << endl;
            cout << "Peak is: " << peak() << endl;
        }
        else {
            cerr << "\nQueue is Empty";
        }
    }
    
};

template<typename T>
void reverseQueueByRecursion(CircularQueue<T> &q) {
    if (q.isEmpty()) {
        return;
    }

    T element = q.peak();
    q.dequeue();
    reverseQueueByRecursion(q);
    q.enqueue(element);
}

template<typename T>
void reverseQueueStack(CircularQueue<T>& q) {
    if (q.isEmpty())
        return;
    stack<T> obj;
    while (!q.isEmpty())
    {
        obj.push(q.peak());
        q.dequeue();
    }

    while (!obj.empty())
    {
        q.enqueue(obj.top());
        obj.pop();
    }
}

template<typename T>
void Reverse(CircularQueue<T>& q1)
{
    int maxsize = q1.size();
    int ms = maxsize;
    CircularQueue<T> q2(5);
    CircularQueue<T> q3(5);
    while (!q1.isEmpty())
    {
        while (maxsize != 1)
        {
            q2.enqueue(q1.peak());
            q1.dequeue();
            maxsize--;
        }
        q3.enqueue(q1.peak());
        q1.dequeue();
        ms--;
        maxsize = ms;
        while (!q2.isEmpty())
        {
            q1.enqueue(q2.peak());
            q2.dequeue();
        }

    }
    while (!q3.isEmpty())
    {
        q1.enqueue(q3.peak());
        q3.dequeue();
    }
}

int main()
{
    CircularQueue<char> obj(5); // Creating a queue with a maximum size of 5

    // Enqueue some elements
    obj.enqueue('A');
    obj.enqueue('B');
    obj.enqueue('C');
    obj.enqueue('D');
    obj.enqueue('E');

    // Display the state of the queue
    cout << "After enqueuing elements: " << endl;
    obj.display();

    // Dequeue some elements
    cout << "\nDequeueing two elements: " << endl;
    obj.dequeue();
    obj.dequeue();

    // Display the state of the queue after dequeuing
    obj.display();

    // Enqueue another element
    obj.enqueue('F');

    // Display the state of the queue after enqueuing
    cout << "\nAfter enqueuing 'F': " << endl;
    obj.display();

    cout << "\nAfter Reversing: \n";
    //reverseQueueByRecursion(obj);
    reverseQueueStack(obj);
    obj.display();
    //Reverse(obj);
    return 0;
}
