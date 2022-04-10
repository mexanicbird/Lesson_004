#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>
#define LENGHT 14

using namespace std;

vector<int> vectorCreate();
void vectorRead(vector<int> &readVector);
int countingTheSame(vector<int> &readVector);



/* task 001 */
class Container {
    int* data;
    int size;
    int capacity;
    int& operator[](int idx) {
        assert(idx >= 0 && idx < size);
        return data[idx];
    }

public:
    Container() : size(0), data(nullptr), capacity(0) {}
    Container(int _size) : size(_size) {
        if (_size == 0) {
            Container();
        } else if (_size < 0) {
            std::cout << "Bad thing happened" << std::endl;
            Container();
        } else {
            this->data = new int[_size];
            this->capacity = 0;
        }
    }

    virtual ~Container() {
        delete[] data;
    }

    void setData(int idx, int value) {
        assert(idx >= 0 && idx < size);
        this->data[idx] = value;
    }

    int getData(int idx) {
        assert(idx >= 0 && idx < size);
        return this->data[idx];
    }

    int getCapacity() {
        return this->capacity;
    }

    int getSize() {
        return this->size;
    }

    void resize(int newLength) {
        if (newLength == size) return;
        if (newLength <= 0) {
            erase();
            return;
        }
        int* newData = new int[newLength];
        if (size > 0) {
            int elemToCopy = (newLength > size) ? size : newLength;
            for (int idx = 0; idx < elemToCopy; idx++) {
                newData[idx] = data[idx];
            }
        }
        delete[] data;
        data = newData;
        size = newLength;
    }

    void erase() {
        capacity = 0;
        for (int idx = 0; idx < size; idx++) {
            data[idx] = 0;
        }
    }

    void pop_back(){
        resize(size - 1);
    }

    void pop_front(){
        for (int i = 0; i < (size - 1); ++i) {
            setData((i), getData(i + 1));
        }
        resize(size - 1);
    }

    void bubbleSort(){
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    int temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    void printConteiner(){
        if (size == 0) {
            std::cout << "There is no data in the container" << std::endl;
        } else {
            std::cout << "Conteiner data = {";
            for (int i = 0; i < (size); ++i) {
                std::cout << data[i];
                if (i < (size - 1)  ){std::cout << ", ";
                } else {std::cout << "}" << std::endl;}
            }
        }
    }
};



/* task 002 */
vector<int> vectorCreate() {
    std::vector<int> array;
    for (int i = 0; i < LENGHT; ++i) {
        array.push_back(rand() % 7 + 1);
    }
    return array;
}

void vectorRead(vector<int> &readVector) {
    std::vector<int>::iterator iter;
    iter = readVector.begin();
    std::cout << "Vector data = {";
    for (int i = 0; i < readVector.size(); ++i, ++iter) {
        std::cout << *iter;
        if (i < (readVector.size() - 1)  ){std::cout << ", ";
        } else {std::cout << "}" << std::endl;}
    }
}

int countingTheSame(vector<int> &readVector) {
    int count = 1;
    int tempArray[readVector.size()];
    sort(readVector.begin(), readVector.end());
    std::vector<int>::iterator iter;
    iter = readVector.begin();
    for (int i = 0; i < (readVector.size()); ++i, ++iter) {
        tempArray[i] = *iter;
    }
    for (int i = 1; i < (sizeof(tempArray)/sizeof(int)); ++i, ++iter) {
        if (tempArray[i] != tempArray[i - 1]) {
            count++;
        }
    }
    return count;
}



/* task 003 */
enum ECardSuit { SPADES, CLUBS, DIAMONDS, HEARTS };
enum ECardValue {
    ACE   = 1,
    TWO   = 2,
    THREE = 3,
    FOUR  = 4,
    FIVE  = 5,
    SIX   = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE  = 9,
    TEN   = 10,
    JACK  = 10,
    QUEEN = 10,
    KING  = 10
};

class Card {
    ECardSuit suit;
    ECardValue value;
    bool isCoverUp;
public:
    Card(ECardSuit _suit, ECardValue _value) : suit(_suit), value(_value) {
        isCoverUp = true;
    }

    void flip() {
        isCoverUp =! isCoverUp;
    }
    ECardValue getValue() const {
        return value;
    }
};

class Hand {
protected:
    std::vector<Card*> m_cards;
public:
    void Add(Card* newCard) {
        m_cards.push_back(newCard);
    };

    void Clear() {
        m_cards.clear();
    };

    int getTotal(){
        int points = 0;
        for (Card* card: m_cards)
        {
            points += card->getValue();
        }
        return points;
    }
};



int main(int argc, const char** argv) {
    /* execution time control */
    double start_time =  clock();

    std::cout << "Lesson 004" << std::endl;
    std::cout << "Task 1" << std::endl;
    Container c1(LENGHT);
    for (int i = 0; i < c1.getSize(); ++i) {
        c1.setData(i,(rand() % 100 + 1));
    }
    c1.printConteiner();

    c1.bubbleSort();
    c1.printConteiner();

    c1.pop_back();
    c1.printConteiner();

    c1.pop_front();
    c1.printConteiner();
    std::cout << "\n";

    std::cout << "Task 2" << std::endl;
    vector<int> Array = vectorCreate();
    vectorRead(Array);
    countingTheSame(Array);
    std::cout << "Different numbers in an array = " << countingTheSame(Array) << std::endl;
    std::cout << "\n";

    std::cout << "Task 3" << std::endl;
    Card heardsTen(HEARTS, TEN);
    Card heardsSeven(HEARTS, SEVEN);
    Hand playerOne;
    playerOne.Add(&heardsTen);
    playerOne.Add(&heardsSeven);
    std::cout << "Player's card value = " << playerOne.getTotal() << std::endl;
    playerOne.Clear();
    std::cout << "Player's card value = " << playerOne.getTotal() << std::endl;
    std::cout << "\n";

    /* execution time control */
    double end_time = clock();
    double search_time = (end_time - start_time)/1000;
    std::cout << "Program execution time = " << search_time << " sec"<< std::endl;
    return 0;
}