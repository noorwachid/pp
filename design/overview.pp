# typed
# cpp: int typed = 10
var type: Int = 10

# deduced
# cpp: auto deduced = 10
var deduced := 10

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

# reference
# cpp: int& referenceOfInt = int
refer var referenceOfInt: Int = int

# moved-value
# symbol int, pointerOfInt, and referenceOfInt are no longger accesible
# cpp: int&& movedValueOfInt = static_cast<int&&>(int)
move var movedValueOfInt: Int = int 

# tuple
var tuple: Tuple<Bool, Int, String>

# resizable string
var string: String

# fixed string (unerlyingly add 1 for null termination)
var fixedString: FixedString<11> = "hello world"

# non owning sub-string
var mirageString := MirageString(fixedString.data, fixedString.length)

# resizeable array
var array: Array<Int> = { 1, 2, 3 }
array.add(4) 
array.add(5) 

# fixed array 
var fixedArray: FixedArray<Int, 3> = { 1, 2, 3 }

# non owning sub-array
var mirageArray := MirageArray<Int, 2>(fixedArray.data + 1, 2)

# dictionary
var dictionary: Dictionary<String, String> = {
	"int" = "",
}

# dictionary with Array<Tuple<> as underlying memory layout
var arrayDictionary: ArrayDictionary<String, String> = {
	"int" = "",
}

# enum is always scoped
enum State {
	waiting
	inProgress
	resolved
	rejected
}

# struct cannot hold method, constructor and destructor
struct WindowData {
	var title: String
}

class Person {
	# by convention leading underscore is private
    # namespace access :: is replaced by .
	var _name: String
	var _age: int

	# will generate std::string () const
    func toString() -> String {
		return "Person: {0} {1}".format(_name, _age)
    }

	# add set keyword to allow mutation 
	# and add syntaxtic sugar for person.name = "new name"
	# will generate void name(const std::string& name)
	set func name(value: &String) {
		_name = value
	}

	# add get keyword to allow mutation 
	# and add syntaxtic sugar for const name = person.name
	# will generate const std::string& name() const
	get func name() -> &String {
		return _name
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

func main(arguments: Array<String>) -> int {
	return 0;
}
