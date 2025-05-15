#include <iostream>
#include <thread>
#include <mutex>



class Data {
    int Int;
    double Double;
    std::mutex mut;
    void swapDefault(Data& other) {
        int tempI = Int;
        Int = other.Int;
        other.Int = tempI;

        double tempD = Double;
        Double = other.Double;
        other.Double = tempD;
    }
public:
    Data(int i, double d): Int(i), Double(d) {}
    friend void print(Data&, Data&);
    friend void swap1(Data&, Data&);
    friend void swap2(Data&, Data&);
    friend void swap3(Data&, Data&);
    friend void swap4(Data&, Data&);
};

void print(Data& a, Data& b) {
    std::cout << "1 - int: " << a.Int << " - duble: " << a.Double << std::endl;
    std::cout << "2 - int: " << b.Int << " - duble: " << b.Double << std::endl << std::endl;
}

void swap1(Data& a, Data& b) {
    a.mut.lock();
    b.mut.lock();

    a.swapDefault(b);

    a.mut.unlock();
    b.mut.unlock();
}

void swap2(Data& a, Data& b) {
    std::unique_lock<std::mutex> m1(a.mut, std::defer_lock);
    std::unique_lock<std::mutex> m2(b.mut, std::defer_lock);
    a.swapDefault(b);
}

void swap3(Data& a, Data& b) {
    std::scoped_lock lc{ a.mut, b.mut };
    a.swapDefault(b);
}

void swap4(Data& a, Data& b) {
    std::lock(a.mut, b.mut);
    std::lock_guard<std::mutex>(a.mut, std::adopt_lock);
    std::lock_guard<std::mutex>(b.mut, std::adopt_lock);
    a.swapDefault(b);
}

int main()
{
    Data data1( 1, 2.4 );
    Data data2(7, 4.3);
    print(data1, data2);

    swap1(data1, data2);
    print(data1, data2);

    swap2(data1, data2);
    print(data1, data2);

    swap3(data1, data2);
    print(data1, data2);

    swap4(data1, data2);
    print(data1, data2);


}
