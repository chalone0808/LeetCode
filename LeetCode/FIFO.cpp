#include <iostream>

using namespace std;

class MyCircularQueue {
private:
	int *q;
	int front, rear, size, FULL_TAG;
public:
	/** Initialize your data structure here. Set the size of the queue to be k. */
	MyCircularQueue(int k) {
		size = k;
		q = new int[size];
		front = 0;
		rear = 0;
		FULL_TAG = 0;
	}

	/** Insert an element into the circular queue. Return true if the operation is successful. */
	bool enQueue(int value) {
		if (rear == front && FULL_TAG) return false;
		q[rear] = value;
		rear = (rear + 1) % size;
		if (rear == front) FULL_TAG = 1;
		return true;
	}

	/** Delete an element from the circular queue. Return true if the operation is successful. */
	bool deQueue() {
		if (front == rear && !FULL_TAG) return false; //Ã»ÓÐÔªËØ
		front = (front + 1) % size;
		if (front == rear) FULL_TAG = 0;
		return true;
	}

	/** Get the front item from the queue. */
	int Front() {
		if (front == rear && !FULL_TAG) return -1;
		return q[front];
	}

	/** Get the last item from the queue. */
	int Rear() {
		if (front == rear && !FULL_TAG) return -1;
		return rear == 0 ? q[size - 1] : q[rear - 1];
	}

	/** Checks whether the circular queue is empty or not. */
	bool isEmpty() {
		return (front == rear && !FULL_TAG);
	}

	/** Checks whether the circular queue is full or not. */
	bool isFull() {
		return (front == rear && FULL_TAG);
	}
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */