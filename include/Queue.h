class Queue{
    private:
        int size;
        int maxSize;
        char** queue;
    public:
        // Constructor
        Queue(int maxSize);
        // Selectores
        int getSize();
        int getMaxSize();
        char** getQueue();
        // Modificadores
        void push(char* element);
        char* pop();
        void addMemory();
        // Otros
        void print();
};