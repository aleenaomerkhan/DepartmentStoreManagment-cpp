#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Product {
    int id;
    string name;
    float price;
    int quantity;
};

void addProduct() {
    Product p;
    ofstream file("products.txt", ios::app);

    cout << "Enter Product ID: ";
    cin >> p.id;
    cout << "Enter Product Name: ";
    cin >> p.name;
    cout << "Enter Price: ";
    cin >> p.price;
    cout << "Enter Quantity: ";
    cin >> p.quantity;

    file << p.id << " " << p.name << " " << p.price << " " << p.quantity << endl;
    file.close();

    cout << "Product Added Successfully!\n";
}

void viewProducts() {
    Product p;
    ifstream file("products.txt");

    cout << "\nID\tName\tPrice\tQuantity\n";
    cout << "----------------------------------\n";

    while (file >> p.id >> p.name >> p.price >> p.quantity) {
        cout << p.id << "\t" << p.name << "\t" << p.price << "\t" << p.quantity << endl;
    }

    file.close();
}

void searchProduct() {
    int id;
    Product p;
    bool found = false;

    cout << "Enter Product ID to Search: ";
    cin >> id;

    ifstream file("products.txt");

    while (file >> p.id >> p.name >> p.price >> p.quantity) {
        if (p.id == id) {
            cout << "Product Found!\n";
            cout << "Name: " << p.name << endl;
            cout << "Price: " << p.price << endl;
            cout << "Quantity: " << p.quantity << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Product Not Found!\n";

    file.close();
}

void deleteProduct() {
    int id;
    Product p;

    cout << "Enter Product ID to Delete: ";
    cin >> id;

    ifstream file("products.txt");
    ofstream temp("temp.txt");

    bool found = false;

    while (file >> p.id >> p.name >> p.price >> p.quantity) {
        if (p.id == id) {
            found = true;
        } else {
            temp << p.id << " " << p.name << " " << p.price << " " << p.quantity << endl;
        }
    }

    file.close();
    temp.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");

    if (found)
        cout << "Product Deleted Successfully!\n";
    else
        cout << "Product Not Found!\n";
}

/////// NEW FEATURE 1 – UPDATE PRODUCT ///////

void updateProduct() {
    int id;
    Product p;

    cout << "Enter Product ID to Update: ";
    cin >> id;

    ifstream file("products.txt");
    ofstream temp("temp.txt");

    bool found = false;

    while (file >> p.id >> p.name >> p.price >> p.quantity) {
        if (p.id == id) {
            cout << "Enter New Price: ";
            cin >> p.price;
            cout << "Enter New Quantity: ";
            cin >> p.quantity;

            found = true;
        }

        temp << p.id << " " << p.name << " " << p.price << " " << p.quantity << endl;
    }

    file.close();
    temp.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");

    if (found)
        cout << "Product Updated Successfully!\n";
    else
        cout << "Product Not Found!\n";
}

/////// NEW FEATURE 2 – TOTAL BILL ///////

void generateBill() {
    int id, qty;
    Product p;
    float total = 0;
    char choice;

    do {
        cout << "Enter Product ID: ";
        cin >> id;
        cout << "Enter Quantity: ";
        cin >> qty;

        ifstream file("products.txt");
        bool found = false;

        while (file >> p.id >> p.name >> p.price >> p.quantity) {
            if (p.id == id) {
                total += p.price * qty;
                found = true;
                cout << p.name << " Added to Bill\n";
                break;
            }
        }

        if (!found)
            cout << "Product Not Found!\n";

        file.close();

        cout << "Add More Items? (y/n): ";
        cin >> choice;

    } while (choice == 'y');

    cout << "\n==== TOTAL BILL ====\n";
    cout << "Total Amount: " << total << endl;
}

int main() {
    int choice;

    do {
        cout << "\n==== Department Store Management ====\n";
        cout << "1. Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Search Product\n";
        cout << "4. Delete Product\n";
        cout << "5. Update Product\n";
        cout << "6. Generate Bill\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                updateProduct();
                break;
            case 6:
                generateBill();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
