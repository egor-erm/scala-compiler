object Exceptions {
  def risky(n: Int): Int = {
    if (n < 0) throw new RuntimeException("negative")
    n
  }

  def guarded(n: Int): Int = {
    try {
      risky(n)
    } catch {
      case e: RuntimeException => 0
      case e: Exception => -1
    } finally {
      println("done")
    }
  }

  def nested(): Int = {
    try {
      try {
        throw new IllegalStateException("inner")
      } catch {
        case e: IllegalStateException => 1
      }
    } catch {
      case e: Exception => 2
    } finally {
      0
    }
  }

  def earlyReturn(n: Int): Int = {
    if (n < 0) {
      return 0
    }
    return n * 2
  }

  def safeDivide(a: Int, b: Int): Int = {
    val result = try {
      a / b
    } catch {
      case e: ArithmeticException => 0
    }
    result
  }
}
