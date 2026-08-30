import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class ToCSVFile 
{
    public static PrintWriter getWriter(String filename) 
    {
        try 
        {
            // create or overwrite dataset file
            return new PrintWriter(new FileWriter(filename));
        } catch (IOException e) {
            System.out.println("Error writing to CSV file.");
            e.printStackTrace();
            return null;
        }
    }
}
