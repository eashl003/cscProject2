#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
    for (auto i: territoryIdVec) {
        cout << (i) << endl;
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
    cout << " key " << cId << " clientId " << cAmount << endl;
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
    Territory * tPtr = nullptr;
    char comma, comma1;
    // while loop to store objects
    SalesRep * sr;

        while(file >> saleRepId >> comma >> id1 >> comma1 >> amount) {
            Territory * tptr = mapTerritories.at(id1); // we are getting the territory with this current key
            sr = new SalesRep(saleRepId, tptr, amount);
            mapSaleReps.insert(pair<int, SalesRep*> (saleRepId, sr)); // insert object into map  
        
            cout << "sale rep id" << sr->getSaleRepId() << " territory type " << sr->getTerritoryPtr()->getType() << endl; 
          
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
        srInitialAmount = sr->getAmount(); // we just want the inital amount
        srInitialAmountVec.push_back(srInitialAmount);
        it1++;
    }


    typedef std::multimap<int, double>::iterator itt;
    for (int i = 0; i <= salesId.size(); i++) {
      
        std::pair<itt, itt> result = srIdAmountMap.equal_range(salesId[i]);
      
        for (itt it = result.first; it != result.second; it++) {
            
            sum += it->second;
            sum1 = srInitialAmountVec[i] + sum;
        }
        cout << "sales rep id " << salesId[i] << " total " << sum1 << endl;
        sum = 0;
    }    
}


//CALCULATE TERRITORY TRANSACTIONS

vector<double> tsums;
vector<int> tIds = {1,2,3,4,5,6}; // territory ids
multimap<int,double> tIdAmountMap; // key -> territory id and value -> amount
map<int, int> srIdTIdMap; // key -> sales rep id value -> territory id
void calcTerritoryTransactions(map<int, Transaction *> m, map<int, SalesRep *> srmap) {
    double territoryRatio[] = {1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 0};
    double tAmount, sum;
    int territoryIds, srIds; // territory ids and sales rep ids
    SalesRep * srObj; // can we use this to get what we need?

    map<int, Transaction *>::iterator it = m.begin();
    while(it != m.end()) {
        Transaction * t = it->second;
        tAmount = t->getAmount() * territoryRatio[t->getTrxType() -1]; // sotre calculated territory amount in tAmount
        tIdAmountMap.insert(pair<int, double>(t->getSaleRepId(), tAmount)); // this is a multimap so we'll have multiple keys that are the same
        // we want to check the salesrepId and then see what territory is associated with it??
        it++;
    } // while

    //  we want to get amount for each of the sales reps who have the same territory id and sum it
    multimap<int, Transaction *>::iterator it = m.begin();

} // END OF CALC

    /* THIS IS JUST A PRINT 
    cout << "tIdAmountMap :" << endl;
    map<int, double>::iterator it4 = tIdAmountMap.begin();
       while(it4 != tIdAmountMap.end()) {
        int cId = it4->first;
        double cAmount = it4->second;
        cout << " sale rep id: " << cId << " t Amount: " << cAmount << endl;
        // for all equal client ids add all their amounts together 
        it4++;
    } 
 
    
}

*/

int main () {
    /*
    int main (int argc, char *argv[v])
    cout << argc << endl; // argument counts
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    ....
    */

    freopen ("client_output.txt","w",stdout);
    ifstream territoryFile("territory.txt");
    ifstream saleRepFile("salerep.txt");
    ifstream trxFile("transaction.txt");
    cout << "load territories :" << endl;
 
    loadTransactions(trxFile);
    loadTerritories(territoryFile);
    loadSaleReps(saleRepFile,  mapTerritories); 
    cout << "client output: " << endl;

    calcClientsTransactions(mapTransaction);
    //calcTerritoryTransactions(mapTransaction, mapSaleReps);


    fclose(stdout);


    freopen ("salerep_outputTest.txt","w",stdout);
    calcSaleRepsTransactions(mapTransaction, mapSaleReps);
    fclose(stdout);    
    return 0;
}