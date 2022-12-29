#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <cstring>

using namespace std;

struct lunchMeal
{
    char lunch[4][20];

}lnch[3];

struct dinnerMeal
{
    char dinner[4][20];

}dine[3];

struct customerReceipt
{
    char receipt[4][20];

}meal[6];

struct Employee
{
	char name[30];
	char position[20];
	char id[10];
	float rate;
	int hours;
};


struct water
{
    int coke;
	int lightcoke;
	int sprite;
	int redbull;
};

struct eat
{
    int chickens;
	int fries;
	int fishes;
	int buns;
	int paratha;
	int mac;
};

struct Inventory // NESTED STRUCT
{
	water drink;
	eat food;
};
void declareMeal(dinnerMeal dine[], lunchMeal lnch[])//function 2D array
{
    ifstream inLunch,inDinner;
    int i,j;

    inLunch.open("lunchMenu.txt");
    inDinner.open("dinnerMenu.txt");

    if(!inLunch)
    {
        cout<<"File lunch menu does not exist";
        exit(-1);
    }

    if(!inDinner)
    {
        cout<<"File dinner menu does not exist";
        exit(-1);
    }

    for(j = 0; j < 3 ; j++)
    {
        for(i = 0; i < 4 ; i++)
            inLunch.getline(lnch[j].lunch[i],20,';');
    }

    for(j = 0; j < 3 ; j++)
    {
        for(i = 0; i < 4 ; i++)
            inDinner.getline(dine[j].dinner[i],20,';');
    }

    inLunch.close();
    inDinner.close();
}


int bootingScreen()
{
    int num;

    cout<<" WELCOME TO \"PROF & CO (FAST FOOD)\" SERVICE"<<endl;
    cout<<"     --TYPE OF SERVICE--"<<endl;
    cout<<" (1) - CUSTOMER"<<endl;
    cout<<" (2) - EMPLOYEE"<<endl;

    cout<<" Please choose a service :";
    cin>>num;

    return num;
}

void menu()
{
    cout<<"|-----LUNCH DEAL-----|-----DINNER DEAL-----|"<<endl;
    cout<<"|       SET A        |        SET A        |"<<endl;
    cout<<"|  -Fried Chicken    |   -Fish Fillet      |"<<endl;
    cout<<"|  -Fries            |   -Red Bull         |"<<endl;
    cout<<"|  -Coke             |                     |"<<endl;
    cout<<"|  -RM 19            |   -RM 12            |"<<endl;
    cout<<"|--------------------|---------------------|"<<endl;
    cout<<"|       SET B        |        SET B        |"<<endl;
    cout<<"|  -Burger           |   -Paratha Wrap     |"<<endl;
    cout<<"|  -Coke             |   -Sprite           |"<<endl;
    cout<<"|  -RM 14            |   -RM 8             |"<<endl;
    cout<<"|--------------------|---------------------|"<<endl;
    cout<<"|       SET C        |        SET C        |"<<endl;
    cout<<"|  -Fries            |   -Mac & Cheese     |"<<endl;
    cout<<"|  -Coke             |   -Coke Light       |"<<endl;
    cout<<"|  -RM 10            |   -RM 13            |"<<endl;
    cout<<"|--------------------|---------------------|"<<endl;
}

int discount(double &discount, int &priceCard)
{
    int typeDiscount,notify;
    char choice;

    cout<<"-- TYPE OF DISCOUNTS --"<<endl;
    cout<<" (1) - Student"<<endl;
    cout<<" (2) - Member Card"<<endl;
    cout<<" (3) - None of the above"<<endl;
    cout<<" Please choose type of discount :";

    cin>>typeDiscount;

    if(typeDiscount == 1)
    {
         discount = 0.1;
         priceCard = 0;
         notify = 0;
    }
    else
        if(typeDiscount == 2)
        {
            discount = 0.15;
            priceCard = 0;
            notify = 0;
        }
        else
            if(typeDiscount == 3)
            {
                cout<<"\n Would you like to create a member card? (Y/N)";
				cout<<"\n If yes, an additional RM 20 will be adde : ";
                cin>>choice;

                if(choice == 'Y')
                {
                    discount = 0.15;
                    priceCard = 20;
                    notify = 1;
                }
                if(choice == 'N')
                {
                    discount = 0;
                    priceCard = 0;
                    notify = 0;
                }
            }
            else
            {
                cout<<" WRONG INPUT :  NO CHOICE HAS BEEN MADE ";
                priceCard = 0;
                notify = 0;
                discount = 0;
            }


    return notify;
}

