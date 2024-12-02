#include <iostream>
#include <string>
using namespace std;

// Admin panel side

class adminAuthorization
{
private:
    string username;
    string password;

public:
    adminAuthorization()
    {
        username = "mustafa";
        password = "mustafa123";
    }

    void changeCredentials(string userentered)
    {
        if (this->username == userentered)
        {
            cout << "Enter the new username " << endl;
            cin >> username;
            cout << "Enter the new Password " << endl;
            cin >> password;
            cout << "Your username and password is successfully changed" << endl;
        }
        else
        {
            cout << "Incorrect username, try again" << endl;
        }
    }

    bool login()
    {
        string enteredUsername, enteredPassword;
        cout << "Enter Username " << endl;
        cin >> enteredUsername;
        cout << "Enter Password " << endl;
        cin >> enteredPassword;

        if (enteredUsername == username && enteredPassword == password)
        {
            cout << "Welcome Back " << username << endl;
        }
        else
        {
            cout << enteredUsername << " and " << enteredPassword << "is incorrect" << endl;
        }
    }
};

class foodItem
{
public:
    string name;
    int id;
    float price;
    foodItem() {}
    foodItem(string nam, int id, float price)
    {
        this->name = nam;
        this->id = id;
        this->price = price;
    }

    void displayFood()
    {
        cout << "Item name is: " << name << endl;
        cout << "Item price is: " << price << endl;
        cout << "Item ID is: " << id << endl;
    }
};

class itemsNode
{
public:
    foodItem items;
    itemsNode *next;
    itemsNode() {}
    itemsNode(foodItem item)
    {
        this->items = item;
        this->next = NULL;
    }
};

class menu
{
public:
    itemsNode *head;
    menu()
    {
        head = NULL;
    }

