// Elisabeth Ashley
// Project 2 - process a set of transactions regarding a sale
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
/*
    // function to check if territory is premium or normal - 0 they compare equal
    bool isTerritoryPremium(string territory type){
        string premiumStr ("PREMIUM");
        if (premiumStr.compare(type) == 0) {
            return true;
        } else {
            return false;
        }
    }
*/
}; // end of Territory class

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
    int getTrxTyep() { 
        return trxType;
    }
    int getAmount() {
        return amount;
    }
}; // end of Transaction class

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

    // function that creates a vector of territories from the text file 
    void declareTerritories(ifstream& file) {
        // variables for territory 
        int territoryId;
        char comma;
        string type = "";
        vector<Territory> territories;
        while(file.good()) {
            file >> territoryId >> comma >> type;
            Territory t(territoryId, type);
            territories.push_back(t);
        }
        vector<Territory>::iterator it;
        for(it=territories.begin();it!=territories.end();++it) {
           cout<<(*it).territoryId<<" "<<(*it).type<<endl;
        }
    } // end of loadTerritories
    // function that transaction a vector of transactions from the text file for transactions.txt
    void declareTransactions(ifstream& file) {
        int trxId; // transaction id
        int saleRepId;
        int clientId;
        int trxType; // transaction type
        int amount;
        char comma;
        char comma1;
        char comma2;
        char comma3;
        vector<Transaction> transactionsVec;
        while(file.good()) {
            file >> trxId >> comma >> saleRepId >> comma1 >> clientId >> comma2 >> trxType >> comma3 >> amount;
            Transaction t(trxId, saleRepId, clientId, trxType, amount);
            transactionsVec.push_back(t);
        }
        vector<Transaction>::iterator it;
        for(it=transactionsVec.begin();it!=transactionsVec.end();++it) {
           cout<<(*it).trxId<<" "<<(*it).saleRepId<<" "<<(*it).clientId<<" "<<(*it).trxType<<" "<<(*it).amount<<endl;
        }
    }
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
    cout << "-----------------------------------" << endl;
    declareSaleReps(saleRepFile);
    cout << "-----------------------------------" << endl;
    declareTransactions(trxFile);

    return 0;
}