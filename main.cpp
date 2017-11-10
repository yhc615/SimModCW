#include <iostream>
#include <cmath>
#include <random>
#include <map>
#include <time.h>
#include "cache.hpp"

using namespace std;

double nextRequestTime(double lambda){
    double randNum = (double)rand()/RAND_MAX;
    return -log(randNum)*lambda;
}

int processQueue(double &time, map<double, int> &que, Cache &cache){
    int itemIndex = que.begin()->second;
    cache.request(itemIndex); // FIFO=0
    que.erase(que.begin());
    que.insert(pair<double,int>(time+nextRequestTime(itemIndex),itemIndex));
    return 0;
}

int timeStep(double &time, map<double, int> &que, Cache &cache){
    double eventTime = que.begin()->first;
    time = eventTime;
    //cout << "TIME: " << time << endl;
    processQueue(time, que, cache);
    return 0;
} 


int main(int argc, char* argv[]) { // argv=>  [1] = item size , [2] = cache size (m), 
                                   //         [3] = time steps, [4] = mode (FIFO:0, RAND:1)
    srand(time(NULL)); // initialize random no. generator

    double gTime = 0;
    int missNum = 0;

    //convert params
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int tSteps = atoi(argv[3]);
    int mode = atoi(argv[4]);


    //Create and initialize cache
    Cache simCache(m, mode);
    simCache.fill();

    map<double, int> q;
    //Fill events(que) with exponentially distributed request times
    for(int i=1; i<=n; i++){
        q.insert(pair<double,int>(nextRequestTime(i),i));
    }

    simCache.print(); // initial cache contents
    for(int i=0; i<tSteps; i++){ // progress time in hops
        timeStep(gTime, q, simCache);
    }
    simCache.print(); // cache contents after simluation

    cout << "Final Time: " << gTime << endl;
    cout << "Hit Count: " << simCache.getHitCount() << endl;
    cout << "Miss Count: " << simCache.getMissCount() << endl;
    cout << "Hit Rate: " << simCache.getHitCount()/gTime << endl;
    cout << "Miss Rate: " << simCache.getMissCount()/gTime << endl;
    
    return 0;
}