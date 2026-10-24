
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

class Product {
public:
    int id;
    string name;
    double price;
    int stock;

    Product(int i, string n, double p, int s) {
        id = i;
        name = n;
        price = p;
        stock = s;
    }

    void display() const {
        cout << left << setw(8) << id
             << setw(20) << name
             << "Rs. " << fixed << setprecision(2)
             << setw(10) << price
             << "Stock: " << stock << endl;
    }
};

class ShoppingCart {
private:
    vector<int> productIDs;
    vector<int> quantities;

public:
    void addProduct(vector<Product>& products, int id, int qty) {
        for (int i = 0; i < (int)products.size(); i++) {
            if (products[i].id == id) {
                if (qty <= 0) {
                    cout << "Invalid quantity!\n";
                    return;
                }

                int index = -1;
                for (int j = 0; j < (int)productIDs.size(); j++) {
                    if (productIDs[j] == id) {
                        index = j;
                        break;
                    }
                }

                int alreadyAdded = (index == -1) ? 0 : quantities[index];

                if (qty + alreadyAdded > products[i].stock) {
                    cout << "Not enough stock available!\n";
                    return;
                }

                if (index == -1) {
                    productIDs.push_back(id);
                    quantities.push_back(qty);
                } else {
                    quantities[index] += qty;
                }

                cout << "Product added to cart!\n";
                return;
            }
        }

        cout << "Product not found!\n";
    }

    void displayCart(const vector<Product>& products) const {
        double total = 0;

        cout << "\n========== SHOPPING CART ==========\n";

        if (productIDs.empty()) {
            cout << "Your cart is empty!\n";
            return;
        }

        for (int i = 0; i < (int)productIDs.size(); i++) {
            for (const Product& p : products) {
                if (p.id == productIDs[i]) {
                    double subtotal = p.price * quantities[i];

                    cout << p.name
                         << " | Quantity: " << quantities[i]
                         << " | Subtotal: Rs. "
                         << fixed << setprecision(2)
                         << subtotal << endl;

                    total += subtotal;
                    break;
                }
            }
        }

        double discount = (total >= 2000) ? total * 0.10 : 0;
        double finalAmount = total - discount;

        cout << "-----------------------------------\n";
        cout << "Total Amount : Rs. " << total << endl;
        cout << "Discount     : Rs. " << discount << endl;
        cout << "Final Bill   : Rs. " << finalAmount << endl;
    }
};

int main() {
    vector<Product> products = {
        Product(101, "Keyboard", 800, 10),
        Product(102, "Mouse", 400, 15),
        Product(103, "Headphones", 1200, 8),
        Product(104, "USB Drive", 600, 12),
        Product(105, "Webcam", 1800, 5)
    };

    ShoppingCart cart;
    int choice;

    do {
        cout << "\n===== ONLINE SHOPPING SYSTEM =====\n";
        cout << "1. View Products\n";
        cout << "2. Add Product to Cart\n";
        cout << "3. View Cart and Bill\n";
        cout << "4. Checkout\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nID      Product             Price      Stock\n";
            cout << "---------------------------------------------\n";
            for (const Product& p : products) {
                p.display();
            }
            break;

        case 2: {
            int id, qty;

            cout << "Enter product ID: ";
            cin >> id;
            cout << "Enter quantity: ";
            cin >> qty;

            cart.addProduct(products, id, qty);
            break;
        }

        case 3:
            cart.displayCart(products);
            break;

        case 4:
            cout << "\nCheckout summary:\n";
            cart.displayCart(products);
            cout << "Please verify your bill before payment.\n";
            break;

        case 5:
            cout << "Thank you for shopping!\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
