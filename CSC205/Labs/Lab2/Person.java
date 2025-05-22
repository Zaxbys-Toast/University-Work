public class Person
{
  private String name;
  private int    id;
  private static int personCount = 0;

  // constructor
  public Person(String pname)
  {
    name = pname;
    personCount++;
    id = 100 + personCount;
  }
//Makes a default person object with a name NA and an ID of -1
  public Person(){
    this.name = "N/A";
    personCount++;
    this.id = -1;
  }
 //Returns the name and id of a person object as a string	
  public String  toString()
  {
    return "name: " + name + "  id: " + id 
      + "  (Person count: " + personCount + ")";
  }

  // static/class method
  public static int getCount()
  {
    return personCount;
  }
//Reset to make person class mutable
  public void reset(String pname,int newId)
 {
   name = pname;
   id = newId;
 } 
//Getter methods
  public String getName()
 {
   return name;
 }
  public int getId()
 {
   return id;
 }
}
