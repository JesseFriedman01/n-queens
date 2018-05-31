#include <iostream>
#include <vector>
#include <math.h>   

using namespace std;

//Function declarations
double round (double amount_left_unrounded);
void number_to_cents (double amount, double amount_left);
int n_queens (vector<char> &nums, int nums_size);
void print_vector (vector<char> &nums);
void reverse_vector (vector<char> &nums, int start_pos, int end_pos);
void swap_items (vector<char> &nums, int largestI, int largestJ);
void lexicograph (vector<char>& nums, vector<char>& orig_vector, bool match, int queens_match, string selection);

int main()
{
	int user_num = 0, char_counter = 0, queens_size = 0;
	double amount = 0;
	string selection, keep_going;
	char vector_char;
		
	vector<char> main ( 1 );   
	
	cout<<"EXTRA CREDIT"<<endl<<endl;
	cout<<"A. Enter \"perms\" to see all of the permutations of N characters (stack memory may need to be increased based on # of characters). "<<endl<<endl;
	cout<<"B. Enter \"queens\" to see the solutions to the Queens problem on an N * N board (stack memory may need to be increased based on size of board)."<<endl<<endl;
	cout<<"C. Enter \"change\" to minimum # of coins in N amount of money."<<endl;
	cout<<"-->";
	cin>>selection;
	
	while (true)                                                                                     // user selection
	{
	if (selection == "perms")                                                                  
		{
			cout<<endl;
			cout << "Enter a character: ";                                                           // user can enter their own values to permutate instead of a series of numbers
			cin >> vector_char;
			main[char_counter] = vector_char;        	
			
			cout << endl;	
						
			cout << "Do you have more characters to enter? (enter \"yes\" or \"no\") ";
			cin >> keep_going;
			
			cout << endl;	
			
			if (keep_going == "no")												
				{
				lexicograph(main, main, 0, 0, selection);                                           // call lexicograph with necessary inputs including the vector of characters 
				break;
				}
			else
				main.resize(main.size()+1); 	
			
			char_counter++;
		}
				
		else if (selection == "queens")
		{
			main.resize(main.size()-1);
			
			cout<<endl;
			cout << "Enter a value of the number of rows and columns: ";                           // value entered represents an N x N square board
			cin >> queens_size;
			cout<<endl;
	 				
			main.resize( main.size() + queens_size ); 
					
			for (int i = 0; i < queens_size; i++)                                                  // create a vector 0 - N 
			{
				main[i] = i + '0';
			}
			lexicograph(main, main, 0, 0, selection);										       // call lexicograph with necessary inputs including the vector of characters 
			break;
		}
		
		else if (selection == "change")
		{
		cout<<endl;
		cout << "Enter a dollar amount: ";                                                         // amount is entered in dollar.cents (e.g. 5.54)
		cin >> amount;
		cout<<endl;
		cout<<"The minimum # of coins needed is: "<<endl;
		cout<<endl;
		number_to_cents (amount, amount);                                                          // call number_to_cents with the user entered amount 
		}
		
	else
		{
		cout<<"Invalid selection"<<endl<<endl;
		break;
		}
	}			 
}

// Function definitions  
  
//#####################################################################  
// double round (double amount_left_unrounded)  
// Purpose:  simple function to round a double to 2 decimal places
// Pre-conditions: amount_left_unrounded is a double  
// Post-conditions: returns rounded double  
//######################################################################  

double round (double amount_left_unrounded)
{
	double rounded_num = floor( amount_left_unrounded * 100.00 + 0.5 ) / 100.00;           // round double to 2 decimal places to accurately represent dollar.change format
	return rounded_num;
}

//#####################################################################  
// void number_to_cents (double amount, double amount_left) 
// Purpose:  recursively identifies the minimum number of coins to 
// represent a user entered amount of dallars and cents
// Pre-conditions: amount is a double, amount_left is a double
// Post-conditions: returns rounded double  
//######################################################################  

