#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

class Product {
private:
    string name;
    double price;
    int quantity;
    bool IsShippable = 0;
    bool IsExpirable = 0;
    int Weight = 0;
public:
    Product(string name, double price, int quantity)
        : name(name), price(price), quantity(quantity){ }

    Product(string name, double price, int quantity, bool IsExpirable)
        : name(name), price(price), quantity(quantity), IsExpirable(IsExpirable) {
    }

    Product(string name, double price, int quantity, bool IsShippable, int Weight)
        : name(name), price(price), quantity(quantity), IsShippable(IsShippable), Weight(Weight) {
    }

    Product(string name, double price, int quantity, bool IsShippable, bool IsExpirable, int Weight)
        : name(name), price(price), quantity(quantity), IsShippable(IsShippable), IsExpirable(IsExpirable), Weight(Weight) {
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    int getQuantity() {
        return quantity;
    }

    bool IsShipping() {
        return IsShippable;
    }

    bool IsExpired() {
        return IsExpirable;
    }

    int getWeight() {
        return Weight;
    }

    bool Is_in_Stock(int Quantity_Needed) {
        return quantity >= Quantity_Needed;
    }

    void ReduceStock(int QuantityToReduce) {
        if (Is_in_Stock(QuantityToReduce)) {
            quantity -= QuantityToReduce;
        }
    }

};

class Customer {
    string name;
    double Balance;
public:
    Customer(string name, double Balance)
        :name(name), Balance(Balance){ }
    
    double getName() {
        return Balance;
    }

    double getBalance() {
        return Balance;
    }

    bool CanDeduct (double amount) {
        return Balance >= amount;
    }

    void DeductBalance(double amount) {
        if (Balance >= amount) {
            Balance -= amount;
        }
    }
};

class Cart {
    map<Product*, int> items;

public:
    void addProduct(Product* product, int quantity) {
        if (quantity <= 0) return; 

        if (!product->Is_in_Stock(quantity)) {
            cout << "Warning: Cannot add " << quantity << " of " << product->getName()
                << ". Only " << product->getQuantity() << " available." << endl;
            return;
        }

        items[product] += quantity;
        cout << product->getName() << " added to cart." << endl;
    }

    map<Product*, int> getItems() {
        return items;
    }

    bool isEmpty() {
        return items.empty();
    }

    void clear() {
        items.clear();
    }
};

class Shipping {
public:
    void send(vector<pair<Product*, int>> shippableItems) {
        if (shippableItems.empty()) {
            return;
        }

        cout << "** Shipment notice **" << endl;
        double totalWeight = 0;

        for (auto& shippableItem : shippableItems) {
            Product* item = shippableItem.first;
            int quantity = shippableItem.second;
            double itemTotalWeight = item->getWeight() * quantity;
            totalWeight += itemTotalWeight;
            cout << quantity << "x " << item->getName() << "\t";
            cout << itemTotalWeight << "g" << endl;
        }
        cout << "Total package weight " << totalWeight / 1000.0 << "kg" << endl;
        cout << "-----------------------------" << endl;
    }
};

void checkout(Customer& customer, Cart& cart, Shipping shipping) {
    cout << "\n\n";
    if (cart.isEmpty()) {
        cout << "Error: Cart is empty. Cannot checkout.\n\n";
        return;
    }

    double subtotal = 0;
    vector<pair<Product*, int>> shippableItems;

    for (auto& item : cart.getItems()) {
        Product* product = item.first;
        int quantity = item.second;
        
        if (!product->Is_in_Stock(quantity)) {
            cout << "Error: Product '" + product->getName() + "' is out of stock.\n\n";
            return;
        }

        if (product->IsExpired()) {
            cout << "Error: Product '" + product->getName() + "' is expired.\n\n";
            return;
        }

        subtotal += product->getPrice() * quantity;

        if (product->IsShipping()) {
            shippableItems.push_back({ product, quantity });
        }
    }

    double shippingFees = 30;
    double totalAmount = subtotal + shippingFees;

    if (!customer.CanDeduct(totalAmount)) {
        cout << "Error: Insufficient balance. Required: $" + to_string(totalAmount)
            + ", Available: $" + to_string(customer.getBalance()) + "\n\n";
        return;
    }

    shipping.send(shippableItems);

    cout << "** Checkout receipt **" << endl;
    for (auto& item : cart.getItems()) {
        Product* product = item.first;
        int quantity = item.second;
        cout << quantity << "x " << product->getName() << "\t";
        cout << fixed << setprecision(2) << product->getPrice() * quantity << endl;

        product->ReduceStock(quantity);
    }

    cout << "Subtotal\t" << subtotal << endl;
    cout << "Shipping\t" << shippingFees << endl;
    cout << "Amount\t\t" << totalAmount << endl;
    cout << "-----------------------------" << endl;

    customer.DeductBalance(totalAmount);

    cart.clear();
}

int main() {

    // This products is shippable and expirable
    Product rice("rice", 150, 5, 1, 0, 500);
    Product cheese("cheese", 150, 10, 1, 0, 200);

    // This product is simple
    Product scratch_card("scratch_card", 20, 15);

    // This product is shippable only
    Product cell_phone("cell_phone", 1000, 2, 1, 200);


    Customer Nader("Nader", 10000);

    Cart cart;

    Shipping service;

    //cart.addProduct(&cell_phone, 1);
    //cart.addProduct(&cheese, 1);
    cart.addProduct(&scratch_card, 5);

    checkout(Nader, cart, service);
}