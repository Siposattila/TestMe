package ast

import (
	"fmt"

	"github.com/Siposattila/TestMe/tmtsl/token"
)

func astError(function string, expected string, variable string, got interface{}) error {
	return fmt.Errorf("AST construction error: In function: %s, expected %s for %s. got=%T", function, expected, variable, got)
}

func (c *Configuration) TokenLiteral() string { return "Configuration" }

func NewConfiguration(testDefinitions, globalDefinitions Attribute) (*Configuration, error) {
	t, ok := testDefinitions.([]Definition)
	if !ok {
		return nil, astError("NewConfiguration", "[]Definition", "testDefinitions", testDefinitions)
	}

	g, ok := globalDefinitions.([]Definition)
	if !ok {
		return nil, astError("NewConfiguration", "[]Definition", "globalDefinitions", globalDefinitions)
	}

	return &Configuration{TestDefinitions: t, GlobalDefinitions: g}, nil
}

func (td *TestDefinition) definitionNode()      {}
func (td *TestDefinition) TokenLiteral() string { return "TestDefinition" }

func NewTestDefinition(name, givenBlock, callBlock, thenBlock Attribute) (*TestDefinition, error) {
	n, ok := name.(Expression)
	if !ok {
		return nil, astError("NewTestDefinition", "StringLiteral", "name", name)
	}

	g, ok := givenBlock.(GivenBlock)
	if !ok {
		return nil, astError("NewTestDefinition", "GivenBlock", "givenBlock", givenBlock)
	}

	c, ok := callBlock.(CallBlock)
	if !ok {
		return nil, astError("NewTestDefinition", "CallBlock", "callBlock", callBlock)
	}

	t, ok := thenBlock.(ThenBlock)
	if !ok {
		return nil, astError("NewTestDefinition", "ThenBlock", "thenBlock", thenBlock)
	}

	return &TestDefinition{Name: n, GivenBlock: &g, CallBlock: &c, ThenBlock: &t}, nil
}

func NewTestDefinitionList() (*[]Definition, error) {
	return &[]Definition{}, nil
}

func AppendTestDefinition(testDefinitions, testDefinition Attribute) (*[]Definition, error) {
	ts, ok := testDefinitions.([]Definition)
	if !ok {
		return nil, astError("AppendTestDefinition", "[]Definition", "testDefinitions", testDefinitions)
	}

	t, ok := testDefinition.(TestDefinition)
	if !ok {
		return nil, astError("AppendTestDefinition", "TestDefinition", "testDefinition", testDefinition)
	}

	ts = append(ts, &t)

	return &ts, nil
}

func (gd *GlobalDefinition) definitionNode()      {}
func (gd *GlobalDefinition) TokenLiteral() string { return "GlobalDefinition" }

func NewGlobalDefinition(expression Attribute) (*GlobalDefinition, error) {
	e, ok := expression.(Expression)
	if !ok {
		return nil, astError("NewGlobalDefinition", "Expression", "expression", expression)
	}

	return &GlobalDefinition{Expression: e}, nil
}

func NewGlobalDefinitionList() (*[]Definition, error) {
	return &[]Definition{}, nil
}

func AppendGlobalDefinition(globalDefinitions, globalDefinition Attribute) (*[]Definition, error) {
	gs, ok := globalDefinitions.([]Definition)
	if !ok {
		return nil, astError("AppendGlobalDefinition", "[]Definition", "globalDefinitions", globalDefinitions)
	}

	g, ok := globalDefinition.(GlobalDefinition)
	if !ok {
		return nil, astError("AppendGlobalDefinition", "GlobalDefinition", "globalDefinition", globalDefinition)
	}

	gs = append(gs, &g)

	return &gs, nil
}

func (gb *GivenBlock) expressionNode()      {}
func (gb *GivenBlock) TokenLiteral() string { return gb.Token.StringValue() }

func NewGivenBlock(givenExpressions Attribute) (*GivenBlock, error) {
	ge, ok := givenExpressions.([]Expression)
	if !ok {
		return nil, astError("NewGivenBlock", "[]Expression", "givenExpressions", givenExpressions)
	}

	return &GivenBlock{Expressions: ge}, nil
}

func NewGivenExpressionList() (*[]Expression, error) {
	return &[]Expression{}, nil
}

func AppendGivenExpression(givenExpressions, givenExpression Attribute) (*[]Expression, error) {
	gs, ok := givenExpressions.([]Expression)
	if !ok {
		return nil, astError("AppendGivenExpression", "[]Expression", "givenExpressions", givenExpressions)
	}

	ge, ok := givenExpression.(Expression)
	if !ok {
		return nil, astError("AppendGivenExpression", "Expression", "givenExpression", givenExpression)
	}

	gs = append(gs, ge)

	return &gs, nil
}

func (cb *CallBlock) expressionNode()      {}
func (cb *CallBlock) TokenLiteral() string { return cb.Token.StringValue() }

func NewCallBlock(function, arguments Attribute) (*CallBlock, error) {
	f, ok := function.(Identifier)
	if !ok {
		return nil, astError("NewCallBlock", "Identifier", "function", function)
	}

	as, ok := arguments.([]Expression)
	if !ok {
		return nil, astError("NewCallBlock", "[]Expression", "arguments", arguments)
	}

	return &CallBlock{Function: f, Arguments: as}, nil
}

