#include<iostream>
#include<memory>
template<typename T, typename Alloc=std::allocator<T>>
class my_list{

private:
    class Node{
    public:
        T value;
        Node* p_next;
        Node(const T& val){
            value=val;
            p_next=nullptr;
        }
    };
    using NodeAlloc = typename Alloc::template rebind<Node>::other;
    using nodeAllocTraits = std::allocator_traits<NodeAlloc>;

    Node* head;
    Node* tail;
    std::size_t size_;
    NodeAlloc allocator; 
public:
    
    my_list(){
        head=nullptr;
        tail=nullptr;
        size_=0;
    }
    my_list(const Alloc& alloc){
        head=nullptr;
        tail=nullptr;
        size_=0;
        allocator=NodeAlloc(alloc);
    }
    ~my_list(){
        clear();
    }
    void push_back(const T& value){
        Node* newNode = nodeAllocTraits::allocate(allocator, 1);
        nodeAllocTraits::construct(allocator, newNode, value);


        if(!head){
            head=tail=newNode;
        }
        else{
            tail->p_next=newNode;
            tail=newNode;
        }
        ++size_;
    }
    std::size_t size() const{return size_;}
    bool empty() const {return size_==0;}
    class Iterator{
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Node* ptr) : current(ptr) {}

        T& operator*() const { return current->value; }
        T* operator->() const { return &current->value; }

        // Префиксный инкремент
        Iterator& operator++() {
            current = current->p_next;
            return *this;
        }

        // Постфиксный инкремент
        Iterator operator++(int) {
            Iterator temp = *this;
            current = current->p_next;
            return temp;
        }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }

    private:
        Node* current;
    };
    Iterator begin(){
        return Iterator(head);
    }
    Iterator end(){
        return Iterator(nullptr);
    }
    void clear(){
        Node* current=head;
        while(current){
            Node* temp=current->p_next;
            nodeAllocTraits::destroy(allocator, current);
            nodeAllocTraits::deallocate(allocator, current, 1);
            current=temp;
        }
        head=tail=nullptr;
        size_=0;
    }

};