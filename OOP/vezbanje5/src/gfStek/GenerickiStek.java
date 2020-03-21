package gfStek;

public interface GenerickiStek<T> {
    T peek();
    T pop();
    void push(T v);
}