double calcMeal(double total, double discount, int cardPrice)
{
    double finalTOT;

    finalTOT = (total + cardPrice) - ((total + cardPrice) * discount);

    return finalTOT;
}

void eatingLoc(int place[], int &x)
{

    cout<<" Would you like to eat -"<<endl;
    cout<<" 1 - Eat Here "<<endl;
    cout<<" 2 - Take away "<<endl;

    cout<<" Please choose :";

    cin>>place[x];
}

void chooseMeal(int &countLA,int &countLB,int &countLC,int &countDA, int &countDB, int &countDC, int &custQ) //1D ARRAY
{
    char deal,mSet,purchMore;
    int i,quant[30],j = 0, k , counter = 0,x =0 , loc,priceCard ,q ,eatPlace[30] , locArr[30], note;
    bool repeat = true;
    double price,tot = 0, discountPrice, grandTOT;


    ifstream inFile;
    ofstream outFile;

    declareMeal(dine,lnch);

    remove("customerOrder.txt");

    outFile.open("customerOrder.txt" , ios::app);

    inFile.open("customerOrder.txt");

    if(!inFile)
    {
        cout<<"File does not exist";
        exit(-1);
    }

    while(repeat)
    {
        cout<<endl;

        eatingLoc(eatPlace,x);

        cout<<" Please choose deal (L - Lunch / D - Dinner ) : ";
        cin>>deal;

        cout<<endl;

        cout<<" Please choose set (A/B/C) : ";
        cin>>mSet;

        cout<<" Please enter quantity : ";
        cin>>quant[x];

        cout<<endl;

        if(deal == 'L')
        {
            if(mSet == 'A')
            {
                loc = 0;
                countLA++;
                price = 19;
            }

            if(mSet == 'B')
            {
                loc = 1;
                countLB++;
                price = 14;
            }

            if(mSet == 'C')
            {
                loc = 2;
                countLC++;
                price = 10;
            }
        }

        if(deal == 'D')
        {
            if(mSet == 'A')
            {
                loc = 0;
                countDA++;
                price = 12;
            }

            if(mSet == 'B')
            {
                loc = 1;
                countDB++;
                price = 8;
            }

            if(mSet == 'C')
            {
                loc = 2;
                countDC++;
                price = 13;
            }
        }

        locArr[x] = loc;

        if(deal == 'L')
        {
            for(i=0 ; i<4; i++)
            {
                outFile<<lnch[loc].lunch[i];
                outFile<<";";
            }
            outFile<<endl;
        }

        if(deal == 'D')
        {
            for(i=0 ; i<4; i++)
            {
                outFile<<dine[loc].dinner[i];
                outFile<<";";
            }
            outFile<<endl;
        }

        tot += price*quant[x];


        cout<<" Would you like to purchase more? (Y-Yes/N-No) : ";
        cin>>purchMore;

        if(purchMore == 'Y')
            repeat = true;

        if(purchMore == 'N')
            repeat = false;

        x++;
        counter++;

    }//endwhile

    while(!inFile.eof())
    {
        for(k = 0 ; k < 4 ; k++)
        {
            inFile.getline(meal[j].receipt[k],20,';');
        }
        j++;
    }

    system("CLS");

    note = discount(discountPrice,priceCard);

    system("CLS");

    grandTOT = calcMeal(tot,discountPrice,priceCard);

    cout<<"Thank you for purchasing at PROF & CO (FAST FOOD)"<<endl;
    cout<<"==========================="<<endl;

    for(q = 0 ; q < counter ; q++)
    {
        if(locArr[q] == 0)
            cout<<endl;

        for(k = 0 ; k < 4 ; k++)
        {
            if(q == 0 && locArr[q] == 0 && k == 0)
                cout<<meal[q].receipt[0]<<endl;
            else
                if(q == 0 && locArr[q] == 0 && k > 0)
                    cout<<" "<<meal[q].receipt[k]<<endl;
            else
                cout<<" "<<meal[q].receipt[k]<<endl;
        }
        cout<<" Place to eat :";

        if(eatPlace[q] == 1)
        {
           cout<<" Here"<<endl;
        }
        if(eatPlace[q] == 2)
        {
            cout<<" Take-Away"<<endl;
        }

        cout<<" Quantity : "<<quant[q]<<endl<<endl;
        cout<<"===========================";
    }
    cout<<endl<<endl;

    cout<<" --MEMBER CARD NOTIFY-- "<<endl;

    if( note == 1 )
    {
         cout<<" An additional RM "<<priceCard<<" has been added"<<endl;
         cout<<" Thank you for joining PROF & CO (FAST FOOD)"<<endl<<endl;

    }
    cout<<" A discount of "<<discountPrice*100<<"% has been given"<<endl<<endl;

    cout<<" Total price :RM "<<grandTOT<<endl<<endl;

    custQ++;

    if(custQ < 10)
        cout<<" Your Que Number : 00"<<custQ<<endl<<endl;
    else
        if(custQ >= 10 && custQ <= 99)
            cout<<" Your Que Number : 0"<<custQ<<endl<<endl;
        else
            cout<<" Your Que Number : "<<custQ<<endl<<endl;

    inFile.close();
    outFile.close();
}