void number_to_cents (double amount, double amount_left)
{
	if (amount_left>0)                                                                     // recursive while there is still an amount of money left after subtracting N number of coin type (i.e. quarters, dimes, etc.) 
	{
		if (amount_left > .25)															   // if the amount left is greater than a quarter, calculate # of times (N) .25 goes into that value
		{
		
			double coin_val = .25;	
			int amount_div = amount/coin_val;
			cout<<amount_div<<" quarter(s)"<<endl;										   // output number of quarters
			amount_left = amount - (amount_div * coin_val);                                // amount left is original amount minus N # of quarters
			amount_left = round (amount_left);                                             // call round to round the amount left to 2 decimal places
	
		}
		
		else if (amount_left >= .1 && amount_left < .25)                                   // see comments above and this is for an amount left greater than a dime and less than a quarter (i.e. dimes)
		{
			double coin_val = .1;	
			int amount_div = amount_left/coin_val;
			cout<<amount_div<<" dime(s)"<<endl;
			amount_left = amount_left - (amount_div * coin_val);
			amount_left = round (amount_left);
	
		}
		
		else if (amount_left >= .05 && amount_left < .1)									// see comments above and this is for an amount left greater than a nickel and less than a penny (i.e. nickels)
		{
			
			double coin_val = .05;	
			int amount_div = amount_left/coin_val;
			cout<<amount_div<<" nickle(s)"<<endl;
			amount_left = amount_left - (amount_div * coin_val);
			amount_left = round (amount_left);

		}
		
		else if (amount_left < .05)															// see comments above and this is for an amount left less than a nickel (i.e. pennies)
		{
			double coin_val = .01;	
			int amount_div = amount_left/coin_val;
			cout<<amount_div<<" pennie(s)"<<endl;
			amount_left = amount_left - (amount_div * coin_val);
			amount_left = round (amount_left);
		
		}
	
		number_to_cents (amount,amount_left);												// RECURSIVE -- call number to cents with original amount and amount left as inputs
	
	}
}

//#####################################################################  
// double round (double amount_left_unrounded)  
// Purpose:  places "Queens" (represented by a 1) in an N x N 
// 2 dimensional array as per the combination received from the vector 
// nums. Checks each "Queen" to determine if that "Queen" has any other
// "Queens" in its diagonal.
// Pre-conditions: nums is a vector with integers in character format 
// Post-conditions: returns 1 if the current configuration of "Queens"
// has no conflicts. 
//######################################################################  

int n_queens (vector<char> &nums, int nums_size)
{
	int array_size = nums_size;
	
	int square_array[array_size][array_size];                                             // create a 2D array of user entered size
			
    for (int n=0; n<nums_size; n++)                                                       // fill the array with all zeros 
    {
	    for (int m=0; m<nums_size; m++)
	    	square_array[n][m]=0;
	}
	
	for (int j = 0; j < nums.size(); j++)                                                 // as per the combination sent from lexicograph place 1's in array (a 1 is a Queen). 
		square_array[j][nums[j] - '0'] = 1; 

	int conflict_counter = 0;
	int array_counter = 0; 
	
	for (int m = 0; m < nums.size(); m++)                                                 // iterate through each row of the array
	{
		int counter = 1; 
	
		while (m - counter >= 0)                                                          // make sure we aren't checking elements outside of the size of the array
		{
		if  ( (nums[m] - '0') - counter < 0)
			break;
				
		if (square_array[m-counter][(nums[m] - '0') -counter] == 1)                       // if the value in an element is a 1, check all of the values on the Northeast diagonal. 
          	conflict_counter ++;                                                          // if another 1 is found, increment conflict_counter
   			
		counter++;
		}
		
		counter = 1;
		
		while ((nums[m] - '0') < nums.size() -1 )
        {
         if (m + counter > nums.size() -1)
           break;
           
        if ((nums[m] - '0') + counter > nums.size() -1)
           break;

        if ( square_array[m+counter][(nums[m]- '0')+counter] == 1 )               	    // if the value in an element is a 1, check all of the values on the Southwest diagonal. 
             conflict_counter ++;													    // if another 1 is found, increment conflict_counter
   
        counter ++;
		}
			
		counter = 1;
			
		while ( (  (nums[m]- '0')  - counter) >= 0)
		{
			if ((nums[m]- '0') + counter > nums.size() -1)
               break;
               
            if (m-counter < 0)
            	break;
			
			if ( square_array[m-counter][(nums[m]- '0')+counter] == 1 )                // if the value in an element is a 1, check all of the values on the Northwest diagonal. 
                conflict_counter ++;												   // if another 1 is found, increment conflict_counter
       		
			counter ++;
		}
		
		counter = 1;
		
		while ( ((nums[m]- '0')  - counter) >= 0)
		{
			
		if (m + counter > nums.size() -1)
           break;

		if ( square_array[m+counter][(nums[m]- '0')-counter] == 1 )				     	// if the value in an element is a 1, check all of the values on the Southeast diagonal. 
           conflict_counter ++;												       	    // if another 1 is found, increment conflict_counter
    			
		counter ++;
		}
	}

	if (conflict_counter == 0)                        
	{
		for (int n = 0; n < nums.size(); n++)                                           // the commented code would display the actual board.
	    {
		    for (int m = 0; m < nums.size(); m++)
		    	cout << square_array[n][m] << " ";
		    
			cout << endl;	  
		}
		cout << endl;	  
		
		return 1;                                                                       // return a 1 if the are no Queens in conflict with each other
	}
	else
		return 0;

}

