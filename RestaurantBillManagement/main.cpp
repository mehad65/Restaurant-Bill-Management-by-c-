#include <iostream>
#include <string>
#include <Windows.h>
#include <list>
#include <iomanip>

using namespace std;

class Restaurant
{
public:
    int food_item_codes[12];
    string food_item_names[12];
    int food_item_prices[12];
private:
    int total_tax;
public: void set_Total_Tax(string secretkey,int tax_amount) {
    if(secretkey=="123")
      total_tax = tax_amount;
}
public: int get_Total_Tax()
{
    return total_tax;
}
public:
    Restaurant(int* codes, string* names, int* prices) {
        for (int i = 0;i < 12;i++) {
            this->food_item_codes[i] = codes[i];
            this->food_item_names[i] = names[i];
            this->food_item_prices[i] = prices[i];
        }
    }
};

Restaurant* update_Restaurant_items()
{
    cout << "Input Restaurant:" << endl;
    int food_item_codes[12];
    string food_item_names[12];
    int food_item_prices[12];
    int item_number;
    cin >> item_number;
    for (int i = 0;i < item_number;i++) {
        int code, price;
        string foodName;
        cin >> code;
        getline(cin>>ws, foodName);
        cin >> price;
        food_item_codes[i] = code;
        food_item_names[i] = foodName;
        food_item_prices[i] = price;
    }
    Restaurant* restaurant = new Restaurant(food_item_codes, food_item_names, food_item_prices);
    return restaurant;
}
void gotoxy(short x, short y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
struct Item
{
    int code;
    int quantity;
};
int getindex(Restaurant* res,int num) {
    for (int i = 0;i < 12;i++) {
        if (num == res->food_item_codes[i]) {
            return i;
        }
    }
    return -1;
}
bool isExist(Restaurant* res, int code) {
    for (int i = 0;i < 12;i++) {
        if (code == res->food_item_codes[i]) {
            return true;
        }
    }
    return false;
}
int main()
{
    Restaurant* restaurant=update_Restaurant_items();
    gotoxy(30, 40);
    cout << "MAKE BILL";
    gotoxy(25, 41);
    cout << "-------------------";
    gotoxy(1, 42);
    cout << "Item Code";
    gotoxy(25, 42);
    cout << "Item name";
    gotoxy(60, 42);
    cout << "Item price";
    for(int i=0;i<12;i++){
        gotoxy(1, i + 43);
        cout << restaurant->food_item_codes[i];
        gotoxy(25, i + 43);
        cout << restaurant->food_item_names[i];
        gotoxy(60, i + 43);
        cout << restaurant->food_item_prices[i];
    }
    int tableno;
    int number_of_items;
    list<Item> mixedlist;
    Item item;
    cout << endl << endl;
    cout << "Enter table no: ";
    cin >> tableno;
    cout <<"Enter number of items: ";
    cin >> number_of_items;
    for (int i = 0;i < number_of_items;i++) {
        Flag:
        cout << "Enter item "<<i+1<<" code : ";
        cin >> item.code;
        if (isExist(restaurant, item.code)) {
            cout << "Enter item " << i+1 << " quantity: ";
            cin >> item.quantity;
        }
        else {
            cout << "Invalid item code" << endl;
            goto Flag;
        }
        
        mixedlist.push_back(item);
    }
    list<Item>:: iterator it;
    int totalcal=0;
    cout <<endl<< endl;
    cout << setw(40) << "BILL SUMMARY" << endl;
    cout << setw(45) << right<<"........................." << endl;
    cout << "Table no:" << 45 << endl;
    cout <<setw(12)<<left<< "Item code"<<setw(25) << "Item name" <<setw(12)<< "Item price" << setw(16) << "Item quantity" << setw(12) << "Total price" << endl;
    for (it = mixedlist.begin();it!= mixedlist.end();it++)
    {
        int index=getindex(restaurant, it->code);
        int itemprice = restaurant->food_item_prices[index];
        string itemname = restaurant->food_item_names[index];
        int itemtotal = itemprice * it->quantity;
        int itemcode = it->code;
        int itemquantity = it->quantity;
        totalcal += itemtotal;
        cout <<setw(12)<<left<<itemcode<<setw(25) << itemname <<setw(12)<<itemprice << setw(16) << itemquantity << setw(12) << itemtotal << endl;
    }
    double taxcal = totalcal * 0.05;
    double netTotal = totalcal + taxcal;
    cout <<"Tax"<< setw(65) << right << taxcal << endl;
    cout << "....................................................................................." << endl;
    cout <<"Net Total"<< setw(60) << right << netTotal <<" Taka"<< endl;

    //set total tax to the restaurant class
    restaurant->set_Total_Tax("123",taxcal); 
    return 0;
}
