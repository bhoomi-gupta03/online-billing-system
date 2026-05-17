#include <iostream>
#include <vector>

using namespace std;

class Product
{
private:
    int id;
    string name;
    float price;

public:
    Product(int i, string n, float p)
    {
        id = i;
        name = n;
        price = p;
    }

    int getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    float getPrice()
    {
        return price;
    }

    void display()
    {
        cout << id << " | "
             << name << " | Rs."
             << price << endl;
    }
};

class CartItem
{
public:
    Product product;
    int quantity;

    CartItem(Product p, int q)
        : product(p), quantity(q)
    {
    }
};

class User
{
private:
    string username;
    string password;

public:
    User(string u, string p)
    {
        username = u;
        password = p;
    }

    string getUsername()
    {
        return username;
    }

    string getPassword()
    {
        return password;
    }
};

class AuthSystem
{
private:
    vector<User> users;

public:

    void signup()
    {
        string username, password;

        cout << "\n===== SIGN UP =====\n";

        cout << "Enter Username: ";
        cin >> username;

        cout << "Enter Password: ";
        cin >> password;

        for(User u : users)
        {
            if(u.getUsername() == username)
            {
                cout << "Username Already Exists\n";
                return;
            }
        }

        users.push_back(User(username, password));

        cout << "Account Created Successfully\n";
    }

    bool login()
    {
        string username, password;

        cout << "\n===== LOGIN =====\n";

        cout << "Enter Username: ";
        cin >> username;

        cout << "Enter Password: ";
        cin >> password;

        for(User u : users)
        {
            if(u.getUsername() == username
               &&
               u.getPassword() == password)
            {
                cout << "Login Successful\n";

                return true;
            }
        }

        cout << "Invalid Username or Password\n";

        return false;
    }
};

class Cart
{
private:
    vector<CartItem> items;

public:
    void addProduct(Product p, int quantity)
    {
        for(auto &item : items)
        {
            if(item.product.getId() == p.getId())
            {
                item.quantity += quantity;

                cout << "Quantity Updated\n";
                return;
            }
        }

        items.push_back(CartItem(p, quantity));

        cout << "Product Added To Cart\n";
    }

    void removeProduct(int id)
    {
        for(auto it = items.begin(); it != items.end(); it++)
        {
            if(it->product.getId() == id)
            {
                items.erase(it);

                cout << "Product Removed\n";
                return;
            }
        }

        cout << "Product Not Found In Cart\n";
    }

    void showCart()
    {
        if(items.empty())
        {
            cout << "Cart is Empty\n";
            return;
        }

        float total = 0;

        cout << "\n===== CART =====\n";

        for(auto item : items)
        {
            float subtotal =
                item.product.getPrice() * item.quantity;

            cout << item.product.getName()
                 << " | Qty: "
                 << item.quantity
                 << " | Rs."
                 << subtotal
                 << endl;

            total += subtotal;
        }

        cout << "\nTotal Bill: Rs."
             << total << endl;
    }
};
int main()
{
    vector<Product> products;

    products.push_back(Product(1, "Laptop", 55000));
    products.push_back(Product(2, "Phone", 25000));
    products.push_back(Product(3, "Headphones", 2000));
    products.push_back(Product(4, "Keyboard", 1500));

    Cart cart;

    AuthSystem auth;

    int mainChoice;

    while(true)
    {
        cout << "\n===== SMART CART =====\n";

        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cin >> mainChoice;

        if(mainChoice == 1)
        {
            auth.signup();
        }

        else if(mainChoice == 2)
        {
            bool loggedIn = auth.login();

            if(loggedIn)
            {
                int choice;

                while(true)
                {
                    cout << "\n===== SHOPPING MENU =====\n";

                    cout << "1. View Products\n";
                    cout << "2. Add To Cart\n";
                    cout << "3. View Cart\n";
                    cout << "4. Remove From Cart\n";
                    cout << "5. Logout\n";

                    cin >> choice;

                    if(choice == 1)
                    {
                        cout << "\nAvailable Products:\n";

                        for(Product p : products)
                        {
                            p.display();
                        }
                    }

                    else if(choice == 2)
                    {
                        int id, quantity;

                        cout << "Enter Product ID: ";
                        cin >> id;

                        cout << "Enter Quantity: ";
                        cin >> quantity;

                        bool found = false;

                        for(Product p : products)
                        {
                            if(p.getId() == id)
                            {
                                cart.addProduct(p, quantity);

                                found = true;
                                break;
                            }
                        }

                        if(!found)
                        {
                            cout << "Invalid Product ID\n";
                        }
                    }

                    else if(choice == 3)
                    {
                        cart.showCart();
                    }

                    else if(choice == 4)
                    {
                        int id;

                        cout << "Enter Product ID To Remove: ";
                        cin >> id;

                        cart.removeProduct(id);
                    }

                    else if(choice == 5)
                    {
                        cout << "Logged Out\n";
                        break;
                    }

                    else
                    {
                        cout << "Invalid Choice\n";
                    }
                }
            }
        }

        else if(mainChoice == 3)
        {
            cout << "Thank You!\n";
            break;
        }

        else
        {
            cout << "Invalid Choice\n";
        }
    }

    return 0;
}

