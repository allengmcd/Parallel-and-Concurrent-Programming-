import java.io.*;
import java.lang.*;

public class McDermott_hw6 {

	public static void main(String[] args) {
		if(args.length < 3) {
			System.out.println("Must provide a read file, # of threads, and a write file");
			return;
		}
		int size = 0;
		String fileName = args[0];
		try {
            // FileReader reads text files in the default encoding.
            FileReader fileReader = 
                new FileReader(fileName);

            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader = 
                new BufferedReader(fileReader);
            int i = 0;
            while(bufferedReader.readLine() != null) {

                
            	i++;
            }   
            size=i;
            // Always close files.
            bufferedReader.close();         
        }
        catch(Exception ex) {
            System.out.println(
                "Unable to open file '" + 
                fileName + "'");                
        }



        String[] words = new String[size];
	        

	        //String fileName = "words.txt";

        // This will reference one line at a time
        String line = null;

        try {
            // FileReader reads text files in the default encoding.
            FileReader fileReader = 
                new FileReader(fileName);

            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader = 
                new BufferedReader(fileReader);
            int i = 0;
            while((line = bufferedReader.readLine()) != null) {

                words[i] = line;
            	i++;
            }   

            // Always close files.
            bufferedReader.close();         
        }
        catch(Exception ex) {
            System.out.println(
                "Unable to open file '" + 
                fileName + "'");                
        }


        

        try {
       		sorting.quickSort(words,0,Integer.parseInt(args[1]));
       	}
       	catch(Exception ex) {
       		
       	}
        try { 
            Writer writer = new BufferedWriter(new OutputStreamWriter(
          new FileOutputStream(args[2]), "utf-8"));
            for(int i = words.length-1; i>-1;i--) {
                 writer.write(words[i]+"\n");
            }
            writer.close();
        }
        catch(Exception ex) {

        }
	}

}