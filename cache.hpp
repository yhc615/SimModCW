#ifndef CACHE_HPP
#define CACHE_HPP

#include <iostream>
#include <cmath>
#include <random>
#include <queue>

class Cache{
public:
	Cache(int m, int policy)
            : size(m), replacement_policy(policy), missCount(0), hitCount(0)
    {std::cout<<"created Cache of capacity: "<<m<<std::endl;
	 std::cout<<"Replacement Policy: "<<replacement_policy<<std::endl;}

    //Methods
    void fill(){
        for(int i=0; i<size; i++){
            items.push_back(i+1);
        }
    }
    void print(){
    	std::cout << "----------Printing Cache contents----------" << std::endl;
        for(int i=0; i<size; i++){
            std::cout << items[i] << "  |  ";
        }
        std::cout<<"\n";
        std::cout << "-------------------------------------------" << std::endl;
    }
    void request(int itemIndex){
        std::deque<int>::iterator it = find(items.begin(), items.end(), itemIndex);
        if(it == items.end()){
            if(replacement_policy==0){
                items.pop_front();
                items.push_back(itemIndex);
            }
            if(replacement_policy==1){
                int randNum = (double)rand()*size/RAND_MAX;
                items[randNum] = itemIndex;
            }
            std::cout << "MISS: " << itemIndex << std::endl;
            missCount++;
        }
        else{
            std::cout << "HIT: " << itemIndex << std::endl;
            hitCount++;
        }
    }

    //Getters
    int getMissCount(){
        return missCount;
    }
    int getHitCount(){
        return hitCount;
    }

	//Member data
private:
	int size;
	int replacement_policy; //FIFO: 0, RAND:1
	int hitCount;
	int missCount;
	std::deque<int> items; // each element is an int representing an item from population
};


#endif