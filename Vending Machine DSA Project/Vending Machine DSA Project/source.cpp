#include <iomanip>
#include <iostream>
#include <string>
#include<stdio.h>
#include<conio.h>// for _getch()(press enter to continue)
#include<Windows.h>// for sleep() command (Login animation)
#include <algorithm>

using namespace std;

// Coin Struct
struct Coin{
    int value;
    int quantity;
};
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
Coin denominations[5] = {{500,2},{100,10},{50,10},{20,5},{10,10}};
Category categories[5] ;
int yourBalance;
int totalAmount;
void changeHandling();
void calculateTotalAmount();
void addToDenomination(int value,int quantity);
void addBalance();
void returnToMenuAnimation();
bool pushToCart(Item* item,int quantity);
Cart popFromCart();
void enQueueItem(Category category,Item* item);
void deQueueItem(Category category, Item* item);
void purchase();
void removeItemFromCart();
void cartMenu();
void restockItem();
void restockMenu();
void adminLogin();
void mainMenu();
void initializeData();

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
    do
    {   
       mainMenu();
    }while(true);
    return 0;
}
void changeHandling(){
    int change = yourBalance - totalAmount;
    int tempChange = change;
    int denominationCount = 0;
    for(int i = 0; i < 5; i++){
        denominationCount += denominations[i].quantity * denominations[i].value;
    }
    if(change > 0){
        if(change > denominationCount){
            cout << "| Sorry, we don't have enough change to return" << endl;
            cout << "| Press Enter to Continue" << endl;
            (void)_getch();
            system("CLS");
            return;
        }
        else{
            for(int i = 0; i < 5; i++){
                int count = 0;
                while(change >= denominations[i].value && denominations[i].quantity > 0){
                    change -= denominations[i].value;
                    denominations[i].quantity--;
                    count++;
                }
                if(count > 0){
                    cout << "| Rs. " << denominations[i].value << " x " << count << endl;
                }
            }
            cout << "| Change Returned" << endl;
            cout << "| Press Enter to Continue" << endl;
            (void)_getch();
            system("CLS");
            mainMenu();
            return;
        }
    }
    else{
        cout << "| No Change Returned" << endl;
        cout << "| Press Enter to Continue" << endl;
        (void)_getch();
        system("CLS");
       mainMenu();
    }
}
void calculateTotalAmount(){
    totalAmount = 0;
    for(int i = 0; i < topCartStack + 1; i++){
        totalAmount += cartStack[i].price * cartStack[i].quantity;
    }

}
void addToDenomination(int value,int quantity){
    for(int i = 0; i < 5; i++){
        if(denominations[i].value == value){
            denominations[i].quantity += quantity;
        }
    }
}
void addBalance(){
    Coin receivedCoins[5];
    Coin coin1 = {500,0};
    Coin coin2 = {100,0};
    Coin coin3 = {50,0};
    Coin coin4 = {20,0};
    Coin coin5 = {10,0};
    do
    {
    system("CLS");
    cout<<"|====================Add Balance====================|"<<endl;
    cout<<"| Your Balance: "<<yourBalance<<endl;
    cout<<"| Total Amount: "<<totalAmount<<endl;
    cout<<"|---------------------------------------------------|"<<endl;
    if(yourBalance < yourBalance + 100 )
    {
     cout << "| Enter the amount of money you want to insert: "<<endl;
     cout << "| 1) Rs. 500"<<endl;
     cout << "| 2) Rs. 100"<<endl;
     cout << "| 3) Rs. 50"<<endl;
     cout << "| 4) Rs. 20"<<endl;
     cout << "| 5) Rs. 10"<<endl;
     cout << "| 6) Proceed to Checkout"<<endl;
     cout << "| 7) Return to Main Menu"<<endl;
     int choice;
     cout<< "| INPUT: ";
     cin >> choice;
     if(cin.fail()){
     cin.clear();
     cin.ignore(10000,'\n');
     cout <<"| Invalid Input "<<endl;
     cout <<"| Press Enter to Continue " << endl;
     (void)_getch();
     system("CLS");
     addBalance();
    }
    switch(choice){
        case 1:
            yourBalance += 500;
            coin1.quantity++;
            break;
        case 2:
            yourBalance += 100;
            coin2.quantity++;
            break;
        case 3:
            yourBalance += 50;
            coin3.quantity++;
            break;
        case 4:
            yourBalance += 20;
            coin4.quantity++;
            break;
        case 5:
            yourBalance += 10;
            coin5.quantity++;
            break;
        case 6:
        addToDenomination(500,coin1.quantity);
        addToDenomination(100,coin2.quantity);
        addToDenomination(50,coin3.quantity);
        addToDenomination(20,coin4.quantity);
        addToDenomination(10,coin5.quantity);
        // //UNIT TESTING OF DENOMINATIONS ADDITION
        // for(int i = 0; i < 5; i++){
        //     cout << denominations[i].value << " " << denominations[i].quantity << endl;
        // }
            changeHandling();
            break;
        case 7:
            system("CLS");
            break;
        default:
            cout<<"| Invalid Choice"<<endl;
            break;
    }
    }
    else{
        cout << "| Balance Limit Reached " <<endl; 
        cout << "| 1) Proceed to Checkout"<<endl;
        cout << "| 2) Return to Main Menu"<<endl;
        int choice;
        cout<< "| INPUT:";
        cin >> choice;
        if(cin.fail()){
        cin.clear();
        cin.ignore(10000,'\n');
        cout<<"| Invalid Input"<<endl;
        cout <<"| Press Enter to Continue" << endl;
        (void)_getch();
        system("CLS");
        addBalance();
        }
        switch(choice){
            case 1:
                changeHandling();
                break;
            case 2:
                system("CLS");
                break;
            default:
                cout<<"| Invalid Choice"<<endl;
                break;
        }
    }
    
    }while(true);
    

}
void returnToMenuAnimation(){
    cout << "| RETURNING TO MAIN MENU";
        for (int a = 1; a < 6; a++)
        {
            Sleep(500);
            cout << "...";
        }
        system("CLS");
        mainMenu();
}
bool pushToCart(Item* item,int quantity) {
    if(topCartStack == quantity_max_size - 1){
        cout << "| Cart is full" << endl;
        return false;
    }
    else{
        Cart* cartItem = new Cart;
        cartItem->name = item->name;
        cartItem->price = item->price;
        cartItem->quantity = quantity;
        topCartStack++;
        cartStack[topCartStack] = *cartItem;
        cout<<"| Item Added to Cart"<<endl;
         returnToMenuAnimation();
        return true;
    }
}
Cart popFromCart() {
    Cart temp;
    if(topCartStack == -1){
        cout << "| Cart is empty" << endl;
        return temp;
    }
    else
    {
        temp = cartStack[topCartStack];
        topCartStack--;
        return temp;
    }
} 
void enQueueItem(Category category,Item* item) {
    cout << "| Enter Quantity: ";
    int quantity;
    cin >> quantity;
    cout<<"| Restocking Item";
    for (int a = 1; a < 4; a++)
        {
            Sleep(500);
            cout << "...";
        }
        cout<<endl;
    for (int i = 0; i < quantity; i++) {
        cout<< "| " << item->name << " Added to the inventory" << endl;
        if ((item->front == item->rear + 1) || ((item->front == 0) && (item->rear == quantity_max_size - 1))) {
            cout << "| The item inventory is at maximum capacity. No further restocking is possible at this time." << endl;
            break;
        }
        // else if(item->rear == quantity_max_size - 1 && item->front != 0){
        //     item->rear = 0;
        //     item->isAvailableQueue[item->rear] = true;
        // }
        else
        {
          item->rear = (item->rear + 1) % quantity_max_size;
          item->isAvailableQueue[item->rear] = true;
        }
    }
    cout << "| Item Restocking Completed" << endl;
    cout<<"| Press Enter to Continue"<<endl;
    (void)_getch();
    returnToMenuAnimation();
}
void deQueueItem(Category category, Item* item) {
    if(item->rear == -1 && item->front == -1){
        cout << "| Item is out of stock" << endl;
        cout << "| Press Enter To Continue" << endl;
        (void)_getch();
        returnToMenuAnimation();
    }
    else {
        cout << "| Enter Quantity: ";
        int quantity;
        cin >> quantity;
        if (quantity > (item->rear + quantity_max_size - item->front) % quantity_max_size + 1) {
            cout << "| Inventory capacity constraint: Only " << (item->rear + quantity_max_size - item->front) % quantity_max_size + 1 << " units of " << item->name << " are Availble ." << endl;
            returnToMenuAnimation();
        }
        else {
            for (int i = 0; i < quantity; i++) {
                item->isAvailableQueue[item->front] = false;
                item->front = (item->front + 1) % quantity_max_size;
            }
            if (item->front == (item->rear + 1) % quantity_max_size) {
                item->front = -1;
                item->rear = -1;
            }
            pushToCart(item, quantity);
        }
    }
}
void purchase() 
{
   cout << "| Enter the code of the item you want to purchase: ";
   string code;
   cin >> code;
   if(cin.fail())
   {
    cin.clear();
    cin.ignore(10000,'\n');
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
    else
    {
         cout << "| Wrong Product Code" << endl;
         return;
    } 
   Item* item = categories[categoryCodeInt].top;
   while (item != NULL) {
       if (item->id == code) {
           break;
       }
       item = item->next;
   }
   if (item == NULL) 
   {
       cout << "| Wrong Product Code" << endl;
       return;
   }
   else 
   {
     
             deQueueItem(categories[categoryCodeInt],item);
             return;
   }
}    
void removeItemFromCart() 
{
    cout<< "| Enter the item no you want to remove: ";
    int itemNo;
    cin >> itemNo;
    if(cin.fail())
    {
    cin.clear();
    cin.ignore(10000,'\n');
    cout<<"| Invalid Input "<<endl;
    cout <<  "| Press Enter to Continue" << endl;
    (void)_getch();
    system("CLS");
    return;
    }
    if(itemNo > topCartStack + 1)
    {
        cout << "| Invalid Item No" << endl;
        cout << "| Press Enter to Continue" << endl;
        (void)_getch();
        system("CLS");
        return;
    }
    else
    {
       //Create a temp stack pop and save it till the given index and pop the given index and push the temp stack back to the cart stack
         Cart tempStack[5];
            int topTempStack = -1;
            for (int i = 0; i < itemNo - 1; i++) {
                Cart temp = popFromCart();
                topTempStack++;
                tempStack[topTempStack] = temp;
            }
            Cart temp = popFromCart();
            for (int i = 0; i < topTempStack + 1; i++) {
                topCartStack++;
                cartStack[topCartStack] = tempStack[i];
            }
            cout << "| Item Removed" << endl;
            cout << "| Press Enter to Continue" << endl;
            (void)_getch();
            system("CLS");
            return;
    }                           
}
void cartMenu(){
    system("CLS");
        cout << "|------Your Cart--------|" << endl;
        if(topCartStack == -1){
            cout << "| Cart is empty" << endl;
            cout << "| Press Enter to Continue" << endl;
            (void)_getch();
            system("CLS");
            return;
        }
        else{
    for (int i = 0; i < topCartStack + 1; i++) {
        cout << "|-----------"<<i+1<<"-----------|" << endl;
        cout << "| " << setw(4) << left << cartStack[i].name << " \t\t"<< "|" << endl;
         cout << "| " << setw(4) << left <<"Quantity: " <<cartStack[i].quantity << " \t\t" << "|" << endl;
        cout << "| Rs. " << setw(4) << left << cartStack[i].price << " \t\t" << "|" << endl;
        cout << "|-----------------------|" << endl;
    }
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
    cin.ignore(10000,'\n');
    cout<<"| Invalid Input"<<endl;
    cout<<"| Press Enter to Continue" << endl;
    (void)_getch();
    system("CLS");
    cartMenu();
   }

   switch(choice){
       case 1:
           calculateTotalAmount();
           addBalance();
           break;
       case 2:
           removeItemFromCart();
           break;
       case 3:
           system("CLS");
              break;
       case 4:
           exit(0);
           break;
       default:
           cout<<"| Invalid Choice"<<endl;
           break;
}
        }
}
void restockItem(){
    cout << "| Enter the code of the item you want to restock: ";
   string code;
   cin >> code;
   if(cin.fail()){
    cin.clear();
    cin.ignore(10000,'\n');
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
         cout << "| Wrong Product Code" << endl;
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
       enQueueItem(categories[categoryCodeInt],item);
       return;
   }

}
void restockMenu(){
    system("CLS");
    cout << "|========================Restock Menu===========================|" << endl;
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
        cout << "|---------------------------------------------------------------|" << endl;
    }
    cout << "| 1. Restock    | 2. Return to Main Menu        | 3. Exit       | " << endl;
    cout << "|===============================================================|" << endl;
    cout<<"| INPUT: ";   
   int choice;
   cin>>choice;
    if(cin.fail()){
    cin.clear();
    cin.ignore(10000,'\n');
    cout<<"| Invalid Input"<<endl;
    cout <<"| Press Enter to Continue" << endl;
    (void)_getch();
    system("CLS");
    restockMenu();
   }
   switch(choice){
       case 1:
           restockItem();
           break;
       case 2:
           system("CLS");
           break;
       case 3:
           exit(0);
           break;
       default:
           cout<<"| Invalid Choice"<<endl;
           break;
}

}
void adminLogin(){
    system("CLS");
    string pass = "";
    char ch;
    cout << "|==================Admin Login==============================|" << endl;
    cout << "| Enter Password: ";
    ch = _getch();
    while (ch != 13) {
        //character 13 is enter
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    cout << endl;
    if(pass == "admin"){
        cout << "| Login Successful" << endl;
        cout << "| Loading...";
        for (int a = 1; a < 4; a++)
        {
            Sleep(500);
            cout << "...";
        }
        system("CLS");
        restockMenu();
    }
    else{
        cout << "| Wrong Password" << endl;
        cout << "| Press Enter to Continue" << endl;
        (void)_getch();
        system("CLS");
        adminLogin();
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
                ////UNIT TESTING OF QUEUE AVAIBILITY
                // cout<< "| "<<item->name << " ";
                //  cout << item->isAvailableQueue[j] << ",";
                if (item->isAvailableQueue[j] == true) {
                    availableCount++;
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
    cin.ignore(10000,'\n');
    cout<<"| Invalid Input"<<endl;
    cout <<"| Press Enter to Continue" << endl;
    (void)_getch();
    system("CLS");
    mainMenu();
   }else{
   switch(choice){
       case 1:
           purchase();
           break;
       case 2:
           adminLogin();
           break;
       case 3:
              cartMenu();
              break;
       case 4:
           exit(0);
           break;
       default:
           cout<<"| Invalid Choice"<<endl;
           break;
}
}
}