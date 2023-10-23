#include <iostream>
using namespace std;

class MyStack {
public:
    struct MyNode {
        int mValue;
        MyNode* mNext = nullptr;

        MyNode(int aValue) : mValue(aValue) {}
    };

    struct MyException {
        string mDescription;

        MyException(string aDescription) : mDescription(aDescription) {}
    };

    MyStack() : mMaxSize(10), mHead(nullptr), mCurrentSize(0) {}

    MyStack(int aSize) : mMaxSize(aSize), mHead(nullptr), mCurrentSize(0) {}

    ~MyStack() {
        while (mHead) {
            MyNode* temp = mHead;
            mHead = mHead->mNext;
            delete temp;
        }
    }

    void Pop() {
        if (!mHead) {
            throw MyException("Cannot pop from an empty stack.");
        }

        MyNode* temp = mHead;
        mHead = mHead->mNext;
        delete temp;
        mCurrentSize--;
    }

    void Push(int aValue) {
        if (mCurrentSize == mMaxSize) {
            throw MyException("Cannot push to a full stack.");
        }

        if (Contains(aValue)) {
            cout << "Value already exists. Only unique values are allowed.\n";
            return;
        }

        MyNode* newNode = new MyNode(aValue);
        newNode->mNext = mHead;
        mHead = newNode;
        mCurrentSize++;
    }

    int Top() {
        if (!mHead) {
            throw MyException("Cannot get the top of an empty stack.");
        }

        return mHead->mValue;
    }

    bool IsEmpty() {
        return mHead == nullptr;
    }

private:
    MyNode* mHead;
    unsigned int mMaxSize;
    unsigned int mCurrentSize;

    bool Contains(int aValue) {
        MyNode* temp = mHead;
        while (temp) {
            if (temp->mValue == aValue) return true;
            temp = temp->mNext;
        }
        return false;
    }
};

int main() {
    MyStack stack(3);

    try {
        stack.Push(10);
        stack.Push(20);
        stack.Push(30);
        cout << "Top value: " << stack.Top() << endl; // should display 30
        stack.Push(40);  // should give error due to size limit
        stack.Push(10);  // should give error due to uniqueness
        stack.Pop();
        stack.Pop();
        cout << "Top value after 2 pops: " << stack.Top() << endl; // should display 10
        stack.Pop();
        stack.Pop(); // should give error as the stack is empty
    } catch (const MyStack::MyException& e) {
        cout << "Error: " << e.mDescription << endl;
    }

    return 0;
}
