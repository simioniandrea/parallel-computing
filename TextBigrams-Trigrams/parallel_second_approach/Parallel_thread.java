import java.util.HashMap;
import java.util.concurrent.ConcurrentHashMap;

public class Parallel_thread implements Runnable {

    private String id;
    private int n;
    private double start, stop;
    private HashMap<String, Integer> n_grams;
    private char[] fileString;
    ConcurrentHashMap<String, Integer> finalNgrams;
    StringBuilder builder;


    public Parallel_thread (String id, double start, double stop, int n, char[] fileString, ConcurrentHashMap<String, Integer> finalNgrams){   //n is the n-grams dimension

        this.id = id;
        this.start = start;
        this.stop = stop;
        this.n = n;
        this.fileString = fileString;
        this.finalNgrams = finalNgrams;
        this.n_grams = new HashMap<>();


    }

    public void run()
    //calculate n_grams and merge into finalNgrams
    {
        if (stop > fileString.length-1)
        {
            stop = fileString.length-1;
        }

        for (double i = this.start + n - 1; i <= this.stop; i++)
        {
            builder = new StringBuilder();      
            for (double j = n - 1; j >= 0; j--)
            {
                builder.append(this.fileString[(int)(i - j)]);
            }

            String key = builder.toString();
            if(!this.n_grams.containsKey(key))
            {
                this.n_grams.put(builder.toString(), 1);
            }
            else
            {
                if(this.n_grams.containsKey(key))
                {
                    this.n_grams.put(builder.toString(), this.n_grams.get(key) + 1);
                }
            }

        }
        //merge
        for (ConcurrentHashMap.Entry<String, Integer> entry : n_grams.entrySet()) {
            int newValue = entry.getValue();
            Integer existingValue = finalNgrams.get(entry.getKey());
            if (existingValue != null) {
                newValue = newValue + existingValue;
            }
            finalNgrams.put(entry.getKey(), newValue);
        }

    }
}

