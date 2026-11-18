object Arrays {
  def builders(size: Int): Int = {
    val buffer = new Array[Int](size)
    val literal = Array[Int](1, 2, 3)
    val inferred = Array(4, 5, 6)
    val filled = Array.fill[Int](size)(0)
    val first = literal(0)
    val combined = buffer.length + literal.length + inferred.length
    first + combined
  }

  def matrix(rows: Int): Int = {
    val grid = new Array[Array[Int]](rows)
    val row = new Array[Int](rows)
    grid.length + row.length
  }

  def chained(size: Int): Int = {
    val text = new StringBuilder("abc")
    text.append("d").append("e")
    val result = new StringBuilder("x").append("y").length
    val scaled = Array.fill[Int](size)(1).length
    result + scaled + text.length
  }

  def main(args: Array[String]): Unit = {
    println(builders(3))
    println(matrix(2))
    println(chained(4))
  }
}
