#include <iomanip>
#include <iostream>
#include <string>
#include<stdio.h>
#include<conio.h>// for _getch()(press enter to continue)
#include<Windows.h>// for sleep() command (Login animation)
#include <algorithm>
using namespace std;

// Item Linked List
struct Item {
    string id;
    string name;
    int price;
    // Queue
    int front = -1;
    int rear = -1;
    bool isAvailableQueue[5] = {false,false, false, false, false};
    Item* next;
};
// Array of Categories
struct Category {
    string name;
    Item* top;
    Category* next;
};
// Cart Stack
struct Cart {
    string name;
    int price;
    double quantity;
};
Cart cartStack[5];
int topCartStack= -1;
int quantity_max_size = 5;
Category categories[5];
void returnToMenuAnimation(){
    cout << "RETURNING TO MAIN MENU";
        for (int a = 1; a < 8; a++)
        {
            Sleep(500);
            cout << "...";
        }
        system("CLS");
}
bool pushToCart(Item* item,int quantity) {
    if(topCartStack == quantity_max_size - 1){
        cout << "Cart is full" << endl;
        return false;
    }
    else{
        Cart* cartItem = new Cart;
        cartItem->name = item->name;
        cartItem->price = item->price;
        cartItem->quantity = quantity;
        topCartStack++;
        cartStack[topCartStack] = *cartItem;
        cout<<"Item Added to Cart"<<endl;
         returnToMenuAnimation();
        return true;
    }
}
Cart popFromCart() {
    Cart temp;
    if(topCartStack == -1){
        cout << "Cart is empty" << endl;
        return temp;
    }
    else{
        temp = cartStack[topCartStack];
        topCartStack--;
        return temp;
    }
}
void enQueueItem(Category category,string itemName) {
    Item* item = category.top;
    while (item != NULL) {
        if (item->name == itemName) {
            break;
        }
        item = item->next;
    }
    if (item == NULL) {
        cout << "Wrong Product Name" << endl;
    }
    else {
        if(item->rear = quantity_max_size - 1 ){
            cout << "The item inventory is at maximum capacity. No further restocking is possible at this time." << endl;
             returnToMenuAnimation();
        }
        else{
            cout << "Enter Quantity: ";
            int quantity;
            cin >> quantity;
            if (quantity > quantity_max_size - item->rear - 1) {
    cout << "Inventory capacity constraint: Only " << quantity_max_size - item->rear << " units of " << item->name << " can be added at this time." << endl;
     returnToMenuAnimation();
}
            else {
                for (int i = 0; i < quantity; i++) {
                    item->rear++;
                    item->isAvailableQueue[item->rear] = true;
                }
                cout << "Item Restocked successfully" << endl;
            }
        
        }
    }
}
void deQueueItem(Category category, string itemID) {
    Item* item = category.top;

    while (item != NULL) {
        if (item->id == itemID) {
            break;
        }
        item = item->next;
    }
    if (item == NULL) {
        cout << "Invalid Product ID" << endl;
    }
    else {
        if(item->rear == -1 && item->front == -1){
            cout << "Item is out of stock" << endl;
            cout << "Press Enter To Continue" << endl;
            (void)_getch();
             returnToMenuAnimation();
        }
        else {
            cout << "Enter Quantity: ";
            int quantity;
            cin >> quantity;
            if (quantity > item->rear + 1) {
                cout << "Inventory capacity constraint: Only " << item->rear + 1 << " units of " << item->name << " are Availble ." << endl;
                returnToMenuAnimation();
            }
            else {
                if(item->rear == 0 && quantity == 1 && item->front == 0){
                    item->front = -1;
                    item->rear = -1;
                } else {
                    for (int i = 0; i < quantity; i++) {
                        // cout << "unit testing line #137 " << endl;
                        // cout << "Product " << item->name<<endl;
                        // cout << "front " << item->front << endl;
                        // cout << "rear " << item->rear << endl;
                        // system("pause");
                        item->isAvailableQueue[item->front] = false;
                        item->front++;
                        
                        
                    }
                    if (item->front > item->rear) {
                        item->front = -1;
                        item->rear = -1;
                    }
                    pushToCart(item, quantity);
                    cout << "Item Added to Cart" << endl;
                }
            }
        }
    }
}
//Depreciateed Function
// void deQueueItem(Category category,string itemID){
//     Item* item = category.top;
//     while (item != NULL) {
//         if (itemID._Equal(item->id)){
//             break;
//         }
//         item = item->next;
//     }
//     if (item == NULL) {
//         cout << "Wrong Product ID" << endl;
//     }
//     else {
//         if(item->rear == -1 && item->front -1){
//             cout << "Item is out of stock" << endl;
//          cout<< "Press Enter To Continue"<<endl;
//          (void)_getch();
//          system("CLS");
//         }
//         else{
//             cout << "Enter Quantity: ";
//             int quantity;
//             cin >> quantity;
//             if (quantity > item->rear + 1) {
//     cout << "Inventory capacity constraint: Only " << item->rear + 1 << " units of " << item->name << " can be removed at this time." << endl;
// }
//             else if(item->rear == 0 && quantity == 1 && item->front == 0){
//                 item->rear--;
//                 }else {
//                 for (int i = 0; i < quantity; i++) {
//                     item->rear--;
//                     item->isAvailableQueue[item->rear] = NULL;
//                 }
//                 pushToCart(item,quantity);
//                 cout << "Item Added to Cart" << endl;

