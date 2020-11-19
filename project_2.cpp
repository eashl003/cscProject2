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



//map<int , double> tIdAmountMap; // key is trxId and value is current amount
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
    typedef std::multimap<int, double>::iterator itt;
    for (int i = 1000; i < 1005; i++) {
        std::pair<itt, itt> result = cIdAmountMap.equal_range(i);
        for (itt it = result.first; it != result.second; it++) {
            if (i == 1000) {
                sum0 += it->second; // this will sum up the total about for client
            } else if (i == 1001) {
                sum1 += it->second; 
            } else if (i == 1002) {
                sum2 += it->second; 
            } else if (i == 1003) {
                sum3 += it->second; 
            } else if (i == 1004) {
                sum4 += it->second; 
            }
        }
    }
    cout << "1000 " << sum0 << endl; 
    cout << "1001 " << sum1 << endl;   
    cout << "1002 " << sum2 << endl;
    cout << "1003 " << sum3 << endl;  
    cout << "1004 " << sum4 << endl;    
} // end of calcTransaction2()

vector<double> sums;
vector<int> salesId;
multimap<int, double> srIdAmountMap; // key is trxId and value is amount
map<int,double> thinkofbettana; 
void calcSaleRepsTransactions(map<int, Transaction *> m) {
    double saleRepRatio[] = {1.10, 1.10, -1 , -1.25, 0, -1.10, 0.75};
    double srAmount; // sale rep amount and total is for the amount earned by each sales rep
    //double sum0, sum1, sum2, sum3, sum4, sum5, sum6, sum7, sum8, sum9, sum10, sum11, sum12;

    map<int, Transaction *>::iterator it = m.begin();
    while( it != m.end()) {
        Transaction * t = it->second; // returns transaction object
        srAmount = t->getAmount() * saleRepRatio[t->getTrxType() - 1]; 
        srIdAmountMap.insert(pair<int, double>(t->getSaleRepId(), srAmount));

        vector<int>::iterator iv = find(salesId.begin(), salesId.end(), t->getSaleRepId());
        if (iv == salesId.end()) {
            salesId.push_back(t->getSaleRepId());
        } 

        it++;
    }

    typedef std::multimap<int, double>::iterator itt;
    for (int i = 1; i <= salesId.size(); i++) {
      
        std::pair<itt, itt> result = srIdAmountMap.equal_range(salesId[i]);
      
        for (itt it = result.first; it != result.second; it++) {
            
            if(salesId[i]){
                sums.push_back(it->second);
            }
            
        }
    }



    for (int i = 0; i < salesId.size(); i++) {
       cout << salesId[i] << "#---------------#"<<"total money is: " <<"#----------------#"<< sums[i] << endl;
    }
      
}

void updateSaleFile(){
    fstream f("salesrep.txt", ios::in);
    string line;
    if(f.is_open()){
        getline(f,line);
        while(f){
            getline(f,line);
        }
        f.close();
         
    }
}




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
    calcClientsTransactions(mapTransaction);
    fclose(stdout);
    freopen ("SalesRep_output.txt","w",stdout);
    calcSaleRepsTransactions(mapTransaction);
    fclose(stdout);


    
    return 0;
}