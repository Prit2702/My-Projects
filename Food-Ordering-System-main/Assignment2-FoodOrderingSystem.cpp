#include <iostream>
#include <fstream>
#include <string> 
#include <iomanip>
#include <cstdlib>
using namespace std;

const int FOOD = 15;
const int COL = 4;

void mainMenu(int[FOOD]);
void menuView(string[][COL], int&);
void managerView(string[][COL], int);
void menuUpdate(string[][COL], int);
void priceUpdate(string[][COL], int);
bool acceptOrder(string[][COL], int, int, int[FOOD]);
double totalPayments(string[][COL], int, double, double &);
int deliveryTime(string[][COL], int, int, int&);
void totalSalesDay(double, double&);
int popularDish(string[][COL], int, int, int[FOOD]);
void customerView(string[][COL], int, int[FOOD]);
void makeOrder(string[][COL], int, int[FOOD]);
void payment(string[][COL], int, double, int[FOOD], int, int);
void displayMessage (string[][COL], int, double, int);

int main(){
	int popularFood[FOOD];
	for (int i = 0; i < FOOD; i++){
		popularFood[i] = 0;
	}
	mainMenu(popularFood);
	return 0;
}

void mainMenu(int popularFood[FOOD]){
	
	int num_food = 0;
	
	string nameFoodPrice[FOOD][COL];
												
	int choice;

	cout <<"----------WELCOME------------"<<endl;

	cout << "\t		  Burger Restaurant	" << endl << endl;
	cout << "1. Restaurant Manager" << endl;
	cout << "2. Customer " << endl;
	cout << "3. Exit" << endl << endl;
	cout << "Please enter the number to select the user or enter 3 to exit: ";
	cin >> choice;
	
	while (choice != 1 && choice != 2 && choice != 3){
		cout << "Invalid number. Please try again!" << endl;
		cin >> choice;
	}
	
		if (choice == 1){
			cout << endl << endl;										
			system("pause");
			system("CLS");
			managerView(nameFoodPrice, num_food);

		}
			
		if (choice == 2){
			cout << endl << endl;	
			system("pause");		
			system("CLS");
			menuView(nameFoodPrice, num_food);
			customerView(nameFoodPrice, num_food, popularFood);

		}

		if (choice == 3){
			cout << "Thank you! Please come again! " << endl;
			cin.ignore();
		}	

}

void managerView(string nameFoodPrice[][COL], int num_food){			
	
	int managerChoice;
	
	cout << "\t\t Manager Access " << endl << endl;
	cout << "1. Create / Update Menu " << endl;
	cout << "2. Update Prices " << endl << endl;
	
	cout << "Please select a number for further details: ";
	cin >> managerChoice;

	while(managerChoice != 1 && managerChoice !=2){
		cout << endl;
		cout << "Invalid number! Please try again! " << endl;
		cin >> managerChoice;
		}	
		
		if(managerChoice == 1){
			cin.ignore();
			cout << endl << endl;
			system("pause");
			system("CLS");
			menuUpdate(nameFoodPrice, num_food);
		}
		else{
			cout << endl << endl;
			system("pause");
			system("CLS");
			menuView(nameFoodPrice, num_food);
			priceUpdate(nameFoodPrice, num_food);
		}
}
void menuView(string nameFoodPrice[][COL], int &num_food){	
	
	ifstream inFile;
	inFile.open("MenuFood.txt");	
	
	if (inFile){								
		
		int i = 0;
		
	while (inFile){
		
		int j = 0;
	
		getline(inFile, nameFoodPrice[i][j], '\t');
		getline(inFile, nameFoodPrice[i][j+1], '\t');
		getline(inFile, nameFoodPrice[i][j+2], ' ');
		getline(inFile, nameFoodPrice[i][j+3]);
		i++;
		num_food++;

		inFile.ignore();
		}	
		
	}
	else{
		cout << "Error when opening the file " << endl;
		}		
		
}

