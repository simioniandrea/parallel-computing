import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.concurrent.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;


public class Main {


    public static void awaitTerminationAfterShutdown(ExecutorService threadPool) {
        threadPool.shutdown();
        try {
            if (!threadPool.awaitTermination(60, TimeUnit.SECONDS)) {
                threadPool.shutdownNow();
            }
        } catch (InterruptedException ex) {
            threadPool.shutdownNow();
            Thread.currentThread().interrupt();
        }
    }

    // MAIN
    public static void main(String[] args) throws IOException {
        int default_ngrams = 2;   // set n_grams
        int default_nruns = 1;    // set runs number
        int defaul_n_thread = 4;  // set threads number
        boolean showmap = false;  // nGrams visualization
        String noVisualizeMap = "n";
        if (args.length > 4) {
            wrongInput();
            return;
        }
        int n_g = (args.length > 0) ? Integer.parseInt(args[0]) : default_ngrams;
        if ( n_g < 2 || n_g > 3){
            System.out.println("Invalid n. Choose between 2 or 3.");
            return;
        }
        int numberOfRuns =  (args.length > 1) ? Integer.parseInt(args[1]) : default_nruns;
        int n_thread = (args.length > 2) ? Integer.parseInt(args[2]) : defaul_n_thread;
        String showResult = (args.length > 3) ? args[3] : noVisualizeMap;
        if (showResult.equals("-v")){

            showmap = true;
        }
        else if (args.length == 4){
            System.out.println("wrong input. Insert -v if you want to visualize the hashmap");
        }

        int size;
        List<String> result;
        //load .txt from sample directory /Users/andreasimioni/Desktop/parallelComputing/mid_term_BIGRAMS_TRIGRAMS/TextBigrams-Trigrams copia 2/Java/sample
        ///home/student4/TextBigrams-Trigrams/Java/sample
        try (Stream<Path> walk = Files.walk(Paths.get("/home/student4/TextBigrams-Trigrams/Java/sample"))) {
            result = walk.map(Path::toString)
                    .filter(f -> f.endsWith(".txt")).collect(Collectors.toList());
            size = result.size();
        }
        try (PrintWriter out = new PrintWriter("result.txt")){
            for (int p = 0; p < size; p++) {
                double avg_time = 0;
                boolean too_short = false;
                for (int j = 0; j < numberOfRuns; j++) {
                    char[] text = Utils.readAndCleanText(result.get(p));  // read text
                    int fileLen = text.length;  // save text length

                    ConcurrentHashMap<String, Integer> finalNgrams = new ConcurrentHashMap<>(); // Create ConcurrentHashMap <gram, value>
                    ExecutorService exec = Executors.newFixedThreadPool(n_thread); // create the threads

                    long start, end;

                    start = System.currentTimeMillis();
                    double k = Math.floor(fileLen / n_thread); // divide text according to number of threads
                    if (k == 0.0){
                        System.out.println("Text is too short for the number of thread chosen. Insert a lower number.");
                        too_short = true;
                    }
                    for (int i = 0; i < n_thread; i++) {
                        exec.submit(new Parallel_thread("t" + i, i * k, ((i + 1) * k) + (n_g - 1) - 1, n_g, text,finalNgrams)); //executor.submit start the runnable
                    }
                    try {
                        awaitTerminationAfterShutdown(exec);
                        end = System.currentTimeMillis();

                        // Print Map
                        if (showmap) {
                            Utils.visualize(finalNgrams);
                        }
                        double totalTime = ((end - start) / 1000.0);
                        System.out.println(totalTime);
                        avg_time = avg_time + totalTime;
                    } catch (Exception e) {
                        System.out.println(e);
                    }
                }
                avg_time = avg_time / numberOfRuns;
                //print and save average time
                System.out.println("average time: ");
                System.out.println(avg_time);
                if (!too_short) {
                    out.println(avg_time);
                }
            }
        }
    }
    private static void wrongInput() {
        //helper
        String showError = "Too many inputs. Choose only between: \n\t" +
                "Number of ngrams to compute. Choose 2 or 3 (default 2) \n\t" +
                "Number of runs for each task(default 1)\n\t" +
                "Number of threads(default 4)\n\t" +
                "Visualize Results typing -v (default no visualization)";
        String example = "Example: \n\t" +
                "java Main 3 5  \n\t" +
                "java Main 3 5 2  \n\t" +
                "java Main 3 5 2 -v ";

        System.out.println(showError);
        System.out.println(example);
    }



}
