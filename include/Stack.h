
class Stack {
public:
    int height;
    char** stack;
    int capacity;

    Stack();
    void push(char* state);
    char* pop();
    bool isEmpty();
    void printStack();
};
