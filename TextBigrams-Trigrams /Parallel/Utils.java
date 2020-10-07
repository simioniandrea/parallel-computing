import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Utils {
    public static char[] readAndCleanText(String s) {
        // Read from the text and remove special characters ( ();:,. ). Also set all in Lowercase
        Path path = Paths.get(s);
        System.out.println("path: " + s);

        try {
            Stream<String> lines = Files.lines(path);
            char[] filestring = (lines.collect(Collectors.joining())).replaceAll("[{}? \" % $ £ & - + \\[\\]'();:,.]", "").toCharArray();

            for(int i = 0; i < filestring.length - 1; ++i) {
                if (Character.isUpperCase(filestring[i])) {
                    filestring[i] = Character.toLowerCase(filestring[i]);
                }
            }
            return filestring;
        }
        catch (IOException e) {
            System.out.println(e);
            System.exit(1);
            return null;
        }
    }

    public static void visualize(ConcurrentHashMap<String, Integer> finalHashMap){
        // Print keys and values
        Set set = finalHashMap.entrySet();
        for (Object o : set) {
            Map.Entry map_entry = (Map.Entry) o;
            System.out.print("key: " + map_entry.getKey() + " , value: ");
            System.out.println(map_entry.getValue());
        }
    }









}
