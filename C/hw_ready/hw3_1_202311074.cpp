#include <string>
#include <iostream>
using namespace std;

class Product {
protected:
    static int nextId;
    int id;
    string p_name;
    double p_price;
    double p_calorie;
public:
    Product(string name, double price, double calorie){
        p_name = name;
        p_price = price;
        p_calorie = calorie;
        id = ++nextId;
        cout << "[Constructor] Product created: "<< p_name << " (ID: " << id <<", Price: $" << p_price <<")" << endl;
    }
    virtual ~Product(){
        cout << "[Destructor] Product destroyed: " << p_name <<" (ID: "<< id <<") "<< endl;
    }
    virtual string getName() const { return p_name; }
    virtual double getPrice() const { return p_price; }
    virtual int getId() const { return id; }
    virtual void describe() const {
    cout << "Product: " << p_name << " (ID: " << id << ", Price: $" << p_price << ")\n";
    }
};

int Product::nextId = 0;

class Beverage : public Product {
public:
    Beverage(string name, double price, double calorie) : Product(name, price, calorie) {
        cout << "Beverage created: "<< p_name <<" (" << p_calorie <<" calories)" << endl;
    }
    void describe() const override {
        cout << "Beverage: " << getName() << " (ID: " << getId()
            << ", Price: $" << getPrice() << ", Calories: " << this->p_calorie << 
            " calories)\n";
    }
};

class Snack : public Product {
public:
    Snack(string name, double price, double calorie) : Product(name, price, calorie) {
        cout << "Snack created: "<< p_name <<" (" << p_calorie <<" calories)" << endl;
    }
    void describe() const override {
        cout << "Snack: " << getName() << " (ID: " << getId()
            << ", Price: $" << getPrice() << ", Calories: " << this->p_calorie <<
            " calories)\n";
    }
};

class VendingMachine;

class State {
protected:
    string s_name;
    VendingMachine* machine;
public:
    State(VendingMachine* machine){this->machine = machine;}
    virtual ~State(){}
    virtual string getName() const = 0;
    virtual void insertCoin(double coin) = 0;
    virtual void ejectCoin() = 0;
    virtual void dispense(string productName) = 0;
};

class NoCoinState : public State {
public:
    NoCoinState(VendingMachine* t_machine) : State(t_machine){
        s_name = "No Coin";        
        cout << "[Constructor] Constructing State: " << s_name << endl; 
    }
    ~NoCoinState() override {
        cout << "[Destructor] Destructing State: " << s_name << endl;
    };
    void insertCoin(double coin) override;
    void ejectCoin() override;
    void dispense(string productName) override;
    string getName() const override { return this->s_name; }
};

class HasCoinState : public State {
public:
    HasCoinState(VendingMachine* t_machine) : State(t_machine){
        s_name = "Has Coin";        
        cout << "[Constructor] Constructing State: " << s_name << endl; 
    }
    ~HasCoinState() override {
        cout << "[Destructor] Destructing State: " << s_name << endl;
    };
    void insertCoin(double coin) override;
    void ejectCoin() override;
    void dispense(string productName) override;
    string getName() const override { return this->s_name; }
};

class SoldOutState : public State {
public:
    SoldOutState(VendingMachine* t_machine) : State(t_machine){
        s_name = "Sold Out";        
        cout << "[Constructor] Constructing State: " << s_name << endl; 
    }
    ~SoldOutState() override {
        cout << "[Destructor] Destructing State: " << s_name << endl;
    };
    void insertCoin(double coins) override;
    void ejectCoin() override;
    void dispense(string productName) override;
    string getName() const override { return this->s_name; }
};

class VendingMachine {
private:
    State* noCoinState;
    State* hasCoinState;
    State* soldOutState;
    State* currentState;
    const int MAX_NUM_PRODUCT = 10;
    Product* inventory[10];
    int num_of_products;
    bool hasCoin;
    double coinValue;

