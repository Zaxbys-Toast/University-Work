public class Clock{
	private int hours;
	private int minutes;
	private int seconds;
	public void Clock(int myHours, int myMin, int mySec){
		hours = myHours;
		minutes = myMin;
		seconds = mySec;
	}
	public void Clock(){
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	public void reset(){
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	public void reset(int myHours, int myMin, int mySec){
		hours = myHours;
		minutes = myMin;
		seconds = mySec;
	}
	public void advance(){
		seconds += 1;
		if (seconds > 59){
			seconds = 0;
			minutes = minutes + 1;
		}
		if (minutes > 59){
			minutes = 0;
			hours = hours + 1;
		}
		if (hours > 23){
			hours = 0;
		}
	}
	public String toString(){
		String time = "";
		if (hours < 10){
			time += '0';
		}
		time += hours + ":";
		if (minutes < 10){
			time += '0';	
		}
		time += minutes + ":";
		
		if (seconds < 10){
			time += '0';
		}	
		time += seconds;
		return time;
		
	}
}
