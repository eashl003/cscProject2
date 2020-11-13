// Elisabeth Ashley
// Project 2 - process a set of transactions regarding a sale
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
// this verison prints out territory map

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
    os << "territoryId:" << t.territoryId << "type:" << t.type << endl;
    return os;
}

map<int, Territory *> mapTerritories;
// function that creates a vector of territories from the text file, return the vector
void declareTerritories(ifstream& file) {
    // variables for territory 
    int territoryId;
    char comma;
    string type = "";

    while(file.good()) {
        file >> territoryId >> comma >> type;
        //Territory t(territoryId, type);
        //territoryVec.push_back(t);
        Territory * t = new Territory(territoryId, type);
        for( int i = 0; i < 6; i++) {
            mapTerritories.insert(pair<int ,Territory *> (i, t));
            
        }
    } // while

    map<int, Territory *>::iterator it = mapTerritories.begin();

    while(it != mapTerritories.end()) {
        int num = it->first;

        Territory *ter = it->second;

        cout << num << " : " << *ter << endl;

        it++;

    }
    
}
    


class Client {

    private: 
        int clientId;
        int amount;
    
    public:
        Client(int clientId, int amount) {
            this -> clientId = clientId;
            this -> amount = amount;
        }

        // setters?
        // getters
        int getClientId(){
            return clientId;
        }

        int getAmount() {
            return amount;
        }

}; // end of Client class

class Transaction {
    
    public:
        int trxId; // transaction id
        int saleRepId;
        int clientId;
        int trxType; // transaction type
        int amount;

    Transaction(int trxId, int saleRepId, int clientId, int trxType, int amount) {
        this -> trxId = trxId;
        this -> saleRepId = saleRepId;
        this -> clientId = clientId;
        this -> trxType = trxType;
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
// should it be const?
ostream & operator<<(ostream &os, Transaction& t) {
    os  << t.getTrxId() << ", " << t.getSaleRepId() << ", " << t.getClientId() << ", " << t.getTrxType() << ", " << t.getAmount() << endl;
    return os;
}

map<int, Transaction *> mapTransaction;

void loadTransactions(ifstream& file) {
    // declare variables for Territory
    int trxId, saleRepId, clientId, trxType, amount;
    char comma, comma1, comma2, comma3;
    // while loop to store objects
    while(file.good()) {
        // assign values to variables
        file >> trxId >> comma >> saleRepId >> comma1 >> clientId >> comma2 >> trxType >> comma3 >> amount;
        for(int i = 0; i < 29; i++) {
            // create instance of Territory obj
            Transaction * t = new Transaction(trxId, saleRepId, clientId,trxType, amount);
            mapTransaction.insert(pair<int, Transaction*> (i, t)); // insert object into map
        }
    }
    map<int, Transaction*>::iterator it = mapTransaction.begin();
    while(it != mapTransaction.end()) {
        int num = it->first;
        Transaction *transaction = it -> second;
        cout << num << " : " << *transaction << endl;
        it++;
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

    // function that creates a vector of territories from the text file for salerep
    void declareSaleReps(ifstream& file) {
        // variables for SaleRep
        int saleRepId;
        int territoryId;
        int amount;
        char comma;
        char comma1;
        
        vector<SalesRep> salesRepVec;
        
        while(file.good()) {
            file >> saleRepId >> comma >> territoryId >> comma1 >> amount;
            //long saleRepIdInt = stol(saleRepId, &sz);
            SalesRep s(saleRepId, territoryId, amount);
            salesRepVec.push_back(s);
        }
        vector<SalesRep>::iterator it;
        for(it=salesRepVec.begin();it!=salesRepVec.end();++it) {
           cout<<(*it).getSaleRepId()<<" "<<(*it).getTerritoryId()<<" "<<(*it).getAmount()<< endl;
        }
    } // end of declareSaleReps


int main () {
    ifstream territoryFile("territory.txt");
    ifstream saleRepFile("salerep.txt");
    ifstream trxFile("transaction.txt");

   
    
   declareTerritories(territoryFile);
   loadTransactions(trxFile);

   // vector<Territory>::iterator it;
    //for(it=territories.begin();it!=territories.end();++it) {
      //  cout<<(*it).territoryId<<" "<<(*it).type<<endl;
    //}
    

    cout << "-----------------------------------" << endl;
    //declareSaleReps(saleRepFile);
    cout << "-----------------------------------" << endl;
    //declareTransactions(trxFile);

    return 0;
}