void menuUpdate(string nameFoodPrice[][COL], int num_food){
	
	int timeDelivery, stockFood;
	char choice;
	string newFoodName;
	double newFoodPrice;
		
	ofstream outFile;
	outFile.open("MenuFood.txt", ios_base::app);
	
	for (int i = 0; i < num_food; i++){
		
		for (int j = 0; j < COL; j++){
			
			if(j == 1){
				outFile << '\t';
				outFile << nameFoodPrice[i][j];
			}
			
			else if(j == 2){
				outFile << '\t';
				outFile << nameFoodPrice[i][j];
			}
			
			else if (j == 3){	
				outFile << ' ';
				outFile << nameFoodPrice[i][j];
			}
			else{
				outFile << ' ' << nameFoodPrice[i][j];
			}
		} 
		outFile << '\n';
	}
		
	do{
	cout << endl << "Please enter a new food name: " ;
	getline(cin, newFoodName);
	
	cout << "Please enter the price of the food: RM ";
	cin >> newFoodPrice;
	cout << endl;
	
	while (newFoodPrice < 4 || newFoodPrice > 30){
		
		cout << "The price of the food must be set in the range from "
		<< "RM 4 to RM 30 " << endl; 
		cout << "Please set the price of the food again: RM ";
		cin >> newFoodPrice;
		cout << endl;
	}
	
	cout << "Please enter the estimated delivery time of the food (in minutes): ";
	cin >> timeDelivery;
	
	while (timeDelivery < 5 || timeDelivery > 30){
		
		cout << "The delivery time for the food must be set in the range from "
		<< "5 minutes to 30 minutes " << endl; 
		cout << "Please set the delivery time again: ";
		cin >> timeDelivery;
		cout << endl;
		
	}
	
	cout << "Please enter the stock of the food: ";
	cin >> stockFood;
	cout << endl;
	 
	outFile << setprecision(2) << fixed << showpoint;
	outFile << '\n';
	outFile << ' ' << newFoodName << '\t' << newFoodPrice << '\t' << timeDelivery << ' ' << stockFood;

	cout << "Would you like to add another food? (Y/N) Your choice: ";
	cin >> choice;
	
	while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n'){
		cout << "Invalid ! Please try again! " << endl;
		cin >> choice;
		}
		
	cin.ignore();
		
	} while (choice == 'Y' || choice == 'y');
	
	cout << endl << "Update Successfully! Please check the updated menu " << endl;
}

void priceUpdate(string nameFoodPrice[][COL], int num_food){	

	cout << "--------MENU---------"<<endl;
	
		for (int x = 0; x < num_food; x++){
			cout << "Food " << x + 1 << ": ";
			
			for (int y = 0; y < COL - 2; y++){
			
			cout <<	nameFoodPrice[x][y] << "\t\t";
		
			if (y = 1){
				
				if (x < 3){	
				cout << "RM " << nameFoodPrice[x][y];
				}
				
				else{
					cout << "\tRM " << nameFoodPrice[x][y];
				}
			}
		
		cout << endl;
			}
		
		}
		
	cout << endl;

	int updateChoice;
	double updatePrice;

	cout << "Please enter the number available in order to update the food price: Food ";
	cin >> updateChoice;
	
	while (updateChoice < 1 || updateChoice > num_food){
		
		cout << "Invalid number. Please enter again: Food ";
		cin >> updateChoice; 
	}
	
	cout << "Please enter the new price for the dish: RM ";
	cin >> updatePrice;

	
	while (updatePrice < 4 || updatePrice > 30){
		
		cout << "The price of the dish must be updated in the range from "
		<< "RM 4 to RM 30 " << endl; 
		cout << "Please update the price of the dish again: RM ";
		cin >> updatePrice;
		cout << endl;
	}
	
	updateChoice--;
		
	ifstream inFile;
	inFile.open("MenuFood.txt");
	
	ofstream outFile;
	outFile.open("TempMenuFood.txt");
	
	if (inFile){
		
		int i = 0;
		
	while (inFile){
		
		int j = 0;
	
		getline(inFile, nameFoodPrice[i][j], '\t');
		getline(inFile, nameFoodPrice[i][j+1], '\t');
		getline(inFile, nameFoodPrice[i][j+2], ' ');
		getline(inFile, nameFoodPrice[i][j+3]);
		
		outFile << setprecision(2) << fixed << showpoint;
		if (updateChoice == i){
			outFile << ' ' << nameFoodPrice[i][j] << '\t'
			<< updatePrice << '\t' << nameFoodPrice[i][j+2] << ' ' << nameFoodPrice[i][j+3] << '\n';
			}
			
		else{
			outFile << ' ' << nameFoodPrice[i][j];
			outFile << '\t' << nameFoodPrice[i][j+1] << '\t' << nameFoodPrice[i][j+2] 
			<< ' ' << nameFoodPrice[i][j+3] << '\n';
			}
			
		i++;
		
		inFile.ignore();
		}	
			
	}
	
	else{
		cout << "Error when opening the file..." << endl;
		}

	inFile.close();
	outFile.close();
	remove("MenuFood.txt");
	rename("TempMenuFood.txt", "MenuFood.txt");
	
	cout << "Update Successfully! Kindly check the updated menu " << endl;
}

