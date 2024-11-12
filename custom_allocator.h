#include<iostream>
#include<memory>
template <class T>

struct c_allocator{
    using value_type = T;
    c_allocator() noexcept{
        pool_size=10;
        current_pool=nullptr;
        current_index=0;
        free_list=nullptr;
        allocated_count=0;
        restriction=false;
    }
    c_allocator(std::size_t max_elements) noexcept{
        pool_size=max_elements;
        current_pool=nullptr;
        current_index=0;
        free_list=nullptr;
        allocated_count=0;
        restriction=true;
    }
    template <class U> c_allocator(const c_allocator<U>&other) noexcept{
        pool_size=other.pool_size;
        current_pool=nullptr;
        current_index=other.current_index;
        free_list=nullptr;
        allocated_count=0;
    }
    
    T* allocate(std::size_t n){
        if(n>1){
            return static_cast<T*>(::operator new(n*sizeof(T)));
        }
        if (allocated_count >= pool_size && restriction) {
            throw std::runtime_error("c_allocator: Exceeded maximum number of elements.");
        }
        if(free_list){
            T* obj=reinterpret_cast<T*>(free_list);
            free_list=free_list->next;
            allocated_count;
            return obj;
        }
        if(current_pool==nullptr || current_index==pool_size){
            allocate_pool();
        }
        allocated_count++;
        return &current_pool[current_index++];
    }
    void deallocate(T*p, std::size_t n){
        if(n>1){
            ::operator delete(p);
            return;
        }
        Node* node=reinterpret_cast<Node*>(p);
        node->next=free_list;
        free_list=node;
        allocated_count--;
    }
   
    template <typename U>
    struct rebind {
        using other = c_allocator<U>;
    };

    struct Node{
        Node* next;
    };

    void allocate_pool(){
        current_pool=static_cast<T*>(::operator new(pool_size*sizeof(T)));
        current_index=0;
    }
    std::size_t pool_size;
    T* current_pool;
    std::size_t current_index;
    Node* free_list;
    std::size_t allocated_count;
    bool restriction;
};

template<class T, class U>
constexpr bool operator==(const c_allocator<T>& a1, const c_allocator<U>& a2) noexcept{
    return true;
}

template<class T, class U>
constexpr bool operator!=(const c_allocator<T>& a1, const c_allocator<U>& a2) noexcept{
    return false;
}