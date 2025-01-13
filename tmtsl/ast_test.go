package main

import (
	"encoding/json"
	"fmt"
	"reflect"
	"testing"

	"github.com/Siposattila/TestMe/tmtsl/ast"
)

func TestAST(t *testing.T) {
	const input = `
            /* comment */
            "class Dog" AS "Dog";

            TEST "Example"
                CALL "Bark"()
                THEN OUTPUT EQUALS "WAU";
			`

	out := &ast.Configuration{
		GlobalDefinitions: []ast.Definition{
			ast.GlobalDefinition{
				Expression: ast.DefinitionExpression{
					Value: ast.StringLiteral{Value: "class Dog"},
					Name:  ast.StringLiteral{Value: "Dog"},
				},
			},
		},
		TestDefinitions: []ast.Definition{
			ast.TestDefinition{
				Name:       "Example",
				GivenBlock: ast.GivenBlock{},
				CallBlock:  ast.CallBlock{Function: "Bark", Arguments: []ast.Expression{}},
				ThenBlock: ast.ThenBlock{
					Expression: ast.TestOperationExpression{
						TestOperation: "OUTPUT",
						Operation:     "EQUALS",
						Expression:    ast.StringLiteral{Value: "\"WAU\""},
					},
				},
			},
		},
	}

	configuration := parse(input)

	js, _ := json.MarshalIndent(configuration, "", "    ")
	jsOut, _ := json.MarshalIndent(out, "", "    ")

	if !reflect.DeepEqual(js, jsOut) {
		fmt.Printf("\n%s\n", js)
		fmt.Println("****************************")
		fmt.Printf("\n%s\n", jsOut)

		t.Fatalf("Wrong AST")
	}

}