void displaySeller(int locDinnerHigh ,int locDinnerLow ,int locLunchHigh,int locLunchLow,int lowLunch,int highLunch,int lowDine,int highDine)
{
    char infoLunchLow[7], infoLunchHigh[7], infoDineLow[7], infoDineHigh[7];

    if(locLunchLow == 0)
        strcpy(infoLunchLow,"Set A");
    if(locLunchLow == 1)
        strcpy(infoLunchLow,"Set B");
    if(locLunchLow == 2)
        strcpy(infoLunchLow,"Set C");

    if(locLunchHigh == 0)
        strcpy(infoLunchHigh,"Set A");
    if(locLunchHigh == 1)
        strcpy(infoLunchHigh,"Set B");
    if(locLunchHigh == 2)
        strcpy(infoLunchHigh,"Set C");

    if(locDinnerLow == 0)
        strcpy(infoDineLow,"Set A");
    if(locDinnerLow == 1)
        strcpy(infoDineLow,"Set B");
    if(locDinnerLow == 2)
        strcpy(infoDineLow,"Set C");

    if(locDinnerHigh == 0)
        strcpy(infoDineHigh,"Set A");
    if(locDinnerHigh == 1)
        strcpy(infoDineHigh,"Set B");
    if(locDinnerHigh == 2)
        strcpy(infoDineHigh,"Set C");

    cout<<endl;
    cout<<" Highest lunch set ordered is "<<infoLunchHigh<<" : "<<highLunch<<" orders"<<endl;
    cout<<" Lowest lunch set ordered is "<<infoLunchLow<<" : "<<lowLunch<<" orders"<<endl<<endl;

    cout<<" Highest dinner set ordered is "<<infoDineHigh<<" : "<<highDine<<" orders"<<endl;
    cout<<" Lowest dinner set ordered is "<<infoDineLow<<" : "<<lowDine<<" orders"<<endl;


}
void bestSeller()
{
    cin.sync();
    int bestLunch[3], bestDinner[3], locL , locD , highestLunch, highestDinner, lowestDinner, lowestLunch;
    int locDinnerHigh , locDinnerLow , locLunchHigh, locLunchLow;
    ifstream inLunch, inDine;

    inLunch.open("bestLunch.txt");
    if(!inLunch)
    {
        cout<<"FILE DOES NOT EXIST";
        exit(-1);
    }

    inDine.open("bestDine.txt");
    if(!inDine)
    {
        cout<<"FILE DOES NOT EXIST";
        exit(-1);
    }

    for(int i = 0 ; i < 3 ; i++)
        inLunch>>bestLunch[i];

    for(int i = 0 ; i < 3 ; i++ )
        inDine>>bestDinner[i];

    highestLunch = 0;
    lowestLunch = 99999;
    lowestDinner = 99999;
    highestDinner = 0;

    for(int k=0;k<3;k++)
    {

            if (bestLunch[k] > highestLunch)
            {
                highestLunch = bestLunch[k];
                locLunchHigh = k;
            }

            if (bestLunch[k] < lowestLunch)
            {
                lowestLunch = bestLunch[k];
                locLunchLow = k;
            }

    }
    for(int k = 0 ; k < 3 ; k++)
    {

            if (bestDinner[k] > highestDinner)
            {
                highestDinner = bestDinner[k];
                locDinnerHigh = k;
            }

            if (bestDinner[k] < lowestDinner)
            {
                lowestDinner = bestDinner[k];
                locDinnerLow = k;
            }

    }

    displaySeller(locDinnerHigh , locDinnerLow , locLunchHigh, locLunchLow , lowestLunch ,highestLunch ,lowestDinner ,highestDinner );

    inLunch.close();
    inDine.close();
    cin.ignore();
}

