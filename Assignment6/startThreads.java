import java.lang.*;
 

public class startThreads implements Runnable {

	String[] words;
	int left;
	int right;
	int depth;
	int depthMax;
	public startThreads(String[] wordList, int lefts,int rights, int depths,int maxDepth) {
		words = wordList;
		left = lefts;
		right = rights;
		depth = depths;
		depthMax = maxDepth;
	}


	public void run() {
		
		sorting sort = new sorting();
		

		try {
            sorting.quickSort(left, right,depth,depthMax);
        } catch (InterruptedException ex) {
            
        }

	}


}