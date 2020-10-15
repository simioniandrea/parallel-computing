import java.util.HashMap;
import java.util.concurrent.*;

public class HashMerge {

    public static ConcurrentHashMap<String, Integer> merge(HashMap<String, Integer> n_grams, ConcurrentHashMap<String, Integer> finalNgrams) {
        // Marge n_grams in finalNgrams

        //long s, e;
        //s = System.currentTimeMillis();
        for (ConcurrentHashMap.Entry<String, Integer> entry : n_grams.entrySet()) {
            int newValue = entry.getValue();
            Integer existingValue = finalNgrams.get(entry.getKey());
            if (existingValue != null) {
                newValue = newValue + existingValue;
            }
            finalNgrams.put(entry.getKey(), newValue);
        }

        // e = System.currentTimeMillis();
        // System.out.println(e - s);
        // Tested that all HashMerge executes in 3 - 4  ms for 300 mb text

        return finalNgrams;
    }
}
