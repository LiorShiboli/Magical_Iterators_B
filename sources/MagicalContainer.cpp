#include "MagicalContainer.hpp"
#include <iostream>
#include <stdexcept>
namespace ariel
{
    int primalityTest(int num){
        if (num<=1)
        {
            return false;
        }
        if (num==2)
        {
            return true;
        }
        if (num%2==0)
        {
            return false;
        }
        
        
        for (int i = 3; i*i <= num ; i+=2)
        {
            if (num%i ==0)
            {
                return false;
            }
            
        }
        return true;
        
        
    }
    MagicalContainer::MagicalContainer(){
        tail = nullptr;
        head = nullptr;
        primetail = nullptr;
        primehead = nullptr;
    }
    MagicalContainer::~MagicalContainer(){
        node* tmp;
        while (head!=nullptr)
        {
            tmp = head;
            head = head->next;
            free(tmp);

        }
    }
    void MagicalContainer::addElement(int element){
        
        node* curr = new node(element);
        if (numbers.contains(curr))
        {
            return;
        }
        bool isPrime = primalityTest(element);
        addToNumbers(curr);
        if (isPrime)
        {
            
            addtoPrimes(curr);
        }
        
        
        
    }
    void MagicalContainer::addToNumbers(node* curr){

        if (head==nullptr)
        {
            head = curr;
            tail = curr;
            numbers.insert(curr);
            return;
        }
        if (head->data>curr->data)
        {
            head->prev = curr;
            curr->next = head;
            head = curr;
            numbers.insert(curr);
            return;
        }
        if (curr->data>tail->data)
        {
            curr->prev = tail;
            tail->next = curr;
            tail = curr;
            numbers.insert(curr);
            return;
        }
        
        
        node* prev = (*numbers.lower_bound(curr))->prev;
        curr->next = prev->next;
        prev->next->prev =curr;
        prev->next= curr;
        curr->prev = prev;
        numbers.insert(curr);
        
    }
    void MagicalContainer::addtoPrimes(node* curr){
        if (primehead==nullptr)
        {
            primehead = curr;
            primetail = curr;
            primes.insert(curr);
            return;
        }
        if (primehead->data>curr->data)
        {
            
            primehead->primePrev = curr;
            curr->primeNext = head;
            primehead = curr;
            primes.insert(curr);
            return;
        }
        if (curr->data>primetail->data)
        {
            curr->primePrev = primetail;
            primetail->primeNext = curr;
            primetail = curr;
            primes.insert(curr);
            return;
        }
        node* prev = (*primes.lower_bound(curr))->primePrev;
        curr->primeNext = prev->primeNext;
        prev->primeNext->primePrev =curr;
        prev->primeNext= curr;
        curr->primePrev = prev;
        primes.insert(curr);
    }
    int MagicalContainer::size(){
        return numbers.size();}
    void  MagicalContainer::removeElement(int element){
        node* curr =  new node(element);
        if (!numbers.contains(curr))
        {
            throw std::runtime_error("cant remove whats not there");
        }
        
        bool isPrime = primalityTest(element);
        if (isPrime)
        {
            removeFromPrimes(curr);
        }
        removeFromNumbers(curr);
        
        free(curr);

    }
    void MagicalContainer::removeFromNumbers(node* curr){
        node* num = *numbers.lower_bound(curr);
        if (num==head)
        {
            head=num->next;
        }
        if (num==tail)
        {
            tail=num->prev;
        }
        if (num->next!=nullptr)
        {
            num->next->prev= num->prev;
        }
        if (num->prev!=nullptr)
        {
            num->prev->next= num->next;
        }
        numbers.erase(num);
        free(num);
    }
    void MagicalContainer::removeFromPrimes(node* curr){
        node* num = *primes.lower_bound(curr);
        if (primehead==head)
        {
            primehead=num->primeNext;
        }
        if (num==primetail)
        {
            primetail=num->primePrev;
        }
        if (num->primeNext!=nullptr)
        {
            num->primeNext->primePrev= num->primePrev;
        }
        if (num->primePrev!=nullptr)
        {
            num->primePrev->primeNext= num->primeNext;
        }
        primes.erase(num);
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &magical){
        this-> container = &magical;
        this->curr=magical.head;
    }
    MagicalContainer::AscendingIterator::~AscendingIterator(){}
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin(){
        AscendingIterator  begin =*this;
        begin.curr= this->container->head;
        return begin;

    }
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end(){
        AscendingIterator  end =*this;
        end.curr= nullptr;
        return end;
    }
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator& something){
        if (this->container!=something.container)
        {
            throw std::runtime_error("different containers");
        }
        this->curr=something.curr;
        return *this;
     }
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
        if (this->curr==nullptr)
        {
            throw std::runtime_error("cannot increment");
        }
        this->curr =this->curr->next;
        return *this;
    }
    bool   MagicalContainer::AscendingIterator::operator==(const MagicalContainer::AscendingIterator& obj2)const{
        if (this->container!=obj2.container)
        {
            return false;
        }
        if (this->curr==nullptr||obj2.curr==nullptr)
        {
             
            if (this->curr==nullptr&&obj2.curr==nullptr)
            {
                return true;
            }
            return false;
            
        }
        
        return this->curr->data==obj2.curr->data;
        
    }
    int  MagicalContainer::AscendingIterator::operator*()const{
        return this->curr->data;
        }
    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& rhs)const{
         if (curr==nullptr)
        {
            return false;
        }
        if (rhs.curr==nullptr)
        {
           
            return true;
        }
        return this->curr->data<rhs.curr->data;
    }
     bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& rhs)const{
         if (rhs.curr==nullptr)
        {
            return false;
        }
        if (curr==nullptr)
        {
            if (rhs.curr==nullptr)
            {
                return false;
            }
            return true;
        }
        return this->curr->data > rhs.curr->data;
    }




    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& magical){
        container = &magical;
        max =magical.tail;
        min = magical.head;
        fromMin =true;
    }
    MagicalContainer::SideCrossIterator::~SideCrossIterator(){}
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin(){
        SideCrossIterator tmp = *this;
        tmp.max =container->tail;
        tmp.min =container->head;
        tmp.fromMin =true;
        return tmp;
    }
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end(){
        SideCrossIterator tmp = *this;
        tmp.min =nullptr;
        tmp.max =container->head;
        tmp.fromMin =false;
        return tmp;
    }
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator& something){
        if (this->container!=something.container)
        {
            throw std::runtime_error("different containers");
        }
        max = something.max;
        min = something.min;
        fromMin = something.fromMin;
        return *this;
    }
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){
        if (min==nullptr||(min->data>max->data))
        {
            throw std::runtime_error("cannot increment beyond this point");
        }
        
        if (fromMin)
        {
            min = min->next;
            
        }
        else
        {
            max= max->prev;
        }
        
        
        
        fromMin = !fromMin;
        return *this;
        }
    bool   MagicalContainer::SideCrossIterator::operator==(const MagicalContainer::SideCrossIterator& obj2)const{
        if (this->container!=obj2.container)
        {
            return false;
        }

        bool isEndThis =(this->min==nullptr)||(this->min->data>this->max->data);
        bool isEndObj2 = (obj2.min==nullptr)||(obj2.min->data>obj2.max->data);
        if (isEndObj2||isEndThis)
        {
            if (isEndObj2&&isEndThis)
            {
                return true;
            }
            return false;
            
        }
        if (this->min->data==obj2.min->data&&this->max->data==obj2.max->data)
        {
            return true;
        }
        return false;
        
    }
    int    MagicalContainer::SideCrossIterator::operator*()const{return (max->data)*(1- fromMin)+fromMin*min->data;}
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& rhs)const{
        if (this->min->data<rhs.min->data)
        {
            return true;
        }
        else if (this->max->data>rhs.max->data)
        {
            return true;
        }
        return false;
        
        
    }
     bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& rhs)const{
        if (this->min->data>rhs.min->data)
        {
            return true;
        }
        else if (this->max->data>rhs.max->data)
        {
            return true;
        }
        return false;
    }

    
    


     MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& magical){
        this-> container = &magical;
        this->curr=magical.primehead;
     }
    MagicalContainer::PrimeIterator::~PrimeIterator(){}
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin(){
        PrimeIterator  begin =*this;
        begin.curr= this->container->primehead;
        return begin;

    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end(){
        PrimeIterator  end =*this;
        end.curr= nullptr;
        return end;
    }
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const MagicalContainer::PrimeIterator& something){
        if (this->container!=something.container)
        {
            throw std::runtime_error("different containers");
        }
        
        this->curr=something.curr;
        return *this;}
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
        if (this->curr==nullptr)
        {
            throw std::runtime_error("cannot increment");
        }
        
         this->curr =this->curr->primeNext;
         
        return *this;
    }
    bool   MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator& obj2)const{
          if (this->container!=obj2.container)
        {
            return false;
        }
        
        if ((this->curr==nullptr)||(obj2.curr==nullptr))
        {
            if (this->curr==nullptr&&obj2.curr==nullptr)
            {
                return true;
            }
            return false;
            
        }
        return this->curr->data==obj2.curr->data;
        
    }
    int   MagicalContainer::PrimeIterator::operator*()const{
        return this->curr->data;
    }
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& rhs)const{
        if (curr==nullptr)
        {
            return false;
        }
        if (rhs.curr==nullptr)
        {
            return true;
        }
        
        return this->curr->data<rhs.curr->data;
    }
     bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& rhs)const{
        if (rhs.curr==nullptr)
        {
            return false;
        } 
        if (curr==nullptr)
        {
            
            return true;
        }
        return this->curr->data > rhs.curr->data;
    }

    
    
} // namespace ariel