void infileBest(int &LA,int &LB,int &LC,int &DA,int &DB,int &DC)
{
    ifstream inLunch, inDine;
    inLunch.open("bestLunch.txt");
    inDine.open("bestDine.txt");

    if(!inLunch)
    {
        cout<<"FILE DOES NOT EXIST ";
        exit(-1);
    }

     if(!inDine)
    {
        cout<<"FILE DOES NOT EXIST ";
        exit(-1);
    }

    inLunch>>LA;
    inLunch>>LB;
    inLunch>>LC;
    inDine>>DA;
    inDine>>DB;
    inDine>>DC;

    inLunch.close();
    inDine.close();
}

void outfileBest(int &LA,int &LB,int &LC,int &DA,int &DB,int &DC)
{
    ofstream outLunch,outDine;
    outLunch.open("bestLunch.txt");
    outDine.open("bestDine.txt");

    outLunch<<LA<<endl;
    outLunch<<LB<<endl;;
    outLunch<<LC<<endl;
    outDine<<DA<<endl;
    outDine<<DB<<endl;
    outDine<<DC<<endl;

    outLunch.close();
    outDine.close();

}

void customerService(int & custQ)
{
    int priceCard,transac;
    double discount,tot,grandTOT;
    char choice,eatPlace;
    int countLA , countLB , countLC , countDA , countDB , countDC ;

    cout<<" WELCOME TO PROF & CO (FAST FOOD) DEAR VALUED CUSTOMER"<<endl<<endl;

    menu();

    infileBest(countLA,countLB,countLC,countDA,countDB,countDC);
    chooseMeal(countLA,countLB,countLC,countDA,countDB,countDC,custQ);
    outfileBest(countLA,countLB,countLC,countDA,countDB,countDC);

    cout<<" **Please wait until you que number is displayed "<<endl;
    cout<<"  to pick up food from pick up counter**"<<endl<<endl;
    cout<<" Press 1 to end transaction :";
    cin>>transac;

    if(transac == 1)
        system("CLS");
}