    void addItems(foodItem item)
    {
        itemsNode *newNode = new itemsNode(item);
        itemsNode *temp = head;

        if (head == NULL)
        {
            head = newNode;
        }
        else
        {

            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void removeFoodItem(int id)
    {

        if (head == NULL)
        {
            cout << "No items in the menu to remove." << endl;
            return;
        }
        if (head->items.id == id)
        {
            itemsNode *temp = head;
            head = head->next;
            delete temp;
            cout << "The item with id " << id << " in head is successfully deleted" << endl;
            return;
        }

        itemsNode *temp = head;
        while (temp->next != NULL && temp->items.id != id)
        {
            if (temp->next->items.id == id)
            {
                itemsNode *toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                cout << "The item with id " << id << " is successfully deleted" << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Item with Id " << id << " not found" << endl;
    }

    void updateItemsInformation(int id, string newName, float newPrice)
    {
        itemsNode *temp = head;

        if (head == NULL)
        {
            cout << "There is No item in the menu to update its information" << endl;
            return;
        }

        else
        {
            while (temp != NULL)
            {
                if (temp->items.id == id)
                {
                    temp->items.name = newName;
                    temp->items.price = newPrice;
                    cout << "Item with id: " << id << " is Successfully changed its Information " << endl;

                    return;
                }
                temp = temp->next;
            }

            cout << "Item with id: " << id << " is not found" << endl;
        }
    }

    void viewMenu()
    {
        if (head == NULL)
        {
            cout << "There is no item in the menu to show " << endl;
            return;
        }
        else
        {
            itemsNode *temp = head;
            cout << endl;
            while (temp != NULL)
            {
                cout << "Item Name is: " << temp->items.name << endl;
                cout << "Item Price is: " << temp->items.price << endl;
                cout << "Item Id is: " << temp->items.id << endl;
                temp = temp->next;
                cout << endl;
            }
        }
    }
};

class order
{
public:
    foodItem itms;
    int Order_id;
    string orderStatus;

    double totalCost;

    order() {}

    order(foodItem items, int ord, string status, double bill)
    {
        this->itms = items;
        this->Order_id = ord;
        this->orderStatus = status;

        this->totalCost = bill;
    }
};
class node
{
public:
    order data;
    node *next;
    node(order datas)
    {
        this->data = datas;
        next = NULL;
    }
};

class queue
{

public:
    node *front;
    node *back;

    queue()
    {
        this->front = NULL;
        this->back = NULL;
    }
    void enqueue(order orders)
    {
        node *newNode = new node(orders);
        if (isEmpty())
        {
            front = back = newNode;
            return;
        }
        else
        {
            back->next = newNode;
            back = newNode;
        }
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "No items to dequeue" << endl;
            return;
        }
        else
        {
            node *temp = front;
            front = front->next;
            delete temp;

            if (front == NULL)
            {
                back = NULL;
            }
        }
    }

    bool isEmpty()
    {
        return front == NULL;
    }

    order peek()
    {
        if (isEmpty())
        {
            cout << "There are no orders" << endl;
            return order();
        }
        else
        {
            return front->data;
        }
    }
};

class salesManager
{
public:
    double totalsales;
    salesManager()
    {
        this->totalsales = 0.0;
    }
    
    void CompletedOrders(order completedOrders)
    {
        if (completedOrders.orderStatus == "completed")
        {
            totalsales += completedOrders.totalCost;
            cout << "The order with Order Id: " << completedOrders.Order_id << " proccessed" << endl;
        }
        else
        {
            cout << "The order with Order Id: " << completedOrders.Order_id << " not proccessed" << endl;
        }
    }

    void displayTotalCost()
    {
        cout << "The total sale of the day: " << totalsales << endl;
    }
};

/*Customer functionalities start*/
queue pendingOrders;
queue completedOrders;
class customer
{
public:
    string name;

    customer() {}
    customer(string CustName)
    {
        this->name = CustName;
    }

    void updateStatus(queue *pendingOrders, int id, salesManager &manager)
    {
        if (pendingOrders->isEmpty())
        {
            cout << "No orders in pending." << endl;
            return;
        }
        else
        {
            node *temp = pendingOrders->front;
            node *prev = NULL;
            while (temp != NULL)
            {
                if (temp->data.Order_id == id)
                {
                    if (temp->data.orderStatus == "pending")
                    {
                        cout << "Order found and marked as completed" << endl;
                        temp->data.orderStatus = "completed";

                        completedOrders.enqueue(temp->data);

                        manager.CompletedOrders(temp->data);

                        if (prev == NULL)
                        {
                            pendingOrders->dequeue();
                        }
                        else
                        {
                            prev->next = temp->next;
                            if (temp == pendingOrders->back)
                            {
                                pendingOrders->back = prev;
                            }
                            delete temp;
                        }
                        cout << "Order successfully moved to the completed orders list" << endl;
                        return;
                    }
                    else
                    {
                        cout << "Order is already marked as completed" << endl;
                        return;
                    }
                }
                prev = temp;
                temp = temp->next;
            }
            cout << "Order with ID " << id << " not found" << endl;
        }
    }

    void checkMenuANDPlaceOrder(menu &menuItems)
    {
        int itemId, quantity;

        float totalPrice = 0.0;

        cout << "Welcome  ****" << name << "****  below is the menu " << endl;
        menuItems.viewMenu();
        cout<<endl;
        cout << "To place an order, enter the item ID from the above menu (enter -1 to stop): " << endl;
        while (true)
        {
            cin >> itemId;
            if (itemId == -1)
                break;

            itemsNode *item = menuItems.head;
            while (item != NULL && item->items.id != itemId)
                item = item->next;

            if (item != NULL)
            {
                cout << "Enter quantity for item " << item->items.name << ": ";
                cin >> quantity;

                float itemTotal = item->items.price * quantity;
                totalPrice += itemTotal;

                order newOrder(item->items, itemId, "pending", itemTotal);
                pendingOrders.enqueue(newOrder);

                cout << quantity << " " << item->items.name << " added to your order." << endl;
            }
            else
            {
                cout << "Invalid item ID. Please try again." << endl;
            }
        }

        cout << "Your total order cost is: " << totalPrice << endl;
    }
};

/*Main function start here*/

int main()
{
    adminAuthorization auth;
    menu men;
    order ord;
    salesManager sales;
    queue orders;
    customer cust;
    foodItem item1("pizza", 111, 245);
    foodItem item2("Burger", 222, 400);
    foodItem item3("Pasta", 333, 200);
    foodItem item4("Chicken", 444, 450);
    men.addItems(item1);
    men.addItems(item2);
    men.addItems(item3);
    men.addItems(item4);

    int choice = -1;
    cout << endl;

    cout << "**************Restuarant Managment System****************" << endl;
        

    do
    {
        cout << "1.Admin panel" << endl;
        cout << "2.Customer" << endl;
        cout << "0.Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            bool logedIn = auth.login();
            if (logedIn)
            {
                int select;
                do
                {
                    cout << "Below are the operations you can perform " << endl;
                         
                    cout << "1.Change credentials" << endl;
                    cout << "2.Add new food Item" << endl;
                    cout << "3.Remove existing food item from the menu" << endl;
                    cout << "4.Update Existing food item from the menu" << endl;
                    cout << "5.View Menu" << endl;
                    cout << "6.Check total sales" << endl;
                    cout << "7.Check and update order status" << endl;
                    cout << "0. Logout" << endl;
                    cin >> select;

                    switch (select)
                    {
                    case 1:
                    {
                        string userName = "";
                        cout << "Enter the Username" << endl;
                        cin >> userName;
                        auth.changeCredentials(userName);
                        break;
                    }
                    case 2:
                    {

                        string name = "";
                        int id2 = 0;
                        float price = 0.0;
                        cout << "Enter the Name of the Item " << endl;
                        cin >> name;
                        cout << "Enter the Id of the Item" << endl;
                        cin >> id2;
                        cout << "Enter the price of the Item" << endl;
                        cin >> price;

                        foodItem newItem(name, id2, price);
                        men.addItems(newItem);
                        cout << "Food item added Successfully" << endl;
                        break;
                    }
                    case 3:
                    {
                        int id3 = 0;
                        cout << "Enter the Id of the item that you want to remove" << endl;
                        cin >> id3;
                        men.removeFoodItem(id3);
                        break;
                    }
                    case 4:
                    {
                        int id = 0;
                        string newName = "";
                        float newPrice = 0.0;
                        cout << "Enter the ID of the food item to update: ";
                        cin >> id;
                        cout << "Enter the new name: ";
                        cin >> newName;
                        cout << "Enter the new price: ";
                        cin >> newPrice;
                        men.updateItemsInformation(id, newName, newPrice);
                        break;
                    }
                    case 5:
                        men.viewMenu();
                        break;

                    case 6:
                        sales.displayTotalCost();
                        break;

                    case 7:
                        int id;
                        cout << "Enter the id of the order to update the status " << endl;
                        cin >> id;
                        cust.updateStatus(&pendingOrders, id, sales);
                        break;

                    case 0:
                        cout << "Logged out !" << endl;
                        break;
                    default:
                        cout << "Please select the correct choice " << endl;
                    }

                } while (select != 0);
            }
            break;
        }
        case 2:
        {
            string customerName;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, customerName);
            cust = customer(customerName);
            cust.checkMenuANDPlaceOrder(men);
            break;
        }
        }

    } while (choice != 0);
}