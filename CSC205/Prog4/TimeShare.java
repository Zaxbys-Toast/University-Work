import java.util.*;
import java.io.*;
public class TimeShare
{
  public static void main(String[] args)
  {
	Queue q = new Queue();
	input(args, q);
	menu();
	run(q);
	
  }

  public static void menu()
  {
	System.out.println("Job Control Analysis: Summary Report\n");
	System.out.println("job id  arrival  start   run  wait  turnaround");
	System.out.println("        time     time   time  time  time");
	System.out.println("------ -------- ------- ----- ----- -----------");

  }

  public static void run(Queue q)
  {
	int clockTime = 1;
	int waitTime = 0;
	int idleTime = 0;
	int turnaroundTime = 0;
	int time = 0;
	int count = 0;
	int cpuUsageTime = 0;
	while(!q.isEmpty())
	{
		int i = 0;
		Job job =(Job)q.front();
	
		while(job.arrivalTime > clockTime)
		{
			idleTime++;
			clockTime++;
		}		
	
		job.startTime = clockTime;
		job.waitTime = clockTime - job.arrivalTime;
		waitTime += job.waitTime;
		turnaroundTime = job.runTime + job.waitTime;
		job.turnTime = turnaroundTime;
	
		while(i < job.runTime)
		{
			clockTime++;
			i++;
			cpuUsageTime++;	
		}		
		
		System.out.println(q.dequeue().toString());
		count++;		
  	}
	System.out.println("-------------------------------------------");
	System.out.printf("%20s %.2f" ,"Average Wait Time => " , (double)waitTime/count);
	System.out.println("");
	System.out.printf("%25s" ,"CPU Usage => " + cpuUsageTime);
	System.out.println("");
	System.out.printf("%25s" ,"CPU Idle => " + idleTime);
	System.out.println("");
	System.out.printf("%20s %.2f" ,"CPU Usage (%) => " ,(double)((double)cpuUsageTime/(cpuUsageTime + idleTime) * 100));	
	System.out.println("");
  }

  public static void input(String fileName[], Queue q)
  {
	int arrival = 0;
	int runTime = 0;
	String name = fileName[0];
	String job = "";
	if(name.length() < 1)
	{
		System.out.println("No Input File Found");
	}
	else
	{
                try
                {
                        Scanner in = new Scanner(new File(name));
                        while(in.hasNext())
                        {
                                Scanner lsc = new Scanner(in.nextLine()).useDelimiter("\t");

                                job  = lsc.next();
                                arrival  = lsc.nextInt();
                                runTime = lsc.nextInt();
				q.enqueue(new Job(job, arrival, runTime));
                        }
                }
                catch (IOException e)
                {
                        System.out.println(e.getMessage());
                }

	}
  }

}
