import java.lang.*;

public class sorting {


	static String[] words;
	static int depth;
	static boolean split;
	static int depthMax;


	public static void quickSort(String[] wordlist,int depths, int maxDepth) throws InterruptedException {

        depth = depths;
		words = wordlist;
		depthMax = maxDepth;
		long start = System.currentTimeMillis();
        quickSort(0, words.length - 1,depth,maxDepth);
        long end = System.currentTimeMillis();
        long time = end - start;
        System.out.println();
        System.out.println("Time: " + time);
    }



    public static void quickSort(int left,int right, int depths, int maxDepth) throws InterruptedException   {
    	depthMax = maxDepth;
    	depth = depths;

    	if(left >= right)
    		return;



	    int partition = partition(left, right);

        if(depth < depthMax) {

	        Thread thread1 = new Thread(new startThreads(words, left, partition-1,depth++,depthMax));
	        thread1.start();
	        Thread thread2 = new Thread(new startThreads(words, partition+1, right,depth++,depthMax));
	        thread2.start();
	        thread1.join();
	        thread2.join();

    	}	
    	else {
    		
	        normal_quickSort(left, right);
    		
    	}
    }


    private static void normal_quickSort(int left,int right){

        if(left >= right)
            return;
        
        
        int partition = partition(left, right);
        
        normal_quickSort(left, partition-1);
        normal_quickSort(partition+1, right);

    }


   

    private static int partition(int left,int right){
        String x = words[right];
        int i = left-1;
        for(int j=left; j<right;j++) {
        	if(words[j].trim().toLowerCase().compareTo(x.trim().toLowerCase()) > 0) {
        		i = i+1;
        		exchange(i,j);
        	}
        }
        exchange(i+1,right);



        return i+1;
    }


	public static void exchange(int left,int right){
        String temp = words[left];
        words[left] = words[right];
        words[right] = temp;
    }

}