//             }
        
//         }
//     }
// }
void purchase() {
   cout << "| Enter the code of the item you want to purchase: ";
   string code;
   cin >> code;
   if(cin.fail()){
    cin.clear();
    cin.ignore();
    cout<<"| Invalid Input "<<endl;
    cout <<  "| Press Enter to Continue" << endl;
    (void)_getch();
    system("CLS");
    return;
   }
   transform(code.begin(), code.end(), code.begin(), ::toupper); 
   char categoryCode = code[0];
   int categoryCodeInt;
   if (categoryCode == 'A') {
         categoryCodeInt = 0;
    }
   else if (categoryCode == 'B') {
         categoryCodeInt = 1;
    }
    else if(categoryCode == 'C') {
         categoryCodeInt = 2;
    }
    else if(categoryCode == 'D') {
         categoryCodeInt = 3;
    }
    else if(categoryCode == 'E'){
         categoryCodeInt = 4;
    }
    else{
         cout << "Wrong Product Code" << endl;
         return;
   } 
   Item* item = categories[categoryCodeInt].top;
   while (item != NULL) {
       if (item->id == code) {
           break;
       }
       item = item->next;
   }
   if (item == NULL) {
       cout << "| Item not found" << endl;
       return;
   }
   else {
     
             deQueueItem(categories[categoryCodeInt],code);
             return;
         }
     }
      
