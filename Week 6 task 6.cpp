#include <iostream>
#include <vector>
using namespace std;

const double MIN_GRAVEL_WEIGHT = 49.9;
const double MAX_GRAVEL_WEIGHT = 50.1;
const double MIN_SAND_WEIGHT = 49.9;
const double MAX_SAND_WEIGHT = 50.1;
const double MIN_CEMENT_WEIGHT = 24.9;
const double MAX_CEMENT_WEIGHT = 25.1;

const double CEMENT_PRICE = 3.0;
const double GRAVEL_PRICE = 2.0;
const double SAND_PRICE = 2.0;
const double SPECIAL_PACK_PRICE = 10.0;

bool checkSackContentsAndWeight(char contents, double weight);
double calculateRegularPrice(char contents);
double calculateSpecialPackPrice(int cementSacks, int sandSacks, int gravelSacks);

int main() 
{
    
    
    char sackContents;
    double sackWeight;

    cout << "Task 1 - Check the contents and weight of a single sack\n";
    cout << "Enter the contents of the sack (C for cement, G for gravel, S for sand): ";
    cin >> sackContents;
    cout << "Enter the weight of the sack in kilograms: ";
    cin >> sackWeight;

    if (checkSackContentsAndWeight(sackContents, sackWeight)) 
	{
        cout << "Accepted sack:\n";
        cout << "Contents: " << sackContents << "\n";
        cout << "Weight: " << sackWeight << " kilograms\n";
    } else 
	{
        cout << "Rejected sack. ";
        if (sackWeight < MIN_CEMENT_WEIGHT || sackWeight > MAX_CEMENT_WEIGHT) 
		{
            cout << "Invalid weight.\n";
        } else 
		{
            cout << "Invalid contents.\n";
        }
    }

    int numCement, numGravel, numSand;
    int rejectedSacks = 0;
    double totalWeight = 0.0;

    cout << "\nTask 2 - Check a customer's order for delivery\n";
    cout << "Enter the number of cement sacks: ";
    cin >> numCement;
    cout << "Enter the number of gravel sacks: ";
    cin >> numGravel;
    cout << "Enter the number of sand sacks: ";
    cin >> numSand;

    for (int i = 0; i < numCement; ++i) 
	{
        if (!checkSackContentsAndWeight('C', MIN_CEMENT_WEIGHT)) 
		{
            rejectedSacks++;
        }
        totalWeight += MIN_CEMENT_WEIGHT;
    }

    for (int i = 0; i < numGravel; ++i) 
	{
        if (!checkSackContentsAndWeight('G', (MIN_GRAVEL_WEIGHT + MAX_GRAVEL_WEIGHT) / 2)) 
		{
            rejectedSacks++;
        }
        totalWeight += (MIN_GRAVEL_WEIGHT + MAX_GRAVEL_WEIGHT) / 2;
    }

    for (int i = 0; i < numSand; ++i) 
	{
        if (!checkSackContentsAndWeight('S', (MIN_SAND_WEIGHT + MAX_SAND_WEIGHT) / 2)) 
		{
            rejectedSacks++;
        }
        totalWeight += (MIN_SAND_WEIGHT + MAX_SAND_WEIGHT) / 2;
    }

    cout << "Total weight of the order: " << totalWeight << " kilograms\n";
    cout << "Number of rejected sacks: " << rejectedSacks << "\n";

    double regularPrice = calculateRegularPrice('C') * numCement +
                          calculateRegularPrice('G') * numGravel +
                          calculateRegularPrice('S') * numSand;

    int numSpecialPacks = min({numCement, 2 * numSand, 2 * numGravel});
    double specialPackPrice = calculateSpecialPackPrice(numCement, 2 * numSand, 2 * numGravel);
    double totalPrice = regularPrice - (numSpecialPacks * (regularPrice - specialPackPrice));

    cout << "\nTask 3 - Calculate the price for a customer's order\n";
    cout << "Regular price for the order: $" << regularPrice << "\n";

    if (numSpecialPacks > 0) 
	{
        cout << "Discount price for special packs: $" << specialPackPrice << "\n";
        cout << "Total price for the order (with discount): $" << totalPrice << "\n";
        cout << "Amount saved: $" << regularPrice - totalPrice << "\n";
    } else 
	{
        cout << "No special packs in the order. Total price for the order: $" << regularPrice << "\n";
    }

    return 0;
}

bool checkSackContentsAndWeight(char contents, double weight) 
{
    switch (contents) 
	{
        case 'C':
            return weight >= MIN_CEMENT_WEIGHT && weight <= MAX_CEMENT_WEIGHT;
        case 'G':
            return weight >= MIN_GRAVEL_WEIGHT && weight <= MAX_GRAVEL_WEIGHT;
        case 'S':
            return weight >= MIN_SAND_WEIGHT && weight <= MAX_SAND_WEIGHT;
        default:
            return false;
    }
}

double calculateRegularPrice(char contents) 
{
    switch (contents) 
	{
        case 'C':
            return CEMENT_PRICE;
        case 'G':
            return GRAVEL_PRICE;
        case 'S':
            return SAND_PRICE;
        default:
            return 0.0;
    }
}

double calculateSpecialPackPrice(int cementSacks, int sandSacks, int gravelSacks) 
{
    int numPacks = min({cementSacks, sandSacks / 2, gravelSacks / 2});
    return numPacks * SPECIAL_PACK_PRICE;
}
