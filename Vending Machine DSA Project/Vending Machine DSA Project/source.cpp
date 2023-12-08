#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
//Item Linked List
 struct Item{
    string name;
    int price;
    //Queue
    bool isAvailable[5]={true,true,true,true,true};
    Item* next;
 };
 //Category Stack
struct Category
{
    string name;
    Item* top;
    Category* next;
};
 //Cart Queue 
    struct Cart{
        string name;
        int price;
        Cart* next;
    };

 Cart queue[5];
 Category categoryStack[5];
 Category* topCategory = NULL;
 Category* bottom = NULL;


                                        
// void displayMenu() {
//     cout << "|==================Vending Machine=======================|" << endl;
//     cout << "| Pepsi(5)    | Coke(4)     | Sprite(5)   | Fanta(1)     |" << endl;
//     cout << "| Rs. 70      | Rs. 60      | Rs. 50      | Rs. 40       |" << endl;
//     cout << "|--------------------------------------------------------|" << endl;
//     cout << "| Lays(5)     | Doritos(4)  | Cheetos(5)  | Pringles(1)  |" << endl;
//     cout << "| Rs. 50      | Rs. 120     | Rs. 50      | Rs. 40       |" << endl;
//     cout << "|--------------------------------------------------------|" << endl;
//     cout << "| KitKat(5)   | Mars(2)     | Snickers(1) | Bounty(4)    |" << endl;
//     cout << "| Rs. 50      | Rs. 120     | Rs. 90      | Rs. 60       |" << endl;
//     cout << "|--------------------------------------------------------|" << endl;
//     cout << "| Skittles(3) | Starburst(4)| M&M(5)      | Twix(1)      |" << endl;
//     cout << "| Rs. 50      | Rs. 120     | Rs. 90      | Rs. 60       |" << endl;
//     cout << "|--------------------------------------------------------|" << endl;
//     cout << "| JuicyFrut(4)| Trident(4)  | Orbit(4)    | Extra(5)     |" << endl;
//     cout << "| Rs. 50      | Rs. 120     | Rs. 90      | Rs. 60       |" << endl;
//     cout << "|========================================================|" << endl;
//     cout << "| 1. Purchase | 2. Restock  | 3. Exit                    | " << endl;
//     cout << "|========================================================|" << endl;
// }
// void displayMenu() {
//     cout << "|==================Vending Machine=======================|" << endl;
//     for (int i = 0; i < 5; i++) {
//         Category category = categoryStack[i];
//         Item* item = category.top;
//         while (item != NULL) {
//             int availableCount = 0;
//             for (int j = 0; j < 5; j++) {
//                 if (item->isAvailable[j]) {
//                     availableCount++;
//                 }
//             }
//             cout << "| " << item->name << "(" << availableCount << ") ";
//             item = item->next;
//         }
//         cout << "|" << endl;
//         item = category.top;
//         while (item != NULL) {
//             cout << "| Rs. " << item->price << " ";
//             item = item->next;
//         }
//         cout << "|" << endl;
//         cout << "|--------------------------------------------------------|" << endl;
//     }
//     cout << "| 1. Purchase | 2. Restock  | 3. Exit                    | " << endl;
//     cout << "|========================================================|" << endl;
// }
void displayMenu() {
    cout << "|==================Vending Machine==============================|" << endl;
    for (int i = 0; i < 5; i++) {
        Category category = categoryStack[i];
        Item* item = category.top;
        while (item != NULL) {
            int availableCount = 0;
            for (int j = 0; j < 5; j++) {
                if (item->isAvailable[j]) {
                    availableCount++;
                }
            }
            cout << "| " << setw(4) << left << item->name << "(" << availableCount << ") \t";
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
    cout << "| 1. Purchase    | 2. Restock  | 3. Exit                        | " << endl;
    cout << "|===============================================================|" << endl;
}


void mainMenu(){
    displayMenu();
    int choice;
    cout<<"Enter your choice: ";
    cin>>choice;
    switch(choice){
        case 1:
            //purchaseMenu();
            break;
        case 2:
            //restockMenu();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout<<"Invalid Choice"<<endl;
            mainMenu();
    }
}
void initializeData(){
    Item* pepsi = new Item;
    pepsi->name = "Pepsi";
    pepsi->price = 70;
    pepsi->next = NULL;
    Item* coke = new Item;
    coke->name = "Coke";
    coke->price = 60;
    coke->next = NULL;
    Item* sprite = new Item;
    sprite->name = "Sprite";
    sprite->price = 50;
    sprite->next = NULL;
    Item* fanta = new Item;
    fanta->name = "Fanta";
    fanta->price = 40;
    fanta->next = NULL;
    pepsi->next = coke;
    coke->next = sprite;
    sprite->next = fanta;
    Category* drinks = new Category;
    drinks->name = "Drinks";
    drinks->next = NULL;
    drinks->top = pepsi;
    categoryStack[0] = *drinks;
    Item* lays = new Item;
    lays->name = "Lays";
    lays->price = 50;
    lays->next = NULL;
    Item* doritos = new Item;
    doritos->name = "Doritos";
    doritos->price = 120;
    doritos->next = NULL;
    Item* cheetos = new Item;
    cheetos->name = "Cheetos";
    cheetos->price = 50;
    cheetos->next = NULL;
    Item* pringles = new Item;
    pringles->name = "Pringles";
    pringles->price = 40;
    pringles->next = NULL;
    lays->next = doritos;
    doritos->next = cheetos;
    cheetos->next = pringles;
    Category* chips = new Category;
    chips->name = "Chips";
    chips->next = NULL;
    chips->top = lays;
    categoryStack[1] = *chips;
    Item* kitkat = new Item;
    kitkat->name = "KitKat";
    kitkat->price = 50;
    kitkat->next = NULL;
    Item* mars = new Item;
    mars->name = "Mars";
    mars->price = 120;
    mars->next = NULL;
    Item* snickers = new Item;
    snickers->name = "Snickers";
    snickers->price = 90;
    snickers->next = NULL;
    Item* bounty = new Item;
    bounty->name = "Bounty";
    bounty->price = 60;
    bounty->next = NULL;
    kitkat->next = mars;
    mars->next = snickers;
    snickers->next = bounty;
    Category* chocolates = new Category;
    chocolates->name = "Chocolates";
    chocolates->next = NULL;
    chocolates->top = kitkat;
    categoryStack[2] = *chocolates;
    Item* skittles = new Item;
    skittles->name = "Skittles";
    skittles->price = 50;
    skittles->next = NULL;
    Item* starburst = new Item;
    starburst->name = "Starburst";
    starburst->price = 120;
    starburst->next = NULL;
    Item* mm = new Item;
    mm->name = "M&M";
    mm->price = 90;
    mm->next = NULL;
    Item* twix = new Item;
    twix->name = "Twix";
    twix->price = 60;
    twix->next = NULL;
    skittles->next = starburst;
    starburst->next = mm;
    mm->next = twix;
    Category* candies = new Category;
    candies->name = "Candies";
    candies->next = NULL;
    candies->top = skittles;
    categoryStack[3] = *candies;
    Item* juicyfrut = new Item;
    juicyfrut->name = "JuicyFrut";
    juicyfrut->price = 50;
    juicyfrut->next = NULL;
    Item* trident = new Item;
    trident->name = "Trident";
    trident->price = 120;
    trident->next = NULL;
    Item* orbit = new Item;
    orbit->name = "Orbit";
    orbit->price = 90;
    orbit->next = NULL;
    Item* extra = new Item;
    extra->name = "Extra";
    extra->price = 60;
    extra->next = NULL;
    juicyfrut->next = trident;
    trident->next = orbit;
    orbit->next = extra;
    Category* gums = new Category;
    gums->name = "Gums";
    gums->next = NULL;
    gums->top = juicyfrut;
    categoryStack[4] = *gums;
    topCategory = drinks;
    bottom = gums;

}
void main() {
    initializeData();
    mainMenu();
}