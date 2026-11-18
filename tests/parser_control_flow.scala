object ControlFlow {
  def classify(n: Int): String = {
    if (n < 0) "negative"
    else if (n == 0) "zero"
    else "positive"
  }

  def sumTo(n: Int): Int = {
    var i = 0
    var acc = 0
    while (i <= n) {
      acc += i
      i += 1
    }
    acc
  }

  def countdown(n: Int): Int = {
    var i = n
    do {
      i -= 1
    } while (i > 0)
    i
  }

  def evenSquares(limit: Int): Int = {
    var total = 0
    for (i <- 0 to limit if i % 2 == 0) {
      total += i * i
    }
    total
  }

  def nested(rows: Int, cols: Int): Int = {
    var count = 0
    for (r <- 0 to rows) {
      for (c <- 0 to cols if c != r) {
        count += 1
      }
    }
    count
  }

  def blockValue(x: Int): Int = {
    val value = {
      val doubled = x * 2
      doubled + 1
    }
    if (value > 10) value else x
  }

  def guards(limit: Int): Int = {
    var found = 0
    for {
      i <- 1 to limit
      if i % 3 == 0
      if i % 5 != 0
    } {
      found += i
    }
    found
  }
}