void NewEmpStore() // Function to store employee information in EmpInfo.txt
{
	Employee empNew;

	ofstream empIn;
	empIn.open("EmpInfo.txt", ios::app);
	cin.sync();
	cout << "Enter Name : ";
	cin.getline(empNew.name,30);

	cout << "Enter Position : ";
	cin.getline(empNew.position,20);

	cout << "Enter Staff ID : ";
	cin.getline(empNew.id,10);

	cout << "Enter Hours Worked : ";
	cin >> empNew.hours;

	if(strcmp(empNew.position,"Head Chef") == 0)
		empNew.rate = 5.0;
	else
		if(strcmp(empNew.position,"Cook") == 0)
			empNew.rate = 3.0;
		else
			if(strcmp(empNew.position,"Cashier") == 0)
				empNew.rate = 2.5;
			else
				if(strcmp(empNew.position,"Manager") == 0)
					empNew.rate = 4.5;
				else
					if(strcmp(empNew.position,"Waiter") == 0)
						empNew.rate = 2.0;
					else
					{
						cout << "No Information on Position " << endl;
						cout << "Enter Hourly Rate : " ;
						cin >> empNew.rate;
					}

	empIn << empNew.name << "/" << empNew.position << "/" << empNew.id << "/" << empNew.rate << " " << empNew.hours << " ";

	empIn.close();
	return;
}

void DisplayEmployeeInfo() // To display all the workers and the relevant information
{
	Employee empData[50];
	ifstream empTotal;
	empTotal.open("EmpInfo.txt");
	if(!empTotal)
	{
		cout << "An Erorr Has Occured : File Was Not Found!";
		exit(-1);
	}

	int i = 0;
	int j = 0;
	while(!empTotal.eof())
	{
		empTotal.getline(empData[i].name,30,'/');
		empTotal.getline(empData[i].position,20,'/');
		empTotal.getline(empData[i].id,10,'/');
		empTotal >> empData[i].rate >> empData[i].hours ;
		i++;
		j++;
	}

	for(int r = 0 ; r < j-1 ; r++)
	{
		cout << "Employee " << r+1 << ":\n\t Name \t\t: " << empData[r].name << endl;
		cout << "\t Position \t: " << empData[r].position << endl;
		cout << "\t Staff ID \t: " << empData[r].id << endl;
		cout << "\t Hours Worked \t: "<< empData[r].hours << endl;
		cout << "\t Hourly Rate \t: RM " << empData[r].rate << "/hour" << endl << endl;
	}

	empTotal.close();

	cout << "Press Enter to continue " ;

	cin.sync();
	cin.ignore();

	return;
}

void InventoryDisplay(Inventory stock)
{
	char ingredients[6][15] = {"Fried Chicken","Fish Fillet","Fries","Paratha Wrap","Burger Buns","Macaroni"};
	char drinks[4][15] = {"Coke","Coke Light","Red Bull","Sprite"};

    cout<<endl;
    cout << "FOODS : " << endl;

	for(int i = 0 ; i < 6 ; i++)
	{
		cout << ingredients[i] << " \t ";
	}
	cout << endl;

	cout << setw(7) << stock.food.chickens << setw(15) << stock.food.fishes <<setw(14) << stock.food.fries <<setw(11);
	cout << stock.food.paratha << setw(16) <<  stock.food.buns << setw(15) << stock.food.mac <<endl;

	cout << "\nDRINKS : " << endl;

	for(int i = 0; i < 4 ; i++)
	{
		cout << drinks[i] << " \t " ;
	}
	cout << endl;

	cout << setw(2)<< stock.drink.coke << setw(13) << stock.drink.lightcoke << setw(15)<<  stock.drink.redbull << setw(15) <<  stock.drink.sprite << endl;

	return;
}

