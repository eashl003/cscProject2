// Elisabeth Ashley
// Project 2 - process a set of transactions regarding a sale
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
    //int i = 0;
    while(  file >> territoryId >> comma >> type) {
        Territory * t = new Territory(territoryId, type);
        mapTerritories.insert(pair<int ,Territory *> (territoryId, t));
        territoryIdVec.push_back(territoryId);
       // i++;
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
// should it be const?
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
        int territoryId;
        int amount;
        // variable to store points - for each transaction sale salerep are awared points 
        int points; 
    
    public:
        SalesRep(int saleRepId, int territoryId, int amount) {
            this -> saleRepId = saleRepId;
            this -> territoryId = territoryId;
            this -> amount = amount;
        }

        // getters
        int getSaleRepId() {
            return saleRepId;
        }
        int getTerritoryId() {
            return territoryId;
        }
        int getAmount() {
            return amount;
        }

}; // end of SalesRep class


// should it be const?
ostream & operator<<(ostream &os, SalesRep& sr) {
    os  << sr.getSaleRepId() << ", " << sr.getTerritoryId() << ", " << sr.getAmount() << endl;
    return os;
}

map<int, SalesRep *> mapSaleReps;

void loadSaleReps(ifstream& file) {
    // declare variables for Territory
    int saleRepId, territoryId, amount;
    char comma, comma1;
    // while loop to store objects
    SalesRep * sr;
   //int i = 0;
    while(file >> saleRepId >> comma >> territoryId >> comma1 >> amount) {
        // assign values to variable
        sr = new SalesRep(saleRepId, territoryId, amount);
        mapSaleReps.insert(pair<int, SalesRep*> (saleRepId, sr)); // insert object into map   
       // i++;
    }
    
    map<int, SalesRep*>::iterator it = mapSaleReps.begin();
    while(it != mapSaleReps.end()) {
        int num = it->first;
        SalesRep * saleR = it -> second;
        cout << num << " : " << *saleR << endl;
        it++;
    }
} // end of loadSaleReps



// TEST another calculate transaction function
map<int , double> tIdAmountMap; // key is trxId and value is current amount
multimap<int , double> cIdAmountMap; // key = Client id, value = current amount
// m is for mapTransaction map and cia is for cInitialAmount map
void calcTransactions2(map<int, Transaction *> m){
    // these numbers represent the mulitplicity based on one of the 7 trx types
    double clientRatio[] = {1, 1, -1, -1, 0, -1, 0}; // array to store multiplicities 
    double ca0,ca1,ca2,ca3,ca4; // client amount 
    double ca0c, ca1c, ca2c, ca3c, ca4c; // client current amount 
    double updatedCAmount, currentAmount;
    int caId = 0;
    double sum = 0;
    // remember that the map we are going to pass in has the trxId as key and then T 
    // for each transaction ... we need to iterator through the map
   
    map<int, Transaction *>::iterator it = m.begin();
    while( it != m.end()) {
        
        // we need to get client id and amount and insert it 
        int transactId = it->first; // first returns key so we'd like 1
        Transaction * t = it->second; // returns transaction object
        // store calculated client amount
      
        //ca = t->getAmount() * clientRatio[t->getTrxType() - 1];
        ca0 = t->getAmount() * clientRatio[t->getTrxType() - 1];
        cIdAmountMap.insert(pair<int, double>(t->getClientId(), ca0)); // this stores the first five initial amounts with client ids
        it++;
    }
    // try to sum the values
    typedef std::multimap<int, double>::iterator itt;
    std::pair<itt, itt> result = cIdAmountMap.equal_range(1002);
    for (itt it = result.first; it != result.second; it++) {
        //cout << "pls : " << it->second << endl;
        sum += it->second;
        cout << sum << endl;
    }


    
    // print it
    map<int, double>::iterator it3 = cIdAmountMap.begin();
    while(it3 != cIdAmountMap.end()) {
    int cId = it3->first;
    double cAmount = it3->second;
    cout << " get client id: " << cId << " cAmount: " << cAmount << endl;
    // for all equal client ids add all their amounts together 
    it3++;
      
    }
        
}
// END



// direct output to client_output (clientID , client amount)
void clientOutput(vector<int> ci, vector<double> ca) {
    for (int i = 0; i < ci.size(); i++) {
        cout << " client id is:" << ci[i] << " client amount is: " << ca[i] << endl;
    }

    if(ca.size()==0){
        cout<< "yes";
    }else{cout<<"no";}


}
// TEST 
// territory id and territory amount 
void territoryOutput(vector<int> ti, vector<double> ta) {
    
}


// END TEST
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
    loadTerritories(territoryFile);
    loadTransactions(trxFile);
    //for (auto i : amountVec)
    //cout << (i) << endl;
    //loadSaleReps(saleRepFile);
    //calcTransaction(typeVec, amountVec);
    cout << "client output: " << endl;
    //clientOutput(clientIdVec, clientsVec); 
    calcTransactions2(mapTransaction);

    fclose(stdout);
    return 0;
}
