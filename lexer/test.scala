object Main {
  
  def main(args: Array[String]): Unit = {
    // однострочный комментарий
    /* многострочный
       комментарий 
    */

    val X: Int = 0_2
    val Int = 0_123
    val s = "test \u0041 "

    println(s + X + " " + Int)
    _Hi_+()
  }

  def _Hi_+(): Unit = {
    // однострочный комментарий
    /* многострочный
       комментарий 
       /* 
       вложенный комментарий
       */
    */
    val a = 0b010
    val b = 0x2A
    val c = 101_163
    val d = 21_10.63F
    val x = .53
    val e: Char = 'a'

    println("Hi, Scala! " + a + " " + b + " " + c + " " + d + " " + e + " " + x)
  }
}