void cartMenu(){
    system("CLS");
    cout << "|============Cart=======|" << endl;
    for (int i = 0; i < topCartStack + 1; i++) {
        cout << "| " << setw(4) << left << cartStack[i].name << " \t";
    }
    cout << "|" << endl;
    for (int i = 0; i < topCartStack + 1; i++) {
        cout << "| Rs. " << setw(4) << left << cartStack[i].price << " \t";
    }
    cout << "|" << endl;
    for (int i = 0; i < topCartStack + 1; i++) {
        cout << "| " << setw(4) << left <<"Quantity: " <<cartStack[i].quantity << " \t";
    }
    cout << "|" << endl;
    cout << "|-----------------------|" << endl;
    cout << "| 1. Checkout           |"<< endl;
    cout << "| 2. Remove Item        |"<<endl;
    cout << "| 3. Return to Main Menu|"<<endl;
    cout << "|=======================|" << endl;
    cout<<"| INPUT: ";   
   int choice;
   cin>>choice;
    if(cin.fail()){
    cin.clear();
    cin.ignore();
    cout<<"| Invalid Input"<<endl;
    cout <<"| Press Enter to Continue" << endl;
    (void)_getch();
    system("CLS");
    cartMenu();
   }
   switch(choice){
       case 1:
           //checkout();
           break;
       case 2:
           //removeItem();
           break;
       case 3:
           system("CLS");
              break;
       case 4:
           exit(0);
           break;
       default:
           cout<<"Invalid Choice"<<endl;
           break;
}

}
void mainMenu() {
    cout << "|==================Vending Machine==============================|" << endl;
    for (int i = 0; i < 5; i++) {
        Category category = categories[i];
        Item* item = category.top;
        while (item != NULL) {
            int availableCount = 0;
            for (int j = 0; j < 5; j++) {
                if (item->isAvailableQueue[j] == true) {
                    availableCount++;
                }
                else {
                    break;
                }
            }
            cout << "| " << setw(4) << left  << item->name << "(" << availableCount << ") \t";
            item = item->next;
        }
        cout<< "|" << endl;
        item = category.top;
        while (item != NULL) {
            cout << "|" << setw(4) << left <<" Code: "<< item->id << "" << " \t";
            item = item->next;
        }
        cout << "|" << endl;
        item = category.top;
        while (item != NULL) {
            cout << "| Rs. " << setw(4) << left << item->price << " \t";
            item = item->next;
        }
        cout << "|" << endl;
        cout << "|---------------------------------------------------------------|" << endl;
    }
    cout << "| 1. Purchase   | 2. Restock    | 3. Cart       | 4. Exit       | " << endl;
    cout << "|===============================================================|" << endl;
    cout<<"| INPUT: ";   
   int choice;
   cin>>choice;
    if(cin.fail()){
    cin.clear();
    cin.ignore();
    cout<<"| Invalid Input"<<endl;
    cout <<"| Press Enter to Continue" << endl;
    (void)_getch();
    system("CLS");
    mainMenu();
   }
   switch(choice){
       case 1:
           purchase();
           break;
       case 2:
           //restockMenu();
           break;
       case 3:
              cartMenu();
              break;
       case 4:
           exit(0);
           break;
       default:
           cout<<"Invalid Choice"<<endl;
           break;
}
}

