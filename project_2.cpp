// Elisabeth Ashley, Naol Legesse, Meron Mengistu
// Project 2 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <map>
#include <sstream>
#include <unordered_map>
#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <array>
#include <iomanip>

using namespace std;

class Territory {

    private:
        int territoryId;
        string type;
    
    public:
    Territory();
    // parameterized constructor
    Territory(int territoryId, string type){
        this -> territoryId = territoryId;
        this -> type = type;
    }

    // setters:
    void setTerritoryId(int territoryId) {
        this -> territoryId = territoryId;
    }
    void setType(string type) {
        this -> type = type;
    }
    // getters:
    int getTerritoryId() {
        return territoryId;
    }
    string getType() {
        return type;
    }

}; // end of Territory class

map<int, Territory *> mapTerritories; // global map so you can have access outside this function
// function that creates a vector of territory ids and a map that maps Territory id's to a Territory ptr
void loadTerritories(ifstream& file) {
    string line, type; 
    int territoryId;
    char comma; 
    // this will store the lines of the code into variable names
    while( file >> territoryId >> comma >> type) {
        Territory * t = new Territory(territoryId, type); // this will create a new pointer to a Territory object
        mapTerritories.insert(pair<int ,Territory *> (territoryId, t)); // insert id and pointer to Territory object
    }
}
class Transaction {
    
    public:
        // declare variables for transaction class
        int trxId, saleRepId, clientId, trxType, amount; 

    Transaction();
    // parameterized constructor
    Transaction(int trxId, int saleRepId, int clientId, int trxType, int amount) {
        this -> trxId = trxId;
        this -> saleRepId = saleRepId;
        this -> clientId = clientId;
        this -> trxType = trxType;
        this -> amount = amount;
    }
    // setters
    void setTrxId() {
        this -> trxId = trxId;
    }
    void setSaleRepId() {
        this -> saleRepId = saleRepId;
    }
    void setClientId() {
        this -> clientId = clientId;
    }
    void setTrxType() { 
        this -> trxType = trxType;
    }
    void setAmount() {
        this -> amount = amount;
    }
    // getters 
    int getTrxId() {
        return trxId;
    }
    int getSaleRepId() {
        return saleRepId;
    }
    int getClientId() {
        return clientId;
    }
    int getTrxType() { 
        return trxType;
    }
    int getAmount() {
        return amount;
    }
}; // end of Transaction class

class Client : public Transaction {

    public:
        Client(int clientId, int amount);

}; // end of Client class

map<int, Transaction *> mapTransaction; // maps Transaction Id to Transaction pointer
void loadTransactions(ifstream& file) {
    // declare variables for Territory
    int trxId1, saleRepId1, clientId1, trxType1, amount1;
    char comma, comma1, comma2, comma3;
    // while loop to store objects
    while(file >> trxId1 >> comma >> saleRepId1 >> comma1 >> clientId1 >> comma2 >> trxType1 >> comma3 >> amount1) {
        Transaction * t = new Transaction(trxId1, saleRepId1, clientId1,trxType1, amount1); // creates pointer to transaction object
        mapTransaction.insert(pair<int, Transaction*> (trxId1, t)); // insert object into map
    }
} // end of loadTransaction

class SalesRep {

    private:
        int saleRepId;
        int amount; 
        Territory * territoryPtr = nullptr;  // create a pointer to territory so we can refer directly to territory if we know what SaleRep it is
        // this will help when we have to do the calculations for the territories
    public:
        SalesRep(int saleRepId, Territory * territoryPtr, int amount) {
            this -> saleRepId = saleRepId;
            this -> territoryPtr = territoryPtr;
            this -> amount = amount;
        }
        // getters
        int getSaleRepId() {
            return saleRepId;
        }
        int getAmount() {
            return amount;
        }
        Territory * getTerritoryPtr() {
            return territoryPtr;
        }
}; // end of SalesRep class

map<int, SalesRep *> mapSaleReps; // maps salerep id to SaleRep pointer to object
void loadSaleReps(ifstream& file, map<int, Territory *> tm) {
    int saleRepId, amount, terId;  // declare variables for Territory
    char comma, comma1;
    // while loop to store objects
    while(file >> saleRepId >> comma >> terId >> comma1 >> amount) {
        Territory * tptr = mapTerritories.at(terId); // we are getting the territory with this current key, accessing via mapTerritories
        SalesRep * sr = new SalesRep(saleRepId, tptr, amount); // create new sales rep, with ptr to Territory object
        mapSaleReps.insert(pair<int, SalesRep*> (saleRepId, sr)); // insert object into map  
    }  
}// end load sale reps
 
