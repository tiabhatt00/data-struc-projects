/*
Rudra Bhattacharya
rubhatta
CMPS 12B
Queens.java a java program that finds all solutions to n-Queens. print solutions in -v mode, otherwise print number of solutions
Queens.java 
*/
import java.util.Scanner;
import java.util.Arrays;

public class Queens {

	public static void main(String[] args) {
		//initialize integer n and String mode 
		//assign String value as "-v", for the verbose mode option
		int n = 0;
		String mode = "-v";

		//if command line has one arugument, check that it is an integer value, else print error message and exit
		if (args.length ==1){
			//validate that first arguement is integer, parse string value to integer so it can be used as n-number of Queens
        	try {
            	n = Integer.parseInt(args[0]);
        	} 
        	catch(Exception e) {
            	showError();
        	}
		}
		//if command line has two arguemnts, validate that first is correct String value for verbose mode, and that second is integer value
		else if (args.length == 2) {
			//validate that first arguement is correct String value, else return error message
			if (!(args[0].equals(mode))) {
				showError();
			}
			//validate that second arguemnt is integer, parse string value to integer so it can be used as n-number of Queens
			try {
            	n = Integer.parseInt(args[1]);
        	} 
        	catch(Exception e) {
            	showError();
        	}
		}
		// if there is <1 or >2 arguements, print error message and exit 
		else {
			showError();
		}
		// create two dimensional bit-array 
		int[][] B = new int[(n+1)][(n+1)];
		// if first arguement calls verbose mode then print print board 
		if(args[0].equals("-v"))  {
			n = findSolutions(B, 1, "-v");
			System.out.println(args[1]+" " + "Queens has " + n + " solutions"); //start at args[1] bc first arg is "-v"
		}
		else {
			n = findSolutions(B, 1, "");
			System.out.println(args[0]+" " + "Queens has " + n + " solutions");
		}		

	}
	// method increments array from its initial value of 0 to 1 and sets B[i][0] to j
	//decrement B[k][l] 
	public static void placeQueen (int[][] B, int i, int j) {
		//intiliaze values 
	    B[i][0] = j;//increments B[i][j] from  0 to 1
	    B[i][j] = 1; //sets B[i][0] to j 


		for (int k = i+1; k <= B.length - 1; k++) {
			B[k][j] = B[k][j] - 1;
			if((j + k - i) <= B.length - 1){
				B[k][j + k - i] = B[k][j + k - i] -1;
			}
			if((j - k + i) >= 1){
				B[k][j - k + i] = B[k][j - k + i] -1;
			}
		}
	}
	//undoes everything the first function does,
	//decrements B[i][j] from initial value 
	//resets 𝐵[𝑖][0] from 𝑗 to 0
	//increments B[k][l] for every square 
	public static void removeQueen (int[][] B, int i, int j) {
		//initialize values 
		B[i][j] = 0;
		B[i][0] = 0;
		for (int k = i+1; k <=B.length - 1; k++) {
			B[k][j] = B[k][j] + 1;
			if((j + (k - i)) <= B.length - 1){
				B[k][j + k - i] = B[k][j + k - i] +1;
			}
			if((j - (k - i)) >= 1){
				B[k][j - k + i] = B[k][j - k +i ]+1;
			}
		}
	}

	//print board with all values where queens are place
	public static void printBoard(int[][] B) {
		System.out.print("("); //add openeing brace
		for(int j = 1; j <= B.length - 1;j++){

			if( j != B.length - 1) {
				System.out.print(B[j][0] + ", ");
			}
		else {
				System.out.println(B[j][0] + ")");//and of recur, prints closing brace
			}
		}

	}
//if string arguement has value verbose, then method prints our solutions by calling printBoard, otherwise it prints just the number of solutions 
	public static int findSolutions(int[][] B, int i, String mode) {
		int sum = 0;
		if(i > B.length - 1){
			if(mode.equals("-v")){ //if in verbose mode
			printBoard(B);
			}
			return 1;
		}
		else{
			for(int j = 1; j <= B.length - 1; j++){
				if(B[i][j] == 0){
					placeQueen(B, i, j);//place queen
					sum += findSolutions(B, i + 1, mode);
					removeQueen(B, i, j);//remove queen
				}
			}
		}
		return sum;
	}

	//method to print error message 
	public static void showError() {
		System.out.println("Usage: Queens [-v] number\nOption: -v  verbose output, print all solutions");
		System.exit(1);
	}

}