func NewArgumentList() (*[]Expression, error) {
	return &[]Expression{}, nil
}

func AppendArgument(arguments, argument Attribute) (*[]Expression, error) {
	as, ok := arguments.([]Expression)
	if !ok {
		return nil, astError("AppendArgument", "[]Expression", "arguments", arguments)
	}

	a, ok := argument.(Expression)
	if !ok {
		return nil, astError("AppendArgument", "Expression", "argument", argument)
	}

	as = append(as, a)

	return &as, nil
}

func (tb *ThenBlock) expressionNode()      {}
func (tb *ThenBlock) TokenLiteral() string { return tb.Token.StringValue() }

func NewThenBlock(expression Attribute) (*ThenBlock, error) {
	e, ok := expression.(Expression)
	if !ok {
		return nil, astError("NewThenBlock", "Expression", "expression", expression)
	}

	return &ThenBlock{Expression: e}, nil
}

func (i *Identifier) expressionNode()      {}
func (i *Identifier) TokenLiteral() string { return i.Token.StringValue() }

func NewIdentifier(value Attribute) (*Identifier, error) {
	v, ok := value.(string)
	if !ok {
		return nil, astError("NewIdentifier", "string", "value", value)
	}

	return &Identifier{Value: v}, nil
}

func (il *IntegerLiteral) expressionNode()      {}
func (il *IntegerLiteral) TokenLiteral() string { return il.Token.StringValue() }

func NewIntegerLiteral(value Attribute) (*IntegerLiteral, error) {
	v, ok := value.(int)
	if !ok {
		return nil, astError("NewIntegerLiteral", "int", "value", value)
	}

	return &IntegerLiteral{Value: v}, nil
}

func (sl *StringLiteral) expressionNode()      {}
func (sl *StringLiteral) TokenLiteral() string { return sl.Token.StringValue() }

func NewStringLiteral(value Attribute) (*StringLiteral, error) {
	v, ok := value.(*token.Token)
	if !ok {
		return nil, astError("NewStringLiteral", "*token.Token", "value", value)
	}

	return &StringLiteral{Token: v, Value: v.StringValue()}, nil
}

func (toe *TestOperationExpression) expressionNode()      {}
func (toe *TestOperationExpression) TokenLiteral() string { return toe.Token.StringValue() }

func NewTestOperationExpression(testOperation, operation, value Attribute) (*TestOperationExpression, error) {
	t, ok := testOperation.(string)
	if !ok {
		return nil, astError("NewTestOperationExpression", "string", "testOperation", testOperation)
	}

	o, ok := operation.(string)
	if !ok {
		return nil, astError("NewTestOperationExpression", "string", "operation", operation)
	}

	v, ok := value.(Expression)
	if !ok {
		return nil, astError("NewTestOperationExpression", "Expression", "value", value)
	}

	return &TestOperationExpression{TestOperation: t, Operation: o, Value: v}, nil
}

func (de *DefinitionExpression) expressionNode()      {}
func (de *DefinitionExpression) TokenLiteral() string { return de.Token.StringValue() }

func NewDefinitionExpression(value, id Attribute) (*DefinitionExpression, error) {
	v, ok := value.(Expression)
	if !ok {
		return nil, astError("NewDefinitionExpression", "Expression", "value", value)
	}

	i, ok := id.(Identifier)
	if !ok {
		return nil, astError("NewDefinitionExpression", "Identifier", "id", id)
	}

	return &DefinitionExpression{Value: v, Id: i}, nil
}

func (o *Object) expressionNode()      {}
func (o *Object) TokenLiteral() string { return o.Token.StringValue() }

func NewObject(name, properties Attribute) (*Object, error) {
	n, ok := name.(Identifier)
	if !ok {
		return nil, astError("NewObject", "Identifier", "name", name)
	}

	p, ok := properties.([]ObjectProperty)
	if !ok {
		return nil, astError("NewObject", "[]ObjectProperty", "properties", properties)
	}

	return &Object{Name: n, Properties: p}, nil
}

func NewObjectProperty(key, value Attribute) (*ObjectProperty, error) {
	k, ok := key.(StringLiteral)
	if !ok {
		return nil, astError("AppendObjectProperty", "StringLiteral", "key", key)
	}

	v, ok := value.(Expression)
	if !ok {
		return nil, astError("AppendObjectProperty", "Expression", "value", value)
	}

	return &ObjectProperty{Key: k, Value: v}, nil
}

func NewObjectPropertyList() (*[]ObjectProperty, error) {
	return &[]ObjectProperty{}, nil
}

func AppendObjectProperty(objectProperties, objectProperty Attribute) (*[]ObjectProperty, error) {
	os, ok := objectProperties.([]ObjectProperty)
	if !ok {
		return nil, astError("AppendObjectProperty", "[]ObjectProperty", "objectProperties", objectProperties)
	}

	o, ok := objectProperty.(ObjectProperty)
	if !ok {
		return nil, astError("AppendObjectProperty", "ObjectProperty", "objectProperty", objectProperty)
	}

	os = append(os, o)

	return &os, nil
}
