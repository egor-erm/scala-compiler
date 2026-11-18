import scala.collection

final class Box(val value: Int) extends Base(value) {
  def this(other: Int) = this()

  def abstractMethod(x: Int): Int

  def calculate(x: Int): Int = {
    var result = x
    result += 1
    if (result > 0) result else 0
  }

  def loops(n: Int): Int = {
    var i = 0
    while (i < n) {
      i += 1
    }
    do {
      i -= 1
    } while (i > 0)
    for (j <- 0 to n) {
      i += j
    }
    return i
  }

  def expressions(size: Int): Int = {
    val a = new Array[Int](size)
    val b = Array[Int](1, 2)
    val c = Array(1, 2)
    val d = Array.fill[Int](2)
    val e = new Box(1)
    val f = -size
    val g = true
    val h = null
    val i = 'x'
    val j = 1.5
    val k = "text"
    val u = ()
    try {
      throw e
    } catch {
      case x: Int =>
        x
    } finally {
      0
    }
  }
}

object Main {
  def main(args: Array[String]): Unit = {
    println(new Box(1).calculate(2))
  }
}
