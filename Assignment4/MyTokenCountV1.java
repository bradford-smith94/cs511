/* Bradford Smith (bsmith8)
 * CS 511 Assignment 4 MyTokenCountV1.java
 * 11/07/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

import java.util.HashMap;
import java.util.Set;
import java.util.ArrayList;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Collections;
import java.util.Comparator;
import java.util.concurrent.ArrayBlockingQueue;


public class MyTokenCountV1
{
    private static final HashMap<String, Integer> tokenFreq = new HashMap<String, Integer>();
    private static ArrayBlockingQueue<Page> queue = new ArrayBlockingQueue<Page>(100);

    //https://stackoverflow.com/questions/6463178/is-static-inner-class-thread-safe-inside-another-java-class

    //Producer Thread Runnable
    static class Producer implements Runnable
    {
        private Integer numPages;
        private String arg;
        private ArrayBlockingQueue<Page> queue;

        public Producer(Integer n, String s, ArrayBlockingQueue<Page> q)
        {
            this.numPages = n;
            this.arg = s;
            this.queue = q;
        }

        public void run()
        {
            //System.out.println("Producer started");
            Iterable<Page> allPages = new Pages(this.numPages, this.arg);
            for (Page pg: allPages)
            {
                try
                {
                    this.queue.put(pg);
                }
                catch (Exception e)
                {
                    System.out.println("[ERROR]\tCould not put page on queue!");
                }
            }

            try
            {
                this.queue.put(new PoisonPill());
            }
            catch (Exception e)
            {
                System.out.println("[ERROR]\tCould not put Poison Pill on queue!");
            }
        }
    }

    //Consumer Thread Runnable
    static class Consumer implements Runnable
    {
        private ArrayBlockingQueue<Page> queue;

        public Consumer(ArrayBlockingQueue<Page> q)
        {
            this.queue = q;
        }

        public void run()
        {
            //System.out.println("Consumer started");
            while (true)
            {
                try
                {
                    Page pg = queue.take();

                    if (pg.isPoisonPill())
                        break;

                    Iterable<String> allTokens = new Words(pg.getText());
                    for (String s: allTokens)
                        countToken(s);
                }
                catch (Exception e)
                {
                    System.out.println("[ERROR]\tCould not get page from queue");
                }
            }
        }
    }

    public static void main(String[] args) throws Exception
    {
        if (args.length != 2)
        {
            System.out.println("usage: java MyTokenCountV1 number-of-pages XML-file");
            System.exit(0);
        }
        Integer numPages = Integer.parseInt(args[0]);

        // print number of available processors
        System.out.println(Runtime.getRuntime().availableProcessors() + " available processors");

        Producer p = new Producer(numPages, args[1], queue);
        Consumer c = new Consumer(queue);

        Thread pthread = new Thread(p);
        Thread cthread = new Thread(c);

        /* begin timed code ... */
        final long before = System.nanoTime();

        // parse XML into pages and put them in queue
        pthread.start();
        // on each page, find all tokens then increase the count for each token
        cthread.start();

        try //try to join producer
        {
            pthread.join();
            //System.out.println("Producer joined");
        }
        catch (Exception e)
        {
            System.out.println("[ERROR]\tCould not join producer thread");
        }

        try //try to join consumer
        {
            cthread.join();
            //System.out.println("Consumer joined");
        }
        catch (Exception e)
        {
            System.out.println("[ERROR]\tCould not join consumer thread");
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
