namespace CSharpTutorials {
class Program {
  static void Main(string[] args) {
    string message = "Hello World!!";
    Console.WriteLine(message);
  }

  static void Method() {
    string message = "Method";
    Console.WriteLine(message);
  }

  static void Method(string message) { Console.WriteLine(message); }

  static void JustMethod() { string method = "method"; }
}
}