bool acceptOrder(string nameFoodPrice[][COL], int num_food, int arrFoodChoice, int stockFood[FOOD]){
	
	bool status = true;

	for (int i = 0; i < FOOD; i++){
			
		if (i == arrFoodChoice){
			stockFood[i]--;
				
			if (stockFood[i] < 0){
				status = false;
			}
				
			else{
				status = true;
			}
		}
			
	}

	return status;
}

double totalPayments(string nameFoodPrice[][COL], int arrFoodChoice, double orderPrice, double &newOrderPrice){
	
	orderPrice = strtod(nameFoodPrice[arrFoodChoice][1].c_str(), NULL);
	newOrderPrice += orderPrice;
	
	return newOrderPrice;
}

int deliveryTime(string nameFoodPrice[][COL], int arrFoodChoice, int estimatedTime, int &newEstimatedTime){
	
	estimatedTime = strtod(nameFoodPrice[arrFoodChoice][2].c_str(), NULL);
	newEstimatedTime += estimatedTime;
	
	return newEstimatedTime;
}

void customerView(string nameFoodPrice[][COL], int num_food, int popularFood[FOOD]){
	
	char orderFoodChoice;
	
	cout << "------------MENU--------------"<<endl;
	
		for (int x = 0; x < num_food; x++){
			cout << "Food " << x + 1 << ": ";
			
			for (int y = 0; y < COL - 2; y++){
			
			cout <<	nameFoodPrice[x][y] << "\t\t";
		
			if (y = 1){
				
				if (x < 3){	
				cout << "RM " << nameFoodPrice[x][y];
				}
				
				else{
					cout << "\tRM " << nameFoodPrice[x][y];
				}
			}
		
		cout << endl;
			}
		
		}
	cout << endl << "Welcome! New Customer! :)" << endl;
	cout << "Would you like to make food order? (Y/N) " << endl;
	cout << "Press Y or to make food order or press N to exit. Your choice: ";	
	cin >> orderFoodChoice;
		
		while(orderFoodChoice != 'Y' && orderFoodChoice != 'y' && orderFoodChoice != 'N' && orderFoodChoice != 'n'){
		cout << "Invalid choice ! Please try again! Your choice: ";
		cin >> orderFoodChoice;
		}
		
		if (orderFoodChoice == 'Y' || orderFoodChoice == 'y'){
			makeOrder(nameFoodPrice, num_food, popularFood);
		}
		
		else {
		cout << endl << "Thank you! Please come again! :D" << endl;
		}
	
}