void InventoryInfo(Inventory &stock) //
{
    ofstream outFile;
    outFile.open("stock.txt");

	cout << "Enter Amount of Chicken In Stock \t: " ;
	cin >> stock.food.chickens;
	cout << "Enter Amount of Fish In Stock \t\t: " ;
	cin >> stock.food.fishes;
	cout << "Enter Amount of Fries In Stock \t\t: ";
	cin >> stock.food.fries;
	cout << "Enter Amount of Paratha Wrap In Stock \t: ";
	cin >> stock.food.paratha;
	cout << "Enter Amount of Burger Buns In Stock \t: ";
	cin >> stock.food.buns;
	cout <<"Enter Amount of Coke In Stock \t\t: ";
	cin >> stock.drink.coke;
	cout << "Enter Amount of Light Coke In Stock \t: ";
	cin >> stock.drink.lightcoke;
	cout << "Enter Amount of Sprite In Stock \t: ";
	cin >> stock.drink.sprite;
	cout << "Enter Amount of Red Bull In Stock \t: ";
	cin >> stock.drink.redbull;
	cout << "Enter Amount of Macaroni in Stock \t: ";
	cin >> stock.food.mac;

    outFile<<stock.food.chickens<<" ";
    outFile<<stock.food.fishes<<" ";
    outFile<<stock.food.fries<<" ";
    outFile<<stock.food.paratha<<" ";
    outFile<<stock.food.buns<<" ";
    outFile<<stock.drink.coke<<" ";
    outFile<<stock.drink.lightcoke<<" ";
    outFile<<stock.drink.sprite<<" ";
    outFile<<stock.drink.redbull<<" ";
    outFile<<stock.food.mac<<" ";

    outFile.close();
}

void autoUpdateInventory(Inventory &stock)
{

    ifstream inFile;

    inFile.open("stock.txt");

    if(!inFile)
    {
        cout<<" File does not exist";
        exit(-1);
    }

    inFile>>stock.food.chickens;
    inFile>>stock.food.fishes;
    inFile>>stock.food.fries;
    inFile>>stock.food.paratha;
    inFile>>stock.food.buns;
    inFile>>stock.drink.coke;
    inFile>>stock.drink.lightcoke;
    inFile>>stock.drink.sprite;
    inFile>>stock.drink.redbull;
    inFile>>stock.food.mac;

    inFile.close();
}

void InventoryMenu() // 
{
	char o = 'Y';
	Inventory stock;
	int option;
	while(o != 'N')
	{
		cout << "1. Display Inventory " << endl;
		cout << "2. Update Inventory " << endl;
		cout << "It is recommended to Update Inventory if this is the first time" << endl << endl;

		cout << "Choose Your Option : " ;
		cin >> option ;

		if(option == 1)
        {
            autoUpdateInventory(stock);
            InventoryDisplay(stock);
            cout<<endl;
        }
		else
			if(option == 2)
				InventoryInfo(stock);

		cout << "Do You Wish to Continue? (Y/N) : " ;
		cin >> o;
		system("CLS");
	}
}

void inputProfit()
{
    int year;
    int i,j;
    int profit[12];

    cin.sync();

    ofstream out;
    out.open("profit.txt" , ios::app);

    cout<<"Please input what year it is :";

    cin>>year;

    for(j = 0; j < 12 ; j++)
    {
        cout<<" Enter profit for month "<<j+1<<":";
        cin>>profit[j];
    }

    out<<endl;
    out<<year<<" "<<endl;

    for(i = 0 ; i < 12 ; i++)
        out<<profit[i]<<" ";

    out.close();

}

void displayMonthlySales(int years ,int sales [][10],char month [][20],int year[]) //2D ARRAY IN FUNCTION
{
    int highest, sum;

    cout<<" **MONTHLY SALES FOR EACH YEAR** "<<endl;



    for(int i = 0; i < years ; i++)
    {
        cout<<"\t"<<year[i];
    }

    cout<<endl;

    for (int k=0;k<12;k++)
    {
        cout<<month[k];

        for (int h=0; h< years;h++)
        {
            cout<<"\t"<<sales[k][h];
        }
        cout<<endl;
    }


}

