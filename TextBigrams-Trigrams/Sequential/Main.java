import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.HashMap;


public class Main
{
    // MAIN
    public static void main(String[] args) throws IOException {
        int default_ngrams = 2; // set n_grams
        int default_nruns = 1;  // set runs number
        boolean showmap = false; // n_grams visualization
        String noVisualizeMap = "n";
        if (args.length > 3) {
            wrongInput();
            return;
        }
        int numberOfGrams = (args.length > 0) ? Integer.parseInt(args[0]) : default_ngrams;
        int numberOfRuns =  (args.length > 1) ? Integer.parseInt(args[1]) : default_nruns;
        String showResult = (args.length > 2) ? args[2] : noVisualizeMap;
        if (showResult.equals("-v")){

             showmap = true;
        }
        else if (args.length == 3){
            System.out.println("wrong input. Insert -v if you want to visualize the hashmap");

        }
        int size;
        List<String> result;
        //load .txt from sample directory
        //  /home/student4/TextBigrams-Trigrams/Java/sample
        try (Stream<Path> walk = Files.walk(Paths.get("/Users/andreasimioni/Desktop/parallelComputing/mid_term_BIGRAMS_TRIGRAMS/TextBigrams-Trigrams/Java/sample"))) {
            result = walk.map(Path::toString)
                    .filter(f -> f.endsWith(".txt")).collect(Collectors.toList());
            size = result.size();
        }
        try (PrintWriter out = new PrintWriter("../result.txt")){
            for (int i = 0; i < size; i++) {
                double avg_time = 0;
                for (int j = 0; j < numberOfRuns; j++) {
                    char[] text = Utils.readAndCleanText(result.get(i));
                    long start, end;
                    start = System.currentTimeMillis();
                    HashMap hmap = Ngrams.computeNGrams(numberOfGrams,text); //compute n_grams
                    end = System.currentTimeMillis();
                    // Print Map
                    if (showmap) {
                        Utils.visualize(hmap);
                    }
                    // Print time
                    double totalTime = ((end - start) / 1000.0);
                    System.out.println(totalTime);
                    avg_time = avg_time + totalTime;
                }
                // print and save average time
                avg_time = avg_time/numberOfRuns;
                System.out.println("average time: ");
                System.out.println(avg_time);
                out.println(avg_time);
            }
        }
    }
    private static void wrongInput() {
        //helper
        String showError = "Too many inputs. Choose only between: \n\t" +
                "Number of ngrams to compute(default 2) \n\t" +
                "Number of runs for each task(default 1)\n\t" +
                "Visualize Results typing -v (default no visualization)";
        String example = "Example: \n\t" +
                "java Main 3 5  \n\t" +
                "java Main 3 5 -v ";

        System.out.println(showError);
        System.out.println(example);
    }
}