// now for calculations
multimap<int , int> cIdAmountMap; // key = Client id, value = current amount
void calcClientsTransactions(map<int, Transaction *> m){
    // these numbers represent the mulitplicity based on one of the 7 trx types
    double clientRatio[] = {1, 1, -1, -1, 0, -1, 0}; // array to store multiplicities 
    double ca0, sum0; // ca stands for client amount 
    vector<int> cIds = {1000, 1001, 1002, 1003, 1004}; // client ids
    
    map<int, Transaction *>::iterator it = m.begin(); 
    while( it != m.end()) {
        //int transactId = it->first; // first returns key which is the transaction id
        Transaction * t = it->second; // returns transaction object
        // t -> getAmount() will get the amount of that transaction than multiply it by the correct ratio depending on its type
        ca0 = t->getAmount() * clientRatio[t->getTrxType() - 1];  // store calculated client amount in ca0
        cIdAmountMap.insert(pair<int, double>(t->getClientId(), ca0)); // this stores the first five initial amounts with client ids
        it++;
    }
    // total sums print
    typedef std::multimap<int, int>::iterator itt;
    for (int i = 0; i < cIds.size(); i++) {
        std::pair<itt, itt> result = cIdAmountMap.equal_range(cIds[i]);
        for (itt it = result.first; it != result.second; it++) {
            sum0 += it->second; // this will essentially generate the overall totals for each client
        }
        cout  << setfill('0') << setw(5) << cIds[i] << "," << setfill('0') << setw(7) << sum0 << endl; // left fill with zeros
        sum0 = 0; // reset sum
    }
} // end of calcTransaction2()

multimap<int, int> srIdAmountMap; // key is trxId and value is amount
void calcSaleRepsTransactions(map<int, Transaction *> m, map<int, SalesRep *> srmap) {
    double saleRepRatio[] = {1.10, 1.10, -1 , -1.25, 0, -1.10, 0.75};
    double srAmount, sum, sum1, srInitialAmount; // sale rep amount and total is for the amount earned by each sales rep
    vector<double> srInitialAmountVec; // vector to store sale reps initial amounts
    vector<double> sums;
    vector<int> salesId = {1,2,10,11,12,14,20,21,22,23,24,25}; // vector for all the sale rep ids

    map<int, Transaction *>::iterator it = m.begin();
    while( it != m.end()) {
        Transaction * t = it->second; // returns transaction object
        srAmount = t->getAmount() * saleRepRatio[t->getTrxType() - 1]; // calculate salerep amount by getting t's amount and multiplying it by salesRepRatio
        srIdAmountMap.insert(pair<int, int>(t->getSaleRepId(), srAmount)); // insert sale rep amount with sale rep id into map
        it++; // increment iterator
    }
    map<int, SalesRep *>::iterator it1 = srmap.begin(); // now iterate through the sales rep map we created earlier
    while ( it1 != srmap.end()) {
        SalesRep * sr = it1->second; // getting the ptr to SalesRep obect
        srInitialAmount = sr->getAmount(); // we just want the inital amount
        srInitialAmountVec.push_back(srInitialAmount); // there are 12 different initial values
        it1++; // increment iterator
    }

    typedef std::multimap<int, int>::iterator itt;
    for (int i = 0; i <= salesId.size()-1; i++) {
      
        std::pair<itt, itt> result = srIdAmountMap.equal_range(salesId[i]); // map::equal_range returns the bounds of range that include all 
        // elemnts in the container which have a key equivalent to salesId at the index i

        for (itt it = result.first; it != result.second; it++) {
            
            sum += it->second; // get srAmount
            sum1 = srInitialAmountVec[i] + sum; // now add the newly calculated sum to sum1
        }
        cout << setfill('0') << setw(5) << salesId[i] << "," << setfill('0') << setw(7)<< sum1 << endl;
        sum = 0; // reset sum so you don't have to have 12 different sum variables, just the one
    }    
}

