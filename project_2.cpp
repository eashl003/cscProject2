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

// this verison prints out all three but as one obj

using namespace std;
// git hub

class Territory {

    public:
        int territoryId;
        string type;
    
    public:
    Territory();

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

    // function to check if territory is premium or normal - 0 they compare equal
    bool isTerritoryPremium(string type){
        string premiumStr ("PREMIUM");
        if (premiumStr.compare(type) == 0) {
            return true;
        } else {
            return false;
        }
    }

}; // end of Territory class

ostream & operator<<(ostream &os, const Territory& t) {
    os << " territoryId: " << t.territoryId << " type: " << t.type << endl;
    return os;
}

map<int, Territory *> mapTerritories;
vector<int> territoryIdVec;
// function that creates a vector of territories from the text file, return the vector
void loadTerritories(ifstream& file) {
    string line; 
    int territoryId;
    char comma;
    string type; 
    while(  file >> territoryId >> comma >> type) {
        Territory * t = new Territory(territoryId, type);
        mapTerritories.insert(pair<int ,Territory *> (territoryId, t));
        territoryIdVec.push_back(territoryId);
    }    
}
class Transaction {
    
    public:
        int trxId; // transaction id
        int saleRepId;
        int clientId;
        int trxType; // transaction type
        int amount;

   Transaction();

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
    // get transaction type 
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
ostream & operator<<(ostream &os, Transaction& t) {
    os  << t.getTrxId() << ", " << t.getSaleRepId() << ", " << t.getClientId() << ", " << t.getTrxType() << ", " << t.getAmount() << endl;
    return os;
}

map<int, Transaction *> mapTransaction;
map<int, double> clientIdM; // this will store the client Id as the value and 0-5 
void loadTransactions(ifstream& file) {
    // declare variables for Territory
    int trxId1, saleRepId1, clientId1, trxType1, amount1;
    char comma, comma1, comma2, comma3;
  
    // while loop to store objects
    while(file >> trxId1 >> comma >> saleRepId1 >> comma1 >> clientId1 >> comma2 >> trxType1 >> comma3 >> amount1) {
        Transaction * t = new Transaction(trxId1, saleRepId1, clientId1,trxType1, amount1);
        mapTransaction.insert(pair<int, Transaction*> (trxId1, t)); // insert object into map
    }

    for (int i = 1000; i < 1005; i++){
      
        clientIdM.insert(pair<int, int>(i, i));
        
    }
        // print it
    map<int, double>::iterator it3 = clientIdM.begin();
    while(it3 != clientIdM.end()) {
    int cId = it3->first;
    int cAmount = it3->second;
    
    // for all equal client ids add all their amounts together 
    it3++;
    }

} // end of loadTransaction

class SalesRep {

