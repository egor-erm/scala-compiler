object Expressions {
  def arithmetic(a: Int, b: Int): Int = {
    val sum = a + b
    val difference = a - b
    val product = a * b
    val quotient = a / b
    val remainder = a % b
    val mixed = a + b * 2 - 1
    val grouped = (a + b) * 2
    val shifted = (a << 1) + (b >> 1)
    val masked = (a & 255) | (b & 255)
    val xored = a ^ b
    val negated = -a
    val positive = +b
    val inverted = ~a
    sum + difference + product + quotient + remainder + mixed +
      grouped + shifted + masked + xored + negated + positive + inverted
  }

  def comparisons(a: Int, b: Int): Boolean = {
    val eq = a == b
    val neq = a != b
    val lt = a < b
    val gt = a > b
    val le = a <= b
    val ge = a >= b
    val both = eq && neq
    val either = lt || gt
    val notBoth = !both
    both || either || notBoth || le && ge
  }

  def assignments(): Int = {
    var x = 10
    x = 20
    x += 1
    x -= 2
    x *= 3
    x /= 4
    x %= 5
    x &= 7
    x |= 8
    x
  }

  def literals(): Unit = {
    val i = 42
    val d = 3.14
    val s = "scala 2.13"
    val c = 'x'
    val t = true
    val f = false
    val n = null
    val u = ()
  }

  def precedence(a: Int, b: Int, c: Int): Boolean = {
    val first = a + b * c
    val second = (a + b) * c
    val third = a < b && b < c
    first == second || third
  }
}