    void printState(string action) const {
    cout << "Action: " << action << " | Current State: " << currentState->getName() << " | Coin Value: " << this->coinValue << "\n";
}
public:
    VendingMachine(){
        cout << "[Constructor] Constructing VendingMachine" << endl;
        noCoinState = new NoCoinState(this);
        hasCoinState = new HasCoinState(this);
        soldOutState = new SoldOutState(this);
        currentState = noCoinState;
        num_of_products = 0;
        hasCoin = false;
        coinValue = 0.0;
        printState("Initialization");
    }
    ~VendingMachine(){
        cout << "[Destructor] Destructing VendingMachine" << endl;
        for (int count3{0}; count3 < num_of_products; count3++){
            delete inventory[count3];
        }
        delete noCoinState;
        delete hasCoinState;
        delete soldOutState;
    }
    void setState(State* state){
        currentState = state;
        printState("State Changed");
    };
    void insertCoin(double coin){
        currentState->insertCoin(coin);
        printState("Insert Coin");
    };
    void ejectCoin(){            
        currentState->ejectCoin();
        printState("Eject Coin");
    };
    void dispense(string productName){
        currentState->dispense(productName);
        printState("Dispense");
    };
    Product* removeProduct(string productName){
        for (int counter1{0}; counter1 < getInventoryCount(); counter1++)
            if (productName == (inventory[counter1])->getName()){
                delete inventory[counter1];
                for (;counter1 < getInventoryCount(); counter1++){
                    inventory[counter1] = inventory[counter1+1];
                }
            }
            num_of_products -= 1;
            return 0;
        return 0;
    }
    void addProduct(Product* product){
        inventory[num_of_products] = product;
        num_of_products++;
        if (currentState->getName()=="Sold Out"){
            setState(noCoinState);
        }
    } 
    bool isProductAvailable(string productName) const{
        for (int counter1{0}; counter1 < num_of_products; counter1++)
            if (productName == (inventory[counter1])->getName()){
                return 1;
            }
        return 0;
    };
    double getProductPrice(string productName) const{
        for (int counter1{0}; counter1 < num_of_products; counter1++)
            if (productName == (inventory[counter1])->getName()){
                return inventory[counter1]->getPrice();
            }
        return 0;
    };
    void displayInventory() const{
        cout << "Current Inventory:" << endl;
        for (int counter1{0}; counter1 < num_of_products; counter1++)
            inventory[counter1]->describe();
        cout << "Total items: " << num_of_products << endl;
    }
    int getInventoryCount() const { return num_of_products; }
    State* getNoCoinState() const { return noCoinState; }
    State* getHasCoinState() const { return hasCoinState; }
    State* getSoldOutState() const { return soldOutState; }
    bool hasInsertedCoin() const { return hasCoin; }
    void setCoinInserted(bool inserted) { hasCoin = inserted; }
    double getCoinValue() const { return coinValue; }
    void resetCoinValue() { coinValue = 0.0; }
    void addCoinValue(double coin) {coinValue += coin;}
};

void NoCoinState::insertCoin(double coin){
    machine->addCoinValue(coin);
    machine->setState(machine->getHasCoinState());
    machine->setCoinInserted(true);}
void NoCoinState::ejectCoin(){}
void NoCoinState::dispense(string productname){        
    cout << "Insufficient funds. Please insert more coins." << endl;
    cout << "Current balance: $" << machine->getCoinValue() <<", Required: $" <<machine->getProductPrice(productname) << endl;               
    }

void HasCoinState::insertCoin(double coin){
    machine->addCoinValue(coin);}
void HasCoinState::ejectCoin(){
    if (machine->getCoinValue()!=0){     
        cout << "Change returned: $" << machine->getCoinValue() << endl;    
        machine->resetCoinValue();
    }
    machine->setCoinInserted(false);
    if (machine->getInventoryCount()==1){
        machine->setState(machine->getSoldOutState());
    }
    else{            
    machine->setState(machine->getNoCoinState());
    }}
void HasCoinState::dispense(string productname){    
    if (machine->isProductAvailable(productname)){
        if (machine->getCoinValue() >= machine->getProductPrice(productname)){
            machine->addCoinValue(-(machine->getProductPrice(productname))); 
            ejectCoin();                
            machine->removeProduct(productname);
        }
        else{
            cout << "Insufficient funds. Please insert more coins." << endl;
            cout << "Current balance: $" << machine->getCoinValue() <<", Required: $" <<machine->getProductPrice(productname) << endl;               
        }
    }
    else{
        cout << "No product to dispense" << endl;
    }}

void SoldOutState::insertCoin(double coin){
    cout << "SOLD OUT: No additional coin accepted" << endl;}
void SoldOutState::ejectCoin(){}
void SoldOutState::dispense(string productname){cout << "No product to dispense" << endl;}

int main() {
    cout << "==========Part 1==========" << endl;
    VendingMachine machine; //Create a VendingMachine instance
    Product* p_cola = new Beverage("Cola", 1.50, 330); //Create a new product
    Product* p_chips = new Snack("Chips", 1.00, 150); //Create a new product
    Product* p_water = new Beverage("Water", 1.00, 0); //Create a new product
    cout << "==========Part 2==========" << endl;
    //Add three products
    machine.addProduct(p_cola);
    machine.addProduct(p_chips);
    machine.addProduct(p_water);
    //Display inventory
    machine.displayInventory();
    cout << "==========Part 3==========" << endl;
    //Insert coin and dispense
    machine.insertCoin(1.00);
    machine.insertCoin(0.50);
    machine.dispense("Cola");
    cout << "==========Part 4==========" << endl;
    machine.insertCoin(1.00);
    machine.dispense("Water");
    cout << "==========Part 5==========" << endl;
    machine.insertCoin(0.50);
    machine.dispense("Chips"); // Should say insufficient funds
    machine.insertCoin(0.50);
    machine.dispense("Chips");
    cout << "==========Part 6==========" << endl;
    machine.insertCoin(1.00);
    machine.dispense("Candy"); // Should say product not available
    machine.displayInventory();
    cout << "==========Part 7==========" << endl;
    Product* p_chocolate = new Snack("Chocolate", 1.25, 200);
    Product* p_juice = new Beverage("Orange Juice", 1.75, 250);
    machine.addProduct(p_chocolate);
    machine.addProduct(p_juice);
    machine.displayInventory();
    cout << "==========Part 8==========" << endl;
    machine.insertCoin(2.00);
    machine.dispense("Chocolate");
    machine.insertCoin(2.00);
    machine.dispense("Orange Juice");
    machine.displayInventory();
    return 0;
}