//#####################################################################  
// void print_vector (vector<char> &nums)
// Purpose: simply print the vector for each permutation. 
// Pre-conditions: nums is a vector of characters
// Post-conditions: none
//######################################################################  

void print_vector (vector<char> &nums)
{
	cout << endl;
	
	for (int j = 0; j < nums.size(); j++)
	{
		if (j < nums.size() - 1)
			cout << nums[j] << ",";
		else 
			cout << nums[j];
	}
}

//#####################################################################  
// void reverse_vector (vector<char> &nums, int start_pos, int end_pos)
// Purpose: reverses characters in a vector based on the rules for
// lexicographical ordering
// Pre-conditions: nums is a vector of characters, start_pos and end_pos
// are integer values that both exists within the length of the vector
// Post-conditions: none
//######################################################################  

void reverse_vector (vector<char> &nums, int start_pos, int end_pos)
{
	int char_temp;
	
	if (end_pos - start_pos >= 1)                                        // continue as there are characters left to reverse                                 
    {
		char_temp = nums[start_pos];                                     // hold character in start position in char_temp
		nums[start_pos] = nums[end_pos];                          		 // swap character in start position with character in end position
		nums[end_pos] = char_temp;                                       // swap character is end position with character in char_temp
		start_pos++;                                                     // increment start_pos
		end_pos--;                                                       // decrement end_pos
		reverse_vector (nums, start_pos, end_pos);                       // RECURSION -- call reverse_vector with a modified start_pos and end_pos
	}	
}

//#####################################################################  
// void swap_items (vector<char> &nums)
// Purpose: finds the "largestI" and "largestJ" based on the rules for
// lexicographical ordering and swaps them. It then calls reverse_vector
// to reverse the remainder of the vector. 
// Pre-conditions: nums is a vector of characters, start_pos and end_pos
// are integer values that both exists within the length of the vector
// Post-conditions: none
//######################################################################  

void swap_items (vector<char> &nums)
{
	int temp;
	
	int largestI = -1;
	
	int nums_size = nums.size();
	
	for (int i = 0; i < nums_size - 1; i++)
	{
		if (nums[i] < nums[i + 1])
			largestI=i;                                         // largestI is largest I such that P[I] < P[I+1]
	}
		
	int largestJ = -1;
	
	for (int j = largestI+1; j < nums_size; j++)
	{
		if (nums[largestI] < nums[j] )
			largestJ=j;                                        // LargestJ is largest J such that P[I]<P[J].
	}
		
	if (largestI != -1)
	{
	temp = nums[largestI];                                     // swap largestI with LargestJ
	nums[largestI] = nums[largestJ];
	nums[largestJ] = temp;
	}	
	
	reverse_vector(nums, largestI + 1, nums_size - 1);         // reverse remainder of vector after a position largestI + 1
}

//#####################################################################  
// void lexicograph (vector<char>& nums, vector<char>& orig_vector...)
// Purpose: recursively creates permutations for either the displaying of
// these permutations or for sending these permutations to n_queens for 
// further analysis. Also increments a counter per the number of n_queens
// valid configurations and displays it. 
// Pre-conditions: nums is a vector of characters, orig_vector is a 
// vector containing the same elements as per the user's original entry
// Post-conditions: none
//######################################################################  

void lexicograph (vector<char>& nums, vector<char>& orig_vector, bool match, int queens_match, string selection)
{
	int nums_size = nums.size();
	
	vector<char> nums_copy = nums;                                  						 // addresses a bug in which the original user entry was not being passed accurately in certain instances 
		
	if (match == 1)                                                  			   			 // once a permutation matches the original user entry, there are no more permutations left. If so, stop recursion (base-case). 
	{	
		if (selection == "queens")
		cout<<"There are "<<queens_match<<" configurations."<<endl;
	}
	else
	{
		
	swap_items (nums_copy);
	
	if (selection == "perms")
		print_vector(nums);
	
	if (selection == "queens")
		queens_match = queens_match + n_queens(nums_copy, nums.size());                     // increment queens_match by 1 each time a valid board is found 
		
	lexicograph(nums_copy, orig_vector, nums_copy == orig_vector, queens_match, selection);   // RECURSION -- call lexicograph until there are no more permutation 
	}
}