void makeOrder(string nameFoodPrice[][COL], int num_food, int popularFood[FOOD]){
	
	const int NUM_ORDER = 15;
	char confirm, paymentChoice;
	int foodChoice, arrFoodChoice;
	int totalDeliveryTime, estimatedTime, newEstimatedTime = 0;
	static int num_customers = 0;
	int num_orders_customers = 0;
	double orderPrice, newOrderPrice = 0, totalPay;
	bool orderFlag;
	int num_most_popular_dish;
	int stockFood[FOOD];
		
	for (int i = 0; i < num_food; i++){						
	
		if (i < num_food){	
		
			stockFood[i] = stoi(nameFoodPrice[i][3]);
		}
		
		else{
			stockFood[i] = 0;
		}
	}



	do{	
		cout << endl;
		cout << "Please enter the number as shown in menu to order the food: ";
		cin >> foodChoice;
	
		while (foodChoice < 1 || foodChoice > num_food){
		
		cout << "Invalid number. Please enter the number again: Food ";
		cin >> foodChoice; 
		}
		
		arrFoodChoice = foodChoice - 1;
	
		cout << setprecision(2) << fixed << showpoint;
		cout << "You order of food is " << nameFoodPrice[arrFoodChoice][0] << endl;
		
		totalPay = totalPayments(nameFoodPrice, arrFoodChoice, orderPrice, newOrderPrice);
		totalDeliveryTime = deliveryTime(nameFoodPrice, arrFoodChoice, estimatedTime, newEstimatedTime);
		num_most_popular_dish = popularDish(nameFoodPrice, num_food, arrFoodChoice, popularFood);
		orderFlag = acceptOrder(nameFoodPrice, num_food, arrFoodChoice, stockFood);
	
		if (orderFlag == true){
		cout << "Order Accepted! " << endl;
		}
		
		else{
		cout << "Out of stock! You will be returned to main menu " << endl;
		system("pause");
		system("CLS");
		mainMenu(popularFood);
		}
		
		cout << "The total price is RM" << totalPay << endl << endl;
		cout << "Would you like to add more? (Y/N)" << endl;
		cin >> confirm;
		
		while(confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n'){
		cout << "Invalid ! Please try again! " << endl;
		cin >> confirm;
		
		}
		
		num_orders_customers++;
		} while (confirm == 'Y' || confirm == 'y');
		
		num_customers++;
		
		cout << endl << "You have ordered " << num_orders_customers << " dish(es) " << endl;
		cout << "Estimated delivery time is " << totalDeliveryTime << " minutes" << endl;
		cout << "The total payment is RM " << totalPay << endl << endl;
		cout << "Press P to make your payment: ";
		cin >> paymentChoice;
		
		while(paymentChoice != 'P' && paymentChoice != 'p'){
			cout << "Invalid! Please try again! " << endl;
			cin >> paymentChoice;
		}
		
		cout << endl << endl;
		system("pause");
		system("CLS");
		payment(nameFoodPrice, num_food, totalPay, popularFood, num_customers, num_most_popular_dish);
}
void payment(string nameFoodPrice[][COL], int num_food, double totalPay, int popularFood[FOOD], int num_customers, int num_most_popular_dish){
	
	double pay; 														
	static double sales = 0;
	
	cout << "Please enter the amount of your payment: RM ";
	cin >> pay;
	
	while (pay != totalPay){
		
		cout << "Invalid amount! Please enter the exact amount of your payment: RM ";
		cin >> pay; 
	}
	
	totalSalesDay(totalPay, sales);
	displayMessage(nameFoodPrice, num_customers, sales, num_most_popular_dish);
	
	cout << "Payment successful! " << endl;
	cout << "Please come again! :D " << endl;
	
	cout << endl << endl;
	system("pause");
	system("CLS");
	customerView(nameFoodPrice, num_food, popularFood);
	
}

void totalSalesDay(double totalPay, double &sales){
	
	sales += totalPay;
		
}

int popularDish(string nameFoodPrice[][COL], int num_food, int arrFoodChoice, int popularFood[FOOD]){	
	
	int mostPopular, numMostPopular;
	
	popularFood[arrFoodChoice]++;
		
	mostPopular = popularFood[0];
	
	for (int x = 1; x < FOOD; x++){
			
		if (mostPopular < popularFood[x]){
				
			mostPopular = popularFood[x];
			numMostPopular = x;
				
			}
			
	}
	
	return numMostPopular;
}

void displayMessage (string nameFoodPrice[][COL], int num_customers, double sales, int num_most_popular_dish){
	
	ofstream outFile;
	outFile.open("OutputFile.txt");
	
	outFile << "Number of customers for the day: " << num_customers << endl;
	outFile << setprecision(2) << fixed << showpoint;
	outFile << "The total sales is RM " << sales << endl;
	outFile << "The most popular dish is " << nameFoodPrice[num_most_popular_dish][0] << endl;
	
	outFile.close();
}
