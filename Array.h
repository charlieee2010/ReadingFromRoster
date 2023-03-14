
//Structures relating to arrays


template<class T>
class Array {

public:
    class InsufficientMemory { };
    class IndexOutOfRange { };

protected:
    T           *storage;
    int         storageCount;

public:
                Array(int size);
                ~Array();
    T           &operator [](int index);
};