void monthSales()
{
    char month[12][20]={"Jan","Feb","Mar","Apr","May","Jun","July","Aug","Sept","Oct","Nov","Dec"};
    int year[10];
    int sales[12][10];
    int years , highest, sum = 0, loc;


    cout<<"Please input how many years to display data (less then 10) :";
    cin>>years;

    if(years >= 10)
        exit(-1);

    ifstream infile;
    infile.open("profit.txt");

    cout<<endl;


    if(!infile)
    {
        cout<<"FILE DOES NOT EXIST";
        exit(-1);
    }

    for (int i=0; i <years ;i++)
    {
        infile>> year[i];

        for (int j=0;j<12 ;j++)
        {
            infile>>sales[j][i];
        }
    }

    displayMonthlySales(years,sales,month,year);

      highest = sales[0][0];

    for (int i=0;i< years ;i++)
    {
        sum =0;


        for (int j=0;j<12;j++)
        {
            sum += sales[j][i];

        }
        if(sum > highest)
        {
            highest=sum;
            loc = i;
        }
    }
    cout<<" HIGHEST PROFIT RM :"<<highest;
    cout<<"\n Year :"<<year[loc];

    infile.close();
}

void profitMenu() 
{
    char o = 'Y';
	int option;
	while(o != 'N')
	{
		cout << "1. Display yearly profit" << endl;
		cout << "2. Update yearly sales " << endl;
		cout << "It is recommended to Update sales if this is the first time" << endl;
		cout << "Please use this service only if the yearly data is above 3 years " <<endl<<endl;

		cout << "Choose Your Option : " ;
		cin >> option ;

		if(option == 1)
        {
            monthSales();
            cout<<endl;
        }
		else
			if(option == 2)
				inputProfit();

		cout << "Do You Wish to Continue? (Y/N) : " ;
		cin >> o;
		system("CLS");
	}
}

int main()
{
    int typeService, custQ = 0 , control = 0 , falseControl = 0, choice;


    if(control == 0)
    {
        cout<<"Press '1' to START : ";
        cin>>control;
    }

    system("CLS");

    if(control != 1)
        cout<<" Wrong input";

    if(control == 1)
        typeService = bootingScreen();

    while(control == 1)
    {
            if(falseControl == 1)
            {
                system("CLS");
                cout<<"     --PLEASE ENTER CORRECTLY--\n";
                typeService = bootingScreen();
            }

            if(typeService == 1)
            {
                system("CLS");
                customerService(custQ);
                falseControl = 0;
                cout<<"Press 1 for next customer : ";
                cin>>control;
            }
            else
                if(typeService == 2)
                {
                    system("CLS");
                    cout << "Management System For PROF & CO (FAST FOOD)" << endl;
                    cout << "Choose Option : " << endl;
                    cout << "**Enter '0' (ZERO) to stop**"<<endl;
                    cout << "(1). Inventory " << endl;
                    cout << "(2). Add New Employee " << endl;
                    cout << "(3). Show Employees Information " << endl;
                    cout << "(4). Show Current Best Selling Set " << endl;
                    cout << "(5). Yearly / Monthly Sales Statistic " << endl;
                    cout << "Enter Number : ";
                    cin >> choice;

                    system("CLS");

                    if(choice == 1)
                        InventoryMenu();

                    else
                        if(choice == 2)
                            NewEmpStore();
                        else
                            if(choice == 3)
                                DisplayEmployeeInfo();
                            else
                                if(choice == 4)
                                    bestSeller();
                                else
                                    if(choice == 5)
                                        profitMenu();
                                else
                                    if(choice == 0)
                                    {
                                        break;
                                        typeService = 0;
                                    }
                                    else
                                    {
                                        cin.sync();
                                        cout << "Invalid Option ! " << endl;
                                    }
                    }
                    else
                    {
                        cout<<"   **INVALID OPTION** ";
                        falseControl = 1;
                    }
        }

        cout<<"\n Thank you for using PROF & CO (FAST FOOD) management system"<<endl;
}
