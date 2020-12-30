#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;


// When a costorm to buy a car, they want to get the follow informatons,
// so I set the six attributions
struct car{
      string model;
      string make;
      int year;
      int price;
      string color;
      int mileage;
};


// Get a random nunmber, model and make are together
int get_random_14(){
      int ran_Num = rand() % 14;

      return ran_Num;
}

// Get the attributions about a car
string car_model(int a){
      string car_model [14] = {"Audi", "Tesla", "Toyota", "Porsche", "Chevrolet", "Acura",
      "Ford", "BWM", "Ferrari", "Honda", "Jeep", "Kia", "Nissan", "Mazda"};

      return car_model[a];
}

string car_make(int a){
      string car_make [14] = {"A4", "Model S", "Camry", "911", "Malibu", "TLX", "Fusion", "X5",
      "488", "Accord", "Latitude", "Optima", "Maxima", "Mazda 6"};

      return car_make[a];
}

int car_year(int a){
      int car_year [14] = {2020, 2019, 2018, 2017 ,2016, 2015, 2014, 2013, 2012, 2011, 2010, 2009, 2008, 2007};

      return car_year[a];
}

string car_color(int a){
      string car_color [14] = {"Beige", "Black", "Blue", "Brown", "Gold", "Gray", "Green", "Orange",
      "Pink", "Purple", "Red", "Silver", "White", "Yellow"};

      return car_color[a];
}

int get_price(){
      int ran_price = rand() % 100 + 10;

      return ran_price * 1000;
}

int get_mileage(){
      int ran_Mileage = rand() % 120000;

      return ran_Mileage;
}


// Create a struct 1-D array and set the informatons of a car
// Random get informatons
struct car* create_car_array(){
      struct car* car_array = new struct car [14];

      // Make initial settings for each room
      for(int i = 0; i < 14; i++){
            int num = get_random_14();

            car_array[i].model = car_model(num);
            car_array[i].make = car_make(num);
            car_array[i].year = car_year(get_random_14());
            car_array[i].price = get_price();
            car_array[i].color = car_color(get_random_14());
            car_array[i].mileage = get_mileage();
      }

      return car_array;
}


// Create a 2D array to store cars
struct car** func(int rows, int columns){
      // Create 2-D dynamc array
      struct car** two_array = new struct car* [rows];

      for(int i = 0; i < rows; i++){
            two_array[i] = new struct car[columns];
      }

      return two_array;
}


// Set some cars informatons to 2D array
void set_car_info(struct car* car_array, struct car** two_array, int rows, int columns){
      for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                  two_array[i][j] = car_array[get_random_14()];
            }
      }
      return;
}


// get the all values of cars, in order to display the user's value
int get_value(struct car** two_array, int rows, int columns){
      int value = 0;

      for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                  value += two_array[i][j].price;
            }
      }

      return value;
}


// get the cars number, in order to display
int get_Carnum(struct car** two_array, int rows, int columns){
      int num = 0;
      for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                  if(two_array[i][j].model != "-----"){
                        num += 1;
                  }
            }
      }
      return num;
}


// after every step, will display all informatons
void disply_case(struct car** two_array, int rows, int columns, int value, int bank, int num){
      for(int i = 0; i < rows; i++){
            cout << "| " ;
            for(int j = 0; j < columns; j++){
                  cout << setw(9) << two_array[i][j].model << " | ";
            }
            cout << endl;
      }

      value = get_value(two_array, rows, columns);
      cout << "Total value of " << num << " items: $" << value << ". Your bank account :$" << bank << "." << endl;

      return;
}


// show a cars all informatons
void show(struct car** two_array, int rows, int columns, int value, int bank){
      int rows_1, columns_1;

      cout << "Enter number of rows: ";
      cin >> rows_1;
      cout << "Enter number of columns: ";
      cin >> columns_1;

      cout << "Car: " << endl;
      cout << "Model: " << two_array[rows_1][columns_1].model << ", Make: " << two_array[rows_1][columns_1].make;
      cout << ", Year: " << two_array[rows_1][columns_1].year << ", Price: " << two_array[rows_1][columns_1].price;
      cout << ", Color: " << two_array[rows_1][columns_1].color << ", Mileage: " << two_array[rows_1][columns_1].mileage << endl;

      int num = get_Carnum(two_array, rows, columns);
      disply_case(two_array, rows, columns, value, bank, num);
}


// if sell a car, the informatons will clear
void set_zero(struct car** two_array, int rows, int columns){
      two_array[rows][columns].model = "-----";
      two_array[rows][columns].make = "-----";
      two_array[rows][columns].year = 0;
      two_array[rows][columns].price = 0;
      two_array[rows][columns].color = "-----";
      two_array[rows][columns].mileage = 0;
}


// sell a car
void sell(struct car** two_array, int rows, int columns, int value, int bank){
      int rows_1, columns_1;

      cout << "Enter number of rows: ";
      cin >> rows_1;
      cout << "Enter number of columns: ";
      cin >> columns_1;

      value = value - two_array[rows_1][columns_1].price;
      bank = bank + two_array[rows_1][columns_1].price;
      set_zero(two_array, rows_1, columns_1);

      int num = get_Carnum(two_array, rows, columns);
      disply_case(two_array, rows, columns, value, bank, num);
}


