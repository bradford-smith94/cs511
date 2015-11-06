/* Bradford Smith (bsmith8)
 * CS 511 Assignment 4 MyTokenCountV2.java
 * 11/06/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

import java.util.HashMap;
import java.util.Set;
import java.util.ArrayList;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Collections;
import java.util.Comparator;


public class MyTokenCountV2
{
    private static final HashMap<String, Integer> tokenFreq = new HashMap<String, Integer>();

    public static void main(String[] args) throws Exception
    {
        if (args.length != 2)
        {
            System.out.println("usage: java TokenCount number-of-pages XML-file");
            System.exit(0);
        }
        Integer numPages = Integer.parseInt(args[0]);

        // print number of available processors
        System.out.println(Runtime.getRuntime().availableProcessors() + " available processors");

        /* begin timed code ... */
        final long before = System.nanoTime();
        // parse XML into pages
        Iterable<Page> allPages = new Pages(numPages, args[1]);
        // on each page, find all tokens then increase the count for each token
        for (Page pg: allPages)
        {
            Iterable<String> allTokens = new Words(pg.getText());
            for (String s: allTokens)
                countToken(s);
        }
        final long after = System.nanoTime();
        /* ... end  timed code */

        System.out.println("Time to process " + numPages + " pages = " + (after - before)/1000000 + " milliseconds");

        // sort tokenFreq by value & print top 30 most common tokens
        Set<Entry<String, Integer>> entries = tokenFreq.entrySet();
        ArrayList<Entry<String, Integer>> list = new ArrayList<Entry<String, Integer>>(entries);
        Collections.sort(list, new Comparator<Map.Entry<String, Integer>>()
                {
                    public int compare(Map.Entry<String, Integer> obj1, Map.Entry<String, Integer> obj2)
                    {
                        return (obj2.getValue()).compareTo(obj1.getValue());
                    }
                } );
        for(int i=0; i<30; i++)
            System.out.println(list.get(i).getKey() + " appears " + list.get(i).getValue() + " times");
    }

    private static void countToken(String tok)
    {
        Integer currentCount = tokenFreq.get(tok);
        if (currentCount == null)
            tokenFreq.put(tok, 1);
        else
            tokenFreq.put(tok, currentCount + 1);
    }
}
