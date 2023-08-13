# TYPE INSTANCIATION
# typed
# cpp: int typed = 10
var type: Int = 10

# deduced
# cpp: auto deduced = 10
var deduced = 10

# constant
const pi: Float = 3

# primitive
var bool: Bool

var int: Byte
var short: Short
var int: Int
var long: Long
var longLong: LongLong

var float: Float
var double: Double

# pointer
var pointerOfInt: *Int = null

# address of 
pointerOfInt = &int

# underlying data pointed
print(*pointerOfInt)

pointerOfAnimal = new Animal()
# syntactic sugar for (*pointerOfInt).speak()
pointerOfAnimal:speak()


# reference
# cpp: int& referenceOfInt = int
refer var referenceOfInt: Int = int

# moved-value
# symbol int, pointerOfInt, and referenceOfInt are no longger accesible
# cpp: int&& movedValueOfInt = static_cast<int&&>(int)
move var movedValueOfInt: Int = int 

# BUILT-IN TYPE
# optional
var optionalInt: Optional<Int>

# tuple
var tuple: Tuple<Bool, Int, String>
tuple.0 = true
tuple.1 = 123
tuple.3 = "whoa"

# resizable string
var string: String

# fixed string (unerlyingly add 1 for null termination)
var fixedString: FixedString<11> = "hello world"

# non owning sub-string
var mirageString = MirageString(fixedString.data, fixedString.length)

# resizeable array
var array: Array<Int> = { 1, 2, 3 }
array.add(4) 
array.add(5) 

# fixed array 
var fixedArray: FixedArray<Int, 3> = { 1, 2, 3 }

# non owning sub-array
var mirageArray = MirageArray<Int, 2>(fixedArray.data + 1, 2)

# key, value type with hash table
var dictionary: Dictionary<String, String> = {
	"int" = "",
}

# key, value type without hash table
# Array<Tuple<Key, Value>> as underlying memory layout 
var thesaurus: Thesaurus<String, String> = {
	"int" = "",
}

# USER DEFINED TYPE

# enum is always scoped
enum State {
	waiting
	inProgress
	resolved
	rejected
}

# namespace 
namespace OS {
	# struct cannot hold method, constructor and destructor
	struct WindowData {
		var title: String
	}
}

# bleed the namespace to the current file only
use OS

class Enemy {
	# by convention leading underscore is private
    # namespace access :: is replaced by .
	var _id: ECS.ID
	var _name: String
	var _age: Int
	var _health: Int
	var _damage: Int

    func restore() {
		_health = 100
    }

	# overridable by derived class
	virtualize func attack(refer var player: Player) {
		player.health -= _damage
	}

	# add set keyword to allow mutation 
	# and add syntaxtic sugar for person.name = "new name"
	set func name(value: String) {
		_name = value
	}

	# add get keyword to allow mutation 
	# and add syntaxtic sugar for const name = person.name
	get func name() -> String {
		return _name
	}
}

# derived class
class WizardHead: Enemy {
	# override virtual function
	override func attack(refer var player: Player) {
		player.health -= damage
		player.mana -= damage / 2
	}
}

class Vector {
	var x: Float
	var y: Float
	var z: Float

	get func length() -> Float {
		return Math.sqrt(x * x + y * y + z * z)
	}

	operate func mult(other: &Vector) -> Vector {
		return 
	}
}

# USER DEFINED FUNCTION

func main(arguments: Array<String>) -> int {
	return 0
}

func affect(refer var int: Int) {
	int++
}

# CONTROL FLOW

if true || false {
	print("it's true")
}

if true && false && !false {
	print("it's not happening")
} else {
	print("it's happening")
}

var number = 10

switch number {
	case 1 {
		print("one")
	}
	case 2 {
		print("two")
	}
	case 3 || 4 {
		print("three or four")
	}
	default {
		print("unknown")
	}
}

# LOOP
# good-old for loop
for var i = 0; i < 10; i++ {
	print(i)
}

# range-based loop
for i in 1...10 {
	print(i)
}

# while loop
for true {
}

# no do {} while() who needed it anyway


