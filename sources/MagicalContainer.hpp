#pragma once
#include <set>
#include  <iostream>
namespace ariel
{
    struct node
    {
        int data;
        node* next;
        node* prev;
        node* primeNext;
        node* primePrev;
        node(int element){
            data=element;
            next=nullptr;
            prev =nullptr;
            primeNext= nullptr;
            primePrev =nullptr;
        }
        
    };
    struct cmp {
    bool operator() (node* a, node* b) const {
        //std::cout<<a->data<<"<"<<b->data<< std::endl;
        return a->data < b->data;
    }
};

    class MagicalContainer
    {
    private:
        node* tail;
        node* head;
        node* primetail;
        node* primehead;
        std::set<node*,cmp> primes;
        std::set<node*,cmp> numbers;

        void addToNumbers(node*);
        void addtoPrimes(node*);
        void removeFromNumbers(node*);
        void removeFromPrimes(node*);
    public:
        MagicalContainer();
        ~MagicalContainer();
        void addElement(int);
        int size();
        void removeElement(int);
        class AscendingIterator{
            private:
            MagicalContainer* container;//just in order to identify which container we are in
            node* curr;
            public:
                AscendingIterator(MagicalContainer&);
                ~AscendingIterator();
                AscendingIterator begin();
                AscendingIterator end();
                AscendingIterator& operator=(const AscendingIterator&);
                AscendingIterator& operator++();
                bool operator==(const AscendingIterator&)const;
                bool operator<(const AscendingIterator&)const;
                bool operator>(const AscendingIterator&)const;
                int  operator*()const;
        };
        class SideCrossIterator{
            private:
            node* max;
            node* min;
            bool fromMin;
            MagicalContainer* container;
            public:
                SideCrossIterator(MagicalContainer&);
                ~SideCrossIterator();
                SideCrossIterator begin();
                SideCrossIterator end();
                SideCrossIterator& operator=(const SideCrossIterator&);
                SideCrossIterator& operator++();
                bool operator==(const SideCrossIterator&)const;
                bool operator<(const SideCrossIterator&)const;
                bool operator>(const SideCrossIterator&)const;
                int  operator*()const;
        };
    
    
    class PrimeIterator{
            private:
            MagicalContainer* container;
            node* curr;
            public:
                PrimeIterator(MagicalContainer&);
                ~PrimeIterator();
                PrimeIterator begin();
                PrimeIterator end();
                PrimeIterator& operator=(const PrimeIterator&);
                PrimeIterator& operator++();
                bool operator==(const PrimeIterator&)const;
                bool operator<(const PrimeIterator&)const;
                bool operator>(const PrimeIterator&)const;
                int  operator*()const;
        };
    };
    
}