// get the min value of all car
int get_min_price(struct car** two_array, int rows, int columns){
      int temp = two_array[0][0].price;

      for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                  if(temp > two_array[i][j].price){
                        temp = two_array[i][j].price;
                  }
            }
      }

      return temp;
}


// check the bank, and buy a car
void Proceed_buy(struct car** two_array, int rows, int columns, int value, int bank, struct car* car_array){
      int rows_1, columns_1;

      cout << "Enter number of rows: ";
      cin >> rows_1;
      cout << "Enter number of columns: ";
      cin >> columns_1;

      while(two_array[rows_1][columns_1].model != "-----"){
            cout << "That location is taken. Please try again." << endl;
            cout << "Enter number of rows: ";
            cin >> rows_1;
            cout << "Enter number of columns: ";
            cin >> columns_1;
      }

      if(two_array[rows_1][columns_1].price > bank){
            cout << "You don't have enough money." << endl;
      }
      else{
            two_array[rows_1][columns_1] = car_array[get_random_14()];

            cout << "New Car:" << endl;
            cout << "Model: " << two_array[rows_1][columns_1].model << ", Make: " << two_array[rows_1][columns_1].make;
            cout << ", Year: " << two_array[rows_1][columns_1].year << ", Price: " << two_array[rows_1][columns_1].price;
            cout << ", Color: " << two_array[rows_1][columns_1].color << ", Mileage: " << two_array[rows_1][columns_1].mileage << endl;
      }

      return;
}


// buy a car, if don't have enough money, will try again.
void buy(struct car** two_array, int rows, int columns, int value, int bank, struct car* car_array){
      char y;
      int min = get_min_price(two_array, rows, columns);

      if(bank < min){
            cout << "You need $" << min << " to buy a car. Please try again." << endl;
      }
      else{
            cout << "You will be charged $ to buy a car. Proceed(y/n)? ";
            cin >> y;

            if(y == 'y'){
                  Proceed_buy(two_array, rows, columns, value, bank, car_array);
                  int num = get_Carnum(two_array, rows, columns);
                  disply_case(two_array, rows, columns, value, bank, num);
            }
      }
      return;
}


// first car will become more value
void luck(struct car** two_array, int rows, int columns, int value, int bank){
      if(two_array[0][0].model == "-----"){
            cout << "unfortunatly, you don't have first car.\nSo, you will get anything." << endl;
      }
      else{
            cout << "You first car will become more value!" << endl;
            two_array[0][0].price += 1000;
            int num = get_Carnum(two_array, rows, columns);
            disply_case(two_array, rows, columns, value, bank, num);
      }

      return;
}


// The last option
// get a lottery ticket worth $10,000 and it will be deposited in your bank
void secret(struct car** two_array, int rows, int columns, int value, int bank){
      cout << "Now, I will tell you the secret!" << endl;
      cout << "You get a lottery ticket worth $10,000 and it will be deposited in your bank." << endl;
      bank += 10000;

      int num = get_Carnum(two_array, rows, columns);
      disply_case(two_array, rows, columns, value, bank, num);
      return;
}


// While loop to display every step
void showcase(struct car** two_array, int rows, int columns, int value, int bank, struct car* car_array){
      int choose = 0;

      while(choose != 6){
            cout<< "Choose:\n1) Show, 2)Sell, 3)Buy, 4)Luck, 5)Secret 6)Quit: ";
            cin >> choose;

            if(choose == 1){
                  show(two_array, rows, columns, value, bank);
            }
            else if(choose == 2){
                  sell(two_array, rows, columns, value, bank);
            }
            else if(choose == 3){
                  buy(two_array, rows, columns, value, bank, car_array);
            }
            else if(choose == 4){
                  luck(two_array, rows, columns, value, bank);
            }
            else if(choose == 5){
                  secret(two_array, rows, columns, value, bank);
            }
      }

}


/*
Free memory
*/
void free_strcut(struct car* car_array){
      delete [] car_array;
      return;
}


void free_dyarray(struct car** two_array, int rows, int columns){
      for(int i = 0;  i < rows; i++){
            delete[] two_array[i];
      }
      delete[] two_array;

      return;
}


int main(){
      srand (time(NULL));

      int rows;
      int columns;
      int value = 0;
      int bank = 0;

      cout << "Welcome to the Cars market" << endl;
      cout << "Enter number of rows: ";
      cin >> rows;
      cout << "Enter number of columns: ";
      cin >> columns;

      struct car* car_array = create_car_array();
      struct car** two_array = func(rows, columns);

      set_car_info(car_array, two_array, rows, columns);
      disply_case(two_array, rows, columns, value, bank, rows * columns);
      showcase(two_array, rows, columns, value, bank, car_array);

      free_strcut(car_array);
      free_dyarray(two_array, rows, columns);
}
