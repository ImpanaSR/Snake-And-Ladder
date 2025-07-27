#include<iostream>
#include<vector>
#include<map>
#include<deque>
#include<cstdlib>
#include<ctime>

using namespace std;

class IObserver {
    public: 
    virtual void update(string msg) = 0;
    virtual ~IObserver() {}
};

class SnakeAndLadderConsoleNotifier : public IObserver{
    public:
        void update(string msg) override {
            cout<<"[NOTIICATION] "<<msg<<endl;
        }
};

class Dice {
    private:
        int faces;
    
    public:
        Dice(int f) {
            faces = f;
            srand(time(0));
        }

        int roll() {
            return (rand() % faces) + 1;
        }
};