package main

const (
	ROLL_DICE = 0
	DO_THIS = 1
)

type actionStruct struct {
	action int
	valueToAction int
	expectedReturn int
}

type stateStruct struct {
	stateOfDice int
	stateOfAnotherThing int
	// ...
}

type testStruct struct {
	action	actionStruct
	state stateStruct
}

func main() {
	tests := []testStruct{}

	// Add stuff to tests

	for _, test := range(tests) {
		var returnValue int
		switch test.action.action {
			case ROLL_DICE:
				returnValue = game.rollDice(tests.action.valueToAction)
			case DO_THIS:
				returnValue = game.doThis(tests.aciton.valueToAction)
		}

		assert(test.action.expectedReturn == returnValue)

		assert(test.state.stateOfDice == game.getDice())
		assert(test.state.stateOfAnotherThing == game.getAnotherThing())

		// over and over again

	}
}

