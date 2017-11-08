#include <iostream>
#include <cmath>
#include <random>
#include <queue>
#include <map>

using namespace std;

struct cache{
    int size;
    deque<int> items; // each element is an int representing an item from population

    cache(int m)
            : size(m)
    {}

    void fillCache(){
        for(int i=0; i<size; i++){
            items.push_back(i+1);
        }
    }
    void printCache(){
        cout << "----------" << endl;
        for(int i=0; i<size; i++){
            cout << items[i] << endl;
        }
        cout << "----------" << endl;
    }

    void request(int itemIndex, int mode){ // mode: FIFO=0, RAND=1
        deque<int>::iterator it = find(items.begin(), items.end(), itemIndex);
        if(it == items.end()){
            if(mode==0){
                items.pop_front();
                items.push_back(itemIndex);
            }
            if(mode==1){
                int randNum = rand()*size/RAND_MAX;
                items[randNum] = itemIndex;
            }
            cout << "MISS: " << itemIndex << endl;
        }
        else{
            cout << "HIT: " << itemIndex << endl;
        }
    }
};

double nextRequestTime(double lambda){
    double randNum = (double)rand()/RAND_MAX;
    return -log(randNum)*lambda;
}

int processQueue(double &time, map<double, int> &que, cache &cache){
    int itemIndex = que.begin()->second;
    cache.request(itemIndex, 0); // FIFO=0
    que.erase(que.begin());
    que.insert(pair<double,int>(time+nextRequestTime(itemIndex),itemIndex));
    return 0;
}

int timeStep(double &time, map<double, int> &que, cache &cache){
    double eventTime = que.begin()->first;
    time = eventTime;
    cout << "TIME: " << time << endl;
    processQueue(time, que, cache);
    return 0;
}

int main() {
    srand(time(NULL));

    double gTime = 0;

    int n;
    int m;
    int tSteps;
    cout << "Enter item size, cache size, time steps:" << endl;
    cin >> n >> m >> tSteps;

    map<double, int> q;
    cache simCache(m);

    simCache.fillCache();
    for(int i=1; i<=n; i++){
        q.insert(pair<double,int>(nextRequestTime(i),i));
    }

    simCache.printCache(); // cache before sim
    for(int i=0; i<tSteps; i++){ // 'tSteps' amount of time steps
        timeStep(gTime, q, simCache);
    }
    simCache.printCache(); // cache after sim

    return 0;
}