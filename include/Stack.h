
class Stack {
public:
    int height;
    char** stack;
    int capacity;

    Stack();
    ~Stack();
    void push(char* state);
    char* pop();
    bool isEmpty();
    void printStack();
};
