import scala.collection.mutable

class Animal(val name: String) {
  def speak(): String = "..."

  def describe(): String = name + " says " + speak()

  def parent(): Animal = this
}

class Dog(name: String) extends Animal(name) {
  override def speak(): String = "Woof"

  override def describe(): String = super.describe()
}

final class Puppy(name: String) extends Dog(name) {
  override def speak(): String = "Yip"
}

object Zoo {
  def makeSound(animal: Animal): String = animal.speak()

  def main(args: Array[String]): Unit = {
    val dog = new Dog("Rex")
    val puppy = new Puppy("Bit")
    val animals = Array("dog", "puppy")
    println(makeSound(dog))
    println(makeSound(puppy))
    println(dog.describe())
    println(animals.length)
  }
}