//CALCULATE TERRITORY TRANSACTIONS
vector<int> srIdKeys1, srIdKeys2, srIdKeys3, srIdKeys4, srIdKeys5, srIdKeys6; // this will store all the keys that have the same values 
vector<double> t1sums, t2sums, t3sums, t4sums,t5sums, t6sums; // territory sums - 6 territories
vector<int> tIds = {1,2,3,4,5,6}; // territory ids
multimap<int,double> tIdAmountMap; // key -> territory id and value -> amount
map<int, int> srIdTIdMap; // key -> sales rep id value -> territory id
void calcTerritoryTransactions(map<int, Transaction *> m, map<int, SalesRep *> srmap) {
    double territoryRatio[] = {1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 0};
    double tAmount, sum;
    int territoryIds, srIds; // territory ids and sales rep ids
    // we want to check if keys (aka sales reps) have the same territory id's
    // for example sales reps - 2, 14, and 20 have the same territory ids (2) so essentially what we do is check
    // the line in the transaction file and see the sales rep id, then we check to see what territory is associated with that
    // sales rep, then we can check and see if that territory is premium or normal, caclulate amount and add it to 
    // whichever territory 
    map<int, SalesRep *>::iterator itt = srmap.begin(); // iterate through sales rep map which we generated from salerep.txt
    while(itt != srmap.end()) { // while map isn't empty
        int srIdNum = itt->first; // stores sales rep id
        SalesRep * srPtr = itt->second; // the second will be the pointer to the sale rep object
        int terrrrid = srPtr->getTerritoryPtr()->getTerritoryId(); // now the sick thing is we can access the territory's id via the territory pointer via our sales rep
        if (terrrrid == 1 ) {
            srIdKeys1.push_back(srIdNum); // now if the territory id is 1 we push back that sales rep id number at this line
        } else if (terrrrid == 2) {
            srIdKeys2.push_back(srIdNum); // now if the territory id is 2 we push back that sales rep id number etc...
            // so this will have sales reps with the ids 2, 14 and 20
        } else if (terrrrid == 3) {
            srIdKeys3.push_back(srIdNum);
        } else if (terrrrid == 4) {
            srIdKeys4.push_back(srIdNum);
        } else if (terrrrid == 5) {
            srIdKeys5.push_back(srIdNum);
        } else if (terrrrid == 6) {
            srIdKeys6.push_back(srIdNum);
        }
        itt++; // increment iterator
    }
    // calculate sum for each territory 
    // find will find elment in vector, so (vec.begin(), vec.end(), itemtofind != vec.end())
    map<int, Transaction *>::iterator it = m.begin();
    while(it != m.end()) {
        Transaction * t = it->second; // pointer to transaction object
        tAmount = t->getAmount() * territoryRatio[t->getTrxType() -1]; // store calculated territory amount in tAmount
        if ((find(srIdKeys1.begin(), srIdKeys1.end(), t->getSaleRepId())) != srIdKeys1.end() ) {
            t1sums.push_back(tAmount); // so if the sales rep id is is in that we push back tAmount for the  territory
        } else if ((find(srIdKeys2.begin(), srIdKeys2.end(), t->getSaleRepId())) != srIdKeys2.end() ) {
            t2sums.push_back(tAmount);
        } else if ((find(srIdKeys3.begin(), srIdKeys3.end(), t->getSaleRepId())) != srIdKeys3.end() ) {
            t3sums.push_back(tAmount);
        } else if ((find(srIdKeys4.begin(), srIdKeys4.end(), t->getSaleRepId())) != srIdKeys4.end() ) {
            t4sums.push_back(tAmount);
        } else if ((find(srIdKeys5.begin(), srIdKeys5.end(), t->getSaleRepId())) != srIdKeys5.end() ) {
            t5sums.push_back(tAmount);
        } else if ((find(srIdKeys6.begin(), srIdKeys6.end(), t->getSaleRepId())) != srIdKeys6.end() ) {
            t6sums.push_back(tAmount);
        }
        it++;
    } 
    // accumlate returns the result of adding all the values in the range
    cout << setfill('0') << setw(6)<< "1,";
    cout<< setfill('0') << setw(7) << accumulate(t1sums.begin(),t1sums.end(),0) << endl;
    cout << setfill('0') << setw(6)<< "2,";
    cout<< setfill('0') << setw(7) << accumulate(t2sums.begin(),t2sums.end(),0) << endl;
    cout << setfill('0') << setw(6)<< "4,";
    cout << setfill('0') << setw(7) <<accumulate(t4sums.begin(),t4sums.end(),0) << endl;
    cout << setfill('0') << setw(6)<< "5,";
    cout<< setfill('0') << setw(7) <<accumulate(t5sums.begin(),t5sums.end(),0) << endl;
    cout << setfill('0') << setw(6)<< "6,";
    cout<< setfill('0') << setw(7) <<accumulate(t6sums.begin(),t6sums.end(),0) << endl;
    cout << setfill('0') << setw(6)<< "3,";
    cout<< setfill('0') << setw(7) <<accumulate(t3sums.begin(),t3sums.end(),0) << endl;
}

int main (int argc, char *argv[]) {
   
    argv[0] = "./project_2";

    char* territoryInput = argv[1];
    ifstream territoryFile(territoryInput); // territory.txt

    char* srInput = argv[2];
    ifstream srFile(srInput); // territory.txt

    char* trxInput = argv[3];
    ifstream trxFile(trxInput); // territory.txt

    loadTransactions(trxFile);
    loadTerritories(territoryFile);
    loadSaleReps(srFile,  mapTerritories); 
    
    char* territoryOutput = argv[4];
    
    freopen (territoryOutput,"w",stdout);
    calcTerritoryTransactions(mapTransaction, mapSaleReps);
    fclose(stdout);

    char* clientOutput = argv[5];
    freopen (clientOutput,"w",stdout);
    calcClientsTransactions(mapTransaction);
    fclose(stdout);

    freopen (srInput,"w",stdout);
    calcSaleRepsTransactions(mapTransaction, mapSaleReps);
    fclose(stdout);

   
    return 0;

}