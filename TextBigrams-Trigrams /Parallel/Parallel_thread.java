import java.util.concurrent.Callable;
import java.util.concurrent.ConcurrentHashMap;

public class Parallel_thread implements Callable<ConcurrentHashMap<String, Integer>> {

    private String id;
    private int n;
    private double start, stop;
    private ConcurrentHashMap<String, Integer> n_grams;
    private char[] fileString;


    StringBuilder builder;


    public Parallel_thread (String id, double start, double stop, int n, char[] fileString){   //n is the n-grams dimension

        this.id = id;
        this.start = start;
        this.stop = stop;
        this.n = n;
        this.fileString = fileString;
        this.n_grams = new ConcurrentHashMap();


    }

    public ConcurrentHashMap<String, Integer> call()
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
        return n_grams;
    }
}