//ignore this function
void initializeData(){
    Item* pepsi = new Item;
    pepsi->id = "A1";
    pepsi->name = "Pepsi";
    pepsi->isAvailableQueue[0] = true;
    pepsi->isAvailableQueue[1] = true;
    pepsi->isAvailableQueue[2] = true;
    pepsi->isAvailableQueue[3] = true;
    pepsi->front=0;
    pepsi->rear=3;
    pepsi->price = 70;
    pepsi->next = NULL;
    Item* coke = new Item;
    coke->id = "A2";
    coke->name = "Coke";
    coke->isAvailableQueue[0] = true;
    coke->isAvailableQueue[1] = true;
    coke->front = 0;

    coke->rear = 1;
    coke->price = 60;
    coke->next = NULL;
    Item* sprite = new Item;
    sprite->id = "A3";
    sprite->name = "Sprite";
    sprite->isAvailableQueue[0] = true;
    sprite->isAvailableQueue[1] = true;
    sprite->isAvailableQueue[2] = true;
    sprite->front = 0;
    sprite->rear = 2;
    sprite->price = 50;
    sprite->next = NULL;
    Item* fanta = new Item;
    fanta->id = "A4";
    fanta->name = "Fanta";
    fanta->isAvailableQueue[0] = true;
    fanta->isAvailableQueue[1] = true;
    fanta->isAvailableQueue[2] = true;
    fanta->isAvailableQueue[3] = true;
    fanta->isAvailableQueue[4] = true;
    fanta->front = 0;
    fanta->rear = 4;
    fanta->price = 40;
    fanta->next = NULL;
    pepsi->next = coke;
    coke->next = sprite;
    sprite->next = fanta;
    Category* drinks = new Category;
    drinks->name = "Drinks";
    drinks->next = NULL;
    drinks->top = pepsi;
    categories[0] = *drinks;
    Item* lays = new Item;
    lays->id="B1";
    lays->name = "Lays";
    lays->isAvailableQueue[0] = true;
    lays->isAvailableQueue[1] = true;
    lays->isAvailableQueue[2] = true;
    lays->front = 0;
    lays->rear = 2;
    lays->price = 50;
    lays->next = NULL;
    Item* doritos = new Item;
    doritos->id="B2";
    doritos->name = "Doritos";

    doritos->isAvailableQueue[0] = true;
    doritos->isAvailableQueue[1] = true;
    doritos->isAvailableQueue[2] = true;
    doritos->isAvailableQueue[3] = true;
    doritos->front = 0;
    doritos->rear = 3;

    doritos->price = 120;
    doritos->next = NULL;
    Item* cheetos = new Item;
    cheetos->id="B3";
    cheetos->name = "Cheetos";
    cheetos->isAvailableQueue[0] = true;
    cheetos->isAvailableQueue[1] = true;
    cheetos->front = 0;
    cheetos->rear = 1;
    cheetos->price = 50;
    cheetos->next = NULL;
    Item* pringles = new Item;
    pringles->id="B4";
    pringles->name = "Pringles";
    pringles->isAvailableQueue[0] = true;
    pringles->isAvailableQueue[1] = true;
    pringles->isAvailableQueue[2] = true;
    pringles->isAvailableQueue[3] = true;
    pringles->front = 0;
    pringles->rear = 3;
    pringles->price = 40;
    pringles->next = NULL;
    lays->next = doritos;
    doritos->next = cheetos;
    cheetos->next = pringles;
    Category* chips = new Category;
    chips->name = "Chips";
    chips->next = NULL;
    chips->top = lays;
    categories[1] = *chips;
    Item* kitkat = new Item;
    kitkat->id="C1";
    kitkat->name = "KitKat";
    kitkat->isAvailableQueue[0] = true;
    kitkat->isAvailableQueue[1] = true;
    kitkat->front = 0;
    kitkat->rear = 1;
    kitkat->price = 50;
    kitkat->next = NULL;
    Item* mars = new Item;
    mars->id="C2";
    mars->name = "Mars";

    mars->isAvailableQueue[0] = true;
    mars->isAvailableQueue[1] = true;
    mars->isAvailableQueue[2] = true;
    mars->isAvailableQueue[3] = true;
    mars->front = 0;
    mars->rear = 3;
    mars->price = 120;
    mars->next = NULL;
    Item* snickers = new Item;
    snickers->id="C3";
    snickers->name = "Snickers";
    snickers->isAvailableQueue[0] = true;
    snickers->isAvailableQueue[1] = true;
    snickers->isAvailableQueue[2] = true;
    snickers->isAvailableQueue[3] = true;
    snickers->front = 0;
    snickers->rear = 3;
    snickers->price = 90;
    snickers->next = NULL;
    Item* bounty = new Item;
    bounty->id="C4";
    bounty->name = "Bounty";
    bounty->isAvailableQueue[0] = true;
    bounty->isAvailableQueue[1] = true;
    bounty->isAvailableQueue[2] = true;
    bounty->isAvailableQueue[3] = true;
    bounty->front = 0;
    bounty->rear = 3;
    bounty->price = 60;
    bounty->next = NULL;
    kitkat->next = mars;
    mars->next = snickers;
    snickers->next = bounty;
    Category* chocolates = new Category;
    chocolates->name = "Chocolates";
    chocolates->next = NULL;
    chocolates->top = kitkat;
    categories[2] = *chocolates;
    Item* skittles = new Item;
    skittles->id="D1";
    skittles->name = "Skittles";
    skittles->isAvailableQueue[0] = true;
    skittles->isAvailableQueue[1] = true;
    skittles->isAvailableQueue[2] = true;
    skittles->isAvailableQueue[3] = true;
    skittles->isAvailableQueue[4] = true;
    skittles->front = 0;
    skittles->rear = 4;
    skittles->price = 50;
    skittles->next = NULL;
    Item* starburst = new Item;
    starburst->id="D2";
    starburst->name = "Starburst";
    starburst->isAvailableQueue[0] = true;
    starburst->isAvailableQueue[1] = true;
    starburst->isAvailableQueue[2] = true;
    starburst->isAvailableQueue[3] = true;
    starburst->isAvailableQueue[4] = true;
    starburst->front = 0;
    starburst->rear = 4;
    starburst->price = 120;
    starburst->next = NULL;
    Item* mm = new Item;
    mm->id="D3";
    mm->name = "M&M";
    mm->isAvailableQueue[0] = true;
    mm->isAvailableQueue[1] = true;
    mm->isAvailableQueue[2] = true;
    mm->isAvailableQueue[3] = true;
    mm->isAvailableQueue[4] = true;
    mm->front = 0;
    mm->rear = 4;
    mm->price = 90;
    mm->next = NULL;
    Item* twix = new Item;
    twix->id="D4";
    twix->name = "Twix";
    twix->isAvailableQueue[0] = true;
    twix->isAvailableQueue[1] = true;
    twix->isAvailableQueue[2] = true;
    twix->isAvailableQueue[3] = true;
    twix->isAvailableQueue[4] = true;
    twix->front = 0;
    twix->rear = 4;
    twix->price = 60;
    twix->next = NULL;
    skittles->next = starburst;
    starburst->next = mm;
    mm->next = twix;
    Category* candies = new Category;
    candies->name = "Candies";
    candies->next = NULL;
    candies->top = skittles;
    categories[3] = *candies;
    Item* juicyfrut = new Item;
    juicyfrut->id="E1";
    juicyfrut->name = "JuicyFrut";
    juicyfrut->isAvailableQueue[0] = true;
    juicyfrut->isAvailableQueue[1] = true;
    juicyfrut->isAvailableQueue[2] = true;
    juicyfrut->front = 0;
    juicyfrut->rear = 2;
    juicyfrut->price = 50;
    juicyfrut->next = NULL;
    Item* trident = new Item;
    trident->id="E2";
    trident->name = "Trident";
    trident->isAvailableQueue[0] = true;
    trident->isAvailableQueue[1] = true;
    trident->isAvailableQueue[2] = true;
    trident->isAvailableQueue[3] = true;
    trident->front = 0;
    trident->rear = 3;
    trident->price = 120;
    trident->next = NULL;
    Item* orbit = new Item;
    orbit->id="E3";
    orbit->name = "Orbit";
    orbit->isAvailableQueue[0] = true;
    orbit->isAvailableQueue[1] = true;
    orbit->isAvailableQueue[2] = true;
    orbit->isAvailableQueue[3] = true;
    orbit->isAvailableQueue[4] = true;
    orbit->front = 0;
    orbit->rear = 4;    
    orbit->price = 90;
    orbit->next = NULL;
    Item* extra = new Item;
    extra->id="E4";
    extra->name = "Extra";
    extra->isAvailableQueue[0] = true;
    extra->isAvailableQueue[1] = true;
    extra->front = 0;
    extra->rear = 1;
    extra->price = 60;
    extra->next = NULL;
    juicyfrut->next = trident;
    trident->next = orbit;
    orbit->next = extra;
    Category* gums = new Category;
    gums->name = "Gums";
    gums->next = NULL;
    gums->top = juicyfrut;
    categories[4] = *gums;
    // topCategory = drinks;
    // bottom = gums;
}

int main(){
    initializeData();
    do{
    mainMenu();
    }while(true);
    return 0;
}
// #include<conio.h>// for _getch()(press enter to continue)
// void pause(int dur)//pause duration(status:ok/working)
// {
//     time_t temp = time(NULL) + dur;
//     while (temp > time(NULL));
// }
// 
//  cout << "\n\n\n" << centre_allign << "LOADING \n" << centre_allign;
//         for (int a = 1; a < 8; a++)
//         {
//             Sleep(500);
//             cout << "...";
//         }

// // Password ** code 
//  string pass = "";
//     char ch;
//     cout << centre_allign << "============================================" << endl;
//     cout << centre_allign << "              HR MANAGEMENT SYSTEM          " << endl;
//     cout << centre_allign << "============================================" << endl;
//     cout << "\n\n\n\n";
//     cout << centre_allign << "=>Enter Your Password :";
//     ch = _getch();
//     while (ch != 13) {//character 13 is enter
//         pass.push_back(ch);
//         cout << '*';
//         ch = _getch();
//     }
//     cout << endl;