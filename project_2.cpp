// Elisabeth Ashley
// Project 2 - process a set of transactions regarding a sale
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <unordered_map>
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
// function that creates a vector of territories from the text file, return the vector
void loadTerritories(ifstream& file) {
    string line; 
    int territoryId;
    char comma;
    string type; 
    int i = 0;
    while(  file >> territoryId >> comma >> type) {
        Territory * t = new Territory(territoryId, type);
        mapTerritories.insert(pair<int ,Territory *> (i, t));
        i++;
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
        //Client(int clientId, int amount);

}; // end of Client class
// should it be const?
ostream & operator<<(ostream &os, Transaction& t) {
    os  << t.getTrxId() << ", " << t.getSaleRepId() << ", " << t.getClientId() << ", " << t.getTrxType() << ", " << t.getAmount() << endl;
    return os;
}

map<int, Transaction *> mapTransaction;

void loadTransactions(ifstream& file) {
    // declare variables for Territory
    int trxId1, saleRepId1, clientId1, trxType1, amount1;
    char comma, comma1, comma2, comma3;
    int i = 0;
    // while loop to store objects
    while(file >> trxId1 >> comma >> saleRepId1 >> comma1 >> clientId1 >> comma2 >> trxType1 >> comma3 >> amount1) {
        Transaction * t = new Transaction(trxId1, saleRepId1, clientId1,trxType1, amount1);
        mapTransaction.insert(pair<int, Transaction*> (i, t)); // insert object into map
        i++; 
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
    int i = 0;
    while(file >> saleRepId >> comma >> territoryId >> comma1 >> amount) {
        // assign values to variable
        sr = new SalesRep(saleRepId, territoryId, amount);
        mapSaleReps.insert(pair<int, SalesRep*> (i, sr)); // insert object into map   
        i++;
    }
    
    map<int, SalesRep*>::iterator it = mapSaleReps.begin();
    while(it != mapSaleReps.end()) {
        int num = it->first;
        SalesRep * saleR = it -> second;
        cout << num << " : " << *saleR << endl;
        it++;
    }
} // end of loadSaleReps

// TEST
vector<double> clientsVec;
void calcTransaction(map<int, Transaction*> &t) {
    int i = 0;

    while(!t.empty()) {
      
        int client_Id = t.find(i)->second->getClientId();
 
        double clientsAmount;
        int type = t.find(i)->second->getTrxType();
        double amount = mapTransaction.find(i)->second->getAmount();
        double territoryAmount, saleRepAmount;
        if ((type == 1) || (type == 2) || type == 6) {
            territoryAmount = amount * 1; // calcualte territory
            saleRepAmount = amount * 1.10; // calculate for salerep
            clientsAmount = amount * 1; // calculate for client
            clientsVec.push_back(clientsAmount);
        } else if ( type == 3) {
            territoryAmount = amount * 1; // calcualte territory
            saleRepAmount = amount * 1; // calculate for salerep
            clientsAmount = amount * 1; // calculate for client
            clientsVec.push_back(clientsAmount);
        } else if (type == 4) {
            territoryAmount = amount * 1; // calcualte territory
            saleRepAmount = amount * 1.25; // calculate for salerep
            clientsAmount = amount * 1; // calculate for client
            clientsVec.push_back(clientsAmount);
        } else if ( type == 5) {
            territoryAmount = amount * 1; // calcualte territory
            saleRepAmount = amount * 0; // calculate for salerep
            clientsAmount = amount * 0; // calculate for client
            clientsVec.push_back(clientsAmount);
        } else if ( type == 7) {
            territoryAmount = amount * 0; // calcualte territory
            saleRepAmount = amount * .75; // calculate for salerep
            clientsAmount = amount * 0; // calculate for client
            clientsVec.push_back(clientsAmount);
        }  
    
        i++;
    }
 
    for (int i = 0; i < clientsVec.size(); i++) {
        cout << clientsVec[i] << endl;
    }
   
}


// END OF TEST


int main () {
    ifstream territoryFile("territory.txt");
    ifstream saleRepFile("salerep.txt");
    ifstream trxFile("transaction.txt");
   //loadTerritories(territoryFile);
    loadTransactions(trxFile);
   //loadSaleReps(saleRepFile);
    calcTransaction(mapTransaction);
    return 0;
}