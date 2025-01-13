package main

import "testing"

func TestParser(t *testing.T) {
	const input = `
			/* comment */
            TEST "Example"
                GIVEN "XY" AS "parameter"
                CALL "Method"()
                THEN OUTPUT EQUALS "parameter";

            TEST "Example"
                GIVEN 12 AS "number1", 12 AS "number2"
                CALL "Method"("number1", "number2")
                THEN RESULT EQUALS 24;

            TEST "Example"
                CALL "Method"()
                THEN OUTPUT EQUALS "XY";

            TEST "Example"
                GIVEN "XY" AS "parameter", OBJECT "Object" {
                   "property":"YY"
                } AS "object"
                CALL "Method"("parameter")
                THEN "object"."property" EQUALS "parameter";

            TEST "Example"
                GIVEN "XY" AS "parameter", OBJECT "Object1" {
                   "property":"YY"
                } AS "object1",
                OBJECT "Object2" {} AS "object2"
                CALL "Method"("parameter")
                THEN "object1"."property" EQUALS "parameter";
			`

	parse(input)
}
