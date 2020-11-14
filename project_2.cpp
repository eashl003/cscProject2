// Elisabeth Ashley
// Project 2 - process a set of transactions regarding a sale
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
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
        int clientId1;
        int trxType; // transaction type
        int amount;

    Transaction(int trxId, int saleRepId, int clientId1, int trxType, int amount) {
        this -> trxId = trxId;
        this -> saleRepId = saleRepId;
        this -> clientId1 = clientId1;
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
    int getClientId1() {
        return clientId1;
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
    os  << t.getTrxId() << ", " << t.getSaleRepId() << ", " << t.getClientId1() << ", " << t.getTrxType() << ", " << t.getAmount() << endl;
    return os;
}

map<int, Transaction *> mapTransaction;

void loadTransactions(ifstream& file) {
    // declare variables for Territory
    int trxId, saleRepId, clientId, trxType, amount;
    char comma, comma1, comma2, comma3;
    int i = 0;
    // while loop to store objects
    while(file >> trxId >> comma >> saleRepId >> comma1 >> clientId >> comma2 >> trxType >> comma3 >> amount) {
        Transaction * t = new Transaction(trxId, saleRepId, clientId,trxType, amount);
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

ostream & operator<<(ostream &os, Client& c) {
    os  << c.getClientId() << ", " << c.getAmount() << endl;
    return os;
}


// test
void calcTransaction(map<int, Transaction*> &t) {
    int i = 0;
    vector<Client*> clientsVec;
    while(!t.empty()) {
     
            int clientId = t.find(i)->second->getClientId1();
            int type = t.find(i)->second->getTrxType();
            double amount = mapTransaction.find(i)->second->getAmount();
            double territoryAmount, saleRepAmount, clientsAmount;
            if ((type == 1) || (type == 2) || type == 6) {
                territoryAmount = amount * 1; // calcualte territory
                saleRepAmount = amount * 1.10; // calculate for salerep
                clientsAmount = amount * 1; // calculate for client
            } else if ( type == 3) {
                territoryAmount = amount * 1; // calcualte territory
                saleRepAmount = amount * 1; // calculate for salerep
                clientsAmount = amount * 1; // calculate for client
            } else if (type == 4) {
                territoryAmount = amount * 1; // calcualte territory
                saleRepAmount = amount * 1.25; // calculate for salerep
                clientsAmount = amount * 1; // calculate for client
            } else if ( type == 5) {
                territoryAmount = amount * 1; // calcualte territory
                saleRepAmount = amount * 0; // calculate for salerep
                clientsAmount = amount * 0; // calculate for client
            } else if ( type == 7) {
                territoryAmount = amount * 0; // calcualte territory
                saleRepAmount = amount * .75; // calculate for salerep
                clientsAmount = amount * 0; // calculate for client
            } 
            Client * c = new Client(clientId, clientsAmount);
            clientsVec.push_back(c);
            i++;
        
    }
    // print vector
    //for (std::vector<Client*>::iterator i = clientsVec.begin(); i != clientsVec.end(); ++i)
    //std::cout << (*i) << ' ';
    cout << clientsVec[2]->getClientId();
}


// end of test


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