import java.util.HashMap;


public class Ngrams {


    public static HashMap<String, Integer> computeNGrams(int n, char[] fileString) {
        // input: n = number of grams ; fileString = text
        // return: HashMap that contains bigrams or trigrams with their occorrence values
        HashMap<String, Integer> hashMap = new HashMap();

        for(int i = 0; i < fileString.length - n + 1; i++) {
            StringBuilder builder = new StringBuilder();

            for(int j = 0; j < n; j++) {
                builder.append(fileString[i + j]);
            }

            String key = builder.toString(); // convert to String

            if (!hashMap.containsKey(key)) {
                hashMap.put(key, 1);
            }
            else{
                hashMap.put(key, hashMap.get(key) + 1);
            }
        }
        return hashMap;
    }


}
