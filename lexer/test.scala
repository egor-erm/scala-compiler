
@main def hello(): Unit = {
   // однострочный комментарий
   /* многострочный
      комментарий 
   */

   val X: Int = 0_2
   val Int = 0_123
   val s = "test \u0041 "

   println(s + X + " " + Int)
   _Hi()
}

def _Hi(): Unit = {
   // однострочный комментарий
   /* многострочный
      комментарий 
   */
   val a = 0b010
   val b = 0x2A
   val c = 101_163
   val d = 21_10.63F
   val e: Char = 'a'

   println("Hi, Scala! " + a + " " + b + " " + c + " " + d + " " + e)
}