    private:
        int saleRepId;
        int amount; 
        Territory * territoryPtr = nullptr;  // create a pointer to territory so i can refer directly to territory if i know what SaleRep it is

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

ostream & operator<<(ostream &os, SalesRep& sr) {
    os  << sr.getSaleRepId() << ", " << sr.getTerritoryPtr() << ", " << sr.getAmount() << endl;
    return os;
}

map<int, SalesRep *> mapSaleReps;

void loadSaleReps(ifstream& file, map<int, Territory *> tm) {
    // declare variables for Territory
    int saleRepId, amount, id1;
    //Territory * tPtr = nullptr;
    char comma, comma1;
    // while loop to store objects
    SalesRep * sr;

        while(file >> saleRepId >> comma >> id1 >> comma1 >> amount) {
            Territory * tptr = mapTerritories.at(id1); // we are getting the territory with this current key
            sr = new SalesRep(saleRepId, tptr, amount);
            mapSaleReps.insert(pair<int, SalesRep*> (saleRepId, sr)); // insert object into map     
        }  
}// end load sale reps
 

vector<double> csums;
vector<int> cIds = {1000, 1001, 1002, 1003, 1004}; // client ids
multimap<int , double> cIdAmountMap; // key = Client id, value = current amount
// m is for mapTransaction map and cia is for cInitialAmount map
void calcClientsTransactions(map<int, Transaction *> m){
    // these numbers represent the mulitplicity based on one of the 7 trx types
    double clientRatio[] = {1, 1, -1, -1, 0, -1, 0}; // array to store multiplicities 
    double ca0, sum0, sum1, sum2, sum3, sum4; // client amount and sum variables for calculating total amounts for each of the five clients

    map<int, Transaction *>::iterator it = m.begin(); 
    while( it != m.end()) {
        //int transactId = it->first; // first returns key which is the transaction id
        Transaction * t = it->second; // returns transaction object
        ca0 = t->getAmount() * clientRatio[t->getTrxType() - 1];  // store calculated client amount in ca0
        cIdAmountMap.insert(pair<int, double>(t->getClientId(), ca0)); // this stores the first five initial amounts with client ids
        it++;
    }
    // total sums print
    typedef std::multimap<int, double>::iterator itt;
    for (int i = 0; i < cIds.size(); i++) {
      
        std::pair<itt, itt> result = cIdAmountMap.equal_range(cIds[i]);
      
        for (itt it = result.first; it != result.second; it++) {
            sum0 += it->second;
        }
        cout << "client id " << cIds[i] << " total " << sum0 << endl;
        sum0 = 0;
    }
    
} // end of calcTransaction2()

vector<double> srInitialAmountVec;
vector<double> sums;
vector<int> salesId = {1,2,10,11,12,14,20,21,22,23,24,25};
multimap<int, double> srIdAmountMap; // key is trxId and value is amount
map<int,double> thinkofbettana; 
void calcSaleRepsTransactions(map<int, Transaction *> m, map<int, SalesRep *> srmap) {
    double saleRepRatio[] = {1.10, 1.10, -1 , -1.25, 0, -1.10, 0.75};
    double srAmount, sum, sum1, srInitialAmount; // sale rep amount and total is for the amount earned by each sales rep

    map<int, Transaction *>::iterator it = m.begin();
    while( it != m.end()) {
        Transaction * t = it->second; // returns transaction object
        srAmount = t->getAmount() * saleRepRatio[t->getTrxType() - 1]; 
        srIdAmountMap.insert(pair<int, double>(t->getSaleRepId(), srAmount));
        it++;
    }
    map<int, SalesRep *>::iterator it1 = srmap.begin();
    while ( it1 != srmap.end()) {
        SalesRep * sr = it1->second;
        if ((sr->getTerritoryPtr()->getType()) == "PREMIUM") {// TEST
            srInitialAmount = sr->getAmount() *2; // we just want the inital amount
            srInitialAmountVec.push_back(srInitialAmount);
        } else {
            srInitialAmount = sr->getAmount(); // we just want the inital amount
            srInitialAmountVec.push_back(srInitialAmount);
        }
        it1++;
    }
    typedef std::multimap<int, double>::iterator itt;
    for (int i = 0; i <= salesId.size(); i++) {
        std::pair<itt, itt> result = srIdAmountMap.equal_range(salesId[i]);
        for (itt it = result.first; it != result.second; it++) {
            
            sum += it->second;
            // if premium than sum * 2
            sum1 = srInitialAmountVec[i] + sum;
        }
        cout << "sales rep id " << salesId[i] << " total " << sum1 << endl;
        sum = 0;
    }    
}

//CALCULATE TERRITORY TRANSACTIONS
vector<int> srIdKeys1, srIdKeys2, srIdKeys3, srIdKeys4, srIdKeys5, srIdKeys6; // this will store all the keys that have the same valeus 
vector<double> t1sums, t2sums, t3sums, t4sums,t5sums, t6sums; // territory 1 sum 
vector<int> tIds = {1,2,3,4,5,6}; // territory ids
multimap<int,double> tIdAmountMap; // key -> territory id and value -> amount
map<int, int> srIdTIdMap; // key -> sales rep id value -> territory id
void calcTerritoryTransactions(map<int, Transaction *> m, map<int, SalesRep *> srmap) {
    double territoryRatio[] = {1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 0};
    double tAmount, sum;
    int territoryIds, srIds; // territory ids and sales rep ids
    // we want to check if two keys (two sales reps) have the same value ( same territory id's)
    map<int, SalesRep *>::iterator itt = srmap.begin();
    while(itt != srmap.end()) {
        int srIdNum = itt->first; // stores sales rep id
        SalesRep * srPtr = itt->second; // the second will be the pointer to the sale rep object
        int terrrrid = srPtr->getTerritoryPtr()->getTerritoryId();
        if (terrrrid == 1 ) {
            srIdKeys1.push_back(srIdNum);
            
        } else if (terrrrid == 2) {
            srIdKeys2.push_back(srIdNum);
            
        } else if (terrrrid == 3) {
            srIdKeys3.push_back(srIdNum);
            
        } else if (terrrrid == 4) {
            srIdKeys4.push_back(srIdNum);
            
        } else if (terrrrid == 5) {
            srIdKeys5.push_back(srIdNum);
           
        } else if (terrrrid == 6) {
            srIdKeys6.push_back(srIdNum);
           
        }
        itt++;
    }
    // calculate sum for each territory 
    map<int, Transaction *>::iterator it = m.begin();
    while(it != m.end()) {
        Transaction * t = it->second;
        tAmount = t->getAmount() * territoryRatio[t->getTrxType() -1]; // sotre calculated territory amount in tAmount
        if ((find(srIdKeys1.begin(), srIdKeys1.end(), t->getSaleRepId())) != srIdKeys1.end() ) {
            t1sums.push_back(tAmount);
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
    } // while

    cout << " the sum for territory one " << endl;
    cout<<accumulate(t1sums.begin(),t1sums.end(),0) << endl;
    cout << " the sum for territory two " << endl;
    cout<<accumulate(t2sums.begin(),t2sums.end(),0) << endl;
    cout << " the sum for territory 4 " << endl;
    cout<<accumulate(t4sums.begin(),t4sums.end(),0) << endl;
    cout << " the sum for territory 5 " << endl;
    cout<<accumulate(t5sums.begin(),t5sums.end(),0) << endl;
    cout << " the sum for territory 6 " << endl;
    cout<<accumulate(t6sums.begin(),t6sums.end(),0) << endl;
    cout << " the sum for territory 3 " << endl;
    cout<<accumulate(t3sums.begin(),t3sums.end(),0) << endl;
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
    
    char* territoryOutput = argv[5];
    
    freopen (territoryOutput,"w",stdout);
    calcTerritoryTransactions(mapTransaction, mapSaleReps);
    fclose(stdout);

    char* clientOutput = argv[6];
    freopen (clientOutput,"w",stdout);
    calcClientsTransactions(mapTransaction);
    fclose(stdout);

    char* saleRepOutput = argv[7];
    freopen (saleRepOutput,"w",stdout);
    calcSaleRepsTransactions(mapTransaction, mapSaleReps);
    fclose(stdout);

   
    return 0;

}