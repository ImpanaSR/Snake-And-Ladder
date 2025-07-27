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

//Base class for Snake and Ladder (both have start adn end positions)
class BoardEntity {
    protected: 
    int startPosition;
    int endPosition;

public:
    BoardEntity(int start, int end){
        startPosition = start;
        endPosition = end;
    }

    int getStart() {
        return startPosition;
    }

    int getEnd(){
        return endPosition;
    }

    virtual void display() = 0;
    virtual string name() = 0;
    virtual ~BoardEntity() {}
};

//snake class
class Snake : public BoardEntity {
    public:
    Snake(int start, int end) : BoardEntity(start, end) {
        if(end>=start) {
            cout<<"Invalid snake! End must be less than start."<<endl;
        }
    }

    void display() override {
        cout<<"Snake: "<< startPosition <<" -> "<<endPosition<<endl;
    }

    string name() override {
        return "SNAKE";
    }
};

//Ladder class
class Ladder : public BoardEntity {
public: 
     Ladder(int start, int end) : BoardEntity(start, end) {
        if(end<=start) {
            cout<<"Invalid ladder! End must be greater than start."<<endl;
        }
     }

     void display() override {
        cout<<"Ladder: "<<startPosition <<" -> "<<endPosition<<endl;
     }

     string name() override {
        return "LADDER";
     }
};

class BoardSetupStrategy;

// Board class
class Board {
private:
    int size;
    vector<BoardEntity*> snakesAndLadders;
    map<int, BoardEntity*> boardEntities;

public:
    Board(int s) {
        size = s*s;
    }

    bool canAddEntity(int position) {
        return boardEntities.find(position) == boardEntities.end();
    }

    void addBoardEntity(BoardEntity* boardEntity) {
        if(canAddEntity(boardEntity->getStart())) {
            snakesAndLadders.push_back(boardEntity);
            boardEntities[boardEntity->getStart()] = boardEntity;
        }
    }
 
 void setupBoard(BoardSetupStrategy* strategy);

 BoardEntity* getEntity(int position) {
    if(boardEntities.find(position) != boardEntities.end()) {
        return boardEntities[position];
    }
    return nullptr;
 }

 int getBoardSize() {
    return size;
 }

 void display() {
    cout<<"\n===Board Configuration ==="<<endl;
    cout<<"Board Size: " << size <<"cells" <<endl;

    int snakeCount=0;
    int ladderCount = 0;
    for(auto entity  : snakesAndLadders) {
        if(entity->name() == "SNAKE") snakeCount++;
        else ladderCount++;
    }

    cout<<"\nSnakes: "<<snakeCount<<endl;
    for(auto entity : snakesAndLadders) {
        if(entity->name() =="SNAKE") {
            entity->display();
        }
    }

    cout<<"\nLadders: "<<ladderCount << endl;
    for(auto entity: snakesAndLadders) {
        if(entity->name() == "LADDER") {
            entity->display();
        }
    }
    cout<<"================================"<<endl;
 }
 ~Board() {
    for(auto entity: snakesAndLadders) {
        delete entity;
    }
 }
};