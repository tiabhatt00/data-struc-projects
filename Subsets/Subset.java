
/*
Rudra Bhattacharya
rubhatta
CMPS 12B
Subset.java is a java program that takes in two inputs on the command line and creats k-element subsets from an n-element set
Subset.java
*/
import java.util.Scanner;

public class Subset {

//method converts bit-array and returns string that returns the k-element subsets with the appropriate brackets
	static String setToString(int[] B) {
		// create the printable subset from the bit array B
		String ret = new String();
        ret = ret + "{";
        //case : If there is no element, empty set having space only
        if (B.length == 1) {
            ret = ret + " " + "}";
            return ret;
        }
        //case : If there are numbers in set 1 or more
        for (int i = 1; i <= (B.length-1); ++i) { //ignore the first
            if (B[i] == 1) {
                if(ret.length() > 1) { //there is already some element, add comma and space then nthis number
                    ret = ret + ", ";
                    ret = ret + String.valueOf(i);
                } else {
                    ret = ret + String.valueOf(i);
                }
            }
        }
        ret = ret + "}";
        return ret;
    }
//method printSubsets() implements the recursive algorithim to generate the subsets, using the box trace diagram approach.
//subsets print when the k-value is 0
//validating that subset cannot be of greater length than the set
//printing subset where k is decremented (B value is 1), then where k remains the same 
//i value increases with each implementation 
	static void printSubsets(int B[], int k, int i)
    {
	    //n = number of elements = size of the array
        //k = number of elements yet to be selected for the subset
		if (k == 0) // start printing when k reaches 0
		{
            String subSetStr = setToString(B); // find the printable subset from the bit array B
            System.out.println(subSetStr);
            return;
        }

        if ( i > (B.length-1)) { //subset can't be of greater length
            return;
        }
        //include element at i (left branch k is decremented)
        B[i] = 1;
        printSubsets(B, k-1, i+1);

        //exclude element at i (right branch k remains the same)
        B[i] = 0;
        printSubsets(B, k, i+1);
    }

//method showUsageHelp() to print error message 	 
	public  static void showUsageHelp() {
		// generic method to print error message
	        System.out.println("Usage: Java Subset <int> <int>");
	    }
	
//main() method that initializes required int and arrays, reads the command line arguemnts, calls appropraite functions
    public static void main(String[] args){
        int n = 0;  //n = number of elements = size of the array
        int k = 0;  //k = number of elements yet to be selected for the subset
        
        //case 1. if args length should be 2 (command, n, k)
        if (args.length != 2) {
            showUsageHelp();
            return;
        }
        //case 2. Get the first arg and check if it's not integer return
        try {
            n = Integer.parseInt(args[0]);
        } catch(Exception e) {
            showUsageHelp();
            return;
        }
        // case 3. Get the second arg and check if it's not integer return
        try {
            k = Integer.parseInt(args[1]);
        } catch(Exception e) {
            showUsageHelp();
            return;
        }
        //case 3: If n is less than k
         if (n < k) {
             showUsageHelp();
             return;
         }
         int[] B = new int[n+1]; // create a 'bit' array n+1 for determining what value to print
         for (int i=0; i <= n; ++i) {
             B[i] = 0;
         }
      printSubsets(B, k, 1); //start from i = 1 from the top

} 


}
