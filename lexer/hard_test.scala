object Main {
   def main(args: Array[String]): Unit = {
      // однострочный комментарий
      /* многострочный
         тест
         комментарий 
      */
      val x: Int = 0_2
      val Int = 0_123
      
      val s = "hello world"

      val
      a = 1
      + 2

      val ab = (1
      + 2)

      val ac = 1 +
      3

      val ad = 1
      +3

      val + = 2

      println("Hello, Scala! " + a + " " + ab + " " + ac + " " + ad)
      println("Hello, Scala! " + x + " " + Int + " " + +)

      demo();
   }

   def demo(): Unit = {
      // ---------- if ----------
      val x = 10
      val y = 45
      if (x > 5) {
         println("x больше 5")
      } else {
         println("x не больше 5")
      }

      if (x > 5
      && y > 55) {
         println("test1")
      } else {
         println("test2")
      }

      // ---------- while ----------
      var i = 0
      while (i < 3) {
         println(s"while: i = $i")
         i += 1
      }

      // ---------- for ----------
      for (n <- 1 to 3) {
         println(s"for: n = $n")
      }
      }
}