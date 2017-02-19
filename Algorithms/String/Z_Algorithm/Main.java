import java.util.Scanner;
import java.util.Vector;


public class Main
{
    public static void main (String args[])
    {
        String text,subString;

        Scanner sc = new Scanner (System.in);

        System.out.println("Enter the Text: ");
        text = sc.nextLine();

        System.out.println("Enter Substring");
        subString= sc.nextLine();

        ZAlgorithm a = new ZAlgorithm(subString,text);
        a.clearZArray();
        Vector<Integer> matches = a.findExactMatches();

        if(matches.size() == 0){
            System.out.println("No matches");
        }
        else {
            System.out.println("Mathces occurred at:");
            for (int i = 0; i < matches.size(); i++) {
                System.out.println(matches.get(i));
            }
        }
    }
}