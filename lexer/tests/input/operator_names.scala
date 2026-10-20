object A {
  val + = 1
  val - = 2
  def *(x: Int) = x
  def -(x: Int): Int = x
  x.+(1)
  val t = a +: b ::: c
  val r = a +/* c */ b
  val q = a +// c
  val w = a =/* c */ b
  val v = a /**/ b
}
