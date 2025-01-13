package ast

import "fmt"

func astError(function, expected, variable string, got interface{}) error {
	return fmt.Errorf("AST construction error: In function: %s, expected %s for %s. got: %T", function, expected, variable, got)
}

func NewDefinitionList() ([]Definition, error) {
	return []Definition{}, nil
}

func AppendDefinition(definitions, definition Attribute) ([]Definition, error) {
	ds, ok := definitions.([]Definition)
	if !ok {
		return nil, astError("AppendDefinition", "[]Definition", "definitions", definitions)
	}

	d, ok := definition.(Definition)
	if !ok {
		return nil, astError("AppendDefinition", "Definition", "definition", definition)
	}

	return append(ds, d), nil
}
