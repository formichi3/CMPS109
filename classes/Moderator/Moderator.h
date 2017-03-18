template <typename T>
// The Moderator class takes data from the parser and distributes it to the KB and RB.
class Moderator {
   Moderator(); // will be variadic constructor taking in all types of data 
   Moderator~();
   virtual T add(T); // adds an entity to the RB or KB database
   virtual T remove(T); // removes an entity to the RB or KB database 
   virtual T infer(T); // return all facts that follow a rule
   virtual T dump(T) // dumps all rules and facts into a file
   virtual T load() // loads rules and facts from a file into database
}
