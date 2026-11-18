abstract class Shape(val name: String) {
  def area(): Double

  def describe(): String = name
}

final class Rectangle(val width: Double, val height: Double) extends Shape("rectangle") {
  private var cached = 0.0

  def this(size: Double) = this(size, size)

  override def area(): Double = width * height

  override def describe(): String = "rectangle"

  protected def scale(factor: Double): Double = {
    cached = area() * factor
    cached
  }

  def scaledArea(factor: Double): Double = scale(factor)
}

sealed class Counter(private var value: Int) {
  def increment(): Int = {
    value += 1
    value
  }

  def current(): Int = value
}

object Shapes {
  def main(args: Array[String]): Unit = {
    val rectangle = new Rectangle(2.0, 3.0)
    val square = new Rectangle(4.0)
    val area = rectangle.area()
    val scaled = rectangle.scaledArea(2.0)
    val counter = new Counter(0)
    counter.increment()
    counter.increment()
    println(area)
    println(scaled)
    println(counter.current())
  }
}
